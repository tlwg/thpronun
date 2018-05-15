#include "output/sylout-thai.h"
#include "output/sylout-roman.h"
#include "output/sylout-phonetic.h"
#include "output/output-delim.h"
#include "output/output-roman.h"
#include "output/output-json.h"

#include <iostream>
#include <memory>

using namespace std;

bool
TestThaiPronun()
{
    bool isSuccess = true;
    SylString syls;
    auto output
        = make_unique<DelimOutput> (make_unique<ThaiSylOutput>(), '-');

    // กกต้นหูกฺวางเหฺลียวเลาะร้องเป็นตาแซ่บ
    syls = Syl ("k_ok1");

    auto thaiPronun = output->output (syls);
    if (thaiPronun != u8"กก") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_on2");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"กก-ต้น") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("h_U_4");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"กก-ต้น-หู") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("kwAg0");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_Yw4");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_c_3");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("r_Cg3");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ-ร้อง") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("p_en0");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ-ร้อง-เป็น") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_A_0");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ-ร้อง-เป็น-ตา") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("s_xp2");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"กก-ต้น-หู-กฺวาง-เหฺลียว-เลาะ-ร้อง-เป็น-ตา-แซ่บ") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // ละลันหลั่นล้า
    syls = Syl ("l_a_3");
    syls += Syl ("l_an0");
    syls += Syl ("l_an1");
    syls += Syl ("l_A_3");
    thaiPronun = output->output (syls);
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
    thaiPronun = output->output (syls);
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
    thaiPronun = output->output (syls);
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
    thaiPronun = output->output (syls);
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
    thaiPronun = output->output (syls);
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
    auto output
        = make_unique<RomanOutput> (make_unique<RomanSylOutput>());
    auto outputCap
        = make_unique<RomanOutput> (make_unique<RomanSylOutput>(), true);

    // กกต้นหูกฺวางเหฺลียวเลาะร้องเป็นตาแซ่บ
    syls = Syl ("k_ok1");

    auto romanized = output->output (syls);
    if (romanized != "kok") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_on2");
    romanized = output->output (syls);
    if (romanized != "kokton") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("h_U_4");
    romanized = output->output (syls);
    if (romanized != "koktonhu") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("kwAg0");
    romanized = output->output (syls);
    if (romanized != "koktonhukwang") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_Yw4");
    romanized = output->output (syls);
    if (romanized != "koktonhukwangliao") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_c_3");
    romanized = output->output (syls);
    if (romanized != "koktonhukwangliaolo") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("r_Cg3");
    romanized = output->output (syls);
    if (romanized != "koktonhukwangliaolorong") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("p_en0");
    romanized = output->output (syls);
    if (romanized != "koktonhukwangliaolorongpen") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_A_0");
    romanized = output->output (syls);
    if (romanized != "koktonhukwangliaolorongpenta") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("s_xp2");
    romanized = output->output (syls);
    if (romanized != "koktonhukwangliaolorongpentasaep") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // ละลันหลั่นล้า
    syls = Syl ("l_a_3");
    syls += Syl ("l_an0");
    syls += Syl ("l_an1");
    syls += Syl ("l_A_3");
    romanized = output->output (syls);
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
    romanized = output->output (syls);
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
    romanized = outputCap->output (syls);
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
    romanized = output->output (syls);
    if (romanized != u8"muemuetkritkungphunnuengsingmimi-ngulurue")
    {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // เกินเลยเม้ย
    syls = Syl ("k_Wn0");
    syls += Syl ("l_Wy0");
    syls += Syl ("m_Wy3");
    romanized = output->output (syls);
    if (romanized != u8"koenloeimoei")
    {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // Test hyphenation cases

    // สง่า = sa-nga
    syls = Syl ("s_a_1");
    syls += Syl ("g_A_1");
    romanized = output->output (syls);
    if (romanized != "sa-nga") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // บังอร = bang-on
    syls = Syl ("b_ag0");
    syls += Syl ("?_Cn0");
    romanized = output->output (syls);
    if (romanized != "bang-on") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // สะอาด = sa-at
    syls = Syl ("s_a_1");
    syls += Syl ("?_At1");
    romanized = output->output (syls);
    if (romanized != "sa-at") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // สำอาง = sam-ang
    syls = Syl ("s_am4");
    syls += Syl ("?_Ag0");
    romanized = output->output (syls);
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
    auto output
        = make_unique<DelimOutput> (make_unique<PhoneticSylOutput>(), ' ');

    // กกต้นหูกฺวางเหฺลียวเลาะร้องเป็นตาแซ่บ
    syls = Syl ("k_ok1");

    auto phonetic = output->output (syls);
    if (phonetic != "KOHK1") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_on2");
    phonetic = output->output (syls);
    if (phonetic != "KOHK1 TOHN2") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("h_U_4");
    phonetic = output->output (syls);
    if (phonetic != "KOHK1 TOHN2 HUW4") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("kwAg0");
    phonetic = output->output (syls);
    if (phonetic != "KOHK1 TOHN2 HUW4 KWAANG0") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_Yw4");
    phonetic = output->output (syls);
    if (phonetic != "KOHK1 TOHN2 HUW4 KWAANG0 LIAAW4") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_c_3");
    phonetic = output->output (syls);
    if (phonetic != "KOHK1 TOHN2 HUW4 KWAANG0 LIAAW4 LAOH3") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("r_Cg3");
    phonetic = output->output (syls);
    if (phonetic != "KOHK1 TOHN2 HUW4 KWAANG0 LIAAW4 LAOH3 RAOWNG3") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("p_en0");
    phonetic = output->output (syls);
    if (phonetic != "KOHK1 TOHN2 HUW4 KWAANG0 LIAAW4 LAOH3 RAOWNG3 PEHN0") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_A_0");
    phonetic = output->output (syls);
    if (phonetic != "KOHK1 TOHN2 HUW4 KWAANG0 LIAAW4 LAOH3 RAOWNG3 PEHN0 TAA0") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("s_xp2");
    phonetic = output->output (syls);
    if (phonetic != "KOHK1 TOHN2 HUW4 KWAANG0 LIAAW4 LAOH3 RAOWNG3 PEHN0 TAA0 SAEHP2") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    // ละลันหลั่นล้า
    syls = Syl ("l_a_3");
    syls += Syl ("l_an0");
    syls += Syl ("l_an1");
    syls += Syl ("l_A_3");
    phonetic = output->output (syls);
    if (phonetic != "LAH3 LAHN0 LAHN1 LAA3") {
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
    phonetic = output->output (syls);
    if (phonetic != "KHRAHY0 KHRAHY2 KHAAY4 KHAHY1 KAHY1 KHRAA0 KHRAHM2 MAAY3 MAHY4 LAHW2") {
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
    phonetic = output->output (syls);
    if (phonetic !=
        "MAEEW0 LAEH3 DEHK1 LEY1 LEHN2 JOEH1 JOEE0 KLUEAA0 DOEEN0 KLUEAAK1 KHUAA2 KLIHNG2 RUAAM2 ROWNG0 RIAAN0")
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
    phonetic = output->output (syls);
    if (phonetic != "MUEE0 MUEET2 KRIYT1 KUHNG2 PHUWN3 NUEHNG1 SIHNG1 MIH3 MIY0 NGUW0 LUH3 RUEH3")
    {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    // เกินเลยเม้ย
    syls = Syl ("k_Wn0");
    syls += Syl ("l_Wy0");
    syls += Syl ("m_Wy3");
    phonetic = output->output (syls);
    if (phonetic != "KOEEN0 LOEEY0 MOEEY3")
    {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

bool
TestJson()
{
    bool isSuccess = true;
    SylString syls;
    auto output
        = make_unique<JsonOutput> (make_unique<ThaiSylOutput>());

    // กกต้นหูกฺวางเหฺลียวเลาะร้องเป็นตาแซ่บ
    syls = Syl ("k_ok1");

    auto thaiPronun = output->output (syls);
    if (thaiPronun != u8"[\"กก\"]") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_on2");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"[\"กก\",\"ต้น\"]") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("h_U_4");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"[\"กก\",\"ต้น\",\"หู\"]") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("kwAg0");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"[\"กก\",\"ต้น\",\"หู\",\"กฺวาง\"]") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_Yw4");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"[\"กก\",\"ต้น\",\"หู\",\"กฺวาง\",\"เหฺลียว\"]") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_c_3");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"[\"กก\",\"ต้น\",\"หู\",\"กฺวาง\",\"เหฺลียว\",\"เลาะ\"]") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("r_Cg3");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"[\"กก\",\"ต้น\",\"หู\",\"กฺวาง\",\"เหฺลียว\",\"เลาะ\",\"ร้อง\"]") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("p_en0");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"[\"กก\",\"ต้น\",\"หู\",\"กฺวาง\",\"เหฺลียว\",\"เลาะ\",\"ร้อง\",\"เป็น\"]") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_A_0");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"[\"กก\",\"ต้น\",\"หู\",\"กฺวาง\",\"เหฺลียว\",\"เลาะ\",\"ร้อง\",\"เป็น\",\"ตา\"]") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("s_xp2");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"[\"กก\",\"ต้น\",\"หู\",\"กฺวาง\",\"เหฺลียว\",\"เลาะ\",\"ร้อง\",\"เป็น\",\"ตา\",\"แซ่บ\"]") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // ละลันหลั่นล้า
    syls = Syl ("l_a_3");
    syls += Syl ("l_an0");
    syls += Syl ("l_an1");
    syls += Syl ("l_A_3");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"[\"ละ\",\"ลัน\",\"หฺลั่น\",\"ล้า\"]") {
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
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"[\"คฺรัย\",\"คฺรั่ย\",\"ขาย\",\"ขั่ย\",\"กั่ย\",\"คฺรา\",\"คฺรั่ม\",\"ม้าย\",\"หฺมัย\",\"เล่า\"]") {
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
    thaiPronun = output->output (syls);
    if (thaiPronun !=
        u8"[\"แมว\",\"และ\",\"เด็ก\",\"เหฺล่\",\"เล่น\",\"เจอะ\",\"เจอ\",\"เกฺลือ\",\"เดิน\",\"เกฺลือก\",\"คั่ว\",\"กฺลิ้ง\",\"ร่วม\",\"โรง\",\"เรียน\"]")
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
    thaiPronun = output->output (syls);
    if (thaiPronun !=
        u8"[\"มือ\",\"มืด\",\"กฺรีด\",\"กุ้ง\",\"พู้น\",\"หฺนึ่ง\",\"สิ่ง\",\"มิ\",\"มี\",\"งู\",\"ลุ\",\"รึ\"]")
    {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // เกินเลยเม้ย
    syls = Syl ("k_Wn0");
    syls += Syl ("l_Wy0");
    syls += Syl ("m_Wy3");
    thaiPronun = output->output (syls);
    if (thaiPronun !=
        u8"[\"เกิน\",\"เลย\",\"เม้ย\"]")
    {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
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

    if (!TestJson()) {
        isSuccess = false;
    }

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
