#include "bla.h"
#include <stdlib.h>
#include <stdio.h>
#include <alloc.h>
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <bios.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
int ioy=0;
int all_null(int nom)
{
  int iqc,vot_on=0;

	nom_func("4");

  vot_on=markery[nom][6];
  for(iqc=Start_R;iqc<Start_R+WAZO;iqc++)
  if((vot_on!=iqc)&&(fr3[iqc][0]==1))return(1);
return(0);
}
//-----------------------------------------------
void analiz_time()
{
  int i,obekt,j,tip,tek,sled;
  long tim,tt;

	nom_func("9");

  tim=biostime(0,0l);
  for(i=0;i<25;i++)
  {
    if(TIMER_N[i][0]!=0)//если обнаружен включенный таймер
    {
      obekt = TIMER_N[i][0]; // взять номер объекта,для которого запущен таймер seg020:00E3  
      tip = TIMER_N[i][1];
      if(((tim-pooo[obekt]) > 70L)||(tip == 22)||
      (tip == 21)||(tip == 3))// если время ожидания вышло
      switch(tip)  //---------- seg020:0121 loc_50961:
      {
        case 30:  tt = tim-pooo[obekt];
                  if(tt > 360L)
                  {
                    if(pooo[obekt]!=0l)
                    {
                      zvuk_vkl(1,9l);
                      w(239,obekt," НЕ ИСПОЛНЕНА");
                    }
                    TIMER_N[i][0]=0;
                    TIMER_N[i][1]=0;
                    TIMER_N[i][2]=0;
                    pooo[obekt]=0l;
                  }
                  break;
        case 1: // если тип - аварийный перевод стрелок
                tt = tim - pooo[obekt];
                if(tt > 360)// если время ожидания вышло
                {
                  AVARI = 0;  //------------ seg020:0249 
									avap=0;
                  AVARIIN=0;
                  pooo[AVAch]=0l;
                  pooo[AVAn]=0l;
                  vkl_kno(AViA,8);
                  vibeg=0;
                  vib_ma=0;
                  AV_zdem=0;
                  oper=0;
                  zvuk_vkl(1,20);
                  t(0);
                  w(220,obekt," ВРЕМЯ ИСТЕКЛО");
                  TIMER_N[i][0]=0;
                  TIMER_N[i][1]=0;
                  TIMER_N[i][2]=0;
                }
                break;
        case 2: // если тип - анализ исправности огневых пригласительных
						if(pooo[obekt]!=0)
						{
							tt=tim-pooo[obekt];
							if(tt>36L)// хёыш тЁхь  юцшфрэш  т√°ыю
							{
								obekt=TIMER_N[i][0];
								ps_pso(obekt,5);
								pooo[TIMER_N[i][0]]=0l;
							}
						}
						if(pooo[obekt]==0)
						{
							TIMER_N[i][0]=0;
							TIMER_N[i][1]=0;
							TIMER_N[i][2]=0;
						}
						break;

        case 3: // если тип - анализ исправности огневых входных соседа
                tt=tim-pooo[obekt];
                if(tt>36L)// если время ожидания вышло
                {

                  obekt=TIMER_N[i][0];
                  lru_lko(obekt,TIMER_N[i][2],5);
                  pooo[TIMER_N[i][0]]=0l;
                  TIMER_N[i][0]=0;
                  TIMER_N[i][1]=0;
                  TIMER_N[i][2]=0;
                }
                break;

       case 21://если работаем с комплексной лампой
                //не открывается > 2с
                tt=tim-pooo[obekt];
                if(tt>36L)
                {
                  lampa_3c(obekt,TIMER_N[i][2],1);
                  TIMER_N[i][0]=0;
                  TIMER_N[i][1]=0;
                  TIMER_N[i][2]=0;
                  pooo[obekt]=0l;
                }
                break;

         case 66://если работаем с переездом
                //не открывается > 2с
                tt=tim-pooo[obekt];
                if(tt>170L)
                {
                  pooo[obekt]=0l;home(modi);
                  pooo[obekt]=0l;
                  TIMER_N[i][0]=0;
                  TIMER_N[i][1]=0;
                  TIMER_N[i][2]=0;
                  t(0);
                  flagoutmsg=0;
                }
                break;

        case 18:tt=tim-pooo[obekt];
                if(tt>36L)
                {
                  ognev(obekt,TIMER_N[i][2],5);
                  TIMER_N[i][0]=0;
                  TIMER_N[i][1]=0;
                  TIMER_N[i][2]=0;
                  pooo[obekt]=0l;
                }
                break;

        case 22: //таймер для перевода стрелок в другой стойке
                  point=TIMER_N[i][0];
                  pooo[point]=biostime(0,0l);
                  oper=fr3[point][7];
                  fr3[point][7]=0;
                  TIMER_N[i][0]=0;
                  TIMER_N[i][1]=0;
                  TIMER_N[i][2]=0;
                  formkps(oper);//сформировать команду на перевод стрелки
                  flagoutmsg=1;
                  break;
#ifdef OGRAD
        case  46:         // если тип=ограждение
                  tt=tim-pooo[obekt];
                  if(tt>70L)// если время ожидания вышло
                  {
                    analiz_ogr(TIMER_N[i][2],0);// выполнить анализ состояния
                    pooo[obekt]=0l;
                    TIMER_N[i][0]=0;
                    TIMER_N[i][1]=0;
                    TIMER_N[i][2]=0;
                  }
                  break;
#endif
#ifdef POLUAVTOMAT
        case 51:  // если тип=полуавтоматика-отправление
                  tt=tim-pooo[obekt];
                  if(tt>70L)// если время ожидания вышло
                  {
                    analiz_otprav(TIMER_N[i][0],0);// выполнить анализ состояния
                  }
                  break;
        case 52:          // если тип=полуавтоматика-прием
                  tt=tim-pooo[obekt];
                  if(tt>70L)// если время ожидания вышло
                  {
                    analiz_priem(TIMER_N[i][0],0);// выполнить анализ состояния
                  }
                  break;

#endif
        default:  break;
      }
      if(tip==22)break;
    }
cikl:
  }

  for(i=0;i<skoko_stoek;i++)
  {
    j=0;
    if(komanda2[i]!=0)
    {
      tt=tim-pooo[komanda2[i]];
			if(tt>1400)//если прошло более 80 сек
      {
        tek=komanda2[i];
        while(1)
        {
          sled=fr3[tek][8]&0xfff;
					if((fr3[tek][10]==0)&&(fr3[8]==0))break;
          fr3[tek][8]=0;
          fr3[tek][10]=0;
          if(sled==0xfff)break;
          tek=sled;
        }
        komanda2[i]=0;
        if(marshrut[i-1][0]!=0)
        {
          marshrut[i-1][0]=0;
          marshrut[i-1][1]=0;
          marshrut[i-1][2]=0;
        }
      }
    }
    for(j=0;j<5;j++)
    {
      if((strelki[i][0]!=0)&&(pooo[strelki[i][0]]!=0))
      {
        if((biostime(0,0l)-pooo[strelki[i][0]])>740)
        {
          pooo[strelki[i][0]]=0l;
          strelki[j][0]=0;
          strelki[j][1]=0;
          strelki[j][2]=0;
          w(21,999,"(не установлены стрелки)");
        }
      }
    }
  }
  if((komanda2[0]==0)&&(komanda2[1]==0)&&(vozvr==0))
  if((marshrut[0][0]==0)&&(marshrut[1][0]==0))
  for(i=0;i<kol_VO;i++)
  if(fr3[i][10]!=0){fr3[i][10]=0;fr3[i][8]=0;}
}
//---------------------------------------------------------------

void dn_au(int nom)
{
  int ob_au,ob_dn,ob_nn,bit_au,bit_nn,bit_dn;
  ob_nn=fr1[nom][3];bit_nn=fr1[nom][4];
  ob_dn=fr1[nom][5];bit_dn=fr1[nom][6];
  ob_au=fr1[nom][9];bit_au=fr1[nom][10];
  
	nom_func("43");
  
  if(klaval==13)
  { ob_nn=fr1[nom][3];bit_nn=fr1[nom][4];
    ob_dn=fr1[nom][5];bit_dn=fr1[nom][6];
    ob_au=fr1[nom][9];bit_au=fr1[nom][10];
    if(ob_au!=9999)//если есть кнопка "автомат"
    { if(nom==ob_au)//если нажата кнопка "автомат"
      { if(COD_DN>7)
        //автоматический режим уже установлен
        { w(202,999,"");return;}
        //посылаем команду установить режим "автомат"?
        else  w(206,999,"");
      }
    }
    if((nom==ob_nn)||(nom==ob_dn))//если нажата кнопка режима
    { //посылаем команду включить дневной режим
      if((COD_DN==2)||(COD_DN==3)||(COD_DN==8)){w(207,999,"");nom=ob_dn;}
      else
        //посылаем команду включить ночной режим
        if((COD_DN==4)||(COD_DN==5)||(COD_DN==9)){w(208,999,"");nom=ob_nn;}
        //НЕИСПРАВНА СХЕМА ПЕРЕКЛЮЧЕНИЯ РЕЖИМОВ СИГНАЛОВ
        else {w(209,999,"");return;}
		}
		oppp=0; puti=0;
		if(nom==ob_nn)nom=ob_dn;
		else
			if(nom==ob_dn)nom=ob_nn;
		form_kom_knopka(nom,0);
		home(modi);
		return;
	}
	else return;
}
//--------------------------------------------------------------
void first_razd(int nom)
{ //команда включения разделки объекта nom типа РИ, выдается дважды
  //в качестве предварительной и исполнительной
  int nomer,podgr,n,i17,j17,SDVIG=0,FN=0,FIN=0;
  
	nom_func("62");
    
  buf_ko[2]='F'; //сформировать код группы для РИ-объекта
  n=markery[nom][6];//получить номер в базе для выбранного маркером
  if(fr1[n][13]==1)//для объекта из первой стойки
  {
    buf_ko[1]=ZAGO_MPSU(0x61);//записать заголовок
    SDVIG=STR1+SIG1; //получить смещение на СП и РИ
    FN=0;
    FIN=UCH1;//получить конец для объектов СП и РИ
  }
#ifdef KOL_SOO2
  else
  {
    buf_ko[1]=ZAGO_MPSU(0x62);//то же для второй стойки
    SDVIG=STR2+SIG2;
    FN=UCH1;
    FIN=FN+UCH2;
  }
#endif
  nomer=9999; //начать поиск объекта
  for (i17=FN;i17<FIN;i17++) //пройти по подгруппам группы СП+РИ
  for(j17=0;j17<=4;j17++)//пройти по объектам каждой подгруппы
  if (spspu[i17][j17]==n)//если объект найден
  {
		podgr=podgruppa[i17+SDVIG-FN];//получить код подгруппы
		nomer=j17; //запомнить порядковый номер объекта в подгруппе
		break;
	}
	if(nomer==9999) return;//если объект не найден - выход
	buf_ko[3]=podgr;//для найденного объекта записать код подгруппы
	for (i17=0;i17<=4;i17++)
	if (i17==nomer) buf_ko[i17+4]='T';//буква 'T'для байта, соответствующего объекта
	else buf_ko[i17+4]=124; //для прочих объектов - |
	buf_ko[9]=check_sum(buf_ko);//записать контрольную сумму
	pooo[n]=biostime(0,0L);//включить таймер на разделку данного элемента
	fr3[n][9]=9;//установить флаг включенного таймера
	flagoutmsg=1;//выставить требование передачи в ТУМС
}
//--------------------------------------------------------

void form_first_kom(int nom)
{ //процедура формирования предварительной команды для вспомогательной
	//смены направления
	int nomer,podgr,kodd=0,n,i18,j18,SDVIG=0,FN=0,FIN=0;

	nom_func("71");

	if(zapusk!=3)w(11,999,"");//ПОСЫЛАЕМ ПРЕДВАРИТЕЛЬНУЮ КОМАНДУ
	buf_ko[2]='E'; //заполнить код группы
	n=markery[nom][6];//получить номер выбранного маркером объекта для базы
	if(fr1[n][13]==1)//если объект из первой стойки
	{
		buf_ko[1]=ZAGO_MPSU(0x61);//заполнить заголовок
		SDVIG=STR1;FN=0;FIN=SIG1;//получить смещение и границу для сигналов
	}
#ifdef KOL_SOO2
  else
  {
    buf_ko[1]=ZAGO_MPSU(0x62);//аналогичные действия для второй стойки
    SDVIG=STR2;FN=SIG1;FIN=FN+SIG2;
  }
#endif
  //если предварительная команда
  if((fr1[n][1]==31)&&(zapusk==1))n=fr1[n][2];
  nomer=9999;
  for (i18=FN;i18<FIN;i18++)//пройти по подгруппам
  {
    for(j18=0;j18<=4;j18++)//пройти по объектам подгрупп
    if (spsig[i18][j18]==n)//если найден нужный объект
    {
			podgr=podgruppa[i18+SDVIG-FN];//запомнить подгруппу
      nomer=j18;//запомнить порядковый номер в подгруппе для объекта
      break;
    }
    if(nomer!=9999)break;
  }
  if(nomer==9999) return;//если объект не найден - выйти
  buf_ko[3]=podgr;//для найденного объекта заполнить группу
#ifdef VSP
  for(i18=0;i18<VSP;i18++)
  if(mark[i18][0]==nom)
  if(mark[i18][1]==1) priem_=1;
  else priem_=-1;
  if(i18>VSP) return;
  if(priem_==1) kodd='X';//установить для приема свой код команды
  else
    if(priem_==-1) kodd='T';//для отправления - свой код команды
    else return;
#endif
  if((fr1[n][1]==30)||(fr1[n][1]==31))kodd='T';
  for(j18=0;j18<=4;j18++)
  if(j18==nomer) buf_ko[j18+4]=kodd;//для найденного объекта - записать код
  else  buf_ko[j18+4]=124;//для прочих объектов - записать заполнитель
  buf_ko[9]=check_sum(buf_ko);//дополнить команду контрольной суммой
  pooo[n]=biostime(0,0L);//зафиксировать время выдачи команды
  fr3[n][9]=9;//установить признак выдачи предварительной команды 
  zapretvybora=1;
  flagoutmsg=1;//выставить флаг требования передачи команды в ТУМС
  vtora=1;//установить признак ожидания исполнительной команды
}

//------------------------------------------------------------------
#ifdef VSP
void form_second_kom(int nom)
{ //процедура формирования исполнительной команды для вспомогательной смены
  //направления
  int n,nomer,podgr,kodd=0,SDVIG=0,FN=0,FIN=0,i18,j18;
  buf_ko[2]='E'; //заполнить код группы
  n=markery[nom][6]-1;//сместиться на полуобъект
  if(fr1[n][13]==1)//если для первой стойки
  {
    buf_ko[1]=ZAGO_MPSU(0x61);//заполнить заголовок
    SDVIG=STR1;FN=0;FIN=SIG1;//получить необходимый сдвиг и границу
  }
#ifdef KOL_SOO2
  else// если вторая стойка, то для нее - то же самое
  {
    buf_ko[1]=ZAGO_MPSU(0x62);
    SDVIG=STR2;FN=SIG1;FIN=FN+SIG2;
  }
#endif
  nomer=9999;
  for (i18=FN;i18<FIN;i18++)//пройти по подгруппам
  for(j18=0;j18<=4;j18++)//пройти по объектам в подгруппе
  if (spsig[i18][j18]==n)//если найден объект
  {
    podgr=podgruppa[i18+SDVIG-FN];//запомнить подгруппу
    nomer=j18;//запомнить порядковый номер объекта
    break;
  }
  if(nomer==9999) return;//если объект не найден - выход
  buf_ko[3]=podgr;//заполнить подгруппу
  for(i18=0;i18<VSP;i18++)
	if(mark[i18][0]==nom)
  if(mark[i18][1]==1) priem_=1;
  else priem_=-1;
  if(i18>VSP) return;
  if(priem_==1) kodd='X';//заполнить код для приема
  else
    if(priem_==-1) kodd='T';//или заполнить код для отправления
    else return;
  for(j18=0;j18<=4;j18++)
  if(j18==nomer) buf_ko[j18+4]=kodd;//для найденного объекта записать команду
  else  buf_ko[j18+4]=124;  //для остальных объектов - заполнитель
  buf_ko[9]=check_sum(buf_ko);//добавить контрольную сумму
  pooo[n]=biostime(0,0L);//зафиксировать время
  fr3[n][9]=9;//установить признак выдачи команды
  flagoutmsg=1;//установить флаг-требование на передачу в ТУМС
  zapretvybora=0;
  priem_=0;//сбросить признак вспомогательного приема/отправления
}
#endif
//---------------------------------------------------------------
void gri_razd(int nom)
{ // формирует команду для включения выдержки времени
	//на выполнение искусственной разделки
	int nomer,podgr,n,i17,j17,SDVIG=0,FN=0,FIN=0;

	nom_func("100");

	buf_ko[2]='F';//заполнить группу
	n=markery[nom][6];//получить объект
	if(fr1[n][13]==1)//для стойки №1 получить заголовок, сдвиг и границы
	{
    buf_ko[1]=ZAGO_MPSU(0x61);
    SDVIG=STR1+SIG1;FN=0;FIN=UCH1;
  }
#ifdef KOL_SOO2
  else //то же самое для второй стойки
  {
    buf_ko[1]=ZAGO_MPSU(0x62);
    SDVIG=STR2+SIG2;FN=UCH1;FIN=FN+UCH2;
  }
#endif
  nomer=9999;
  for (i17=FN;i17<FIN;i17++)//пройти по подгруппам
  for(j17=0;j17<=4;j17++)//пройти по объектам подгруппы
  if (spspu[i17][j17]==n)//если объект найден
  {
    podgr=podgruppa[i17+SDVIG-FN];//зафиксировать подгруппу
    nomer=j17;//зафиксировать номер в подгруппе
    break;
  }
	if(nomer==9999) return;//если объект не найден - выход
	buf_ko[3]=podgr;//заполнить подгруппу
	for (i17=0;i17<=4;i17++)
	if (i17==nomer) buf_ko[i17+4]='L'; //для выбранного объекта записать команду
	else buf_ko[i17+4]=124; //для прочих объектов записать заполнитель
	buf_ko[9]=check_sum(buf_ko);//дополнить команду контрольной суммой
	pooo[n]=biostime(0,0L);//зафиксировать время
	fr3[n][9]=9;//запомнить факт выдачи команды
	flagoutmsg=1;//установить запрос на передачу в ТУМС
}
//------------------------------------------------------
void k_per(int nom)
{ 
  
	nom_func("113");
        
  if (klaval==13)
  { //ПОСЫЛАЕМ КОМАНДУ НА ОТКРЫТИЕ ПЕРЕЕЗДА
    if((fr3[nom][0]==1)&&(fr3[nom+1][1]==1))w(24,999,"");
    else  w(25,999,"");//ПОСЫЛАЕМ КОМАНДУ НА ЗАКРЫТИЕ ПЕРЕЕЗДА
    oppp=0;puti=0;
    zp_zp(nom);
    return;
  }
  return;
}
//------------------------------------------------------
void knopa(int nom)
{ unsigned int coox,cooy,//координаты
	bit,//бит воздействия на включение
	ob_akt,//объект навязывания состояния (возможно вопреки объекту управления)
	bit_akt,//бит навязывания состояния
	zn_akt,//значение активного состояния навязывающего бита
	ob_vkl,//объект включения
	ob_otkl,//объект отключения
	bit_otkl,//бит отключения
	so1,//сообщение на включение
	so2,//сообщение на отключение
	inv,//признак необходимости инвертировать команду
	i;

	nom_func("121");
          
  if(klaval==13)
  {
    if(fr1[nom][1]!=166)
    { bit=fr1[nom][11];ob_vkl=nom;ob_otkl=nom;
      so1=fr1[nom][3];so2=fr1[nom][4];
      inv=0;
    }
    else
    { bit=(fr1[nom][3]&0xf000)>>12;
      ob_vkl=fr1[nom][3]&0xfff;
      ob_otkl=fr1[nom][4]&0xfff;
      bit_otkl=(fr1[nom][4]&0xf000)>>12;
      so1=fr1[nom][8];
      so2=fr1[nom][9];
		}
    if((fr1[nom][7]!=9999)&&(fr1[nom][2]!=33)&&(fr1[nom][1]!=166))
    {
     ob_akt=fr1[nom][7]>>4; bit_akt=(fr1[nom][7]&0xf)>>1;
     zn_akt=fr1[nom][7]&1;
     if(fr3[ob_akt][bit_akt]!=zn_akt){ w(229,ob_akt,"!"); goto out; }
    }
    if(fr3[nom][bit]==1)w(so2,999,"");
    else
      if(fr3[nom][bit]==0) w(so1,999,"");
    if(fr1[nom][2]!=0)//если кнопка обычная
    {
      if(fr1[nom][1]==166)
      {
        if(fr3[ob_vkl][bit]==0){nom=ob_vkl;inv=0;}
        if(fr3[ob_vkl][bit]==1){nom=ob_otkl;inv=1;}
      }
      form_kom_knopka(nom,inv);
    }
out:
    oppp=0;puti=0;
    home(modi);
    return;
  }
  else return;
}
//------------------------------------------------------------------
void knopka_OK()
{
	int goj=0;

	nom_func("123");
          
  if(pusto==0)
  {
    if(otv_kom==0) setcolor(8);// если нет нажатия кнопки ОК - цвет серый 
    else setcolor(RED);  // иначе(когда нажатие) - цвет красный 
//  goto ris;
  }
  if(otv_kom==1)// если есть нажатие ОК
  {
    sbros_all();
    klaval=0;
    if((nikuda==0)&&(klo==0)&&(help==0))
    {
      t(0);
      if(perekluch==0)
      if(vspz==1) home(pat);
      else
      if(modi!=-1) home(modi);
      else  home(i3);
    }
    po_ma=0;vspz=0;zzzzx=0;first_col=0;u=0;modi=-1;
    finish_strelok();
    for(ukaz_trass=0;ukaz_trass<100;ukaz_trass++)trassa[ukaz_trass]=0xFFFF;
    whole_finish();
    finish_strelok();
		povt1=povt2=poka=vozvr=0;
    flagoutmsg=0;
    setcolor(RED);
  }
  else // если нет нажатия кнопки ОК
  {
    if((nikuda==0)&&(klo==0)&&(help==0))
    {
      if(perekluch==0)
      if(modi!=-1)
      { //если был выбран объект ГРИ 
        if(gri==1){gri=0;fr3[markery[modi][6]][9]=0;}
        if(zalet!=0)
        { was[markery[modi][7]-10]=0;
          fr3[markery[modi][6]][9]=0;
          vtora=0;
          flagoutmsg=0;
        }
        if(zabeg!=0){fr3[markery[modi][6]][9]=0;vtora=0;flagoutmsg=0;}
        home(modi);
      }
      else home(pat);
      setcolor(8);
    }
    u=0;
    modi=-1;
    zzzzx=0;
    if(perekluch==0)
    { if(zalet!=0) zalet=0;
      if(zabeg!=0) zabeg=0;
			 t_otpusk=biostime(0,0L);//зафиксировать время отпускания кнопки
		}
	}
	if((klo==1)||(help!=0)||(nikuda==1))return;
	if((pusto&3)!=0) setcolor(LIGHTCYAN);
ris:
	setlinestyle(0,0,0);
	setfillstyle(0,0);
	for(goj=6;goj>0;goj--)circle(XOK,YOK,goj);// нарисовать кнопку
	if(hudo==1)
	{
		setcolor(cvv);
		for(goj=0;goj<=5;goj++)circle(XOK,YOK,goj);
	}
}
//------------------------------------------------------
void kom_per(int pop)
{
  
	nom_func("126");
         
  if((nikuda==1)||(klo==1)||(help!=0)) return;
  if((fr3[pop][0]==1)&&(fr3[pop+1][1]==1))w(23,999,"");//ОТКРЫТЬ ПЕРЕЕЗД?
  else w(22,999,"");//ЗАКРЫТЬ ПЕРЕЕЗД?
  oppp=1;
  puti=1;
}
//---------------------------------------------------------
void marsh1()
{ //программа трассировки маршрута по топологии станции и проверка достижимости
	int i,nop,sm,test_marsh,vm=0,otvet,obekt2;

	nom_func("164");

	// если нажимается первая точка, запоминаем начало маршрута
	if(povt1==0)
	{
		nop=fr1[nach_marsh][1];//фиксируем направление сигнала
		if(nop==0) sm=1;//по направлению выбираем шаг смещения
		else sm=-1;
	}
	if(poka==0)
	{ for (i=0;i<kol_OSN;i++)fr3[i][6]=0;//для основных объектов - сброс вспомогательного слова
		if(mane==0)
		{
			if((fr1[markery[modi][6]][2]==0)&&//если сигнал маневровый и
			(fr1[markery[modi][6]][6]==0))    // и светофор маневровый
      mane=1;// установить признак маневрового маршрута
      else
        if(manevro==1) mane=1;//если маршрут маневровый  установить признак
        else mane=0;//для поездного сбросить признак
    }
    if(fr1[markery[modi][6]][0]!=2) return;//если выбран не сигнал - выход
    else //если выбран сигнал
    { povt1=1;//зафиксировать факт нажатия
      ko=markery[modi][6];//запомнить объект управления
      if(fr1[markery[modi][6]][6]==3&&mane==0)ko++; //если 2 белых - сместиться
    }
		if(povt2==0)//если второй сигнал не выбран
    { nach_marsh=ko;//присвоить началу маршрута значение выбранного сигнала
      n_m=modi;//запомнить объект управления
      povt2=1;//зафиксировать
      poka=1;
      koni();
      return;
    }
    else  poka=0;
  }
  NM=fra[nach_marsh][0];//взять строку для начала маршрута
  END=find_end();//найти конец маршрута
  if(END==9999)//если конец не найден
  {ioy=1;goto nn;}
  NE=fra[END][0];//взять строку для конца маршрута
#ifdef KOL_SOO2
  if(fr1[nach_marsh][13]!=fr1[end_marsh][13])//если границы маршрута в разных стойках
  {
    for(vm=0;vm<4;vm++)//пройти по сквозным маршрутам
    if(nach_marsh==Skv[vm].B&&end_marsh==Skv[vm].E)break;//найти начало и конец
    if(vm>=4){ioy=1;goto not;}//если нет такого сквозного маршрута
  }
#endif
  if((fr1[nach_marsh][3]==7)&&(fr1[end_marsh][3]==7))//если сквозной
  if(fra[nach_marsh][0]!=fra[end_marsh][0]){ioy=1;goto not;}
  if(nach_marsh==end_marsh)//если конец и начало на одном сигнале
  { ioy=1;goto not;}
  if((nach_marsh-end_marsh==1)||(nach_marsh-end_marsh==-1))//если начало-конец рядом
  { ioy=1; goto not;}
  ZAHOD=0;TEST=1;//устанавливаем признак поиска эталонного маршрута
	test_marsh=may_be(nach_marsh,fr1[nach_marsh][1]);//создать эталон
  ukaz_trass=0;
  while(trassa_osn[ukaz_trass]!=0xFFFF)//очистить указатели заходов и поворотов
  { if((fr3[trassa_osn[ukaz_trass]][8]!=0))
    { t(0);
      w(238,trassa_osn[ukaz_trass],"");//УСТАНОВЛЕНО ПРЕДВАРИТЕЛЬНОЕ ЗАМЫКАНИЕ
      goto not;
    }
    fr3[trassa_osn[ukaz_trass]][6]=0;
    fr3[trassa_osn[ukaz_trass]][10]=0;ukaz_trass++;
  }
  if(test_marsh==2)return(1);
  ZAHOD=0;TEST=0;//установить признак поиска задаваемого маршрута
  ioy=may_be(nach_marsh,fr1[nach_marsh][1]);//проверить достижимость по топологии
  ukaz_trass=0;//встать в начало трассы
  if(ioy==0)//если трасса найдена
  {
    while(trassa[ukaz_trass]!=0xFFFF)//пройти по всем элементам найденного маршрута
    { if(fr1[trassa[ukaz_trass]][0]==1)
        plus_minus();//для стрелок установить признаки желаемого положения
      fr3[trassa[ukaz_trass]][10]=fr3[trassa[ukaz_trass]][10]|1;
      otvet=test_elem(trassa[ukaz_trass]&0x7FFF,0);
      if(otvet==1)
      goto not;//если есть причины отказ от маршрута
      if((manevr==1)||(mane==1))//если маршрут маневровый
      { if(trassa[ukaz_trass]!=END&&//если объект не является концом и
        trassa[ukaz_trass-1]!=0xFFFF)//трасса не закончена
        if(fr1[trassa[ukaz_trass]][0]==5)//если объект=путь
        {
          w(100,999,"");/*НЕВОЗМОЖЕН МАНЕВРОВЫЙ МАРШРУТ ЧЕРЕЗ ПУТЬ*/
					ioy=2;//установить признак выхода на путь
          goto not;
        }
      }
      ukaz_trass++;//перейти на следующий объект
    }
    ukaz_trass=0;
    while(trassa[ukaz_trass++]!=end_marsh)
    {
      if((trassa[ukaz_trass]&0xfff)!=(trassa_osn[ukaz_trass]&0xfff))break;
    }
    if(trassa[ukaz_trass]==trassa_osn[ukaz_trass]){half_marsh=0;nach0_marsh=0;}
    if(prov_avail()==1)
    {
      w(134,999,"");//ТОЧКА КОНЦА МАРШРУТА УКАЗАНА НЕВЕРНО
      home(modi);
      soob_for_oper=1;
      sbros=1;
      whole_finish();
      ukaz_trass=0;
      while(trassa[ukaz_trass]!=0xffff)
      {
        fr3[trassa[ukaz_trass]&0x7FFF][10]=0;
        trassa[ukaz_trass++]=0xFFFF;
      }
      return;
    }
    ris_trassa();
    voper();
  }
	else//если трасса не найдена
	{
not:
		finish_startMM(); //закончить работу с трассой
nn: if(ioy==1)//если "плохой" конец
		w(134,999,""); //ТОЧКА КОНЦА МАРШРУТА УКАЗАНА НЕВЕРНО
		home(modi);
		soob_for_oper=1;
		sbros=1;
		whole_finish();
		return;
	}
}
//---------------------------------------------------------------
void marsh2()
{ //процедура проверки оттрассированного маршрута в маршрутном режиме
  //и проверка возможности установки стрелок в требуемое состояние
  int otv,obekt2,i;
  
	nom_func("165");
         
  vozvr=0;//сбросить флаг нажатий точек задания маршрута
  End_vara=0;//сбросить конец вариантного маршрута
  ukaz_trass=0;//указатель трассы поставить в начало
  while(trassa[ukaz_trass]!=0xFFFF)//проход по всем элементам маршрута
  {
    otv=test_elem(trassa[ukaz_trass]&0xfff,0);//провести тестирование для элемента
    if(otv==1)goto final;//если есть причины отказ от маршрута
    if(otv==22)//если нужно перевести стрелку в другой стойке
    {
      obekt2=fr1[trassa[ukaz_trass]][3];//определить объект для другой стойки
      if(fr1[obekt2][12]!=0)
      {
        fr3[obekt2][7]=oper;//запомнить необходимый код команды
        for(i=0;i<5;i++)
        { if(strelki[i][0]==0)
          { strelki[i][0]=obekt2;
            if(oper=='I'){strelki[i][1]=1;strelki[i][2]=0;}
            if(oper=='J'){strelki[i][1]=0;strelki[i][2]=1;}
            break;
          }
        }
        TIMER_SOB(obekt2,22,obekt2);//зарядить таймер на ожидание выполнения
      }
		}
		ukaz_trass++;//перейти к следующему элементу маршрута по трассе
	}
	w(132,nach_marsh,"");/*ПОСЫЛАЕМ КОМАНДУ НА ОТКРЫТИЕ СИГНАЛА */
	soob_for_oper=1;
	zad_marsh();
	//установить признак выдачи маршрутной команды
	if(fr1[nach_marsh][13]==1)komanda2[0]=nach_marsh;
	if(fr1[nach_marsh][13]==2)komanda2[1]=nach_marsh;
final:
//  finish_startMM();
//  whole_finish();//закончить работу с объектами
}
//-----------------------------------------------------------
int nashel(int nom)
{
  int iqc,kil=0;
  
	nom_func("180");
     
  for(iqc=0;iqc<WAZO;iqc++)
    if (nom==was[iqc]) return(1);
    else if(was[iqc]==0) kil++;
  if(kil==WAZO) return(0);
  else return(2);
}
//----------------------------------------------------------
void nemarsh(int nom)
{
	int coox,cooy;

	nom_func("183");

	if(klaval==13)
	{if(fr3[nom][fr1[nom][11]]==1)w(fr1[nom][4],999,"");
		else
			if(fr3[nom][fr1[nom][11]]==0) w(fr1[nom][3],999,"");
		oppp=0;puti=0;
		form_kom_nemarsh(nom);
		home(modi);
		return;
	}
	else return;
}
//-------------------------------------------------------
void nok(int nom)
{
	int bit;

	nom_func("185");

	bit=(fr1[nom][3]&0xf000)>>12;
	if(fr1[nom][0]==3)
	{
		if((fr3[nom][0]==1)&&(fr3[nom][bit]==0))
		{
			w(51,999,"");return;
		}
	}
	if(fr3[nom][bit]==0)vopros(1,9999,215,"?");//ОТКЛЮЧИТЬ УКСПС
	else
		if(fr1[nom][0]==2)
		{
			if(fr3[nom][bit]==1)vopros(1,9999,214,"?");//ВКЛЮЧИТЬ УКСПС
			else {home(modi);oppp=0;puti=0;return;}
		}
		else {w(229,999,"");home(modi);oppp=0;puti=0;return;}
	zapretvybora=1;oppp=1;puti=1;
	return;
}
//---------------------------------------------------------
void noka(nom)
{ int coox,cooy;
  
	nom_func("186");
 
  if(klaval==13)
  { if(fr3[nom][(fr1[nom][3]&0xf000)>>12]==0)w(109,999,"");//ПОСЫЛАЕМ КОМАНДУ НА ОТКЛЮЧЕНИЕ УКСПС 
    else
      if(fr3[nom][(fr1[nom][3]&0xf000)>>12]==1)w(108,999,"");//ПОСЫЛАЕМ КОМАНДУ НА ВКЛЮЧЕНИЕ УКСПС 
      else {home(modi);oppp=0;puti=0;return;}
    home(modi);
    oppp=0;
    puti=0;
    form_kom_nk_chk(nom);
    return;
  }
  else return;
}
//-----------------------------------------------
void nokb(nom)
{ int coox,cooy;

	nom_func("187");

	if(klaval==13)
	{ if((fr3[nom][0]==0)&&(oppp==1))
		{
			w(11,999,"");//ВЫДАНА ПРЕДВАРИТЕЛЬНАЯ КОМАНДА
			TIMER_SOB(nom,30,nom);
			oppp=2;
		}
    else
      if((fr3[nom][0]==1)&&oppp==2)
      {
        w(109,999,"");//ВЫДАНА КОМАНДУ НА ВКЛЮЧЕНИЕ УКСПС 
        oppp=0;
        home(modi);
      }
      else {home(modi);oppp=0;puti=0;return;}
    puti=1;
    first_razd(fr1[nom][3]&0xfff);
    return;
  }
  else return;

}
//------------------------------------------------
void opoveshe(int nom,int n)
{ int zm,b_zm,rm,b_rm,coox,cooy;

	nom_func("201");

  rm=fr1[nom][2]&0xfff; /*rm*/
  b_rm=(fr1[nom][2]&0xf000)>>12;
  zm=fr1[nom][7]&0xfff; /*zm*/
  b_zm=(fr1[nom][7]&0xf000)>>12;
  if (klaval==13)
  {
    oppp=0;puti=0;
    if(n==0)
    {
      //ПОСЫЛАЕМ КОМАНДУ ВКЛЮЧИТЬ ОПОВЕЩЕНИЕ
      if((fr3[rm][b_rm]==0)&&(fr3[zm][b_zm]==0))
      {
        w(36,999,"");
        form_kom_knopka(rm,0);
      }
      else
        //ПОСЫЛАЕМ КОМАНДУ ОТКЛЮЧИТЬ ЗАПРЕТ МОНТЕРАМ
        if((fr3[rm][b_rm]==1)&&(fr3[zm][b_zm]==1))
        {
          w(30,999,"");
          form_kom_knopka(zm,0);
        }
        else {home(modi);return;}
    }
    if(n==1)
		{
			w(31,999,"");
			form_kom_knopka(zm,0);//если включается запрет монтерам
		}
		if(n==2)
		{
			w(162,999,"");
			form_kom_knopka(rm,0);//если отключается оповещение
		}
		home(modi);
		return;
	}
	else return;
}
//----------------------------------------------------
//------------------------------------------------------------------
//процедура организации диалога при открытии сигнала в раздельном режиме
//po_ma - признак типа светофора
void otkrs()
{
	int nop,sm,Rez,j1,j2;

	nom_func("208");

	if((fr1[point][0]!=2)||(fr1[point][2]>1)||(fr1[point][1]>1))
	{
		w(228,999,"!");
#ifdef MOUSE
		if(MOUSE_ON!=0)
		{
			clear_mouse();
			for(j1=0;j1<12;j1++)line_old_gor_kurs[j1]=0;
			for(j1=0;j1<40;j1++)line_old_vert_kurs[j1]=0;
    }
#endif
    soob_for_oper=1;
    zapretvybora=1;
    return;
  }
  if(vibeg==2)goto step2;
  if(vih_vopr==2)goto step2;//если выдано предупреждение, и запрошено подтверждение
  if(uprav==1)point=markery[i3][6];//запомнить выбранный объект
  danet=0;//сбросить флаг ожидаемых ответов
 // если имеется признак отмены или открыт маневровый или поездной
  //сигнал закрывается
  if((ot==1)||(fr3[point][0]==1)||(fr3[point][1]==1)||(fr3[point][2]==1)||(fr3[point][3]==1))
  { vopros(0,point,136,"");// ЗАКРЫТЬ СИГНАЛ?
		danet=2;//установить флаг ожидания ответа для закрытия сигнала
		vibeg=2;//установить признак задания вопроса для сигнала
    zapretvybora=1;
    // если имеется признак отмены и закрыты поездной и маневровый
    if((ot==1)&&(fr3[point][0]==0)&&(fr3[point][1]==0))
    { if(fr1[point][6]==2)
      {
        po_ma=1;// если совмещенный сигнал,то установить признак
      }
      if(fr1[point][6]==3)//если у сигнала есть 2 белых
      { point++;//идем вперед на специальный сигнал - для 2-го белого огня
        po_ma=5;//устанавливаем признак наличия 2-х белых
      }
    }
    return;
  }
  if((fr3[point][0]==0)&&(fr3[point][1]==0)) //если закрыты оба сигнала
  { vopros(0,point,135,"");// ОТКРЫТЬ СИГНАЛ?
    if(fr1[point][6]==2)po_ma=1; //если сигнал совмещенный
    if(fr1[point][6]==3)// если есть два белых
    { point++;//идем вперед на специальный сигнал - для 2-го белого огня
      po_ma=5;//устанавливаем признак наличия 2-х белых
    }
    danet=1;//устанавливаем флаг ожидания ответа для открытия сигнала
    vibeg=2;//установить признак задания вопроса для сигнала
    return;
  }
step2:
  if(klaval==13)//если нажата Enter
  { if(vih_vopr==2)//если ранее выдавалось предупреждение для подтверждения
		{ t(0);        //убрать с экрана вопрос
			vih_vopr=0; //обнулить признак ожидания подтверждения при запретах
      goto step3; //перейти к действиям
    }
    if(vih_vopr==3)//если было предложено подтвердить
    { t(0);//очистить зону текстов
      vih_vopr=0;//сброс признака ожидания подтверждения при запретах
      goto step4;
    }
    if((danet==3)||(danet==2))//если спрашивали о закрытии
    { vibeg=0;//сброс флага ожидания подтверждения
      danet=0;
      zakrsi();//закрытие сигнала
    }
    else   // если спрашивали об открытии, то проверяем можно ли открывать
    { nop=fr1[markery[modi][6]][1];//взять направление
      if(nop==0) sm=1;// определить шаг приращения
      else sm=-1;
      if((fr1[markery[modi][6]][2]==0)&&  //если маневровый сигнал и

      (fr1[markery[modi][6]][6]==0))// не совмещенный
      manevro=1;                    // то установить признак маневрового
      if(mane==1)manevro=1;
      if(manevro==0) oper='B';// установить команду по открываемому сигналу
      else oper='A';
      for(ukaz_trass==0;ukaz_trass<100;ukaz_trass++)trassa[ukaz_trass]=0xFFFF;
      ukaz_trass=0;//освободить trass[]
      point=markery[i3][6];
      TEST=0;
      otkrsi();//набрать структуру КК вдоль существующего маршрута
			if(tst_nal_sig()==1)//проверить наличие сигнала конца, и если его нет
      {
        if(PROV_SCB==1)
        {
          podtver();//запросить подтверждение выдачи команды на открытие в "никуда"
          vih_vopr=3;//установить флаг ожидания подтверждения для открытия сигнала
        }
        klaval=-1;//сброс клавиатурного символа
        return;
      }
step4:
      ukaz_trass=0;
step3:
      while((ukaz_trass<100)&&(trassa[ukaz_trass]!=0xFFFF))//продолжать пока для объектов есть память
      { Rez=sogl_otkr(trassa[ukaz_trass]);//проверить очередной элемент
        if(Rez==-1){vibeg=0;return;}
        if((Rez==1)||
        //если неисправна стрелка(сигнал,участок,путь),стрелка без контроля,
        //на пути башмаки, открыт враждебный сигнал или
        (Rez==3)||   //
        (Rez==4)||
        (Rez==5))//стрелка на макете
        {
          if((Rez!=2)&&(PROV_SCB==1))
          {
            podtver();//если все предупреждения кроме fr4 - запрос на выполнение
            vih_vopr=2;//установка флага выдачи предупреждения и ожидания ответа
          }
          else
          {
						soob_for_oper=1;
            menu_N=0;
            return;
          }
          if((Rez==1)&&(fr1[trassa[ukaz_trass]][0]==3))ukaz_trass--;
          if((Rez==1)&&(fr1[trassa[ukaz_trass]][0]==4))
          ukaz_trass--;
          if((Rez!=4)&&(Rez!=3)&&(Rez!=5))
          {
            ukaz_trass++;
            maka=0;
          }
          if(Rez==5)maka=5;//если стрелка на макете
          klaval=-1;
          return;
        }
        else
        if(Rez==2) goto fini;//если ограничения введены оператором - выйти
				ukaz_trass++;//иначе перейти к следующему объекту
      }
      //если есть 2 белых сигнала на светофоре
			//для 2-го белого используется следующий объект
      menu_N=0;
      for(j1=0;j1<10;j1++)BEDA[j1]=0;
      if(fr1[point][6]==3)
      { //для поездного используется основной объект
        if(manevro==0)w(132,point,"");//ПОСЫЛАЕМ КОМАНДУ НА ОТКРЫТИЕ СИГНАЛА
        if(manevro==1)w(132,point-1,"");// ПОСЫЛАЕМ КОМАНДУ НА ОТКРЫТИЕ СИГНАЛА
      }
      else
			{
        del_kursor(i3);
        okno_otkaz=0;
        w(132,point,"");// ПОСЫЛАЕМ КОМАНДУ НА ОТКРЫТИЕ СИГНАЛА
      }
		}
    if(oper!=0)fotksig(oper);//заполнение буфера выдачи команды
fini:
    if(danet==1)
    for(ukaz_trass=0;ukaz_trass<100;ukaz_trass++)trassa[ukaz_trass]=0xFFFF;//окончание работы для стрелок
    home(modi);//курсор - "ДОМОЙ!
    //сброс всех флагов
    basha=0;manevro=0;mane=0;manevr=0;first_col=0;vibeg=0;vih_vopr=0;
    return;
  }
  else
  {
    if(klaval==32)//если сброс (нажатие пробела) после выбора сигнала
    { vibeg=0;//сброс флагов задания вопросов
      vih_vopr=0;
      if(danet==1)//сброс массивов
      for(ukaz_trass=0;ukaz_trass<100;ukaz_trass++)trassa[ukaz_trass]=0xFFFF;//окончание работы для стрелок
      whole_finish();
      //если была активизирована отмена,сбросить активность отмены
      if(ot==1){vkl_kno(0,8);ot=0;}
      if(vrem==1){uprav=1;puti=0;}
      t(0);
      mane=0;manevr=0;manevro=0;basha=0;
      return;
    }
		else return;
	}
}
//-------------------------------------------------------
void perekl_komp(int nom)
{
  
	nom_func("218");
       
  if(((fr3[nom][0]==0)&&(fr3[nom][1]==0)&&(fr3[nom][2]==0))||
  ((fr3[nom][0]==1)&&(fr3[nom][1]==0)&&(fr3[nom][2]==0)))
  { //ПЕРЕКЛЮЧИТЬ КОМПЛЕКТ? 
    vopros(1,9999,113,"");oppp=1;puti=1;return;
  }
  else 
  { //ПЕРЕКЛЮЧЕНИЕ КОМПЛЕКТОВ НЕВОЗМОЖНО 
    w(40,999,"");oppp=0;return;
  }
}
//-------------------------------------------------------------
void perstr()
{
	int point1,ij,avtr;

	nom_func("219");

	point1=point;
#ifdef AVTOD
	avtr=prov_ele_avtod(point);
	if(avtr==1){w(245,999,"");return;}
	if(avtr==2){w(244,999,"");return;}
#endif
	if(vibeg==1) goto step2;
	if(vib_ma==1) goto ddo;// если переводится стрелка на макете
	if(vih_vopr==1)goto step2;//если ранее был задан вопрос для подтверждения
  osya=0;//обнуление счетчика выданных ненорм по объекту
  for(ij=0;ij<10;ij++)BEDA[ij]=0;
  hod=0;//сброс флага входа в проверку для анализа спаренных стрелок 
  if(Opred()<0)return;//поиск объекта информационных пакетов
          //для стрелки(имеет смысл для спаренной стрелки)
  if(fr4[point][1]==1)//Если стрелка на макете
  { w(99,markery[modi][6]," НА МАКЕТЕ, ПОСЫЛАТЬ КОМАНДУ?");
    vib_ma=1;//установка флага работы с макетом
    zapretvybora=1;
    return;
  }
ddo:
  //если стрелка без контроля
  if(net_kontro==2){fi_co1=0;se_co1=1;goto beda;}
  //если потеря контроля
	if(fr3[point][5]==1){net_kontro=1;return;}
  if(fr3[point][0]==fr3[point][1]==1){net_kontro=1;return;}
  else
  {
beda:
    if(((fr3[point][0]==1)&&(fr3[point][1]==0))||  //если стрелка в плюсе или
    ((net_kontro==2)&&((oper=='B')||  //стрелка без контроля и перевод в минус
    (oper=='F'))))//или стрелку без контроля на макете переводят в минус
    { if(net_kontro==2) vopros(0,point1,125,"");//без контр.СТРЕЛКУ ## В МИНУС?
      else vopros(0,markery[modi][6],125,"+");// с контролем СТРЕЛКУ ##+ В МИНУС?
      if(fr4[point][1]==0) oper='B';//если не на макете - команда простая
      else oper='F'; // если на макете - команда макетная
      net_kontro=0;//снять признак отсутствия контроля
    }
    else
    { //далее аналогично для перевода стрелки в плюс
      if(net_kontro==2) vopros(0,point1,124,"");
      else vopros(0,markery[modi][6],124,"-");// СТРЕЛКУ В ПЛЮС?
      if(fr4[point][1]==0) oper='A';
      else oper='E';
      net_kontro=0;
    }
    vibeg=1;
    zapretvybora=1;
    return;
  }
step2:
  vibeg=0;
  vib_ma=0;
  if((osya>=4)&&(osya<10))osya=0;
	else
  { //выполнить проверку возможности перевода
    osya=tst_strelok(point);
    if(osya==10){home(modi);finish_strelok();return;}
  }
  //если нет запрета на перевод стрелки
  if(osya==0)
  { // ПОСЫЛАЕМ КОМАНДУ НА ПЕРЕВОД СТРЕЛКИ
    okno_otkaz=0;
    if(AVARI==0){zapretvybora=0;w(123,point1,"");}
    else
    { //ОЖИДАЕТСЯ НАЖАТИЕ КНОПКИ СЧЕТЧИКА "ВСП.ПЕРЕВОД"
      w(55,999,"");AV_zdem=1;
    }
    for(ij=0;ij<10;ij++)BEDA[ij]=0;
    formkps(oper);
  }
  else
  if((osya>1)&&(PROV_SCB==1))
  { if(AVARI==0){vih_vopr=1;podtver();klaval=0;return;}
    else
    {if(osya<=2){vih_vopr=1;podtver();klaval=0;return;}
      else
      {home(modi);finish_strelok();klaval=0;return;}
    }
  }
  del_kursor(modi);
  show_kursor(modi);
  osya=0;vih_vopr=0;
  return;
}
//--------------------------------------------------------
void prkl(int nom)
{
	int coox,cooy;

	nom_func("238");

	if (klaval==13)
	{ //ПОСЫЛАЕМ КОМАНДУ НА ПЕРЕКЛЮЧЕНИЕ КОМПЛЕКТОВ
		t(0);w(41,999,"");home(modi);
		oppp=0;puti=0;
		form_kom_prkl(nom);
		return;
	}
	else return;
}
//---------------------------------------------------------------
void smen_napr(int nom1)
{
  int h=0,bh=0;
  
	nom_func("309");
          
  if((nikuda==1)||(klo==1)||(help!=0)) return;
  if(fr3[fr1[nom1][9]][7]!=0)
  {
    w(237,999,"");return;//СМЕНА НАПРАВЛЕНИЯ НЕ ВОЗМОЖНА
  }
  if((fr3[nom1][2]==1)||(fr3[nom1][5]==1))
  { oppp=1;
    #ifdef POLUAVTOMAT
      w(0,999,"");//Дать согласие на прием невозможно: занят перегон
    #else
      w(182,999,"");//СМЕНА НАПРАВЛЕНИЯ НЕВОЗМОЖНА: ЗАНЯТ ПЕРЕГОН
    #endif
    home(modi);oppp=0;
    return;
  }
  else
  if(fr3[nom1][1]==1)
  { oppp=1;
    w(170,999,"");//направление менять не надо
zz:
    home(modi);oppp=0;
    return;
  }
  else
	{ if(oppp==0)vopros(17,markery[modi][6],117,"?"); //отправление
		oppp=1;puti=1;zapretvybora=1;
		return;
	}
}
//----------------------------------------------------
void smena(int nom)
{
  
	nom_func("310");
        
  if (klaval==13) 
  {
    #ifdef POLUAVTOMAT 
    w(2,999,"");
    #else
    w(183,999,"");
    #endif
    home(modi); oppp=0;puti=0;
    form_kom_smen(nom);
  }
  return;
}
//----------------------------------------------------
void start_time_date()
{

	nom_func("319");

	rg.h.ah=0x2a;        // дата
	int86(0x21,&rg,&rg);
	dayy_=rg.h.dl;
	monn_=rg.h.dh;
	yearr_=rg.x.cx;
	rg.h.ah=0x2c;       // время
	int86(0x21,&rg,&rg);
	ho_ur=rg.h.ch;
	mi_n=rg.h.cl;
	se_c=rg.h.dh;
}
//-------------------------------------------------------
#ifdef POLUAVTOMAT
void kom_dso(int ndso_chdso)
{
	int npo_chpo,nfp_chfp,nfdp_chfdp;
	int bit_ndso_chdso,bit_npo_chpo,bit_nfp_chfp,bit_nfdp_chfdp;
	bit_ndso_chdso=fr1[ndso_chdso][3];
	npo_chpo=fr1[ndso_chdso][4]; bit_npo_chpo=fr1[ndso_chdso][5];
  nfp_chfp=fr1[ndso_chdso][6]; bit_nfp_chfp=fr1[ndso_chdso][7];
  nfdp_chfdp=fr1[ndso_chdso][8];bit_nfdp_chfdp=fr1[ndso_chdso][9];
  if(nikuda==1||klo==1||help!=0)return;
  if(fr3[npo_chpo][bit_npo_chpo]==1){w(0,999,"");home(modi);return;}  
  // если нет согласия 
  if(fr3[ndso_chdso][bit_ndso_chdso]==0)
  // ВЫДАТЬ СОГЛАСИЕ НА ПРИЕМ СО СТАНЦИИ? 
  { vopros(18,ndso_chdso,84,"?");oppp=1;zapretvybora=1;return;}
  else
  // СНЯТЬ СОГЛАСИЕ НА ПРИЕМ?  
  if(fr3[ndso_chdso][bit_ndso_chdso]==1)
  { vopros(18,ndso_chdso,85,"?");oppp=1;zapretvybora=1;return;}
}
//-------------------------------------------------------------------
void k_dso(int ndso_chdso)
{
	unsigned char koda;
	int npo_chpo,nfp_chfp,nfdp_chfdp;
	int bit_ndso_chdso,bit_npo_chpo,bit_nfp_chfp,bit_nfdp_chfdp;
	bit_ndso_chdso=fr1[ndso_chdso][3];
	npo_chpo=fr1[ndso_chdso][4];
	nfp_chfp=fr1[ndso_chdso][6];
	nfdp_chfdp=fr1[ndso_chdso][8];
	bit_npo_chpo=fr1[ndso_chdso][5];
	bit_nfp_chfp=fr1[ndso_chdso][7];
  bit_nfdp_chfdp=fr1[ndso_chdso][9];
  if(nikuda==1||klo==1||help!=0)return;
  if(klaval==13)
  {
    if(fr3[ndso_chdso][bit_ndso_chdso]==0)
    {
      vopros(17,ndso_chdso,86,"!");/* ВЫДАЕМ СОГЛАСИЕ НА ПРИЕМ НА СТАНЦИЮ##*/
      koda='A';
    }
    if(fr3[ndso_chdso][bit_ndso_chdso]==1)
    {
      vopros(17,ndso_chdso,87,"!");/* СНИМАЕМ СОГЛАСИЕ НА ПРИЕМ НА СТАНЦИЮ##*/
      koda='M';
    }
    home(modi);
    oppp=0;
    point=ndso_chdso;
    if(fotksig(koda)==1)return;
    buf_ko[9]=check_sum(buf_ko);
		pooo[ndso_chdso]=biostime(0,0L);
		flagoutmsg=1;
	}
}
//-----------------------------------------------------------
void kom_fdp(int nfdp_chfdp)
{
  int ndso_chdso,npo_chpo,nfp_chfp;
  int bit_ndso_chdso,bit_npo_chpo,bit_nfp_chfp,bit_nfdp_chfdp;
  ndso_chdso=fr1[nfp_chfp][2];
  bit_ndso_chdso=fr1[ndso_chdso][3];
  npo_chpo=fr1[nfp_chfp][4];
  nfp_chfp=fr1[nfdp_chfdp][6];
  bit_npo_chpo=fr1[nfp_chfp][5];
  bit_nfp_chfp=fr1[nfp_chfp][7];
  bit_nfdp_chfdp=fr1[nfp_chfp][9];
  if(nikuda==1||klo==1||help!=0)return;
  if(fr3[nfdp_chfdp][bit_nfdp_chfdp]==0)//если нет дачи прибытия 
  //ДАЧА ПРИБЫТИЯ?
  {vopros(17,nfdp_chfdp,161,"?");oppp=1;zapretvybora=1;return;}
  else
  if(fr3[nfdp_chfdp][bit_nfdp_chfdp]==1)
  //ПРИБЫТИЕ УЖЕ ВЫДАНО 
  {vopros(18,nfdp_chfdp,3,"");oppp=0;home(modi);return;}
}
//---------------------------------------------------------------
void k_fdp(int nfdp_chfdp)
{
	unsigned char koda;
	int ndso_chdso,npo_chpo,nfp_chfp;
	int bit_ndso_chdso,bit_npo_chpo,bit_nfp_chfp,bit_nfdp_chfdp;
	ndso_chdso=fr1[nfp_chfp][2];
	bit_ndso_chdso=fr1[ndso_chdso][3];
	npo_chpo=fr1[nfdp_chfdp][4];
	nfp_chfp=fr1[nfdp_chfdp][6];
	bit_npo_chpo=fr1[nfp_chfp][5];
  bit_nfp_chfp=fr1[nfp_chfp][7];
  bit_nfdp_chfdp=fr1[nfp_chfp][9];
  if(nikuda==1||klo==1||help!=0)return;
  if(klaval==13)
  {
    if(fr3[nfdp_chfdp][bit_nfdp_chfdp]==0)
    {
      vopros(18,nfdp_chfdp,13,"!");//ПОСЫЛАЕМ КОМАНДУ ДАЧИ ПРИБЫТИЯ
      koda='A';
    }
    home(modi);
    oppp=0;
    point=nfdp_chfdp;
    if(fotksig(koda)==1)return;
    buf_ko[9]=check_sum(buf_ko);
    pooo[nfdp_chfdp]=biostime(0,0L);
    flagoutmsg=1;
  }
}
#endif
//---------------------------------------------------------
void vkl_avto()
{ //процедура реализации предварительного диалога при вкл./откл. автодействия
	int avt_plt,bt_avt;

	nom_func("394");

	if(markery[modi][6]!=9999)//если имеется пультовое автодействие
	{
		avt_plt=markery[modi][6]&0xfff;//номер объекта пультового автодействия
		bt_avt=(markery[modi][6]&0xf000)>>12;
		if(fr3[avt_plt][bt_avt]!=0){w(258,999,"");return;}
	}
	if(markery[modi][7]-777==0)//если нажата кнопка нечетного автодействия
		if(na==0) w(26,999,"");//если оно выключено"ВКЛЮЧИТЬ АВТОДЕЙСТВИЕ ПО 1П?"
		else w(28,999,"");//если включено "ВЫКЛЮЧИТЬ АВТОДЕЙСТВИЕ ПО 1П?"
	else
	 if (markery[modi][7]-777==1)//если нажата кнопка четного автодействия
		if(cha==0) w(27,999,"");//если оно выключено"ВКЛЮЧИТЬ АВТОДЕЙСТВИЕ ПО 2П?"
		else w(29,999,"");//если включено "ВЫКЛЮЧИТЬ АВТОДЕЙСТВИЕ ПО 2П?"
	zapretvybora=1;oppp=1;puti=1; return;
}
//-------------------------------------------------
void vkl_dn(int nom)
{ int ob_au,ob_dn,ob_nn,bit_au,bit_nn,bit_dn;
	ob_nn=fr1[nom][3];bit_nn=fr1[nom][4];
	ob_dn=fr1[nom][5];bit_dn=fr1[nom][6];
	ob_au=fr1[nom][9];bit_au=fr1[nom][10];

	nom_func("395");

	if(ob_au!=9999)//если есть кнопка "автомат"
	{ if(nom==ob_au)//если нажата кнопка "автомат"
		{ if(COD_DN>7)//если автоматический режим уже установлен
			//АВТОМАТИЧ.РЕЖИМ РАБОТЫ СИГНАЛОВ УЖЕ УСТАНОВЛЕН
			{ w(202,999,"");oppp=0;puti=0;home(modi);return;}
			else vopros(1,9999,203,"?");//установить режим "автомат"?
		}
	}
	if((nom==ob_nn)||(nom==ob_dn))//если нажата кнопка режима
	{ if((COD_DN==2)||(COD_DN==3)||(COD_DN==8))vopros(1,9999,204,"?");//включить дневной режим?
		else
			if((COD_DN==4)||(COD_DN==5)||(COD_DN==9))vopros(1,9999,205,"?");//включить ночной режим?
			else {w(209,999,"");
			oppp=0;puti=0;home(modi);return;}
	}
	if((nom!=ob_au)&&( nom!=ob_dn)&&( nom!=ob_nn))
	{oppp=0;puti=0;home(modi);return;}
	oppp=1;puti=1;return;
}
//--------------------------------------------------------
void vkl_knop(int nom)
{
	int bit,// бит включения объекта
	vopr1,//вопрос перед включением
	vopr2;//вопрос перед отключением

	nom_func("397");

	if((fr1[nom][2]==5)&&(na==1))
	{
		w(245,999,"");
		return;
	}
	if((fr1[nom][2]==6)&&(cha==1))
	{
		w(244,999,"");
		return;
	}
	if(fr1[nom][1]!=166){bit=fr1[nom][11];vopr1=fr1[nom][8];vopr2=fr1[nom][9];}
	else {bit=(fr1[nom][3]&0xf000)>>12;vopr1=fr1[nom][6];vopr2=fr1[nom][7];}
	if(fr1[nom][2]==33)//если это кнопка смены направления
	{ if(fr3[nom][bit]==0)//если объект пассивен
		{
			if(vopr1!=9999) //если предусмотрен вопрос на включение
			{ //задать вопрос о включении
				setfillstyle(1,14),setcolor(4);
				vopros(18,markery[modi][6],vopr1,"?");
			}
			else {oppp=0;puti=0;home(modi);return;}//если вопроса нет, то выйти
		}
		else// если объект не пассивен
		{
			if(fr3[nom][bit]==1)//если объект активен
			{
				if(vopr2!=9999)//если предусмотрен вопрос на отключение
				{ setfillstyle(1,14),setcolor(4);
					vopros(18,markery[modi][6],vopr2,"?");
				}
				else {oppp=0;puti=0;home(modi);return;}
			}
		}
	}
	else//для всех остальных кнопок
	{
		if(fr3[nom][bit]==0)//если объект пассивен
		{
			if(vopr1!=9999)//если есть текст на включение
			{
				setfillstyle(1,14),setcolor(4);
        vopros(1,9999,vopr1,"?");
      }
      else {oppp=0;puti=0;home(modi);return;}
    }
    else //если объект активен
    {
      if(fr3[nom][bit]==1)
      {
        if(fr1[nom][2]==2)//если не предусмотрено отключение
        {
          w(229,999,"");return;
        }
        if(vopr2!=9999)//если есть текст на отключение
        {
          setfillstyle(1,14),setcolor(4);
          vopros(1,9999,vopr2,"");
        }
        else {oppp=0;puti=0;home(modi);return;}
      }
    }
  }
  oppp=1;puti=1;return;
}
//--------------------------------------------------------------
void vkl_nemarsh(int nom)
{ int otvet;

	nom_func("398");

	if(fr1[nom][2]==33)
  { if(fr3[nom][fr1[nom][11]]==0)
      if(fr1[nom][8]!=9999){setfillstyle(1,14),setcolor(4);vopros(18,markery[modi][6],fr1[nom][8],"?");}
      else {oppp=0;puti=0;home(modi);return;}
    else
      if(fr3[nom][fr1[nom][11]]==1)
        if(fr1[nom][9]!=9999){setfillstyle(1,14),setcolor(4);vopros(18,markery[modi][6],fr1[nom][9],"?");}
        else{oppp=0;puti=0;home(modi);return;}
  }
  else
  { if(fr3[nom][fr1[nom][11]]==0)
      if(fr1[nom][8]!=9999){setfillstyle(1,14),setcolor(4);vopros(1,9999,fr1[nom][8],"?");}
      else {oppp=0;puti=0;home(modi);return;}
    else
      if(fr3[nom][fr1[nom][11]]==1)
        if(fr1[nom][9]!=9999){setfillstyle(1,14),setcolor(4);vopros(1,0,fr1[nom][9],"?");}
        else {oppp=0;puti=0;home(modi);return;}
  }
  if(fr3[nom][fr1[nom][11]]==0)
  {
    nach_marsh=fr1[nom][2];
    end_marsh=fr1[nom][7];
    END=end_marsh;
    TEST=0;
    if(may_be(nach_marsh,fr1[nach_marsh][1])==0)
		{
      ukaz_trass=0;
      while(trassa[ukaz_trass]!=0xffff)
      {
        if(fr1[trassa[ukaz_trass]][0]==1)plus_minus();
        fr3[trassa[ukaz_trass]][10]=fr3[trassa[ukaz_trass]][10]|1;
        otvet=test_elem(trassa[ukaz_trass]&0x7fff,2);
        if(otvet==1)goto not;
        ukaz_trass++;
      }
      ris_trassa();
      oppp=1;
      puti=1;
      return;
    }
    w(83,999,"");
not:
    whole_finish();
    return;
  }
  else
  {
    oppp=1;
    puti=1;
    return;
  }
}
//------------------------------------------------------------------
void vkl_opoveshe(int nom)
{ // объект для РМ, объект для ЗМ
	int bz1,bz2,bb;
  
	nom_func("400");
      
  bz1=fr1[nom][2];bz2=fr1[nom][7];bb=fr1[bz1][11];
  if((fr3[bz1][bb]==0)&&(fr3[bz2][bb]==0))
  //ВКЛЮЧИТЬ ОПОВЕЩЕНИЕ?
  { vopros(1,9999,38,"");zapretvybora=1;}
  else
  {
    if((fr3[bz1][bb]==1)&&(fr3[bz2][bb]==1))
    //ОТКЛЮЧИТЬ ЗАПРЕТ МОНТЕРАМ?
    { vopros(1,9999,39,"");zapretvybora=1;}
    else
      if((fr3[bz1][bb]==1)&&(fr3[bz2][bb]==0))
      {
        menu_N=4;
        punkt_N=1;
        klaval=-1;
        regs.x.ax=4;
        regs.x.cx=590;
        regs.x.dx=50;
        int86(0x33,&regs,&regs);
        X_m=590;
        Y_m=50;
        obnov_kur_mouse(590,50);
        menu1();
        return;
			}
      else
      {oppp=0;puti=0;home(modi);return;}
  }
  oppp=1;
  puti=1;
  return;
}
//-------------------------------------------------
void vopr_mar()
{
	int end_marsh1;

	nom_func("403");

	if(end_marsh!=0)nach_marsh=end_marsh;
	end_marsh=markery[modi][6];
	if(markery[modi][7]==7)end_marsh1=fr1[end_marsh][2];
	else end_marsh1=end_marsh;
	if((fr1[nach_marsh][5]!=0)&&
	((fr1[nach_marsh][5]&0x00ff)==end_marsh1)||
	(((fr1[nach_marsh][5]&0xFF00)>>8)==end_marsh1))//если может быть вариант
	{
		if(fr1[end_marsh][4]==10)
		{ if(fr1[nach_marsh][1]==fr1[end_marsh][1])
			{ menu_N=5;
				punkt_N=1;
				klaval=-1;
			}
		}
		else
    if(fr1[end_marsh][4]==11)
    { menu_N=5;
      punkt_N=1;
      klaval=-1;
    }
    Zdem_vibor_marshruta=1;
    return;
  }
if((end_marsh!=0)&&(nach_marsh!=0))voper();
}
//------------------------------------------------------
int ZAGO_MPSU(int Coc1)
{
  int BZ;
  int mask3y=0x08;//второй основной установить
  int mask2y=0x04;//первый основной установить
  int mask3n=0x77;//второй основной сбросить
  int mask2n=0x7b;//первый основной сбросить
  
	nom_func("425");
          
  BZ=Coc1;
  if(NOMER_ARMA==1)
  {//если основная ПЭВМ, установить основным первый
    if(STATUS==1){BZ=BZ|mask2y;BZ=BZ&mask3n;}
    if((STATUS==0)||(STATUS==2)){BZ=BZ&mask2n;BZ=BZ|mask3y;}//установить основным второй
  }
  if(NOMER_ARMA==2)
  {
    if(STATUS==1){BZ=BZ|mask3y;BZ=BZ&mask2n;}
    if(STATUS==0){BZ=BZ|mask2y;BZ=BZ&mask3n;}
    if(STATUS==2){BZ=BZ&mask2n;BZ=BZ&mask3n;}
  }
  if((TELEUP==1)&&(DU==1)&&(SEZON==0))BZ=BZ|16;
  if(((TELEUP==1)||(SEZON==1))&&(DU==0))BZ=BZ|32;
  return(BZ);
}
//---------------------------------------------------------
void ZAP_BUF_SPD()
{
	int iz,jz,kz,aa,n_rpc;

	nom_func("433");

#ifdef SPDLP
	if(spdlp!=0)return;
	if(STATUS!=1)
	{
		BUF_OUT_SPD[0]=0x16;
		BUF_OUT_SPD[1]=0x5;
		BUF_OUT_SPD[2]=0x4;
		spdlp=1;
		ukaz_spd=3;
		ukaz_out_spd=0;
		return;
	}
	BUF_OUT_SPD[0]=0x16;
	BUF_OUT_SPD[1]=0x5;
	BUF_OUT_SPD[2]=0x80;
	BUF_OUT_SPD[3]=LEN_SPD;
	BUF_OUT_SPD[4]=adr_spdlp;
	BUF_OUT_SPD[5]=0x1c;
	BUF_OUT_SPD[6]=ho_ur;
	BUF_OUT_SPD[7]=mi_n;
	BUF_OUT_SPD[8]=se_c;
	ukaz_spd=9;
	while(ukaz_spd<75)
	{
		for(iz=0;iz<K64;iz++)//пройти по платам 64 контактным
		{
			BUF_OUT_SPD[ukaz_spd++]=0x80|iz;//записать имя платы
			for(jz=0;jz<8;jz++)//пройти по всем байтам платы
			{
				for(kz=0;kz<8;kz++) //пройти по всем битам байта
				{
					n_rpc=64*iz+8*jz+kz;
					if(fr3[byte_spdlp[n_rpc]][bt_spdlp[n_rpc]]==1)
						BUF_OUT_SPD[ukaz_spd]=BUF_OUT_SPD[ukaz_spd]|(0x80>>kz);
					else
						if(fr3[byte_spdlp[n_rpc]][bt_spdlp[n_rpc]]==0)
						BUF_OUT_SPD[ukaz_spd]=BUF_OUT_SPD[ukaz_spd]&(~(0x80>>kz));
				}
				ukaz_spd++;
			}
		}
		for(iz=0;iz<K32;iz++)
		{
			BUF_OUT_SPD[ukaz_spd++]=iz+K64;
			for(jz=0;jz<4;jz++)
			{
				for(kz=0;kz<8;kz++)
				{
					n_rpc=64*K64+8*jz+kz;
					if(fr3[byte_spdlp[n_rpc]][bt_spdlp[n_rpc]]==1)
						BUF_OUT_SPD[ukaz_spd]=BUF_OUT_SPD[ukaz_spd]|(0x80>>kz);
					else
						if(fr3[byte_spdlp[8*jz+kz]][bt_spdlp[8*jz+kz]]==0)
						BUF_OUT_SPD[ukaz_spd]=BUF_OUT_SPD[ukaz_spd]&(~(0x80>>kz));
				}
				ukaz_spd++;
			}
		}
		jz=0;
		for(iz=1;iz<ukaz_spd;iz++)jz=jz+BUF_OUT_SPD[iz];
		BUF_OUT_SPD[ukaz_spd++]=jz%256;
		BUF_OUT_SPD[ukaz_spd]=0x4;
		ukaz_out_spd=0;
		break;
	}
	spdlp=1;
#endif
	return;
}
//---------------------------------------------------------
void OUT_SPD()
{
  unsigned char ts;
  
	nom_func("212");
         
  if(spdlp==0)return;
  inportb(BAZ_ADR6);
  ts=inportb(BAZ_ADR6+5);
  if((ts&0x20)==0x20)
  {

    outportb(BAZ_ADR6,BUF_OUT_SPD[ukaz_out_spd]);
    BUF_OUT_SPD[ukaz_out_spd]=0;
    ukaz_out_spd++;
  }
  else return;
  if(ukaz_out_spd>ukaz_spd)
  {
    spdlp=0;
    ukaz_spd=0;
    ukaz_out_spd=0;
		return;
  }
}
//-----------------------------------------------
void Zona_k()
{

	nom_func("436");

	if(klo==1||help!=0) return;
  if(nikuda==1) return;
  if(ZONA_KURSORA==ZONA_N)ZONA_KURSORA=ZONA_CH;
  else ZONA_KURSORA=ZONA_N;
  pat=i3;
  del_kursor(pat);
  i3=ZONA_KURSORA;
  show_kursor(i3);
  pat=i3;
  modi=i3;
}
//--------------------------------------------------------
void zp_zp(int nnn)
{
	int koda=0;

	nom_func("438");

	prorisovka=0;
	NOM_NEXT=nnn+1;
	if((fr3[nnn][0]==1)&&(fr3[NOM_NEXT][1]==1))koda='M';
	else koda='A';
	point=nnn;
	if(form_kosig(koda)==1) return;
	buf_ko[9]=check_sum(buf_ko);
	pooo[nnn]=biostime(0,0L);
  TIMER_SOB(nnn,66,nnn);
  buf_ko[0]='('; buf_ko[10]=')';
  kom_v_bufer(fr1[nnn][13]-1);
  if((fr3[NOM_NEXT][1]==1)&&(koda=='M'))koda='N';
  else koda='B';
  point=NOM_NEXT;
	if(form_kosig(koda)==1) return;
  buf_ko[9]=check_sum(buf_ko);
  buf_ko[0]='(';buf_ko[10]=')';
  kom_v_bufer(fr1[NOM_NEXT][13]-1);
  flagoutmsg=0;zapretvybora=0;NOM_NEXT=0;puti=0;oppp=0; prorisovka=1;
}
//--------------------------------------------------------------
void voper()
{
  char mess[10]="";
	int vniz=0;
	
	nom_func("402");
	/*
	if(PREDUPR==1)
	{
		t(2);
		vniz = 14;
		PREDUPR = 0;
	}
	else */

	t(0);

	setfillstyle(1,14);bar(476,1+vniz,635,27+vniz);moveto(478,8+vniz);
	setcolor(4);outtext(" МАРШРУТ ОТ ");
	strcpy(mess,pako[nach_marsh]);outtext(mess);strcpy(mess,"");
	moveto(500,17+vniz);strcpy(mess,pako[end_marsh]);
	if((fr1[nach_marsh][1]==fr1[end_marsh][1])||
	((mane==1)&&(fr1[end_marsh][3]==7)))outtext(" ДО     , ДА ?  ");
	else outtext(" ЗА     , ДА ?  ");
	moveto(532,17+vniz);outtext(mess);setlinestyle(0,0,0);
	rectangle(478,4+vniz,633,26+vniz);
	vozvr=1;
	klaval=-1;
	poka=0;
//	PREDUPR=0;
	zapretvybora=1;
	return;
}
//----------------------------------------
//процедура выдачи вопросительного предложения в окно экрана
void vopros(int longo,int nomo,int N_v,char Sy[8])
{
//longo - вариант размера,цвета и расположения текста
	int CVE,CVEB,lp,lp1,D=0;
	char NAME[25]="",Nam[8]="";
	struct fillsettingstype fillinfo;
	int xv,yv,exv,eyv;

	nom_func("404");

	switch(longo)
	{
		case 0: yv=1; eyv=26; break;
		case 1: yv=1; eyv=18; break;
		case 2: yv=1; eyv=18; break;
		case 3: yv=1; eyv=24; break;
		case 17:yv=0; eyv=28; break;
		case 18:yv=0; eyv=28; break;
		case 19:yv=1; eyv=28; break;
		default: return;
	}
  lseek(file_soob,N_v*63L,0L);
  read(file_soob,&soob.lex,60);
  for(lp=0;lp<60;lp++)soob.lex[lp]=~soob.lex[lp];
  while(soob.lex[lp]==0x20){soob.lex[lp]=0;lp--;}
  read(file_soob,&soob.COlo,1);
  CVE=soob.COlo;
  if(CVE==14)CVEB=4;
  if(CVE==2)CVEB=15;
  if(CVE==4)CVEB=15;
	if(longo==17)
  xv=639-max(10+strlen(soob.lex)*7,16+strlen(otopri[fr1[nomo][11]])*7);
  else xv=639-(7+strlen(soob.lex))*7;
  exv=639;
  wind_w(xv,yv,exv,eyv,SOLID_FILL,CVE,CVEB,0);
  moveto(xv+8,yv+4);
  outtext(soob.lex);
  if(longo==17)
  { moveto(xv+1,yv+17);
    outtext(otopri[fr1[nomo][10]]);
    outtext(Sy);
    return;
  }
  if(longo==18)
  { moveto(xv+8,yv+17);
    outtext(otopri[fr1[nomo][7]]);
    outtext(Sy);
    return;
  }
  if(longo==19)
  { outtext(" ДЛЯ");
    moveto(xv+8,yv+17);
    outtext("ВСПОМОГАТ. ПЕРЕВОДА");
    return;
  }
  if(nomo==9999){outtext(Sy);return;}
  if(fr1[nomo][0]==1) //если стрелка
  { lp=0;
    while(pako[nomo][lp]!=146)lp++;
    lp++;
		for(lp1=0;lp1<25;lp1++)NAME[lp1]=0;
		lp1=0;
		while(pako[nomo][lp]!=':'){NAME[lp1]=pako[nomo][lp];lp++;lp1++;}
	}
	else
	{ lp1=0;
		NAME[lp1++]=32;
		for(lp=0;lp<25;lp++)
		{ NAME[lp1]=0;
			if(pako[nomo][lp]!=32)NAME[lp1++]=pako[nomo][lp];
		}
		NAME[lp1]=0;
	}
	outtext(NAME);
	xv=getx(); yv=gety(); moveto(xv,yv);
	strcpy(Nam,Sy);outtext(Nam);
}
//------------------------------------------------------------------
void zad_marsh_avto()
{ //процедура задания маршрута
  int vv=0;
  
	nom_func("424");
          
  buf_ko[2]='b';//то же самое, если поездной маршрут в одной стойке
  vv=vibor(nach_avto);//получить код-индекс для задания начала
  buf_ko[1]=BAM;//заполнить заголовок
  if(vv!=9999)buf_ko[4]=vv; //заполнить код-индекс для сигнала начала
  else return;
  buf_ko[3]=podgr;//установить подгруппу начала
  vv=vibor(end_avto);//получить код-индекс для задания конца
  if(vv!=9999)  buf_ko[6]=vv; //заполнить код-индекс для сигнала конца
  else return;
  buf_ko[5]=podgr;//установить подгруппу конца
  //если задается вариантный маршрут
  buf_ko[7]=124;//в оставшиеся байты записать заполнитель
  buf_ko[8]=124;
zc:
  buf_ko[9]=check_sum(buf_ko);//дополнить команду контрольной суммой
  buf_ko[0]='(';
  buf_ko[10]=')';
  pooo[nach_avto]=biostime(0,0L);//зафиксировать время выдачи
  flagoutmsg=1;//выставить флаг-требование на передачу в ТУМС
}
//----------------------------------------------------------------
void zad_marsh()
{ //процедура задания маршрута
	int vv=0;

	nom_func("423");

	for(vv=0;vv<100;vv++)
	{
		fr3[trassa[vv]][8]=trassa[vv+1]&0xfff;
		if(fr3[trassa[vv]][8]==0xfff)break;
  }
#ifdef KOL_SOO2
  if((mane==0)&& //если задается поездной маршрут и
  (fr1[nach_marsh][13]!=fr1[end_marsh][13]))// он проходит через 2 стойки
  {
    zad2_marsh();//вызвать функцию задания сквозного маршрута
    return;
  }
#endif
  if(mane==1)buf_ko[2]='a';//установить код команды,если маневровый маршрут
  else buf_ko[2]='b';//то же самое, если поездной маршрут в одной стойке
  if(marshrut[fr1[nach_marsh][13]-1][0]!=0)buf_ko[2]=buf_ko[2]|8;
  vv=vibor(nach_marsh);//получить код-индекс для задания начала
  buf_ko[1]=BAM;//заполнить заголовок
  if(vv!=9999)buf_ko[4]=vv; //заполнить код-индекс для сигнала начала
  else return;
  buf_ko[3]=podgr;//установить подгруппу начала
  vv=vibor(end_marsh);//получить код-индекс для задания конца
  if(vv!=9999)  buf_ko[6]=vv; //заполнить код-индекс для сигнала конца
  else return;
	buf_ko[5]=podgr;//установить подгруппу конца
  //если задается вариантный маршрут
  if((half_marsh1>0)&&(nach0_marsh>0))
  if((fr1[end_marsh][11]&256)==256)// и для конца - есть вариантный конец
  {
    vv=vibor(half_marsh1);//получить код-индекс для вариантной точки
    if(vv!=9999)buf_ko[8]=vv;//заполнить код-индекс вариантного сигнала
    else return;
    buf_ko[7]=podgr;//заполнить подгруппу вариантного сигнала
    goto zc;
  }
  else
  {
    sbros_all();
    w(241,999,"");//нет такого вариантного маршрута
    return;
  }
  buf_ko[7]=124;//в оставшиеся байты записать заполнитель
  buf_ko[8]=124;
zc:
  buf_ko[9]=check_sum(buf_ko);//дополнить команду контрольной суммой
  buf_ko[0]='(';
  buf_ko[10]=')';
  pooo[nach_marsh]=biostime(0,0L);//зафиксировать время выдачи
  flagoutmsg=1;//выставить флаг-требование на передачу в ТУМС
}

//-----------------------------------------------------------------
//формирования команды на закрытие сигнала
void zakrsi()
{ int stit=9999,ii,jj,tk,sl,napr;
  
	nom_func("428");
        
#ifdef AVTOD
  stit=prov_avtod1(point);//проверить вхождение в автодействие
  if(stit!=-1)//если сигнал входит в маршрут установленного автодействия
  { if(stit<=1)
    {
      snyato_avto(1);//если в нечетное - снять нечетное
      zvuk_vkl(0,0);
    }
    else
      if((stit>1)&&(stit<=3))
      {
        snyato_avto(2);//если в четное - снять четное
        zvuk_vkl(0,0);
      }
    w(137,point,"автод.снято");//ПОСЫЛАЕМ КОМАНДУ НА ОТМЕНУ МАРШРУТА ОТ СИГНАЛА
  }
  else
#endif
  if (vrem==1)vrem=5;//установка признака выполнения закрытия сигнала
  if((ot==1)&&(fr3[point][0]==0)&& //если отмена и закрыт маневровый и
  (fr3[point][1]==0))//закрыт поездной
  {
    if(fr1[point][1]==0)napr=3;
    else napr=2;
    jj=point;
repit:
    stit=findspu1(jj,napr);
    if((stit==-1)&&(jj<kol_VO))
    {
      if(napr==2)jj++;
      else jj--;
      goto repit;
    }
    if(stit==-1){w(44,point," 5");return;}
    if(fr3[stit][12]==0){w(142,stit," (по типу маршрута)");oper=0;goto otm;}
    if(napr==1)//если направление сигнала четное
    {
      if((fr3[stit][12]&1)==1)mane=1;//если замыкание четное маревровое
      else
        if((fr3[stit][12]&2)==2){mane=0;manevro=0;}//если замыкание четное поездное
    }
    if(napr==0)//если направление сигнала нечетное
    {
      if((fr3[stit][12]&4)==4)mane=1;//если замыкание нечетное маревровое
      else
        if((fr3[stit][12]&8)==8){mane=0;manevro=0;}//если замыкание нечетное поездное
    }
    if(fr1[point][6]==2) //если сигнал совмещенный
    { if((manevro==1)||(mane==1)) oper='E';//если работа с маневровым сигналом
      else oper='F';//если работа с поездным
    }
    else//если сигнал не совмещенный
    if(fr1[point][2]==1)oper='F';//если поездной
    else oper='E';//если маневровый
    w(137,point,"");//ПОСЫЛАЕМ КОМАНДУ НА ОТМЕНУ МАРШРУТА ОТ СИГНАЛА
	}
  else
    if(fr3[point][0]==1)oper='E';//если открыт маневровый
    else oper='F';//если не открыт маневровый
  w(137,point,"");//ПОСЫЛАЕМ КОМАНДУ НА ОТМЕНУ МАРШРУТА ОТ СИГНАЛА
otm:
  if(ot==1)//если установлен признак "отмена"
  {
    vkl_kno(0,8);//кнопку "Отмена" на экране перекрасить в серый
    ot=0;//сбросить признак отмены
    for(ii=0;ii<skoko_stoek;ii++)
    if(komanda2[ii]==point)
    { jj=0;
      tk=komanda2[ii];
      while(1)
      {
        sl=fr3[tk][8]&0xfff;
        fr3[tk][8]=0;
        fr3[tk][10]=0;
        trassa[jj++]=tk;
        if(sl==0xfff)break;
        if((fr1[sl][13]!=9999)&&((fr1[sl][13]-1)!=ii))break;
        tk=sl;
      }
      komanda2[ii]=0;
      if(marshrut[ii][0]!=0)
      {
        marshrut[ii][0]=0;
        marshrut[ii][1]=0;
        marshrut[ii][2]=0;
			}
      ris_trassa();
      jj=0;
      while(trassa[jj]!=0xFFFF)trassa[jj++]=0xffff;
    }
  }
  clear_mouse();
  for(ii=0;ii<4;ii++){line_gor_kurs[4+2*ii]=0xff;line_gor_kurs[5+2*ii]=0xf8;}
  line_gor_kurs[0]=0xC;
  for(ii=4;ii<40;ii++)line_vert_kurs[ii]=0x80;
  line_vert_kurs[2]=8;
}
//--------------------------------------------------

