#include "bla.h"
#include "disk.h"
#include <process.h>
#include <dos.h>
#include <bios.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys\stat.h>
#include <FCNTL.H>
#include <io.h>
int SMI,ao_ar[skoko_stoek][11]={2,0,0,0,0,0,0,0,0,0,0},errorcode;
int b_day,b_h0,b_m,b_m0,b_mon,b_mon0,b_mon1,
b_s,b_s0,b_second,b_u,bb_d,bb_h,bb_m,bb_mi,bb_y,box_uk,
bq,bqq,col,dodo,dubl,durdom,ee,end_,fing,flpass,goga,hop,ismena_,no,nome,old,
opred_new,opred1,opred_old,poshag,PRICHINA_SN_AVTO[2],
sss,zahod,zapr;
unsigned char buf[skoko_stoek][11],data[30];
unsigned date, time;
unsigned long int wait();
void Disk_arc()
{
  int d,fl,errorcod,ohoho=0,iNt=0,ic,po1,po2,po3,po4,po5,po6,po7,sddf;
	long td,T2;
	char nA[4]="",dob_str[10]="";
	struct SREGS sreg;

	nom_func("37");

	DISK=0xF;
#ifndef WORK
  iNt=creat("dat\\fr3.bin",S_IWRITE|O_BINARY);
  to_chislo=kol_VO*13*2;
  write(iNt,fr3,to_chislo);
  close(iNt);
#endif
	//удаление старых записей журналов-------------------
  iNt=remove("disk\\oblom1.fix");
 	iNt=remove("disk\\oblom2.fix");
  iNt=remove("disk\\neispr1.fix");
  iNt=remove("disk\\neispr2.fix");
	iNt=remove("disk\\ogr.fr4");
	iNt=mkdir("disk");
  for(iNt=0;iNt<kol_OSN;iNt++)
  {
    fr4[iNt][0]=0;
    fr4[iNt][1]=0;
    fr4[iNt][2]=0;
  }
  disco();
  //инициализация видеосистемы ------------------------
  GraphMode=VGAHI;
  errorcode = graphresult();
  initgraph(&GraphDriver,&GraphMode,"");
  errorcode = graphresult();
  GraphMode=VGAHI;
AA:
  regs.x.ax=0x1000;// функция установки палитры
  regs.h.bl=7;
  regs.h.bh=14;
  int86(0x10,&regs,&regs);
  setbkcolor(7);
  clscreen();
/* select the user font */
  USER_FONT= registerbgifont(small_font);
	settextstyle(USER_FONT,0,4);
  //загрузка консервативных данных
	fl=open("dat\\tranc.svs",O_RDONLY|O_BINARY);
	if(fl==-1)
	{
		clrscr(); moveto(80,80);
		outtext("Не открыт файл с исходными данными tranc.svs.");
		moveto(80,160);
		outtext("Для выхода из программы нажмите любую клавишу");
		getch();
		exit(1);
	}
	formula(fl);//считывание данных для организации каналов обмена данными
	if(fl>0)close(fl);
	fl=0;
	read_lex();
  flagoutmsg=0;
  perekluch=2;
  sddf=starit();//ввод времени,поиск точки входа и "прокрутка" в памяти до точки входа
	if(sddf<0)
	{
		sddf=0;
		FINAL();
		return;
	}
repit:
	clscreen();
//  outportb(0x3c3,0);
	while((b_m1<bb_mi)||(b_h1<bb_h))
	{

		if(read_bl_box()==0)goto fdf1;
		for(iNt=0;iNt<11;iNt++){buf[0][iNt]=bu[0][iNt];buf[1][iNt]=bu[1][iNt];}
		work();
		proverka_svyazi();
	}
//  outportb(0x3c3,1);
	ZAGRUZKA=0;
	clscreen();perekluch=1;
	nach_zagruzka();//прорисовка стартовой картинки
	menu();
	perekluch=0;
	pusto = 0;
	for(ohoho=0;ohoho<20;ohoho++)data[ohoho]=0;
	if((klo==0)&&(nikuda==0)&&(help==0))
  {
	  strcpy(data," АРХИВ ЗА ");
		itoa(bb_d,dob_str,10);
		strcat(data,dob_str);
  	strcat(data,"-");strcat(data,itoa(bb_m,dob_str,10));
		strcat(data,"-");strcat(data,itoa(bb_y,dob_str,10));
		setcolor(12);outtextxy(26,16,data);setcolor(4);outtextxy(25,15,data);
	}
	first_time=biostime(0,0l);tii=first_time;i3=-1;
met0://----------------------------------------------- время
	if((klo==0)&&(nikuda==0)&&(help==0))
  {
		regs.x.ax=0x1000;// функция установки палитры
		regs.h.bl=7;
		regs.h.bh=14;
		int86(0x10,&regs,&regs);
		setbkcolor(7);
		setcolor(12);outtextxy(25,15,data);setcolor(4);outtextxy(26,16,data);

		if(pusto==0xff00)
			dr();

		if(pusto==1)
			for(ic=0;ic<kol_VO;ic++)fr3[ic][5]=1;

		prov_lX();
		tu_tc();
		kvadrat();
		knopka(KS1);
#ifdef KOL_SOO2
		knopka(KS2);
#endif
		xc=0;yc=0;
  }
kll:
	//если не был прочитан код отсутствия связи и просмотр любого журнала
	if((nikuda==1)||(klo==1)||(help==1))goto cikl;
ssl:
	PRINT_ALL(); //вывод на экран времени,стартового символа и текста сообщения
	work(); //обработка архивной строки (команда или сообщение)
	proverka_svyazi();
fdf1:
	outportb(0x3c3,1);
  opred_old=opred;
  //чтение следующей строки архива и вычисление задержки
  if(der()==-1){FINAL();goto AA;}//$$
  opred_new=opred;
  opred=opred_old;
  if((pusto&3)!=0)//если была потеря связи
	{ if(klo==1) kartina();
		else  if(nikuda==0&&help==0)  zagruzen();
		w(138,999,"");//ОТСУТСТВУЕТ СВЯЗЬ С МПСУ
	}
  T2=biostime(0,0l);
cikl:
	if(cikl_obnov>=kol_VO)cikl_obnov=0;
  if((klo==0)&&(nikuda==0))
  {
	  prorisovka=1;
  	if(obnov<5)
	  {
		  switch(fr1[cikl_obnov][0])
  		{
				case 1: displaystrelka(cikl_obnov,obnov,0);break;
				case 3: sekci(cikl_obnov,obnov);break;
  		  case 2: if(fr1[cikl_obnov][1]==13)komplekt(cikl_obnov,obnov);
    		        else  displaysignal(cikl_obnov,obnov);
      		      break;
		    case 4: displaypathuch(cikl_obnov);break;
  		  case 5: displaypath(cikl_obnov,obnov);break;
    		default:break;
		  }
  	}
  	obnov++;
  	if(obnov==100){obnov=0;cikl_obnov++;}
  	prorisovka=0;
  }
  if(kbhit()||(poshag==1))//если нажата клавиша
  {
		if(keykey()==-1){FINAL();return;}
    if(ismena_==1)//если изменена точка входа в архив
    {
      ismena_=0;
      FINAL();
      goto AA;
    }
    if((poshag==1)&&(klaval!=13))goto cikl;
  }
  else
  {
  	if(klo==1)card();
    else
     if(nikuda==1)read_neisprav();
  }
  if(tormoz==0)goto fdf;
  if((klo==0)&&(nikuda==0)&&(help==0))
  {
	  if(tormoz>0)//цикл задержки на разницу времени строк архива
  	{ tst_zvuk();
    	td=biostime(0,0l);
	    sss++;
  	  if(sss==10)
    	{
   			setfillstyle(1,7);bar(35,26,99,36);moveto(35,26);
	   		setcolor(1);
 				Printf(b_h1,b_m1,b_s1);
    	  sss=0;
	    }
  	  if((td-T2)>=tormoz) tormoz=0;
    	goto cikl;
	  }
  }
fdf:
  opred=opred_new;
  b_h0=b_h1; b_m0=b_m1; b_s0=b_s1;
  for(iNt=0;iNt<=10;iNt++)buf[0][iNt]=bu[0][iNt];
fdf2:
  col=3;
  goto met0;
}
//----------------------------------------------------------------
analiz(int gog)
{
  
	nom_func("5");
  
  switch(gog)
  { case 131: STATUS=1;slom_interf(7400);//"Г"
              if(perekluch!=2){ispr_pvm(0,0);ispr_pvm(0,NEISPRAVEN);}
              break;
		case 132: STATUS=0;slom_interf(7500);//"Д"
              if(perekluch!=2){ispr_pvm(0,0);ispr_pvm(0,NEISPRAVEN);}
              break;
    case 134: STATUS=2;slom_interf(7600); //Ж
              if(perekluch!=2){ispr_pvm(0,0);ispr_pvm(0,NEISPRAVEN);}
              break;
		case 'S': slom_interf(9000);w(174,999," ПЕРЕЗАГРУЗКА");pusto=0;break;
    case 175: otkaz_ts[0]=0;break;//"п"
    case 162: otkaz_ts[1]=0;break;//"в"
    case 15: gog=gog;
              break;

    case 'A': otkaz_ts[0]=1;slom_interf(7000);pusto=pusto|1;break;
    case 'a': otkaz_ts[1]=1;slom_interf(7001);pusto=pusto|2;break;

    case 'B': otkaz_tu[0]=1;slom_interf(7010);break;
    case 'b': otkaz_tu[1]=1;slom_interf(7011);break;

    case 'C': zapret[0]=zapret[0]|0x8000;slom_interf(7020);break;
    case 'c': zapret[1]=zapret[1]|0x8000;slom_interf(7021);break;

    case 'E': otkaz_ts[0]=0;slom_interf(7050);pusto=pusto&0xfffe;break;
    case 'e': otkaz_ts[1]=0;slom_interf(7051);pusto=pusto&0xfffd;break;

    case 'F': otkaz_tu[0]=0;slom_interf(7060);break;
    case 'f': otkaz_tu[1]=0;slom_interf(7061);break;

    case 'D': zapret[0]=zapret[0]&0x7fff;slom_interf(7070);break;
    case 'd': zapret[1]=zapret[1]&0x7fff;slom_interf(7071);break;
    // отказ ТС соседней
    case 'Q': otkaz_sos[0]=1;slom_interf(7070);NEISPRAVEN=0;break;
    case 'q': otkaz_sos[1]=1;slom_interf(7070);NEISPRAVEN=0;break;
    // отказ ТУ соседней
    case 'R': slom_interf(7010);otkaz_tu_sos[0]=1;break;
    case 'r': slom_interf(7011);otkaz_tu_sos[1]=1;break;
		// восст ТС соседней */
    case 'U': slom_interf(7150);otkaz_sos[0]=0;break;
    case 'u': slom_interf(7151);otkaz_sos[1]=0;break;
    // восст ТУ соседней */
    case 'V': otkaz_tu_sos[0]=0;slom_interf(7160);break;
    case 'v': otkaz_tu_sos[1]=0;slom_interf(7161);break;

    case 'X': slom_interf(7300);NEISPRAVEN=1;break;
    case 'x': slom_interf(7200);NEISPRAVEN=0;break;

    case 158: slom_interf(7701); break;//Ю
    case 238: slom_interf(7700); break;//ю

    case 'J': NEISPRAVEN=0;break;
    case 'j': NEISPRAVEN=0;break;
    case '-': NEISPRAVEN=0;break;
    default:  break;
  }
}
//---------------------------------------------
int der()
{

	nom_func("35");

  b_u=box_uk;
  b_h0=b_h1;
  b_m0=b_m1;
  b_s0=b_s1;
  opred=read_bl_box();
  if(opred==0)
  { music1();
    ramka(15,15,51,18); moveto(16*7,16*7);
		outtext(" ДАННЫЕ ФАЙЛА АРХИВА ИСЧЕРПАНЫ! ");
		getch();
		return(-1);
	}
	if((opred!='>')&&(opred!='<'))flagoutmsg=0;
	else flagoutmsg=1;
	tormoz=wait()/to_chislo;
	if(tormoz>1000l)tormoz=0;
	box_uk=b_u;
	return(0);
}
//--------------------------------------------------
void ismena()
{
	nom_func("111");

  ismena_=1;
  return;
}
//---------------------------------------------------
int keykey()
{
  int out;

	nom_func("119");

  klaval=getch();
	if(flag_paro!=0)
	{
		read_passw();
		return(0);
	}
  if(klaval==27)return(0);
  if(klaval==32)
  {
		if((nikuda==0)&&(help==0)&&(klo==0))t(0);
    okno_otkaz=0;
    return(0);
  }
vx:
  if((klaval==0)||(klaval==27))out=vyborklav();
  if(out==-1)return(-1);
  return(0);
}
//-------------------------------------------------
void music1()
{
  int i;

	nom_func("176");

  for(i=0;i<4;i++){sound(600);delay(50);nosound();sound(1000);delay(70);nosound();}    
}
//--------------------------------------------------
int POISK()
{ long len_file,delta,delta0,ij;
  int minut,min,chas,sek,ik;
  char tq[3]="",opr[10]="";

	nom_func("229");

  opred=0;
  len_file=filelength(box_uk);
  minut=bb_h*60+bb_mi-12;
  if(minut<0)minut=0;
  chas=minut/60;min=minut%60;delta0=len_file/2;delta=delta0;
  while(1)
  { ij=lseek(b_u,delta,0);
		while(opred!=13)read(b_u,&opred,1);
    read(b_u,&opr,10);opred=0;
    for(ik=0;ik<2;ik++)tq[ik]=opr[ik+1];
    tq[ik]=0;chas=atoi(tq);
    for(ik=0;ik<2;ik++)tq[ik]=opr[ik+4];
    tq[ik]=0;min=atoi(tq);
    if(abs(chas*60+min-minut)<=1)
    { for(ik=0;ik<2;ik++)tq[ik]=opr[ik+7];
      tq[ik]=0;sek=atoi(tq);
			b_day=bb_d;b_mon=bb_m;
      b_h0=chas;b_m0=min;b_s0=sek;
      return(0);
    }
    delta0=delta0/2;
    if(chas*60+min<minut)delta=delta+delta0;
    if(chas*60+min>minut)delta=delta-delta0;
    if(delta0<2)
    { delta=tell(b_u);
      if(chas*60+min<minut||tell(b_u)<40L)return(1);
      else return(2);//точка входа не найдена
    }
    strcpy(opr,"");
  }
}
//------------------------------------------
void PRINT_ALL()
{
  int gogi=0,i,i1;
  char soobs[12]="",gog[2];

	nom_func("235");

  setfillstyle(1,cvv);setcolor(1);
  bar(35,26,180,36);moveto(35,26);
  Printf(b_h0,b_m0,b_s0);//вывод на экран текущего времени
  ho_ur=b_h0;mi_n=b_m0;se_c=b_s0;//копирование времени для ведения журнала
  gog[0]=opred;gog[1]=0;
  moveto(100,26);
  if(gog[0]==0||gog[0]==13)gog[0]=32;
  outtext(gog);//вывод символа
  if((opred==175)||(opred==162)||(opred=='<')||(opred=='>')||(opred=='S')||
  (opred==15)||(opred=='='))
  {
    soobs[11]=0;
    if(opred=='=')
    flagoutmsg=1;
    for(i1=0;i1<11;i1++)soobs[i1]=bu[0][i1];
    outtext(soobs);
  }
  if(gogi=='$')
  {moveto(5,26);outtext("ПЕРЕВОД ВРЕМЕНИ");delay(3000);}
  analiz(opred);
//  if(zapret[0]==1) zapret_TU(0);
//  if(zapret[1]==1) zapret_TU(1);
//  if(otkaz_tu[0]==1) otkaz_TU(0);
//  if(otkaz_tu[1]==1) otkaz_TU(1);
//  if(zapret[0]==0&&otkaz_tu[0]==0) razr_TU(0);
//  if(zapret[1]==0&&otkaz_tu[1]==0) razr_TU(1);
//if(gogi=='S')
//{
//if(fr4[kol_OSN][0]==1)
//{
//  na=1;
//  vkl_kno(NANA,10);
//  for(i=0;i<N_str;i++)otkl_(N_strel[i]);
//}
//else vkl_kno(NANA,8);
//if(fr4[kol_OSN][1]==1)
//{
//  cha=1;
//  vkl_kno(CHACHA,10);
//  for(i=0;i<CH_str;i++)otkl_(C_strel[i]);
//}
//else  vkl_kno(CHACHA,8);
//}
  if(klo==1)
	kartina();
  else
  {
//    tu_tc();
    ispr_pvm(0,0);
    ispr_pvm(1,NEISPRAVEN);
  }
}
//----------------------------------------------------------------
void Printf(int g4,int g5,int g6)
{
	int e=0;
	char AAq[5]="";

	nom_func("237");

	setcolor(1);
	itoa(g4,AAq,10);if(g4<10) outtext("0");outtext(AAq);outtext(":");
	itoa(g5,AAq,10);if(g5<10) outtext("0");outtext(AAq);outtext(":");
	itoa(g6,AAq,10);if(g6<10) outtext("0");outtext(AAq);outtext(" ");
}
//--------------------------------------
void prodol1()
{
  
	nom_func("240");
        
  if (vrem==5) uprav=1;
  setcolor(3);
  if(perekluch==1) poka=0;
  i3=-1;
  menu();
  setfillstyle(SOLID_FILL,cvv);
  setcolor(11);
  if(poshag==0)
  {bar(40,40,170,50); moveto(40,40);   outtext("АВТОМАТИЧ. РЕЖИМ "); }
  else
  {bar(40,40,170,50); moveto(40,40);outtext("ПОШАГОВЫЙ  РЕЖИМ ");}
}
//---------------------------------------------------------------
void ramka(int x1,int y1,int x2,int y2)
{
	int j;

	nom_func("260");

	setfillstyle(SOLID_FILL,8);
	bar(x1*7,y1*7,x2*7,y2*7);
	setcolor(WHITE);
	setlinestyle(0,0,0);
	rectangle(x1*7+2,y1*7+2,x2*7-2,y2*7-2);
	rectangle(x1*7+4,y1*7+4,x2*7-4,y2*7-4);
	if(x1<10)
  {
    setfillstyle(SOLID_FILL,8);
    bar(x1*7+30*7+10,y2*7-10,x1*7+30*7+20+115,y2*7);
    moveto(x1*7+30*7+20,y2*7-10);
    setcolor(11);
    outtext("'Esc' - выход");
  }
}
//--------------------------------------------------------------
int read_bl_box()
{
  int i,fls,ik,ogr=0;
  unsigned long int pozic;
  unsigned char symbos,ss[3],tq[3],opr[25];

	nom_func("265");

  read(b_u,&opred1,1);symbos=opred1;//прочитать один символ
oba:
  while(eof(b_u)!=1)//если не достигнут конец файла
  { //чтение времени
povtor:
    if(symbos==13)read(b_u,&opr,9);//если конец строки,прочитать 9 символов
    else//если это не конец строки
    { while(symbos!=13&&eof(b_u)==0)read(b_u,&symbos,1);//искать конец строки или конец файла
      read(b_u,&opr,10);//прочитать 10 символов
    }
    //чтение символа за временем
    read(b_u,&symbos,1);
    while(symbos==' ')read(b_u,&symbos,1);//поиск символа не пробела
    if(symbos=='Д'){STATUS=0;goto povtor;}
    if(symbos=='Г'){STATUS=1;goto povtor;}
    if(symbos=='b')
    i=1;
    //перевести в целый формат параметры для времени
    for(ik=0;ik<2;ik++)tq[ik]=opr[ik+1]; b_h1=atoi(tq);
    for(ik=0;ik<2;ik++)tq[ik]=opr[ik+4]; b_m1=atoi(tq);
    for(ik=0;ik<2;ik++)tq[ik]=opr[ik+7]; b_s1=atoi(tq);
    //анализ символа идентификатора
    //175="п" - информация из первой стойки
    //162="в" - информация из второй стойки
    //"<" - команда
    //">" - ограничение на объект
    //S - начало работы после перезагрузки программы
    if((symbos==175)||(symbos==162)||(symbos=='<')||(symbos=='>')||
    (symbos=='S')||(symbos=='='))
    { read(b_u,&bu[0],11);//чтение данных
      //если формат не правильный,то вернуться
      if((bu[0][10]!=')')&&(bu[0][10]!='+'))goto povtor;
      if(symbos=='S')
      { fr4[kol_OSN][0]=0; fr4[kol_OSN][1]=0; disco();
        na=0; cha=0;
#ifdef AVTOD
        vkl_kno(NANA,8);vkl_kno(CHACHA,8);
#endif
      }
      pozic=lseek(b_u,0,1);//запомнить позицию
      read(b_u,&opr,2);
      read(b_u,&opr,8);
      //перевести в целый формат параметры для времени
      for(ik=0;ik<2;ik++)tq[ik]=opr[ik]; tq[ik]=0; b_h1=atoi(tq);
      for(ik=0;ik<2;ik++)tq[ik]=opr[ik+3]; tq[ik]=0; b_m1=atoi(tq);
      for(ik=0;ik<2;ik++)tq[ik]=opr[ik+6]; tq[ik]=0; b_s1=atoi(tq);
      lseek(b_u,pozic,0);
      return(symbos);
    }
    else
      if(symbos==15)
      {
        read(b_u,&opr,6);
        i=((0xf0&(~opr[2]))>>4)*1000;
        i=i+(0xf&(~opr[2]))*100;
        i=i+((0xf0&(~opr[1]))>>4)*10;
        i=i+(0xf&(~opr[1]));
        fr4[i][0]=opr[3]&0x7f;
        if(fr1[i][0]==1)//если стрелка
        {
          if((fr4[i][0]&2)==2)
          {
            cha=1;
            vkl_kno(CHACHA,10);
          }
          if((fr4[i][0]&4)==4)
          {
            na=1;
            vkl_kno(NANA,10);
          }
        }
        ogr=opr[4]&1;
        if(ogr==1)fr4[i][1]=1;
        else fr4[i][1]=0;
        ogr=opr[4]&2;
        if(ogr==2)fr4[i][2]=1;
        else fr4[i][2]=0;

      }
      else return(symbos);
  }
  return(0);//дошли до конца файла
}
//------------------------------------------------------------
int Scan(int ik,int ig,int Maxim)
{ int I=0,iks=0,i;
  char sloo[8]="",sluo[8]="",ch[2]="";

	nom_func("295");

  I=0;iks=ik;moveto(iks,ig);
  while(ch[0]!=13)
  { if(I>5){setfillstyle(SOLID_FILL,8);bar(ik,ig,ik+56,ig+8);return(-1);}
    ch[0]=getch();
    if(ch[0]==27)return(-2);
    if(ch[0]==0){getch();setfillstyle(SOLID_FILL,8); bar(ik,ig,ik+56,ig+8);return(-1);}
    if(ch[0]==13){sloo[I]='*';break;}
    if(ch[0]==8)
    { if(I>0)
      { iks=iks-8;setfillstyle(SOLID_FILL,8);
        bar(iks,ig,iks+8,ig+8);
        moveto(iks,ig);
        sloo[I]='*';
        I--;
      }
      goto enn;
    }
    if(!isdigit(ch[0]))
    {setfillstyle(SOLID_FILL,8);bar(ik,ig,ik+8*7,ig+8); return(-1);}
    moveto(iks,ig);outtext(ch);sloo[I]=ch[0];iks=iks+8;I++;
enn:;
  }
  if(I<0){setfillstyle(SOLID_FILL,8);bar(ik,ig,ik+8*7,ig+8);return(-1);}
  i=0;
  while(sloo[i]!='*'){sluo[i]=sloo[i];i++;}
  I=atol(sluo);
  if((I>Maxim)||(I<0))return(-2);
  return(I);
}
//------------------------------------------------------
void spisok_prikazov()
{
  int bz1,bz2,bb,n,nn,nnn,kol,nil,i,spara,ura,uu,STR,UCH,PUT,SIG,UPR,ST;
  char slv[10]="";
  unsigned char kim;

	nom_func("316");

  /******** обычные сигналы ***************/
  if(buf[0][1]=='Z')
  goto Z;
  kim=buf[0][1]&0x40;
  if(kim!=0x40) return;
  kim=buf[0][1]&0x02;
  if(kim!=2) kim=1;
signal:
  if(buf[0][2]=='E')
  { if(kim==2){SIG=SIG2;ST=SIG1;SMI=STR2;}
    else{SIG=SIG1;ST=0;SMI=STR1;}
    for(i=SMI+ST;i<SIG+SMI+ST;i++)
    if(buf[0][3]==podgruppa[i-ST])nn=i-SMI;
    else if(i>=SIG+SMI+ST) return;
    for(i=4;i<=8;i++)
    if(buf[0][i]!=124&&buf[0][i]!='@')n=i-4;
    else if(i>8) return;
    nnn=spsig[nn][n];
    if(fr1[nnn][13]==1)t_com[0]=biostime(0,0l);
    else t_com[1]=biostime(0,0l);
    if(nnn<kol_OSN&&fr1[nnn][8]!=666)
    { if(buf[0][n+4]=='A'||buf[0][n+4]=='B')
			w(132,nnn,"");//выдана команда на открытие сигнала
      else
        if(buf[0][n+4]=='F'||buf[0][n+4]=='E')
        w(137,nnn,"");//выдана команда на отмену маршута от сигнала
        else return;
      return;
    }
    else
    {
    /******** смена обычная ************/
      if(fr1[nnn][8]==666)
      { if(buf[0][n+4]=='A'||buf[0][n+4]=='B')
        {w(2,999,otopri[fr1[nnn][10]]);}
        //ВЫДАНА КОМАНДА СОГЛАСИЯ НА ОТПРАВЛЕНИЕ
        return;
      }
      else
      {  /******** смена вспомогательная ************/
         if(fr1[nnn][1]>=400&&fr1[nnn][1]<=600)
         {  if(fr1[nnn][3]==1&&(buf[0][n+4]=='X'||buf[0][n+4]=='T'))
            { if(buf[0][n+4]=='X')
              {w(11,999,"НА ПРИЕМ ");outtext(otopri[fr1[nnn][11]]);}
              else
              {w(11,999,"НА ОТПРАВЛ. ");outtext(otopri[fr1[nnn][12]]);}
              return;
            }
            if(fr1[nnn][3]==2)
            { if(buf[0][n+4]=='X')w(9,999,otopri[fr1[nnn][11]]);
              else
                if(buf[0][n+4]=='T')w(10,999,otopri[fr1[nnn][12]]);
							return;
            }
          }
          else
          { switch(fr1[nnn][1])
            { case 17:  bz1=fr1[nnn][2]; /*rm*/
                        bz2=fr1[nnn][7]; /*zm*/
                        bb=fr1[bz1][11];
                        if(buf[0][n+4]=='A')
                        {
                          if(fr3[bz1][bb]==0&&fr3[bz2][bb]==0) w(36,999,"");
                          else w(31,999,"");
                        }
                        else
                        {
                          if(fr3[bz1][bb]==1&&fr3[bz2][bb]==1) w(30,999,"");
                          else w(37,999,"");
                        }
                        return;
              case 16: /* любые кнопки */
                        if(buf[0][n+4]=='A'||buf[0][n+4]=='B') w(fr1[nnn][3],999,"");
                        else  w(fr1[nnn][4],999,"");
                        if(fr1[nnn][2]==33)outtext(otopri[fr1[nnn][7]]);
                        return;
              case 166: /* смена кнопка где есть один комплект */
                        if(buf[0][n+4]=='A'||buf[0][n+4]=='B')
                        { if(fr3[fr1[nnn][2]][0]==1)w(2,999,otopri[fr1[nnn][3]]);
                          else
                            if(fr3[fr1[nnn][2]][1]==1)w(2,999,otopri[fr1[nnn][4]]);
                        }
												return;
              case 66:  if(markery[fr1[nnn][12]][7]==333)
                        { if(buf[0][n+4]=='A') w(25,999,"");
                          else w(24,999,"");
                        }
                        return;
              case 67:  if(markery[fr1[nnn][12]][7]==333)
                        { if(buf[0][n+4]=='B') w(25,999,"");
                          else w(24,999,"");
                        }
                        return;
              case 76:  if(markery[fr1[nnn][12]][7]==333)
                        { if(buf[0][n+4]=='A') w(25,999,"");
                          else w(24,999,"");
                        }
                        return;
              case 77:  if(markery[fr1[nnn][12]][7]==333)
                        { if(buf[0][n+4]=='B') w(25,999,"");
                          else w(24,999,"");
                        }
                        return;
              default:  return;
            }
          }
        }
      }
    }
    //маршруты----------------------------------
    if(buf[0][2]=='a'||buf[0][2]=='b')
    { if(kim==2){SIG=SIG2;ST=SIG1;SMI=STR2;}
			else {SIG=SIG1;ST=0;SMI=STR1;}
      n=buf[0][4]-64;
      for(i=SMI+ST;i<SIG+SMI+ST;i++)
      if(buf[0][3]==podgruppa[i-ST]) nnn=i-SMI;
      else if(i>=SIG+SMI+ST) return;
      nn=spsig[nnn][n];
      w(132,nn,"-марш.");
      pooo[nn]=biostime(0,0l);
      return;
    }
    /****** разделка + ГРИ *******************/
F:  if(buf[0][2]=='F')
    { if(kim==2){UCH=UCH2;ST=UCH1;SMI=STR2+SIG2;}
      else {UCH=UCH1;ST=0;SMI=STR1+SIG1;}
      for(i=SMI+ST;i<UCH+SMI+ST;i++)
      if(buf[0][3]==podgruppa[i-ST]) nn=i-SMI;
      else  if(i>=UCH+SMI+ST) return;
      for(i=4;i<=8;i++)
        if(buf[0][i]!=124&&buf[0][i]!='@') n=i-4;
        else if(i>8) return;
      nnn=spspu[nn][n];
      if(buf[0][10]=='+')
      { ura=buf[0][n+4]&0x04;
        if(ura==0x04){fr4[nnn][2]=1;w(115,nnn,"");}
        else {fr4[nnn][2]=0;w(114,nnn,"");}
				displaypathuch(nnn);
        disco();
      }
      else
      { if(fr1[nnn][1]==301)
				{ w(19,999,"");
          fr3[nnn][9]=9;
          return;
        }
        else
        { if(fr1[nnn][1]>200)
          {
            if(fr3[nnn][0]==0)w(11,nnn," НА ИСК. РАЗМ.");
            else w(18,nnn," ПО");
            fr3[nnn][9]=9;
            return;
          }
          else
          {
            ura=buf[0][n+4]&0x04;
            if(ura==0x04){fr4[nnn][2]=1;w(115,nnn,"");}
            else {fr4[nnn][2]=0;w(114,nnn,"");}
            displaypathuch(nnn);
            disco();
          }
        }
      }
    }
    /********* стрелки *************************/
C:  if(buf[0][2]=='C')
    { if(kim==2){STR=STR2;ST=STR1;SMI=0;}
      else {STR=STR1;ST=0;SMI=0;}
      for(i=SMI+ST;i<STR+SMI+ST;i++)
      if(buf[0][3]==podgruppa[i-ST]) nn=i;
      else if(i>=STR+SMI+ST) return;
			for(i=4;i<=8;i++)
      if(buf[0][i]!=124&&buf[0][i]!='@') n=i-4;
      else if(i>8) return;
      nnn=spstr[nn][n];
      if(buf[0][10]=='+')
      {
qwe:    ura=buf[0][n+4]&0x01;
        if(ura==1) fr4[nnn][0]=1;
        else fr4[nnn][0]=0;
        ura=buf[0][n+4]&0x02;
        if(ura==0x02) fr4[nnn][1]=1;
        else fr4[nnn][1]=0;
        ura=buf[0][n+4]&0x04;
        if(ura==0x04) fr4[nnn][2]=1;
        else fr4[nnn][2]=0;
        nach_zakr(nnn,1);
        if(fr1[nnn][12]!=9999&&spara==0)
        { TEST=2;
					nnn=poisk_ras(fr1[nnn][2],fr1[nnn][12]);
          if(nnn!=9999){spara=1;goto qwe;}
        }
        spara=0;
        vkl_kno(MAKET,8);
        disco();
      }
      else
      { ura=buf[0][n+4]&0x01;
        if(ura==0x01){hop=3;w(123,nnn,"");hop=0;}
        else {hop=4;w(123,nnn,"");hop=0;}
      }
			return;
    }
I:  if(buf[0][2]=='I'&&buf[0][10]==')')
    { if(kim==2){PUT=PUT2;ST=PUT1;SMI=STR2+SIG2+UCH2;}
      else {PUT=PUT1;ST=0;SMI=STR1+SIG1+UCH1;}
      for(i=SMI+ST;i<PUT+SMI+ST;i++)
      if(buf[0][3]==podgruppa[i-ST])nn=i-SMI;
      else
        if(i>=PUT+SMI+ST) return;
      for(i=4;i<=8;i++)
      if(buf[0][i]!=124&&buf[0][i]!='@')n=i-4;
      else
        if(i>8) return;
      nnn=spputi[nn][n];
      ura=buf[0][n+4]&0x04;
      if(ura==0x04){fr4[nnn][2]=1;w(115,nnn,"");}
      else {fr4[nnn][2]=0;w(114,nnn,"");}
			displaypath(nnn,0);
      disco();
    }
Z:
#ifdef AVTOD
    switch(buf[0][2])
    {

      case 'A': if(buf[0][3]=='@'){na==0;cha=0;}
                else
                  if(buf[0][3]=='A'){na=1;cha=0;}
                  else
                    if(buf[0][3]=='B'){na=0;cha=1;}
										else
                      if(buf[0][3]=='C'){na=1;cha=1;}
                if(na==1)
                { for(uu=0;uu<N_str;uu++)otkl_(N_strel[uu],1);
                  if(cha==1)w(91,999," И ПО 2П");
                  else w(91,999,"");
                }
                else
                {
                  for(uu=0;uu<N_str;uu++)vkl_(N_strel[uu],1);
                  if(cha==0)w(265,999," ПО 1П И 2П");
                  else w(265,999," НЕЧЕТНОЕ");
                }
                if(cha==1)
                {
                  for(uu=0;uu<CH_str;uu++)otkl_(C_strel[uu],0);
                  if(na==1)w(90,999," И ПО 1П");
                  else w(90,999,"");
                }
                else
                {
                  for(uu=0;uu<CH_str;uu++)vkl_(C_strel[uu],0);
                  if(na==0)w(265,999," ПО 1П И 2П");
                  else w(265,999," ЧЕТНОЕ");
                }
                if(na==1)vkl_kno(NANA,10);
                else vkl_kno(NANA,8);
                if(cha==1)vkl_kno(CHACHA,10);
                else vkl_kno(CHACHA,8);
                break;
			default:return;
    }
#endif
		return;
 L:
	if(buf[0][2]=='L')
	{ if(kim==2)
		{ if(buf[0][2]=='L'&&buf[0][3]=='K')
			if(buf[0][5]=='D') slom_interf(11201);
		}
		else
		{ if(buf[0][2]=='L'&&buf[0][3]=='V')
			if(buf[0][5]=='D') slom_interf(11200);
		}
		w(41,999,"");
	}
	return;
}
//----------------------------------------------------------
int starit()
{
	int xcx,i,j,dd=0, dm=0, dy=0;
	char name_file[25],d_str[10];

	nom_func("317");

	for(i=0;i<25;i++)name_file[i]=0;

qwqw:
	dubl = 0;
	cleardevice();
	ramka(1,9,79,28);
d2:

	if(dd==-2)return(-2);

	moveto(20,80);
	outtext("Введите дату: число - ");
	dd=Scan(170,80,31);

	if((dd<1)||(dd>31))
	{
		putch(7);
		bar(170,80,180,90);
		goto d2;
	}
	bb_d=dd;
d3:


	if(dm==-2)return(-2);
	moveto(20,88);
	outtext("              месяц - ");
	dm = Scan(170,88,12);

	if((dm<1)||(dm>12))
	{
		putch(7);
		bar(170,88,200,98);
		goto d3;
	}
	bb_m = dm;

d4:
	if(dy == -2)return(-2);
	moveto(20,96);
	outtext("                год - ");
	dy = Scan(170,96,2100);
	if(dy<100)dy=2000+dy;

	if((dy>2100)||(dy<2000))
	{
		putch(7);
		bar(170,96,210,106);
		goto d4;
	}
	bb_y=dy;

	strcpy(name_file,"result\\");
	itoa(bb_d,d_str,10);
	if(bb_d<10)strcat(name_file,"0");
	strcat(name_file,d_str);
	itoa(bb_m,d_str,10);

	if(bb_m<10)strcat(name_file,"0");
	strcat(name_file,d_str);
	strcat(name_file,".ogo");
again:
	box_uk=open(name_file,O_RDWR|O_BINARY);
	na=_dos_getftime(box_uk,&date,&time);
	date=(date>>9)+1980;
	if((bb_y!=date)||box_uk<0)
  {
    moveto(20,165);setcolor(12);
    outtext("Информации на указанную дату нет, для продолжения нажмите <Enter>");
    if(getch()==13)goto qwqw;
  }
d11:
  dayy_=bb_d;monn_=bb_m;yearr_=bb_y;
	moveto(20,104);  outtext("Введите коэф.ускорения (1-18) ");
	moveto(270,104);outtext("18-максимум скорости,1-реальная");
	dd = Scan(250,104,18);
	if((dd<1)||(dd>18)){putch(7);bar(250,104,260,114);goto d11;}
	to_chislo = dd;
d5:
	if(dd==-2)return(-2);
	moveto(20,112);outtext("Введите время: часы  - ");dd=Scan(170,112,23);
	if(dd<0){putch(7);bar(170,112,200,122);goto d5;}
	bb_h=dd;
d6:
	if(dd==-2)return(-2);
	moveto(20,120);outtext("             минуты - ");dd=Scan(170,120,59);
	if(dd<0){putch(7);bar(170,120,180,150);goto d6;}
	bb_mi=dd;
	b_u=box_uk;
	if(POISK()>1)
	{
		putch(7);moveto(50,168); setcolor(LIGHTRED);
		outtext(" ДАННЫЕ НЕ НАЙДЕНЫ, ПОПРОБУЙТЕ ИЗМЕНИТЬ ВРЕМЯ, ЕЩЕ РАЗ? (y/n)");
wqwq:
		xcx=getch();
		if(xcx=='y'){if(box_uk>0)close(box_uk);box_uk=0;goto qwqw;}
		else
		{
			if(xcx=='n'){FINAL();return(-1);}
			else goto wqwq;
		}
	}
	else box_uk=b_u;
	read_bl_box();
	return(0);
}
//----------------------------------------------------------
int vyborklav()
{ int a,col,vi=0,vj=0,driver,mode,errorcode;

	nom_func("406");

  if(klaval==0){a=getch();t(0);}
  if(klaval!=0)return(0);
  if((nikuda==0)&&(klo==0)&&(help==0))
  {
a12:
    switch (a)
		{ case 68:  if(b_u>0)errorcode=close(b_u);
								b_u=0;
								FINAL();
                return(-1);;

      case 67:  if(podsvetka==0) podsvetka=1;//подсветка F9
                else podsvetka=0;
                pict_podsvetka();
                return(0);

      case 60 : return(0);//F2

hel:  case 61 : return(0);//F3

as:   case 62 : nosound();bq=0;bqq=0;return(0);//выключить звук F4

      case 63 : if((flag_paro==0)&&(nikuda==0)&&
                (klo==0)&&(help==0))//неисправности СЦБ F5
                {
                  poshag=0;
                  flag_paro=1;strcpy(password,"");
                  w(118,999,"");//ВВЕДИТЕ ПАРОЛЬ
                }
                return(0);

as2:  case 64 : if((flag_paro==0)&&(nikuda==0)&&
                (klo==0)&&(help==0))//неисправности интерфейса F6
                {
                  poshag=0;
                  flag_paro=2;strcpy(password,"");
                  w(118,999,"");//ВВЕДИТЕ ПАРОЛЬ
                }
                return(0);

shp:  case 65 : //изменение точки входа F7
								if((nikuda==1)||(klo==1))return(0);
								ismena();
								if (tst==2) uprav=1;
								else uprav=0;
								return(0);

shsh:  case 66: //переключение Пошаговый - Автоматический
								setfillstyle(SOLID_FILL,cvv);setcolor(11);
								if(poshag==1)
								{ poshag=0;bar(40,40,170,50);
									moveto(40,40);outtext("АВТОМАТИЧ. РЕЖИМ     ");
								}
								else
								{ poshag=1;bar(40,40,170,50);
									moveto(40,40);outtext("ПОШАГОВЫЙ  РЕЖИМ     ");
								}
								return(0);

			case 59 : return(0);

			default: return(0);
		}
	}
	else
	if(nikuda==1)
	{
//	 if(klaval!=0)return;
//		else klaval=getch();
		switch(a)
		{
			case  63: nikuda=0;
								if(tst==2)uprav=1;
								else uprav=0;
								if(n_1>0)close(n_1);n_1=0;
								if(n_2>0)close(n_2);n_2=0;
								end_help();
								sbros_all();
								BEG_TIM[0]=0;
								return(0);
			case  81: bil_bil=1;
								iqw=56;
                klaval=a;
								read_neisprav();
								return(0);
			case 73:	bil_bil=2;
								iqw=56;
                klaval=a;
								read_neisprav();
								return(0);
			default:  return(0);
		}
	}
  else
  if(klo==1)
  {
    switch (a)
    {
as3:  case 64 : klo=0;goga=0;
                if (tst==2) uprav=1;
                else uprav=0;
                perekluch=1;clscreen();setbkcolor(cvv);
                nachalo(); prodol1();perekluch=0;klo=0;
                klaval=-1;
                return(0);
as4:  case 81 : bil_bil=1;
								klaval=a;
								card();
                return;

      case 73 : bil_bil=2;
								klaval=a;
								card();
                return(0);
      default:  return(0);
    }
  }
  return(0);
}
//--------------------------------------------------------------
unsigned long int wait()
{
  unsigned long int t1=0l,t2=0l,tt=0l;

	nom_func("408");

  t1=(b_h1*3600l)+(b_m1*60l)+b_s1;
  t2=(b_h0*3600l)+(b_m0*60l)+b_s0;
  tt=(t1-t2)*18L;
  if(poshag==1)tt=0l;
  return(tt); // тиков между сообщениями
}
//-------------------------------------------------------------
void work()
{
  int ij,knl;
  
	nom_func("423");

  if(buf[0][1]&0x02==2)knl=1;
  else knl=0;
  for(ij=0;ij<11;ij++)bu[knl][ij]=buf[0][ij];
  if(flagoutmsg==0)obrabotka_inf(knl);
  else {spisok_prikazov();flagoutmsg=0;}
}
//------------------------------------------------------------------
void FINAL()
{
	int hndl;

	nom_func("56");

  nosound();
	if(box_uk>0)close(box_uk);
	if(b_u==box_uk)b_u=0;
	box_uk=0;
	if(file_soob>0)close(file_soob);
	file_soob=0;
#ifndef WORK
  hndl=open("dat\\fr3.bin",S_IWRITE|O_BINARY);
  to_chislo=kol_VO*13*2;
  read(hndl,fr3,to_chislo);
  close(hndl);
#endif
	return;
}
