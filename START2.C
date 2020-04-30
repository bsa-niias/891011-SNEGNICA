#include"bla.h"q
#include<stdio.h>
#include<dos.h>
#include<process.h>
#include<io.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<bios.h>
#include<graphics.h>
void *fai;
unsigned int speed_spdlp; 
nach_zagruzka()
{
	int yt,lo;
	modi=-1;pat=-1;i3=-1;
#ifdef NALAD
	nom_func("177");
#endif
	prorisovka=1;
	zagruzen();
	prorisovka=0;
	for(lo=0;lo<skoko_stoek;lo++){sboy_ts[lo]=0;otkaz_ts[lo]=0;}
}
//------------------------------------------------
zagruzen()
{
	int i,lj,X,qi3;
	long time1,time2;
#ifdef NALAD
	nom_func("426");
#endif
	setcolor(3);
	i3=-1;
	read_text1(0);
	for(qi3=0;qi3<kol_OB_UPR;qi3++)
	imena(qi3);
	picture();
	for(lj=0;lj<kol_OB_UPR;lj++)
  if(markery[lj][7]==6||markery[lj][7]==7)init_markery(lj);
  setcolor(8);
  for(i=kol_OSN;i<kol_VO;i++)
  if(fr1[i][0]==2)
  {
    bata=0;
    displaysignal(i,0);
    displaysignal(i,1);
    displaysignal(i,2);
    displaysignal(i,3);
    displaysignal(i,4);
  }
  tel_vkl_vikl(TEL1);
#ifdef KOL_SOO2
  tel_vkl_vikl(TEL2);
#endif
  for(lj=Start_R;lj<Start_R+WAZO;lj++)
  {
    krasit_razd(lj,0);krasit_razd(lj,2);
  }
  krasit_knopki(Start_R+WAZO,2);
  knopka(KS1);
#ifdef KOL_SOO2
  knopka(KS2);
#endif
  vkl_kno(VSPZ,8);
  vkl_kno(MAKET,8);
  vkl_kno(AViA,8);
  if(ot==0)vkl_kno(0,8);
  else vkl_kno(0,LIGHTGREEN);
  if(uprav==0){vkl_kno(1,LIGHTGREEN);vkl_kno(2,8);}
  else {vkl_kno(2,LIGHTGREEN);vkl_kno(1,8);}
#ifdef AVTOD
  if(na==1)
  {
    vkl_kno(NANA,LIGHTGREEN);
    for(lj=0;lj<N_str;lj++)otkl_(N_strel[lj],1);
  }
  else vkl_kno(NANA,8);
  if(cha==1)
  {
    vkl_kno(CHACHA,LIGHTGREEN);
    for(lj=0;lj<CH_str;lj++)otkl_(C_strel[lj],0);
  }
  else  vkl_kno(CHACHA,8);
#endif
#ifdef kol_STY
  Styki();
#endif
  zapretvybora=0; i3=-1; pat=-1;
  if(DISK==0){knopka_OK();out_k();}
  kvadrat();
}
/************************************************/
out_k()
{
#ifdef NALAD  
  nom_func("211");
#endif       
// putimage(65,35,ukazat,COPY_PUT);
}
/***********************************/
imena(int ib)
{ //процедура вывода на экран имени указанного объекта, а также 
  //вывода подсветки курсора и рамки, если объект выбран оператором
  int ix=0,iy=0,ele=0,ix1=0,iy1=0,lp,lp1;
  char imya[20]="";
  int D=0,elo=0,NNBO;
#ifdef NALAD
  nom_func("103");
#endif
  if((klo==1)||(help!=0)||(nikuda==1))return;
//    settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
	setcolor(8);//обычный серый шрифт
	NNBO=ib;//запомнить номер выбранного объекта управления
	if(markery[ib][7]==6)//если выбрана стрелка смены направления
	{
		ele=markery[ib][6];//получить объект управления
		ele=fr1[ele][9]; //объект для перегона
		lp1=fr1[ele][8];//сомножитель для смещения по Y
		lp=fr1[ele][9]; //получить обратную ссылку на объект управления
		if(fr1[lp][1]==0)
		{
			if(OBRAT==1)D=1;// если объект для приема с левой стороны
			else D=2;
		}
		else
		{
			if(OBRAT==1)D=2;
			else D=1;
		}
		// 1 - слева   2 - справа
		switch(D) // в зависимости от места расположения записать координаты
		{
			case 1: markery[ib][4]=left_up_left[0]+7;
							markery[ib][5]=left_up_left[1]+lp1*fr1[ele][4]+2;
							break;
			case 2: markery[ib][4]=right_up_left[0]+12;
							markery[ib][5]=right_up_left[1]+lp1*fr1[ele][4]+2;
							break;
		}
		return;
	}
	if(markery[ib][7]==5||markery[ib][7]==4)
	{ //если путь или участок пути
		if(fr1[markery[ib][6]][8]==9999)return;//если путь не закрывается - выход
		ele=markery[ib][6];//получить номер объекта в базе
		if(fr1[markery[ib][6]][8]==0)strcpy(imya,pako[ele]);//для остальных - имя
		//вычислить координаты
		ix1=div(fr2[ele][0]+fr2[ele][2],2)-strlen(pako[ele])*4;
		iy1=fr2[ele][1]-10;
		if(fr4[ele][2]==1)setcolor(LIGHTRED);//для закрытого - цвет красный
		else setcolor(8);//иначе - цвет серый
	}
	else
	{
		if(markery[ib][7]==2)
		{ // если сигнал
			ele=markery[ib][6];//получить номер в базе для объекта
			if(fr1[ele][8]!=666)//если это - не смена направления
			{
				strcpy(imya,pako[ele]);//скопировать имя строкой
				D=strlen(pako[ele]);//определить длину
				switch(fr3[ele][0]*8+fr3[ele][1]*4+fr3[ele][3]*2+fr3[ele][2])
				{
					case 1: setcolor(15);break;
					case 2: setcolor(14);break;
					case 3: setcolor(5);break;
					default: setcolor(8);break;
				}
			}
			else
			{//если смена направления???????????????????
				if(fr3[fr1[ele][11]][1]==0)
				{
					imya[0]=pako[ele][3];   //скопировать пол-имени побайтно
					imya[1]=pako[ele][4];
				}
				else
				{
					imya[0]=pako[ele][0];
					imya[1]=pako[ele][1];
				}
				D=strlen(imya);
			}
			ix=fr2[ele][0];iy=fr2[ele][1]+3;//взять координаты для текста
			if(fr1[ele][9]==1) //сигнал над путем
			{
				if(fr1[ele][1]==1)//сигнал нечетный
				{
					if(OBRAT==-1) goto a1; //учесть ориентацию на экране
a2:       ix1=ix+3;
					iy1=iy-14;//скорректировать координаты
				}
				else//аналогично для четного сигнала
				{
					if(OBRAT==-1) goto a2;
a1:       if(fr1[ele][3]==7)ix1=ix-(D*7+3);
					else ix1=ix-D*7;
					iy1=iy-14;
				}
			}
			else //аналогично для сигнала под путем
			if(fr1[ele][9]==0)
			{
				if(fr1[ele][1]==0)//сигнал четный
				{
					if(OBRAT==-1) goto a3;
a4:       if(fr1[ele][3]==7)ix1=ix-(D*7+3);
					else ix1=ix-(D*7+3);
					iy1=iy+2;
				}
				else//сигнал нечетный
				{
					if(OBRAT==-1) goto a4;
a3:       if(fr1[ele][3]==7)ix1=ix+3;
					else ix1=ix;
					iy1=iy+2;
				}
			}
		}
		else
		if(markery[ib][7]==1)//если это имя для стрелки
		{
			ele=markery[ib][6];//получить объект для стрелки
			lp=0;
			D=strlen(pako[ele]);//вычистить длину имени
			while(pako[ele][lp]!=':') lp++; //дойти до разделителя
			lp++;
			for(lp1=0;lp1<20;lp1++)imya[lp1]=0; //очистить имя
			lp1=0;
			while(lp<D)
			{
				imya[lp1]=pako[ele][lp];//переписать имя от разделителя
				lp++;
				lp1++;
			}
      D=strlen(imya);
      if(fr3[ele][0]==fr3[ele][1])setcolor(12);//если для стрелки нет контроля
      else
      if((fr3[ele][0]==1)&&(fr3[ele][1]==0))setcolor(LIGHTGREEN);//если в плюсе

      else
      if((fr3[ele][0]==0)&&(fr3[ele][1]==1))setcolor(14);//если в минусе
      if(fr3[ele][5]==1)setcolor(LIGHTCYAN);
      ix=fr2[ele][0];
      iy=fr2[ele][1];
      switch(fr1[ele][9])//переключатель по ветвлению
      { //вверх
        case 1: if(fr1[ele][7]==0) //вход четный
                {
                  if(OBRAT==-1) goto ob2;//учесть ориентацию
ob1:              ix1=ix-(D*7);iy1=iy-11;//получить координаты
                }
                else
                { // вход нечетный
                  if(OBRAT==-1) goto ob1;
ob2:              ix1=ix;iy1=iy-11;
                }
                break;
        // вниз
        case 0: if(fr1[ele][7]==1) //вход нечетный
                {
                  if(OBRAT==-1) goto ob4;
ob3:              ix1=ix;iy1=iy+5;
                }
                else //вход четный
                {
                  if(OBRAT==-1) goto ob3;
ob4:              ix1=ix-(D*7)+2; iy1=iy+5;
                }
                break;
        default:  ix1=ix;iy1=iy;break;
      }
      if(fr1[ele][3]==2)/* вход по косой слева-сверху вправо-вниз */
      {
        ix1=ix+3;iy1=iy-11;
      }
    }
  }
fin:
  if(markery[NNBO][7]<=6)//если не кнопки
  {
//    settextstyle(0,0,0);
    moveto(ix1,iy1);
    if(fr1[ele][0]!=1)//если не стрелка
    {
      if((fr1[ele][0]==2)&&(fr1[ele][11]!=9999))//если сигнал
      {
        setfillstyle(SOLID_FILL,cvv); //стереть имя
        bar(ix1,iy1,ix1+D*7,iy1+7);
        moveto(ix1,iy1);
        outtext(imya); //написать имя
      }
      else outtext(imya);//если что-то другое - написать не стирая
    }
    else
    if(fr1[ele][0]==1) //если стрелка
    {
      outtext(imya);   //написать имя
      if((i3!=-1)&&(markery[i3][6]==ele))//если маркер на стрелке

      {
        Fla_no_pp=1;
        show_kursor(i3);//нарисовать курсор
        Fla_no_pp=0;
      }
    }
    //для всего
    if(markery[NNBO][7]!=7)//если не вариантная кнопка
    {
      markery[NNBO][4]=ix1;//заполнить координаты
      markery[NNBO][5]=iy1;
    }
  }
}
/*****************************************************/
init_markery(int ie)
{
  int ix=0,iy=0,ele=0,ix1=0,iy1=0,lp,lp1;
  int D=0,elo=0;
  char imya[20]="";
#ifdef NALAD  
  nom_func("107");
#endif          
  if((nikuda==1)||(klo==1)||(help!=0))return;
  if(markery[ie][7]==7)//если вариантная точка 
  {
    ix=markery[ie][4];
    iy=markery[ie][5];
    setfillstyle(1,8);
    bar(ix-3,iy-3,ix+3,iy+3);
    return;
  }
  if((markery[ie][7]==5)||(markery[ie][7]==4))
  {
    ele=markery[ie][6];
    markery[ie][4]=fr2[ele][2]+div(fr2[ele][0]-fr2[ele][2],2)+7;
    markery[ie][5]=fr2[ele][1];
    return;
  }
  if(markery[ie][7]==6)
  {
    ele=markery[ie][6];
    ele=fr1[ele][9]; /* адрес перегона */
    lp1=fr1[ele][8];
    lp=fr1[ele][9];
    if(fr1[lp][1]==0)
    {
      if(OBRAT==1)D=1;
      else  D=2;
    }
    else
    {
      if(OBRAT==1)D=2;
      else  D=1;

    }
    /* 1 - слева   2 - справа */
    switch(D)
    {
      case 1: markery[ie][4]=left_up_left[0]+7;
              markery[ie][5]=left_up_left[1]+lp1*fr1[ele][4]+2;
              break;
      case 2: markery[ie][4]=right_up_left[0]+12;
              markery[ie][5]=right_up_left[1]+lp1*fr1[ele][4]+2;
              break;
    }
    return;
  }
  if(markery[ie][7]==2)
  {
    ele=markery[ie][6];
    D=strlen(pako[ele]);
    ix=fr2[ele][0];
    iy=fr2[ele][1]+3;
    if(fr1[ele][9]==1) // сигнал над путем
    {
      if(fr1[ele][1]==1)//сигнал нечетный
      {
        if(OBRAT==-1) goto a1; //если у нечетных сигналов имена слева
a2:     ix1=ix+9;
        iy1=iy-12;
      }
      else //сигнал под путем
      {
        if(OBRAT==-1) goto a2; //если у четных сигналов имена справа
a1:     ix1=ix-(D*7);
        iy1=iy-12;
      }
    }
    else
    if(fr1[ele][9]==0)
    {
      if(fr1[ele][1]==0)
      {
        if(OBRAT==-1) goto a3;
a4:     ix1=ix-(D*7);
        iy1=iy;
      }
      else
      {
        if(OBRAT==-1) goto a4;
a3:     ix1=ix+9;
        iy1=iy;
      }
    }
  }
  else
  if(markery[ie][7]==1)
  {
    ele=markery[ie][6];
    lp=0;
    D=strlen(pako[ele]);
    while(pako[ele][lp]!=':') lp++;
    lp++;
    for(lp1=0;lp1<20;lp1++)imya[lp1]=0;
    lp1=0;
    while(lp<D)
    {
      imya[lp1]=pako[ele][lp];
      lp++;
      lp1++;
    }
    D=strlen(imya);
    ix=fr2[ele][0];
    iy=fr2[ele][1];
    if(fr1[ele][9]==1) /*вверх*/
    if(fr1[ele][7]==0) /* вход четный */
    {
      if(OBRAT==-1) goto ob2;
ob1:  ix1=ix-(D*7)+6;
      iy1=iy-10;
    }
    else
    { /* вход нечетный */
      if(OBRAT==-1) goto ob1;
ob2:  ix1=ix+7;
      iy1=iy-10;
    }
    else /*  вниз */
    {
      if(fr1[ele][7]==1) /* нечет */
      {
        if(OBRAT==-1) goto ob4;
ob3:    ix1=ix+7;
        iy1=iy+4;
      }
      else
      {
        if(OBRAT==-1) goto ob3;
ob4:    ix1=ix-(D*7)+6;
        iy1=iy+4;
      }
    }
  }
fin:
  markery[ie][4]=ix1+div(10*D,2);
  markery[ie][5]=iy1+7;
  return;
}
/*******************************************/
formula(int fu)
{
	unsigned char *chislo="0000000000",prob;
	long hh;
	int KUP=0,ind=0,in=0,inn=0,NB=0;
	unsigned int speed,speed11,speed_pvm,speed_bbkp;
#ifdef NALAD
	nom_func("87");
#endif
	for(inn=0;inn<10;inn++)chislo[inn]=0xf;
	inn=0;
	setcolor(8);
	len=(kol_VO+1)*6;//определение длины файла для ограничений
	//выполнение чтения файла tranc.svs
	in=0;
	hh=lseek(fu,0,0l);
	while(chislo[in-1]!=0x20)read(fu,&chislo[in++],1);
	DVA_MO=atoi(chislo);
  while(prob!='\n')read(fu,&prob,1);//поиск конца строки
  if(DVA_MO!=0)//если установлен признак наличия модемов
  {
    clrscr();
    moveto(8,80);
    outtext("В данном случае первый параметр в файле tranc.svs должен быть равен 0");
    getch();
    exit(1);
  }

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
  //считывание адреса для ТУМС-1
  BAZ_ADR1=(chislo[2]-48)*256+(chislo[3]-48)*16+chislo[4]-48;
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
  speed=atoi(chislo);//считывание скорости для ТУМС-1
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
	//считывание адреса для ТУМС-2
  BAZ_ADR11=(chislo[2]-48)*256+(chislo[3]-48)*16+chislo[4]-48;
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
  speed11=atoi(chislo);//считывание скорости для ТУМС-2
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
  //считывание адреса для ББКП
  BAZ_ADR2=(chislo[2]-48)*256+(chislo[3]-48)*16+chislo[4]-48;
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
  speed_bbkp=atoi(chislo);//считывание скорости для ББКП
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
	//считывание адреса для кнопки ОК
  BAZ_ADR3=(chislo[2]-48)*256+(chislo[3]-48)*16+chislo[4]-48;
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
	//считывание адреса для обмена ПЭВМ
  BAZ_ADR4=(chislo[2]-48)*256+(chislo[3]-48)*16+chislo[4]-48;
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
  speed_pvm=atoi(chislo);//считывание скорости для обмена ПЭВМ
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
	//считывание адреса для СПДЛП
  BAZ_ADR6=(chislo[2]-48)*256+(chislo[3]-48)*16+chislo[4]-48;
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
  speed_spdlp=atoi(chislo);//считывание скорости для СПДЛП
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
	//считывание адреса переключателя ОСН/РЕЗ
  BAZ_ADR5=(chislo[2]-48)*256+(chislo[3]-48)*16+chislo[4]-48;
  while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
  NB=atoi(chislo);//считывание вектора прерывания
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
  TEST_N=atoi(chislo);//считывание признака фиксации ЛС/ЗС
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
  MODE_KN=atoi(chislo);//считывание флага способа включения кнопки ОК
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

  in=0;prob=0;
  while(chislo[in-1]!=32)read(fu,&chislo[in++],1);
  chislo[in]=0;
  PROV_SCB=atoi(chislo);//считывание флага проверки СЦБ
	while(prob!='\n')read(fu,&prob,1);//поиск конца строки

	//задание делителей для заданной скорости
	switch(speed)
	{
		case 300:    ml_ba=0x80; st_ba=0x01; break;
		case 600:    ml_ba=0xc0; st_ba=0x00; break;
		case 1200:   ml_ba=0x60; st_ba=0x00; break;
		case 2400:   ml_ba=0x30; st_ba=0x00; break;
		case 4800:   ml_ba=0x18; st_ba=0x00; break;
		case 9600:   ml_ba=0x0c; st_ba=0x00; break;
		case 19200:  ml_ba=0x6;  st_ba=0x00; break;
		case 38400:  ml_ba=0x3;  st_ba=0x00; break;
		case 57600:  ml_ba=0x2;  st_ba=0x00; break;
		case 115200: ml_ba=0x1;  st_ba=0x00; break;
		default:  clrscr();moveto(80,80);
							outtext("Неизвестная скорость обмена МПСУ1-ПЭВМ");
							getch();exit(1);
	}
#ifdef KOL_SOO2
	switch(speed11)
	{
		case 300:    ml_ba2=0x80; st_ba2=0x01; break;
		case 600:    ml_ba2=0xc0; st_ba2=0x00; break;
		case 1200:   ml_ba2=0x60; st_ba2=0x00; break;
		case 2400:   ml_ba2=0x30; st_ba2=0x00; break;
		case 4800:   ml_ba2=0x18; st_ba2=0x00; break;
		case 9600:   ml_ba2=0x0c; st_ba2=0x00; break;
		case 19200:  ml_ba=0x6;   st_ba=0x00;  break;
		case 38400:  ml_ba=0x3;   st_ba=0x00;  break;
		case 57600:  ml_ba=0x2;   st_ba=0x00;  break;
		case 115200: ml_ba=0x1;   st_ba=0x00;  break;
		default: clrscr();moveto(80,80);
						 outtext("Неизвестная скорость обмена МПСУ2-ПЭВМ");
						 getch();
						 exit(1);
	}
#endif
	switch(speed_pvm)
	{
		case 300: ml_bap=0x80;st_bap=0x01;break;
		case 600: ml_bap=0xc0;st_bap=0x00;break;
		case 1200: ml_bap=0x60;st_bap=0x00;break;
		case 2400: ml_bap=0x30;st_bap=0x00;break;
		case 4800: ml_bap=0x18;st_bap=0x00;break;
		case 9600: ml_bap=0x0c;st_bap=0x00;break;
		case 19200:  ml_ba=0x6;st_ba=0x00;  break;
		case 38400:  ml_ba=0x3;st_ba=0x00;  break;
		case 57600:  ml_ba=0x2;st_ba=0x00;  break;
		case 115200: ml_ba=0x1;st_ba=0x00;  break;
		default:   clrscr(); moveto(80,80);
							 outtext("Неизвестная скорость для обмена ПЭВМ-ПЭВМ");
							 getch();
							 exit(1);
	}
	switch(speed_bbkp)
	{
	 case 300: ml_bab=0x80; st_bab=0x01;break;
	 case 600: ml_bab=0xc0; st_bab=0x00;break;
	 case 1200: ml_bab=0x60;st_bab=0x00;break;
	 case 2400: ml_bab=0x30;st_bab=0x00;break;
	 case 4800: ml_bab=0x18;st_bab=0x00;break;
	 case 9600: ml_bab=0x0c;st_bab=0x00;break;
	 default: clrscr(); moveto(80,80);
						outtext("Неизвестная скорость для обмена ПЭВМ-ББКП");
						getch();
						exit(1);
	}
	switch(NB)
	{
	 case 1 : V=0x0c; break;
	 case 2 : V=0x0b; break;
	 default: clrscr(); moveto(80,80);
						outtext("Неизвестный вектор прерывания");
						getch();
						exit(1);
	}
}
/******************************************/
read_lex()
{
  int ddo=0;
  int i=0,j=0,u=0;
  char cvet;
#ifdef NALAD  
  nom_func("268");
#endif          
#ifdef lex_lex//если выполняется конвертация файла lex.lex
  fai=fopen("dat\\lex.lex","r");
  file_soob=creat("dat\\lex.bin",S_IREAD | S_IWRITE | O_BINARY);
  if(fai==NULL)
  {
    gotoxy(5,20);
    printf("Недостаточно данных для запуска программы, проверьте DAT");
    getch();
    exit(0);
  }
  while(1)
  {
    for(u=0;u<60;u++)soob.lex[u]=0x0;
    u=0;
    while(u!='#')
    {
      u=fgetc(fai);
      if(u=='@') goto end;
      if(u=='#') break;
      if(u==0x09) soob.lex[j]=32;
      else soob.lex[j]=u;
      j++;
    }
    j=0;
    u=0;
    fscanf(fai,"%d",&soob.COlo);
    for(u=0;u<60;u++)soob.lex[u]=~soob.lex[u];
    write(file_soob,soob.lex,60);
    cvet=soob.COlo;
    write(file_soob,&cvet,1);
    cvet=10;
    write(file_soob,&cvet,1);
oo:
    ddo=fgetc(fai);
    while(ddo!='\n') goto oo;
  }
end:
	if(fai!=NULL)fclose(fai);
	fai=NULL;
	if(file_soob>0)close(file_soob);
	file_soob=0;
#else
  file_soob=open("dat\\lex.bin",S_IREAD|O_BINARY);
#endif
}
//-------------------------------------------------
prov_lX()
{ long t_lu=0L,t_lv=0L,t_ly=0L,t_lz=0L,t_lc=0L;
  int vi=0,Nmp=0;
#ifdef NALAD  
  nom_func("246");
#endif          
  for(Nmp=0;Nmp<skoko_stoek;Nmp++)
  { if(time_lu[Nmp]!=0L)
    { t_lu=biostime(0,0L);
      if((t_lu-time_lu[Nmp])>=40L)
      { for(vi=0;vi<=14;vi++)if(mas_lu[Nmp][vi]<3)mas_lu[Nmp][vi]=0;
        for(vi=0;vi<=2;vi++)lu[Nmp][vi]='@';
        time_lu[Nmp]=0L;
      }
    }
    if(time_lv[Nmp]!=0L)
    { t_lv=biostime(0,0L);
      if((t_lv-time_lv[Nmp])>=40L)
      { for(vi=0;vi<=14;vi++)if(mas_lv[Nmp][vi]<3);mas_lv[Nmp][vi]=0;
        for(vi=0;vi<=2;vi++)lv[Nmp][vi]='@';
        time_lv[Nmp]=0L;
      }
    }
    if(time_ly[Nmp]!=0L)
    { t_ly=biostime(0,0L);
      if((t_ly-time_ly[Nmp])>=40L)
      { for(vi=0;vi<=15;vi++)if(mas_ly[Nmp][vi]<3)mas_ly[Nmp][vi]=0;
        for(vi=0;vi<=3;vi++)ly[Nmp][vi]='@';
        time_ly[Nmp]=0L;
      }
    }
    if(time_lz[Nmp]!=0L)
    { t_lz=biostime(0,0L);
      if((t_lz-time_lz[Nmp])>=40L)
      { for(vi=0;vi<=15;vi++)if(mas_lz[Nmp][vi]<3)mas_lz[Nmp][vi]=0;
        for(vi=0;vi<=3;vi++)lz[Nmp][vi]='@';
        time_lz[Nmp]=0L;
      }
    }
    if(time_lc[Nmp]!=0L)
    { t_lc=biostime(0,0L);
      if((t_lc-time_lc[Nmp])>=40L)
      { for(vi=0;vi<=15;vi++)if(mas_lc[Nmp][vi]<3)mas_lc[Nmp][vi]=0;
        for(vi=0;vi<=3;vi++)lc[Nmp][vi]='@';
        time_lc[Nmp]=0L;
      }
    }
  } /* for */
}
//---------------------------------------------------------------
z1(int WHO)
{
  int ip,lj,TELL,KSS,KVVv,i33;
#ifdef NALAD  
  nom_func("424");
#endif          
  if(WHO==1) { TELL=TEL1; KSS=KS1; KVVv=KVV1;}
#ifdef KOL_SOO2
  else { TELL=TEL2; KSS=KS2; KVVv=KVV2;}
#endif
  pict1(WHO);
  setcolor(3);
  for(ip=kol_OSN;ip<kol_VO;ip++)
  if(fr1[ip][0]==2)
    if(fr1[ip][13]==WHO)
    {
      bata=0;
      displaysignal(ip,5);
		}
  tel_vkl_vikl(TELL);
  for(lj=Start_R;lj<Start_R+WAZO;lj++)
  {
    if(fr1[lj][13]==WHO)
    {
      krasit_razd(lj,0);
      krasit_razd(lj,2);
    }
  }
  krasit_knopki(Start_R+WAZO,2);
  for(i33=0;i33<kol_OB_UPR;i33++)imena(i33);
#ifdef kol_STY
  Styki();
#endif
  kvadrat();
  //if(zapret[WHO-1]==1||zapret_otv[WHO-1]==1)
  //{
  //  if(WHO==1)w(172,999," 1 ТУМС");
  //  if(WHO==2)w(172,999," 2 ТУМС");
  //}
  //else
  //  if(otkaz_tu[WHO-1]==1)
  //  {
  //    if(WHO==1)w(171,999," 1 ТУМС");
  //    if(WHO==2)w(171,999," 2 ТУМС");
  //  }
  knopka(KSS);
  kvv(KVVv,0);
  if(DISK==0)knopka_OK();
	/*i3 =-1;*/
}
/******************************************/
read_spdlp(void *fai)
{
	//выполнение чтения файла spdlp.dat
	int inn,in1,fu;
#ifdef SPDLP
	inn=fscanf(fai,"%d",&byte_spdlp[0]);//чтение адреса пункта СПДЛП
	if(byte_spdlp[0]>255)
	{
		clrscr(); moveto(80,80);
		outtext("Адрес СПДЛП превышает допустимое значение");
		moveto(80,160);
		outtext("Для выхода из программы нажмите любую клавишу");
		getch();
		exit(1);
	}
	else   adr_spdlp=byte_spdlp[0];
	for(in1=0;in1<N_BIT_SCB;in1++)
	{
		fu=0;while(fu!='\n')fu=fgetc(fai);//поиск конца строки
		inn=fscanf(fai,"%d%d",&byte_spdlp[in1],&bt_spdlp[in1]);//чтение массива СПДЛП
		if(inn!=2)
		{
			clrscr(); moveto(80,80);
			outtext("Нарушена структура файла с данными для СПДЛП spdlp.dat.");
			moveto(80,160);
			outtext("Для выхода из программы нажмите любую клавишу");
			getch();
			exit(1);
		}
	}
		switch(speed_spdlp)
	{
		case 300:    ml_bas=0x80; st_bas=0x01; break;
		case 600:    ml_bas=0xc0; st_bas=0x00; break;
		case 1200:   ml_bas=0x60; st_bas=0x00; break;
		case 2400:   ml_bas=0x30; st_bas=0x00; break;
		case 4800:   ml_bas=0x18; st_bas=0x00; break;
		case 9600:   ml_bas=0x0c; st_bas=0x00; break;
		case 19200:  ml_bas=0x6;  st_bas=0x00; break;
		case 38400:  ml_bas=0x3;  st_bas=0x00; break;
		case 57600:  ml_bas=0x2;  st_bas=0x00; break;
		case 115200: ml_bas=0x1;  st_bas=0x00; break;
		default:  clrscr();moveto(80,80);
							outtext("Неизвестная скорость обмена c СПДЛП");
							getch();exit(1);
	}
	K64=N_BIT_SCB/64;
	K32=0;
	if((N_BIT_SCB-K64*64)>32)K64++;
	else
		if(N_BIT_SCB==K64*64)K32=0;
		else K32=1;
	LEN_SPD=K64*9+K32*5+5;
#endif
}