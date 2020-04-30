#include"opred.h"
#include"nastroy.h"
#include <graphics.h>
//--------------------------------------
extern unsigned long int
BAZ_ADR1,
BAZ_ADR11,
BAZ_ADR2,
BAZ_ADR3,
BAZ_ADR4,
BAZ_ADR5,
BAZ_ADR6,
to_chislo,
tormoz;
extern long FIR_time,
first_time,
pooo[kol_VO],
SEC_time,
second_time,
t_inf[skoko_stoek],//фиксатор времени выдачи информации в ДЦ
t_com[skoko_stoek],//фиксатор времени выдачи команды в стойку
t_com_dc[skoko_stoek],//фиксатор времени выдачи команды ДЦ в стойку
TIME_OUT_PVM,
tii,
tiiq,
time_ly[skoko_stoek],
time_lz[skoko_stoek],
time_lc[skoko_stoek],
time_ls[skoko_stoek],
time_lu[skoko_stoek],
time_lv[skoko_stoek];
extern int
    mas_lu[skoko_stoek][15],
    mas_lv[skoko_stoek][15],
    mas_ly[skoko_stoek][16],
    mas_lz[skoko_stoek][16],
    mas_lc[skoko_stoek][16],
    mas_ls[skoko_stoek][16],
    mas_lu[skoko_stoek][15],
    mas_lv[skoko_stoek][15],
        ly[skoko_stoek][4],
        lz[skoko_stoek][4],
        lc[skoko_stoek][4],
        ls[skoko_stoek][4],
        lu[skoko_stoek][3],
        lv[skoko_stoek][3];

//----------------------------------------
extern struct so_so soob;
extern struct dosdate_t dat;
//----------------------------------------
extern int a_klav;
extern int ANALIZ[skoko_stoek];
extern int ANALIZ_DC;
extern int old_aoar[skoko_stoek];
extern int AV_zdem;
extern int avap;
extern int AVARI;
extern int AVARIIN;
extern int b_h1;
extern int b_m1;
extern int b_s1;
extern int BAIT_PRER;
extern int BAM;
extern int basha;
extern int bata;
extern int BAZA;
extern int BEDA[10];
extern int beg[2];
extern int bi;
extern int bil_bil;
extern int bit_pso;
#ifdef SPDLP
extern int bt_spdlp[N_BIT_SCB];
extern int byte_spdlp[N_BIT_SCB];
#endif
#ifdef AVTOD
extern int C_strel[CH_str];
#endif
extern int cha;
extern int chasi;
extern int chit;
extern int chita;
extern int cikl_obnov;
extern int cikl_avto;
extern int COD_OGR;
extern int COD_OTPR[2];
extern int COD_PRIEM[2];
extern int COD_PS_NEW;
extern int COD_PS_OLD;
extern int COD_UCH_UDAL[2];
extern int CVETCVETOF;
extern int CVTF;
extern int cvv;
extern int da1;
extern int d_d;
extern int danet;
extern int dayy_;
extern int den;
extern int den1;
extern int DISK;
extern int down;
extern int DU;
extern int dv;
extern int DVA_MO;
extern int ELE;
extern int END;
extern int end_avto;
extern int end_marsh;
extern int End_vara;
extern int FFFlag;
extern int f_ob1;
extern int fi_co1;
extern int fiki;
extern int file_arc;
extern int file_neispr;
extern int file_oblom;
extern int file_soob;
extern int finish;
extern int first_col;
extern int fix_ts_sos[skoko_stoek];
extern int fix_tu_sos[skoko_stoek];
extern int fix_rek_sos[skoko_stoek];
extern int fl_file;
extern int fl_read;
extern int Fla_no_pp;
extern int flag_paro;
extern int FLAG_PO;
extern int flago;
extern int flagoutmsg;
extern int flms;
extern int flpass;
extern int flug;
extern int fr1[kol_VO][14];
extern int fr2[kol_VO][16];
extern int fr3[kol_VO][13];
extern int fra[kol_VO][2];
extern int g_g;
extern int god;
extern int god1;
extern int GraphDriver;
extern int GraphMode;
extern int gri;
extern int GUAV;
extern int half_marsh;
extern int half_marsh1;
extern int having;
extern int help;
extern int ho_ur;
extern int hod;
extern int hoz_poezd[2];
extern int hudo;
extern int hudoo;
extern int i_s;
extern int i3;
extern int iqw;
extern int j_jj;
extern int k;
extern int kadr[12][50];
extern int klaval;
extern int klo;
extern int ko;
extern int kom_pereezd;
extern int komanda2[skoko_stoek];
extern int konec[2];
extern int konec_dc;
extern int kot;
extern int KSK[skoko_stoek];
extern int last_day;
extern int left_up_left[14];
extern int left_up_right[14];
extern int m_m;
extern int maka;
extern int maket;
extern int Makst;
extern int mane;
extern int manevr;
extern int manevro;
extern int MAR_GOT[skoko_stoek];
extern int marazm;
extern int MAR_GOT[skoko_stoek];
extern int marshrut[skoko_stoek][3];
#ifdef VSP
extern int mark[VSP][2];
#endif
extern int markery[kol_OB_UPR][8];
extern int me_uk;
extern int menu_N;
extern int mes;
extern int mes1;
extern int mi_n;
extern int minu;
extern int misto;
extern int mlc[16];
extern int mls[16];
extern int mlu[15];
extern int mlv[15];
extern int mly[16];
extern int mlz[16];
extern int mo1;
extern int MODE_KN;
extern int modi;
extern int modi_new;
extern int monn_;
extern int mouse_down;
extern int MOUSE_ON;
extern int mouser;
extern int n;
extern int n_1;
extern int n_2;
extern int N_HELP;
extern int n_m;
extern int n_ob1;
extern int n_ob2;
extern int N_OGR;
extern int n_s;
#ifdef AVTOD
extern int N_strel[N_str];
#endif
extern int na;
extern int nach_avto;
extern int nach_marsh;
extern int nach0_marsh;
extern int NE;
extern int NEISPRAVEN;
extern int net_kontro;
extern int new_day;
extern int nikuda;
extern int NM;
extern int NOM_NEXT;
extern int nomer;
extern int NOMER_ARMA;
extern int NOMER_FOR_FR4;
extern int number;
extern int OB_PRER;
extern int obnov;
extern int okno_otkaz;
extern int old_me;
extern int old_modi;
extern int old_punkt;
extern int oper;
extern int oppp;
extern int opred;
extern int oshibka;
extern int osya;
extern int ot;
extern int otkaz_sos[skoko_stoek];//флаг индикации отказа ТС соседней ПЭВМ
extern int otkaz_tu_sos[skoko_stoek];//флаг индикации отказа ТУ соседнейПЭВМ
extern int otl_soob;
extern int Otlog;
extern int otv_kom;
extern int pat;
extern int pauza;
extern int perekluch;
extern int perezap;
extern int plo;
extern int plu;
extern int po_ma;
extern int podgr;
extern int podsvetka;
extern int point;
extern int pointer;
extern int poka;
extern int povt1;
extern int povt1;
extern int povt2;
extern int priem_;
extern int PRIEM_FR4;
extern int PRKL;
extern int prohod_1;
extern int prorisovka;
extern int PROV_SCB;
extern int prv[skoko_stoek];
extern int punkt_N;
extern int pust_pvm;
extern int pusto;
extern int puti;
extern int qf;
extern int R;
extern int r;
extern int raz_raz;
extern int re;
extern int right_up_left[14];
extern int right_up_right[14];
extern int ris_krest;
extern int row;
extern int s1;
extern int s2;
extern int sbros;
extern int sbros1;
extern int schet;
extern int ScLk;
extern int se_c;
extern int se_co1;
extern int seku;
extern int SEZON;
extern int siv;
extern int soob_for_oper;
extern int spa;
extern int spdlp;
extern int spkont[UPR1+UPR2][5];
extern int spputi[PUT1+PUT2][5];
extern int spsig[SIG1+SIG2][5];
extern int spspu[UCH1+UCH2][5];
extern int spstr[STR1+STR2][5];
extern int STAT;
extern int STATUS;
extern int STOP;
extern int STOP_TUMS[2];
extern int STOP_BBKP;
extern int str_i;
extern int strelki[5][3];
#ifdef kol_STY
extern int styki[kol_STY][3];
#endif
extern int t_koma[2];
extern int t_otpusk;
extern int t_pust[skoko_stoek];
extern int t_pust_dc;
extern int t_t;
extern int TELEUP;
extern int TEST_KANAL;
extern int TEST_N;
extern int the_kon;
extern int timer_set;
extern int TORMOZ;
extern int tst;
extern int u;
extern int ukaz_ot_dc;
extern int ukaz_out_spd;
extern int ukaz_spd;
extern int ukaz_trass;//числовойуказательобъектавмассивеtrassa
extern int uprav;
extern int USER_FONT;
extern int V;
extern int vib_ma;
extern int vibeg;
extern int vih_vopr;
extern int vozvr;
extern int vrem;
extern int vspz;
extern int vtora;
extern int vvod_set;
extern int vysv;
extern int vysvv;
extern int vzvod;
extern int was[WAZO];
extern int who_was;
extern int X_DC;
extern int X_kan[2];
extern int X_m;
extern int X_m_old;
extern int X_time;
extern int xc;
extern int Y_DC;
extern int Y_kan[2];
extern int Y_m;
extern int Y_m_isk;
extern int Y_m_old;
extern int Y_txt;
extern int yc;
extern int ye1;
extern int yearr_;
extern int zabeg;
extern int zafix;
extern int ZAGRUZKA;
extern int ZAHOD;
extern int zakr;
extern int zalet;
extern int zapr;
extern int zapret[skoko_stoek];
extern int zapret_sos[skoko_stoek];
extern int zapretvybora;
extern int ZAPROS_FR4;
extern int zapusk;
extern int zdem_ps_pso;
extern int Zdem_vibor_marshruta;
extern int Zdem_vibor_opov;
extern int Zdem;
extern int ZONA_KURSORA;
extern int zvuk;
extern int zzzzx;

//--------------------------
extern int ukaz_vyd[skoko_stoek];//указатели очередного байта выдачи в буфере BUF_OUT в ТУМС
extern int ukaz_zap[skoko_stoek];//указатели очередного байта записи данных в буфере BUF_OUT в ТУМС
extern int ukaz_read[skoko_stoek];//указатели очередного байта выдачи в буфере BUF_OUT в ТУМС
extern int ukaz_priem[skoko_stoek];//указатели очередного байта записи данных в буфере BUF_OUT в ТУМС
extern int N_RAZ[skoko_stoek];//счетчик числа повторений выдачи команд в ТУМС
extern int sboy_ts[skoko_stoek]; //счетчики сбоев канала ТС для ТУМС
extern int sboy_tu[skoko_stoek];//счетчики сбоев канала ТУ для ТУМС
extern int otkaz_ts[skoko_stoek];//индикаторы отказа канала ТС для ТУМС
extern int otkaz_tu[skoko_stoek];//индикаторы отказа канала управления ТУМС
//------------------------------------------------------
extern int ukaz_vyd_dc;//указатели очередного байта выдачи в ДЦ
extern int ukaz_zap_dc;//указатель очередного;байта записи из ДЦ 
extern int ukaz_read_dc;
extern int ukaz_priem_dc;
extern int ukaz_com_dc;//указатель на активный регистр приема команд ДЦ для передачи в ТУМС

extern int sboy_ts_dc;//счетчик сбоев канала ТС для ДЦ
extern int otkaz_ts_dc;//индикатор отказа канала ТС для ДЦ
extern int otkaz_tu_dc;//индикатор отказа канала управления ДЦ
extern int dc_not_plus;

//-------------------------------------------------------
extern unsigned char password[8],
adr_spdlp,
str_baz[32],
BEG_TIM[20],
BUF_OUT_SPD[75],
chudo[20],
END_TIM[20],
K64,
K32,
LEN_SPD,
NAME_FILE[17],
OBMEN_PVM,
OBMEN_PVM_OLD,
STRoka[40],
sbis[2],
D_kont[1][9],
otopri[kopo][50],
#ifdef KOL_SOO2
#if KOL_SOO1>KOL_SOO2
podgruppa[KOL_SOO1],
#else
podgruppa[KOL_SOO2],
#endif
#else
podgruppa[KOL_SOO1],
#endif
pako[kol_VO][30],
//-------------------перемннные для обмена с ТУМС и ДЦ
SYMBOL[skoko_stoek],//массив приемных ячеек для записи очередного
                    //символа из порта вводаBUF_OUT[skoko_stoek][SIZE_BUF_OUT],//кольцевые буферы вывода в ТУМС
BUF_IN[skoko_stoek][SIZE_BUF_PRIEM],//кольцевые буферы приема из ТУМС
BUF_OUT[skoko_stoek][SIZE_BUF_OUT], //кольцевые буферы вывода в ТУМС
REG_INFO[skoko_stoek][11],//массивы регистров сообщений из ТУМС
REG_OT[skoko_stoek][6],//массив регистров ответов для передачи в ТУМС
REG_COM_TUMS[skoko_stoek][11],//массив регистров команд для передачи в ТУМС
REG_PODT_TUMS[skoko_stoek][11]
#ifdef DISPETCHER
,//массив регистров подтверждений из ТУМС
//-------------------перемннные для обмена с ДЦ
BUF_OUT_DC[SIZE_BUF_OUT_DC],//кольцевой буфер выдачи данных для ДЦ
BUF_IN_DC[SIZE_BUF_PRIEM_DC],//кольцевой буфер приема из ДЦ
REG_INF_DC[KOL_SOO][13],//массивы регистров сообщений ТУМС для передчи в ДЦ
            //11 байт сообщение + 1 байт новизна
REG_OT_DC[6],//массив регистров ответов ДЦ для передачи в ТУМС
REG_COM_DC[11],//массив регистров команд ДЦ для передачи в ТУМС
REG_RON[11],
REG_PODT_DC[skoko_stoek][6]//массив регистров подтверждений от ТУМС для передачи в ДЦ
#endif
;
//--------------------------------------
//---------------------------------------
extern unsigned char
    IT_IS_COM_PVM,
    IT_IS_FR4,
    IT_IS_INF,
    PERED_PVM,
    REG_INF[4], BUF_INF[4],     REG_KVIT_INF[3],KVIT_INF,POVTOR_INF,
    REG_COM[11],BUF_COM_PVM[11],REG_KVIT_COM[3],KVIT_COM,POVTOR_COM,
    REG_FR4[6], BUF_FR4[6],     REG_KVIT_FR4[3],KVIT_FR4,POVTOR_FR4,
    soobs[12];

extern int UKAZ_INF,END_INF,
    UKAZ_FR4,END_FR4,
    UKAZ_COM,END_COM,
    UKAZ_KVIT_INF,END_KVIT_INF,
    UKAZ_KVIT_FR4,END_KVIT_FR4,
    UKAZ_KVIT_COM,END_KVIT_COM,
    MY_INF,MY_COM,MY_FR4,UKAZ_ZAP_OUT,UKAZ_VYVOD, UKAZ_PRIEMA_PVM;
extern unsigned char BUF_OUT_PVM[MAX_SIZE_OUT];
extern unsigned char BUF_IN_PVM[MAX_SIZE_IN];
extern unsigned char TIME[11];
//-----------------------------

#ifdef MOUSE
  extern int mouse_mark[mouse_all][3];
  extern unsigned char
  line_gor_kurs[12],
  line_vert_kurs[40],
  line_old_gor_kurs[12],
  line_old_vert_kurs[40];
#endif

//---------------------------------------------------------------------
extern unsigned char H_0,H_1,M_0,M_1;
extern unsigned int 
fr4[kol_VO][3],
ukazat[138],//массив для слов описывающих изображение указателя-курсораtrassa[100],//массив слов описания трассы для задаваемого маршрута
trassa[100],//массив слов описания трассы для задаваемого маршрута
trassa_osn[100],//массив слов описания трассы для основного маршрута
TEST,
ml_ba,
ml_bas,
st_ba,
st_bas,
ml_ba2,
st_ba2,
ml_bap,
st_bap,
ml_bab,
st_bab,
SP_STR[10][5],
COD_DN,
len,
TIMER_N[25][3];
extern unsigned char TEST_SOOB[skoko_stoek][7];
//--------------------------------
extern int  zvu_tabl[K_oo][8];
extern unsigned int cvt[K_oo][8];
extern unsigned char
buf_ko[11],
buf_ko_p[11],
buf_ko_mm[11],
buf_ko_vsp[12],
buf_zap_disk[11];
extern unsigned char bu[2][11],buf_ko_p2[11];
/**********************/
extern struct  so_so
{
  char  lex[60];
  int COlo;
};
//--------------------------------------
extern struct elem_marsh
{
  int N_sek;
  int Beg_s;
  int End_s;
  int Elems[K_EL];
}Avto_el[4];
//-----------------------------------------
extern struct skvoz_marsh
{
 int B1_s,E1_s,B2_s,E2_s;
} Skvo[4];

extern struct skv_m
{
 int B,E;
} Skv[4];
//------------------------------
#ifdef AVTOVOZVRAT
extern struct avst_
{
  int  N_sst,
      b0,
      b1,
      N_spu1,
      N_spu2,
      MSP1,
      MSP2,
      Sx,
      Sy,
      Sra,
      LU,
      Fl_kom;
} coAV[Kol_avstr];
#endif

extern struct zvuk
{
  unsigned long time_begin;
  int dlit;
  int tip;
}zvuk_sig;

extern void *f22,*saus,*qfr,*wew,*fq,*fai,*f_o;
extern union REGS regs,rg;
//extern FILE *qf,*fq;
