#include"bla.h"
#include<bios.h>
form_kom_put(int poin,int kod)
{ int nomer,i18,j18,n=0,mar,SDVIG=0,FN=0,FIN=0,OGR=0;
#ifdef NALAD  
  nom_func("79");
#endif    
  n=poin;
  mar=fr1[poin][9];
  for(i18=0;i18<11;i18++)buf_ko_p[i18]=0;
  if(fr1[n][13]==1)
  { buf_ko_p[1]=0x61;
    if(fr1[n][0]==5)
    {buf_ko_p[2]='I';SDVIG=STR1+SIG1+UCH1;FN=0;FIN=PUT1;}
    else {buf_ko_p[2]='F';
    SDVIG=STR1+SIG1;FN=0;FIN=UCH1;}
  }
#ifdef KOL_SOO2
  else
  { buf_ko_p[1]=0x62;
    if(fr1[n][0]==5)
    { buf_ko_p[2]='I';
      SDVIG=STR2+SIG2+UCH2;
      FN=PUT1;
      FIN=FN+PUT2;
    }
    else
    { buf_ko_p[2]='F';
      SDVIG=STR2+SIG2;
      FN=UCH1;
      FIN=FN+UCH2;
    }
  }
#endif
  nomer=9999;
  for (i18=FN;i18<FIN;i18++)for(j18=0;j18<=4;j18++)
  { if(fr1[n][0]==5)
    { if(spputi[i18][j18]==n)
      {podgr=podgruppa[i18+SDVIG-FN];nomer=j18;break;}
    }
    else
    { if(spspu[i18][j18]==n)
      {podgr=podgruppa[i18+SDVIG-FN];nomer=j18;break;}
    }
  }
  if(nomer==9999) return;
  buf_ko_p[3]=podgr;
  for (j18=0;j18<=4;j18++)
  if(j18==nomer)buf_ko_p[j18+4]=kod;
  else buf_ko_p[j18+4]=124;
  buf_ko_p[9]=check_sum(buf_ko_p);
  buf_ko_p[0]='(';buf_ko_p[10]=')';flms=1;
  kom_v_bufer_pvm(1,"p");
}
//-----------------------------------------------------
form_kom_str(int poin,unsigned char kod)
{ //формирование команды для передачи команд ограничения стрелок
  int nomer,podegr,i18,j18,n=0,SDVIG=0,FN=0,FIN=0,nnom=9999;
#ifdef NALAD  
  nom_func("81");
#endif        
  disco();
  for(i18=0;i18<11;i18++)buf_ko_p[i18]=0;//очистить буфер команд
  buf_ko_p[2]='S';//установить код группы "стрелки"
  point=poin;//установить номер для стрелки
  if(Opred()<0)return;//найти стрелку, входящую в сообщения (имеет смысл для спаренных)
  poin=point;//передача найденного номера
  n=poin;
  //для стрелок из первой стойки ТУМС сформировать заголовок
  if(fr1[n][13]==1){buf_ko_p[1]=0x61;SDVIG=0;FN=0;FIN=STR1;}
#ifdef KOL_SOO2
  //аналогично для стрелок второй стойки
  else {buf_ko_p[1]=0x62;SDVIG=0;FN=STR1;FIN=FN+STR2;}
#endif
  nomer=9999;
  for (i18=FN;i18<FIN;i18++)//пройти по подгруппам стрелок данной стойки
  for(j18=0;j18<=4;j18++)//пройти по объектам очередной подгруппы 
  if (spstr[i18][j18]==n)//если найдена стрелка 
  {
    podegr=podgruppa[i18+SDVIG-FN];//выбрать подгруппу 
    nomer=j18;//взять номер объекта в подгруппе 
    break;
  }
  if(nomer==9999)//если объект не найден
  {
    TEST=2;
    nnom=poisk_ras(fr1[n][2],n);//поискать спаренную стрелку 
    if(nnom==9999)return;//если не найдена парная - выход 
    else//если найдена парная
    {
      for (i18=FN;i18<FIN;i18++)//найти для неё подгруппу 
      for(j18=0;j18<=4;j18++)//найти для подгруппы номер байта 
      if (spstr[i18][j18]==nnom)//если найдено 
      {
        podegr=podgruppa[i18+SDVIG-FN];//взять подгруппу 
        nomer=j18;//взять номер объекта 
        break;
      }
    }
  }
  buf_ko_p[3]=podegr; //запомнить код подгруппы 
  for (j18=0;j18<=4;j18++)// пройти по всем объектам подгруппы 
  if (j18==nomer) buf_ko_p[j18+4]=kod; //для найденного объекта записать код 
  else  buf_ko_p[j18+4]=124;//для остальных объектов - записать код-заполнитель 
  buf_ko_p[9]=check_sum(buf_ko_p);//получить и записать контрольную сумму 
  buf_ko_p[0]='(';//заполнить начало и конец команды скобками-ограничителями
  buf_ko_p[10]=')';
  flms=1;//установить признак-требование передачи в соседнюю ПЭВМ
  if(kom_v_bufer_pvm(1,"C")==-1)//если вызов процедуры неудачен
  {
    MY_COM=0;//сбросить признак наличия в ПЭВМ команды для соседа
    MY_INF=0;//сбросить признак наличия в ПЭВМ информации для соседа
    MY_FR4=0;//сбросить признак наличия в ПЭВМ ограничений для соседа
    POVTOR_COM=0;//сбросить требование повтора команды соседу
    POVTOR_INF=0;//сбросить требование повтора информации соседу
    POVTOR_FR4=0;//сбросить требование повтора ограничений соседу
  }
}
//-------------------------------------------------------
zad2_marsh()
{ //процедура задания сквозного маршрута через две стойки
#ifdef KOL_SOO2
  int vv=0,vmv=0;
#ifdef NALAD
  nom_func("422");
#endif
  if(DISK!=0)return;
  buf_ko[2]='b';//записать в буфер для первой и второй стоек код поездного
  buf_ko_mm[2]='b';
  vmv=9999;
  if(fr1[nach_marsh][1]==1)//если маршрут нечетный
  {
    for(vmv=0;vmv<2;vmv++)//пройти по сквозным маршрутам
    if(Skvo[vmv].B1_s==nach_marsh) break;//если нашли маршрут с таким началом
  }
  else //если маршрут четный
  {
    for(vmv=2;vmv<4;vmv++)//пройти по сквозным четным
    if(Skvo[vmv].B1_s==nach_marsh) break;//если нашли такое начало
  }
  komanda2[fr1[Skvo[vmv].B2_s][13]-1]=Skvo[vmv].B2_s;
  komanda2[fr1[Skvo[vmv].B1_s][13]-1]=Skvo[vmv].B1_s;
  if(vmv>3)return;
  vv=vibor(Skvo[vmv].B2_s);//получить для начала второго полумаршрута код-индекс
  buf_ko[1]=BAM;//заполнить заголовок во втором буфере
  if(vv!=9999)buf_ko[4]=vv;//заполнить код-индекс
  buf_ko[3]=podgr;//заполнить подгруппу
  vv=vibor(Skvo[vmv].E2_s);//получить код-индекс для конца второго полумаршрута
  if(vv!=9999)  buf_ko[6]=vv;//заполнить подгруппу
  buf_ko[5]=podgr;
  buf_ko[7]=124;//в свободные байты записать заполнитель
  buf_ko[8]=124;
  buf_ko[9]=check_sum(buf_ko); //дополнить команду контрольной суммой
  buf_ko[0]='(';
  buf_ko[10]=')';
  pooo[Skvo[vmv].B2_s]=biostime(0,0L);//зафиксировать время
  vv=vibor(Skvo[vmv].B1_s);//получить код-индекс для начала первого полумаршрута
  buf_ko_mm[1]=BAM;//вписать заголовок в первый буфер
  if(vv!=9999)buf_ko_mm[4]=vv;//вставить код-индекс
  buf_ko_mm[3]=podgr;//вставить код подгруппы
  vv=vibor(Skvo[vmv].E1_s);//получить код-индекс для конца первого полумаршрута
  if(vv!=9999)buf_ko_mm[6]=vv;//вставить код индекс
  buf_ko_mm[5]=podgr;//вставить код подгруппы
  buf_ko_mm[7]=124;//в свободные байты записать заполнитель
  buf_ko_mm[8]=124;
  buf_ko_mm[9]=check_sum(buf_ko_mm);//вставить контрольную сумму
  buf_ko_mm[0]='(';
  buf_ko_mm[10]=')';
  pooo[Skvo[vmv].B1_s]=biostime(0,0L);//зафиксировать время выдачи
  home(modi);//вернуть курсор "домой"
  flagoutmsg=11;//выставить флаг-требование на передачу команд в 2 стойки
//  TIMER_SOB(Skvo[vmv].B2_s,11,Skvo[vmv].B2_s);//запустить таймер
#endif
}
/*****************************************************************/
int vibor(int pot)
{
  //выбор кода команды для указания объекта, в зависимости от номера байта
  int nomer,n=0,SDVIG=0,FN=0,FIN=0,i11,j11;
#ifdef NALAD  
  nom_func("388");
#endif      
  if(DISK!=0)return(9999);
  n=pot;
  if(fr1[n][0]==2)
  {
    if(fr1[n][13]==1)//если объект в первой стойке ТУМС
    {
      BAM=ZAGO_MPSU(0x61);//получить заголовок
      SDVIG=STR1;//взять сдвиг на сигналы
      FN=0;FIN=SIG1;
    }
#ifdef KOL_SOO2
    else
    {
      BAM=ZAGO_MPSU(0x62);//если вторая стойка
      SDVIG=STR2;FN=SIG1;FIN=FN+SIG2;
    }
#endif
    nomer=9999;
    for (i11=FN;i11<FIN;i11++)//пройти по строкам сообщений
    for(j11=0;j11<=4;j11++)//пройти по объектам строки
    if (spsig[i11][j11]==n)//если нашли заданный объект
    {
      podgr=podgruppa[i11+SDVIG-FN];//получить код подгруппы
      nomer=j11;//получить номер байта
      break;//прервать цикл
    }
  }
  if((fr1[n][0]==3)||(fr1[n][0]==4))
  {
    if(fr1[n][13]==1)//если объект в первой стойке ТУМС
    {
      BAM=ZAGO_MPSU(0x61);//получить заголовок
      SDVIG=STR1+SIG1;//взять сдвиг на сигналы
      FN=0;FIN=UCH1;
    }
#ifdef KOL_SOO2
    else
    {
      BAM=ZAGO_MPSU(0x62);//если вторая стойка
      SDVIG=STR2+SIG2;FN=UCH1;FIN=FN+UCH2;
    }
#endif
    nomer=9999;
    for (i11=FN;i11<FIN;i11++)//пройти по строкам сообщений
    for(j11=0;j11<=4;j11++)//пройти по объектам строки
    if (spspu[i11][j11]==n)//если нашли заданный объект
    {
      podgr=podgruppa[i11+SDVIG-FN];//получить код подгруппы
      nomer=j11;//получить номер байта
      break;//прервать цикл
    }
  }

  if(nomer==9999) return(9999);//если объект не найден вернуть 999
  switch(nomer)//переключатель по номеру байта в строке
  {
    case 0:return(64); //код для байта №0 = @
    case 1:return(65); //код для байта №1 = A
    case 2:return(66); //код для байта №2 = B
    case 3:return(67); //код для байта №3 = C
    case 4:return(68); //код для байта №4 = D
    default:return(64);//код для неопределенного байта = @
   }
}
/**********************************************************/
int check_sum(unsigned char num[11])
{              /* складывает все байты по модулю 2 */
  unsigned char sum=0;
  int i22;
#ifdef NALAD  
  nom_func("18");
#endif  
  for(i22=1;i22<9;i22++)
  sum=sum^num[i22];
  sum=sum|0x40;
  return(sum);
}
//----------------------------------------------------
int form_kosig(int kod)
{ //процедура формирования команд раздельного управления для объектов
  //группы "сигнал"
  int nomer,podgr,i18,j18,SDVIG=0,FN=0,FIN=0,n=0;
#ifdef NALAD  
  nom_func("83");
#endif        
  if(DISK!=0)return;
  buf_ko[2]='E';//заполнить группу
  n=point;//зафиксировать объект выбранный оператором
  //если объект из первой стойки: заголовок,сдвиг и граница
  if(fr1[n][13]==1){buf_ko[1]=ZAGO_MPSU(0x61);SDVIG=STR1;FN=0;FIN=SIG1;}
#ifdef KOL_SOO2
  else//для второй стойки - аналогично
  { buf_ko[1]=ZAGO_MPSU(0x62);SDVIG=STR2;FN=SIG1;FIN=FN+SIG2;}
#endif
  nomer=9999;
  if((fr1[n][1]==16)&&(fr1[n][2]>=5)&&(fr1[n][2]<=8))//если РОН/РОЧ
  {
    buf_ko[1]=buf_ko[1]&3;
    buf_ko[1]=buf_ko[1]|0x50;
  }
  for (i18=FN;i18<FIN;i18++) //пройти по подгруппам
  for(j18=0;j18<=4;j18++) //пройти по объектам подгруппы
  if (spsig[i18][j18]==n) //если найден объект
  {
    podgr=podgruppa[i18+SDVIG-FN];//зафиксировать подгруппу
    nomer=j18; //зафиксировать порядковый номер объекта в подгруппе
    break;
  }
  if(nomer==9999) return(1); //если не найден объект - выйти
  buf_ko[3]=podgr; // заполнить подгруппу
  for (j18=0;j18<=4;j18++)
  if (j18==nomer) buf_ko[j18+4]=kod;//для найденного объекта - заполнить код
  else  buf_ko[j18+4]=124;// для прочих вписать заполнитель
  return(0);
}

//------------------------------------------------------------

int form_koda(int nob,int invr)
{
  int nobi=0;
#ifdef NALAD  
  nom_func("73");
#endif      
  if((fr1[nob][1]!=166)&&(fr1[nob][1]!=27))nobi=fr1[nob][11];
  else nobi=(fr1[nob][3]&0xf000)>>12;
  switch(nobi)
  {
    case 0: if(fr3[nob][nobi]==0)
            {
              if(invr==0)return('A');
              else return('M');
            }
            else
            {
              if(invr==0)return('M');
              else return('A');
            }
    case 1: if(fr3[nob][nobi]==0)
            {
              if(invr==0)return('B');
              else  return('N');
            }
            else
            {
              if(invr==0)return('N');
              else  return('B');
            }
   default: return(9999);
  }

}
//-----------------------------------------------------------
fotksig(int koda)
{ //процедура формирования команды открытия сигнала
  //в раздельном режиме и для передачи в резервную ПЭВМ
  int j;
#ifdef NALAD  
  nom_func("88");
#endif        
  if(DISK!=0)return;
  for(j=0;j<11;j++)buf_ko_p[j]=0;//очистка буфера команд
  ot=0;vkl_kno(0,8);
  if(form_kosig(koda)==1) return;//если неудачное формирование - выход
  buf_ko[9]=check_sum(buf_ko);//запись контрольной суммы
  pooo[point]=biostime(0,0L);//фиксация времени выдачи
  flagoutmsg=1;//установка требования для передачи в ТУМС
  if(manevro==1) manevro=0; //сброс маневрового признака
  for(j=0;j<11;j++)buf_ko_p[j]=buf_ko[j]; //перезапись в буфер обмена с ПЭВМ
  flms=1;//установка требования для передачи в резервную ПЭВМ
}
//------------------------------------------------------------
//функция определения номера объекта включенного в прием
//данных из стойки ТУМС для спаренной стрелки
int Opred()
{
  int iks,jks,lom,FN=0,FIN=0;
#ifdef NALAD
  nom_func("202");
#endif
  if(fr1[point][13]==1){FN=0;FIN=STR1;}
#ifdef KOL_SOO2
  else{FN=STR1;FIN=FN+STR2;}
#endif
  if(fr1[point][12]!=9999)
  {
    TEST=2;
    lom=poisk_ras(fr1[point][2],point);
  }
  for(iks=FN;iks<FIN;iks++)
    for(jks=0;jks<5;jks++)
      if(point==spstr[iks][jks])return(0);
      else
        if(spstr[iks][jks]==lom){point=lom;return(0);}
  return(-1);
}

