#include<graphics.h>
#include<bios.h>
#include"bla.h"
/*******************************************************************/
displaystrelka(int oi,int bt_,int povtor)
{
	int ri,
			colc[16],
			ui=0,
			xl,
			yl,
			N_sp,
			sp_s,
			sp_s1,
			zm_sp;
#ifdef NALAD
	nom_func("42");
#endif
	if(fr3[oi][5]==1)
	{
		if(tst_fix(oi,5)){slom_interf(oi);fix(oi,5);}
	}
	if(fr3[oi][4]==1)//если есть потеря контроля
	{
		if(tst_fix(oi,4))//если нет реакции оператора и не было записи на диск
		{
#ifdef AVTOD
			if(na==1)
			{
				for(ui=0;ui<N_str;ui++)
				{
					if(N_strel[ui]==oi)
					{
						snyato_avto(1);
						w(149,oi,"");
						zvuk_vkl(0,0);
					}
				}
			}
			if(cha==1)
			{
				for(ui=0;ui<CH_str;ui++)
				{
					if(C_strel[ui]==oi)
					{
						snyato_avto(2);
						w(149,oi,"");
						zvuk_vkl(0,0);
					}
				}
			}
#endif
			if(povtor==0)
			{
				for(ui=0;ui<20;ui++)chudo[ui]=0;
				ui=0;
				while(pako[oi][ui]!=':')chudo[ui]=pako[oi][ui++];
				w(127,999,chudo);//НЕ ИМЕЕТ КОНТРОЛЯ СТРЕЛКА
				strcat(chudo,"-без_к.");
				neisprav_na_disk('#',chudo);
				zvuk_vkl(3,0);
			}
			fix(oi,4);
		}
	}
	if(fr3[oi][4]==0)//если восстановлен контроль и первая стрелка
	{
		if(tst_fix(oi,4)&&(povtor==0))
		{
			for(ui=0;ui<20;ui++)chudo[ui]=0;
			ui=0;
			while(pako[oi][ui]!=':')chudo[ui]=pako[oi][ui++];
			w(227,999,chudo);//ВОССТАНОВЛЕН КОНТРОЛЬ СТРЕЛКИ
			strcat(chudo,"-есть_к.");
			neisprav_na_disk('#',chudo);
			zvuk_vkl(0,0);
		}
		fix(oi,4);  //----------------- seg021:02C4   
	}
	if(bt_==3)//если бит неустановки стрелки    seg021:02CB 
	{
    if(tst_fix(oi,bt_))//если нет реакции оператора и не было записи на диск
    {
			if(fr3[oi][3]==1)//если есть неустановка и первая стрелка
      {
        w(99,oi," НЕ ПЕРЕВЕДЕНА");//СТРЕЛКА НЕ УСТАНОВЛЕНА
        zvuk_vkl(3,0);
			}
		}
		fix(oi,bt_);
	}
	//------------------ seg021:0321 loc_57751:
	if((bt_!=5)&&(bt_>1))
		goto vyh;
	
	if((nikuda==1)||(klo==1)||(help!=0))
		goto vyh;
beg:	
	if(fr2[oi][0]!=0)//если стрелка рисуется    seg021:0365
	{
		if(fr1[oi][6]!=0)//если крестовая
		{
			sp_s = (fr1[oi][6]&0xff00)>>8;  //получить объект для СП этой стрелки  seg021:03A3
			sp_s1 = (fr1[ris_krest&0xfff][6]&0xff00)>>8;
			zm_sp = fr3[sp_s][1]|fr3[sp_s1][1];//получить значение замыкания
			ris_krest = 0; //----------------------------------------------- seg021:03FF
			krest(sp_s,1,zm_sp); //----------------------------------------- seg021:0410
		}
		else
		{
			zap_matr(oi);  //---------------------------- seg021:041B
			cvet_matr();
			ris_sp_str();
		}
		N_sp = SP_STR[0][0];
		setcolor(8);  //-------------------------------------- seg021:043B
		if((fr1[oi][10]&8)==8)//если охранная стрелка плюсовая
		{
			if(((fr3[oi][0]!=1)||(fr3[oi][1]!=0))&&(fr3[N_sp][1]!=1))
				setcolor(12);  //------------------------------- seg021:04A3
		}
		if((fr1[oi][10]&4)==4)//если охранная стрелка минусовая
		{
			if((fr3[oi][0]!=0)||(fr3[oi][1]!=1)&&( fr3[N_sp][1]!=1))
				setcolor(12);  //----------------------------------- seg021:050B
		}
		if(((fr1[oi][10]&4)==4)||((fr1[oi][10]&8)==8))
		{
			if(fr1[oi][9]==0)
				yl = fr2[oi][1] + 20;  //-------------------------------- seg021:0573 
			if(fr1[oi][9]==1)
				yl = fr2[oi][1]-20;
			if((fr1[oi][7]==0)&&(OBRAT==1))
				xl=fr2[oi][0]-3;  //---------------------------------- seg021:05CB
			if((fr1[oi][7]==1)&&(OBRAT==-1))
				xl=fr2[oi][0]-3;
			if((fr1[oi][7]==0)&&(OBRAT==-1))
				xl=fr2[oi][0]+3;
			if((fr1[oi][7]==1)&&(OBRAT==1))
				xl=fr2[oi][0]+3; //---------------------------- seg021:0653
			for(ui=3;ui>0;ui--)
				circle(xl,yl,ui);  //------------------------------------ seg021:0662
		}
	}
	else //--------------------------------- seg021:0672 loc_57AA2:
	{
		setlinestyle(0,0,0);  //---------------------------- seg021:067B
		if(fr2[oi][12]!=0)  //----------------------------- seg021:06A7
		{
			if(fr3[oi][5]==1)
      {
				setcolor(11);
    		for(ui=4;ui>0;ui--)
					circle(fr2[oi][12],fr2[oi][13],ui); //seg021:06DF 
      	for(ui=4;ui>0;ui--)
					circle(fr2[oi][14],fr2[oi][15],ui); //seg021:0712
      }
      else
      { //----------------------- seg021:0722 loc_57B52: 
		  	if(fr3[oi][0]==1) //------------------ seg021:0730 
				{
					if(fr3[oi][1]==0)
					{
						setcolor(10);
          	for(ui=4;ui>0;ui--)circle(fr2[oi][12],fr2[oi][13],ui);
	          setcolor(8);
  	        for(ui=4;ui>0;ui--)circle(fr2[oi][14],fr2[oi][15],ui);
    	    }
      		else
					{
						setcolor(13);
	          for(ui=4;ui>0;ui--)circle(fr2[oi][12],fr2[oi][13],ui);
  	        for(ui=4;ui>0;ui--)circle(fr2[oi][14],fr2[oi][15],ui);
    	    }
	    	}
	  	  
				if(fr3[oi][0]==0) //--------------------------- seg021:084B
				{
					if(fr3[oi][1]==1)  //------------------------ seg021:0864 
					{
						setcolor(8);
          	for(ui=4;ui>0;ui--)circle(fr2[oi][12],fr2[oi][13],ui);
	          setcolor(14);
  	        for(ui=4;ui>0;ui--)circle(fr2[oi][14],fr2[oi][15],ui);
      	  }
		      else
					{
						setcolor(13);
      	    for(ui=4;ui>0;ui--)circle(fr2[oi][12],fr2[oi][13],ui);
        	  for(ui=4;ui>0;ui--)circle(fr2[oi][14],fr2[oi][15],ui);
		      }
  		  }		
    	}
  	}
  }
	if(fr1[oi][12] == 1)
	{
		oi = poisk_ras(fr1[oi][2],oi);
		goto beg;
	}	
vyh:
	return;
}
#ifdef AVTOVOZVRAT
//-----------------------------------------------------------
prov_av_str(int strf,int uchf,int mspf,int m_b,int param)
{//проверка стрелки на наличие автовозврата и выдача команды при необходимости
 //strf - объект для стрелки
 //uchf - объект для охранного участка СП
 //mspf - объект для МСП
 //m_b - номер бита для объекта МСП
 //param - признак объекта, по которому прошло изменение
	int x,y,ra,wr,poH=0,x_kir,y_kir,kod,lu,b_lu,MSP,B_MSP,ij,hod;
#ifdef NALAD
	nom_func("241");
#endif
	if((klo==1)||(help>0)||(nikuda==1))return;
	wr = 0;
	hod = 0;
proc:
	switch(param)
	{
		case 2: //если произошло изменение СП
						if(hod==0)
						{
							for(wr=wr;wr<Kol_avstr;wr++)// по всем стрелкам с автовозвратом
							if(coAV[wr].N_spu1==uchf)break;//если данное СП участвует-выйти
						}
						if(wr>=Kol_avstr)//если СП не найдено
						{
							hod=1;
							for(wr=0;wr<Kol_avstr;wr++)//поискать во втором СП
							if((coAV[wr].N_spu2==uchf)&&(coAV[wr].N_spu2!=0))break;
            }
            break;
    case 4: //если произошло изменение МСП
            for(wr=wr;wr<Kol_avstr;wr++)//поискать МСП
            {
              MSP=coAV[wr].MSP1&0xfff;
              B_MSP=(coAV[wr].MSP1&0xf000)>>12;
            	if((MSP==mspf)&&(B_MSP==m_b)) break;
            }
            break;
   default: return;
  }
  if(wr>=Kol_avstr)return;//если данная стрелка без автовозврата, выйти
  x=coAV[wr].Sx;// для стрелок с автовозвратом получить координаты лампочки
  y=coAV[wr].Sy;
  ra=coAV[wr].Sra;//взять радиус лампочки
  strf=coAV[wr].N_sst;//получить стрелку с автовозвратом
  lu=coAV[wr].LU&0xfff;//получить объект ЛУ
  b_lu=(coAV[wr].LU&0xf000)>>12;//получить бит ЛУ
kirp:
  //если стрелка парная и сбрасывающая - найти вторую

  kod=0;
	if((fr1[strf][11]&256)==256)
  {
//    if(fr1[strf][12]==0)strf=poisk_ras(fr1[strf][2],strf);
  	kod=fr1[strf][7]+OBRAT*2;//получить код входа
  	switch(kod)
  	{
    	case -2:  //в зависимости от ориентации получить координаты "кирпича"
    	case 3:   if(fr2[strf][0]<fr2[strf][2])
      	        {
        	        x_kir=fr2[strf][0]; y_kir=fr2[strf][1];ij=1;break;
          	    }
            	  else
              	{
                	x_kir=fr2[strf][2]; y_kir=fr2[strf][3];ij=1; break;
	              }
  	  case 2:
    	case -1:  if(fr2[strf][0]<fr2[strf][2])
      	        {
        	        x_kir=fr2[strf][2]; y_kir=fr2[strf][3];ij=-1; break;
          	    }
            	  else
              	{
                	x_kir=fr2[strf][0]; y_kir=fr2[strf][1];ij=-1; break;
	              }
  	  default:  break;
    }

  }
  //если стрелка в плюсе или в минусе,и соответствует охранному
  if((fr3[coAV[wr].N_sst][0]==coAV[wr].b0)&&(fr3[coAV[wr].N_sst][1]==coAV[wr].b1))
  { //сбросить все флаги и изобразить красный кирпич в тупике
    coAV[wr].Fl_kom=0;
    setfillstyle(1,12);
		if(kod!=0)bar(x_kir-4*ij,y_kir-3,x_kir-1*ij,y_kir+3);
    setcolor(8);//установить серый цвет
  }
  else //если положение не охранное
  { setfillstyle(1,7);
		if(kod!=0)bar(x_kir-4*ij,y_kir-3,x_kir-1*ij,y_kir+3);//стереть кирпич
    if((fr1[strf][10]&16)!=16)goto risun;//если нет автовозврата - рисовать
// если одно СП
    if(coAV[wr].N_spu2==0)
		{ //если СП замкнуто
			if(fr3[coAV[wr].N_spu1][1]==1)
      //взвести флаг команды и установить серый цвет
      { coAV[wr].Fl_kom=1; setcolor(8);}
      else//если СП разомкнуто, то проверить МСП
      { MSP=coAV[wr].MSP1&0xfff;B_MSP=(coAV[wr].MSP1&0xf000)>>12;
msp:    if(fr3[MSP][B_MSP]==1)//если МСП не готово установить желтый цвет
        { setcolor(14);
          if(fr3[lu][b_lu]==1)coAV[wr].Fl_kom=0;//если ЛУ - сбросить флаг
        }
        else //если МСП готово
        {
					setcolor(12);
					if(coAV[wr].Fl_kom==1)
					{

						if(pooo[coAV[wr].N_sst]==0)pooo[coAV[wr].N_sst]=biostime(0,0l);
						else
						if((biostime(0,0l)-pooo[coAV[wr].N_sst])>18l)
						{
							coAV[wr].Fl_kom=2;
							pooo[coAV[wr].N_sst]=0;
							com_avtovozvr(wr);
							setcolor(12);
						}
					}
				}
			}
		}
//если есть второе СП
		else
		{ //если оба СП замкнуты
			if((fr3[coAV[wr].N_spu1][1]==1)&&(fr3[coAV[wr].N_spu2][1]==1))
			{coAV[wr].Fl_kom=1;setcolor(8);}
			else
				 //если замкнуто только второе
				if((fr3[coAV[wr].N_spu1][1]==0)&&(fr3[coAV[wr].N_spu2][1]==1))
				{coAV[wr].Fl_kom=1;setcolor(8);}
				else
					 //если замкнуто только первоое
					if((fr3[coAV[wr].N_spu1][1]==1)&&(fr3[coAV[wr].N_spu2][1]==0))
      		{coAV[wr].Fl_kom=1;setcolor(8);}
          //если все разомкнулось
      		else
					{
            MSP=coAV[wr].MSP1&0xfff;
            B_MSP=(coAV[wr].MSP1&0xf000)>>12;
    				if(fr3[MSP][B_MSP]==1)//если МСП1 не готово
        		{
							setcolor(14);//установить желтый цвет
          		if(fr3[lu][b_lu]==1)coAV[wr].Fl_kom=0;//если ЛУ - сбросить флаг
        		}
            else//если 1-ое МСП готово
            {
							MSP=coAV[wr].MSP2&0xfff;
							B_MSP=(coAV[wr].MSP2&0xf000)>>12;
    					if((fr3[MSP][B_MSP]==1)&&(MSP!=0))//если МСП2 не готово
        			{
								setcolor(14);//установить желтый цвет
          			if(fr3[lu][b_lu]==1)coAV[wr].Fl_kom=0;//если ЛУ - сбросить флаг
        			}
							else //если МСП готовы
							{
								setcolor(12);
								if(coAV[wr].Fl_kom==1)
								{
									if(pooo[coAV[wr].N_sst]==0)pooo[coAV[wr].N_sst]=biostime(0,0l);
									else
									if((biostime(0,0l)-pooo[coAV[wr].N_sst])>18l)
									{
										pooo[coAV[wr].N_sst]=0;
										coAV[wr].Fl_kom=2;
										com_avtovozvr(wr);
										setcolor(12);
									}
								}
							}
            }
					}
    }
  }
risun:
  if((fr3[strf][5]==1)||(fr3[coAV[wr].N_spu1][5]==1)||
	(fr3[coAV[wr].MSP1&0xfff][5]==1))
	setcolor(LIGHTCYAN);
  
	if(coAV[wr].N_spu2!=0)
 	if(fr3[coAV[wr].N_spu2&0xfff][5]==1) 
	setcolor(LIGHTCYAN);
  //------------------------------------------ seg021:143C loc_5886C:
	setlinestyle(0,0,0);
  
	if((fr1[strf][10]&16)==16)
		for(ij=0;ij<ra;ij++)
			circle(x,y,ij);
	
	if(wr < (Kol_avstr-1))
	{
		wr++;
		goto proc;
	}
}
#endif
//-----------------------------------------------------------
int poisk_ras (int nomer,int otkuda)// вход с номером объекта, указанным переходом
{
  int oi,dvig,klp=9999,klop=9999;
#ifdef NALAD
  nom_func("231");
#endif
  klop=nomer;
  if(fr1[klop][0]==6) // если это переход
  { if(fr1[klop][1]==otkuda)//если ссылка туда откуда пришли
    { if(TEST==0){if(trassa[ukaz_trass]==0xFFFF)trassa[ukaz_trass++]=klop;}
      else
      if(TEST==1){if(trassa_osn[ukaz_trass]==0xFFFF)trassa_osn[ukaz_trass++]=klop;}
aa:
      klp=otkuda;
      if((fr1[klp][8]&0x8000)!=0)dvig=-1;
      else dvig=1;
      klop=klop+dvig;
      if((fr1[klop][0]==7)&&(FLAG_PO==1)&&(TEST!=2))// если это ДЗ и делается поворот
      { // если маршрутное управление, то запомнить элемент в трассе
        if(uprav==1)
        { if(TEST==0)trassa[ukaz_trass++]=klop;
          else trassa_osn[ukaz_trass++]=klop;
        }
        else  trassa[ukaz_trass++]=klop;//для раздельн. управления++
      }
      if((fr1[klop][0]>=1)&&(fr1[klop][0]<=5))return(klop);
      if(fr1[klop][0]!=6) goto aa;
      else
      { if(TEST==0){if(trassa[ukaz_trass]==0xFFFF)trassa[ukaz_trass++]=klop;}
        else
        if(TEST==1){if(trassa_osn[ukaz_trass]==0xFFFF)trassa_osn[ukaz_trass++]=klop;}
        klop=fr1[klop][1];
        return(klop);
      }
    }
    else klop=fr1[klop][1];
  }
  return(klop);
}
//----------------------------------
com_avtovozvr(int wr)
{
	int poH;
	if(coAV[wr].Fl_kom>1) //если флаг взведен
  { AVARIIN=1;
    point=coAV[wr].N_sst;//взять стрелку
    if(pooo[point]!=0l)return;
    if(coAV[wr].b0==1)poH=1; //взять охранное положение
    else poH=-1;
    if((TELEUP==1)&&(STATUS==1)&&(DU==0))//если телеуправление наше
    {
			if(tst_str(point,poH)==0)//если стрелку можно переводить
      { if(poH==1) oper='A';//выбрать код команды перевода стрелки
        else oper='B';
        coAV[wr].Fl_kom=0;
				formkps(oper);//сформировать команду для перевода
				prorisovka=0;
				w(123,point,"");//ПОСЫЛАЕМ КОМАНДУ НА ПЕРЕВОД СТРЕЛКИ
				okno_otkaz=1;
      }
    }
    AVARIIN=0;
    coAV[wr].Fl_kom=0;//сбросить флаг команды
  }
}
//-------------------------------------------------------
// процедура оценки четности или нечетности стрелки ob
// по имени стрелки
// возвращает 0 для четной стрелки
// возвращает 1 для нечетной стрелки
int tst_chet(int ob)
{
	int ns,jj;
  char strlk[10];
  for(ns=0;ns<10;ns++)strlk[ns]=0;
  ns=0;
  while(isdigit(pako[ob][ns])==0)ns++;
  jj=0;
  while(isdigit(pako[ob][ns])!=0)strlk[jj]=pako[ob][ns++];
  ns=atoi(strlk);
  if((ns%2)==0)return(0);
  else return(1);
}
