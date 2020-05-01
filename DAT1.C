#include "bla.h"
#include <graphics.h>
#include <stdio.h>
#include <dos.h>
//--------------------------------------
unsigned long int BAZ_ADR1,
BAZ_ADR11,
BAZ_ADR2,
BAZ_ADR3,
BAZ_ADR4,
BAZ_ADR5,
BAZ_ADR6,
to_chislo,
tormoz;
long FIR_time,
first_time,
pooo[kol_VO],
SEC_time,
second_time,
t_inf[skoko_stoek],//фиксатор времени выдачи информации в ДЦ
t_com[skoko_stoek],//фиксатор времени выдачи команды в стойку
TIME_OUT_PVM,
tii,
tiiq;
//----------------------------------------
struct dosdate_t dat;
struct so_so soob;
struct zvuk zvuk_sig={0l,0,0};
//-----------------------------------------------
int ANALIZ[skoko_stoek];
int ANALIZ_DC;
#ifdef KOL_SOO2
int old_aoar[skoko_stoek]={9999,9999};
#else
int old_aoar[skoko_stoek]={9999};
#endif
int AV_zdem;
int avap=0;
int AVARI=0;
int AVARIIN=0;
int b_h1;
int b_m1;
int b_s1;
int BAIT_PRER=0;//номер байта,на котором прервана передача
int BAM=0;
int basha=0;
int bata=0;
int bata;
int BAZA;//хендл для файла контроля базы данных
int BEDA[10];
int beg[2]={-1,-1};
int bi=0;
int bil_bil;
int bit_pso=0;
#ifdef SPDLP
int bt_spdlp[N_BIT_SCB];
int byte_spdlp[N_BIT_SCB];
#endif
int cha=0;
int chita=0;
int cikl_obnov;
int cikl_avto;
int COD_OGR;
int COD_OTPR[2];
int COD_PRIEM[2];
int COD_PS_NEW=0;
int COD_PS_OLD=0;
int COD_UCH_UDAL[2];
int CVETCVETOF=0;
int CVTF=4;
int cvv=7;
int danet;
int dayy_;
int DISK;
int down;
int DU=0;
int dv;
int DSP_SHN=15;
int ELE=0;
int END;
int end_marsh;//конец текущего маршрута
int end_avto;//конец текущего маршрута автодействия
int End_vara=0;
int FFFlag=1;
int f_ob1;
int fi_co1;
int fiki=0;
int file_arc;
int file_soob;//хендл для файла текстов сообщений
int first_col=0;
int fix_ts_sos[skoko_stoek];//индикатор фиксации состяния ТС соседа
int fix_tu_sos[skoko_stoek];//индикатор фиксации состояния ТУ соседа
int fix_rek_sos[skoko_stoek];//индикатор фиксации реконфиг. каналов соседа
int Fla_no_pp=0;
int flag_paro=0;
int FLAG_PO=0;
int flagoutmsg;
int flms=0;
int GraphDriver=VGA;
int GraphMode;
int gri=0;
int GUAV;
int half_marsh=0;
int half_marsh1;
int having;
int help;
int ho_ur;
int hod;
int hoz_poezd[2]={0,0};
int hudo=0;
int hudoo=0;
int i_s;
int i3;
int iqw;
int k;
int kadr[12][50];
int klaval;
int klo;
int ko;
int komanda2[skoko_stoek];
int konec[2];
int konec_dc;
int kot=0;
int KSK[skoko_stoek]={KS1};
int last_day=0;
int left_up_left[14];
int left_up_right[14];
int maka=0;
int maket;
int Makst=0;
int mane;
int manevr;
int manevro;
int MAR_GOT[skoko_stoek];
int marazm=0;
int marshrut[skoko_stoek][3];
int me_uk=0;
int menu_N;
int mi_n;
int misto=1;
int mlc[16];
int mls[16];
int mlu[15];
int mlv[15];
int mly[16];
int mlz[16];
int MODE_KN=0;
int modi=-1;
int modi_new;
int monn_;
int mouse_down;
int MOUSE_ON;//признак обнаружения мыши при загрузке
int mouser;
int n;
int n_1;
int n_2;
int n_m=0;
int n_ob1=0;
int n_ob2=0;
int N_OGR=0;
int n_s=0;
int na=0;
int nach_marsh;
int nach0_marsh;
int nach_avto;//начало текущего маршрута автодействия
int NE;
int NEISPRAVEN=1;
int net_kontro=0;
int nikuda;
int NM;
int NOM_NEXT=0;
int nomer;
int NOMER_ARMA=3;
int NOMER_FOR_FR4;
int notHDD=15;
int number=5555;
int new_day=0;//флаг разрешения/запрета формирования нового файла
int OB_PRER=0;//объект,на котором прервана передача
int obnov;
int okno_otkaz;
int old_me=0;
int old_modi;
int old_punkt;
int oper;
int oppp;
int opred;
int oshibka;
int osya=0;
int ot=0;
int otkaz_sos[skoko_stoek];//флаг индикации отказа ТС соседней ПЭВМ
int otkaz_tu_sos[skoko_stoek];//флаг индикации отказа ТУ соседней ПЭВМ
int otl_soob;//хранитель отложенного сообщения
int Otlog=0;
int otv_kom;
int pat;
int pauza;//пауза для торможения процедуры перерисовки экрана
int perekluch;
int perezap;
int plo;
int plu=0;
int po_ma;
int podgr=0;
int podsvetka;
int point;
int pointer;
int poka;
int povt1;
int povt1;
int povt2;
//int PREDUPR=0;
int priem_;
int PRIEM_FR4;
int PRKL=0;
int prohod_1;
int prorisovka;
int PROV_SCB;
int prv[skoko_stoek];
int punkt_N;//пункт меню, на котором находится курсор
int pust_pvm=0;
int pusto;
int puti;
int qf;//хэндл для работы с журналом состояния УВК
int R;
int r;
int right_up_left[14];
int right_up_right[14];
int ris_krest; //флаг выполнения прорисовки первой стрелки креста
int s1;
int s2;
int sbros;
int sbros1;
int schet=0;
int ScLk;//Индикатор состояния лампочки Scroll Lock на клавиатуре
int se_c;
int se_co1;
int SEZON=0;
int siv=0;
int soob_for_oper;
int spdlp;
int spa=0;
int STAT;
int STATUS=2;
int STOP=0;//признак остановки кадра для отладки каналов
int STOP_BBKP=0;//признак приостановки передачи в ДЦ
int STOP_TUMS[2]={0,0};
int str_i=20;
int strelki[5][3];
int t_koma[2];
int t_otpusk;
int t_pust[skoko_stoek];
int t_pust_dc;
int t_t=0;//флаг требования начала полной 10-минутной записи данных в архив
int TELEUP=0;
#ifdef KANALS
int TEST_KANAL;//флаг переключения АРМа в просмотр каналов
#endif
int TEST_N=0;
int timer_set;
int TORMOZ=0;
int tst;
int u;
int ukaz_ot_dc;
int ukaz_out_spd;
int ukaz_spd;
int ukaz_trass;//числовой указатель объекта в массиве trassa
int uprav=0;
int USER_FONT;
int V=0;
int vib_ma=0;
int vibeg;
int vih_vopr=0;
int vozvr;
int vrem=0;
int vspz;
int vtora;
int vvod_dc;
int vvod_set;
int vvod_tums;
int vysv;
int vysvv;
int vzvod=0;
int was[WAZO];
int X_DC=0;//коорд.X для просмотра конвертации данных ДЦ (в отладке)
int X_kan[2]={0,0};//коорд.X для просмотра принятых данных ТУМС1(2)(в отладке)
int X_m=10;
int X_m_old;
int X_time;
int xc;
int Y_DC=100;//коорд.Y для просмотра конвертации данных ДЦ (в отладке)
int Y_kan[2]={20,60};//коорд.Y для просмотра принятых данных ТУМС1(2)(в отладке)
int Y_m=10;
int Y_m_isk;
int Y_m_old;
int Y_txt=0;
int yc;
int yearr_;
int zabeg;
int zafix=0;
int ZAGRUZKA=0;
int ZAHOD=0;
int zakr=0;
int zalet;
int zapret[skoko_stoek];
int zapret_sos[skoko_stoek];
int zapret_otlad;
int zapretvybora;
int ZAPROS_FR4=0;
int zapusk;
int zdem_ps_pso=0;
int Zdem_vibor_marshruta=0;
int Zdem_vibor_opov=0;
int Zdem=0;
int ZONA_KURSORA=-1;
int zzzzx;

//------------------------------
int mas_lu[skoko_stoek][15],
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
long time_ly[skoko_stoek]={0},
time_lz[skoko_stoek]={0},
time_lc[skoko_stoek]={0},
time_ls[skoko_stoek]={0},
time_lu[skoko_stoek]={0},
time_lv[skoko_stoek]={0};

//--------------------------переменные для организации обменов ТУМС-АРМ
int ukaz_vyd[skoko_stoek];//указатели очередного байта выдачи в буфере BUF_OUT в ТУМС
int ukaz_zap[skoko_stoek];//указатели очередного байта записи данных в буфере BUF_OUT в ТУМС
int ukaz_read[skoko_stoek];//указатели очередного байта выдачи в буфере BUF_OUT в ТУМС
int ukaz_priem[skoko_stoek];//указатели очередного байта записи данных в буфере BUF_OUT в ТУМС

int N_RAZ[skoko_stoek];//счетчик числа повторений выдачи команд в ТУМС
int sboy_ts[skoko_stoek]; //счетчики сбоев канала ТС для ТУМС
int sboy_tu[skoko_stoek]; //счетчики сбоев канала ТУ для ТУМС
int otkaz_ts[skoko_stoek];//индикаторы отказа канала ТС для ТУМС
int otkaz_tu[skoko_stoek];//индикаторы отказа канала управления ТУМС
//---------------------------переменные для организации обменов АРМ-ДЦ
int ukaz_vyd_dc;//указатели очередного байта выдачи в ДЦ
int ukaz_zap_dc;//указатель очередного;байта записи из ДЦ
int ukaz_read_dc;
int ukaz_priem_dc;
int ukaz_com_dc;//указатель на активный регистр приема команд ДЦ для передачи в ТУМС
int sboy_ts_dc;//счетчик сбоев канала ТС для ДЦ
int otkaz_ts_dc;//индикатор отказа канала ТС для ДЦ
int otkaz_tu_dc;//индикатор отказа канала управления ДЦ
int dc_not_plus;

//-------------------------------------------------------
unsigned char password[8]="", //строковая переменная для ввода пароля
adr_spdlp,
str_baz[32],//строка для контроля целостности базы
BEG_TIM[20],
BUF_OUT_SPD[75],//буфер вывода для СПДЛП
chudo[20]="",
END_TIM[20],
K64, //число плат СПДЛП на 64 контакта
K32, //число плат СПДЛП на 32 контакта
LEN_SPD, //длина информационного пакета СПДЛП
NAME_FILE[17],
OBMEN_PVM,
OBMEN_PVM_OLD,
STRoka[40]="",
sbis[2]="",
soobs[12]="",
//-------------------перемннные для обмена с ТУМС
SYMBOL[skoko_stoek], //пара приемных ячеек для приема очередного символа из порта ввода
BUF_OUT[skoko_stoek][SIZE_BUF_OUT], //кольцевые буферы вывода в ТУМС
BUF_IN[skoko_stoek][SIZE_BUF_PRIEM],//кольцевые буферы приема из ТУМС
//массивы регистров сообщений из ТУМС
REG_INFO[skoko_stoek][11],
//={{0,0,0,0,0,0,0,0,0,0,0},{'(','b','F','C','@','@','Q','@','@','r',')'}},
REG_OT[skoko_stoek][6],          //массив регистров ответов для передачи в ТУМС
REG_COM_TUMS[skoko_stoek][11],   //массив регистров команд для передачи в ТУМС
REG_PODT_TUMS[skoko_stoek][11] //массив регистров подтверждений из ТУМС
#ifdef DISPETCHER
,
//-------------------перемннные для обмена с ДЦ
BUF_OUT_DC[SIZE_BUF_OUT_DC],        //кольцевой буфер выдачи данных для ДЦ
BUF_IN_DC[SIZE_BUF_PRIEM_DC],    //кольцевой буфер приема из ДЦ
REG_INF_DC[KOL_SOO][13],     //массивы регистров сообщений ТУМС для передчи в ДЦ
                             //11 байт сообщение + 1 байт новизна
REG_OT_DC[6],                   //регистр ответов ДЦ для передачи в ТУМС
REG_COM_DC[11],                  //регистр команд ДЦ для передачи в ТУМС
REG_RON[11], //регистр команд для РОН/РОЧ
REG_PODT_DC[skoko_stoek][6]                 //массив регистров подтверждений от ТУМС для передачи в ДЦ
#endif
;
//--------------------------------------

#ifdef MOUSE

  unsigned char
  line_gor_kurs[12],
  line_vert_kurs[40],
  line_old_gor_kurs[12],
  line_old_vert_kurs[40];
#endif
//------------------------------
unsigned char
  H_0,
  H_1,
  M_0,
  M_1;
//---------------------------------------------------------------------
unsigned int fr4[kol_VO][3];
unsigned int ukazat[138];//массив для слов описывающих изображение указателя-курсора
unsigned int trassa[100];//массив слов описания трассы для задаваемого маршрута
unsigned int trassa_osn[100];//массив слов описания трассы для основного маршрута
unsigned int TEST;
unsigned int ml_ba;
unsigned int ml_bas;
unsigned int st_ba;
unsigned int st_bas;
unsigned int ml_ba2;
unsigned int st_ba2;
unsigned int ml_bap;
unsigned int st_bap;
unsigned int ml_bab;
unsigned int st_bab;
unsigned int SP_STR[10][5];
unsigned int COD_DN;
unsigned int len; /* счит kol_OSN * 2 * 3 */
//--------------------------------
int zvu_tabl[K_oo][8]=
{
0, 0, 0, 0,  0,  0,  0,  0 ,  /*0*/
0, 0, 0, 0,  0,  0,  0,  0 ,  /*1*/
0, 0, 0, 0,  0,  0,  0,  0 ,  /*2*/
0, 0, 0, 0, '*','*','*','*',  /*3*/
1, 1, 1, 1, '$','$', 0,  0 ,  /*4*/
0, 0, 0, 0, '%','%','%', 0 ,  /*5*/
0, 0, 0, 0, '%', 0 ,'%', 0 ,  /*6*/
0, 0, 0, 0, '%', 0 ,'%', 0 ,  /*7*/
1, 0, 1, 0, '@', 0 ,'@', 0 ,  /*8*/
0, 0, 0, 0,  0 , 0 , 0 , 0 ,  /*9*/
0, 0, 0, 0, '@','@','@','@',  /*10*/
0, 1, 0, 0,  0 ,'@','@', 0 ,  /*11*/
0, 0, 0, 0,  0 , 0 , 0 , 0 ,  /*12*/
0, 0, 0, 0, '%','%','%','%',  /* неиспр пит*/
1, 1, 1, 0, '%','%','%', 0 ,  /*14*/
0, 0, 0, 0, '%','%','%', 0 ,  /*15*/
1, 1, 1, 1, '%','%','%','%',  /*16*/
0, 0, 0, 0, '%','%','%', 0 ,  /*17*/
0, 0, 0, 0, '%','%', 0 , 0 ,  /*18*/
0, 0, 0, 0, '%','%','%', 0 ,  /*19*/
0, 1, 0, 0,  0, '%', 0,  0 ,  /*20*/
0, 0, 0, 0, '#', 0 , 0 , 0 ,  /*21*/
0, 1, 0, 0,  0 ,'@', 0 , 0 ,  /*22*/
0, 0, 0, 0,  0 , 0 , 0 , 0 ,  /*23*/
0, 0, 0, 0,  0 , 0 , 0 , 0 ,  /*24*/
1, 1,216,0, '%','%','$', 0 ,  /*25*/
0, 0, 0, 0,  0 , 0 , 0 , 0 ,  /*26*/
0, 1, 1, 0,  0 ,'$','$', 0 ,  /*27*/
0, 1, 1, 1, '$','@','@','$',  //28
0, 1, 1, 0,  0, '@','@', 0 ,  //29
0, 0, 0, 0,  0,  0,  0,  0,   //30
0, 0, 0, 0,  0,  0,  0,  0,   //31
1, 1, 1, 0, '%','%','%', 0,   //32
0, 1, 0, 1, '$','@','$','@',  //33
0, 0, 0, 0,  0,  0,  0,'$',   //34
0, 1, 1, 1, '$', '%','%','%',  //35
0, 0, 0, 0, '$','$', 0,  0,   //36
0, 0, 0, 0, '$', 0,  0,  0,   //37
0, 0, 0, 0, '$','%','%','%',  //38
0, 0, 0, 0,  0,  0, '$', 0,   //39
1, 1, 1, 1, '@','@','@','@',   //40
};

unsigned int cvt[K_oo][8]=
{
  8, 4, 8, 4,0, 0,0, 0,       //0 без звука и без записей
 10, 4, 0, 0,0, 0,0, 0,       /*1*/
  0, 0, 8, 4,0, 0,0, 0,       /*2*/
  0,15, 0,15,0,15,0,15,       /*3*/
  8, 4, 8, 4,8, 4,0, 0,       //4 со звуком на все
  8, 4, 8, 4,8, 4,7, 7,       /*5*/
  8, 4, 8, 4,8, 4,8, 4,       //6 без звуков, с записью 0-го и 2-го
  8,14, 8, 4,8, 4,8, 4,       /*7*/
  8,14,10,15,8,14,8,14,       /*8*/
  8,10, 8,10,8,10,8,10,       /*9*/
  7,15, 7,15,7,15,7,15,       /*10*/
0x8a88,0x8a88,0x88c8,0x888c,0xc88d,0xdede,0, 0, //11
  8, 4, 8,10,8,14,0, 0,       /*12*/
  8, 4, 8, 4,8, 4,8, 4,       //13 без звука с записью всех
  8,14, 8,14,8,14,8,14,       /*14*/
  8, 4, 8, 4,8, 4,0, 0,       //15 без звука с записью всех
  8, 4, 8, 4,8, 4,8, 4,       //16 со звуком на все
 10,14, 8, 4,8, 4,8, 4,       /*17*/
	4, 7,10,10,8, 8,8, 8,       /*18*/
  8, 4, 8, 4,0, 0,0, 0,       /*19*/
  8, 4, 8, 4,8, 4,8, 4,       //20 со звуками на 0-й и 2-ой
  8, 4, 8, 4,7, 7,7, 7,       /*21*/
  8,12, 8,12,8,12,8,12,       /*22*/
  7,14, 7,14,7,14,7,14,       /*23*/
 10,14, 0, 0,0, 0,0, 0,       /*24*/
  8,12, 8,12,8,12,0, 0,       /*25*/
  8,14, 8,14,8,14,8,14,       /*26*/
  8, 4, 8,10,8,14,0, 0,       /*27*/
  8, 4, 7, 7,7, 7,7, 7,       /*28*/
0x87,0xda,0x87,0xda,0x87,0xda,0x87,0xda,//29
  8,14,12,12,0, 0,0, 0,       //30
  8,13, 7,10,0, 0,0, 0,       //31
  8,12, 9,13,0, 0,0, 0,       //32
 14,10,13,13,0, 0,0, 0,       //33
  8,14,13,13,0, 0,0, 0,       //34
  8,12,14,12,0, 0,0, 0,       //35
  7,15, 7,15,7,15,7,15,       //36
  8, 4, 8,10,8,14,0, 0,       //37
  8, 4, 8, 4,8, 4,8, 4,       //38
  8,14, 8,10,0, 0,0, 0,       //39
 10, 8, 8, 4,8, 4,0, 0,       //40
};
unsigned char
buf_ko[11],
buf_ko_p[11],
buf_ko_mm[11],
buf_ko_vsp[12],
buf_zap_disk[11];
/**********************/
unsigned char bu[2][11],buf_ko_p2[11];
unsigned char TIME[11];



union REGS regs,rg;

unsigned int TIMER_N[25][3];// Блок из 25 таймеров по 3 слов
               // 1-номер объекта,
               // 3-тип объекта 
               // 4-номер подобъекта инициализации 
unsigned char TEST_SOOB[skoko_stoek][7];

//---------------------------------------
unsigned char
    IT_IS_COM_PVM=0,
    IT_IS_FR4=0,
    IT_IS_INF=0,
    PERED_PVM=2,
    REG_INF[4], BUF_INF[4],     REG_KVIT_INF[3],KVIT_INF,POVTOR_INF,
    REG_COM[11],BUF_COM_PVM[11],REG_KVIT_COM[3],KVIT_COM,POVTOR_COM,
    REG_FR4[6], BUF_FR4[6],     REG_KVIT_FR4[3],KVIT_FR4,POVTOR_FR4;

int UKAZ_INF=0,END_INF=0,
    UKAZ_FR4=0,END_FR4=0,
    UKAZ_COM=0,END_COM=0,
    UKAZ_KVIT_INF=0,END_KVIT_INF=0,
    UKAZ_KVIT_FR4=0,END_KVIT_FR4=0,
    UKAZ_KVIT_COM=0,END_KVIT_COM=0,
    MY_INF,MY_COM,MY_FR4,UKAZ_ZAP_OUT,UKAZ_VYVOD, UKAZ_PRIEMA_PVM;
unsigned char BUF_OUT_PVM[MAX_SIZE_OUT];
unsigned char BUF_IN_PVM[MAX_SIZE_IN];
unsigned char D_kont[1][9]={'p','q','r','s','t','u','v','w','x'};
//-----------------------------
unsigned char bu[2][11],buf_ko_p2[11];

