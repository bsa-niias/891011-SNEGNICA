#include"bla.h"
#include <bios.h>
obrabotka_inf(int kanal)
{
  int kum=0,SMEZ=0,ST=0,jj;
#ifdef NALAD  
  nom_func("196");
#endif     
  vysvv = 9999;   //------------------------------ seg015:0041
  if((pusto&3)!=0) //---------------------------- seg015:004D 
		return;
  //------------------------------ seg015:0059 loc_468C9:
	kum = bu[kanal][1] & 0x02;
  
	if(kum != 2) //----------------------------- seg015:0076
		kum=1;
	
  if(otkaz_ts[kum-1] == 1)
		return;
	
  switch(bu[kanal][2])
  {
    case 'C': 
			if((pusto&3) != 0)
				return;
      if(kum == 2)
			{
				SMEZ = 0;  //------------------ seg015:00CE 
				ST = STR1;
			}
      else //------------------------ seg015:00DA loc_4694A: 
			{
				SMEZ = 0;
				ST = 0;
			}
      vysvv = strelok(bu[kanal],SMEZ,kum,ST);  //----------------- seg015:00FC
			break;

			//если объект собственных нужд контроллера
    //case 'J': do_it(kum,bu[kanal]);vysvv=1;break;
    case 'L':
#ifdef KOL_SOO2
      if(kum==2){SMEZ=STR2+SIG2+UCH2+PUT2;ST=UPR1;}
#endif
      if(kum==1)
			{
				SMEZ = STR1 + SIG1 + UCH1 + PUT1; //------------ seg015:0113
				ST = 0;
			}
      vysvv = kontroler(bu[kanal],SMEZ,kum,ST); //------- seg015:0135 
			break;
							
    case 'E':            //--------------------------- seg015:013A loc_469AA:  
			if((pusto&3) != 0)
				return;

#ifdef KOL_SOO2
       if(kum==2){SMEZ=STR2;ST=SIG1;}
#endif
       if(kum==1)   //------------------------------- seg015:014B 
				{
					SMEZ = STR1;
					ST = 0;
				}
        vysvv = signale(bu[kanal],SMEZ,kum,ST);
				break;
				
    case 'F': 
			if((pusto&3) != 0)
				return;
#ifdef KOL_SOO2
        if(kum==2){SMEZ=STR2+SIG2;ST=UCH1;}
#endif
        if(kum == 1)
				{
					SMEZ = STR1 + SIG1;  //----------------- seg015:018D  
					ST = 0;
				}
        vysvv = uchastic(bu[kanal],SMEZ,kum,ST);
				break;
				
    case 'I': 
			if((pusto&3)!=0) //-------------------- seg015:01BA 
				return;
#ifdef KOL_SOO2
              if(kum==2){SMEZ=STR2+SIG2+UCH2;ST=PUT1;}
#endif
        if(kum==1)  //----------------------- seg015:01C6
				{
					SMEZ = STR1+SIG1+UCH1; //---------  seg015:01CB
					ST=0;
				}
        vysvv = putec(bu[kanal],SMEZ,kum,ST);  //------------------------ seg015:01ED
				break;
				
    case 'J':  //--------------------------- seg015:01F3 loc_46A63
			for(jj=0;jj<9;jj++)
      { 
				if(bu[kanal][3] == D_kont[0][jj])//если объект собственных нужд 
        {
					do_it(kanal,bu[kanal]);  //----------------------------------------- seg015:022C
          vysvv=1;
          break;
				}
			} 
      break;            
			
    default:  
			vysvv = 9999;  //-------------- seg015:0252
			break;
  }
	//-------------------- seg015:0260
  if((DISK==0) && (vysvv!=9999))
		fixation(kanal,vysvv);
  return;
}
/**************************************************************/
int putec(unsigned char bufpu[11],int Smo, int kim,int sto)
{ //процедура распаковки сообщений для путей
  int Z=5,kh=0,M,l;
  unsigned int tst_bit,tst;
  unsigned char kop=0;
  int iv,jv,tester=999,reza=0,FIN=0,FN=0;
#ifdef NALAD
  nom_func("257");
#endif
  tester=999;
#ifdef KOL_SOO2
  if(kim==2)//если стойка 2
  {
    FN=PUT1;
    FIN=FN+PUT2;
  }
#endif
  if(kim==1) //если стойка 1
  {
    FIN=PUT1;
    FN=0;
  }
  for(iv=FN;iv<FIN;iv++) //пройти по подгруппам
  if(bufpu[3]==podgruppa[iv+Smo-sto])//если вышли на подгруппу
  {
    tester=iv;
    break;
  }
  if(tester==999) return(tester);//если подгруппа не найдена - вернуть 999
  for(jv=0;jv<Z;jv++)//пройти по объектам подгруппы
  {
    vysv=0;
    kh=spputi[tester][jv]; //взять номер объекта
    if(kh==1111) goto Bbreak; //если объект пустой - пропустить
    l=1;
    n=jv+4;
    for(M=0;M<=5;M++)//пройти по битам
    {
      kop=bufpu[n]&l; //получить значение бита
      if(kop==0)//если бит следует сбросить
      {
        if(fr3[kh][M]==0)goto nono;
        else// если ранее бит был установлен
        {
          if(fr1[kh][7]<9999)goto met0;//если участок приближения
          else
#ifdef PUTI_IN_2
          if(fr1[kh][13]!=9999)
          goto met0;
          else
          {
            if(CHET==2)
            {
              if((FN>0)&&//если вторая стойка и
              (M==2)&&(fr1[kh][8]==1010))//бит ЧИ и приемо-отправочный
              goto nono;//то уйти
              if((FN==0)&&(M==1)&&(fr1[kh][8]==1010)&&(skoko_stoek==2))goto nono;// если НИ,а стойка 1
              if(FN==0)tst_bit=1<<(M*2);//если первая стойка, то тест-бит нечетный
              else tst_bit=2<<(M*2);//если вторая стойка, то тест-бит четный
              tst_bit=~tst_bit;//инверсия тест-бита
            }
            else
            {
              if((FN>0)&&//если вторая стойка и
              (M==1)&&(fr1[kh][8]==1010))//бит НИ и приемо-отправочный
              goto nono;//то уйти
              if((FN==0)&&(M==2)&&(fr1[kh][8]==1010)&&(skoko_stoek==2))goto nono;// если НИ,а стойка 1
              if(FN==0)tst_bit=2<<(M*2);//если первая стойка, то тест-бит нечетный
              else tst_bit=1<<(M*2);//если вторая стойка, то тест-бит четный
              tst_bit=~tst_bit;//инверсия тест-бита
            }
          }
          fr3[kh][6]=fr3[kh][6]&tst_bit;//сбрасывание бита в слове увязки
          tst_bit=3<<(M*2);//формирование тест-бита на два разряда
          if((fr3[kh][6]&tst_bit)==0)
#endif
met0:     fr3[kh][M]=0;//если оба разряда увязки пустые сбросит бит в 0
          if((ZAGRUZKA==0)||(DISK!=0))
          {
            if(fr1[kh][0]==4)displaypathuch(kh);
            else displaypath(kh,M);//если не загрузка -нарисовать путь
          }
          vysv=1;//установить признаки получения изменения
          reza=1;
        }
      }
      else//если бит следует установить
      {
        if(fr3[kh][M]!=1) // если ранее был сброшен
        {
          if(fr1[kh][7]<9999)goto met1;
          else
#ifdef PUTI_IN_2
          if(fr1[kh][13]!=9999)goto met1;
          else
          if(CHET==2)
          {
            if((FN>0)&&(M==2)&&(fr1[kh][8]==1010)) goto nono;
            if((FN==0)&&(M==1)&&(fr1[kh][8]==1010)&&(skoko_stoek==2)) goto nono;
            if(FN==0)tst_bit=1<<(M*2);
            else tst_bit=2<<(M*2);
            fr3[kh][6]=fr3[kh][6]|tst_bit;
            tst_bit=3<<(M*2);
          }
          else
          {
            if((FN>0)&&(M==1)&&(fr1[kh][8]==1010)) goto nono;
            if((FN==0)&&(M==2)&&(fr1[kh][8]==1010)&&(skoko_stoek==2)) goto nono;
            if(FN==0)tst_bit=2<<(M*2);
            else tst_bit=1<<(M*2);
            fr3[kh][6]=fr3[kh][6]|tst_bit;
            tst_bit=3<<(M*2);
          }
          if((kh==167)&&(M==3))
          iv=0;
          if((fr3[kh][6]&tst_bit)!=0)fr3[kh][M]=1;
#endif
met1:     fr3[kh][M]=1;
          if((ZAGRUZKA==0)||(DISK!=0))
          {
            if(fr1[kh][0]==4)displaypathuch(kh);
            else displaypath(kh,M);
          }
          vysv=1;
          reza=1;
        }
      }
nono: l=l*2;
    }
    if(vysv==0&&ZAGRUZKA==0)time20sec(kh);//если нет новых данных по объекту
Bbreak:;
  }
  return(reza);//вернуть признак появления новых данных по объекту
}

/***************************************************************/
int uchastic(unsigned char bufus[11],int Smo,int kim,int sto)
{
	int kh=0,Z=5,M,test_bit,iv,jv,tester=9999,reza=0,FIN=0,FN=0,l;
  unsigned char kop=0;
#ifdef NALAD
  nom_func("379");
#endif
#ifdef KOL_SOO2
  if(kim==2){FIN=UCH1+UCH2;FN=UCH1;}
#endif
  if(kim==1){FIN=UCH1;FN=0;}
  for(iv=FN;iv<FIN;iv++)
  if(bufus[3]==podgruppa[iv+Smo-sto]){tester=iv;break;}
  if(tester==9999) return(tester);
	for(jv=0;jv<Z;jv++)
	{ vysv=0;
		kh=spspu[tester][jv];
		if(kh==1111) break;
		if(kh==3)
		n=0;
		l=1;
		n=jv+4;
		for(M=0;M<=5;M++)
		{ kop=bufus[n]&l;
      if(kop==0)//хёыш сшЄ эрфю ёсЁюёшЄ№
      {
        //хёыш ¤Єю фрээ√х яю ёрьюьє ╤╧ ш ╤╧ чрт чрэю т ъЁхёЄх
				if((fr1[kh][1]<3)&&(fr1[kh][2]<3)&&((fr1[kh][4]&1)==1))
				{
					if(fr3[kh][M]!=0){vysv=1;reza=1;}
					krest(kh,M,0);
					l=l*2;
					continue;
				}
				if(fr3[kh][M]!=0)// р сшЄ с√ы єёЄрэютыхэ
				{
					fr3[kh][M]=0;
					pooo[kh]=0;
					if((ZAGRUZKA==0)||(DISK!=0))
					{
#ifdef POLUAVTOMAT
						if(fr1[kh][1]==52)analiz_priem(kh,M);
						else
#endif
						if(fr1[kh][0]==3)sekci(kh,M);
						if(fr1[kh][0]==4)displaypathuch(kh);
						if(fr1[kh][0]==2)displaysignal(kh,M);
					}
					vysv=1;
					reza=1;
				}
			}
			else//хёыш сшЄ эрфю єёЄрэютшЄ№
			{
				if((fr1[kh][1]<3)&&(fr1[kh][2]<3)&&((fr1[kh][4]&1)==1))
				{
					if(fr3[kh][M]!=1){vysv=1;reza=1;}
					krest(kh,M,1);
					l=l*2;
					continue;
				}
				if(fr3[kh][M]!=1)//р сшЄ с√ы ёсЁю°хэ
				{ fr3[kh][M]=1;
					pooo[kh]=0;
					if((ZAGRUZKA==0)||(DISK!=0))
					{
#ifdef POLUAVTOMAT
						if(fr1[kh][1]==52)analiz_priem(kh,M);
						else
#endif
							if(fr1[kh][0]==3)sekci(kh,M);
							if(fr1[kh][0]==4)displaypathuch(kh);
							if(fr1[kh][0]==2)displaysignal(kh,M);
					}
					vysv=1;
					reza=1;
				}
			}
			l=l*2;
		}
		if((vysv==0)&&(ZAGRUZKA==0))time20sec(kh);
	}
	return(reza);
}
/******************/
int strelok(unsigned char bufstr[11],int Smo,int kim,int sto)
{
  int vse=0,
			Z=5,
			kh=0,
			M,
			iv,
			jv,
			tester=9999,
			reza=0,
			FN=0,
			FIN=0,
			l,
			sp_s,
			zm_sp;
  unsigned char kop=0;
#ifdef NALAD  
  nom_func("323");
#endif          
  tester=9999; //------------------- seg015:09AD  
#ifdef KOL_SOO2
  if(kim==2){FIN=STR1+STR2;FN=STR1;}
#endif
  if(kim==1){FIN=STR1;FN=0;}
	
  for(iv=FN;iv<FIN;iv++) //------------------- seg015:09C2 loc_47232: 
  if(bufstr[3]==podgruppa[iv+Smo-sto]) //-------- seg015:09DF 
	{
		tester=iv;  //-------------------- seg015:09EC 
		break;
	}
  
	if(tester==9999)
		return(tester);
  
	for (jv=0;jv<Z;jv++)
  {//--------------- seg015:05ED loc_46E5D:
    kh = spstr[tester][jv]; //----------- seg015:0A24 
    if(kh==1111)  //--------------------- seg015:0A29
			break;
			
		vysv = 0;	//--------------- seg015:0A37
		
spar:
    l = 1;
    n = jv + 4;  //-------------------------- seg015:0A4E 
    for(M = 0; M <= 5; M++)
    { 
			kop = bufstr[n]&l;  //-------------------- seg015:0A6E
      if(kop == 0)
      { 
				if(fr3[kh][M]!=0)  //------------------ seg015:0A8E 
					pooo[kh] = 0l; //---------------------- seg015:0AA1
				
        fr3[kh][M] = 0; //--------------------- seg015:0AC3
				if(fr1[kh][6]!=0)//------------------- seg015:0AD8  
				{
					sp_s = (fr1[kh][6]&0xff00)>>8;  //------------ seg015:0AFA
					if((ZAGRUZKA==0)||(DISK!=0))
					{
						krest(sp_s,2,2);  //--------------------------- seg015:0B24
						displaystrelka(fr1[kh][6]&0xff,M,vse);  //----- seg015:0B45    
					}
				}
				if((ZAGRUZKA==0)||(DISK!=0))
				displaystrelka(kh,M,vse); //------------ seg015:0B6C 
        vysv=1;
        reza=1;
      }
      else
      { //----------------------- seg015:0B88 loc_473F8: 
        if(fr3[kh][M] != 1)
        { 
					fr3[kh][M] = 1;
          pooo[kh] = 0;
					if(fr1[kh][6]!=0)
					{
						sp_s=(fr1[kh][6]&0xff00)>>8;  //яюыєўшЄ№ юс·хъЄ фы  ╤╧
						if((ZAGRUZKA==0)||(DISK!=0))
						{
							krest(sp_s,2,2);
							displaystrelka(fr1[kh][6]&0xff,M,vse);
						}
					}
          if((ZAGRUZKA==0)||(DISK!=0))
          displaystrelka(kh,M,vse);
          vysv=1;
          reza=1;
        }
      }
      l=l*2;
    }
    if((vysv==0)&&(ZAGRUZKA==0))time20sec(kh);
    if (vse==1)vse=0;
    else
    if(fr1[kh][12]!=9999)
    {
      TEST=2;
      kh=poisk_ras(fr1[kh][2],kh);
      vse=1;
      goto spar;
    }
  }
  return(reza);
}

/****************************************************************/

int kontroler(unsigned char bufde[11],int Smo,int kim,int sto)
{
  int vs=0,kh=0,Z=5,M,iv,jv,tester=9999,reza=0,FN=0,FIN=0,KOKS=0,l;
  unsigned char kop=0;
#ifdef NALAD
  nom_func("132");
#endif
  vysv=0;
#ifdef KOL_SOO2
  if(kim==2){FIN=UPR1+UPR2;FN=UPR1;}
#endif
  if(kim==1){FIN=UPR1;FN=0;}
  for(iv=FN;iv<FIN;iv++)if(bufde[3]==podgruppa[iv+Smo-sto]){tester=iv;break;}
  if(tester==9999) return(tester);
  for (jv=0;jv<Z;jv++)//пройти по всем объектам подгруппы
  { kh=spkont[tester][jv];//взять очередной объект
    if(kh==1111) goto BReak;//если объект не смотреть, то пропустить
    if(fr1[kh][1]==9999)goto BReak;//если объект пустой, то пропустить
    l=1; n=jv+4; //установить тест-бит в исходное,встать на байт первого объекта
    for(M=0;M<=5;M++)// пройти по битам объета
    { kop=bufde[n]&l;//получить значение очередного бита
      if(kop==0)// если по объекту произошел сброс бита
      { //если отпустило групповое или объектное
        if((fr1[kh][1]>=1000)&&(M<=1))
        {
          if((ZAGRUZKA==0)||(DISK!=0))
          { if(fr3[kh][M]!=0)reza=1;//если до сих пор реле было под током
            fr3[kh][M+6]=fr3[kh][M];//запомнить ранее имевшееся значение для бита
          }
          fr3[kh][M]=0;//установить текущее значение
          //проверить корректность прохождения команды
          if((ZAGRUZKA==0)||(DISK!=0))
          test_deshifr(kh,M);
          goto kiv;
        }
      //далее для объектов не групповых и не объектных реле
        if(fr3[kh][M]!=0)//если объект был в состоянии 1
        { fr3[kh][M]=0; //установить его в 0
          if((ZAGRUZKA==0)||(DISK!=0))
          {vysv=1;reza=1;}  //зафиксировать факт изменения
        }
      }
      else //если по объекту произошла установка бита
      {
        //если сработало групповое или объектное
        if((fr1[kh][1]>=1000)&&(M<=1))
        {
          if((ZAGRUZKA==0)||(DISK!=0))
          { if(fr3[kh][M]!=1)reza=1;//зафиксировать факт изменения объекта
            fr3[kh][M+6]=fr3[kh][M];//запомнить предыдущее состояние бита
          }
          fr3[kh][M]=1;
          if((ZAGRUZKA==0)||(DISK!=0))
          {test_deshifr(kh,M);vysv=1;reza=1;}
          goto kiv;
        }
      //далее для объектов не групповых и не объектных реле
        if(fr3[kh][M]!=1)
        { fr3[kh][M]=1;
          if((ZAGRUZKA==0)||(DISK!=0))
          {vysv=1;reza=1;}
        }
      }
kiv:
      if((ZAGRUZKA==0)||(DISK!=0))
      { if((fr1[kh][1]==911)&&(vysv==1))//если проблемы с памятью
        { Pam(kh,M);
          vysv=0;
          vs=1;
        }
        //при обнаружении ошибок работы выходного интерфейса
        if((fr1[kh][1]>=1000)&&(vysv==1)&&(M>1))
        { dispdatch(kh,M);
          vysv=0;
          vs=1;
        }
        //для объекта KVV (ввода вывода)
        if((fr1[kh][1]==11)&&(vysv==1))
        { kvv(kh,M);
          if(M>0){ vs=1; reza=1;}
          else { vs=0;reza=0;}
          vysv=0;
        }
        //для объекта Ар из состава KS
        if((fr1[kh][1]==13)&&(M==2))
        {
#ifdef KOL_SOO2
          if(kim==2) KOKS=KS2;
          else
#endif
          KOKS=KS1;
        }
        //если получено изменение по объекту KS (биты Р,Ао,Ар или непарафазность)
        if((fr1[kh][1]==13)&&(vysv==1)&&(M<=5))
        {komplekt(kh,M);vysv=0;vs=1;}
      }
      l=l*2;
    }
asa:
    if(fr1[kh][1]==6)test_marsh(kh);
    if((vysv==1)&&(ZAGRUZKA==0))
    if(vs==1){vs=0; vysv=1; reza=1;}
    if((vysv==1)&&(ZAGRUZKA==0))
    { if(fr3[kh][5]==1)slom_interf(kh);
      if(fr1[kh][1]==12)tel_vkl_vikl(kh);
    }
BReak:
    ;//переход на следующий объект (если был не последний
  }
it:
  return(reza);
}
//--------------------------------------------------------------
int signale(unsigned char bufsig[11],int Smo,int kim,int sto)
{
  int kh=0,
			M,
			jo,
			iv,
			jv,
			sled,
			tek,
			tester=9999,
			reza=0,
			i_str,
			str,
			p,
			sp,
			kod,
			para,
			l;
	unsigned char kop=0;
	int 
		FN=0,
		FIN=0;
#ifdef NALAD
	nom_func("304");
#endif
	tester=9999;
#ifdef KOL_SOO2
	if(kim==2){FIN=SIG1+SIG2;FN=SIG1;}
#endif
	if(kim==1)
	{
		FIN = SIG1;
		FN = 0;
	}
	for(iv = FN; iv < FIN; iv++)
	if(bufsig[3]==podgruppa[iv+Smo-sto])
	{
		tester = iv;
		break;
	}
	if(tester==9999)
		return(tester); //--------------- seg015:1387 loc_47BF7: 
	
	for(jv=0;jv<5;jv++) //--------------------- seg015:139C loc_47C0C:  
  { 
		vysv=0;
    kh = spsig[tester][jv];  //------------- seg015:13BE   
    if(kh == 1111) 
			goto Bre;
		if((kh==117)&&(ZAGRUZKA==0))
		M = 0;
    
		l = 32;
    n = jv+4;
    for(M = 5; M >= 0; M--)
    { kop=bufsig[n]&l;
      if(kop==0)//если бит сбрасывается
      {
				if(fr3[kh][M]!=0)//если бит был установлен
				{ fr3[kh][M]=0;
					pooo[kh]=0;
					if((ZAGRUZKA==0)||(DISK!=0))displaysignal(kh,M);
					vysv=1;reza=1;
				}
			}
			else//если бит устанавливается
			{ if(fr3[kh][M]!=1)//если бит был сброшен
				{ fr3[kh][M]=1;
					pooo[kh]=0;
					if(M<4)//если устанавливается ВС или открывается сигнал
					{ if(komanda2[kim-1]==kh)
						{ tek=komanda2[kim-1];
							jo=0;
							while(1)
							{
								sled=fr3[tek][8]&0xfff;
								if((fr3[tek][10]==0)&&(fr3[tek][8]==0))break;
								fr3[tek][8]=0;
								fr3[tek][10]=0;
								if(sled==0xfff)break;
								tek=sled;
							}
							komanda2[kim-1]=0;
						}
					}
					if((ZAGRUZKA==0)||(DISK!=0))displaysignal(kh,M);
					vysv=1;
					reza=1;
				}
			}
			if((M<4)&&(ZAGRUZKA==0)&&(kh<kol_OSN))
			{ if(fr2[kh][8]!=0)sp=fr2[kh][8];//если есть СП,взять его номер
				if(fr2[kh][3]!=0)//если для сигнала есть стрелки в пути
				for(i_str=3;i_str<8;i_str++)
				{ if(fr2[kh][i_str]==0)break;//если очередной стрелки нет
					str=fr2[kh][i_str]&0xfff;//получить номер для стрелки
					p=(fr2[kh][i_str]&0xf000)>>12;//получить тип замыкания
					kod=(fr3[kh][0]|fr3[kh][2])*2;//проверить маневровые
					kod=kod+(fr3[kh][1]|fr3[kh][3]);//добавить поездные
					switch(p)//переключение по типу замыкания
					{
						case 0: break;
						//четное поездное
						case 2: if(fr1[kh][1]==0)//если сигнал четный
										{
											if((kod==1)||(kod==3))//если поездной сигнал открыт
											{
												if(fr3[sp][1]==1)//если СП замкнута
												fr4[str][0]=fr4[str][0]|8;
											}
											else//если поездной сигнал закрыт
											{
												if(fr3[sp][1]==0)//если СП разомкнута
												fr4[str][0]=fr4[str][0]&0xfff7;
											}
										}
										break;
							//четное любое
							case 3: if(fr1[kh][1]==0)//если сигнал четный
											{
												if(kod!=0)//если какой-либо сигнал открыт
												{
													if(fr3[sp][1]==1)//если СП замкнута
													fr4[str][0]=fr4[str][0]|8;
												}
												else //если все сигналы закрыты
												{
													if(fr3[sp][1]==0)//если СП разомкнута
													fr4[str][0]=fr4[str][0]&0xfff7;
												}
											}
											break;
							//нечетное поездное
							case 4: if(fr1[kh][1]==1)//если сигнал нечетный
											{
												if((kod==1)||(kod==3))//если поездной сигнал открыт
												{
													if(fr3[sp][1]==1)//если СП замкнута
													fr4[str][0]=fr4[str][0]|0x10;
												}
												else //если поездной сигнал закрыт
												{
													if(fr3[sp][1]==0)//если СП разомкнута
													fr4[str][0]=fr4[str][0]&0xffef;
												}
											}
											break;
							//нечетное любое
							case 5: if(fr1[kh][1]==1)//если сигнал нечетный
											{
												if(kod!=0)//если какой-либо сигнал открыт
												{
													if(fr3[sp][1]==1)//если СП замкнута
													fr4[str][0]=fr4[str][0]|0x10;
												}
												else //если все сигналы закрыты
												{
													if(fr3[sp][1]==0)//если СП разомкнута
													fr4[str][0]=fr4[str][0]&0xffef;
												}
											}
											break;
							//четное - нечетное поездные
							case 6:   if((kod==1)||(kod==3))//если поездной сигнал открыт
												{
													if(fr3[sp][1]==1)//если СП замкнута
													fr4[str][0]=fr4[str][0]|0x18;
												}
												else //если поездной сигнал закрыт
												{
													if(fr3[sp][1]==0)//если СП разомкнута
													fr4[str][0]=fr4[str][0]&0xffe7;
												}

												break;
						//четное -   нечетное любое
							case 7:   if(kod!=0)//если любой сигнал открыт
												{
													if(fr3[sp][1]==1)//если СП замкнута
													fr4[str][0]=fr4[str][0]|0x18;
												}
												else //если сигналы закрыты
												{
													if(fr3[sp][1]==0)//если СП разомкнута
													fr4[str][0]=fr4[str][0]&0xffe7;
												}
												break;
							default: w(44,sp," 4");break;
					}
					nach_zakr(str,0);
					if(fr1[str][12]!=9999)
					{ TEST=2;
						para = poisk_ras(fr1[str][2],str);
						fr4[para][0]=fr4[str][0];
						nach_zakr(para,0);
					}
				}
			}
			l=l>>1;
		}
		if((vysv==0)&&(ZAGRUZKA==0))time20sec(kh);
Bre:;
	}
  return(reza);
}
/*******************************************/
fixation(int knl, int need)
{
#ifdef NALAD  
  nom_func("67");
#endif  
  if(DISK!=0)return;
  if((need==1)||(ZAGRUZKA==1))
  { if((prv[0]==1)&&(knl==0))
    {
      /*outportb(0x2F8,0x61);*/
      add(0,'п');
      SBROS_BIT_TEST_SOOB(0,bu[0][3]);
      prv[0]=0;
    }
#ifdef KOL_SOO2
    if((prv[1]==1)&&(knl==1))
    {
      /*outportb(0x2F8,0x62);*/
      add(1,'в');
      SBROS_BIT_TEST_SOOB(1,bu[1][3]);
      prv[1]=0;
    }
#endif
  }
}
//-----------------------------
//процедура вызывается при отсутствии изменений для текущего объекта
//предназначена для анализа получения изменений по объектам в заданный
//интервал времени после выдачи команды
time20sec(int numba)
{
  long TIME_CC,vr;
  int goj=0, vmv=0;
#ifdef NALAD  
  nom_func("359");
#endif    
  if((numba==AVAch)||(numba==AVAn))
	return;
	
	if((fr1[numba][0]==2)&&(numba<kol_OSN))
		TIME_CC=1400L;//для сигналов - 80 сек
	else 
		TIME_CC=360L; //для других объектов - 20 сек
  
	if(pooo[numba]!=0l)//если для объекта включен таймер
  {
    vmv = fr1[numba][13] - 1;
    //коррекция с учетом возможной очереди объектов
    if(t_com[vmv]!=0l)
			pooo[numba] = t_com[vmv];
		
    vr = biostime(0,0l);  //зафиксировать текущее время
    if((vr - pooo[numba]) >= TIME_CC) //если прошло более заданного
    {
#ifdef KOL_SOO2
      if(flagoutmsg==12)//если задан сквозной маршрут
      {
        if((fr1[numba][0]==2)&&(fr1[numba][1]==1))//если нечетный маршрут

        {
          for(vmv=0;vmv<1;vmv++)//пройти по нечетным маршрутам
          if(Skvo[vmv].B2_s==numba)//если это сигнал начала второй половины
          {
            fin_kom();//сбросить команду
            break;
          }
        }
        else //если четный маршрут
        {
          for(vmv=1;vmv<2;vmv++) //пройти по четным маршрутам
          if(Skvo[vmv].B2_s==numba)//если это сигнал начала второй половины
          {
            fin_kom();//сбросить команду
            break;
          }
        }
      }
#endif
      //zvuk_vkl(1,30);//дать звуковой сигнал
      //if(fr1[numba][1]!=18)
			//	w(239,numba," ЕГО СОСТОЯНИЯ НЕ ИЗМЕНИЛА");
      
			if(pooo[numba]!=0l)
				pooo[numba]=0l;//сбросить фиксатор времени
      
			test_prigol_otm(numba);
      test_ra_fini(numba);
    }
    else test_not_ra(numba);
  }
}
//------------------------------------------------
test_prigol_otm(int nemba)
{
#ifdef NALAD  
  nom_func("349");
#endif  
  //если вспомогательная смена направления 
  if((fr1[nemba][0]==2)&&( fr1[nemba][1]>=400)&&( fr1[nemba][1]<=600))
  {
    fr3[nemba][9]=0;//сброс флага команды 
    vtora=0;//сброс признака для выдачи второй половины команды 
    if((nikuda==0)&&(klo==0)&&(help==0))
    {
      if((otv_kom==1)&&(i3==modi))home(modi);//курсор на место 
      t(0);//очистить строку интерактива 
    }
    zabeg=0;//сброс флагов
  }
}
//--------------------------------------------------------------
test_not_ra(int nemba)
{
#ifdef NALAD  
  nom_func("343");
#endif  
  if((fr1[nemba][0]==3)||(fr1[nemba][0]==4))
  if((fr1[nemba][1]==301)||((fr1[nemba][1]>=200)&&(fr1[nemba][1]<=300)))
  fr3[nemba][9]=0;//сброс флага выдачи команды

}
/**********************************************************/
test_ra_fini(int nemba)
{
#ifdef NALAD  
  nom_func("351");
#endif  
  if((fr1[nemba][0]==3)||(fr1[nemba][0]==4))//если УП или СП
  if((fr1[nemba][1]>=200)&&(fr1[nemba][1]<=300))//объект разделки (РИ)
  {
    fr3[nemba][9]=0;//сбросить метку команды
    was[markery[fr1[nemba][5]][7]-10]=0;//сбросить флаг в массиве учета
    if((klo==0)&&(nikuda==0)&&(help==0))//если система в обычном состоянии
    {
      if((otv_kom==1)&&(i3==modi)&&(fr1[nemba][5]==modi))//если ОК и маркер на объекте
      {
        t(0); //стереть окно интерактива
        zalet=0;vtora=0;//сбросить флаги
        regs.h.ah=5;
        regs.h.ch=0x39;
        regs.h.cl=0x20;
        int86(0x16,&regs,&regs);
        w(169,nemba,"09");
        zvuk_vkl(1,9);
      }
    }
  }
}
//------------------------------------
test_marsh(int obj)
{
  int i,j,k,tek,sled;
  unsigned int kod[skoko_stoek];
#ifdef NALAD
  nom_func("340");
#endif
  if(STATUS!=1)return;
  j=fr1[obj][13]-1;
  kod[j]=0;
  for(i=0;i<=5;i++)kod[j]=kod[j]+(fr3[obj][i]<<i);
  kod[j]=kod[j]|0x40;
  if(komanda2[j]==0)return;//если не было команды - не анализировать
  //если команда выдана недавно не анализировать
  if((biostime(0,0l)-pooo[komanda2[j]])<10l)return;
  if(kod[j]==64){MAR_GOT[j]=kod[j];return;}
  else
  { if(MAR_GOT[j]!=kod[j])
    { MAR_GOT[j]=kod[j];
      if(ZAGRUZKA==0)t_com[j]=biostime(0,0l);
    }
  }
  i=j;
  j=0;
  if(komanda2[i]!=0)//если объект из данной стойки
  {
    if(kod[i]==96)
    {
      w(21,komanda2[i],"");
      pooo[komanda2[i]]=0;
      tek=komanda2[i];
      while(1)
      { sled=fr3[tek][8]&0xfff;
				if((fr3[tek][10]==0)&&(fr3[tek][8]==0))break;
				fr3[tek][8]=0;fr3[tek][10]=0;
				if(sled==0xfff)break;
				tek=sled;
			}
			komanda2[i]=0;
			marshrut[i][0]=0;
			marshrut[i][1]=0;
			marshrut[i][2]=0;
		}
		if(kod[i]==0x50)
		{ if(marshrut[i][0]==0)
			{
				while(1)
				{ sled=fr3[tek][8]&0xfff;
					if((fr3[tek][10]==0)&&(fr3[tek][8]==0))break;
					fr3[tek][8]=0;fr3[tek][10]=0;
					if(sled==0xfff)break;
					tek=sled;
				}
			}
			if(marshrut[i][0]!=0)
			{ kod[i]=0;
        for(j=0;j<5;j++)
        { if((strelki[j][0]!=0)&&(fr1[strelki[j][0]][13]!=(i+1)))
          { if(fr3[strelki[j][0]][0]!=strelki[j][1])kod[i]=kod[i]+1;
            if(fr3[strelki[j][0]][1]!=strelki[j][2])kod[i]=kod[i]+1;
          }
        }
        if(kod[i]==0)
        {
          nach_marsh=marshrut[i][0];marshrut[i][0]=0;
          end_marsh=marshrut[i][1];marshrut[i][1]=0;
          half_marsh=marshrut[i][2];marshrut[i][2]=0;
          komanda2[i]=nach_marsh;
          for(j=0;j<5;j++)
          if(fr1[strelki[j][0]][13]!=(i+1))
          {
            strelki[j][0]=0;
            strelki[j][1]=0;
            strelki[j][2]=0;
          }
          if(DISK==0)zad_marsh();
        }
      }
    }
  }
}

//------------------------------------------------
krest(int ob,int BT,int param)
{
  int str_l, //ыхтр  ёЄЁхыър ╤╧
  str_p, //яЁртр  ёЄЁхыър ╤╧
  sp_l,//ыхтр  ўрёЄ№ ╤╧
  sp_p; //яЁртр  ўрёЄ№ ╤╧
  str_l=(fr1[ob][3]&0xff00)>>8;//тч Є№ ыхтє■ ёЄЁхыъє
  str_p=fr1[ob][3]&0xff;//тч Є№ яЁртє■ ёЄЁхыъє
  sp_l=(fr1[str_l][6]&0xff00)>>8;//тч Є№ ёя фы  ыхтющ ёЄЁхыъш
  sp_p=(fr1[str_p][6]&0xff00)>>8;//тч Є№ ёя фы  яЁртющ ёЄЁхыъш
  if((fr3[str_l][0]==1)&&(fr3[str_l][1]==0))//хёыш ыхтр  т яы■ёх
  {
    if((fr3[str_p][0]==1)&&(fr3[str_p][1]==0))//хёыш яЁртр  т яы■ёх
    {
      fr3[sp_l][6]=0;
      fr3[sp_p][6]=0;
    }
    if((fr3[str_p][0]==0)&&(fr3[str_p][1]==1))//хёыш яЁртр  т ьшэєёх
    {
      fr3[sp_l][6]=1;//чряЁхЄшЄ№ ЁшёютрЄ№ ыхтюх ╠╤╧
      fr3[sp_p][6]=0;
    }
  }
  else
    if((fr3[str_l][0]==0)&&(fr3[str_l][1]==1))//хёыш ыхтр  т ьшэєёх
    {
      if((fr3[str_p][0]==1)&&(fr3[str_p][1]==0))//хёыш яЁртр  т яы■ёх
      {
        fr3[sp_l][6]=0;
        fr3[sp_p][6]=1;//чряЁхЄшЄ№ ЁшёютрЄ№ яЁртюх ╠╤╧
      }
      if((fr3[str_p][0]==0)&&(fr3[str_p][1]==1))//хёыш яЁртр  т ьшэєёх
      {
        fr3[sp_l][6]=0;
        fr3[sp_p][6]=0;
      }
    }
    else
    {
      fr3[sp_l][6]=0;
      fr3[sp_p][6]=0;
    }
  if(param==2)return;
  if(param==0)//хёыш яюыєўхэ 0
  {
    if((fr3[sp_l][BT]!=0)||(fr3[sp_p][BT]!=0))
    {
      vysv=1;
      fr3[sp_l][BT]=0;
      fr3[sp_p][BT]=0;
      goto ris;
      if((ZAGRUZKA==0)&&(klo==0)&&(nikuda==0)&&(help==0))
      {sekci(sp_l,BT);sekci(sp_p,BT);}
    }
    return;
  }
  if(BT==5)
  {
    fr3[sp_l][5]=1;
    fr3[sp_p][5]=1;
    goto ris;
  }
  //хёыш яюыєўхэр 1
  if((fr3[str_l][0]==2)||(fr3[str_p][0]==2))
  {
    fr3[sp_l][BT]=1;
    fr3[sp_p][BT]=1;
    goto ris;
  }

  fr3[sp_l][BT]=1;
  fr3[sp_p][BT]=1;
  goto ris;
  if((fr3[str_l][0]==1)&&(fr3[str_l][1]==0))//хёыш ыхтр  т яы■ёх
  {
    if((fr3[str_p][0]==1)&&(fr3[str_p][0]==0))//хёыш яЁртр  т яы■ёх
    {
      if((fr3[sp_l][BT]!=1)||(fr3[sp_p][BT]!=1))vysv=1;
      fr3[sp_l][BT]=1;
      fr3[sp_p][BT]=1;
    }
    else//хёыш яЁртр  эх т яы■ёх
    if((fr3[str_p][0]==0)&&(fr3[str_p][1]==1))//хёыш яЁртр  т ьшэєёх
    {
      if((fr3[sp_l][BT]==1)||(fr3[sp_p][BT]==0))vysv=1;
      fr3[sp_l][BT]=0;
      fr3[sp_p][BT]=1;
    }
    else //хёыш яЁртр  схч ъюэЄЁюы 
    {
      fr3[sp_l][BT]=1;
      fr3[sp_p][BT]=1;
    }
  }
  else //хёыш ыхтр  эх т яы■ёх
    if((fr3[str_l][0]==0)&&(fr3[str_l][1]==1))//хёыш ыхтр  т ьшэєёх
    {
      if((fr3[str_p][0]==1)&&(fr3[str_p][1]==0))//хёыш яЁртр  т яы■ёх
      {
        if((fr3[sp_l][BT]==0)||(fr3[sp_p][BT]==1))vysv=1;
        fr3[sp_l][BT]=1;
        fr3[sp_p][BT]=0;
      }
      else //хёыш яЁртр  эх т яы■ёх
      if((fr3[str_p][0]==0)&&(fr3[str_p][1]==1))//хёыш яЁртр  т ьшэєёх
      {
        if((fr3[sp_l][BT]==0)||(fr3[sp_p][BT]==0))vysv=1;
        fr3[sp_l][BT]=1;
        fr3[sp_p][BT]=1;
      }
    }
    else //хёыш ыхтр  схч ъюэЄЁюы 
    {
      fr3[sp_l][BT]=1;
      fr3[sp_p][BT]=1;
    }
ris:
    if((ZAGRUZKA==0)&&(nikuda==0)&&(klo==0)&&(help==0))
    {
      sekci(sp_l,BT);
      sekci(sp_p,BT);
    }
}
