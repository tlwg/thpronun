#include "output/sylout-thai.h"
#include "output/sylout-roman.h"
#include "output/sylout-phonetic.h"
#include "output/sylout-raw.h"
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
    syls = SylString ("l_a_3,l_an0,l_an1,l_A_3");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"ละ-ลัน-หฺลั่น-ล้า") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // ใครใคร่ขายไข่ไก่คราคร่ำไม้ไหมเล่า
    syls = SylString (
        "cray0,cray2,c_Ay4,c_ay1,k_ay1,crA_0,cram2,m_Ay3,m_ay4,l_aw2"
    );
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"คฺรัย-คฺรั่ย-ขาย-ขั่ย-กั่ย-คฺรา-คฺรั่ม-ม้าย-หฺมัย-เล่า") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // แมวและเด็กเหล่เล่นเจอะเจอเกลือเดินเกลือกคั่วกลิ้งร่วมโรงเรียน
    syls = SylString (
        "m_Xw0,l_x_3,d_ek1,l_E_1,l_en2,j_w_1,j_W_0,klZ_0,d_Wn0,klZk1,"
        "c_T_2,klig2,r_Tm2,r_Og0,r_Yn0"
    );
    thaiPronun = output->output (syls);
    if (thaiPronun !=
        u8"แมว-และ-เด็ก-เหฺล่-เล่น-เจอะ-เจอ-เกฺลือ-เดิน-เกฺลือก-คั่ว-กฺลิ้ง-ร่วม-โรง-เรียน")
    {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // มือมืดกฺรีดกุ้งพู้นหฺนึ่งสิ่งมิมีงูลุรึ
    syls = SylString (
        "m_V_0,m_Vt2,krIt1,k_ug2,P_Un3,n_vg1,s_ig1,m_i_3,m_I_0,g_U_0,"
        "l_u_3,r_v_3"
    );
    thaiPronun = output->output (syls);
    if (thaiPronun !=
        u8"มือ-มืด-กฺรีด-กุ้ง-พู้น-หฺนึ่ง-สิ่ง-มิ-มี-งู-ลุ-รึ")
    {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // เกินเลยเม้ย
    syls = SylString ("k_Wn0,l_Wy0,m_Wy3");
    thaiPronun = output->output (syls);
    if (thaiPronun !=
        u8"เกิน-เลย-เม้ย")
    {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // with blank syllable
    syls += Syl::Blank;
    syls += SylString ("?_Wy4");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"เกิน-เลย-เม้ย เอ๋ย")
    {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // with literal
    syls += Syl (20, u"hello");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"เกิน-เลย-เม้ย เอ๋ย-(hello)")
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
    auto output    = make_unique<RomanOutput>();
    auto outputCap = make_unique<RomanOutput> (true);

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
    syls = SylString ("l_a_3,l_an0,l_an1,l_A_3");
    romanized = output->output (syls);
    if (romanized != "lalanlanla") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // ใครใคร่ขายไข่ไก่คราคร่ำไม้ไหมเล่า
    syls = SylString (
        "cray0,cray2,c_Ay4,c_ay1,k_ay1,crA_0,cram2,m_Ay3,m_ay4,l_aw2"
    );
    romanized = output->output (syls);
    if (romanized != "khraikhraikhaikhaikaikhrakhrammaimailao") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // แมวและเด็กเหล่เล่นเจอะเจอเกลือเดินเกลือกคั่วกลิ้งร่วมโรงเรียน
    syls = SylString (
        "m_Xw0,l_x_3,d_ek1,l_E_1,l_en2,j_w_1,j_W_0,klZ_0,d_Wn0,klZk1,"
        "c_T_2,klig2,r_Tm2,r_Og0,r_Yn0"
    );
    romanized = outputCap->output (syls);
    if (romanized !=
        "Maeolaedeklelenchoechoeklueadoenklueakkhuaklingruamrongrian")
    {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // มือมืดกฺรีดกุ้งพู้นหฺนึ่งสิ่งมิมีงูลุรึ
    syls = SylString (
        "m_V_0,m_Vt2,krIt1,k_ug2,P_Un3,n_vg1,s_ig1,m_i_3,m_I_0,g_U_0,"
        "l_u_3,r_v_3"
    );
    romanized = output->output (syls);
    if (romanized != u8"muemuetkritkungphunnuengsingmimi-ngulurue")
    {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // เกินเลยเม้ย
    syls = SylString ("k_Wn0,l_Wy0,m_Wy3");
    romanized = output->output (syls);
    if (romanized != u8"koenloeimoei")
    {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // with blank syllable
    syls += Syl::Blank;
    syls += SylString ("?_Wy4");
    romanized = output->output (syls);
    if (romanized != u8"koenloeimoei oei")
    {
        cerr << "Wrong pronunciation '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // with literal
    syls += Syl (20, u"hello");
    romanized = output->output (syls);
    if (romanized != u8"koenloeimoei oei(hello)")
    {
        cerr << "Wrong pronunciation '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // Test hyphenation cases

    // สง่า = sa-nga
    syls = SylString ("s_a_1,g_A_1");
    romanized = output->output (syls);
    if (romanized != "sa-nga") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // บังอร = bang-on
    syls = SylString ("b_ag0,?_Cn0");
    romanized = output->output (syls);
    if (romanized != "bang-on") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // สะอาด = sa-at
    syls = SylString ("s_a_1,?_At1");
    romanized = output->output (syls);
    if (romanized != "sa-at") {
        cerr << "Wrong romanization '" << romanized << "'" << endl;
        isSuccess = false;
    }

    // สำอาง = sam-ang
    syls = SylString ("s_am4,?_Ag0");
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
    if (phonetic != "kohk1") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_on2");
    phonetic = output->output (syls);
    if (phonetic != "kohk1 tohn2") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("h_U_4");
    phonetic = output->output (syls);
    if (phonetic != "kohk1 tohn2 huw4") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("kwAg0");
    phonetic = output->output (syls);
    if (phonetic != "kohk1 tohn2 huw4 kwaang0") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_Yw4");
    phonetic = output->output (syls);
    if (phonetic != "kohk1 tohn2 huw4 kwaang0 liaaw4") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_c_3");
    phonetic = output->output (syls);
    if (phonetic != "kohk1 tohn2 huw4 kwaang0 liaaw4 laoh3") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("r_Cg3");
    phonetic = output->output (syls);
    if (phonetic != "kohk1 tohn2 huw4 kwaang0 liaaw4 laoh3 raowng3") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("p_en0");
    phonetic = output->output (syls);
    if (phonetic != "kohk1 tohn2 huw4 kwaang0 liaaw4 laoh3 raowng3 pehn0") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_A_0");
    phonetic = output->output (syls);
    if (phonetic != "kohk1 tohn2 huw4 kwaang0 liaaw4 laoh3 raowng3 pehn0 taa0") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("s_xp2");
    phonetic = output->output (syls);
    if (phonetic != "kohk1 tohn2 huw4 kwaang0 liaaw4 laoh3 raowng3 pehn0 taa0 saehp2") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    // ละลันหลั่นล้า
    syls = SylString ("l_a_3,l_an0,l_an1,l_A_3");
    phonetic = output->output (syls);
    if (phonetic != "lah3 lahn0 lahn1 laa3") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    // ใครใคร่ขายไข่ไก่คราคร่ำไม้ไหมเล่า
    syls = SylString (
        "cray0,cray2,c_Ay4,c_ay1,k_ay1,crA_0,cram2,m_Ay3,m_ay4,l_aw2"
    );
    phonetic = output->output (syls);
    if (phonetic != "khrahy0 khrahy2 khaay4 khahy1 kahy1 khraa0 khrahm2 maay3 mahy4 lahw2") {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    // แมวและเด็กเหล่เล่นเจอะเจอเกลือเดินเกลือกคั่วกลิ้งร่วมโรงเรียน
    syls = SylString (
        "m_Xw0,l_x_3,d_ek1,l_E_1,l_en2,j_w_1,j_W_0,klZ_0,d_Wn0,klZk1,"
        "c_T_2,klig2,r_Tm2,r_Og0,r_Yn0"
    );
    phonetic = output->output (syls);
    if (phonetic !=
        "maeew0 laeh3 dehk1 ley1 lehn2 joeh1 joee0 klueaa0 doeen0 klueaak1 "
        "khuaa2 klihng2 ruaam2 rowng0 riaan0")
    {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    // มือมืดกฺรีดกุ้งพู้นหฺนึ่งสิ่งมิมีงูลุรึ
    syls = SylString (
        "m_V_0,m_Vt2,krIt1,k_ug2,P_Un3,n_vg1,s_ig1,m_i_3,m_I_0,g_U_0,"
        "l_u_3,r_v_3"
    );
    phonetic = output->output (syls);
    if (phonetic != "muee0 mueet2 kriyt1 kuhng2 phuwn3 nuehng1 sihng1 mih3 miy0 nguw0 luh3 rueh3")
    {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    // เกินเลยเม้ย
    syls = SylString ("k_Wn0,l_Wy0,m_Wy3");
    phonetic = output->output (syls);
    if (phonetic != "koeen0 loeey0 moeey3")
    {
        cerr << "Wrong phonetic '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    // with blank syllable
    syls += Syl::Blank;
    syls += SylString ("?_Wy4");
    phonetic = output->output (syls);
    if (phonetic != "koeen0 loeey0 moeey3 oeey4")
    {
        cerr << "Wrong pronunciation '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    // with literal
    syls += Syl (20, u"hello");
    phonetic = output->output (syls);
    if (phonetic != "koeen0 loeey0 moeey3 oeey4 (hello)")
    {
        cerr << "Wrong pronunciation '" << phonetic << "'" << endl;
        isSuccess = false;
    }

    return isSuccess;
}

bool
TestRawPronun()
{
    bool isSuccess = true;
    SylString syls;
    auto output
        = make_unique<DelimOutput> (make_unique<RawSylOutput>(), ',');

    // กกต้นหูกฺวางเหฺลียวเลาะร้องเป็นตาแซ่บ
    syls = Syl ("k_ok1@2");

    auto rawPronun = output->output (syls);
    if (rawPronun != "k_ok1@2") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_on2@5");
    rawPronun = output->output (syls);
    if (rawPronun != "k_ok1@2,t_on2@5") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("h_U_4@7");
    rawPronun = output->output (syls);
    if (rawPronun != "k_ok1@2,t_on2@5,h_U_4@7") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("kwAg0@11");
    rawPronun = output->output (syls);
    if (rawPronun != "k_ok1@2,t_on2@5,h_U_4@7,kwAg0@11") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_Yw4@17");
    rawPronun = output->output (syls);
    if (rawPronun != "k_ok1@2,t_on2@5,h_U_4@7,kwAg0@11,l_Yw4@17") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("l_c_3@21");
    rawPronun = output->output (syls);
    if (rawPronun != "k_ok1@2,t_on2@5,h_U_4@7,kwAg0@11,l_Yw4@17,l_c_3@21") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("r_Cg3@25");
    rawPronun = output->output (syls);
    if (rawPronun != "k_ok1@2,t_on2@5,h_U_4@7,kwAg0@11,l_Yw4@17,l_c_3@21,r_Cg3@25") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("p_en0@29");
    rawPronun = output->output (syls);
    if (rawPronun != "k_ok1@2,t_on2@5,h_U_4@7,kwAg0@11,l_Yw4@17,l_c_3@21,r_Cg3@25,p_en0@29") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("t_A_0@31");
    rawPronun = output->output (syls);
    if (rawPronun != "k_ok1@2,t_on2@5,h_U_4@7,kwAg0@11,l_Yw4@17,l_c_3@21,r_Cg3@25,p_en0@29,t_A_0@31") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    syls += Syl ("s_xp2@35");
    rawPronun = output->output (syls);
    if (rawPronun != "k_ok1@2,t_on2@5,h_U_4@7,kwAg0@11,l_Yw4@17,l_c_3@21,r_Cg3@25,p_en0@29,t_A_0@31,s_xp2@35") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    // ละลันหลั่นล้า
    syls = SylString ("l_a_3@2,l_an0@5,l_an1@10,l_A_3@13");
    rawPronun = output->output (syls);
    if (rawPronun != "l_a_3@2,l_an0@5,l_an1@10,l_A_3@13") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    // ใครใคร่ขายไข่ไก่คราคร่ำไม้ไหมเล่า
    syls = SylString (
        "cray0@3,cray2@7,c_Ay4@10,c_ay1@13,k_ay1@16,crA_0@19,cram2@23,m_Ay3@26,m_ay4@29,l_aw2@33"
    );
    rawPronun = output->output (syls);
    if (rawPronun != "cray0@3,cray2@7,c_Ay4@10,c_ay1@13,k_ay1@16,crA_0@19,cram2@23,m_Ay3@26,m_ay4@29,l_aw2@33") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    // แมวและเด็กเหล่เล่นเจอะเจอเกลือเดินเกลือกคั่วกลิ้งร่วมโรงเรียน
    syls = SylString (
        "m_Xw0@3,l_x_3@6,d_ek1@10,l_E_1@14,l_en2@18,j_w_1@22,j_W_0@25,"
        "klZ_0@30,d_Wn0@34,klZk1@40,c_T_2@44,klig2@49,r_Tm2@53,r_Og0@56,"
        "r_Yn0@61"
    );
    rawPronun = output->output (syls);
    if (rawPronun !=
        "m_Xw0@3,l_x_3@6,d_ek1@10,l_E_1@14,l_en2@18,j_w_1@22,j_W_0@25,"
        "klZ_0@30,d_Wn0@34,klZk1@40,c_T_2@44,klig2@49,r_Tm2@53,r_Og0@56,"
        "r_Yn0@61")
    {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    // มือมืดกฺรีดกุ้งพู้นหฺนึ่งสิ่งมิมีงูลุรึ
    syls = SylString (
        "m_V_0@3,m_Vt2@6,krIt1@10,k_ug2@14,P_Un3@18,n_vg1@23,s_ig1@27,"
        "m_i_3@29,m_I_0@31,g_U_0@33,l_u_3@35,r_v_3@37"
    );
    rawPronun = output->output (syls);
    if (rawPronun !=
        "m_V_0@3,m_Vt2@6,krIt1@10,k_ug2@14,P_Un3@18,n_vg1@23,s_ig1@27,"
        "m_i_3@29,m_I_0@31,g_U_0@33,l_u_3@35,r_v_3@37")
    {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    // เกินเลยเม้ย
    syls = SylString ("k_Wn0@4,l_Wy0@7,m_Wy3@11");
    rawPronun = output->output (syls);
    if (rawPronun != "k_Wn0@4,l_Wy0@7,m_Wy3@11") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    // with blank syllable
    syls += Syl::Blank;
    syls += SylString ("?_Wy4@15");
    rawPronun = output->output (syls);
    if (rawPronun != "k_Wn0@4,l_Wy0@7,m_Wy3@11 ?_Wy4@15") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
        isSuccess = false;
    }

    // with literal
    syls += Syl (20, u"hello");
    rawPronun = output->output (syls);
    if (rawPronun != "k_Wn0@4,l_Wy0@7,m_Wy3@11 ?_Wy4@15,(hello)@20") {
        cerr << "Wrong pronunciation '" << rawPronun << "'" << endl;
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
    syls = SylString ("l_a_3,l_an0,l_an1,l_A_3");
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"[\"ละ\",\"ลัน\",\"หฺลั่น\",\"ล้า\"]") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // ใครใคร่ขายไข่ไก่คราคร่ำไม้ไหมเล่า
    syls = SylString (
        "cray0,cray2,c_Ay4,c_ay1,k_ay1,crA_0,cram2,m_Ay3,m_ay4,l_aw2"
    );
    thaiPronun = output->output (syls);
    if (thaiPronun != u8"[\"คฺรัย\",\"คฺรั่ย\",\"ขาย\",\"ขั่ย\",\"กั่ย\",\"คฺรา\",\"คฺรั่ม\",\"ม้าย\",\"หฺมัย\",\"เล่า\"]") {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // แมวและเด็กเหล่เล่นเจอะเจอเกลือเดินเกลือกคั่วกลิ้งร่วมโรงเรียน
    syls = SylString (
        "m_Xw0,l_x_3,d_ek1,l_E_1,l_en2,j_w_1,j_W_0,klZ_0,d_Wn0,klZk1,"
        "c_T_2,klig2,r_Tm2,r_Og0,r_Yn0"
    );
    thaiPronun = output->output (syls);
    if (thaiPronun !=
        u8"[\"แมว\",\"และ\",\"เด็ก\",\"เหฺล่\",\"เล่น\",\"เจอะ\",\"เจอ\",\"เกฺลือ\",\"เดิน\",\"เกฺลือก\",\"คั่ว\",\"กฺลิ้ง\",\"ร่วม\",\"โรง\",\"เรียน\"]")
    {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // มือมืดกฺรีดกุ้งพู้นหฺนึ่งสิ่งมิมีงูลุรึ
    syls = SylString (
        "m_V_0,m_Vt2,krIt1,k_ug2,P_Un3,n_vg1,s_ig1,m_i_3,m_I_0,g_U_0,"
        "l_u_3,r_v_3"
    );
    thaiPronun = output->output (syls);
    if (thaiPronun !=
        u8"[\"มือ\",\"มืด\",\"กฺรีด\",\"กุ้ง\",\"พู้น\",\"หฺนึ่ง\",\"สิ่ง\",\"มิ\",\"มี\",\"งู\",\"ลุ\",\"รึ\"]")
    {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // เกินเลยเม้ย
    syls = SylString ("k_Wn0,l_Wy0,m_Wy3");
    thaiPronun = output->output (syls);
    if (thaiPronun !=
        u8"[\"เกิน\",\"เลย\",\"เม้ย\"]")
    {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // with blank syllable
    syls += Syl::Blank;
    syls += SylString ("?_Wy4");
    thaiPronun = output->output (syls);
    if (thaiPronun !=
        u8"[\"เกิน\",\"เลย\",\"เม้ย\",\" \",\"เอ๋ย\"]")
    {
        cerr << "Wrong pronunciation '" << thaiPronun << "'" << endl;
        isSuccess = false;
    }

    // with literal
    syls += Syl (20, u"hello");
    thaiPronun = output->output (syls);
    if (thaiPronun !=
        u8"[\"เกิน\",\"เลย\",\"เม้ย\",\" \",\"เอ๋ย\",\"(hello)\"]")
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

    cout << "Testing Thai Pronunciation" << endl;
    if (!TestThaiPronun()) {
        isSuccess = false;
    }

    cout << "Testing Romanization" << endl;
    if (!TestRomanPronun()) {
        isSuccess = false;
    }

    cout << "Testing Phonetic Pronunciation" << endl;
    if (!TestPhonetic()) {
        isSuccess = false;
    }

    cout << "Testing Raw Pronunciation" << endl;
    if (!TestRawPronun()) {
        isSuccess = false;
    }

    cout << "Testing JSON output" << endl;
    if (!TestJson()) {
        isSuccess = false;
    }

    return isSuccess ? 0 : 1;
}

/*
vi:ts=4:ai:expandtab
*/
