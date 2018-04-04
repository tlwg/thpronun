// parser.cxx - Thai syllable parser class
// Author: Theppitak Karoonboonyanan <theppitak@gmail.com>
// Created: 2018-03-13

#include "parser.h"
#include "thortho/thuni.h"
#include "sylstring/sylstring.h"

#include <locale>
#include <codecvt>
#include <thai/thwctype.h>
#include <cassert>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/////////////////////////
//  Utility Functions  //
/////////////////////////

ETone
ThCharToTone (char16_t c)
{
    static const unordered_map<char16_t, ETone> ThCharToToneTbl_ = {
        { UTH_MAI_EK,       ETone::EK       },
        { UTH_MAI_THO,      ETone::THO      },
        { UTH_MAI_TRI,      ETone::TRI      },
        { UTH_MAI_CHATTAWA, ETone::CHATTAWA },
    };

    assert (th_wcisthtone (c));
    return ThCharToToneTbl_.at (c);
}

EVowel
ThCharToAboveBelowVowel (char16_t c)
{
    static const unordered_map<char16_t, EVowel> ThCharToAboveBelowVowelTbl_ = {
        { UTH_SARA_I,   EVowel::I   },
        { UTH_SARA_II,  EVowel::II  },
        { UTH_SARA_UE,  EVowel::UE  },
        { UTH_SARA_UEE, EVowel::UEE },
        { UTH_SARA_U,   EVowel::U   },
        { UTH_SARA_UU,  EVowel::UU  },
    };

    assert (th_wcisupvowel (c) || th_wcisblvowel (c));
    return ThCharToAboveBelowVowelTbl_.at (c);
}


//////////////////
//  ParseState  //
//////////////////

struct ParseState {
    int         pos;
    SylString   sylString;
    bool        isLinked;

public:
    ParseState();
    ParseState (int pos, const SylString& sylString, bool isLinked = false);
    ParseState (const ParseState& other);
    ParseState (ParseState&& other);

    ParseState& operator= (const ParseState& other);
};

inline
ParseState::ParseState()
    : pos (0), sylString(), isLinked (false) {}

inline
ParseState::ParseState (int pos, const SylString& sylString, bool isLinked)
    : pos (pos), sylString (sylString), isLinked (isLinked) {}

inline
ParseState::ParseState (const ParseState& other)
    : pos (other.pos), sylString (other.sylString), isLinked (other.isLinked) {}

inline
ParseState::ParseState (ParseState&& other)
    : pos (other.pos),
      sylString (move (other.sylString)),
      isLinked (other.isLinked) {}

ParseState&
ParseState::operator= (const ParseState& other)
{
    pos       = other.pos;
    sylString = other.sylString;
    isLinked  = other.isLinked;
}

//////////////////
//  State Pool  //
//////////////////

class StatePool {
public:
    void    add (const ParseState& state);
    bool    pop (ParseState& state);

private:
    list<ParseState>    mStates;
};

void
StatePool::add (const ParseState& state)
{
    mStates.push_back (state);
}

bool
StatePool::pop (ParseState& state)
{
    if (mStates.empty())
        return false;

    state = mStates.front();
    mStates.pop_front();
    return true;
}


///////////////////////
//  Parse Functions  //
///////////////////////

// Partial Syllable: intermediate construct of syllable during parsing
struct PartialSyl {
    int             pos;            // current matched pos in word string

    bool            hasPreSyl;      // whether preSyl is available
    Syl             preSyl;         // pre-syllable in case of อักษรนำอะกึ่งเสียง

    EInitConsSound  iConsSound;     // initial consonant sound
    EInitConsClass  iConsClass;     // effective class of the initial consonant
    ESecInitCons    iCons2;         // second cons in case of อักษรควบ
    EVowel          vowel;          // vowel as analyzed
    EEndConsClass   eConsClass;     // ending consonant class
    ETone           tone;           // written tone

public:
    // c-tor with pre-syllable
    PartialSyl (int             pos,
                const Syl&      preSyl,
                EInitConsSound  iConsSound = EInitConsSound::INVALID,
                EInitConsClass  iConsClass = EInitConsClass::INVALID,
                ESecInitCons    iCons2 = ESecInitCons::NONE,
                EVowel          vowel = EVowel::INVALID,
                EEndConsClass   eConsClass = EEndConsClass::NONE,
                ETone           tone = ETone::INVALID);

    // c-tor without pre-syllable
    PartialSyl (int             pos,
                EInitConsSound  iConsSound = EInitConsSound::INVALID,
                EInitConsClass  iConsClass = EInitConsClass::INVALID,
                ESecInitCons    iCons2 = ESecInitCons::NONE,
                EVowel          vowel = EVowel::INVALID,
                EEndConsClass   eConsClass = EEndConsClass::NONE,
                ETone           tone = ETone::INVALID);
};

inline
PartialSyl::PartialSyl (int             pos,
                        const Syl&      preSyl,
                        EInitConsSound  iConsSound,
                        EInitConsClass  iConsClass,
                        ESecInitCons    iCons2,
                        EVowel          vowel,
                        EEndConsClass   eConsClass,
                        ETone           tone)
    : pos (pos),
      hasPreSyl (true),
      preSyl (preSyl),
      iConsSound (iConsSound),
      iConsClass (iConsClass),
      iCons2 (iCons2),
      vowel (vowel),
      eConsClass (eConsClass),
      tone (tone)
{
}

inline
PartialSyl::PartialSyl (int             pos,
                        EInitConsSound  iConsSound,
                        EInitConsClass  iConsClass,
                        ESecInitCons    iCons2,
                        EVowel          vowel,
                        EEndConsClass   eConsClass,
                        ETone           tone)
    : pos (pos),
      hasPreSyl (false),
      preSyl(),
      iConsSound (iConsSound),
      iConsClass (iConsClass),
      iCons2 (iCons2),
      vowel (vowel),
      eConsClass (eConsClass),
      tone (tone)
{
}

static SylString
AddSyl (const SylString& s, const PartialSyl& p)
{
    SylString r = s;

    if (p.hasPreSyl) {
        r += p.preSyl;
    }

    bool isDeadSyl = (EEndConsClass::NONE == p.eConsClass)
                         ? IsShortVowel (p.vowel)
                         : IsDeadEndConsClass (p.eConsClass);
    r += Syl (p.iConsSound, p.iCons2, p.vowel, p.eConsClass,
              ToneFromWritten (p.iConsClass, p.tone,
                               isDeadSyl, IsShortVowel (p.vowel)));

    return r;
}

static inline bool
IsSylStart (char16_t c)
{
    return th_wcisthcons (c) || th_wcisldvowel (c);
}

// Match initial consonant part of the syllable form
// Returns whether the match is successful
static list<PartialSyl>
MatchInitCons (const u16string& u16word, const ParseState& state)
{
    list<PartialSyl> partialSyls;
    auto firstCons = u16word.at (state.pos);
    auto firstConsSound = InitConsSound (firstCons);
    auto firstConsClass = InitConsClass (firstCons);

    if (state.pos + 1 < u16word.size() &&
        th_wcisthcons (u16word.at (state.pos + 1)))
    {
        auto secCons = u16word.at (state.pos + 1);
        auto secConsSound = InitConsSound (secCons);
        auto secConsClass = InitConsClass (secCons);

        // check อักษรควบแท้
        // (อักษรควบไม่แท้ "ทร" are supposed to be in exception dict)
        switch (secCons) {
        case UTH_RO_RUA:
            switch (firstCons) {
            case UTH_CHO_CHAN:
            case UTH_SO_SO:
            case UTH_SO_SALA:
            case UTH_SO_SUA: {
                // add อักษรควบไม่แท้
                if (state.isLinked)
                    break;
                partialSyls.push_back (
                    PartialSyl (state.pos + 2, firstConsSound, firstConsClass)
                );
                break;
            }

            case UTH_KHO_KHAI:
            case UTH_KHO_KHWAI:
            case UTH_DO_DEK:
            case UTH_THO_THAHAN:
            case UTH_BO_BAIMAI:
            case UTH_PHO_PHAN:
            case UTH_FO_FAN:
                if (state.isLinked)
                    break;
                // fall through for non-linked syllable
                // examples of linked syllable with อักษรควบแท้:
                // จักรี, มาตรา, ศัตรู, อัปรีย์
            case UTH_KO_KAI:
            case UTH_TO_TAO:
            case UTH_PO_PLA:
                // add อักษรควบแท้
                partialSyls.push_back (
                    PartialSyl (state.pos + 2,
                                firstConsSound,
                                firstConsClass,
                                ESecInitCons::RA)
                );
                break;
            }
            break;
        case UTH_LO_LING:
            switch (firstCons) {
            case UTH_KO_KAI:
            case UTH_KHO_KHAI:
            case UTH_KHO_KHWAI:
            case UTH_BO_BAIMAI:
            case UTH_PO_PLA:
            case UTH_PHO_PHUNG:
            case UTH_PHO_PHAN:
            case UTH_FO_FAN:
                if (state.isLinked)
                    break;
                // add อักษรควบแท้
                partialSyls.push_back (
                    PartialSyl (state.pos + 2,
                                firstConsSound,
                                firstConsClass,
                                ESecInitCons::LA)
                );
                break;
            }
            break;
        case UTH_WO_WAEN:
            switch (firstCons) {
            case UTH_KO_KAI:
            case UTH_KHO_KHAI:
            case UTH_KHO_KHWAI:
                if (state.isLinked)
                    break;
                // add อักษรควบแท้
                partialSyls.push_back (
                    PartialSyl (state.pos + 2,
                                firstConsSound,
                                firstConsClass,
                                ESecInitCons::WA)
                );
                break;
            }
            break;
        }

        // check อักษรนำเสียงสนิท
        if (UTH_HO_HIP == firstCons &&
            EInitConsClass::LOWS == InitConsClass (secCons))
        {
            // add อักษรนำเสียงสนิท
            partialSyls.push_back (
                PartialSyl (state.pos + 2,
                            secConsSound,
                            EInitConsClass::HIGH)
            );
        }

        // always add อักษรนำอะกึ่งเสียง
        // - with second consonant's own class,
        //   e.g. กมุท, ขมา, สมา, สรีระ, สราญ, หริภุญชัย, อรุโณทัย
        partialSyls.push_back (
            PartialSyl (state.pos + 2,
                        Syl (InitConsSound (firstCons), ESecInitCons::NONE,
                             EVowel::A, EEndConsClass::NONE,
                             ToneFromWritten (InitConsClass (firstCons),
                                              ETone::SAMAN, true, true)),
                        secConsSound,
                        secConsClass)
        );
        // - using first consonant's class,
        //   e.g. ขนม, ขมิบ, จรวด, จมูก, เฉลิม, โตนด, ตลาด, ผลิต, สนิม, สยบ, สรุป,
        //   สลาย, สวรรค์, สวัสดี, อร่อย, อร่าม
        if (EInitConsClass::LOWS == secConsClass &&
            (EInitConsClass::HIGH == firstConsClass ||
             EInitConsClass::MID == firstConsClass))
        {
            partialSyls.push_back (
                PartialSyl (state.pos + 2,
                            Syl (InitConsSound (firstCons), ESecInitCons::NONE,
                                EVowel::A, EEndConsClass::NONE,
                                ToneFromWritten (InitConsClass (firstCons),
                                                ETone::SAMAN, true, true)),
                            secConsSound,
                            firstConsClass)
            );
        }
    }

    // add single initial consonant sound
    partialSyls.push_back (
        PartialSyl (state.pos + 1, firstConsSound, firstConsClass)
    );

    return partialSyls;
}

// Match ending consonant part of the syllable form, simple version
// Returns whether the match is successful
static bool
EatEndConsSimple (const u16string& u16word, const ParseState& state,
                  PartialSyl& p, StatePool& pool)
{
    auto c = u16word.at (p.pos);
    if (th_wcisthcons (c) && EEndConsClass::NONE != EndConsClass (c)) {
        p.eConsClass = EndConsClass (c);
        ++p.pos; // skip the end cons class

        // add single non-linking ending consonant
        pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));

        return true;
    }

    return false;
}

// Match ending consonant part of the syllable form, complex version
// Returns whether the match is successful
static bool
EatEndConsComplex (const u16string& u16word, const ParseState& state,
                   PartialSyl& p, StatePool& pool)
{
    static const unordered_set<char16_t> afterClusterVowels = {
        UTH_SARA_A,
        UTH_MAI_HAN_AKAT,
        UTH_SARA_AA,
        UTH_SARA_I,
        UTH_SARA_II,
        UTH_SARA_U,
        UTH_SARA_UU,
    };

    auto c = u16word.at (p.pos);
    if (th_wcisthcons (c) && EEndConsClass::NONE != EndConsClass (c)) {
        p.eConsClass = EndConsClass (c);

        // add single non-linking ending consonant
        pool.add (ParseState (p.pos + 1, AddSyl (state.sylString, p)));

        // check for sylable-linking case like จัตุรัส, จักรี, จักรา, มาตรา,
        // มัสยา, มัสมั่น, ศัตรู
        if (p.pos + 1 < u16word.size()) {
            auto clusterEnd = p.pos + 1;
            c = u16word.at (clusterEnd);
            if (th_wcisthcons (c)) {
                ++clusterEnd; // skip second ending consonant
                if (clusterEnd == u16word.size())
                    goto word_done;
                c = u16word.at (clusterEnd);
            }
            if (afterClusterVowels.find (c) != afterClusterVowels.end()) {
                // Linking syllable: add this syllable without consuming
                // the ending cons, and pass the ending cons over to
                // next syllable
                pool.add (ParseState (p.pos,
                                      AddSyl (state.sylString, p),
                                      true));
            }
        }
    word_done:
        return true;
    }

    return false;
}

// Progress the parsing from given state, where a Thai consonant was found.
static void
ParseThCons (const u16string& u16word, ParseState& state, StatePool& pool)
{
    list<PartialSyl> partialSyls = MatchInitCons (u16word, state);

    for (auto& p : partialSyls) {
        if (p.pos >= u16word.size()) {
            continue;
        }
        auto c = u16word.at (p.pos);
        p.tone = ETone::SAMAN;
        if (UTH_MAI_HAN_AKAT == c) {
            ++p.pos; // skip MAI HAN AKAT
            if (p.pos >= u16word.size())
                continue;
            c = u16word.at (p.pos);
            if (th_wcisthtone (c)) {
                // read tone
                p.tone = ThCharToTone (c);
                ++p.pos; // skip the tone mark
                if (p.pos >= u16word.size())
                    continue;
                c = u16word.at (p.pos);
            }
            if (UTH_WO_WAEN == c) {
                // วัว, รั้ว, ยัวะ, จั๊วะ
                ++p.pos; // skip WO WAEN
                if (p.pos < u16word.size() && UTH_SARA_A == u16word.at (p.pos))
                {
                    // ยัวะ, จั๊วะ
                    ++p.pos; // skip SARA A
                    p.vowel = EVowel::UA;
                } else {
                    // วัว, รั้ว
                    p.vowel = EVowel::UAA;
                }
                p.eConsClass = EEndConsClass::NONE;
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
            } else {
                // วัน, จักรี
                p.vowel = EVowel::A;
                // check mandatory end cons
                if (ETone::SAMAN == p.tone) {
                    EatEndConsComplex (u16word, state, p, pool);
                } else {
                    EatEndConsSimple (u16word, state, p, pool);
                }
            }
        } else if (th_wcisupvowel (c) || th_wcisblvowel (c)) {
            // มิ, ซิ่, มิด, ซิ่น, มี, ชี้, มีด, ซี้ด, อึ, อึ๊, อึด, ปึ๊ด, มือ, รื้อ, มืด, ปื๊ด,
            // อุ, อุ๊, อุด, กุ๊น, รู, ปู่, รูด, ปู๊น
            p.vowel = ThCharToAboveBelowVowel (c);
            ++p.pos; // skip the vowel
            if (p.pos < u16word.size()) {
                // check tone mark
                c = u16word.at (p.pos);
                if (th_wcisthtone (c)) {
                    // read tone
                    p.tone = ThCharToTone (c);
                    ++p.pos; // skip the tone
                }
            }
            if (p.pos >= u16word.size() ||
                th_wcisldvowel (u16word.at (p.pos)) ||
                EVowel::UEE != p.vowel)
            {
                // มิ, ซิ่, มี, ชี้, อึ, อึ๊, อุ, อุ๊, รู, ปู่
                // note: คื, มื, and alike is allowed here at word end
                p.eConsClass = EEndConsClass::NONE;
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
            }
            if (p.pos < u16word.size() && !th_wcisldvowel (u16word.at (p.pos)))
            {
                // check end cons
                if (EVowel::UEE == p.vowel) {
                    if (UTH_O_ANG == u16word.at (p.pos)) {
                        // มือ, รื้อ
                        p.eConsClass = EEndConsClass::NONE;
                        ++p.pos; // skip O ANG
                        pool.add (ParseState (p.pos,
                                              AddSyl (state.sylString, p)));
                    } else {
                        // มืด, ปื๊ด
                        EatEndConsSimple (u16word, state, p, pool);
                    }
                } else if (EVowel::UE == p.vowel || ETone::SAMAN != p.tone) {
                    // ซิ่น, ซี้ด, ปึ๊ด, กุ๊น, ปู๊น
                    EatEndConsSimple (u16word, state, p, pool);
                } else {
                    // มิด, จิตรา, มีด, อุด, อุตรา, รูด, คูตร
                    EatEndConsComplex (u16word, state, p, pool);
                }
            }
        } else {
            if (th_wcisthtone (c)) {
                // read tone
                p.tone = ThCharToTone (c);
                ++p.pos; // skip tone mark
            }
            if (p.pos >= u16word.size()) {
                // บ่, also allowing ก่, ก้, etc., at word end
                p.vowel = EVowel::AUU;
                p.eConsClass = EEndConsClass::NONE;
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
                continue;
            }
            switch (u16word.at (p.pos)) {
            case UTH_SARA_A: // กะ, ค่ะ
                ++p.pos; // skip SARA A
                p.vowel = EVowel::A;
                p.eConsClass = EEndConsClass::NONE;
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
                break;

            case UTH_SARA_AA: // กา, ค่า, กาง, ค่าง
                ++p.pos; // skip SARA AA
                p.vowel = EVowel::AA;
                p.eConsClass = EEndConsClass::NONE;
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));

                // check optional end cons
                if (p.pos < u16word.size()) {
                    // ค่าง, มาตรา
                    EatEndConsComplex (u16word, state, p, pool);
                }
                break;

            case UTH_SARA_AM: // คำ, ค่ำ
                ++p.pos; // skip SARA AM
                p.vowel = EVowel::A;
                p.eConsClass = EEndConsClass::KOM;
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
                break;

            case UTH_WO_WAEN:
                // ด้วย
                ++p.pos; // skip WO WAEN
                p.vowel = EVowel::UAA;

                // check mandatory end cons
                if (p.pos < u16word.size()) {
                    EatEndConsSimple (u16word, state, p, pool);
                }
                break;

            case UTH_O_ANG:
                // ข้อ, ร้อน
                ++p.pos; // skip O ANG
                p.vowel = EVowel::AUU;
                p.eConsClass = EEndConsClass::NONE;
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));

                // check optional end cons
                if (p.pos < u16word.size()) {
                    EatEndConsSimple (u16word, state, p, pool);
                }
                break;

            case UTH_RO_RUA:
                // พร, นคร
                if (p.pos + 1 == u16word.size() ||
                    IsSylStart (u16word.at (p.pos + 1)))
                {
                    ++p.pos; // skip RO RUA
                    p.vowel = EVowel::AUU;
                    p.eConsClass = EEndConsClass::KON;
                    pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
                }
                // No else here. The cases like ฟรี, (นา)ครี, etc. should be
                // parsed by other means
                break;

            default:
                if (th_wcisthcons (c) &&
                    EEndConsClass::NONE != EndConsClass (c) &&
                    ESecInitCons::WA != p.iCons2) // prevent e.g. กฺวง
                {
                    // ข้น
                    p.vowel = EVowel::O;

                    // read final consonant
                    EatEndConsSimple (u16word, state, p, pool);
                }
            }
        }
    }
}

// Progress the parsing from given state, where Sara E was found.
static void
ParseSaraE (const u16string& u16word, ParseState& state, StatePool& pool)
{
    if (th_wcisthcons (u16word.at (state.pos + 1))) {
        // check อักษรควบแท้/ควบไม่แท้
        // check อักษรนำเสียงสนิท/อักษรนำอะกึ่งเสียง
    }
    if (UTH_SARA_I == u16word.at (state.pos + 1)) {
        // เดิน, เปิ่น
    } else if (UTH_SARA_II == u16word.at (state.pos + 1)) {
        // เสีย, เสี่ย, เสียม, เยี่ยง
    } else if (UTH_SARA_UEE == u16word.at (state.pos + 1)) {
        // เสือ, เสื่อ, เคือง, เชื่อม
    } else if (UTH_MAITAIKHU == u16word.at (state.pos + 1)) {
        // เป็น
    } else {
        if (th_wcisthtone (u16word.at (state.pos + 1))) {
            // read tone
            ++state.pos;
        }
        if (UTH_O_ANG == u16word.at (state.pos + 1)) {
            // เธอ, เพ้อ
            ++state.pos;
            if (UTH_SARA_A == u16word.at (state.pos + 1)) {
                // เลอะ
                ++state.pos;
            }
        } else if (UTH_SARA_AA == u16word.at (state.pos + 1)) {
            // เบา, เก่า
            ++state.pos;
            if (UTH_SARA_A == u16word.at (state.pos + 1)) {
                // เกาะ
            }
        }
    }
    // match karan
}

// Progress the parsing from given state, where a Thai leading vowel
// other than Sara E was found.
static void
ParseOtherLV (const u16string& u16word, ParseState& state, StatePool& pool)
{
    switch (u16word.at (state.pos)) {
    case UTH_SARA_AE:
    case UTH_SARA_O:
    case UTH_SARA_AI_MAIMALAI:
    case UTH_SARA_AI_MAIMUAN:
        break;
    }
}

static list<SylString>
ParseU16 (const u16string& u16word, StatePool& pool)
{
    list<SylString> sylStrings;
    ParseState s;
    while (pool.pop (s)) {
        if (s.pos >= u16word.size()) {
            sylStrings.push_back (s.sylString);
        } else {
            if (th_wcisthcons (u16word.at (s.pos))) {
                ParseThCons (u16word, s, pool);
            } else if (UTH_SARA_E == u16word.at (s.pos)) {
                ParseSaraE (u16word, s, pool);
            } else if (th_wcisldvowel (u16word.at (s.pos))) {
                ParseOtherLV (u16word, s, pool);
            }
        }
    }
    return sylStrings;
}

list<SylString>
ParseWord (string word)
{
    // convert UTF-8 word string to UTF-16
    wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> u16conv;
    u16string u16word = u16conv.from_bytes (word);

    // parse the UTF-16 word
    StatePool pool;
    pool.add (ParseState());
    return ParseU16 (u16word, pool);
}

/*
vi:ts=4:ai:expandtab
*/
