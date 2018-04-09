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

    if (state.pos + 1 < u16word.size()) {
        auto secChar = u16word.at (state.pos + 1);

        if (th_wcisthcons (secChar)) {
            auto secConsSound = InitConsSound (secChar);
            auto secConsClass = InitConsClass (secChar);

            // check อักษรควบแท้
            // (อักษรควบไม่แท้ "ทร" are supposed to be in exception dict)
            switch (secChar) {
            case UTH_RO_RUA:
                switch (firstCons) {
                case UTH_CHO_CHAN:
                case UTH_SO_SO:
                case UTH_SO_SALA:
                case UTH_SO_SUA:
                    if (state.isLinked)
                        break;
                    // add อักษรควบไม่แท้, but not for cรร, which is ร หัน
                    if (state.pos + 2 >= u16word.size() ||
                        UTH_RO_RUA != u16word.at (state.pos + 2))
                    {
                        partialSyls.push_back (
                            PartialSyl (state.pos + 2, firstConsSound,
                                        firstConsClass)
                        );
                    }
                    break;

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
                    // add อักษรควบแท้, but not for cรร, which is ร หัน
                    if (state.pos + 2 >= u16word.size() ||
                        UTH_RO_RUA != u16word.at (state.pos + 2))
                    {
                        partialSyls.push_back (
                            PartialSyl (state.pos + 2,
                                        firstConsSound,
                                        firstConsClass,
                                        ESecInitCons::RA)
                        );
                    }
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
                EInitConsClass::LOWS == secConsClass)
            {
                // add อักษรนำเสียงสนิท, but not for หรร, which is ร หัน
                if (state.pos + 2 >= u16word.size() ||
                    UTH_RO_RUA != secChar ||
                    UTH_RO_RUA != u16word.at (state.pos + 2))
                {
                    partialSyls.push_back (
                        PartialSyl (state.pos + 2,
                                    secConsSound,
                                    EInitConsClass::HIGH)
                    );
                }
            }

            // always add อักษรนำอะกึ่งเสียง
            // - with second consonant's own class,
            //   e.g. กมุท, ขมา, สมา, สรีระ, สราญ, หริภุญชัย, อรุโณทัย
            // - but not for cรร, which is ร หัน
            if (state.pos + 2 >= u16word.size() ||
                UTH_RO_RUA != secChar ||
                UTH_RO_RUA != u16word.at (state.pos + 2))
            {
                partialSyls.push_back (
                    PartialSyl (state.pos + 2,
                                Syl (firstConsSound, ESecInitCons::NONE,
                                     EVowel::A, EEndConsClass::NONE,
                                     ToneFromWritten (firstConsClass,
                                                      ETone::SAMAN,
                                                      true, true)),
                                secConsSound,
                                secConsClass)
                );
            }
            // - using first consonant's class,
            //   e.g. ขนม, ขมิบ, จรวด, จมูก, เฉลิม, โตนด, ตลาด, ผลิต, สนิม, สยบ,
            //   สรุป, สลาย, สวรรค์, สวัสดี, อร่อย, อร่าม
            // - but not for cรร, which is ร หัน
            if (EInitConsClass::LOWS == secConsClass &&
                (EInitConsClass::HIGH == firstConsClass ||
                 EInitConsClass::MID == firstConsClass))
            {
                if (state.pos + 2 >= u16word.size() ||
                    UTH_RO_RUA != secChar ||
                    UTH_RO_RUA != u16word.at (state.pos + 2))
                {
                    partialSyls.push_back (
                        PartialSyl (state.pos + 2,
                                    Syl (firstConsSound, ESecInitCons::NONE,
                                         EVowel::A, EEndConsClass::NONE,
                                         ToneFromWritten (firstConsClass,
                                                          ETone::SAMAN,
                                                          true, true)),
                                    secConsSound,
                                    firstConsClass)
                    );
                }
            }
        } else if (UTH_RU == secChar) {
            // make sure it's not ฤๅ
            // note: "ตฤๅ" is supposed to be in exception dict here
            if (state.pos + 2 >= u16word.size() || (
                    UTH_LAKKHANGYAO != u16word.at (state.pos + 2) &&
                    UTH_SARA_AA != u16word.at (state.pos + 2)
                ))
            {
                // RU after these cons are always pronounced "RI" clustered
                static const unordered_set<char16_t> riClusterCons = {
                    UTH_KO_KAI,
                    UTH_TO_TAO,
                    UTH_THO_THAHAN,
                    UTH_PO_PLA,
                };
                // RU after these cons are always pronounced "RI",
                // either clustered or as separate syllable
                static const unordered_set<char16_t> riCons = {
                    UTH_SO_SUA,
                    UTH_SO_SALA,
                };
                // RU after these cons are always pronounced short "RUE",
                // clustered
                static const unordered_set<char16_t> ruClusterCons = {
                    UTH_WO_WAEN,
                };
                // RU after these cons are always pronounced short "RUE"
                // as separate syllable
                static const unordered_set<char16_t> ruSepCons = {
                    UTH_NO_NU,
                };
                // RU after these cons are always pronounced short "RUE",
                // either clustered or as separate syllable
                static const unordered_set<char16_t> ruCons = {
                    UTH_KHO_KHWAI,
                    UTH_PHO_PHAN,
                };

                if (riClusterCons.find (firstCons) != riClusterCons.end()) {
                    // อังกฤษ, ตฤณ, ปฤจฉา
                    partialSyls.push_back (
                        PartialSyl (
                            state.pos + 2,
                            firstConsSound,
                            firstConsClass,
                            ESecInitCons::RA,
                            EVowel::I
                        )
                    );
                } else if (riCons.find (firstCons) != riCons.end()) {
                    // ศฤงคาร
                    partialSyls.push_back (
                        PartialSyl (
                            state.pos + 2,
                            firstConsSound,
                            firstConsClass,
                            ESecInitCons::NONE,
                            EVowel::I
                        )
                    );
                    // สฤษฎ์
                    partialSyls.push_back (
                        PartialSyl (
                            state.pos + 2,
                            Syl (
                                firstConsSound, ESecInitCons::NONE,
                                EVowel::A, EEndConsClass::NONE,
                                ToneFromWritten (firstConsClass,
                                                 ETone::SAMAN, true, true)
                            ),
                            EInitConsSound::RA,
                            firstConsClass,
                            ESecInitCons::NONE,
                            EVowel::I
                        )
                    );
                } else if (ruClusterCons.find (firstCons)
                               != ruClusterCons.end())
                {
                    // วฤก, วฤษภ, วฤษละ
                    partialSyls.push_back (
                        PartialSyl (
                            state.pos + 2,
                            firstConsSound,
                            firstConsClass,
                            ESecInitCons::RA,
                            EVowel::UE
                        )
                    );
                } else if (ruSepCons.find (firstCons) != ruSepCons.end()) {
                    // นฤบาล
                    partialSyls.push_back (
                        PartialSyl (
                            state.pos + 2,
                            Syl (
                                firstConsSound, ESecInitCons::NONE,
                                EVowel::A, EEndConsClass::NONE,
                                ToneFromWritten (firstConsClass,
                                                 ETone::SAMAN, true, true)
                            ),
                            EInitConsSound::RA,
                            EInitConsClass::LOWS,
                            ESecInitCons::NONE,
                            EVowel::UE
                        )
                    );
                } else if (ruCons.find (firstCons) != ruCons.end()) {
                    // peek next possible end cons
                    if (state.pos + 2 < u16word.size() &&
                        EEndConsClass::NONE != EndConsClass (u16word.at (state.pos + 2)))
                    {
                        // คฤนถ์, คฤธระ, พฤกษ์, พฤศจิก
                        partialSyls.push_back (
                            PartialSyl (
                                state.pos + 2,
                                firstConsSound,
                                firstConsClass,
                                ESecInitCons::RA,
                                EVowel::UE
                            )
                        );
                    } else {
                        // คฤหัสถ์, คฤโฆษ, พฤหัส
                        partialSyls.push_back (
                            PartialSyl (
                                state.pos + 2,
                                Syl (
                                    firstConsSound, ESecInitCons::NONE,
                                    EVowel::A, EEndConsClass::NONE,
                                    ToneFromWritten (firstConsClass,
                                                     ETone::SAMAN, true, true)
                                ),
                                EInitConsSound::RA,
                                EInitConsClass::LOWS,
                                ESecInitCons::NONE,
                                EVowel::UE
                            )
                        );
                    }
                } else {
                    // ภฤงคาร
                    if (UTH_HO_HIP != firstCons) {
                        partialSyls.push_back (
                            PartialSyl (
                                state.pos + 2,
                                firstConsSound,
                                firstConsClass,
                                ESecInitCons::RA,
                                EVowel::I
                            )
                        );
                    }
                    // หฤษฎ์
                    partialSyls.push_back (
                        PartialSyl (
                            state.pos + 2,
                            Syl (
                                firstConsSound, ESecInitCons::NONE,
                                EVowel::A, EEndConsClass::NONE,
                                ToneFromWritten (firstConsClass,
                                                 ETone::SAMAN, true, true)
                            ),
                            EInitConsSound::RA,
                            EInitConsClass::LOWS,
                            ESecInitCons::NONE,
                            EVowel::I
                        )
                    );
                    // ภฤดก, ภฤตย์
                    if (UTH_HO_HIP != firstCons) {
                        partialSyls.push_back (
                            PartialSyl (
                                state.pos + 2,
                                firstConsSound,
                                firstConsClass,
                                ESecInitCons::RA,
                                EVowel::UE
                            )
                        );
                    }
                    // หฤทัย
                    partialSyls.push_back (
                        PartialSyl (
                            state.pos + 2,
                            Syl (
                                firstConsSound, ESecInitCons::NONE,
                                EVowel::A, EEndConsClass::NONE,
                                ToneFromWritten (firstConsClass,
                                                 ETone::SAMAN, true, true)
                            ),
                            EInitConsSound::RA,
                            EInitConsClass::LOWS,
                            ESecInitCons::NONE,
                            EVowel::UE
                        )
                    );
                }
            }
        }
    }

    // add single initial consonant sound
    partialSyls.push_back (
        PartialSyl (state.pos + 1, firstConsSound, firstConsClass)
    );

    return partialSyls;
}

// Simple Karan: single consonant + THANTHAKHAT
// return end position of the matched string
static int
MatchKaranSimple (const u16string& u16word, int pos)
{
    if (pos + 1 < u16word.size() &&
        UTH_THANTHAKHAT == u16word.at (pos + 1) &&
        th_wcisthcons (u16word.at (pos)))
    {
        return pos + 2; // skip cons + THANTHAKHAT
    }

    return pos;
}

// Complex Karan:
//   - single consonant + THANTHAKHAT
//   - consonant + consonant + THANTHAKHAT
//   - consonant + { SARA I, SARA U } + THANTHAKHAT
// return end position of the matched string
static int
MatchKaranComplex (const u16string& u16word, int pos)
{
    auto p = MatchKaranSimple (u16word, pos);
    if (p != pos)
        return p;

    if (pos + 2 < u16word.size() &&
        UTH_THANTHAKHAT == u16word.at (pos + 2) &&
        th_wcisthcons (u16word.at (pos)) && (
            th_wcisthcons (u16word.at (pos + 1)) ||
            UTH_SARA_I == u16word.at (pos + 1) ||
            UTH_SARA_U == u16word.at (pos + 1)
        ))
    {
        return pos + 3; // skip cons + {cons, SARA I, SARA U } + THANTHAKHAT
    }

    return pos;
}

static bool
EatEndConsSimple (const u16string& u16word, const ParseState& state,
                  PartialSyl& p, StatePool& pool,
                  const unordered_set<char16_t>& excludedECons = {});
static bool
EatEndConsComplex (const u16string& u16word, const ParseState& state,
                   PartialSyl& p, StatePool& pool,
                   const unordered_set<char16_t>& excludedECons = {});

// Match ending consonant part of the syllable form, simple version
// Returns whether the match is successful
static bool
EatEndConsSimple (const u16string& u16word, const ParseState& state,
                  PartialSyl& p, StatePool& pool,
                  const unordered_set<char16_t>& excludedECons)
{
    auto c = u16word.at (p.pos);
    if (th_wcisthcons (c) && EEndConsClass::NONE != EndConsClass (c)
        && excludedECons.find (c) == excludedECons.end())
    {
        p.eConsClass = EndConsClass (c);
        ++p.pos; // skip the end cons

        p.pos = MatchKaranComplex (u16word, p.pos);
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
                   PartialSyl& p, StatePool& pool,
                   const unordered_set<char16_t>& excludedECons)
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
    if (th_wcisthcons (c) && EEndConsClass::NONE != EndConsClass (c)
        && excludedECons.find (c) == excludedECons.end())
    {
        p.eConsClass = EndConsClass (c);

        auto karanEnd = MatchKaranComplex (u16word, p.pos + 1);
        // add single non-linking ending consonant
        pool.add (ParseState (karanEnd, AddSyl (state.sylString, p)));
        if (karanEnd > p.pos + 1)
            goto word_done;

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
                p.pos = MatchKaranSimple (u16word, p.pos);
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
                p.pos = MatchKaranSimple (u16word, p.pos);
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
                        p.pos = MatchKaranSimple (u16word, p.pos);
                        pool.add (ParseState (p.pos,
                                              AddSyl (state.sylString, p)));
                    } else {
                        // มืด, ปื๊ด
                        EatEndConsSimple (u16word, state, p, pool);
                    }
                } else {
                    unordered_set<char16_t> excludedECons;
                    if (EVowel::I == p.vowel || EVowel::II == p.vowel) {
                          excludedECons.emplace (UTH_YO_YAK);
                    }
                    if (EVowel::UE == p.vowel || ETone::SAMAN != p.tone) {
                        // ซิ่น, ซี้ด, ปึ๊ด, กุ๊น, ปู๊น
                        EatEndConsSimple (u16word, state, p, pool,
                                          excludedECons);
                    } else {
                        // มิด, จิตรา, มีด, อุด, อุตรา, รูด, คูตร
                        EatEndConsComplex (u16word, state, p, pool,
                                           excludedECons);
                    }
                }
            }
        } else {
            if (th_wcisthtone (c)) {
                // read tone
                p.tone = ThCharToTone (c);
                ++p.pos; // skip tone mark
            }
            if (p.pos >= u16word.size()) {
                continue;
            }
            switch (u16word.at (p.pos)) {
            case UTH_SARA_A: // กะ, ค่ะ
                ++p.pos; // skip SARA A
                p.vowel = EVowel::A;
                p.eConsClass = EEndConsClass::NONE;
                p.pos = MatchKaranSimple (u16word, p.pos);
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
                break;

            case UTH_SARA_AA: // กา, ค่า, กาง, ค่าง
                ++p.pos; // skip SARA AA
                p.vowel = EVowel::AA;
                p.eConsClass = EEndConsClass::NONE;
                p.pos = MatchKaranSimple (u16word, p.pos);
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
                p.pos = MatchKaranSimple (u16word, p.pos);
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
                p.pos = MatchKaranSimple (u16word, p.pos);
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));

                // check optional end cons
                if (p.pos < u16word.size()) {
                    EatEndConsSimple (u16word, state, p, pool);
                }
                break;

            case UTH_RO_RUA:
                // พร, นคร
                if (p.pos + 1 == u16word.size() || (
                        UTH_RO_RUA != u16word.at (p.pos + 1) &&
                        IsSylStart (u16word.at (p.pos + 1))
                    ))
                {
                    ++p.pos; // skip RO RUA
                    p.vowel = EVowel::AUU;
                    p.eConsClass = EEndConsClass::KON;
                    p.pos = MatchKaranSimple (u16word, p.pos);
                    pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
                } else if (UTH_RO_RUA == u16word.at (p.pos + 1)) {
                    // สรร, ธรรม
                    p.pos += 2; // skip two RO RUA's
                    p.vowel = EVowel::A;
                    p.eConsClass = EEndConsClass::KON;
                    auto karanEnd = MatchKaranSimple (u16word, p.pos);
                    pool.add (ParseState (karanEnd,
                                          AddSyl (state.sylString, p)));

                    // check optional end cons
                    if (karanEnd == p.pos && p.pos < u16word.size()) {
                        EatEndConsSimple (u16word, state, p, pool);
                    }
                }
                // No else here. The cases like ฟรี, (นา)ครี, etc. should be
                // parsed by other means
                break;

            default:
                if (th_wcisthcons (c)) {
                    if (EVowel::INVALID == p.vowel) {
                        if (EEndConsClass::NONE != EndConsClass (c) &&
                            ESecInitCons::WA != p.iCons2) // prevent e.g. กฺวง
                        {
                            // ข้น
                            p.vowel = EVowel::O;

                            // check mandatory end cons
                            EatEndConsSimple (u16word, state, p, pool,
                                              { UTH_YO_YAK, UTH_WO_WAEN });
                        }
                    } else {
                        // cons + RU
                        p.eConsClass = EEndConsClass::NONE;
                        pool.add (ParseState (p.pos,
                                              AddSyl (state.sylString, p)));

                        // check optional end cons
                        EatEndConsComplex (u16word, state, p, pool,
                                           { UTH_WO_WAEN });
                    }
                }
            }
        }
    }
}

// Progress the parsing from given state, where Sara E was found.
static void
ParseSaraE (const u16string& u16word, ParseState& state, StatePool& pool)
{
    assert (UTH_SARA_E == u16word.at (state.pos));

    ++state.pos; // skip SARA E
    if (state.pos >= u16word.size()) {
        return;
    }

    list<PartialSyl> partialSyls = MatchInitCons (u16word, state);

    for (auto& p : partialSyls) {
        p.tone = ETone::SAMAN;
        if (p.pos >= u16word.size()) {
            p.vowel = EVowel::EE;
            p.eConsClass = EEndConsClass::NONE;
            pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
            continue;
        }
        auto c = u16word.at (p.pos);
        switch (c) {
        case UTH_SARA_I:
            // เดิน, เปิ่น
            ++p.pos; // skip SARA I
            p.vowel = EVowel::OEE;
            if (p.pos >= u16word.size()) {
                continue;
            }
            c = u16word.at (p.pos);
            if (th_wcisthtone (c)) {
                // read tone
                p.tone = ThCharToTone (c);
                ++p.pos; // skip tone mark
            }
            p.pos = MatchKaranSimple (u16word, p.pos);
            // check mandatory end cons
            if (p.pos < u16word.size()) {
                EatEndConsSimple (u16word, state, p, pool);
            }
            break;
        case UTH_SARA_II:
            // เลียะ, เปี๊ยะ, เสีย, เสี่ย, เสียม, เยี่ยง
            ++p.pos; // skip SARA II
            if (p.pos >= u16word.size()) {
                continue;
            }
            c = u16word.at (p.pos);
            if (th_wcisthtone (c)) {
                // read tone
                p.tone = ThCharToTone (c);
                ++p.pos; // skip tone mark
            }
            if (p.pos >= u16word.size() || UTH_YO_YAK != u16word.at (p.pos)) {
                continue;
            }
            ++p.pos; // skip YO YAK
            if (p.pos < u16word.size() && UTH_SARA_A == u16word.at (p.pos)) {
                ++p.pos; // skip SARA A
                p.vowel = EVowel::IA;
            } else {
                p.vowel = EVowel::IAA;
            }
            p.eConsClass = EEndConsClass::NONE;
            p.pos = MatchKaranSimple (u16word, p.pos);
            pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
            // check optional end cons
            if (EVowel::IAA == p.vowel && p.pos < u16word.size()) {
                EatEndConsComplex (u16word, state, p, pool);
            }
            break;
        case UTH_SARA_UEE:
            // เสือ, เสื่อ, เกือะ, เกื๊อะ, เคือง, เชื่อม
            ++p.pos; // skip SARA UEE
            if (p.pos >= u16word.size()) {
                continue;
            }
            c = u16word.at (p.pos);
            if (th_wcisthtone (c)) {
                // read tone
                p.tone = ThCharToTone (c);
                ++p.pos; // skip tone mark
            }
            if (p.pos >= u16word.size() || UTH_O_ANG != u16word.at (p.pos)) {
                continue;
            }
            ++p.pos; // skip O ANG
            if (p.pos < u16word.size() && UTH_SARA_A == u16word.at (p.pos)) {
                ++p.pos; // skip SARA A
                p.vowel = EVowel::UEA;
            } else {
                p.vowel = EVowel::UEAA;
            }
            p.eConsClass = EEndConsClass::NONE;
            p.pos = MatchKaranSimple (u16word, p.pos);
            pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
            // check optional end cons
            if (EVowel::UEAA == p.vowel && p.pos < u16word.size()) {
                EatEndConsSimple (u16word, state, p, pool);
            }
            break;
        case UTH_MAITAIKHU:
            // เป็น
            ++p.pos; // skip MAITAIKHU
            // check mandatory end cons
            if (p.pos < u16word.size()) {
                p.vowel = EVowel::E;
                EatEndConsSimple (u16word, state, p, pool);
            }
            break;
        default:
            if (th_wcisthtone (c)) {
                // read tone
                p.tone = ThCharToTone (c);
                ++p.pos; // skip tone mark
            }
            if (p.pos >= u16word.size()) {
                // เก๋, เท่, เบ้
                p.vowel = EVowel::EE;
                p.eConsClass = EEndConsClass::NONE;
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
                continue;
            }
            switch (u16word.at (p.pos)) {
            case UTH_O_ANG:
                // เธอ, เพ้อ, เลอะ, เบ๊อะ
                ++p.pos; // skip O ANG
                if (p.pos < u16word.size() && UTH_SARA_A == u16word.at (p.pos))
                {
                    // เลอะ
                    ++p.pos; // skip SARA A
                    p.vowel = EVowel::OE;
                } else {
                    // SARA OEE with end cons, like เทอม, เทอญ, are exceptions
                    p.vowel = EVowel::OEE;
                }
                p.eConsClass = EEndConsClass::NONE;
                p.pos = MatchKaranSimple (u16word, p.pos);
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
                break;
            case UTH_SARA_A:
                // เตะ, เป๊ะ
                ++p.pos; // skip SARA A
                p.vowel = EVowel::E;
                p.eConsClass = EEndConsClass::NONE;
                p.pos = MatchKaranSimple (u16word, p.pos);
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
                break;
            case UTH_SARA_AA:
                // เบา, เก่า, เกาะ, เอ๊าะ
                ++p.pos; // skip SARA AA
                if (p.pos < u16word.size() && UTH_SARA_A == u16word.at (p.pos))
                {
                    // เกาะ
                    ++p.pos; // skip SARA A
                    p.vowel = EVowel::AU;
                    p.eConsClass = EEndConsClass::NONE;
                } else {
                    p.vowel = EVowel::A;
                    p.eConsClass = EEndConsClass::KOEW;
                }
                p.pos = MatchKaranSimple (u16word, p.pos);
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
                break;
            case UTH_YO_YAK:
                // เลย, เม้ย
                ++p.pos; // skip YO YAK
                p.vowel = EVowel::OEE;
                p.eConsClass = EEndConsClass::KOEY;
                p.pos = MatchKaranSimple (u16word, p.pos);
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
                break;
            default:
                // เก, เก๋, เบน, เก่ง
                p.vowel = EVowel::EE;
                p.eConsClass = EEndConsClass::NONE;
                p.pos = MatchKaranSimple (u16word, p.pos);
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
                // check optional end cons
                if (p.pos < u16word.size()) {
                    EatEndConsComplex (u16word, state, p, pool);
                }
                break;
            }
        }
    }
}

// Progress the parsing from given state, where a Thai leading vowel
// other than Sara E was found.
static void
ParseOtherLV (const u16string& u16word, ParseState& state, StatePool& pool)
{
    assert (state.pos < u16word.size());
    assert (th_wcisldvowel (u16word.at (state.pos)));
    assert (UTH_SARA_E != u16word.at (state.pos));

    auto ldv = u16word.at (state.pos);
    ++state.pos; // skip the leading vowel kept in ldv

    list<PartialSyl> partialSyls = MatchInitCons (u16word, state);

    for (auto& p : partialSyls) {
        p.tone = ETone::SAMAN;
        if (p.pos < u16word.size()) {
            auto c = u16word.at (p.pos);
            if (th_wcisthtone (c)) {
                // read tone
                p.tone = ThCharToTone (c);
                ++p.pos; // skip tone mark
            }
        }

        bool needsEndCons = false;

        switch (ldv) {
        case UTH_SARA_AE:
            // แกะ, แป๊ะ, แก, แก่, แกน, แก่น, แข็ง
            if (p.pos < u16word.size()) {
                auto c = u16word.at (p.pos);
                switch (c) {
                case UTH_SARA_A:
                    // แกะ, แป๊ะ
                    ++p.pos;  // skip SARA A
                    p.vowel = EVowel::AE;
                    break;
                case UTH_MAITAIKHU:
                    // แข็ง
                    ++p.pos;  // skip MAITAIKHU
                    p.vowel = EVowel::AE;
                    needsEndCons = true;
                    break;
                default:
                    // แก, แก่, แกน, แก่น
                    p.vowel = EVowel::AEE;
                }
            } else {
                // แก, แก่
                p.vowel = EVowel::AEE;
            }
            if (!needsEndCons) {
                p.eConsClass = EEndConsClass::NONE;
                p.pos = MatchKaranSimple (u16word, p.pos);
                pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
            }
            // check optional end cons for SARA AEE,
            // mandatory end cons for SARA AE with MAITAIKHU
            if (p.pos < u16word.size() && (
                    EVowel::AEE == p.vowel || needsEndCons
                ))
            {
                EatEndConsSimple (u16word, state, p, pool);
            }
            break;
        case UTH_SARA_O:
            // โละ, โป๊ะ, โต, โอ่, โกน, โล้น
            if (p.pos < u16word.size() && UTH_SARA_A == u16word.at (p.pos)) {
                ++p.pos;  // skip SARA A
                p.vowel = EVowel::O;
            } else {
                p.vowel = EVowel::OO;
            }
            p.eConsClass = EEndConsClass::NONE;
            p.pos = MatchKaranSimple (u16word, p.pos);
            pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
            // check optional end cons for SARA OO
            if (EVowel::OO == p.vowel && p.pos < u16word.size()) {
                EatEndConsSimple (u16word, state, p, pool);
            }
            break;
        case UTH_SARA_AI_MAIMALAI:
        case UTH_SARA_AI_MAIMUAN:
            p.vowel = EVowel::A;
            p.eConsClass = EEndConsClass::KOEY;
            p.pos = MatchKaranSimple (u16word, p.pos);
            pool.add (ParseState (p.pos, AddSyl (state.sylString, p)));
            break;
        }
    }
}

// Progress the parsing from given state, where RU or LU was found.
static void
ParseRuLu (const u16string& u16word, ParseState& state, StatePool& pool)
{
    assert (state.pos < u16word.size());
    assert (UTH_RU == u16word.at (state.pos) ||
            UTH_LU == u16word.at (state.pos));

    auto firstChar = u16word.at (state.pos);
    ++state.pos; // skip RU/LU

    PartialSyl p (
        state.pos,
        ((UTH_LU == firstChar) ? EInitConsSound::LA : EInitConsSound::RA),
        EInitConsClass::LOWS,
        ESecInitCons::NONE
    );
    p.tone = ETone::SAMAN;

    // end cons that cause "RI" sound when following RU
    static const unordered_set<char16_t> riECons = {
        UTH_NO_NEN,
        UTH_THO_THAHAN,
        UTH_SO_RUSI,
    };

    if (state.pos >= u16word.size()) {
        // ฤ/ฦ at string end
        p.vowel = EVowel::UE;
        p.eConsClass = EEndConsClass::NONE;
        pool.add (ParseState (state.pos, AddSyl (state.sylString, p)));
    } else {
        auto secChar = u16word.at (state.pos);
        if (UTH_LAKKHANGYAO == secChar || UTH_SARA_AA == secChar) {
            // ฤๅ, ฦๅ, also allowing ฤา ฦา
            p.vowel = EVowel::UEE;
            p.eConsClass = EEndConsClass::NONE;
            pool.add (ParseState (state.pos + 1, AddSyl (state.sylString, p)));
        } else if (th_wcisthcons (secChar)) {
            auto secConsClass = EndConsClass (secChar);
            if (EEndConsClass::NONE == secConsClass || (
                    state.pos + 1 < u16word.size() &&
                    !IsSylStart (u16word.at (state.pos + 1))
                ))
            {
                // ฤ/ฦ + { ห, อ, ฮ }
                // ฤทัย, ฤดู, ฤษี, ฤชา
                p.vowel = EVowel::UE;
                p.eConsClass = EEndConsClass::NONE;
                pool.add (ParseState (state.pos, AddSyl (state.sylString, p)));
            } else if (riECons.find (secChar) != riECons.end()) {
                // ฤทธิ์, ฤณ, ฤษยา
                p.vowel = EVowel::I;
                EatEndConsComplex (u16word, state, p, pool);
            } else {
                // ฤกษณะ, ฤคเวท, ฤต
                p.vowel = EVowel::UE;
                EatEndConsComplex (u16word, state, p, pool);
            }
            // Note: ฤกษ์ is supposed to be in exception dict
        }
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
            auto c = u16word.at (s.pos);
            if (th_wcisthcons (c)) {
                ParseThCons (u16word, s, pool);
            } else if (UTH_SARA_E == c) {
                ParseSaraE (u16word, s, pool);
            } else if (th_wcisldvowel (c)) {
                ParseOtherLV (u16word, s, pool);
            } else if (UTH_RU == c || UTH_LU == c) {
                ParseRuLu (u16word, s, pool);
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
