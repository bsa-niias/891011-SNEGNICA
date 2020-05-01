#include"bla.h"
#include<dos.h>
#include<bios.h>
#include<alloc.h>
#include<stdio.h>
#include<io.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<graphics.h>
#include<string.h>
void fix(int ob,int bt);
/***************************************/
void uksps(int nom)//nom-номер объекта
{
	int ij,
  ob1_1=0,//первый датчик УКСПС 1-го перегона
  bt1_1=0,//бит первого датчика УКСПС 1-го перегона
  ob1_2=0,//второй датчик УКСПС 1-го перегона
  bt1_2=0,//бит второго датчика УКСПС 1-го перегона
  kz1=0, //датчик контроля линии 1-го перегона
  bt_kz1=0,//бит датчика контроля линии 1-го перегона
  otkl1=0,//отключатель УКСПС 1-го перегона
  bt_otkl1=0,//бит отключателя УКСПС 1-го перегона
  isk1=0,//исключатель УКСПС 1-го перегона
	bt_isk1=0, //бит исключателя УКСПС 1-го перегона
  ob2_1=0,//первый датчик УКСПС 2-го перегона
  bt2_1=0,//бит первого датчика УКСПС 2-го перегона
  ob2_2=0,//второй датчик УКСПС 2-го перегона
  bt2_2=0,//бит второго датчика УКСПС 2-го перегона
  kz2=0, //датчик контроля линии 2-го перегона
  bt_kz2=0,//бит датчика контроля линии 2-го перегона
	otkl2=0,//отключатель УКСПС 2-го перегона
	bt_otkl2=0,//бит отключателя УКСПС 2-го перегона
	isk2=0,//исключатель УКСПС 2-го перегона
	bt_isk2=0, //бит исключателя УКСПС 2-го перегона
		xp,//координата X для 1-го датчика УКСПС
		yp,//координата Y для 2-го датчика УКСПС
 //		dx,//смещение по X для 2-го датчика УКСПС относительно 1-го
	hod=0,
	cod=0,
	cod1=0,
	cod2=0,
	ob,
	bit1,
	bit2,
	kz=0,
	bt_kz,
	isk=0,
	bt_isk,
	otkl=0,
	bt_otkl,
	cv_da1,
	cv_da2,
	cv_kn,
	cv_lam,
	mark=0,
	otk_uksps=0,
	bt_otk;
  char kod[3];

	nom_func("383");

  if(fr1[nom][1]==28)//если получены данные по датчикам УКСПС
  {
		//seg005:00D4  - seg005:00E2 
		if(fr1[nom][2]!=9999)
			//seg005:00EB - seg005:0101
			nom=fr1[nom][2]&0xfff;//если есть управление УКСПС
		else
			goto met0;//если нет управления, то перейти
  }
 // seg005:0108 loc_20408:
	//объект управления УКСПС данного перегона
  if(fr1[nom][1]==27)//если получены данные по объекту управления
  {
		//seg005:0121 loc_20421: - seg005:0137  
		mark = fr1[nom][3]&0xfff; //номер объекта управления в markery
		
		//seg005:0150 
    ob1_1 = fr1[nom][4]&0xfff;//это УКСПС_1 1-го перегона
		
		//seg005:016C 
    bt1_1=(fr1[nom][4]&0xf000)>>12;//это бит УКСПС_1 1-го перегона
    
		//seg005:017D 
		if(fr1[nom][5]!=9999)//если есть второй датчик
    {
			//seg005:019C
      ob1_2=fr1[nom][5]&0xfff;//это УКСПС_2 1-го перегона
			//seg005:01B9 
      bt1_2=(fr1[nom][5]&0xf000)>>12; //это бит УКСПС_2 1-го перегона
    }
    else
			//seg005:01BE loc_204BE:
			ob1_2=9999;

    //seg005:01D1
		if(fr1[nom][7]!=9999)//если в объекте участвует второй перегон
    {
			//seg005:01F3 
      ob2_1=fr1[nom][7]&0xfff;//это УКСПС_1 2-го перегона
     //seg005:0210 
			bt2_1=(fr1[nom][7]&0xf000)>>12; //это бит УКСПС_1 2-го перегона
			//seg005:0221
      if(fr1[nom][8]!=9999)
      {
				//seg005:0240  
        ob2_2=fr1[nom][8]&0xfff;//это УКСПС_2 2-го перегона
				//seg005:025D 
        bt2_2=(fr1[nom][8]&0xf000)>>12;//это бит УКСПС_2 2-го перегона
      }
      else 
				//seg005:0262 loc_20562:
				ob2_2=9999;
    }
	}
	//seg005:0267 loc_20567:
met0:
  if(ob1_1==0)//если нет объекта управления
  {
		//seg005:0284 
    ob1_1 = fr1[nom][6]&0xfff;//первый датчик этого перегона
    //seg005:02A0 
		bt1_1=(fr1[nom][6]&0xf000)>>12;//бит первого датчика УКСПС этого перегона
		//seg005:02B1 
		if(fr1[nom][7]!=9999)//если есть второй датчик для этого перегона
    {
      ob1_2=fr1[nom][7]&0xfff;//второй датчик этого перегона
      bt1_2=(fr1[nom][7]&0xf000)>>12;//бит второго датчика УКСПС этого перегона
    }
    else ob1_2=9999;
  }
	//seg005:0305  
  if(fr1[ob1_1][9]!=9999)//если есть контроль линии первого перегона
  {
    kz1=fr1[ob1_1][9]&0xfff;//это датчик контроля линии 1-го перегона
    bt_kz1=(fr1[ob1_1][9]&0xf000)>>12;//это бит контроля линии 1-го перегона
  }
	//seg005:0344 loc_20644: - seg005:0352
  if(fr1[ob1_1][10]!=9999)//если есть объект исключения первого перегона
  {
    isk1=fr1[ob1_1][10]&0xfff;//это датчик контроля линии 1-го перегона
    bt_isk1=(fr1[ob1_1][10]&0xf000)>>12;//это бит контроля линии 1-го перегона
  }
	//seg005:0391 loc_20691:
	if(ob2_1!=0)//если есть второй перегон для объекта управления
  {
		//seg005:039A loc_2069A - seg005:03A9 
		if(fr1[ob2_1][9]!=9999)//если есть контроль линии 2-го перегона
    {
      kz2=fr1[ob2_1][9]&0xfff;//это датчик контроля линии 2-го перегона
      bt_kz2=(fr1[ob2_1][9]&0xf000)>>12;//это бит контроля линии 2-го перегона
    }
	  //seg005:03EA loc_206EA - seg005:03F9		
    if(fr1[ob2_1][10]!=9999)//если есть объект исключения 2-го перегона
    {
      isk2=fr1[ob2_1][10]&0xfff;//это датчик контроля линии 2-го перегона
      bt_isk2=(fr1[nom][9]&0xf000)>>12;//это бит контроля линии 2-го перегона
    }
  }
  
	
	//seg005:0439 loc_20739: - 
	if(fr1[ob1_1][2]!=9999)//если есть управление
  {
      otkl1=fr1[ob1_1][2]&0xfff;
      bt_otkl1=(fr1[ob1_1][2]&0xf000)>>12;
  }
  
	//seg005:0486 loc_20786: 
	if((ob2_1!=0)&&(fr1[ob2_1][2]!=9999))
  {
      otkl2=fr1[ob2_1][2]&0xfff;
			bt_otkl2=(fr1[ob2_1][2]&0xf000)>>12;
  }

	//seg005:04DC loc_207DC: 
	if(ob1_2!=9999)
	cod1 = fr3[ob1_1][bt1_1] * 4 +
				 fr3[ob1_2][bt1_2] * 2 +
				 fr3[isk1][bt_isk1];    //1 перегон
	else
	cod1=fr3[ob1_1][bt1_1]*4+fr3[isk1][bt_isk1];//1 перегон
	
	//seg005:057F 
	if(ob2_2!=9999)
	cod2=fr3[ob2_1][bt2_1]*4+fr3[ob2_2][bt2_2]*2+fr3[isk2][bt_isk2];//2 перегон
	else
		cod2 = fr3[ob2_1][bt2_1]*4 + fr3[isk2][bt_isk2];//2 перегон

	//seg005:0624
	if(cod1>1)//если сработал УКСПС первого перегона
  {
    if(((OBRAT==1)&&(fr1[ob1_1][11]==0))||//если четн.прием и УКСПС слева
    ((OBRAT==-1)&&(fr1[ob1_1][11]==1)))//или если четн.прием и УКСПС справа
    {
				//seg005:0660
				if(cha==1)//если установлено четное автодействие
				{
					//seg005:066E
					zvuk_vkl(0,0);
					//seg005:0682 
					w(169,999,"УКСПС ЧЕТ.АВТОД.СНЯТО!");
					//seg005:068A 
					snyato_chet();
				}
			}
			if(((OBRAT==-1)&&(fr1[ob1_1][11]==0))||//если нечетный прием и УКСПС слева
			((OBRAT==1)&&(fr1[ob1_1][11]==1)))//если нечетный прием и УКСПС справа
			{
				if(na==1)
				{
					zvuk_vkl(0,0);
					w(169,999,"УКСПС НЕЧЕТ.АВТОД.СНЯТО!");
					snyato_nechet();
				}
			}
		}

//seg005:06F1
met1:
	if(hod==0)
	{
		cod=cod1;
		ob=ob1_1;
		bit1=bt1_1;
		bit2=bt1_2;
		kz=kz1;
		bt_kz=bt_kz1;
		isk=isk1;
		bt_isk=bt_isk1;
		otkl=otkl1;
		bt_otkl=bt_otkl1;
	}
	else
	//seg005:072F loc_20A2F:	
	{
		cod=cod2;
		ob=ob2_1;
		bit1=bt2_1;
		bit2=bt2_2;
		kz=kz2;
		bt_kz=bt_kz2;
		isk=isk2;
		bt_isk=bt_isk2;
		otkl=otkl2;
		bt_otkl=bt_otkl2;
	}
	//seg005:076E 
	switch(cod)
	{
		//seg005:077A loc_20A7A:
		case 0: 
			cv_da1= 8;
			cv_da2= 8;
			goto ris;
		//seg005:0787 loc_20A87: 	
		case 1: 
			cv_da1= 14;
			cv_da2=14;
			goto ris;
		//seg005:0794 loc_20A94: 	
		case 4: 
			cv_da1=12;
			cv_da2= 8;
			if(hod==0)
			{
				otk_uksps = ob1_1;
				bt_otk = bt1_1;
			}
			else 
			{
				otk_uksps = ob2_1;
				bt_otk = bt2_1;
			}
			goto ris;
		case 5: 
			cv_da1=14;
			cv_da2= 8;
			goto ris;
		default: 
					break;
	}
	
	if((fr1[ob][12]&0xff00)==0xff00)//если индикация участков зависимая
	{
		switch(cod)
		{
			case 2: 
				cv_da1=7;
				cv_da2=12;
				if(hod==0)
					{otk_uksps=ob1_2;bt_otk=bt1_2;}
        else 
					{otk_uksps=ob2_2;bt_otk=bt2_2;}
        goto ris;
      case 3: 
				cv_da1=7;
				cv_da2=14;
				break;
      case 6: 
				cv_da1=7;
				cv_da2=12;
        otk_uksps=fr1[ob][7]&0xfff;
        bt_otk=(fr1[ob][7]&0xf000)>>12;
        break;
      case 7: 
				cv_da1=7;
				cv_da2=14;
				break;
    }
    goto ris;
  }
  else //если индикация участков независимая
  {
    switch(cod)
    {
      case 2: 
				cv_da1=8;cv_da2=12;
        if(hod==0)
					{otk_uksps=ob1_2;bt_otk=bt1_2;}
        else 
					{otk_uksps=ob2_2;bt_otk=bt2_2;}
        goto ris;
      case 3: 
				cv_da1=8;
				cv_da2=14;
				break;
      case 6: 
				cv_da1=12;
				cv_da2=12;
        otk_uksps=fr1[ob][7]&0xfff;
        bt_otk=(fr1[ob][7]&0xf000)>>12;
        break;
      case 7: 
				cv_da1=14;
				cv_da2=14;
				break;
    }
    goto ris;
  }
//seg005:0911	
ris:
  if(otk_uksps==9999)
  { 
		if(hod=0)
		{
			bit1=bt1_1;
			bit2=bt1_2;
		}
    else 
		{
			bit1=bt2_1;
			bit2=bt2_2;
		}
		//seg005:0943 		
    if(tst_fix(ob,bit1))
    {
			if(get_str(ob,bit1)==0) neisprav_na_disk('@',chudo);
      w(169,999,chudo);
      zvuk_vkl(0,0);
      home(modi);
      fix(ob,bit1);
    }
		//seg005:09B3 loc_20CB3: 
    if(tst_fix(ob,bit2))
    {
      if(get_str(ob,bit2)==0)neisprav_na_disk('@',chudo);
      w(169,999,chudo);
      zvuk_vkl(0,0);
      home(modi);
      fix(ob,bit2);
    }
  }
  else
  if(otk_uksps>0)
  {
    if(tst_fix(otk_uksps,bt_otk))
    {
      if(get_str(otk_uksps,bt_otk)==0) neisprav_na_disk('@',chudo);
      w(169,999,chudo);
      zvuk_vkl(0,0);
      home(modi);
      fix(otk_uksps,bt_otk);
    }
  }
	//seg005:0AAB loc_20DAB:
  if(kz!=0)//если есть контроль линии
  {
		//seg005:0AC7 
    if(fr3[kz][bt_kz]==0)
			cv_lam=0;
    else 
			cv_lam=12;
  }
  else 
		cv_lam=0;
	//seg005:0AE2 loc_20DE2:  
  if((klo==1)||(help>0)||(nikuda==1))
		return;
  //seg005:0B1B
	if(fr3[ob][5]==1)
	{
		cv_da1=LIGHTCYAN;
		cv_da2=LIGHTCYAN;
	}
	//seg005:0B2D loc_20E2D: 
  if((kz!=0)&&(fr3[kz][5]==1))
		cv_lam=LIGHTCYAN;
	
	//seg005:0B4F loc_20E4F:
  setfillstyle(1,cv_da1);
  yp=fr1[ob1_1][4];// координата Y датчика 1
  xp=fr1[ob1_1][3];// координата X датчика 1
	//seg005:0B9D  
  bar(xp,yp,xp+5,yp+5);
  if(fr1[ob1_1][5]!=0)//если есть второй датчик
  {
    xp=fr1[ob1_1][3]+fr1[ob1_1][5];
    setfillstyle(SOLID_FILL,cv_da2);
    bar(xp,yp,xp+5,yp+5);
  }
  //seg005:0C10 loc_20F10: 
	if(mark!=0)
  {
		//seg005:0C2F
    if(fr3[otkl][bt_otkl]==0)
			cv_kn=8;
    else
      if(fr3[otkl][bt_otkl]==1)
				cv_kn=14;
      else 
				cv_kn=5;
		//seg005:0C68 loc_20F68 - seg005:0C77
    if(fr3[otkl][5]==1)
			cv_kn=11;
		//seg005:0C8B
    setfillstyle(SOLID_FILL,cv_kn);
    // координаты кнопки
    xp=markery[mark][4];  //seg005:0CA3 
		yp=markery[mark][5];  //seg005:0CB7 
	  //seg005:0CD6
    bar(xp-4,yp-4,xp+4,yp+4);
		//seg005:0CED  
    if(fr3[otkl][0]==1)
    {
      if(cv_kn!=11)
      {
        setfillstyle(1,14);
        bar(xp-4,yp-4,xp+4,yp);
        if(oppp==2)w(12,999,"");
      }
    }
		setlinestyle(0,0,0);
		//------------------------------ seg005:0D5D
    if(cv_lam!=0)
    {
      setcolor(cv_lam);
			if(tst_fix(kz,bt_kz))
      {
        if(get_str(kz,bt_kz)==0) neisprav_na_disk('@',chudo);
				w(169,999,chudo);
				zvuk_vkl(1,18);
        fix(kz,bt_kz);
      }
      for(ij=3;ij>=0;ij--)circle(xp,yp,ij);
    }
		else fix(kz,bt_kz);
    if((hod==0)&&(ob2_1!=0)){hod=2;goto met1;}
    else return;
  }
end:
  //если нет управления УКСПС
  if(fr3[nom][0]==1)cv_lam=12;
  if(fr3[nom][0]==0)cv_lam=8;
  if(fr3[nom][5]==1)cv_lam=11;
  setfillstyle(SOLID_FILL,cv_lam);
  if(cv_lam!=8)
  if(get_str(nom,0)==0)neisprav_na_disk('@',chudo);
  yp=fr1[nom][4];// координата Y датчика
  xp=fr1[nom][3];// координата X датчика
  bar(xp,yp,xp+5,yp+5);
  return;
}
//-----------------------------------------------------------
//Процедура отображения, фиксации неисправностей на диске, вывода
//предупреждения на экран и выдачи звукового сигнала для датчиков
//состояния фидеров
void fider3dat(int nom,int bit_)
{
  int goj,//радиус изображения лампы состояния фидера
  F1,//цвет лампы первого фидера
  F2,//цвет лампы второго фидера
  cod_fider;//код состояния фидеров
  
	nom_func("53");

  if(bit_>=fr1[nom][11])return;//если передан не предусмотренный бит - выйти
  if((klo==1)||(help!=0)||(nikuda==1))return;
 //1вф*4+2ф*2+1ф - данные формирования кода состояния фидеров
  cod_fider=fr3[nom][2]*4+fr3[nom][1]*2+fr3[nom][0];
  switch(cod_fider)//в зависимости от состояния фидеров назначить цвета
  {
    case 0: F1=10;F2=14;break;
    case 1: F1=4; F2=14;break;
    case 2: F1=10;F2=4; break;
    case 3: F1=4; F2=4; break;
    case 4: F1=14;F2=10;break;
    case 5: F1=4; F2=10;break;
    case 6: F1=14;F2=4; break;
    case 7: F1=4; F2=4; break;
  }

  if((F1==4)||(F2==4))//если для одного из фидеров назначен красный
  {
    if(tst_fix(nom,bit_)&&fr3[nom][bit_])//если бит==1 и не фиксирован ранее
    {
      if(get_str(nom,bit_)==0)//если найдено название объекта для бита
      {
        neisprav_na_disk('%',chudo);//запись на диск(раздел устройств питания)
        w(169,999,chudo);//вывод на экран текста
        zvuk_vkl(1,18l);//включить звук на 1 сек
      }
    }
  }
  fix(nom,bit_);//установить признак фиксации события
  /*****************************/
  if(fr3[nom][5]==1)setcolor(11);//если имеется непарафазность - цвет циан
  else setcolor(F1);//иначе цвет 1-го фидера установить по коду
  setlinestyle(0,0,0);//назначить тонкую линию
  for(goj=1;goj<fr1[nom][11];goj++)circle(fr1[nom][3+2*0],fr1[nom][4+2*0],goj);
  if(fr3[nom][5]==1)setcolor(11);
  else setcolor(F2);
  for(goj=1;goj<fr1[nom][11];goj++)circle(fr1[nom][3+2*1],fr1[nom][4+2*1],goj);
}

//----------------------------------------------------------------
//изображение на экране лампы для объекта nom и бита bit_
void lampa(int nom,int bit_)
{
  int goj,rad,ZZ,CC;
  unsigned char objkt_z;

	nom_func("141");
     
  if((klo==1)||(help!=0)||(nikuda==1))return;
  if(fr1[nom][2*bit_+3]==9999)return;//если для бита не определена коорд. X
  ZZ=(fr1[nom][2]&0xFF00)>>8;
  CC=fr1[nom][2]&0xff;
  //если объект связан с кнопкой аварийного перевода стрелок
  if(((nom==AVAch)&&(bit_==AV_bch))||((nom==AVAn)&&(bit_==AV_bn)))
  { if(fr3[nom][bit_]==1)//если нажали кнопку аварийного перевода
    if(fr3[nom][5]==1){AV_zdem=0;AVARI=0;}//если объект непарафазен- выход
    else
      if(AVARI==1)//Если выполняется аварийный перевод стрелок
      { if(fr3[nom][bit_]==1)// если нажата кнопка аварийного перевода
				{
          sbros_time(AVAch,AV_bch);//сбросить таймер для четной кнопки
					sbros_time(AVAn,AV_bn);//сбросить таймер для нечетной кнопки
					if((AVAch+AV_bch*1000)!=(AVAn+AV_bn*1000))
					{
						if((nom==AVAch)&&(bit_==AV_bch))//если четный
						{
							if(tst_chet(buf_ko_vsp[0])!=0)
							{
								w(268,999,"");
								zvuk_vkl(0,0);
								goto cont;
							}
						}
						if((nom==AVAn)&&(bit_==AV_bn))//если нечетный
						{
							if(tst_chet(buf_ko_vsp[0])!=1)
							{
								w(268,999,"");
								zvuk_vkl(0,0);
								goto cont;
							}
						}
					}
					form_kom_vsp();//сформировать команду вспомогательного перевода
cont:
					AV_zdem=0; AVARI=0;//сбросить признаки ожидания аварийного перевода
					vkl_kno(AViA,8);//экранную кнопку аварийного перевода сбросить
					avap=0;//сбросить индикатор состояния процесса аварийного перевода
				}
				else
				{ AV_zdem=0;AVARI=0;
					vkl_kno(AViA,8);
					for(goj=0;goj<=9;goj++)buf_ko_vsp[goj]=0;
					avap=0;
				}
			}
	}
	//если бит установлени и нет переключения экранов
	if((fr3[nom][bit_]==1)&&(perekluch==0))
	{ objkt_z=zvu_tabl[ZZ][bit_+4];//взять признак записи на диск
		if(objkt_z!=0)//если требуется запись
		{ //если найдено название объекта и не было фиксации
			if((get_str(nom,bit_)==0)&&(tst_fix(nom,bit_)))
			{
				neisprav_na_disk(objkt_z,chudo);//записать в требуемую графу
				if(objkt_z!='$')w(169,999,chudo);//если не включение, а неисправность
			}
		}
	}
	fix(nom,bit_);//установить флаг фиксации состояния
	if((klo==1)||(help!=0))return;//если помощь или просмотр состояния УВК
	if(fr1[nom][2*bit_+3]==9999) return;//если нет координаты X для лампы
	//если это не объект для контроля макета или бит не нулевой
	if(((nom!=KM1)&&(nom!=KM2))||(bit_!=0))
	{ //если бит установлен то цвет для лампы взять из cvt
		if(fr3[nom][bit_]==1)setcolor(cvt[CC][2*bit_+1]);
		//если бит сброшен-аналогично
		else  setcolor(cvt[CC][2*bit_]);
	}
	else
	{ //если установлен бит контроля макета в обоих стойках,
		//то выбрать цвет для установленного бита из cvt
		if((fr3[KM1][bit_]==1)&&(fr3[KM2][bit_]==1))setcolor(cvt[CC][2*bit_+1]);
		else//аналогично для сброшенных битов КМ
			if((fr3[KM1][bit_]==0)&&(fr3[KM2][bit_]==0))setcolor(cvt[CC][2*bit_]);
			else setcolor(13);//если значение КМ в стойках разное-фиолетовый цвет
	}
	//если бит установлен и требуется звук
	if((fr3[nom][bit_]==1)&&(zvu_tabl[ZZ][bit_]!=0))
	{
		//если нет переключения экранов, то на 1 сек включить звук
		if(perekluch==0)zvuk_vkl(1,18);
	}
	setlinestyle(0,0,0);//тонкая линия
	/****************************************************************************/
	if(fr3[nom][5]==1)  setcolor(LIGHTCYAN);//для непарафазности цвет - циан
	rad=(fr1[nom][11]&(0xf000>>(bit_*4)))>>((3-bit_)*4);//взять радиус
	//для лампочки нарисовать круг
	if(fr1[nom][1]==22)for(goj=rad-1;goj>=0;goj--)circle(fr1[nom][3+2*bit_],fr1[nom][4+2*bit_],goj);
	//для кольца - нарисовать кольцо
	if(fr1[nom][1]==23)for(goj=rad-1;goj>=4;goj--)circle(fr1[nom][3+2*bit_],fr1[nom][4+2*bit_],goj);
}
//-----------------------------------------------------------------------
//изображение на экране цветного прямоугольника для объекта nom и бита bit_
void barcolor(int nom,int bit_)
{
  int goj,rad,ZZ,CC,xx,yy,cvt0,cvt1;
  unsigned char objkt_z;

	nom_func("141");

  if((klo==1)||(help!=0)||(nikuda==1))return;
  if(fr1[nom][2*bit_+3]==9999)return;//если для бита не определена коорд. X
  ZZ = (fr1[nom][2] & 0xFF00)>>8;
  CC = fr1[nom][2] & 0xff;
  cvt0 = cvt[CC][2*bit_];
  cvt1 = cvt[CC][2*bit_+1];
  //если бит установлени и нет переключения экранов
  if((fr3[nom][bit_]==1)&&(perekluch==0))
  { objkt_z = zvu_tabl[ZZ][bit_+4];//взять признак записи на диск
    if(objkt_z!=0)//если требуется запись
    { //если найдено название объекта и не было фиксации
      if((get_str(nom,bit_)==0)&&(tst_fix(nom,bit_)))
      {
        neisprav_na_disk(objkt_z,chudo);//записать в требуемую графу
        if(objkt_z!='$')w(169,999,chudo);//если не включение, а неисправность
      }
    }
  }
  fix(nom,bit_);//установить флаг фиксации состояния
  if(fr1[nom][2*bit_+3]==9999) return;//если нет координаты X
  //если бит установлен то цвет взять из cvt
  if(fr3[nom][bit_]==1){setfillstyle(1,cvt1);setcolor(cvt1);}
   //если бит сброшен-аналогично
  else  {setfillstyle(1,cvt0);setcolor(cvt0);}
  //если бит установлен и требуется звук
  if((fr3[nom][bit_]==1)&&(zvu_tabl[ZZ][bit_]!=0))
	{
		//если нет переключения экранов, то на 1 сек включить звук
		if(perekluch==0)zvuk_vkl(1,18);
	}
	/****************************************************************************/
	if(fr3[nom][5]==1)setfillstyle(1,11);//для непарафазности цвет - циан
	rad=(fr1[nom][11]&(0xf000>>(bit_*4)))>>((3-bit_)*4);//взять размер
	xx=fr1[nom][3+2*bit_];
	yy=fr1[nom][4+2*bit_];
	setlinestyle(0,0,0);
	bar(xx,yy-rad,xx+2,yy+rad);
}
//------------------------------------------------------------------
void den_noch(int nom)
{
  int ob_nn,bit_nn,ob_dn,bit_dn,ob_dnk,bit_dnk,ob_au,bit_au,rad,
  cod,x,y,cvet_au,cvet_ru,cvet_dnk,goj;
  char codik[3];
  
	nom_func("34");
     
  if((klo==1)||(help!=0)||(nikuda==1))return;
  setlinestyle(0,0,0);
  ob_dn=fr1[nom][3];bit_nn=fr1[nom][4];
  ob_nn=fr1[nom][5];bit_dn=fr1[nom][6];
  ob_dnk=fr1[nom][7];bit_dnk=fr1[nom][8];
  ob_au=fr1[nom][9];bit_au=fr1[nom][10];
  if(fr3[nom][5]==1)setcolor(LIGHTCYAN);
  cod=fr3[ob_au][bit_au]*8+fr3[ob_dn][bit_dn]*4+fr3[ob_nn][bit_nn]*2+fr3[ob_dnk][bit_dnk];
  COD_DN=cod;
  if(cod!=0)
  goj=0;
  setcolor(8);
  switch(cod)
  {
    case 0: cvet_au=8;cvet_ru=8;cvet_dnk=10;break;
    case 1: cvet_au=8;cvet_ru=8;cvet_dnk=14;break;
    case 2: cvet_au=8;cvet_ru=14;cvet_dnk=10;break;
    case 3: cvet_au=8;cvet_ru=14;cvet_dnk=14;break;
    case 4: cvet_au=8;cvet_ru=10;cvet_dnk=10;break;
    case 5: cvet_au=8;cvet_ru=10;cvet_dnk=14;break;
    case 6: cvet_au=8;cvet_ru=5;cvet_dnk=10;break;
    case 7: cvet_au=8;cvet_ru=5;cvet_dnk=14;break;
    case 8: cvet_au=10;cvet_ru=8;cvet_dnk=10;break;
    case 9: cvet_au=10;cvet_ru=8;cvet_dnk=14;break;
    case 10: cvet_au=10;cvet_ru=5;cvet_dnk=10;break;
    case 11: cvet_au=10;cvet_ru=5;cvet_dnk=14;break;
		case 12: cvet_au=10;cvet_ru=5;cvet_dnk=10;break;
    case 13: cvet_au=10;cvet_ru=5;cvet_dnk=14;break;
    case 14: cvet_au=10;cvet_ru=5;cvet_dnk=10;break;
    case 15: cvet_au=10;cvet_ru=5;cvet_dnk=14;break;
  }
  if(fr3[ob_au][5]==1)cvet_au=11;
  if(fr3[ob_dn][5]==1)cvet_ru=11;
  if(fr3[ob_nn][5]==1)cvet_ru=11;
  if(fr3[ob_dnk][5]==1)cvet_dnk=11;
  x=markery[fr1[ob_au][12]][4];
  y=markery[fr1[ob_au][12]][5];
  setfillstyle(1,cvet_au);setcolor(cvet_au);
  bar(x-4,y-4,x+4,y+4);//нарисовать кнопку АУ
  x=markery[fr1[ob_dn][12]][4];y=markery[fr1[ob_dn][12]][5];
  setfillstyle(1,cvet_ru);setcolor(cvet_ru);
  bar(x-4,y-4,x+4,y+4);//нарисовать кнопку dn/nn
  if(ob_dnk!=9999)lampa(ob_dnk,bit_dnk);
}
//-------------------------------------------------------------------------
//функция для отображения,записи на диск и вывода сообщений на экран для
//сложного объекта,состоящего из нескольких(до 4-х)ламп,каждая из которых
//сопряжена с
//состояние которых выводится на
//одну лампу, цвет которой определяются состоянием объекта в целом, то есть,
//при изменении состояния любой части объекта меняется цвет лампы
//nom - номер объекта
//bit_ - номер бита
void lampa_3c(int nom,int bit_,int zps)
{
	int goi=0,
	ij,
	ob_cvt,//строка таблицы cvt
	ob_neispr,//строка таблицы zvu_tab
	ob_par[4],//парныe объект
  b_par[4],//биты парных объектов
  rd[4], //радиусы лампы
  cod[4], //коды состояния ламп
  x[4],//координаты X
  y[4],//координаты Y
  color[4];//цвета ламп

	nom_func("143");

  //если помощь просмотр отказов или потеря обмена - выход
  if((klo==1)||(help!=0)||(nikuda==1))return;
  ob_cvt=fr1[nom][2]&0xff;//взять объект для цвета ламп
  ob_neispr=(fr1[nom][2]&0xff00)>>8;//взять объект для записи ненорм
  ob_par[0]=(fr1[nom][11]&0xff00)>>8;
  ob_par[1]=fr1[nom][11]&0xff;
  ob_par[2]=(fr1[nom][12]&0xff00)>>8;
  ob_par[3]=fr1[nom][12]&0xff;
  //определить текущиe кодs состояния
  for(goi=0;goi<4;goi++)//пройти по битам
  {
    b_par[goi]=(fr1[nom][goi*2+3]&0xf000)>>12;
    x[goi]=fr1[nom][goi*2+3]&0xfff;
    rd[goi]=(fr1[nom][goi*2+4]&0xf000)>>12;
    y[goi]=fr1[nom][goi*2+4]&0xfff;
    cod[goi]=fr3[nom][goi]*2+fr3[ob_par[goi]][b_par[goi]];
    switch(cod[goi])
		{ //все выключено
      case 0: color[goi]=(cvt[ob_cvt][goi*2]&0xf0)>>4;break;
      //включен сигнал - нет ПНО
			case 1: color[goi]=cvt[ob_cvt][goi*2]&0xf;break;
      //включено ПНО - нет сигнала
			case 2: color[goi]=(cvt[ob_cvt][goi*2+1]&0xf0)>>4;break;
      //все включено
			case 3: color[goi]=cvt[ob_cvt][goi*2+1]&0xf;break;
			default: break;
		}
	}
	setcolor(color[bit_]);
	setlinestyle(0,0,0);
	for(goi=0;goi<rd[bit_];goi++)circle(x[bit_],y[bit_],goi);
	circle(x[bit_],y[bit_],goi);
	if(color[bit_]==7)
	{setcolor(12);circle(x[bit_],y[bit_],goi);}

	//если не было ранее фиксации и бит установлен
	//если требуется запись и код в допуске
	if((zvu_tabl[ob_neispr][cod[bit_]+4]!=0) && (cod[bit_]<4)&&
	(tst_fix(nom,bit_)|| tst_fix(ob_par[bit_],b_par[bit_])))
	{
		if(zps==0)//если вход не из таймера
		{
			 if(pooo[nom]==0l)TIMER_SOB(nom,21,bit_);
		}
		else//если вход из таймера
		{
			//если найдено имя для бита объекта
			if(get_str(nom,bit_)==0)
			//выполнить запись в требуемую графу
			neisprav_na_disk(zvu_tabl[ob_neispr][cod[bit_]+4],chudo);
			//если требуется звук и вызов функции по новизне данных
			if(zvu_tabl[ob_neispr][cod[bit_]]!=0)
			{
				w(169,999,chudo);//вывести сообщение на экран
				zvuk_vkl(3,0);//включить звук
			}
			fix(nom,bit_);
			fix(ob_par[bit_],b_par[bit_]);
		}
	}
	else
	{
		if((zvu_tabl[ob_neispr][cod[bit_]+4]==0)&&(pooo[nom]!=0))
		sbros_time(nom,bit_);
		fix(nom,bit_);
    fix(ob_par[bit_],b_par[bit_]);
	}
	setlinestyle(0,0,0);//тонкая линия
	if(fr3[nom][5]==1)
	{
		setcolor(LIGHTCYAN);//для непарафазности - цвет циан
		for(goi=0;goi<3;goi++)circle(x[bit_],y[bit_],goi);
	}
}
//---------------------------------------------------------------
//объект типа 2,210 две многоцветные лампы из одного сообщения
void lampa_3(int nom,int bit_,int pisat)
{
	int goj=0,cvet=7,ob_cvt,ob_neispr,ob_2v0,ob_2v1,cod,rad,x,y,b_20,b_21;

	nom_func("142");

	if((klo==1)||(help!=0)||(nikuda==1))return;
	if((fr1[nom][12]&(0xf000>>(bit_*4)))==0)return;
  if((prorisovka==0)&&(ZAGRUZKA==0))prorisovka=0;
  if(fr3[nom][5]==1)cvet=11;
  if(bit_!=5)//если любой бит, кроме бита непарафазности
  {
    ob_2v0=fr1[nom][4+bit_*4]&0xfff;      //объект для 2**0
    b_20=(fr1[nom][4+bit_*4]&0xf000)>>12; //бит для 2**0
    ob_2v1=fr1[nom][5+bit_*4]&0xfff;      //объект для 2**1
    b_21=(fr1[nom][5+bit_*4]&0xf000)>>12; //бит для 2**1
    ob_cvt=(fr1[nom][10+bit_]&0xff00)>>8; //объект таблицы цветов сvt
    ob_neispr=fr1[nom][10+bit_]&0xff;     //объект таблицы неисправностей для диска zvu_tab
    cod=fr3[ob_2v0][b_20]+fr3[ob_2v1][b_21]*2;//код состояния
  }
  else return;
  if(cvet!=11)//если нет непарафазности объекта
	{
		switch(cod)
		{
			case 0: cvet=cvt[ob_cvt][0];break;
			case 1: cvet=cvt[ob_cvt][1];break;
			case 2: cvet=cvt[ob_cvt][2];break;
			case 3: cvet=cvt[ob_cvt][3];break;
		}
	}
	//если требуется запись и код в допуске

	{
		if((zvu_tabl[ob_neispr][cod]!=0)&&(cod<4))
		{ //если найдено имя для бита
			if(get_str(nom,bit_)==0)
			neisprav_na_disk(zvu_tabl[ob_neispr][cod+4],chudo);
		 //если требуется звук и вызов функции по новизне состояния
			if((zvu_tabl[ob_neispr][cod]!=0)&&(prorisovka==0))
			{
				w(169,999,chudo);
				zvuk_vkl(3,0);
			}
		}
	}
rs:
	rad=(fr1[nom][12]&(0xf000>>(4*bit_)))>>(12-bit_*4);
	setlinestyle(0,0,0);
	setcolor(cvet);
	x=fr1[nom][2+bit_*4];y=fr1[nom][3+bit_*4];
	for(goj=rad;goj>=0;goj--)circle(x,y,goj);
	if(cvet==7)//если цвет не определен, то нарисовать окружность
	{
		cvet=8;setcolor(cvet);
		circle(x,y,rad);
	}
}
/************************************************************/
void tel_vkl_vikl(int iwr)
{
//отображает на экране символ установленного варианта управления
	int ir,cod,colorit,obj_2;
	char cod_asc[3];

	nom_func("334");

  for(ir=0;ir<=2;ir++)cod_asc[ir]=0;
  obj_2=fr1[iwr][5];
  if((fr3[iwr][0]!=fr3[obj_2][0])||
  (fr3[iwr][1]!=fr3[obj_2][1])||
  (fr3[iwr][2]!=fr3[obj_2][2])||
  (fr3[iwr][3]!=fr3[obj_2][3]))
  {
#ifdef IN_VNIIAS
  cod=fr3[iwr][0]*8+ // ВСУ
  fr3[iwr][1]*4+     // ДУ
  fr3[iwr][2]*2+     // РУ
  fr3[iwr][3];      // ОРУ
  if(klo==0)
  {
    itoa(cod,cod_asc,10);
    setcolor(7);
    outtextxy(40,31,"████");
    setcolor(8);
    outtextxy(40,31,cod_asc);
  }
#endif
    colorit=8;
    TELEUP=0;
    DU=0;
    SEZON=0;
		goto prodol;
  }
  cod=(fr3[iwr][0]&fr3[obj_2][0])*8+ // ВСУ 
  (fr3[iwr][1]&fr3[obj_2][1])*4+     // ДУ
  (fr3[iwr][2]&fr3[obj_2][2])*2+     // РУ
  (fr3[iwr][3]&fr3[obj_2][3]);      // ОРУ 
  switch(cod)
  {
#ifdef DISP_UPR
    case 1: colorit=14;strcpy(cod_asc,"РУ");
            if(TELEUP==0)
            {
              for(ir=0;ir<=skoko_stoek;ir++)t_com[ir]=biostime(0,0l);
              pooo[KVV1]=biostime(0,0l);
            }
            TELEUP=1;DU=0;SEZON=0;break; //резервное с АРМа
#else
    case 1: colorit=10;strcpy(cod_asc,"ОУ");
            if(TELEUP==0)
            {
              for(ir=0;ir<=skoko_stoek;ir++)
              t_com[ir]=biostime(0,0l);
              pooo[KVV1]=biostime(0,0l);
            }
            TELEUP=1;DU=0;SEZON=0;break; //резервное с АРМа
#endif
    case 2: colorit=12;strcpy(cod_asc,"АУ");TELEUP=0;DU=0;SEZON=0;break; //с пульта
    case 5: colorit=15;strcpy(cod_asc,"ДУ");
            if(TELEUP==0)
            {
              for(ir=0;ir<=skoko_stoek;ir++)
              t_com[ir]=biostime(0,0l);
              pooo[KVV1]=biostime(0,0l);
						}
            TELEUP=1;DU=1;SEZON=0;break; //диспетчерское
    case 9: colorit=10;strcpy(cod_asc,"СУ");
            if(TELEUP==0)
            for(ir=0;ir<=skoko_stoek;ir++)
            t_com[ir]=biostime(0,0l);
            TELEUP=1;DU=0;SEZON=1;break; //сезонное
   default: colorit=8;TELEUP=0;DU=0;SEZON=0;break; //никакого
  }
prodol:
#ifndef TELEUPR
  TELEUP=1;
#endif
  if(klo==0)
  {
    if(fr3[iwr][5]==1)colorit=11;
    if(help!=0) return;
    if(nikuda==1)return;//если просмотр неисправностей
    setcolor(8);
		setlinestyle(0,0,3);
		rectangle(12,30,30,40);
    line(21,40,21,45);
		line(15,45,27,45);
    setcolor(colorit);
    setfillstyle(1,colorit);
		bar(13,31,29,39);
    setcolor(8);
		outtextxy(14,32,cod_asc);
    if(prorisovka==0)
    {
      if((TELEUP==1)&&(SEZON==0)&&(DU==0))
				w(231,999,"");
      if(colorit==12)
				w(192,999,"");
      if(colorit==15)
				w(191,999,"");
      if((TELEUP==1)&&(SEZON==1)&&(DU==0))
				w(190,999,"");
      if(colorit==8||colorit==11)
				w(58,999,"");
			if((DU==1)||(TELEUP==0))//если установили диспетчерское управление
      {
      	if(na==1)//если установлено нечетное автодействие
        {
        	snyato_nechet();
        }
        if(cha==1)//если установлено четное автодействие
        {
          snyato_chet();
				}
			}
    }
  }
	//seg005:2DAF loc_230AF: 
  if(klo==1)
   tele(iwr);
}
/*************************************************/
void tele(int iwr)
{
	int SME=0;

	nom_func("335");

	if(nikuda==1||help!=0) return;
	if(fr1[iwr][13]==2) SME=0;
	else SME=140;
  TELEUP=0;
  setcolor(8);
  setfillstyle(SOLID_FILL,7);
  bar(360,25+SME,560,43+SME);
  setfillstyle(CLOSE_DOT_FILL,YELLOW);
  bar(360,25+SME,560,43+SME);
  if(fr1[iwr][5]==1)return;
  moveto(360,25+SME);
  outtext("РУ  - ");
  setcolor(RED);
  if(fr3[iwr][2]==1) outtext("под током");
  else outtext("без тока");
  setcolor(8);
  moveto(360,35+SME);
  outtext("ОРУ - ");
  setcolor(RED);
  if(fr3[iwr][3]==1) outtext("под током");
  else outtext("без тока");
  if((fr3[iwr][1]==1)&&(fr3[iwr][2]==0))
  {
    setfillstyle(CLOSE_DOT_FILL,YELLOW);
    bar(360,45+SME,580,53+SME);
    setcolor(8);
    moveto(360,45+SME);
		outtext("включено дисп.управление");
		TELEUP=0;
	 }
	 else
	 {
		setfillstyle(CLOSE_DOT_FILL,YELLOW);
		bar(360,45+SME,580,53+SME);
		if((fr3[iwr][2]==0)&&(fr3[iwr][3]==1))
		{
			setcolor(8);
			moveto(360,45+SME);
			outtext("включено управление с ПЭВМ");
			TELEUP=1;
		}
		else
		{
			setcolor(8);
			moveto(360,45+SME);
			outtext("управление с ПЭВМ отключено");
			TELEUP=0;
		}
	}
}
/*******************************************************/
void komplekt(int ir,int bit_)
{
  int chislo=0;
  
	nom_func("129");
        
  if(bit_==5) goto aa; //если бит непарафазности
  if(bit_>2)
    if((fr3[ir][3]==1)||(fr3[ir][4]==1))//если перезапуск или объединение 
    {
      chislo=chego_posl(ir);
      if(chislo!=0) slom_interf(chislo);
      if(klo==1)kartina();
    }
  if(bit_<=2)
  {
aa:
    first_second(ir);
    if((klo==0)&&(nikuda==0)&&(help==0))knopka(ir);
    if(klo==1)kartina();
  }
  return;
}
//------------------------------------------------------------
void ispr_pvm(int nom,int ispr)
{
	char AAq[2]="";
	int colo1=0,x1,y1;

	nom_func("112");

	if((help!=0)||(nikuda==1))return;
	kvadrat();//изображение статуса ПЭВМ (цветом "подставки")

  if(nom==0)// "своя" ПЭВМ
  { //отображение при просмотре состояния интерфейсов УВК
		if(klo==1){PVM(nom,ispr);kanal(0);return;}
    if(STATUS==1) colo1=LIGHTGREEN;//если основная - цвет зеленый
    else  if(STATUS==0) colo1=YELLOW;//если резервна - цвет желтый
          else colo1=8; //если ШН или другое - цвет серый
  }
  else//"соседняя" ПЭВМ
  {
		if(klo==1){PVM(nom,ispr); kanal(1); return; }
    if(ispr==0)//если исправна
    { if(STATUS==1) colo1=YELLOW;//если сосед в резерве
      else
        if(STATUS==0) colo1=10;//если сосед основной
         else colo1=8;//если соседа нет
    }
    else colo1=RED;
  }
  if(nom==0)//своя ПЭВМ
  { x1=Xleft; y1=Yleft; setcolor(10); itoa(NOMER_ARMA,AAq,10);
    moveto(x1-12,y1-2); outtext(AAq);
  }
  else
	{ x1=Xright; y1=Yright; setcolor(8); moveto(x1+8,y1-2);
		if(NOMER_ARMA==1) outtext("2");
		else outtext("1");
	}
	setfillstyle(SOLID_FILL,colo1);
	bar(x1-4,y1-4,x1+4,y1+4);
	setcolor(8);
	setlinestyle(0,0,0);
	rectangle(x1-4,y1-4,x1+4,y1+4);
	line(x1,y1+4,x1,y1+6);
	line(x1-2,y1+6,x1+2,y1+6);
}
/**************************************************************/
void kanal_DC()
{
  int x1,y1;
  char AAq[2];
  
	nom_func("115");
          
  x1=Xleft;y1=Yleft;
  if(STATUS==1)setcolor(10);
  else setcolor(7);
  moveto(x1-30,y1-2);
  AAq[0]=17;AAq[1]=0;outtext(AAq);
  moveto(x1-20,y1-2);AAq[0]=16;AAq[1]=0; outtext(AAq);
  x1=Xright; y1=Yright;
  if(STATUS==0)setcolor(10);
  else setcolor(7);
  moveto(x1+15,y1-2);AAq[0]=17;AAq[1]=0; outtext(AAq);
	moveto(x1+25,y1-2);AAq[0]=16;AAq[1]=0; outtext(AAq);
}
//------------------------
void knopka(int nom) /* цвет кнопки переключения комплектов */
{
	int color1=0,color2=0,x1,y1,KSSk=0,kod;

	nom_func("122");


	if((klo==1)||(help!=0)||(nikuda==1))return;
	KSSk=nom;
	kod=fr3[KSSk][0]+fr3[KSSk][1]*2+fr3[KSSk][2]*4;
	switch(kod)
  {
    case 0: color1=10;color2=14;break;
    case 1: color1=14;color2=10;break;
    case 2: color1=12;color2=14;break;
    case 3: color1=4;color2=10;break;
    case 4: color1=10;color2=4;break;
    case 5: color1=14;color2=12;break;
    case 6: color1=12;color2=4;break;
    case 7: color1=4;color2=12;break;
  }
x:
  if(fr3[KSSk][5]==1)  color1=color2=LIGHTCYAN;
  x1=markery[fr1[KSSk][12]][4];
  y1=markery[fr1[KSSk][12]][5];
  setfillstyle(SOLID_FILL,color1);
  bar(x1-8,y1-3,x1,y1+3);
  setfillstyle(SOLID_FILL,color2);
  bar(x1+1,y1-3,x1+9,y1+3);
  setcolor(8);

}
/************************************************/
void dispdatch(int nom,int bit_)
//работа с датчиками разделки
{
	ELE=nom;

	nom_func("38");

  if(bit_==2)
  { if(fr3[nom][bit_]==1)
		{slom_interf(4059+fr1[nom][13]);return;}
	}
	if(bit_==3)
	{ if(fr3[nom][bit_]==1)
		{slom_interf(4069+fr1[nom][13]);return;}
  }
}
//-------------------------------------------------------
//процедура прорисовки сигнала 
void sigo(int sig,int tip,int obkt,int bt)
{
  int x1,y1,i,cod_cvt,dug1=180,dug2=330,dug3=30,dug4=180;
  int mid=4,half=6,rad=3,lon=10,sme=3,gad=3,og,bit_og;
  int zapret_ris=0,eps=4,eps1=8;
  int cvt_vs,cvt_sig,cvt_og,PNO,B_PNO;

	nom_func("305");
          
  if((klo==1)||(help!=0)||(nikuda==1))zapret_ris=1;
  setlinestyle(0,0,0);
  if(fr1[sig][2]!=0){half=half+1;eps=eps+1;eps1=eps1+1;}
  x1=fr2[sig][0]; y1=fr2[sig][1];
  og=fr1[sig][7];if(og!=9999)bit_og=fr1[sig][8];
  if(fr2[sig][15]!=0)mid=1;
  switch(fr2[sig][2])
  {
    case 1: mid=-mid;rad=-rad;half=-half;
            dug1=0;dug2=150;dug3=210;dug4=360;
            eps=-eps;eps1=-eps1;
            break;
		case 2: half=-half;
            dug1=30;dug2=180;dug3=180;dug4=330;
            eps=-eps;eps1=-eps1;
            break;
    case 3: mid=-mid;rad=-rad;
            dug1=210;dug2=360;dug3=0;dug4=150;
            break;
    default: break;
  }
  if((nikuda==1)||(klo==1)||(help!=0))return;
  switch(tip)
  {
    //если рисуется сигнал
    case 0: ;
    case 5: if(parafaz(sig)<0)
            {cvt_sig=11;cvt_vs=11;cvt_og=7;goto ris1;}
            cod_cvt=fr3[sig][1]*2+fr3[sig][0];
            switch(cod_cvt)
            { //если сигнал закрыт
              case 0: if(fr1[sig][3]==7)cvt_sig=4;
                      else cvt_sig=8;
                      if((fr1[sig][10]>kol_OSN)&&(fr1[sig][10]!=9999))
    									{
      									PNO=fr1[sig][10]&0xfff;
      									B_PNO=(fr1[sig][10]&0xf000)>>12;
      									lampa_3c(PNO,B_PNO,0);// для ПНО/ПЧО
    									}
                      if(tst_fix(sig,0)||tst_fix(sig,1))pooo[sig]=0;
                      fix(sig,0);
											if(fr1[sig][10]==9999)fix(sig,1);//если нет ПНО
                      //если огневых не
                      if(og==9999){cvt_og=cvt_sig; goto ris;}
                      if(parafaz(og)<0){cvt_og=11;break;}
											if(fr3[og][bit_og]==1)//если огневое не в норме
                      { if(tst_fix(og,bit_og))
                        {
                          if(tip==5)//если таймер
                          { fix(og,bit_og);
                            if(get_str(og,bit_og)==0)
                            { zvuk_vkl(3,0);
                              neisprav_na_disk('@',chudo);
                              w(169,999,chudo);
                              cvt_sig=7;cvt_og=12;goto ris;
                            }
                            pooo[sig]=0l;
                          }
                          if(pooo[og]==0l)TIMER_SOB(og,18,bit_og);
                          cvt_og=cvt_sig;
                        }
                        else {cvt_sig=7;cvt_og=12;goto ris;}
                      }
                      else//если огневое в норме
                      {
                        if(tst_fix(og,bit_og))
                        if(pooo[og]!=0l)sbros_time(og,bit_og);
                        cvt_og=cvt_sig;
                        fix(og,bit_og);
                      }
                      break;
              //если маневровый сигнал открыт
              case 1: cvt_sig=15;cvt_og=15;
                      if(tst_fix(sig,0)||tst_fix(sig,1))pooo[sig]=0;
                      if(pooo[og]!=0l)sbros_time(og,bit_og);
                      fix(sig,0);
											if(fr1[sig][10]==9999)fix(sig,1);//если нет ПНО
                      break;
							 //если поездной сигнал открыт
              case 2: cvt_sig=10;cvt_og=10;
                      if(pooo[og]!=0l)sbros_time(og,bit_og);
                      if((fr1[sig][10]>kol_OSN)&&(fr1[sig][10]!=9999))
    									{
      									PNO=fr1[sig][10]&0xfff;
      									B_PNO=(fr1[sig][10]&0xf000)>>12;
      									lampa_3c(PNO,B_PNO,0);// для ПНО/ПЧО
    									}
                      break;
              case 3: cvt_sig=13;cvt_og=13;
                      if(tst_fix(og,bit_og))
                      {
                        w(88,sig,"");
                        zvuk_vkl(1,18);
                        fix(sig,0);fix(sig,1);
                        if(pooo[og]!=0l)sbros_time(og,bit_og);

                     }
                     break;
              default: return;
            }
ris:        cod_cvt=fr3[sig][3]*2+fr3[sig][2];
            switch(cod_cvt)
            {
              case 0: cvt_vs=7;break;
              case 1: cvt_vs=15;break;
              case 2: cvt_vs=14;break;
              case 3: cvt_vs=13;
                      if(tst_fix(sig,2)||tst_fix(sig,3))
                      {
                        w(88,sig,"");
                        zvuk_vkl(1,18);
												fix(sig,2);fix(sig,3);
                        if(pooo[og]!=0l)sbros_time(og,bit_og);

                      }
                      break;
            default: return;
           }
           if(tst_fix(sig,2)||tst_fix(sig,3))pooo[sig]=0;
ris1:      fix(obkt,5);
           if(zapret_ris==0)
           {  //setfillstyle(1,cvt_vs);
              //bar(fr2[sig][0]-1,fr2[sig][1],fr2[sig][0]+1,fr2[sig][1]+eps);
//              bar(fr2[sig][0],fr2[sig][1],fr2[sig][0]+mid/2,fr2[sig][1]+eps);
              setlinestyle(0,0,0);setcolor(cvt_sig);
              for(i=0;i<gad;i++)circle(x1+rad+mid,y1+half,i);
              setcolor(cvt_og);circle(x1+rad+mid,y1+half,gad);
           }
           break;
    //если рисуется зСо
    case 1: //если непарафазность
            if(parafaz(obkt)<0)setcolor(11);
            else
            { if(fr3[obkt][bt]==0) //если норма
              {fix(obkt,bt);setcolor(7);}
              else //если ненорма
              { if(tst_fix(obkt,bt))//если не фиксирована
                {
                  if(get_str(obkt,bt)==0)
                  { neisprav_na_disk('@',chudo);
                    zvuk_vkl(1,18);
                    w(169,999,chudo);
                  }
                   fix(obkt,bt);
								}
                setcolor(2);
              }
            }
            if(zapret_ris==0)
            { arc(x1+rad+mid,y1+half,dug1,dug2,abs(gad)+2);//ЗСО
              arc(x1+rad+mid,y1+half,dug3,dug4,abs(gad)+2);//ЗСО
            }
            break;
    //если рисуется ВНП
    case 2: //если непарафазность
            if(parafaz(obkt)<0)setcolor(11);
            else
            { if(fr3[obkt][bt]==0){fix(obkt,bt);setcolor(7);} //если норма
              else //если ненорма
              { if(tst_fix(obkt,bt))
                {
                  if(get_str(obkt,bt)==0)
                  { neisprav_na_disk('@',chudo);
                    w(169,999,chudo);
                    zvuk_vkl(1,18);
                  }
                }
                fix(obkt,bt);
                setcolor(12);
              }
            }
            if(zapret_ris==0)
            { arc(x1+rad+mid,y1+half,dug1,dug2,abs(gad)+3);//ВНП
              arc(x1+rad+mid,y1+half,dug1,dug2,abs(gad)+4);//ВНП
            }
            break;
    //если рисуется ЖСо
		case 3: if(parafaz(obkt)<0)setcolor(11);//если непарафазность
            else
            {//если норма
              if(fr3[obkt][bt]==0){fix(obkt,bt);setcolor(7);}
              else //если ненорма
              { if(tst_fix(obkt,bt))
                {
                  if(get_str(obkt,bt)==0)
                  {
                    neisprav_na_disk('@',chudo);
                    w(169,999,chudo);
                    zvuk_vkl(1,18);
                  }
                }
                fix(obkt,bt);
                setcolor(14);
              }
            }
            if(zapret_ris==0)
            { arc(x1+rad+mid,y1+half,dug1,dug2,abs(gad)+1);//ЖСО
              arc(x1+rad+mid,y1+half,dug3,dug4,abs(gad)+1);//ЖСО
            }
            break;
    //если рисуется шкаф
    case 4: if(parafaz(obkt)<0)setfillstyle(1,11);//если непарафазность
            else
            { if(fr3[obkt][bt]==0) //если норма
              { fix(obkt,bt);
                setfillstyle(1,7);
              }
              else //если ненорма
              { if(tst_fix(obkt,bt))
                {
									if(get_str(obkt,bt)==0)
                  {
                    neisprav_na_disk('@',chudo);
                    w(175,999,chudo);
                    zvuk_vkl(1,18);
                  }
                }
                fix(obkt,bt);
                setfillstyle(1,12);
              }
            }
            if(zapret_ris==0)bar(x1-2,y1+eps,x1+2,y1+eps1);
            break;
    default:break;
  }
  if(zapret_ris==0)
  { setcolor(8);
    setlinestyle(0,0,0);line(x1,y1+eps,x1,y1+eps1);
    if(mid!=0)line(x1,y1+half,x1+mid,y1+half);
  }
  return;
}
//------------------------------------------------
//процедура обработки данных по огневому реле
void ognev(int oik,int bt,int tip)
{
  int sign,i;

	nom_func("198");

  if(fr1[oik][4+bt]==9999)return;//если бит пустой, то выйти
  else sign=fr1[oik][4+bt];       //иначе номер объекта сигнала
  if(fr3[oik][5]==0)sigo(sign,tip,oik,bt);//если огневой объект парафазен
	else //если непарафазность
    for(i=0;i<fr1[oik][12];i++)//пройти по всем сигналам данного объекта
    {
      if(fr1[oik][4+i]==9999)break;
      else sign=fr1[oik][4+i];
      sigo(sign,tip,oik,i);
    }
  return;
}
//-----------------------------------------------------
//процедура обработки данных по датчикам,связанным с сигналом
//огневое реле, зСо, ЖСо, ВНП, авария шкафа
void ris_batarei(int nomer,int bit_)
{
  int x,y,j,sign,tip;
  
	nom_func("282");
          
    //если огневое реле
  tip=0;
  if(fr1[nomer][3]==1){ognev(nomer,bit_,tip);return;}
  if(fr1[nomer][4+bit_]==9999) return;//если бит пустой, то выйти
  else sign=fr1[nomer][4+bit_];       //иначе номер объекта сигнала
  switch(fr1[nomer][3])
  {
    case 5: tip=1;break;//если зСо
    case 6: tip=3;break;//если ЖСо
    case 7: tip=2;break;//если ВНП
    case 11:tip=4;break;//если авария шкафа
    default: return;
  }
  sigo(sign,tip,nomer,bit_);
  return;
}
//------------------------------------------------------------
void krasit_razd(int nomer,int bt)
{
  int color,x,y,xx,yy,nom,cl1,cl2;
  char bb[5]="";
  
	nom_func("137");
   
  if(((vtora!=0)||(zalet!=0))&&(prorisovka==1))return;
  color=0;
	if((fr1[nomer][1]==301)||(fr1[nomer][1]==302)){sekci(nomer,bt);return;}
  if((bt==5)&&(fr3[nomer][5]==1))slom_interf(nomer);
  if((nikuda==1)||(klo==1)||(help!=0))return;
  if((fr1[nomer][1]>=200)&&(fr1[nomer][1]<=300))
  { if((fr3[nomer][0]==0)&&(fr3[nomer][2]==0))//если предв. и исп. команды нет
    { color=8;//цвет серый 
      if(was[markery[fr1[nomer][5]][7]-10]!=0)//если объект числится в разделке
      {
        was[markery[fr1[nomer][5]][7]-10]=0;//снять флаг выполнения разделки
      //если маркер на этом объекте,вернуть его домой
        if(modi==fr1[nomer][5])
        {
          home(modi);t(0);
          fr3[nomer][9]=0;//снять флаг выдачи команды в стойку
          vtora=0;//снять признак выдачи предварительной команды
          t(0); //стереть окно интерактива 
          zalet=0;vtora=0;//сбросить флаги 
          regs.h.ah=5;
          regs.h.ch=0x39;
          regs.h.cl=0x20;
          pooo[nomer]=0l;
          int86(0x16,&regs,&regs);
          zvuk_vkl(1,9);
          w(169,nomer,"06");
				}
      }
    }
    else
    //если исполнена предварительная команда и окончательная команда
    if((fr3[nomer][0]==1)&&(fr3[nomer][2]==1))
    //установить красный цвет сбросить флаг выдачи команды в стойку
    {
      color=RED; fr3[nomer][9]=0; fr3[nomer][8]=0;
      t(0); //стереть окно интерактива
      zalet=0;vtora=0;//сбросить флаги
      regs.h.ah=5;
      regs.h.ch=0x39;
      regs.h.cl=0x20;
      pooo[nomer]=0l;
      int86(0x16,&regs,&regs);
    }
    else
    {
      if(fr3[nomer][0]==1)//если выполнена только предварительная команда
      { cl1=RED;//цвет красный
        fr3[nomer][9]=0;//сбросить признак выдачи команды
        fr3[nomer][10]=0;
        fr3[nomer][8]=0;
        if((prorisovka==0)&&(STATUS==1)&&(DU==0))
        {
          w(12,999,"");//ПОСЫЛАТЬ ОКОНЧАТЕЛЬНУЮ КОМАНДУ?
          vtora=1;
          zapretvybora=1;
        }
      }
      else
      { cl1=8;//если не выполнена предварительная
				if(fr3[nomer][9]==9)//если была выдана команда
        { if(was[markery[fr1[nomer][5]][7]-10]!=0)//если секция помечена в разделке
          was[markery[fr1[nomer][5]][7]-10]=0;//снять метку о разделке
          //если маркер на этом объекте- вернуть домой
          if(modi==fr1[nomer][5]){home(modi);t(0);}
        }
      }
      if(fr3[nomer][2]==1)//если идет искусственная разделка
      { cl2=RED;color=RED;
        fr3[nomer][9]=0;fr3[nomer][10]=0;fr3[nomer][8]=0;
      }
      else  cl2=8;
    }
  }
  else  return;//если объект не разделка,то выйти
  nom=fr1[nomer][5];//взять номер объекта для маркера
  // получить координаты рисования кнопки
  x=markery[nom][4]-4; y=markery[nom][5]-4;
  xx=markery[nom][4]+4;yy=markery[nom][5]+4;
  //-----------------------------------------
  if(fr3[nomer][5]==1)// если непарафазность
  {setfillstyle(SOLID_FILL,LIGHTCYAN);bar(x,y,xx,yy);return;}
   //--------------------------------------------
  if(color!=0){ setfillstyle(SOLID_FILL,color);bar(x,y,xx,yy);return;}
  else
  { setfillstyle(SOLID_FILL,cl1); bar(x,y,xx,y+4);
    setfillstyle(SOLID_FILL,cl2); bar(x,y+4,xx,yy);
    if(vtora==0)home(-1);
    return;
  }
}
//-------------------------------------
void krasit_knopki(int nomer,int bt)
{
	int nn1,nn2=0,bb2=0,GRIV,color,x,y,xx,yy,nom,cl1,cl2;

	nom_func("136");

  //если получены данные по выдержке
  if(fr1[nomer][1]==302)//если ИВ
  {
		nn1=fr1[nomer][2];//взять объект для кнопки 1 ст
#ifdef KOL_SOO2
    nn2=fr1[nomer][3];//взять объект для кнопки 2 ст
#else
    nn2=nn1;
#endif
  }
  //если получены данные по кнопке
  if(fr1[nomer][1]==301)//получить номера для ГСП и для ГРИВ
  {
    if(prorisovka==0)pooo[nomer]=0l;
    nn1=nomer;//ГСП из этой стойки
    nn2=fr1[nomer][3];  //Кнопка из соседней стойки
    if(nn2==9999)nn2=nn1;
  }
  //взять бит для ИВ
  GRIV=0;//состояние 0
  if(nn1!=9999)//если есть кнопка ГСП
  { if(fr1[nn1][4]!=9999)//если есть ИВ
    {
      bb2=(fr1[nn1][4]&0xf000)>>12;
      nomer=fr1[nn1][4]&0xfff;//ИВ
      GRIV=fr3[nomer][bb2];//получить состояние выдержки
    }
	}
  // если бит непарафазности и есть непарафазность по ИВ
  if((bt==5)&&( fr3[nomer][5]==1))slom_interf(nomer);// ИВ
  //если есть управление и непарафазность по кнопке
  if((nn1!=9999)&&(fr3[nn1][5]==1))
  {
    if(tst_fix(nn1,5))slom_interf(nn1);//Кнопка
    fix(nn1,5);

  }
  if((nn2!=9999)&&(fr3[nn2][5]==1))
  {
    if(tst_fix(nn2,5))slom_interf(nn2);//Кнопка
    fix(nn2,5);
  }
  if((nikuda==1)||(klo==1)||(help!=0))return;
  if((fr1[nomer][1]==301)||(fr1[nomer][1]==302))//если кнопка или выдержка
  { fr3[nomer][8]=0;
    //если нет ГСП и ГРИВ равен 0, то цвет серый
    if((fr3[nn1][2]==0)&&(fr3[nn2][2]==0)&&( GRIV==0))color=8;
    else //если нет ГСП и ГРИВ равен 1, то цвет желтый
      if((fr3[nn1][2]==0)&&(fr3[nn2][2]==0)&&(GRIV==1))color=14;
      else  //если есть ГСП и ГРИВ равен 0, то цвет красный
        if((fr3[nn1][2]==1)&&(fr3[nn2][2]==1)&&(GRIV==0))
				color=RED;
        else
          if(fr3[nn1][2]==fr3[nn2][2])color=14; // иначе цвет - желтый
          else color=13;
    nom=fr1[nn1][5];//номер объекта управления в markery
    //если непарафазность в ГРИ или //непарафазность в ГРИВ или
    // нет связи вообще или //нет связи с данной стойкой
    if((fr3[nn1][5]==1)||(fr3[nn2][5]==1)||(fr3[nomer][5]==1))color=11;
    if(nom!=9999)//если есть управление ГРИ от АРМа
		{ //получить координаты кнопки управления нарисовать кнопку полученным цветом
			x=markery[nom][4]-4; y=markery[nom][5]-4;
			xx=markery[nom][4]+4; yy=markery[nom][5]+4;
			setfillstyle(SOLID_FILL,color);bar(x,y,xx,yy);
		}
		return;
	}
}
/*************************************/
void knopka_vkl_vsego(int nom,int bit_)
{
  int x,y,p,svebf,svebv,nm1,bt1,nm2,bt2,cod;
  
	nom_func("125");
          
  if((klo==1)||(help!=0)||(nikuda==1))return;
  switch(fr1[nom][1])
  {
    case 166: p=fr1[nom][2];
              nm1=fr1[nom][3]&0xfff;bt1=(fr1[nom][3]&0xf000)>>12;
              nm2=fr1[nom][4]&0xfff;bt2=(fr1[nom][4]&0xf000)>>12;
              cod=fr3[nm1][bt1];
              svebf=(fr1[nom][5]&0xff00)>>8;
              svebv=cvt[svebf][cod];
              break;
    default:  if(fr1[nom][2]==0)fr3[nom][bit_]=0;
              p=fr1[nom][10];
              svebf=fr1[nom][5];//цвет для включения
              svebv=fr1[nom][6];//цвет для выключения
              bit_=fr1[nom][11];
              break;
  }
  x=markery[p][4];
  y=markery[p][5];
  if(fr3[nom][5]==1)setfillstyle(1,11);//для непарафазности
  else
    if(fr1[nom][1]==166)setfillstyle(1,svebv);
    else
    {
      //если бит сброшен
      if(fr3[nom][bit_]==0)setfillstyle(1,svebf);
      else setfillstyle(1,svebv);
		}
	bar(x-4,y-4,x+4,y+4);
}
//-----------------------------------------------
void ris_nemar(int nom)
{
  int x,y,p,svebf,svebv,bit_,isp,ob_rm,b_rm,ob_mi,b_mi,ob_ot,b_ot,cd,c_l,ii;
  
	nom_func("285");
          
  if((klo==1)||(help!=0)||(nikuda==1))return;
  p=fr1[nom][10];//объект управления в markery
  svebv=fr1[nom][6];//цвет для включения
  svebf=fr1[nom][5];//цвет для выключения
  bit_=fr1[nom][11];//номер бита
  isp=fr1[nom][12];//объект исполнения
  ob_rm=fr1[isp][3]&0xfff;//объект РМ исполнительный
  b_rm=(fr1[isp][3]&0xf000)>>12;//бит РМ исполнительный
  ob_mi=fr1[isp][4]&0xfff;//объект МИ
  b_mi=(fr1[isp][4]&0xf000)>>12;//бит МИ
  ob_ot=fr1[isp][5]&0xfff;//объект ОТ
  b_ot=(fr1[isp][5]&0xf000)>>12;//бит ОТ
  cd=fr3[ob_ot][b_ot]*4+fr3[ob_mi][b_mi]*2+fr3[ob_rm][b_rm];
  if((fr3[ob_ot][5]==1)||(fr3[ob_mi][5]==1)||(fr3[ob_rm][5]==1))cd=8;
  x=markery[p][4];
  y=markery[p][5];
  if(fr3[nom][5]==1)setfillstyle(SOLID_FILL,LIGHTCYAN);//для непарафазности
  else
    if(fr3[nom][bit_]==0)//если бит сброшен
    setfillstyle(SOLID_FILL,svebf);
    else setfillstyle(SOLID_FILL,svebv);
  bar(x-4,y-4,x+4,y+4);
  switch(cd)
  {
    case 0: c_l=8; break;
    case 1: c_l=15;break;
    case 2: c_l=12;break;
		case 3: c_l=10;break;
    case 4: c_l=13;break;
    case 5: c_l=13;break;
    case 6: c_l=14;break;
    case 7: c_l=13;break;
    case 8: c_l=3;break;
  }
	setlinestyle(0,0,0);
	setcolor(c_l);
	for(ii=3;ii>0;ii--)circle(x,y,ii);
}
//-----------------------------------------------
void nemar(int ob)
{
	int ob_up,bt_up,ob_mark,ob_rm,bt_rm,ob_mi,bt_mi,ob_ot,bt_ot,x,y,ij,cd,
	sig_n,sig_k;
	ob_up=fr1[ob][2]&0xfff; //объект для управления (вкл/откл) немар.передвиж.
	ob_mark=fr1[ob_up][10];
	ob_rm=fr1[ob][3]&0xfff;
	bt_rm=(fr1[ob][3]&0xf000)>>12;
	ob_mi=fr1[ob][4]&0xfff;
	bt_mi=(fr1[ob][4]&0xf000)>>12;
	ob_ot=fr1[ob][5]&0xfff;
	bt_ot=(fr1[ob][5]&0xf000)>>12;
	sig_n=fr1[ob_up][2];
	sig_k=fr1[ob_up][7];

	nom_func("182");

	cd=fr3[ob_ot][bt_ot]*4+fr3[ob_mi][bt_mi]*2+fr3[ob_rm][bt_rm];
	if(cd==0){fr3[sig_n][12]=0;fr3[sig_k][12]=0;}
	if((cd==1)||(cd==3)||(cd==7)){fr3[sig_n][12]=15;fr3[sig_k][12]=15;}
	if((fr3[ob_ot][5]==1)||(fr3[ob_rm][5]==1)||(fr3[ob_mi][5]==1))cd=8;
	for(ij=6;ij<13;ij++)
  {
    if(fr1[ob][ij]==9999)break;
    fr3[fr1[ob][ij]][12]=fr3[fr1[ob][ij]][12]&0xf;
    switch(cd)
    {
      case 1: fr3[fr1[ob][ij]][12]=fr3[fr1[ob][ij]][12]|16;break;
      case 3: fr3[fr1[ob][ij]][12]=fr3[fr1[ob][ij]][12]|32;break;
      case 7: fr3[fr1[ob][ij]][12]=fr3[fr1[ob][ij]][12]|64;break;
    }
    sekci(fr1[ob][ij],0);//изобразить секцию
  }
  ris_nemar(ob_up);
}
//-----------------------------------------------
void knopka_vkl_opove(int nom,int bit_)
{
  int rm, // номер объекта для РМ
  b_rm, //номер бита для РМ
  zm, // номер объекта для ЗМ
  b_zm, // номер бита для РМ
  x,y,p,svebf,i,treug[6];

	nom_func("124");

  if((klo==1)||(help!=0)||(nikuda==1))return;
  rm=fr1[nom][2]&0xfff;
  b_rm=(fr1[nom][2]&0xf000)>>12;
  zm=fr1[nom][7]&0xfff;
  b_zm=(fr1[nom][7]&0xf000)>>12;
  p=fr1[nom][10]; //номер объекта управления в markery
  x=markery[p][4]-4;y=markery[p][5];
  if(fr3[nom][5]==1)svebf=11;
  else
  {   //установить цвета для сочетаний РМ-ЗМ
    switch(fr3[rm][b_rm]*2+fr3[zm][b_zm])
    {
      case 0: svebf=8;break;
      case 1: svebf=13;break;
      case 2: svebf=14;break;
      case 3: svebf=12;break;
    }
  }
  setcolor(svebf); setfillstyle(1,svebf);
  setlinestyle(0,0,0);
  treug[0]=x+2;treug[1]=y;treug[2]=x+8;treug[3]=y-4;treug[4]=x+8;treug[5]=y+4;
  fillpoly(3,treug);
}
//-------------------------------------------------------
void slom_uch(int nomer,char vid)
{
  int o,i;
  char dobav[3];
  
	nom_func("308");
          
  for(o=0;o<20;o++)chudo[o]=0;
  dobav[0]='_';dobav[1]=vid;dobav[2]=0; 
  o=0;
  while(pako[nomer][o]==' ')o++;
  i=0;
  while((pako[nomer][o]!=' ')&&(pako[nomer][o]!=0))chudo[i++]=pako[nomer][o++];
  strcat(chudo,dobav);
  neisprav_na_disk('&',chudo);
}
/**********************************************/
void slom_sign(int nomer)
{
  int o;
  
	nom_func("307");
          
  for(o=0;o<20;o++)chudo[o]=0;
  strcpy(chudo,pako[nomer]);
  if(fr3[nomer][0]==1)strcat(chudo,"_М");
  if(fr3[nomer][1]==1)strcat(chudo,"_П");
  neisprav_na_disk('*',chudo);
}
/***********************************************/
void dr()
{

	nom_func("45");

	if((nikuda==1)||(help>0))goto fin;
	if(klo==1){kartina();goto fin; }
	if (marazm==1){uprav=1;marazm=0;}
	if (tst==2) uprav=1;
	else uprav=0;
	GraphMode=VGAHI;perekluch=1;
	if((otkaz_ts[0]==0)&&(otkaz_ts[1]==0)){clscreen();nachalo();prodol();}
	else
	{
		if(otkaz_ts[0]==0) z1(1);
		if(otkaz_ts[1]==0) z1(2);
	}
fin:
	perekluch=0;pusto=0;
	if(otkaz_ts[0]==0){outportb(BAZ_ADR1+1,3);outportb(BAZ_ADR1,0);}
	if(otkaz_ts[1]==0){outportb(BAZ_ADR11+1,3);outportb(BAZ_ADR11,0);}
}
/***********************************************/
void kvv(int nom,int bit_)
{
	int KVx,Krz,SME=0;

	nom_func("140");

	if(nom==KVV1){KVx=KVV1;Krz=KVV1;SME=625;}
	else
	{
#ifdef KOL_SOO2
		KVx=KVV2;Krz=KVV2;SME=630;
#endif
	}
	if(bit_==0)
	{
		if((klo==0)&&(nikuda==0)&&(help==0))
		{ if(fr3[nom][5]==1)setfillstyle(SOLID_FILL,11);
			else setfillstyle(SOLID_FILL,2);
			if(fr3[nom][bit_]==0)setfillstyle(SOLID_FILL,8);
			bar(SME,450,SME+5,455);
		}
		return;
	}
	if(fr3[nom][1]==1)
	{
		if(tst_fix(nom,1))slom_interf(4070+fr1[nom][13]-1);
		fix(nom,1);
		return;
  }
  if(bit_==2){if(klo==1)kps_osn(KVx);    return;}
  if(bit_==3){if(klo==1)kps_rez(Krz);    return;}
}
/*********************************************************************/
void Pam(int nom)
{

	nom_func("215");

	if(tst_fix(nom,0))
	{
		if(fr3[nom][0]==1){slom_interf(8299+fr1[nom][13]);}
		fix(nom,0);
	}
	if(tst_fix(nom,1))
	{
		if(fr3[nom][1]==1){slom_interf(8399+fr1[nom][13]);}
		fix(nom,1);
	}
}
//------------------------------------------------
void pict_podsvetka()
{ int i,K,falsv,pamjat=0;

	nom_func("221");

	//пройти по всем основным элементам
	for (pamjat=0;pamjat<kol_VO;pamjat++)
	{
		if((fr1[pamjat][0]==3)&&(fr1[pamjat][1]<3)&&(fr1[pamjat][2]<3))
		{K=pamjat;zap_matr(K);cvet_matr();ris_sp_str();}
	}
}
//---------------------------------------------------------
#ifdef VSP
void ris_smen_otv(int nomer,int bit_)
{
	int nom,first,color,xc,yc,x,y,oho,j13;

	if((klo==1)||(help!=0)||(nikuda==1))return;

	if (fr1[nomer][3]==2)
		first=2;
	else
		if(fr1[nomer][3]==1)
			first=1;

	if(bit_==2)
	{
		if (fr3[nomer][2]==1)
			color=RED;
		else
			color=8;
		nom = fr1[nomer][6];
	}
	else
		if(bit_==3)
		{
			if(fr3[nomer][3]==1)
				color=RED;
			else
				color=8;
			nom=fr1[nomer][5];
		}
		else
			return;

	xc = markery[nom][4];
	yc = markery[nom][5];
	oho = 9999;

	for(j13=0;j13<VSP;j13++)
	if(mark[j13][0]==nom)
	{
		oho=j13;
		break;
	}

	if(oho==9999)
		return;
	//	seg005:6426 loc_26726:
	if(fr3[nomer][5]==1)
	{ setfillstyle(SOLID_FILL,LIGHTCYAN);
		bar(xc-4,yc-4,xc+4,yc+4);
		return;
	}

	//seg005:6470 loc_26770:
	setfillstyle(SOLID_FILL,color);
	//seg005:647E
	if(color==RED)
	{
		//seg005:6487 loc_26787:
		if(first==1)
		{ //seg005:64A6
			bar(xc-4,yc-4,xc+4,yc);
			//seg005:64BA - seg005:64DD
			if((mark[oho][1]==1)&&(priem_==1)&&(fr3[nomer][9]!=0))
			{
				//seg005:64F3
				fr3[nomer][9]=0;
				//seg005:6507
				w(12,999,"");
				zapretvybora=1;
			}
			//seg005:651B loc_2681B: -  seg005:654A
			if((mark[oho][1]==-1)&&(priem_==-1)&&(fr3[nomer][9]!=0))
			{
				fr3[nomer][9]=0;
				w(12,999,"");
				zapretvybora=1;
			}
			fr3[nomer][9]=0;
		}
		else
		{
			//seg005:659F loc_2689F:
			bar(xc-4,yc,xc+4,yc+4);
			//seg005:65CB
			fr3[nomer][7]=0;
		}
	}
	else
	{
		//seg005:65D5 loc_268D5:
		if(first==1)
		{
			//seg005:65F4
			bar(xc-4,yc-4,xc+4,yc);
			// seg005:6608 - seg005:6615
			if((mark[oho][1]==1)&&(priem_==1))
			//seg005:662B
			fr3[nomer][9]=0;

		//seg005:663E - seg005:664B
			if((mark[oho][1]==-1)&&(priem_==-1))
				fr3[nomer][9]=0;
		}
		else
			//seg005:666A loc_2696A:
			bar(xc-4,yc,xc+4,yc+4);
	}
}
#endif
//------------------------------------------------
#ifdef OGRAD
k_ograd(int ob_sogl)
{ int ob_zapros,ob_ogr,bit_zapros,bit_sogl,bit_ogr,put;
	int sp_chet,sp_nchet,st_chet,st_nchet,otvod_chet,otvod_nchet;
	unsigned char koda;
	if(DISK!=0)return;
	put=fr1[ob_sogl][4];
	ob_zapros=fr1[ob_sogl][2];bit_zapros=fr1[ob_zapros][3];
	ob_ogr=fr1[ob_sogl][3];bit_ogr=fr1[ob_ogr][5];
	bit_sogl=fr1[ob_sogl][12];
	sp_chet=fr1[ob_sogl][6];st_chet=fr1[ob_sogl][7];otvod_chet=fr1[ob_sogl][8];
	sp_nchet=fr1[ob_sogl][9];st_nchet=fr1[ob_sogl][10];otvod_nchet=fr1[ob_sogl][11];
	if(klaval==13)
	{ if(may_be_ograd(put)==1){home(modi);return;}
		// ВЫДАЕМ СОГЛАСИЕ НА ОГРАЖДЕНИЕ,ПУТЬ ##
		w(156,put,""); home(modi);oppp=0;
		koda='A';
		point=ob_sogl;
		if(fotksig(koda)==1)return;
		buf_ko[9]=check_sum(buf_ko);
		pooo[ob_sogl]=biostime(0,0L);
		flagoutmsg=1;
	}
}
#endif
//----------------------------------------------------------------
//процедура проверки парафазности объекта и сброса таймеров при непарафазности
//возвращает 0 при норме парафазности
//возвращает -1 при ненорме
int parafaz(int ob)
{

	nom_func("216");

	if(fr3[ob][5]==1)//при непарафазности
	{
		if(tst_fix(ob,5))
		{
			slom_interf(ob);
			fix(ob,5);
			if(pooo[ob]!=0l)sbros_time(ob,5);
		}
		return(-1);
	}
	else
	{
		if(tst_fix(ob,5))fix(ob,5);
		return(0);
	}
}
//----------------------------------------------------------------
//процедура отображения, вывода на экран сообщения и записи на диск
//состояния объекта управления типа лампа, зависящая от двух объектов из
//разных сообщений стойки ТУМС
void lampa_compl(int nom,int bit_)
{
	int goj=0,ob_svyaz,ob_sn,bit_sn,jj;

	nom_func("144");

	//если нет координаты X для 1-ой лампы объекта, то выйти
	//если система находитс в просмотре помощи, неисправностей или нет связи
	if((klo==1)||(help!=0)||(nikuda==1))return;
	if((fr1[nom][2*bit_+3]==9999)&&(fr1[nom][2*bit_+4]==9999))return;
	//если бит установлен и нет переключения экранов
	if((fr3[nom][bit_]==1)&&(perekluch==0))
	//если надо фиксировать данное событие
	if(zvu_tabl[fr1[nom][2]][bit_+4]!=0)
	//если найдено имя для бита
	if(get_str(nom,bit_)==0) neisprav_na_disk(zvu_tabl[fr1[nom][2]][bit_+4],chudo);
	ob_svyaz=fr1[nom][11];//определить объект связи
	ob_sn=fr1[ob_svyaz][bit_*2];//определить смежный объект
	bit_sn=fr1[ob_svyaz][bit_*2+1];//определить бит смежного объекта
	if(fr3[nom][bit_]==1)// если основной датчик сработал
	{
		if(fr3[ob_sn][bit_sn]==0)
		setcolor(fr1[ob_svyaz][10]);//взять цвет для 0-вого значения смежного бита
		if(fr3[ob_sn][bit_sn]==1)
		setcolor(fr1[ob_svyaz][11]);//взять цвет для 1-ного значения смежного бита
		setlinestyle(0,0,0);
		//если нужен звук и нет переключения экранов
		if((zvu_tabl[fr1[nom][2]][bit_]!=0)&&(perekluch==0))zvuk_vkl(1,18);
	}
	else // если основной датчик сбросился
	{
		if(fr3[ob_sn][bit_sn]==0)
		setcolor(fr1[ob_svyaz][8]);//взять цвет для 0-го значения смежного бита
		if(fr3[ob_sn][bit_sn]==1)
		setcolor(fr1[ob_svyaz][9]);//взять цвет для 1-го значения смежного бита
		setlinestyle(0,0,0);
		//если надо звук и нет переключения экрана
		if((zvu_tabl[fr1[nom][2]][bit_]!=0)&&(perekluch==0))zvuk_vkl(1,18);
	}
	//если непарафазность или нет связи
	if(fr3[nom][5]==1)setcolor(LIGHTCYAN);
	for(goj=fr1[ob_svyaz][12]-1;goj>=0;goj--)
	circle(fr1[nom][3+2*bit_],fr1[nom][4+2*bit_],goj);
}
#ifdef OGRAD
//------------------------------------------------------
//Процедура проверки возможности установки ограждения пути
int may_be_ograd(int put_ogr)
{ int element,napr,vhod_s_v=0,strelka;
	element=put_ogr;
	napr=1; //начинаем движение в четную сторону
start:
	if(napr==1)element++;
	if(napr==0)element--;
	strelka=0;
	while(fr1[element][0]!=5)
	{ if(napr==1&&vhod_s_v==0)element++;
		if(napr==0&&vhod_s_v==0)element--;
		if(fr1[element][0]==1)//если вышли на стрелку
		{ strelka++;
			if(fr1[element][7]==napr)//если вход на стрелку совпадает с движением
			{ if(fr3[element][0]==1&&fr3[element][1]==0)//если стрелка в плюсе
				{ if(fr1[element][1]==0)// если переход по плюсу c отклонением
					{
					 element=fr1[element][2];
					}
				}
      }
      else//вход на стрелку не совпадает с направлением
      { if(vhod_s_v==1)//если входим с отклонения
        { if(fr3[element][0]==1&&fr3[element][1]==0//если стрелка в плюсе
          &&fr1[element][1]==1)// если переход по плюсу прямой
          { vhod_s_v=0;
            if(strelka==1)break;
          }
          if(fr3[element][0]==0&&fr3[element][1]==1//если стрелка в минусе
          &&fr1[element][1]==0)// если переход по минусу прямой
          { vhod_s_v=0;
            if(strelka==1)break;
          }
        }
        if(vhod_s_v==0)//если входим по прямой
        { if(fr3[element][0]==1&&fr3[element][1]==0//если стрелка в плюсе 
          &&fr1[element][1]==0)// если переход по плюсу отклоненный 
          { vhod_s_v=0;
            if(strelka==1)break;
          }
          if(fr3[element][0]==0&&fr3[element][1]==1//если стрелка в минусе
          &&fr1[element][1]==1)// если переход по минусу отклоненный 
          { vhod_s_v=0;
            if(strelka==1)break;
          }
        }
      }
    }
    if(fr1[element][0]==3)//если вышли на СП за стрелкой
    { if((fr3[element][1]&1)==1)//если СП замкнут
      { w(96,element,"");
        home(modi);
        return(1);
      }
      else break;
    }
    else
    if(fr1[element][0]==6)//если переход 
    { element=fr1[element][1];
      vhod_s_v=1;
    }
    else vhod_s_v=0;
  }
  if(napr==1)
  { napr=0;
    element=put_ogr;
    goto start;
  }
  else return(0);
}
#endif
//-----------------------------------------------------------
//процедура проверки новизны для объекта "ob" по биту "bt"
//для записей ненорм в дисковый архив
//контроль ведется по слову fr3[ob][11]
int tst_fix(int ob,int bt)
{
	int test;

	nom_func("364");

	if(ob==132)
		test = 0;	
  if((fr3[ob][bt]==1)&&((fr3[ob][11]&(1<<bt))!=0))return(0);
  if((fr3[ob][bt]==0)&&((fr3[ob][11]&(1<<bt))==0))return(0);
  return(1);
}
//----------------------------------------------------------
//процедура фиксации восприятия состояния объекта при записи
//на диск и выдаче текстовых сообщений-предупреждений
void fix(int ob,int bt)
{
  
	nom_func("64");
  
  if(fr3[ob][bt]==1)
		fr3[ob][11]=fr3[ob][11]|(1<<bt);
  if(fr3[ob][bt]==0)
		fr3[ob][11]=fr3[ob][11]&(~(1<<bt));
  return;
}
//----------------------------------------------------------
//процедура изображения кнопки выдачи ответственных команд (не разделка)
void ris_otv_knop(int ob)
{
  unsigned int mrk1,//объект управления предварительный
  mrk2,//объект управления исполнительный
  pred,//предварительный объект
  isp,//исполнительный объект
  b_p,//бит предварительного объекта
  b_i,//бит исполнительного объекта
  x,//координата x
  y,//координата y
  ob_dob,//дополнительный(определяющий) объект
  b_d,//бит дополнительного объекта
  invers,//признак инверсии цветов
  cvt,//цвет исполниельного объекта
  cvt1,//цвет предварительного объекта
  inv1;

	nom_func("287");

  pred=fr1[ob][2];//получить предварительный
  isp=fr1[ob][3];//получить исполнительный
  invers=fr1[ob][10];//получить признак инверсии
  if(invers!=0)//если нужна инверсия
  {
    cvt=(fr1[pred][11]&0xff00)>>8;
    cvt1=(fr1[isp][11]&0xff00)>>8;
    invers=fr1[pred][11]&0xff;
    inv1=fr1[isp][11]&0xff;
  }
  else//если нет инверсии
  {
    invers=(fr1[pred][11]&0xff00)>>8;
    inv1=(fr1[isp][11]&0xff00)>>8;
    cvt=fr1[pred][11]&0xff;
    cvt1=fr1[isp][11]&0xff;
  }
  mrk1=fr1[ob][7];
  mrk2=fr1[ob][8];
  x=markery[mrk2][4];y=markery[mrk2][5];//получить координаты исполнительного
  if(fr3[ob][5]==1)
  {
    setfillstyle(1,11);
    bar(x-4,y-4,x+4,y+4);
    goto a;
  }
  b_p=(fr1[ob][4]&0xff00)>>8;
  b_i=fr1[ob][4]&0xff;
  if(fr3[pred][b_p]==1)setfillstyle(1,cvt);
  else setfillstyle(1,invers);
  bar(x-4,y-4,x+4,y);

  if(fr3[isp][b_i]==1)setfillstyle(1,cvt);
  else setfillstyle(1,invers);
  bar(x-4,y,x+4,y+4);
a:
  x=markery[mrk1][4];//получить координаты предварительного
  y=markery[mrk1][5];
  if(fr3[pred][5]==1)
  {
    setfillstyle(1,11);
    bar(x-4,y-4,x+4,y+4);
    return;
  }
  if((fr1[pred][9]<9999)&&(ob==pred))
  {
    ob_dob=fr1[pred][9]&0xfff;
    b_d=(fr1[pred][9]&0xf000)>>12;
    if(fr3[ob_dob][b_d]==1)setfillstyle(1,cvt);
    else setfillstyle(1,invers);
    bar(x-4,y-4,x+4,y+4);
    goto final;
  }
  if((fr3[isp][b_i]==1)&&(fr3[pred][b_p]==1))setfillstyle(1,cvt1);
  else setfillstyle(1,inv1);
  bar(x-4,y-4,x+4,y+4);
final:
  if((fr3[pred][b_p]==0)&&(zapusk==2))
  { if((STATUS==1)&&(tst_fix(pred,b_p)))
    { w(12,999,""); vtora=1;zapretvybora=1; zapusk++; fix(pred,b_p);}
  }
  else { fix(pred,b_p); fix(isp,b_i);}
}
//----------------------------------------------
//отображение "ворот" для УКГ
void UKG(int ob)
{
  int bt_kg, //бит для контроля габарита
  bt_okg, //бит отключателя контроля габарита
  upr,//объект управления отключателем
  bt_upr, //бит управления отключателем
  x,  //x-координата размещения "ворот"
  y,  //y-координата размещения "ворот"
  xt, //x-координата для вывода текста
  yt, //y-координата для вывода текста
  cvt, //цвет "ворот"
  cod; //код состояния
  
  nom_func("382");
      
  bt_kg=fr1[ob][2];
  bt_okg=fr1[ob][3];
  upr=fr1[ob][4]&0xfff;
  bt_upr=(fr1[ob][4]&0xf000)>>12;
  cod=fr3[ob][bt_kg]+fr3[ob][bt_okg]*2+fr3[upr][bt_upr]*4;
  switch(cod)
  {
    case 0:cvt=8;break;
    case 1:cvt=14;break;
    case 3:cvt=13;break;
    case 4:cvt=8;break;
    case 7:cvt=12;break;
    default: cvt=13;break;
  }
  x=fr1[ob][5];
  y=fr1[ob][6];
  xt=fr1[ob][8];
  yt=fr1[ob][9];
  if(fr3[ob][5]==1)cvt=11;
  setcolor(cvt);
  if(fr1[ob][7]==1)//если въезд справа
  {
    setlinestyle(0,0,1);
    line(x,y+2,x+3,y+5);line(x,y+1,x+3,y+4);
    line(x+3,y+5,x+6,y+5);line(x+3,y+4,x+6,y+4);
    line(x,y-2,x+3,y-5); line(x,y-1,x+3,y-4);
    line(x+3,y-5,x+6,y-5);line(x+3,y-4,x+6,y-4);
  }
  if(fr1[ob][7]==0)//если въезд слева
  {
    setlinestyle(0,0,1);
    line(x,y+2,x-3,y+5);line(x,y+1,x-3,y+4);
    line(x-3,y+5,x-6,y+5);line(x-3,y+4,x-6,y+4);
    line(x,y-2,x-3,y-5); line(x,y-1,x-3,y-4);
    line(x-3,y-5,x-6,y-5);line(x-3,y-4,x-6,y-4);
  }
  if(((biostime(0,0)-pooo[ob])>18)&&(pooo[ob]!=0))
  {
    setcolor(7);
    outtextxy(xt,yt,"███████████████████████");
    if((biostime(0,0)-pooo[ob])>36)pooo[ob]=biostime(0,0);
  }
  if(((cod==7)||(cod==0))&&(pooo[ob]==0))pooo[ob]=biostime(0,0);
  if(cod==0)
  {
    if(tst_fix(ob,bt_kg))
    {
      w(255,999,"");
      if(STATUS==1)sound(700);
    }
    setcolor(4);
    if((biostime(0,0)-pooo[ob])<18)
    {
      outtextxy(xt,yt,"НЕОБХОДИМО ВКЛЮЧИТЬ УКГ");
    }
  }
  else
    if(cod==7)
    {
      if(tst_fix(ob,bt_kg))
      {
        if(get_str(ob,bt_kg)==0)neisprav_na_disk('@',chudo);
        w(254,999,"");
        if(STATUS==1)sound(700);
      }
      setcolor(4);
      if((biostime(0,0)-pooo[ob])<18)
      {
        outtextxy(xt,yt,"СРАБОТАЛО УКГ");
      }
    }
    else
      {
        if(tst_fix(ob,bt_kg))nosound();
        pooo[ob]=0;
        setcolor(7);
        outtextxy(xt,yt,"███████████████████████");
      }
   fix(ob,bt_kg);
   fix(ob,bt_okg);
}
//------------------------------------------------------------------
//ob - номер объекта в базе
//bt - номер бита в объекте
//процедура отображения входного сигнала соседней станции
//param - тип входа в данную функцию
//param=0 - вход из объекта типа LRU (датчик сигнала) или смены направления
//param=1 - вход из объекта типа LKO (датчик огневого реле)
//param=5 - вход из анализатора таймера-по истечению времени
void lru_lko(int ob,int bt,int param)
{
	int ob_ru, // датчик сигнала
  bt_ru,     // бит сигнала
  ob_ko,     // датчик огневого
  bt_ko,     // бит огневого
  ob_nv,     // объект управления сменой направления
  ob_sn,     // объект смены направления
  cod,       // код состояния
  color,     // цвет сигнала
  ZZ,        // строка записей неисправностей
  CC,        // строка цветов на коды
  X,         // координата X лампы
  Y,         // координата Y лампы
  i;
  unsigned char  neisp;     // литера неисправности
  if(ZAGRUZKA!=0)return;
  
	if(fr1[ob][bt+2]==9999)return;//если объекта для данного бита нет - выйти
  
	// seg005:77FF loc_27AFF:
	ZZ=(fr1[ob][10]&0xff00)>>8;
	
	// seg005:7834  
  CC=fr1[ob][10]&0xff;
	
 	switch(param)//переключение по типу входа
 	{ //вход с параметрами сигнала
 		//seg005:784B loc_27B4B:
		case 0:
   	case 5:	 
				ob_ru = ob;
				bt_ru = bt;
				ob_ko = fr1[ob_ru][bt+2]&0xfff;
				bt_ko = (fr1[ob_ru][bt+2]&0xf000)>>12;
        break;
		//seg005:7895 loc_27B95:		
    case 1:	 
			  ob_ko = ob;
				bt_ko = bt;
				ob_ru = fr1[ob_ko][bt+2]&0xfff;
				bt_ru = (fr1[ob_ko][bt+2]&0xf000)>>12;
     	  break;
	}
	//seg005:78E3 loc_27BE3:  
  ob_nv = fr1[ob][bt+6];
  ob_sn = fr1[ob_nv][9];
  cod = fr3[ob_sn][1]*4+fr3[ob_ru][bt_ru]*2+fr3[ob_ko][bt_ko];
	//seg005:796F
  if(cod>=4)cod=cod-4;
	else cod=cod+4;
	
	if(pusto!=0)goto ris;//исключение анализа при отсутствии связи
	//seg005:7996 loc_27C96: 
	switch(cod)
	{ //если соседняя станция на приеме
		//если все в норме
		case 0: 
			break;
		//если огневое не в норме - сигнал закрыт-запустить таймер
		//ждем отпускания огневого или открытия сигнала
		case 1: 
			if(tst_fix(ob,bt)&&(pooo[ob_ru]==0))
				TIMER_SOB(ob_ru,3,bt_ru);
			if(param!=5)
				return;
			break;
		//если сигнал открыт - огневое в норме
		case 2: break;
		//если сигнал открыт - огневое в ненорме -запустить таймер
		case 3: if(tst_fix(ob,bt)&&(pooo[ob_ru]==0))TIMER_SOB(ob_ru,3,bt_ru);
						if(param!=5)return;
						break;
		//если соседняя станция на отправлении
		default: break;
	}
	//seg005:7A2F loc_27D2F:
	sbros_time(ob_ru,bt_ru);
	color = cvt[CC][cod];
	//seg005:7A55  
	if((cod<4)&&(tst_fix(ob_ru,bt_ru)||tst_fix(ob_ko,bt_ko)))
	{ 
		neisp = zvu_tabl[ZZ][cod+4];
		
		if(zvu_tabl[ZZ][cod]==1)//если требуется вывод на экран сообщения
		{
			if(neisp!=0)
			{ 
				//seg005:7AC1
				zvuk_vkl(0,0);
				if(get_str(ob_ko,bt_ko)==0)
					neisprav_na_disk(neisp,chudo);
				w(88,999,chudo);
			}
		}
	}
	//seg005:7B07 loc_27E07:  
	fix(ob_ru,bt_ru);
	fix(ob_ko,bt_ko);
	//seg005:7B1D
ris:
	X = fr1[ob_sn][6];
	if(X > 500)//если объект справа на экране
	{
		X = X+fr1[ob_sn][5]-5;
		Y = fr1[ob_sn][7]+7;
	}
	//seg005:7B71 loc_27E71:
	if((fr3[ob][5]==1)||(fr3[ob_sn][5]==1))
		setcolor(11);
	else 
		setcolor(color);
	//seg005:7BB7 
	setlinestyle(0,0,0);
	
	for(i=1;i<=2;i++)
		circle(X,Y,i); //seg005:7BCF  
	
	if(color==7) //seg005:7BE0 loc_27EE0:
		setcolor(12);
	circle(X,Y,3);
}
