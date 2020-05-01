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
main()
{
	int a,b,iNt,ohp,ohoho,fp,i_close,ic,errorcode,ii,fl,test_tmp;
	int driv,ik,test_baz[15];
	char d_0,d_1,m_0,m_1,lstr[4];
	struct dosdate_t dat;

	regs.x.ax=0; //убрать изображение курсора
	int86(0x33,&regs,&regs);      //-------------------- seg012:0041
	if(regs.x.ax==0)
		MOUSE_ON=0; //-------------- seg012:005B
	else 
		MOUSE_ON=0xF; //------------------------- seg012:0069
	GraphMode = VGAHI;
//  driv=installuserdriver("SVGA",NULL);
	errorcode = graphresult();
//  GraphMode=1;
	initgraph(&GraphDriver,&GraphMode,"");
//  initgraph(&driv,&GraphMode,"");
  errorcode = graphresult();
  GraphMode=VGAHI;
	USER_FONT= registerbgifont(small_font);
  settextstyle(USER_FONT,0,4);  //--------------------- seg012:00DE
povtor:
  for(iNt=0;iNt<skoko_stoek;iNt++)
  {
    time_lu[iNt]=0L;time_lv[iNt]=0L;time_ly[iNt]=0L;
    time_lz[iNt]=0L;time_lc[iNt]=0L;
    for(ii=0;ii<=14;ii++){mas_lu[iNt][ii]=0;mas_lv[iNt][ii]=0;}
    for(ii=0;ii<=2;ii++){lu[iNt][ii]='@';lv[iNt][ii]='@';}

    for(ii=0;ii<=15;ii++)
    {
      mas_ly[iNt][ii]=0;
      mas_lz[iNt][ii]=0;
      mas_lc[iNt][ii]=0;
			mas_ls[iNt][ii]=0;
		}
		for(ii=0;ii<=3;ii++)
    {
      ly[iNt][ii]='@';
			lz[iNt][ii]='@';
      lc[iNt][ii]='@';
      ls[iNt][ii]='@';
    }
	}


//  for(iNt=0;iNt<skoko_stoek;iNt++){otkaz_ts[iNt]=1;otkaz_tu[iNt]=1;}

  regs.x.ax=0x1000;// функция установки палитры
  regs.h.bl=7;
  regs.h.bh=7;
  int86(0x10,&regs,&regs);
  setbkcolor(7);
	clscreen();
//  setusercharsize(1,3, 1, 3);
//  setcolor(8);
//  outtext("█АБВГДЕЖЗИКЛМНОПРСТУФХЦЧШЩЭЮЯабвгдежзиклмнопрстуфхцчшщэюя");
  setbkcolor(cvv); //------------------------ seg012:0451
  obnov = 0; //------------------------------ seg012:045C
	cikl_obnov = 0; //------------------------- seg012:0468
	otl_soob = 0xffff; //---------------------- seg012:0474
    //очистка буферов ввода-вывода для обмена с внешними устройствами
#ifdef DISPETCHER
  for(ic=0;ic<SIZE_BUF_OUT_DC;ic++)BUF_OUT_DC[ic]=0;
	for(ic=0;ic<SIZE_BUF_PRIEM_DC;ic++)BUF_IN_DC[ic]=0;
#endif
  for(ic=0;ic<SIZE_BUF_OUT;ic++)
	{
		BUF_OUT[0][ic] = 0;
		BUF_OUT[1][ic] = 0;
	}
	for(ic=0;ic<SIZE_BUF_PRIEM;ic++){BUF_IN[0][ic]=0;BUF_IN[1][ic]=0;}
  for(ic=0;ic<MAX_SIZE_OUT;ic++)BUF_OUT_PVM[ic]=0;
  for(ic=0;ic<MAX_SIZE_IN;ic++)BUF_IN_PVM[ic]=0;
  for(ic=0;ic<skoko_stoek;ic++)
  {
//    otkaz_ts[ic]=0;
//    sboy_ts[ic]=0;
    otkaz_tu[ic]=0;
		sboy_tu[ic]=0;
    old_aoar[ic]=7;
    t_com[ic]=0;
  }
//  OBMEN_PVM=0xf;
  UKAZ_ZAP_OUT=0;
  UKAZ_VYVOD=0;
  UKAZ_PRIEMA_PVM=0;
  N_OGR=0;
  nosound();
	NEISPRAVEN=1;
  
	fl=open("dat\\tranc.svs",O_RDONLY|O_BINARY,S_IWRITE | S_IREAD);
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

	
	if(notHDD == 0)
	{
		//СОЗДАНИЕ КОНТРОЛЬНОГО ФАЙЛА БАЗЫ ДАННЫХ
		BAZA=creat("dat\\baza.bin",S_IWRITE|O_BINARY); //----- seg012:02F2
		for(ic=0;ic<kol_VO;ic++)
		{
			for(iNt=0;iNt<14;iNt++)
			{
				str_baz[iNt*2]=(fr1[ic][iNt]&0xff00)>>8;
				str_baz[iNt*2+1]=fr1[ic][iNt]&0xff;
			}
			ik=CalculateCRC8(fr1[ic],14);
			str_baz[28]=(ik&0xff00)>>8;
			str_baz[29]=ik&0xff;
			ii=_write(BAZA,&str_baz,32);
		}
		if(BAZA>0)
		ii = close(BAZA);
		BAZA = 0; //------------------------ seg012:03F3
	}
	//получение даты	
	_dos_getdate(&dat);
	
	if(notHDD==0)
	{	
	
		//формирование текстового формата и получение имени суточного архива
		strcpy(NAME_FILE,"RESULT//");
		if(dat.day<10){NAME_FILE[8]=0x30;NAME_FILE[9]=dat.day|0x30;}
		else {NAME_FILE[8]=(dat.day/10)|0x30;NAME_FILE[9]=(dat.day%10)|0x30;}
		if(dat.month<10){NAME_FILE[10]=0x30;NAME_FILE[11]=dat.month|0x30;}
		else {NAME_FILE[10]=(dat.month/10)|0x30;NAME_FILE[11]=(dat.month%10)|0x30;}
		strcat(NAME_FILE,".ogo");
		NAME_FILE[16]=0;
		//открытие или создание файла суточного архива
		file_arc=open(NAME_FILE,O_APPEND|O_RDWR,O_BINARY);
		if(file_arc<0)
		{ iNt=mkdir("result");
			file_arc=open(NAME_FILE,O_CREAT|O_TRUNC|O_APPEND|O_RDWR,S_IWRITE|O_BINARY);
		}
		if(file_arc<0)
		{ clscreen(); moveto(100,100); setcolor(14);
			outtext("Нарушение файловой структуры,работа невозможна");
			getch();
			exit(1);
		}
		if(file_arc>0)
		ii=close(file_arc);
		file_arc=0;
		read_t(0); //формирование строки текущего времени TIME
	}
#ifdef SPDLP
	fai=fopen("dat\\spdlp.dat","r");
	if(fai==NULL)
	{
		clrscr(); moveto(80,80);
		outtext("Нет файла с данными для СПДЛП spdlp.dat.");
		moveto(80,160);
		outtext("Для выхода из программы нажмите любую клавишу");
		getch();
		exit(1);
	}
	read_spdlp(fai);
	if(fai!=NULL)fclose(fai);
	fai=NULL;
#endif		
	read_lex();//конвертация или открытие файла текстовых сообщений системы
  start_time_date();//получение даты и времени для ведения архива
  FIR_time=biostime(0,0L);SEC_time=FIR_time+1;
  flagoutmsg=0;//сброс флага наличия не выданной команды
  cha=0;na=0;
  first_time=biostime(0,0L);
	tii=first_time;
  slom_interf(9000);//записать код начала работы в файл oblom#.fix
  strcpy(bu,"( НАЧАЛО  )");
	add(0,'S');//зафиксировать начало работы в .ogo
#ifndef WORK
    STATUS=1;//##
#endif
  ZZagruzka(); //получить данные из стоек по всем сообщениям
	if(notHDD==0)
	{
		if(file_arc>0)i_close=close(file_arc);//закрыть файл архива
		file_arc=0;
  }
	for(iNt=0;iNt<=8;iNt++){bu[0][iNt]=0;bu[1][iNt]=0;}//очистить буфера ТУМС
  prohod_1=1;
  clscreen();//очистить экран
  kursor();//сформировать образ курсора
  //setactivepage(0);setvisualpage(0);
  uprav=1;tst=2;
#ifdef SETKA1
	setcolor(15);
  for(iNt=0;iNt<=640;iNt=iNt+10)
  { gotoxy(iNt,0);
    if(iNt%40==0)outtextxy(iNt-8,0,itoa(iNt,lstr,10));
    line(iNt,0,iNt,470);
    if(iNt%40==0)outtextxy(iNt-8,470,itoa(iNt,lstr,10));
  }
	for(iNt=20;iNt<=480;iNt=iNt+10)
	{ gotoxy(iNt,0);
    if(iNt%40==0)outtextxy(0,iNt,itoa(iNt,lstr,10));
    line(24,iNt,610,iNt);
    if(iNt%40==0)outtextxy(610,iNt,itoa(iNt,lstr,10));
  }
#endif
	nach_zagruzka();//выполнить полную прорисовку экрана
	setfillstyle(SOLID_FILL,cvv);
	menu();//изобразить меню для выбранного режима
	i3=-1;
	#ifdef WORK
		start_port(0);//инициировать порты,установить вектора прерываний
	#endif
	ZAGRUZKA=0;ZONA_KURSORA=ZONA_N;
	home(-1);//перевести курсор в исходное
	regs.h.ah = 5;//сброс клавиатуры
	regs.h.ch = 0;
	regs.h.cl = 0;
	int86(0x16,&regs,&regs);
#ifdef MOUSE
	if(MOUSE_ON!=0)mouse_init();//инициализация мыши
#endif
	FIR_time=biostime(0,0L);SEC_time=FIR_time+1;
	OBMEN_PVM_OLD=OBMEN_PVM;
	cikl_obnov=0;obnov=0;
	pauza=0;
met0://---------------------начало основного цикла

	nom_func("146");

#ifndef WORK
//STATUS=STAT;//##
	STATUS=1;
	TELEUP=1;//##
#endif
  /*  n_cikl++;*/
	tst_zvuk();//проверка включения или выключения звука
  if((klo==0)&&(nikuda==0)&&(help==0))what_is_new();//проверка наличия принятых данных из соседней ПЭВМ
  //инициализация таймера-стророжа на выдержку 3 сек
  outportb(0x443,3);
  pauza++;
  if((pauza<2)||(menu_N!=0))goto mtk;
  pauza=0;
  if(cikl_obnov>=kol_VO)cikl_obnov=0;
	if(notHDD==0)
	{
		if((obnov==0)&&(klo==0));
		{
			BAZA=open("dat\\baza.bin",O_RDONLY|O_BINARY);
			if(BAZA==-1)
			{
				w(44,999," База не открывается");
				getch();
				exit(0);
			}
			lseek(BAZA,32*cikl_obnov,0);
			read(BAZA,str_baz,32);
			for(ik=0;ik<15;ik++)
			{
				test_baz[ik]=(str_baz[ik*2]<<8)+str_baz[ik*2+1];
				if((test_baz[ik]!=fr1[cikl_obnov][ik])&&(ik!=14))
				{
					w(44,cikl_obnov," 6");
					getch();
				}
			}
			if(BAZA>0)close(BAZA);
			BAZA=0;
		}
	}	
	if((klo!=0)||(nikuda!=0)||(help!=0))goto mtk;
	prorisovka = 1;
	if((markery[i3][6]==cikl_obnov)&&(i3!=0))goto out;
//  itoa(cikl_obnov,lstr,10);
//  setcolor(7);
//  outtextxy(600,5,"████");
//  setcolor(8);
//  outtextxy(600,5,lstr);
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
out:
  obnov++;
/*
	ic=getpixel(186,186);
	if((ic==0)||(ic==7))ic=getpixel(187,187);
	else
		pauza=0;
	if((ic==0)||(ic==7))ic=getpixel(185,186);
	else
		pauza=0;
	if((ic==0)||(ic==7))ic=getpixel(185,185);
	else
		pauza=0;
	if((ic!=0)&&(ic!=7))
	pauza=0;*/
	if(obnov==5){obnov=0;cikl_obnov++;}
mtk:

  prorisovka=0;
  for(ik=1;ik<=skoko_stoek;ik++)
  {
    for(iNt=0;iNt<kol_VO;iNt++)if((pooo[iNt]!=0l)&&(fr1[iNt][13]==ik))break;
    if((iNt==kol_VO)&&(t_com[ik-1]<=biostime(0,0l))&&(t_com[ik-1]!=0))
    t_com[ik-1]=0l;
  }
  iNt=test_time1(18L);//проверка прохождения одной секунды
  if(iNt>0) //если прошла одна секунда
  {
#ifdef WORK
    proverka_svyazi();//установка переменных контроля каналов обмена
#endif
    cikl_avto++;
    if(cikl_avto>5)cikl_avto=0;
    if(klo==1){kartina();goto dalee;}// если просмотр неисправностей УВК
#ifdef DOS
    if(peek(0x0040,0x001A)==peek(0x0040,0x001C)//если очередь клавиатуры пуста
    {
      ScLk=peek(0x0040,0x0017);//прочитать состояние индикаторов клавиатуры
      if((ScLk&16)==16)ScLk=ScLk&0xFFEF;//проинвертировать бит для ScLk;
      else ScLk=ScLk|16;
      poke(0x0040,0x0017,ScLk);
      while((inportb(0x64)&2)!=0);
			outportb(0x60,0xED);
      while((inportb(0x64)&1)==0);
      if(inportb(0x60)!=0xFA){w(234,999,"");sound(1200);}
      while((inportb(0x64)&2)!=0);
      outportb(0x60,((ScLk>>4)&7));
    }
#endif
    for(ii=0;ii<20;ii++)
    {
      if(markery[ii][6]==9999)
			{
        if(ii==MAKET)continue;
        ic=getpixel(markery[ii][4],markery[ii][5]);
        a=getpixel(markery[ii][4]+1,markery[ii][5]+1);
        b=getpixel(markery[ii][4]-1,markery[ii][5]-1);
        if((a!=b)||(a!=ic))
        {
          if(b==ic)vkl_kno(ii,b);
          if(a==ic)vkl_kno(ii,a);
          if(a==b)vkl_kno(ii,a);
        }
        else vkl_kno(ii,a);
      }
    }
    if((vih_vopr==0)&&(vibeg==0)&&(vozvr==0)&&(menu_N==0))
    {
      if(otl_soob!=0xffff)
      {
				t(0);
        w(otl_soob,999,"");
        otl_soob=0xffff;
      }
    }
dalee:
#ifdef AVTOD
		if((STATUS==1)&&(TELEUP==1)&&(cikl_avto==5))
    {
      for(ii=0;ii<4;ii++)if(avto_marsh(ii))zad_marsh_avto();
    }
    if(TELEUP==0)
    {
      if(cha==1)snyato_chet();
      if(na==1)snyato_nechet();
    }
#endif
//    setcolor(7);
//    outtextxy(100,10,"████");
//    setcolor(8);
//    itoa(trassa[0],lstr,10);
//    outtextxy(100,10,lstr);
#ifdef SPDLP
    ZAP_BUF_SPD();
#endif
    ANALIZ_KOM_TUMS();
#ifdef WORK
    pust_pvm++;//##
#endif
    //изображение своей ПЭВМ
    ispr_pvm(0,0);
    //изображение ПЭВМ соседа (NEISPRAVEN -признак отказа канала ПЭВМ-ПЭВМ)
    ispr_pvm(1,NEISPRAVEN);
    out_time();
#ifdef WORK
    for(a=0;a<skoko_stoek;a++){sboy_ts[a]++;sboy_tu[a]++;}
#endif
    if(flag_paro==0)
    {
      if((pusto&3)!=0)w(138,999,"");//ОТСУТСТВУЕТ СВЯЗЬ С МПСУ#
      else
        for(ii=0;ii<skoko_stoek;ii++)if(otkaz_ts[0]==1)w(144+ii,999,"");
		}
    if((nikuda==0)&&(klo==0)&&(help==0))
		analiz_time();
    FIR_time=SEC_time;
  }
  ic=0;
  for(ii=0;ii<skoko_stoek;ii++)
  {
    if((otkaz_ts[ii]==0)&&(sboy_ts[ii]<2))ic++;
  }
  if(ic==skoko_stoek)
  {
    if(pusto==0xff00)
    {

			clscreen();
			pusto=0;
			inportb(0x43);
			if(file_soob>0)close(file_soob);
			file_soob=0;
			goto povtor;
		}
  }
#ifdef SPDLP
  if(STATUS==1)OUT_SPD();
#endif
  tu_tc();
  consentr();
  FORM_BUF_PVM_OUT();
  test_otvetstv();
#ifdef WORK
  test_port_pvm();//##
#endif
#ifdef MOUSE
  if((MOUSE_ON!=0)&&(STATUS==1))
  {
    if((help!=0)||(klo!=0)||(nikuda!=0))goto klava;
    if((STATUS==1)&&(DU==0)&&(TELEUP==1))
    {
      modi_new=mouse();//найти новый объект
			if(menu_N!=0)goto move;
      if((modi_new<0)&&(perezap==1))//если ушли с ранее выбранного объекта
      { mouser=0; if(i3!=-1)del_kursor(i3);
        regs.x.ax=0x1A;//повышаем чувствительность
        regs.x.bx=70;regs.x.cx=70;//по горизонтали и вертикали - 100
        int86(0x33,&regs,&regs);
        obnov_kur_mouse(X_m,Y_m);
        home(old_modi);//восстановить старый вид имени
				setcolor(7);outtextxy(45,46,"██████████");				
        perezap=2;
      }
      if((modi_new>=0)&&(perezap==0))//если вновь выделен объект
      {
        clear_mouse();//восстановить фон под последним местом курсора
        for(ik=0;ik<12;ik++)line_gor_kurs[ik]=0;//##
        for(ik=0;ik<40;ik++)line_vert_kurs[ik]=0;//##
        regs.x.ax=0x1A;//снижаем чувствительность
        regs.x.bx=50;regs.x.cx=50;//по горизонтали и вертикали - 2
        int86(0x33,&regs,&regs);
        if(i3>=0)del_kursor(i3);//удалить клавиатурный курсор со старой позиции
        if((old_modi>=0)&&(sbros1==0))del_kursor(old_modi);
        perezap=1;//вывесить флаг захвата объекта
        i3=modi_new;//свести все указатели вместе
        pat=i3;modi=i3;
        old_modi=modi_new;
        show_kursor(i3);//установить клавиатурный курсор на новую позицию
      }
      if(modi_new<0)mouser=0;
move:
      move_mouse();
      if(sbros1==1){t(0);sbros1=0;}
    }
  }
#endif
klava:
  if(kbhit())keyboard();
	else
  {
    if(klo==1)card();
     else
      if(nikuda==1)read_neisprav();
  }
#ifdef SETKA
  setcolor(15);
  for(iNt=0;iNt<=640;iNt=iNt+10)
  { gotoxy(iNt,0);
    if(iNt%40==0)outtextxy(iNt-8,0,itoa(iNt,lstr,10));
    line(iNt,0,iNt,470);
    if(iNt%40==0)outtextxy(iNt-8,470,itoa(iNt,lstr,10));
  }
  for(iNt=20;iNt<=480;iNt=iNt+20)
  { gotoxy(iNt,0);
    if(iNt%40==0)outtextxy(0,iNt,itoa(iNt,lstr,10));
    line(24,iNt,610,iNt);
    if(iNt%40==0)outtextxy(610,iNt,itoa(iNt,lstr,10));
  }
#endif
  prov_lX();
  if(OBMEN_PVM!=OBMEN_PVM_OLD)kom_v_bufer_pvm(0,OBMEN_PVM);
  OBMEN_PVM_OLD=OBMEN_PVM;
m1:
  if(DISK==0xf)
  {
		if(file_soob>0)close(file_soob);
		file_soob=0;
		Disk_arc();
		DISK=0;
		STATUS=2;
		NOMER_ARMA=3;
		if(file_soob>0)close(file_soob);
		file_soob=0;
		goto povtor;
  }
	else
	{
		if(pusto==0xff00)
		{
			pusto=0;
			clscreen();
			inportb(0x43);
			if(file_soob>0)close(file_soob);
			file_soob=0;
			goto povtor;
		}
		goto met0;
	}

  /*
  if(cikl<80000)goto met0;*/
} /* конец main */
/*********************************************/
kursor()
{
  int xk=135,yk=225;

	nom_func("138");

  setlinestyle(0,0,3);setlinestyle(0,0,0);setcolor(LIGHTBLUE);rectangle(xk-5,yk-2,xk+8,yk+3);
  setcolor(15);rectangle(xk-6,yk-3,xk+10,yk+4);
  setcolor(BLUE);rectangle(xk-4,yk-1,xk+9,yk+2);
  setcolor(LIGHTGREEN);rectangle(xk-3,yk-1,xk+7,yk+1);
  getimage(129,220,145,230,ukazat);
  setfillstyle(SOLID_FILL,cvv);
  bar(129,220,145,230);
}
/*****************************************************/
void Init_TEST_SOOB(int K)
{
  int N_bait,N_bit,N_SOOB,i;
  
	nom_func("108");
        
  if((K==1)&&(skoko_stoek==1))return;
  if(K==0)N_SOOB=KOL_SOO1;
#ifdef KOL_SOO2
  if(K==1)N_SOOB=KOL_SOO2;
#endif
  for(i=0;i<=6;i++)TEST_SOOB[K][i]=0xFF;
  for(N_bait=N_SOOB/8;N_bait<7;N_bait++)
  {
    if(N_bait==N_SOOB/8)
    for(N_bit=N_SOOB%8;N_bit<8;N_bit++)
    TEST_SOOB[K][N_bait]=TEST_SOOB[K][N_bait]^(1<<N_bit);
    else TEST_SOOB[K][N_bait]=0;
  }
  return;
}
/************************************************/

/****************************************************/
void SBROS_BIT_TEST_SOOB(int K,int N_SOOB)
{
  int N_bait,N_bit;
  
	nom_func("291");
          
  if((K==1)&&(skoko_stoek==1))return;
  N_SOOB=N_SOOB-48;
  N_bait=N_SOOB/8;
  N_bit=N_SOOB%8;
  if(ZAGRUZKA==1)
  {
    setcolor(1);
    outtextxy(10*(N_SOOB+1)+1,305+K*20,"█");
  }
  TEST_SOOB[K][N_bait]=TEST_SOOB[K][N_bait]&((0x1<<N_bit)^0xFF);
  return;
}
/********************************************************/

int TEST_BIT_SOOB(int K, int N_SOOB)
{
  int N_bait,N_bit;
  
	nom_func("337");
          
  if((K==1)&&(skoko_stoek==1))return;
  N_SOOB=N_SOOB-48;
  N_bait=N_SOOB/8;
	N_bit=N_SOOB%8;
	return(TEST_SOOB[K][N_bait]&(1<<N_bit));
}            
/**************************************************************/
int TEST_SUM_SOOB()
{
  int sum,i;
  
	nom_func("353");
    
  sum=0;
  for(i=0;i<=6;i++)sum=sum+TEST_SOOB[0][i];
#ifdef KOL_SOO2
  for(i=0;i<=6;i++)sum=sum+TEST_SOOB[1][i];
#endif
  return(sum);

}
/******************************************************************/
#ifdef MOUSE
void mouse_init()
{
  union REGS regs;
//  regs.x.ax=0; // установить драйвер мыши в исходное
//  int86(0x33,&regs,&regs);
//  ***********************************
  int ik;
  unsigned char kur[64];
  struct SREGS segregs;
  
	nom_func("174");
     
  for(ik=0;ik<64;ik++)kur[ik]=0;

  regs.x.ax=9; // задать пустое изображение для курсора
  regs.x.bx=0;
  regs.x.cx=0;

  segregs.es = FP_SEG(kur);
  regs.x.dx = FP_OFF(kur);
  int86x(0x33, &regs, &regs, &segregs);

  regs.x.ax=2; //убрать изображение курсора
  int86(0x33,&regs,&regs);

  regs.x.ax=7; // задать пределы движения по горизонтали
  regs.x.cx=X_MIN;
  regs.x.dx=X_MAX;
  int86(0x33,&regs,&regs);
//  *************************************
	regs.x.ax=8;// задать пределы движения по вертикали
  regs.x.cx=Y_MIN;
  regs.x.dx=Y_MAX;
  int86(0x33,&regs,&regs);
//  *******************************************
  regs.x.cx=X_m; //установить мышь в исходное положение
  regs.x.dx=Y_m;
  regs.x.ax=4;
  int86(0x33,&regs,&regs);
//  *****************************************************
  setlinestyle(0,0,0);setcolor(15);
  line(X_m-6,Y_m,X_m+6,Y_m);line(X_m,Y_m-4,X_m,Y_m+4);
  getimage(X_m-6,Y_m,X_m+6,Y_m,line_gor_kurs);
  getimage(X_m,Y_m-4,X_m,Y_m+4,line_vert_kurs);
  setcolor(7);
  line(X_m-6,Y_m,X_m+6,Y_m);line(X_m,Y_m-4,X_m,Y_m+4);
  X_m_old=X_m;Y_m_old=Y_m;
}
//********************************************************
int mouse()
{
  unsigned int size_x=0,size_y=0;
  int delta,N_m,ost;
  char nom_obj[3],X_mous[5],Y_mous[5];

	nom_func("173");

  regs.x.bx=0; //выбираем левую клавишу
  regs.x.ax=5; // получить информацию о нажатии
  int86(0x33,&regs,&regs);

  if(regs.x.bx >= 1)
  {
    down=1;
    if(menu_N!=0)
    {
      regs.h.ah = 5;
      regs.h.ch = 0;
      regs.h.cl = 13;// имитация нажатия Enter
      int86(0x16,&regs,&regs);
      return(-1);
    }
#ifdef MOUSE_NASTR
    itoa(regs.x.cx,X_mous,10);itoa(regs.x.dx,Y_mous,10);
    setcolor(7);outtextxy(300,240,"██████████");
    setcolor(8);outtextxy(300,240,X_mous);
    setcolor(7);outtextxy(300,250,"██████████");
    setcolor(8);outtextxy(300,250,Y_mous);
    getch();
#endif
  }
  regs.x.bx=1; //выбираем правую клавишу
  regs.x.ax=5; // получить информацию о нажатии
  int86(0x33,&regs,&regs);
  if((regs.x.bx>=1)&&(menu_N==0))
  {
    down=0;
    //  ***********************************
    regs.x.ax=7; // задать пределы движения по горизонтали
    regs.x.cx=X_MIN;
    regs.x.dx=X_MAX;
    int86(0x33,&regs,&regs);
    //  *************************************
    regs.x.ax=8;// задать пределы движения по вертикали
    regs.x.cx=Y_MIN;
    regs.x.dx=Y_MAX;
    int86(0x33,&regs,&regs);
    //--------------------------------------------------
    regs.h.ah=5;
    regs.h.ch=0;
    regs.h.cl=32;// имитация нажатия Space
    int86(0x16,&regs,&regs);
  }
  regs.x.ax=6;
  int86(0x33,&regs,&regs);
  if((regs.x.bx&1==1)&&(down==1))
  {
    down=0;
    regs.h.ah=5;
    regs.h.ch=0;
    regs.h.cl=13;// имитация нажатия Enter
    int86(0x16,&regs,&regs);
    mouser=0xf;

  }
  if(zapretvybora>0)return(old_modi);
  regs.x.ax=3; // получить информацию о координатах
  int86(0x33,&regs,&regs);
  if((X_m!=regs.x.cx)||(Y_m!=regs.x.dx))// если позиция сместилась
  {
    X_m=regs.x.cx;
    Y_m=regs.x.dx;
    regs.x.ax=3; //получить информацию о позиции
    int86(0x33,&regs,&regs);

    X_m=regs.x.cx;
    Y_m=regs.x.dx;
    mouse_down=0;
    delta=mouse_all/2+mouse_all%2;
    N_m=delta;//начинаем с объекта в центре упорядоченной базы
rep0:
    if(mouse_mark[N_m][1]>X_m) //если этот объект правее места курсора
    {
      if(mouse_mark[N_m][1]-X_m<=5)// если объект в зоне Х-захвата
      {
        Y_m_isk=Y_m;
        goto poisk_Y;
      }
      if(N_m==0)return(modi);//если нет объекта,привязанного по x
      if(delta==1)return(-1);
      delta=delta/2+delta%2;
      N_m=N_m-delta;//смещаемся влево
      if(N_m<0)return(-1);
      goto rep0;
    }
    if(mouse_mark[N_m][1]<X_m) //если этот объект левее места курсора
    {
      if(X_m-mouse_mark[N_m][1]<=5)// если объект в зоне Х-захвата
      {
        Y_m_isk=Y_m;
        goto poisk_Y;
      }
      if(N_m>=mouse_all) return(-1);// если нет объекта,привязанного по x
      if(delta==1)return(-1);
      delta=delta/2+delta%2;
      N_m=N_m+delta;//смещаемся влево
      goto rep0;
    }
poisk_Y:
    while(abs(mouse_mark[N_m][1]-X_m)<=5) N_m--;// подняться вверх до начала
    N_m++;
    while(abs(mouse_mark[N_m][1]-X_m)<=5)
    {
      if(abs(mouse_mark[N_m][2]-Y_m)<=5) // если объект в зоне Y-захата
      {
        return(mouse_mark[N_m][0]);// вернуть номер выбранного объекта
      }
      N_m++;
    }
    return(-1);// новый объект не найден
  }
  else return(modi);
}
//****************************************
void mem_mous_fon()
{

	nom_func("167");

	getimage(X_m-6,Y_m,X_m+6,Y_m,line_old_gor_kurs);
	getimage(X_m,Y_m-4,X_m,Y_m+4,line_old_vert_kurs);
	return;
}
//**********************************************
void draw_mouse()
// нарисовать курсор
{
  
	nom_func("46");

  putimage(X_m-6,Y_m,line_gor_kurs,0);
  putimage(X_m,Y_m-4,line_vert_kurs,0);
  return;
}
//**************************************
void clear_mouse()
//восстановить фон под мышью
{
	int ik;

	nom_func("25");

	putimage(X_m_old-6,Y_m_old,line_old_gor_kurs,0);
	putimage(X_m_old,Y_m_old-4,line_old_vert_kurs,0);
//  for(ik=0;ik<12;ik++)line_old_gor_kurs[ik]=0;
//  for(ik=0;ik<40;ik++)line_old_vert_kurs[ik]=0;

}
//***********************************
void move_mouse()
{ int i;

	nom_func("175");

	regs.x.ax = 3; //получить информацию о координатах
	/* int86*/
	int86(0x33,&regs,&regs);
	X_m = regs.x.cx;
	Y_m = regs.x.dx;
	//menu ?
	if(menu_N!=0)
	{
		//kursor in menu?
		if((X_m > 520)&&(Y_m < 30))
		{
			clear_mouse();
			for(i=0;i<12;i++)
				line_old_gor_kurs[i]=0;
			for(i=0;i<40;i++)
				line_old_vert_kurs[i]=0;
//      for(i=0;i<12;i++)line_gor_kurs[i]=0;
//      for(i=0;i<40;i++)line_vert_kurs[i]=0;
			if(Y_m<10)
				punkt_N=1;
			if((Y_m>10)&&(Y_m<20))
				punkt_N=2;
			if((Y_m>20)&&(Y_m<30))
				punkt_N=3;
			if(menu_N==1)
				down=0;
			menu1();
			down=0;
			return;
		}
	}
	if(((X_m!=X_m_old)||(Y_m!=Y_m_old)||(down==1))&&(perezap!=1)&&( mouser==0))// если в пустом поле
	{
		if(zapretvybora==1)return;
//   if(perezap==0)
		if(sbros1!=1)
		clear_mouse();//восстановить картинку под старым местом курсора
		if(perezap==2)
		perezap=0;
		mem_mous_fon();//запомнить картинку под новым местом
		draw_mouse();//нарисовать курсор в новом месте
		X_m_old=X_m;
		Y_m_old=Y_m;
		old_modi=-1;
//   if(uprav==0)modi=-1;
		pat=-1;
	}
}
#endif
//-----------------------------------------------------
void tst_zvuk()
{

	nom_func("376");

	if(STATUS!=1)
  {
    nosound;
    return;
  }
  switch(zvuk_sig.tip)
  {
    case 0: return;
    case 1: if((biostime(0,0l)-zvuk_sig.time_begin)<zvuk_sig.dlit)
            {
              sound(600);return;
            }
            else
            {
              nosound();
              return;
            }
    case 2: if((biostime(0,0l)-zvuk_sig.time_begin)<(zvuk_sig.dlit/3))
            {
              sound(400);return;
            }
            else
            {
              if((biostime(0,0l)-zvuk_sig.time_begin)<(2*zvuk_sig.dlit/3))
              {
								sound(600);return;
              }
              else
                if((biostime(0,0l)-zvuk_sig.time_begin)<zvuk_sig.dlit)
                {
									sound(400);return;
                }
                else
                {
                  nosound();
                  return;
                }
            }
    case 3: return;            
    default:  return;
  }
}
//-----------------------------------------------------------
void prodol()
{

	nom_func("239");

	if (vrem==5) uprav=1;
	//settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
	setcolor(8);
	if (vrem==1&&uprav==0)
	{
		puti=0;
		vkl_kno(2,LIGHTGREEN);
		vkl_kno(0,LIGHTGREEN);
    vrem=0;uprav=1;poka=0;tst=2;
  }
  else
  if (ot==1&&uprav==0) 
  {
    vkl_kno(1,LIGHTGREEN);
    vkl_kno(0,LIGHTGREEN);
    tst=0;
  }
  if(ot!=1) 
    if (uprav==0) 
    {
      vkl_kno(1,LIGHTGREEN);
      tst=0;
    }
    else
      if (uprav==1)   
			{
				vkl_kno(2,LIGHTGREEN);
				tst=2;
			}
	if(perekluch==1&&ot==1&&tst==2)
	{
		vkl_kno(2,LIGHTGREEN);
		ot=0;
	}
	else
		if(tst!=2) vkl_kno(1,LIGHTGREEN);
	if(perekluch==1)poka=0;
	i3=-1;
	menu();
}
//-----------------------------------------------------------
//-----------------------------------------------------------
void menu()
{
  
	nom_func("168");

  setfillstyle(CLOSE_DOT_FILL,LIGHTCYAN);
  bar(1,460,640,480);setcolor(GREEN);
  if(DISK==0)
  {
    if(STATUS==0)
    { outtextxy(3,462,"Esc");outtextxy(162,462,"ПРОБЕЛ");
      outtextxy(350,462,"F2");outtextxy(418,462,"F3");
      outtextxy(500,462,"F4");
      outtextxy(3,472,"F5");outtextxy(115,472,"F6");
      outtextxy(259,472,"F9");outtextxy(475,472,"F10");
      setcolor(BROWN);
      outtextxy(2,461,"Esc");outtextxy(161,461,"ПРОБЕЛ");
      outtextxy(349,461,"F2");outtextxy(417,461,"F3");
      outtextxy(499,461,"F4");
      outtextxy(2,471,"F5");outtextxy(114,471,"F6");
      outtextxy(258,471,"F9");outtextxy(474,471,"F10");
      setcolor(8);
      outtextxy(28,462,"-курсор на место");
      outtextxy(210,462,"-отказ от команды ");
      outtextxy(365,462,"-время");
      outtextxy(436,462,"-помощь");
      outtextxy(520,462,"-отключить звук");
      outtextxy(20,471,"-неиспр.СЦБ");
      outtextxy(130,471,"-неиспр.ап.УВК");
      outtextxy(274,471,"-подсв.положения стрелок");
			outtextxy(500,471,"-архив");
    }
    if(STATUS==1)
    {
      outtextxy(3,462,"Esc");outtextxy(162,462,"ПРОБЕЛ");
      outtextxy(350,462,"F1");outtextxy(454,462,"F2");
      outtextxy(3,472,"F4");
      outtextxy(146,472,"F5");outtextxy(290,472,"F9");
      setcolor(BROWN);
      outtextxy(2,461,"Esc");outtextxy(161,461,"ПРОБЕЛ");
      outtextxy(349,461,"F1");outtextxy(453,461,"F2");
      outtextxy(2,471,"F4");
      outtextxy(145,471,"F5");outtextxy(289,471,"F9");
      setcolor(8);
      outtextxy(28,462,"-курсор на место");
      outtextxy(210,462,"-отказ от команды ");
      outtextxy(362,462,"-разд/марш");
      outtextxy(470,462,"-время");
      outtextxy(20,472,"-отключить звук");
      outtextxy(161,472,"-обновить экран");
      outtextxy(305,472,"-подсв.положения стрелок");
    }
  }
  else
  {
    outtextxy(3,462,"F4");outtextxy(130,462,"F5");
    outtextxy(230,462,"F6");outtextxy(330,462,"F7");
    outtextxy(3,472,"F8");outtextxy(330,472,"F9");
    outtextxy(500,472,"F10");
    setcolor(BROWN);
		outtextxy(2,461,"F4");outtextxy(129,461,"F5");
    outtextxy(229,462,"F6");outtextxy(329,461,"F7");
    outtextxy(2,471,"F8");outtextxy(329,471,"F9");
    outtextxy(499,471,"F10");
    setcolor(8);
    outtextxy(18,462,"-отключить звук");outtextxy(142,462,"-неиспр.СЦБ");
    outtextxy(240,462,"-неиспр.ап.УВК");
    outtextxy(345,462,"-переход в архиве к другому моменту времени");
    outtextxy(18,471,"-переключение просмотра (автоматический/пошаговый)");
    outtextxy(345,471,"-подсв.положения стрелок");
    outtextxy(520,471,"-выход");
  }
}
