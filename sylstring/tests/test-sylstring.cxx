#include "sylstring/sylstring.h"

#include <iostream>

using namespace std;

bool
TestThaiPronun()
{
    bool isSuccess = true;
    SylString syls;

    // กกต้นหูกฺวางเหฺลียวเลาะร้องเป็นตาแซ่บ
    syls = Syl ("k_ok1");

    auto thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_on2");
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("h_U_4");
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("kwAg0");
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_Yw4");
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_c_3");
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("r_Cg3");
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ-ร้อง") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("p_en0");
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ-ร้อง-เป็น") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_A_0");
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ-ร้อง-เป็น-ตา") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("s_xp2");
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ-ร้อง-เป็น-ตา-แซ่บ") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // ละลันหลั่นล้า
    syls = Syl ("l_a_3");
    syls += Syl ("l_an0");
    syls += Syl ("l_an1");
    syls += Syl ("l_A_3");
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"ละ-ลัน-หฺลั่น-ล้า") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // ใครใคร่ขายไข่ไก่คราคร่ำไม้ไหมเล่า
    syls = Syl ("cray0");
    syls += Syl ("cray2");
    syls += Syl ("c_Ay4");
    syls += Syl ("c_ay1");
    syls += Syl ("k_ay1");
    syls += Syl ("crA_0");
    syls += Syl ("cram2");
    syls += Syl ("m_Ay3");
    syls += Syl ("m_ay4");
    syls += Syl ("l_aw2");
    thaiPronun = syls.toThai();
    if (thaiPronun != u8"คฺรัย-คฺรั่ย-ขาย-ขั่ย-กั่ย-คฺรา-คฺรั่ม-ม้าย-หฺมัย-เล่า") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // แมวและเด็กเหล่เล่นเจอะเจอเกลือเดินเกลือกคั่วกลิ้งร่วมโรงเรียน
    syls = Syl ("m_Xw0");
    syls += Syl ("l_x_3");
    syls += Syl ("d_ek1");
    syls += Syl ("l_E_1");
    syls += Syl ("l_en2");
    syls += Syl ("j_w_1");
    syls += Syl ("j_W_0");
    syls += Syl ("klZ_0");
    syls += Syl ("d_Wn0");
    syls += Syl ("klZk1");
    syls += Syl ("c_T_2");
    syls += Syl ("klig2");
    syls += Syl ("r_Tm2");
    syls += Syl ("r_Og0");
    syls += Syl ("r_Yn0");
    thaiPronun = syls.toThai();
    if (thaiPronun !=
        u8"แมว-และ-เด็ก-เหฺล่-เล่น-เจอะ-เจอ-เกฺลือ-เดิน-เกฺลือก-คั่ว-กฺลิ้ง-ร่วม-โรง-เรียน")
    {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // มือมืดกฺรีดกุ้งพู้นหฺนึ่งสิ่งมิมีงูลุรึ
    syls = Syl ("m_V_0");
    syls += Syl ("m_Vt2");
    syls += Syl ("krIt1");
    syls += Syl ("k_ug2");
    syls += Syl ("P_Un3");
    syls += Syl ("n_vg1");
    syls += Syl ("s_ig1");
    syls += Syl ("m_i_3");
    syls += Syl ("m_I_0");
    syls += Syl ("g_U_0");
    syls += Syl ("l_u_3");
    syls += Syl ("r_v_3");
    thaiPronun = syls.toThai();
    if (thaiPronun !=
        u8"มือ-มืด-กฺรีด-กุ้ง-พู้น-หฺนึ่ง-สิ่ง-มิ-มี-งู-ลุ-รึ")
    {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // เกินเลยเม้ย
    syls = Syl ("k_Wn0");
    syls += Syl ("l_Wy0");
    syls += Syl ("m_Wy3");
    thaiPronun = syls.toThai();
    if (thaiPronun !=
        u8"เกิน-เลย-เม้ย")
    {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

bool
TestRomanPronun()
{
    bool isSuccess = true;
    SylString syls;

    // กกต้นหูกฺวางเหฺลียวเลาะร้องเป็นตาแซ่บ
    syls = Syl ("k_ok1");

    auto romanized = syls.toRoman();
    if (romanized != "kok") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_on2");
    romanized = syls.toRoman();
    if (romanized != "kokton") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("h_U_4");
    romanized = syls.toRoman();
    if (romanized != "koktonhu") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("kwAg0");
    romanized = syls.toRoman();
    if (romanized != "koktonhukwang") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_Yw4");
    romanized = syls.toRoman();
    if (romanized != "koktonhukwangliao") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_c_3");
    romanized = syls.toRoman();
    if (romanized != "koktonhukwangliaolo") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("r_Cg3");
    romanized = syls.toRoman();
    if (romanized != "koktonhukwangliaolorong") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("p_en0");
    romanized = syls.toRoman();
    if (romanized != "koktonhukwangliaolorongpen") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_A_0");
    romanized = syls.toRoman();
    if (romanized != "koktonhukwangliaolorongpenta") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("s_xp2");
    romanized = syls.toRoman();
    if (romanized != "koktonhukwangliaolorongpentasaep") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // ละลันหลั่นล้า
    syls = Syl ("l_a_3");
    syls += Syl ("l_an0");
    syls += Syl ("l_an1");
    syls += Syl ("l_A_3");
    romanized = syls.toRoman();
    if (romanized != "lalanlanla") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // ใครใคร่ขายไข่ไก่คราคร่ำไม้ไหมเล่า
    syls = Syl ("cray0");
    syls += Syl ("cray2");
    syls += Syl ("c_Ay4");
    syls += Syl ("c_ay1");
    syls += Syl ("k_ay1");
    syls += Syl ("crA_0");
    syls += Syl ("cram2");
    syls += Syl ("m_Ay3");
    syls += Syl ("m_ay4");
    syls += Syl ("l_aw2");
    romanized = syls.toRoman();
    if (romanized != "khraikhraikhaikhaikaikhrakhrammaimailao") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // แมวและเด็กเหล่เล่นเจอะเจอเกลือเดินเกลือกคั่วกลิ้งร่วมโรงเรียน
    syls = Syl ("m_Xw0");
    syls += Syl ("l_x_3");
    syls += Syl ("d_ek1");
    syls += Syl ("l_E_1");
    syls += Syl ("l_en2");
    syls += Syl ("j_w_1");
    syls += Syl ("j_W_0");
    syls += Syl ("klZ_0");
    syls += Syl ("d_Wn0");
    syls += Syl ("klZk1");
    syls += Syl ("c_T_2");
    syls += Syl ("klig2");
    syls += Syl ("r_Tm2");
    syls += Syl ("r_Og0");
    syls += Syl ("r_Yn0");
    romanized = syls.toRoman (true);
    if (romanized !=
        "Maeolaedeklelenchoechoeklueadoenklueakkhuaklingruamrongrian")
    {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // มือมืดกฺรีดกุ้งพู้นหฺนึ่งสิ่งมิมีงูลุรึ
    syls = Syl ("m_V_0");
    syls += Syl ("m_Vt2");
    syls += Syl ("krIt1");
    syls += Syl ("k_ug2");
    syls += Syl ("P_Un3");
    syls += Syl ("n_vg1");
    syls += Syl ("s_ig1");
    syls += Syl ("m_i_3");
    syls += Syl ("m_I_0");
    syls += Syl ("g_U_0");
    syls += Syl ("l_u_3");
    syls += Syl ("r_v_3");
    romanized = syls.toRoman (false);
    if (romanized != u8"muemuetkritkungphunnuengsingmimi-ngulurue")
    {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // เกินเลยเม้ย
    syls = Syl ("k_Wn0");
    syls += Syl ("l_Wy0");
    syls += Syl ("m_Wy3");
    romanized = syls.toRoman();
    if (romanized != u8"koenloeimoei")
    {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // Test hyphenation cases

    // สง่า = sa-nga
    syls = Syl ("s_a_1");
    syls += Syl ("g_A_1");
    romanized = syls.toRoman();
    if (romanized != "sa-nga") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // บังอร = bang-on
    syls = Syl ("b_ag0");
    syls += Syl ("?_Cn0");
    romanized = syls.toRoman();
    if (romanized != "bang-on") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // สะอาด = sa-at
    syls = Syl ("s_a_1");
    syls += Syl ("?_At1");
    romanized = syls.toRoman();
    if (romanized != "sa-at") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // สำอาง = sam-ang
    syls = Syl ("s_am4");
    syls += Syl ("?_Ag0");
    romanized = syls.toRoman();
    if (romanized != "sam-ang") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

bool
TestPhonetic()
{
    bool isSuccess = true;
    SylString syls;

    // กกต้นหูกฺวางเหฺลียวเลาะร้องเป็นตาแซ่บ
    syls = Syl ("k_ok1");

    auto phonetic = syls.toPhonetic();
    if (phonetic != "KOK1") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_on2");
    phonetic = syls.toPhonetic();
    if (phonetic != "KOK1 TON2") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("h_U_4");
    phonetic = syls.toPhonetic();
    if (phonetic != "KOK1 TON2 HU:4") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("kwAg0");
    phonetic = syls.toPhonetic();
    if (phonetic != "KOK1 TON2 HU:4 KWA:NG0") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_Yw4");
    phonetic = syls.toPhonetic();
    if (phonetic != "KOK1 TON2 HU:4 KWA:NG0 LIA:O4") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_c_3");
    phonetic = syls.toPhonetic();
    if (phonetic != "KOK1 TON2 HU:4 KWA:NG0 LIA:O4 LAUH3") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("r_Cg3");
    phonetic = syls.toPhonetic();
    if (phonetic != "KOK1 TON2 HU:4 KWA:NG0 LIA:O4 LAUH3 RAU:NG3") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("p_en0");
    phonetic = syls.toPhonetic();
    if (phonetic != "KOK1 TON2 HU:4 KWA:NG0 LIA:O4 LAUH3 RAU:NG3 PEN0") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_A_0");
    phonetic = syls.toPhonetic();
    if (phonetic != "KOK1 TON2 HU:4 KWA:NG0 LIA:O4 LAUH3 RAU:NG3 PEN0 TA:0") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("s_xp2");
    phonetic = syls.toPhonetic();
    if (phonetic != "KOK1 TON2 HU:4 KWA:NG0 LIA:O4 LAUH3 RAU:NG3 PEN0 TA:0 SAEP2") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    // ละลันหลั่นล้า
    syls = Syl ("l_a_3");
    syls += Syl ("l_an0");
    syls += Syl ("l_an1");
    syls += Syl ("l_A_3");
    phonetic = syls.toPhonetic();
    if (phonetic != "LAH3 LAN0 LAN1 LA:3") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    // ใครใคร่ขายไข่ไก่คราคร่ำไม้ไหมเล่า
    syls = Syl ("cray0");
    syls += Syl ("cray2");
    syls += Syl ("c_Ay4");
    syls += Syl ("c_ay1");
    syls += Syl ("k_ay1");
    syls += Syl ("crA_0");
    syls += Syl ("cram2");
    syls += Syl ("m_Ay3");
    syls += Syl ("m_ay4");
    syls += Syl ("l_aw2");
    phonetic = syls.toPhonetic();
    if (phonetic != "KHRAI0 KHRAI2 KHA:I4 KHAI1 KAI1 KHRA:0 KHRAM2 MA:I3 MAI4 LAO2") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    // แมวและเด็กเหล่เล่นเจอะเจอเกลือเดินเกลือกคั่วกลิ้งร่วมโรงเรียน
    syls = Syl ("m_Xw0");
    syls += Syl ("l_x_3");
    syls += Syl ("d_ek1");
    syls += Syl ("l_E_1");
    syls += Syl ("l_en2");
    syls += Syl ("j_w_1");
    syls += Syl ("j_W_0");
    syls += Syl ("klZ_0");
    syls += Syl ("d_Wn0");
    syls += Syl ("klZk1");
    syls += Syl ("c_T_2");
    syls += Syl ("klig2");
    syls += Syl ("r_Tm2");
    syls += Syl ("r_Og0");
    syls += Syl ("r_Yn0");
    phonetic = syls.toPhonetic();
    if (phonetic !=
        "MAE:O0 LAEH3 DEK1 LE:1 LEN2 JOEH1 JOE:0 KLUEA:0 DOE:N0 KLUEA:K1 KHUA:2 KLING2 RUA:M2 RO:NG0 RIA:N0")
    {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    // มือมืดกฺรีดกุ้งพู้นหฺนึ่งสิ่งมิมีงูลุรึ
    syls = Syl ("m_V_0");
    syls += Syl ("m_Vt2");
    syls += Syl ("krIt1");
    syls += Syl ("k_ug2");
    syls += Syl ("P_Un3");
    syls += Syl ("n_vg1");
    syls += Syl ("s_ig1");
    syls += Syl ("m_i_3");
    syls += Syl ("m_I_0");
    syls += Syl ("g_U_0");
    syls += Syl ("l_u_3");
    syls += Syl ("r_v_3");
    phonetic = syls.toPhonetic();
    if (phonetic != "MUE:0 MUE:T2 KRI:T1 KUNG2 PHU:N3 NUENG1 SING1 MIH3 MI:0 NGU:0 LUH3 RUEH3")
    {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    // เกินเลยเม้ย
    syls = Syl ("k_Wn0");
    syls += Syl ("l_Wy0");
    syls += Syl ("m_Wy3");
    phonetic = syls.toPhonetic();
    if (phonetic != "KOE:N0 LOE:I0 MOE:I3")
    {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

int
main()
{
    bool isSuccess = true;

    if (!TestThaiPronun()) {
        isSuccess = false;
    }

    if (!TestRomanPronun()) {
        isSuccess = false;
    }

    if (!TestPhonetic()) {
        isSuccess = false;
    }

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
