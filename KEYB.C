#include"bla.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>
#include<graphics.h>
#include<conio.h>
//------------------------------------------------
nachalo()
{
#ifdef NALAD  
  nom_func("179");
#endif   
  if(zabeg==0) zapretvybora=0;
  zagruzen();
 }
//-----------------------------------------
end_help()
{
#ifdef NALAD  
  nom_func("50");
#endif
  help=0;
  if (tst==2) uprav=1;
  else uprav=0;
  setfillstyle(1,7);
  bar(0,0,639,479);
  prorisovka=1;
  nachalo();
  prodol();
  prorisovka=0;
  return;
}
/**********************************/
home(int ii3)
{
  int coox,cooy;
#ifdef NALAD  
  nom_func("102");
#endif          
  if(DISK!=0)return;
  mouser=0;
  if(ii3==-1&&i3==-1) return;
  if(ii3==-1)goto a;
  coox=markery[ii3][4];cooy=markery[ii3][5];
  del_kursor(ii3);
a:
  setcolor(7);outtextxy(37,46,"█████████");
//putimage(65,35,ukazat,0);
  i3=-1;modi=-1;pat=-1;
}

//-----------------------------------------------------
show_kursor(int gde)
{ //gde-номер объека в markery - требуемое место для размещения маркера  
  //probel_left - номер символа в имени, где заканчиваются пробелы слева - число пробелов слева 
  //probel_right - номер символа в имени, с которого начинаются пробелы справа
  int i,j,xk,yk,D,lp,lp1,ele,probel_left,probel_right;
  char Imya[20],name[20];
#ifdef NALAD  
  nom_func("303");
#endif
  for(xk=0;xk<20;xk++){Imya[xk]=0;name[xk]=0;}
  //получить координаты экрана для объекта, куда выполняется перенос маркера
  xk=markery[gde][4];yk=markery[gde][5];
#ifdef MOUSE
  if(MOUSE_ON!=0)
  {
    for(i=0;i<mouse_all;i++)if(mouse_mark[i][0]==gde)break;
    if(i<mouse_all)
    { regs.x.ax=4;
      regs.x.cx=mouse_mark[i][1];
      regs.x.dx=mouse_mark[i][2];
      int86(0x33,&regs,&regs);
      X_m=mouse_mark[i][1];Y_m=mouse_mark[i][2];
fin:  regs.x.ax=4;
      regs.x.cx=X_m;
       regs.x.dx=Y_m;
       int86(0x33,&regs,&regs);
    }
  }
#endif
  if(markery[gde][7]==5)//если путь
  { ele=markery[gde][6];
    probel_left=strcspn(pako[ele]," ");//символ пробела слева
    probel_right=strspn(pako[ele]," ");//символ пробела справа
    D=strlen(pako[ele])-probel_left-probel_right;
    if(probel_left<probel_right)//пробелы слева
    {probel_left=probel_right-probel_left;probel_right=0;}
    else
    { if(probel_left>probel_right)
      { if(strlen(pako[ele])-probel_left+probel_right==0)
        {probel_left=0;probel_right=0;}
        else
        if(strlen(pako[ele])-probel_left+probel_right>0)
        {probel_right=0;probel_left=0;}
      }
    }
    // скорректировать координату на величину пробелов
    xk=xk+(probel_left-probel_right)*7;
  }
//----------------------------------------------------------
// если это стрелка, СП, УП, сигнал, путь или смена направления
  if(markery[gde][7]<=6)
  { if(markery[gde][7]==1)// если стрелка 
    {
      D=strlen(pako[markery[gde][6]]);// получить длину имени 
      lp=0;
      while(pako[markery[gde][6]][lp]!=':')lp++;//пройти до двоеточия 
      lp++;
      for(lp1=0;lp1<20;lp1++)Imya[lp1]=0;
      lp1=0;
      while(lp<D)
      { Imya[lp1]=pako[markery[gde][6]][lp];//прочитать от двоеточия 
        lp++;lp1++;
      }
      D=strlen(Imya);// получить новую длину  имени 
    }
    else
    // если не стрелка 
    { strcpy(Imya,pako[markery[gde][6]]);
      j=0;
      for(i=0;i<20;i++)
      if(Imya[i]!=32){Imya[j]=Imya[i];j++;}
      D=strlen(Imya);
    }
    if(markery[gde][7]!=6)// если это не смена направления 
    { get_p(xk-1,yk-1,D); //взять по-пиксельное значение от xk-1, yk-1 до конца строки в D символов
      setfillstyle(1,1);bar(xk-1,yk-1,xk+D*7-1,yk+7);
    }
    if(markery[gde][7]==1)// если это стрелка 
    { D=markery[gde][6];
      if(fr3[D][5]==1)setcolor(LIGHTCYAN);//для отсутствия достоверной информации
      else
      if(fr3[D][0]==fr3[D][1]) setcolor(12);// если есть потеря контроля - красный цвет
      else
        if(fr3[D][0]==1&&fr3[D][1]==0) setcolor(LIGHTGREEN);// если стрелка в плюсе - зеленый
        else setcolor(YELLOW);// иначе - желтый
    }
    else
    //-----------------------------------------------------------------------------------------
    if(markery[gde][7]==6)// если смена направления 
    { // разместить курсор на новом месте 
      setlinestyle(0,0,0);setcolor(15);
      rectangle(xk-28,yk-6,xk+28,yk+6);
      rectangle(xk-29,yk-7,xk+29,yk+7);
    }
    //если не смена направления-------------------------------
    else
      if((markery[gde][7]==4)||(markery[gde][7]==5))// если участок пути или путь
      {
        D=markery[gde][6];// получить номер объекта для основной базы
        if(fr4[D][2]==1) setcolor(LIGHTRED);// если закрыт для движения
        else setcolor(15);
      }
      // если не участок пути и не путь
      else setcolor(15); //то цвет белый 
        if(markery[gde][7]!=6)/* если не смена направления */
        {
          //settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
          outtextxy(xk,yk,Imya);/* вывести имя */
        }
  }
  else // если это особый экранный объект
  { //если вариантная кнопка или вспомогательная смена направления
    if((markery[gde][7]>=7)&&(markery[gde][7]<=9))
    { setlinestyle(0,0,0);setcolor(15);
      rectangle(xk-5,yk-5,xk+5,yk+5);rectangle(xk-6,yk-6,xk+6,yk+6);
    }
    if(markery[gde][7]>7)
    {
      if(markery[gde][6]!=9999)strcpy(Imya,pako[markery[gde][6]]);
      if(gde==MAKET)// если макет
      { setlinestyle(0,0,0); setcolor(15);
        rectangle(xk-22,yk-6,xk+22,yk+6);
        rectangle(xk-23,yk-7,xk+23,yk+7);
      }
      else
      //если курсор к переключателю комплектов ТУМС 1 или 2
      if((gde==VN1)
#ifdef KOL_SOO2
         ||(gde==VN2)
#endif
      )
      { // изобразить курсор
        setlinestyle(0,0,0); setcolor(15);
        rectangle(xk-10,yk-4,xk+10,yk+4);
      }
      else
      { setlinestyle(0,0,0); setcolor(15);
        rectangle(xk-5,yk-5,xk+5,yk+5);
        rectangle(xk-6,yk-6,xk+6,yk+6);
      }
    }
  }
  setcolor(7);outtextxy(37,46,"██████████");
  if(gde!=-1)
  { if(markery[gde][7]==1)
    {strcpy(name,"СТ");strcat(name,Imya);strcpy(Imya,name);}
    else
    if(markery[gde][7]<100)
    { strcpy(name,Imya);
      if(strlen(name)==0&&gde!=VN1
#ifdef KOL_SOO2
      &&gde!=VN2
#endif
      )
      if(markery[gde][6]>kol_OSN)
      { get_str(markery[gde][6]);
        strcpy(name,chudo);
      }
      else strcpy(name,pako[markery[gde][6]]);
    }
    setcolor(15);xk=strlen(name);
    if(markery[gde][6]!=9999)outtextxy(77-xk*4,46,name);
  }
}
//----------------------------------------------
get_p(int xa,int ya,int DD)
{
  int bi,bj;
#ifdef NALAD  
  nom_func("98");
#endif         
  if(Fla_no_pp==1) return;
  for(bj=0;bj<9;bj++)for(bi=0;bi<DD*7+1;bi++)
  kadr[bj][bi]=getpixel(xa+bi,ya+bj);
  for(bj=0;bj<9;bj++)for(bi=DD*7+1;bi<50;bi++)kadr[bj][bi]=0;
}
/***********************************************/
put_p(int xa,int ya,int DD)
{
  int bi,bj;
#ifdef NALAD  
  nom_func("256");
#endif          
  for(bj=0;bj<9;bj++)for(bi=0;bi<DD*7+1;bi++)
  putpixel(xa+bi,ya+bj,kadr[bj][bi]);
}
//----------------------------------
ukazka()
{
#ifdef NALAD  
  nom_func("381");
#endif    
     setcolor(4);outtext(" <<<");
}
//------------------------------------
read_passw()
{
  unsigned long tt,tt1;
  int aaq=0,a,col;
#ifdef NALAD  
  nom_func("270");
#endif          
  aaq=klaval;
  if(aaq==0)
  {
    getch();
fin:
    w(119,999,"");//НЕПРАВИЛЬНО НАБРАН ПАРОЛЬ
    zvuk_vkl(1,18);
    flag_paro=0;
    schet=0;
    strcpy(password,"");
    return;
  }
  else
  {
    if(schet>6)return;
    else
    {
      password[schet]=aaq;schet++;
      if(schet==6)
      {
#ifndef DEMONSTR
        if((strcmp(password,SLOVO)==0)&&(flag_paro<4))
#else
        if((strcmp(password,SLOVO1)==0)&&(flag_paro<4))
#endif
        { klaval=55;
          if(flag_paro==1)
          {
            bil_bil=0;
            iqw=90;
            read_neisprav();
            nikuda=1;
            klaval=-1;
          }
          else
            if(flag_paro==2)
            {
              bil_bil=0;
              iqw=226;
              card();
              klo=1;
              klaval=-1;
            }
            else
              if((flag_paro==3)&&(DISK==0)){flag_paro=0;set_timers();timer_set=15;}
          schet=0;strcpy(password,"");flag_paro=0;return;
        }
        else
        if((strcmp(password,"262793")==0)&&(flag_paro==4))
        {
          inportb(0x43);
          FINAL_();
          closegraph();
          exit(0);
        }
        else goto fin;
      }
    }
    return;
  }
}
//---------------------------------------------------------
finish_strelok()
{
#ifdef NALAD  
  nom_func("61");
#endif  
  vspz=0;avap=0;vib_ma=0;vibeg=0;vih_vopr=0;osya=0;
  first_col=0;AVARI=0;maket=0;net_kontro=0;ot=0;
  vkl_kno(VSPZ,8);
  vkl_kno(MAKET,8);
  vkl_kno(AViA,8);
  zapretvybora=0;
}
//-------------------------------------------------------
FINAL_()
{
#ifdef NALAD  
  nom_func("57");
#endif  
     ochistka();
     finish_startMM();
#ifdef WORK
     reset_int_vect();
#endif
#ifdef MOUSE
     if(MOUSE_ON!=0)clear_mouse();
#endif
//     closegraph();
     if(file_soob>0)close(file_soob);
     file_soob=0;
     if(BAZA>0)close(BAZA);
     BAZA=0;
     nosound();
}
//-----------------------------------------------------
int menu1
()
//Программа вывода на экран необходимого меню для выбора необходимого решения
//menu_N - номер варианта меню
// 1 - отмена/поездной/маневровый (маршрут или сигнал)
// 2 - отмена/стрелку в +/ стрелку в -)
// 3 - отмена/выключить(включить)управление/закрыть(открыть) движение
// 4 - отмена/включить запрет монтерам/отключить оповещение
// 5 - отмена/конец маршрута/вариантная точка
// 6 - отправлен четный(нечетный) ХП /не было четного(нечетного) ХП
{
  unsigned char punkt1[60],punkt2[60],punkt3[60];
  int pnkt1,pnkt2,pnkt3,strelka,i,j;
  long bb;
#ifdef NALAD  
  nom_func("169");
#endif         
  if(DISK!=0)return;
  pnkt1=220;
  perezap=2;
  mouser=0;
  if((punkt_N==old_punkt)&&(klaval!=13))return;
  old_punkt=punkt_N;
  switch(menu_N)
  {
    case 1: if(fr1[point][6]==2)pnkt2=56;//поездной-маневровый
            else
            {
              if(fr1[point][6]==3)pnkt2=46;
              else
              {
                t(0);
                sbros_all();
                return;
              }
            }
            pnkt3=57;break;
    case 2: pnkt2=63;pnkt3=64;break;// стрелку в плюс-стрелку в минус
    case 3: strelka=markery[i3][6]; // выключить из управления/закрыть движения
            if((fr4[strelka][0]&1)==0)pnkt2=59;
            else pnkt2=61;
            if(fr4[strelka][2]==0)pnkt3=60;
            else pnkt3=62;
            break;
    case 4: pnkt2=163;pnkt3=37;break;//включить запрет монтерам-отключить оповещение
    case 5: pnkt2=221;pnkt3=222;break;//конец маршрута- вариантная точка
    case 6: if(hoz_poezd[0]==2){pnkt1=223;pnkt2=225;pnkt3=-1;break;}
            if(hoz_poezd[1]==2){pnkt1=224;pnkt2=226;pnkt3=-1;break;}
    default: return;
  }
  if((pnkt1>229)||(pnkt2>229))
  bb=pnkt1;
  bb=lseek(file_soob,63L*pnkt1,0L);
  read(file_soob,&soob.lex,60);
  for(i=0;i<60;i++)soob.lex[i]=~soob.lex[i];
  while(soob.lex[i]==0x20){soob.lex[i]=0;i--;}
  strcpy(punkt1,soob.lex);
  bb=lseek(file_soob,63L*pnkt2,0L);
  read(file_soob,&soob.lex,60);
  for(i=0;i<60;i++)soob.lex[i]=~soob.lex[i];
  while(soob.lex[i]==0x20){soob.lex[i]=0;i--;}
  strcpy(punkt2,soob.lex);
  if(pnkt3!=-1)
  {
    bb=lseek(file_soob,63L*pnkt3,0L);
    read(file_soob,&soob.lex,60);
    for(i=0;i<60;i++)soob.lex[i]=~soob.lex[i];
    while(soob.lex[i]==0x20){soob.lex[i]=0;i--;}
    strcpy(punkt3,soob.lex);
  }
  if((punkt_N==3)&&(pnkt3==-1))punkt_N=2;
  i=max(strlen(punkt1),strlen(punkt2));
  if(pnkt3!=-1)i=max(i,strlen(punkt3));
  if(punkt_N==1)setfillstyle(1,10);
  else setfillstyle(1,2);
  setcolor(15);
  bar(600-i*8,1,639,10);
  moveto(607-i*8,2);outtext(punkt1);
  if(punkt_N==1)outtext(" <<<");
  if(punkt_N==2)setfillstyle(1,10);
  else setfillstyle(1,2);
  setcolor(15);
  bar(600-i*8,11,639,20);
  moveto(607-i*8,12);outtext(punkt2);
  if(punkt_N==2)outtext(" <<<");
  if(pnkt3!=-1)
  {
    if(punkt_N>3)punkt_N=3;
    if(punkt_N==3)setfillstyle(1,10);
    else setfillstyle(1,2);
    setcolor(15);
    bar(600-i*8,21,639,30);
    moveto(607-i*8,22);outtext(punkt3);
    if(punkt_N==3)outtext(" <<<");
  }
#ifdef MOUSE
  if(MOUSE_ON!=0)
  {
    if((X_m>607-i*8)&&(Y_m<26))
    {
      clear_mouse();
      regs.x.ax=7;//задать границы для мыши по горизонтали
      regs.x.cx=607-i*8;
      regs.x.dx=630;
      int86(0x33,&regs,&regs);
      regs.x.ax=8;//задать границы для мыши по вертикали
      regs.x.cx=5;
      regs.x.dx=26;
      int86(0x33,&regs,&regs);
    }
  }
#endif
  if(klaval==13)//если нажата ENTER
  {
#ifdef MOUSE
    if(MOUSE_ON!=0)
    {
//    clear_mouse();
//    mem_mous_fon();
//for(i=0;i<12;i++)line_old_gor_kurs[i]=0;
//	for(i=0;i<40;i++)line_old_vert_kurs[i]=0;
      regs.x.ax=7;//задать границы для мыши по горизонтали
      regs.x.cx=X_MIN;
      regs.x.dx=X_MAX;
      int86(0x33,&regs,&regs);
      regs.x.ax=8;//задать границы для мыши по вертикали
      regs.x.cx=Y_MIN;
      regs.x.dx=Y_MAX;
      int86(0x33,&regs,&regs);
      if(punkt_N==1)
      {
        home(i3);
        punkt_N=0;menu_N=0;sbros_all();t(0);
        for(i=0;i<12;i++)line_old_gor_kurs[i]=0;
        for(i=0;i<40;i++)line_old_vert_kurs[i]=0;
        return;
      }
    }
#endif
    switch(menu_N)
    {
      case 1: //поездной/маневровый/два белых
              {
                if((uprav==1)&&(ot==0))
                {
                  if(punkt_N==2)mane=0;//поездной
                  if(punkt_N==3)mane=1;//маневровый
                  vozvr=2;
                  poka=1;
                  koni();
                  nach_marsh=end_marsh;
                  menu_N=0;
                  punkt_N=0;
                  return;
                }
                else
                {
                  if(punkt_N==2)mane=0;//поездной
                  if(punkt_N==3)mane=1;//маневровый
                  puti=1;
                  zapretvybora=1;
                  otkrs();//выполнить процедуру открытия/закрытия выбранного сигнала
                  vrem=0;
                  menu_N=0;
                  punkt_N=0;
                  klaval=-1;
                  return;
                }
              }
      case 2: //стрелку в плюс/минус
              {
                if(punkt_N==2)//если перевод в плюс
                {
                  if(vib_ma==1)oper='E';//если стрелка на макете
                  else oper='A';
                  net_kontro=2;
                  perstr();
                  menu_N=0;
                  punkt_N=0;
                  return;
                }
                if(punkt_N==3)//если перевод в минус
                {
                  if(vib_ma==1)oper='F';
                  else oper='B';
                  net_kontro=2;
                  perstr();
                  menu_N=0;
                  punkt_N=0;
                  return;
                }
                break;
              }
      case 3: //включить(отключить)управление/закрыть(открыть)движение
              {
                point=markery[i3][6];
                del_kursor(i3);
                home(modi);
                modi=-1;
                old_modi=-1;
                old_punkt=-1;
                i3=-1;
                pat=-1;
                otkl(point);
                menu_N=0;
                punkt_N=0;
                sbros_all();
#ifdef MOUSE
                if(MOUSE_ON!=0){mouse_init(); mem_mous_fon();}
#endif
                return;
              }
      case 4: //включить запрет монтерам/выключить оповещение
              {
                //если включить запрет монтерам или отключить оповещение
                if(punkt_N==2)
                {
                  t(0);
                  opoveshe(markery[modi][6],1);
                }
                if(punkt_N==3)
                {
                  t(0);
                  opoveshe(markery[modi][6],2);
                }
                menu_N=0;
                punkt_N=0;
#ifdef MOUSE
                if(MOUSE_ON!=0){mouse_init(); mem_mous_fon();}
#endif
                return;
              }
      case 5: //конец маршрута/вариантная точка
              {
                Zdem_vibor_marshruta=0;
                switch(punkt_N)//переключатель по выбранному пункту
                {
                  case 3:  //выбран вариантный маршрут
                    nach0_marsh=markery[i3][6];//nach_marsh=end_marsh;end_marsh=0;
                    if(fr1[nach0_marsh][1]==7)//если вариантная точка
                    nach0_marsh=fr1[nach0_marsh][2];
                    vopros(1,9999,148,""); //ПРОДОЛЖАЙТЕ НАБОР МАРШРУТА
                    End_vara=2;vozvr=2;
                    Zdem_vibor_marshruta=0;

                    menu_N=0;
                    return;
                  case 2: // выбран пункт "конец маршрута"
                    END=find_end();
                    TEST=0;
                    i=may_be(nach_marsh,fr1[nach_marsh][1]);
                    j=prov_avail();
                    if((i!=0)||(j==1))    //если ошибка в выборе конца
                    {
pl:                   w(134,999,"");//ТОЧКА КОНЦА МАРШРУТА УКАЗАНА НЕВЕРНО
                      home(modi);
                      whole_finish();
                      menu_N=0;
                      for(ukaz_trass=0;ukaz_trass<100;ukaz_trass++)trassa[ukaz_trass]=0xFFFF;
                      klaval=-1;
                      vozvr=0;poka=0; me_uk=0; End_vara=0;
                      menu_N=0;
                      return;
                    }
                    End_vara=1;
                    if(test_mp()==1){End_vara=0;goto pl;}
/*                    for(ukaz_trass=0;ukaz_trass<100;ukaz_trass++)
                    {
                      trassa[ukaz_trass]=trassa_osn[ukaz_trass];
                      trassa_osn[ukaz_trass]=0xffff;
                    }*/
                    ukaz_trass=0;
                    while(trassa[ukaz_trass]!=0xFFFF)//пройти по всем элементам найденного маршрута
                    {
                      if(fr1[trassa[ukaz_trass]][0]==1)plus_minus();//для стрелок установить признаки желаемого положения
                      fr3[trassa[ukaz_trass]][10]=fr3[trassa[ukaz_trass]][10]|1;
                      if(test_elem(trassa[ukaz_trass]&0x7fff,0)==1)
                      {
                        finish_startMM();
                        home(modi);
                        whole_finish();
                        klaval=-1;
                        vozvr=0;poka=0; me_uk=0; End_vara=0;
                        menu_N=0;
                        return;
                      }
                      ukaz_trass++;
                    }
                    ris_trassa();//изобразить трассу на экране
                    voper();// задание вопроса для подтверждения
                    vozvr=1;poka=0; me_uk=0; End_vara=0;
                    menu_N=0;
                    return;
                default:  return;
                }
                if(punkt_N==3)nach0_marsh=markery[i3][6];
                if(prov_avail()==1)
                {
                  w(134,999,"");
                  soob_for_oper=1;
                  sbros=1;
                  home(modi);
                  whole_finish();
                  return;
                }
                if(punkt_N==2)
                {
                  t(0);
                  voper();
                  klaval=-1;
                  vih_vopr=5;
                  return;
                }
              }
      case 6: //отправлен четный(нечетный)/не было четного(нечетного) ХП
              {
                break;
              }
    default:  break;
    }
    t(0);menu_N=0;return;
  }
}
//---------------------------------------
WIN_MAIN()
{
  int a,col,objk,strlk;
#ifdef NALAD  
  nom_func("416");
#endif        
  if(DISK!=0)return;
  if(klaval==0)
  {
    klaval=getch();
    if((zapretvybora==0)&&(STATUS==1)&&(DU!=1)&&(TELEUP==1))
    {
      if(((markery[i3][7]&0xf000)==0x1000)&&(otv_kom==0))i3=2;
      if((i3==-1)&&(otv_kom==1))i3=Ok;
      if((i3==-1)&&(otv_kom==0))i3=2;
      switch(klaval)
      {
        case 72: i3=markery[i3][1];break;
        case 80: i3=markery[i3][3];break;
        case 77: i3=markery[i3][2];break;
        case 75: i3=markery[i3][0];break;
        default: goto Metka_A;
      }
met1: klaval=-1;
      if(i3==modi)return;
      del_kursor(modi);
      show_kursor(i3);
      pat=i3;modi=i3;return;
    }
#ifdef WORK
    else if(zapretvybora==1)return;
#endif
Metka_A:
    if(PRIEM_FR4==1)return;
    ot=0;vspz=0;maket=0;avap=0;
    switch(klaval)
    {
      case 59:  if((STATUS!=1)||(DU==1)||(TELEUP==0))return;//F1 - марш/раздельный
                del_kursor(pat);
                sbros_all();
                if(uprav==0)
                {
                  uprav=1;i3=2;tst=2;
                  vkl_kno(1,8);vkl_kno(2,10);
                }
                else
                {
RAZD:             uprav=0;tst=0;i3=1;
                  vkl_kno(2,8);vkl_kno(1,10);
                  t(0);
                  sbros_all();
                }
                //show_kursor(i3);
                pat=i3;
                return;
      case 60:  if(DU==1)return;
                sbros_all();
								set_timers();
								timer_set=15;
								return;//F2 - время
      case 61:  if((DU==1)||(STATUS==1))return;
                if(help!=0)help=0;
                else help=1;
                vio_vi();
                return;
      case 62:  nosound();zapretvybora=0;return;//F4
      case 63:  if(STATUS==1)end_help();//F5
                else
                {
                  sbros_all();
                  flag_paro=1;
                  strcpy(password,"");
                  w(118,999,"");
                }
                return;
      case 64:  if(STATUS==1)return;//F6
                else
                {
                  sbros_all();
                  flag_paro=2;
                  strcpy(password,"");
                  w(118,999,"");
                  return;
                }
      case 67:  if(podsvetka==0)podsvetka=1;
                else podsvetka=0;
                pict_podsvetka();
                return;

      case 68:  //F10
#ifdef WORK
                if(STATUS==1)
                {
                  zvuk_vkl(1,20l);
                  w(165,999,"");
                  return;
                }
#endif
                inportb(0x43);
                FINAL_();
                DISK=0xF;
                return;
      case 79:  //end
#ifdef WORK
                if(STATUS==1)
                {
                  zvuk_vkl(1,20l);
                  w(165,999,"");
                  return;
                }
                sbros_all();
                flag_paro=4;
                strcpy(password,"");
                w(118,999,"");
                return;
#else
                sbros_all();
                FINAL_();
                closegraph();
                exit(0);
#endif
/*      case 133: if((STATUS==1)&&(OTLADKA==1))
                {
                  TEST_KANAL=1;
                  cleardevice();
                  setcolor(8);
                  outtextxy(20,190,"БУФЕР ВВОДА СТОЙКИ УВК-1");
                  outtextxy(20,210,"БУФЕР ВВОДА СТОЙКИ УВК-2");
                  outtextxy(20,230,"БУФЕР ВЫВОДА СТОЙКИ УВК-1");
                  outtextxy(20,250,"БУФЕР ВЫВОДА СТОЙКИ УВК-2");
                  outtextxy(20,270,"БУФЕР ВЫВОДА ДЦ");
                  outtextxy(20,290,"БУФЕР ВВОДА ДЦ");
                  outtextxy(20,Y_kan[0]-10,"ДАННЫЕ ПРИНЯТЫЕ ПО КАНАЛУ УВК-1");
                  outtextxy(20,Y_kan[1]-10,"ДАННЫЕ ПРИНЯТЫЕ ПО КАНАЛУ УВК-2");
                }
                return;
      case 134: if(STOP==0)STOP=1;
                else STOP=0;
                return;*/
#ifndef WORK
      case 71:
#ifdef DEMONSTR
              if(STAT==0)
              {
                STAT=1;
                STATUS=1;
                menu();
              }  
              else 
              {
                STAT=0;
                STATUS=0;
                menu();
              }  
              home(modi);
              return;
#endif

                vvod_set=15;return;//Home - прямой ввод данных
#endif
      default: return;
    }
  }
  else
  switch(klaval)
  {
#ifndef WORK
    case 113:if(MODE_KN==1) //'q'
             {
              if(otv_kom==1)otv_kom=0;
              else otv_kom=1;
              knopka_OK();
              return;
             }
#endif
    case 27: home(modi);show_kursor(-1);
    case 32: sbros_all();nosound();t(0);return;
    case 9:  if((otv_kom==1)||(DU==1))return;
             if(STATUS==1)Zona_k();
             return;
    case 13: if(((markery[i3][7]&0xf000)==0x1000)&&//кнопка для ответств.ком.
             (otv_kom==0))//а режим отв.ком не установлен
             {
              w(266,999,"");
              soob_for_oper=1;
              klaval=-1;
              return;
             }
             if(((markery[i3][7]&0xf000)!=0x1000)&&//кнопка для ответств.ком.
             (otv_kom==1))//а режим отв.ком не установлен
             {
              if(i3!=-1)
							{
								w(267,999,"");
              	soob_for_oper=1;
              }
              klaval=-1;
              return;
             }
             objk=markery[i3][6];
             point=objk;
             if(modi!=-1)modi=i3;
             else return;
             if((vspz==1)||(avap==1))
             {
              if(fr1[objk][0]!=1)
              {
                w(17,999,"!");
                soob_for_oper=1;
                return;
              }
             }
             if(vozvr==2)
             {
              if((fr1[objk][0]!=2)||((fr1[objk][2]>1)&&(fr1[objk][1]!=7)))
              {
                w(134,999,"!");
                soob_for_oper=1;
                home(i3);
                old_modi=-1;
                klaval=-1;
                vozvr=0;
                whole_finish();
                return;
              }
             }
             if(((markery[i3][7]&0xfff)>=10)&&((markery[i3][7]&0xfff)<100)&&(zalet==0))
             {
               make_razdelka();
               return;
             }
             switch(markery[i3][7]&0xfff)
             {
               case 1:  if(avap==1)
                        {
                          avap=2;
                          AVARI=1;
                          perstr();
                          return;
                        }
                        if(maket==1)
                        {
                          del_kursor(MAKET);
                          del_kursor(i3);
                          modi=-1;
                          old_modi=-1;
                          i3=-1;
                          pat=-1;
                          home(i3);
                          maket=2;
                          v_o_ma(objk);
                          sbros_all();
#ifdef MOUSE
                          if(MOUSE_ON!=0){mouse_init();mem_mous_fon();}
#endif
                          return;
                        }
                        if(vspz==1)
                        { menu_N=3;
                          punkt_N=1;
                          klaval=-1;
                          regs.x.ax=4;//переместить курсор к меню
                          regs.x.cx=590;
                          regs.x.dx=50;
                          int86(0x33,&regs,&regs);
                          X_m=590;Y_m=50;
                          obnov_kur_mouse(590,50);
                          menu1();
                          return;
                        }
                        if((fr3[objk][0]==fr3[objk][1])&&(net_kontro!=2))
                        {
Metka_B:                  zapretvybora=0;
                          menu_N=2;
                          punkt_N=1;
                          klaval=-1;
                          regs.x.ax=4;//переместить курсор к меню
                          regs.x.cx=590;
                          regs.x.dx=50;
                          int86(0x33,&regs,&regs);
                          X_m=590;Y_m=50;
                          obnov_kur_mouse(590,50);
                          menu1();
                          return;
                        }
                        else
                        {
                          nomer=markery[modi][6];
                          if(uprav==1)poka=0;
                          perstr();
                          if(net_kontro==1)goto Metka_B;
                          else goto Metka_C;
                        }
               case 2:  make_signal();return;
               case 7:  make_signal();return;
               case 4:  make_put();return;
               case 5:  make_put();return;

               case 6:  make_smena();return;
#ifdef VSP
               case 8:  make_vspom_priem();return;
               case 9:  make_vspom_otpr();return;
#endif
#ifdef AVTOD
               case 777:
               case 778:make_avtod();return;
#endif
               case 100:make_gri();return;
               case 115:make_per_kompl();return;
               case 101:if(objk==9999)
                        {
                          switch(modi)
                          {
                            case 0:     if(ot==0)
                                        {
                                          ot=1;
                                          vkl_kno(0,10);
                                          danet=0;
                                        }
                                        modi=-1;
                                        vibeg=3;
                                        vopros(1,9999,129,"?");
                                        zapretvybora=0;
                                        vih_vopr=0;
                                        return;
                            case 1:     goto RAZD;
                            case 2:     uprav=1;
                                        tst=2;
                                        if(ot==1){t(0);vkl_kno(0,8);}
                                        vkl_kno(2,10);
                                        vkl_kno(1,8);
                                        //modi=-1;
                                        vopros(1,9999,122,"?");
                                        zapretvybora=0;
                                        vih_vopr=2;
                                        return;
                            case AViA:  if(uprav==1)
                                        {
                                          w(159,999,"");
                                          home(i3);
                                          return;
                                        }
                                        else
                                        {
                                          if((fr3[AVAch][AV_bch]==1)||
                                          (fr3[AVAn][AV_bn]==1))
                                          {
                                            w(164,999,"");
                                            home(i3);
                                            return;
                                          }
                                          poka=0;
                                          avap=1;
                                          vkl_kno(AViA,14);
                                          vopros(19,9999,120,"");
                                          return;
                                        }
                            case VSPZ:  poka=0;vspz=1;
                                        vkl_kno(VSPZ,10);
                                        vopros(2,9999,120,"");
                                        return;
                            case MAKET: poka=0;maket=1;
                                        strlk=strelka_v_makete();
                                        if(strlk==0)
                                        {
                                          if(fr3[KM1][BitKM]==1)
#ifdef KOL_SOO2
                                            if((fr3[KM1][BitKM]==1)&&(fr3[KM2][BitKM]==1))
#endif
                                            {
                                              vkl_kno(MAKET,10);
                                              vopros(2,9999,120,"");//укаж.стрелку
                                              vih_vopr=1;
                                              maket=1;
                                              klaval=-1;
                                            }
#ifdef KOL_SOO2
                                            else sbros_all();
#endif
                                          else sbros_all();
                                          return;
                                        }
                                        else
                                        {
                                          modi=str_Makst(strlk);
                                          vkl_otkl_maket(modi);
                                          zapretvybora=1;
                                          return;
                                        }
                          }
                        }
                        else
                        {
                          switch(fr1[markery[modi][6]][1])
                          {
                            case  27: poka=0;
                                      if(oppp==0)nok(markery[modi][6]);
                                      else 
                                      {
                                        if(fr1[markery[modi][6]][0]==2)noka(markery[modi][6]);
                                        else
                                          if(fr1[markery[modi][6]][0]==3)nokb(markery[modi][6]);
                                      }  
                                      return;
                            case 16:  make_knopka();return;
                            case 166: make_knpk2();return;
                            case 30:  make_neotv();return;
                            case 31:  make_otvetst();return;
                            case 38:  make_dn();return;
                            case 39:  make_nemarsh();return;
                            case 17:  make_opoveshenie();return;
                            default:  return;
                          }
                        }
               case 333: make_pereezd();return;
               default: return;
             }
    default: return;
  }
Metka_C:
  klaval=-1;
  return;
}
//-------------------------------------
keyboard()
{
  int j1,i;
#ifdef NALAD
  nom_func("118");
#endif
  if(DISK!=0)return;
  prorisovka=0;
  if(timer_set==15){set_timers();return;}
#ifndef WORK  
  if(vvod_set==15){set_vvod();return;}
#endif  
  if(help>0){klaval=getch();WIN_HELP();return;}
  if(flag_paro>0){klaval=getch();read_passw();return;}
  if(klo>0){WIN_CARD();return;}
  if(nikuda>0){WIN_NEISPRAV();return;}
#ifdef KANALS
  if(TEST_KANAL==1){WIN_KANAL();return;}
#endif
  if(zalet!=0){WIN_RAZD();return;}
  if(zapusk!=0){WIN_OTV();return;}
  klaval=getch();
  if(MODE_KN==1)
  {
    if(klaval=='q')
    {
      if(otv_kom==1)otv_kom=0;
      else otv_kom=1;
      knopka_OK();
      return;
    }
  }
  if((klaval==32)||(klaval==27))
  {
    okno_otkaz=0;
		t(0);
		if(AVARI==1)
		{
			AVARI=0;  avap=0;
			AVARIIN=0;
			sbros_time(AVAch,AV_bch);
			sbros_time(AVAn,AV_bn);
			vkl_kno(AViA,8);
			AV_zdem=0;
		}
#ifdef MOUSE
		if((MOUSE_ON!=0)&&(STATUS==1))
    {
      if((modi!=-1)&&((vih_vopr==0)||(otv_kom==0)))
      {
        for(i=0;i<4;i++){line_gor_kurs[4+2*i]=0xff;line_gor_kurs[5+2*i]=0xf8;}
        line_gor_kurs[0]=0xC;
        for(i=4;i<40;i++)line_vert_kurs[i]=0x80;
        line_vert_kurs[2]=8;
        regs.x.cx=markery[modi][4];//установить мышь в исходное положение
        regs.x.dx=markery[modi][5];
        regs.x.ax=4;
        int86(0x33,&regs,&regs);
      }
      menu_N=0;
      if(vozvr!=0)
      {
        home(i3);
        klaval=-1;
      }
    }
#endif
    sbros_all();
    if(klaval==27)
    {
      home(i3);
      clear_mouse();
      mouse_init();
      return;
    }
    if(help==0)goto m_win;
  }
  if(menu_N>0)
  {
    if(klaval==0)klaval=getch();
    if(klaval==72)
    {
      if(punkt_N==1)punkt_N=1;
      else punkt_N--;
    }
    if(klaval==80)punkt_N++;
    menu1();
    return;
  }
  if(timer_set>0){set_timers();return;}
  if(((vibeg>0)||(vozvr>0))&&(modi!=-1))WIN_VOPROS();
  else
  if((vih_vopr>0)||(danet>0))WIN_VOPROS();
  if((soob_for_oper>0)&&(osya==0)){WIN_SOOB();return;}
m_win:
  WIN_MAIN();
  return;
}
//--------------------------------------
WIN_SOOB()
{
  int i;
#ifdef NALAD  
  nom_func("420");
#endif          
  if(DISK!=0)return;
  soob_for_oper=0;
  if(sbros==1){sbros_all();sbros=0;t(0);}
  return;
//if(uprav==0)return;
//  else t(0);
}
//------------------------------------
WIN_VOPROS()
{
  int j1;
#ifdef NALAD  
  nom_func("421");
#endif          
  if(DISK!=0)return;
  if((klaval==32)||(klaval==27))
  {
    menu_N=0;
    sbros_all();
    return;
  }
  if(klaval==13)
  {
    if((markery[i3][6]!=9999)&&(i3!=-1))point=markery[i3][6];
    if((maket==1)&&(markery[i3][7]!=1)){w(17,999,"!");return;}
    if(maket==2)
    {
      v_o_ma(point);
      home(MAKET);
      del_kursor(modi);
      modi=-1;
      old_modi=-1;
      i3=-1;
      pat=-1;
      home(modi);
      maket=0;
      vih_vopr=0;
      sbros_all();
#ifdef MOUSE
      if(MOUSE_ON!=0){mouse_init();mem_mous_fon();}
#endif
    }
    if(vibeg==1){perstr();klaval=-1;}
    if(vibeg>1)
    {
      TEST=0;
			otkrs();
      home(i3);
      klaval=-1;
#ifdef MOUSE
      if(MOUSE_ON!=0)
      {
        for(j1=0;j1<12;j1++)line_old_gor_kurs[j1]=0;
        for(j1=0;j1<40;j1++)line_old_vert_kurs[j1]=0;
      }
#endif
      return;
    }
    if(vozvr==1)
    {
      vozvr=0;
      marsh2();
      soob_for_oper=1;
      klaval=-1;
      return;
    }
    if(gri==1)
    {
      w(19,999,"");//включаем выдержку времени
      gri_razd(i3);
      for(j1=0;j1<WAZO;j1++)was[j1]=0;
      gri=0;
      home(i3);
      klaval=-1;
#ifdef MOUSE
      if(MOUSE_ON!=0)
      {
        for(j1=0;j1<12;j1++)line_old_gor_kurs[j1]=0;
        for(j1=0;j1<40;j1++)line_old_vert_kurs[j1]=0;
      }
#endif
      vih_vopr=0;
      return;
    }
  }
}
//------------------------------------
#ifdef KANALS
WIN_KANAL()
{
  if(DISK!=0)return;
  klaval=getch();
  if(klaval!=0)return;
  else klaval=getch();
  if(klaval==133)
  {
    TEST_KANAL=0;
    end_help();
    sbros_all();
  }
  return;
}
#endif
//------------------------------------
WIN_HELP()
{
#ifdef NALAD  
  nom_func("415");
#endif        
  vio_vi();
}
//------------------------------------
WIN_NEISPRAV()
{
#ifdef NALAD  
  nom_func("417");
#endif        
  if(DISK!=0)return;
  klaval=getch();
  if(klaval!=0)return;
  else klaval=getch();
  switch(klaval)
  {
    case  63: nikuda=0;
              if(tst==2)uprav=1;
              else uprav=0;
              if(n_1>0)close(n_1);n_1=0;
              if(n_2>0)close(n_2);n_2=0;
              end_help();
              sbros_all();
              BEG_TIM[0]=0;
              return;
    case  81: bil_bil=1;
              iqw=56;
              read_neisprav();
              return;
    case 73:  bil_bil=2;
              iqw=56;
              read_neisprav();
              return;

    default:  return;
  }
}
//------------------------------------
WIN_CARD()
{
#ifdef NALAD
  nom_func("414");
#endif
  if(DISK!=0)return;
  klaval=getch();
  if(klaval!=0)return;
  else klaval=getch();
  switch(klaval)
  {
    case  64: klo=0;
              if(tst==2)uprav=1;
              else uprav=0;
              if(n_1>0)close(n_1);n_1=0;
              if(n_2>0)close(n_2);n_2=0;
              end_help();
              sbros_all();
              BEG_TIM[0]=0;
              return;
    case  81: bil_bil=1;
              iqw=226;
              card();
              return;
    case 73:  bil_bil=2;
              iqw=226;
              card();
              return;
    default:  return;
  }
}
//------------------------------------
//в программу входим при нажатии клавиш после активизации разделки,
//то есть при zalet==1
WIN_RAZD()
{
#ifdef NALAD
  nom_func("419");
#endif        
  //выдана предварительная, но не выполнена
  if(DISK!=0)return;
  klaval=getch();
  if(klaval==0)getch();
  if(klaval==32)
  {
    fr3[point][9]=0;
    zalet=0;
    sbros_all();
    return;
  }
  if(klaval!=13)return;
  if((fr3[point][9]==9)&&(fr3[point][0]==0))return;
  if(fr3[point][0]==0)//если предварительная не выдавалась
  {
    w(11,point,"");//ВЫДАНА ПРЕДВАРИТЕЛЬНАЯ КОМАНДА
    first_razd(i3);//выдать предварительную команду в ТУМС
    return;
  }
fin1:
  //если предварительная выдана и выполнена
  if(zalet==1&&fr3[point][0]==1&&vtora==1)
  {
    w(18,point,"");//ВЫДАНА КОМАНДА НА РАЗМЫКАНИЕ
    first_razd(i3);//выдать окончательную команду в ТУМС
    return;
  }
  else
  {
    zalet=0;
    was[markery[i3][7]-10]=0;
    fr3[point][9]=0;
    vtora=0;
    home(modi);
    return;
  }
}
//------------------------------------
WIN_OTV()
{
  int pred,isp,b_p,b_i,mark1,mark2;
#ifdef NALAD  
  nom_func("418");
#endif          
  if(DISK!=0)return;
  klaval=getch();
  if(klaval==0)getch();
  if(fr1[point][1]!=31)return;
  if(klaval==32){fr3[point][9]=0;zapusk=0; sbros_all(); return;}
  if(klaval!=13)return;
  pred=fr1[point][2]; isp=fr1[point][3];
  b_p=(fr1[point][4]&0xff00)>>8; b_i=fr1[point][4]&0xff;
  mark1=fr1[pred][7];mark2=fr1[pred][8];
  if((fr3[pred][b_p]==1)&&(zapusk==1))//если предварительная не выдавалась
  { w(11,point,"");//ВЫДАНА ПРЕДВАРИТЕЛЬНАЯ КОМАНДА
    form_first_kom(mark1);//выдать предварительную команду в ТУМС
    TIMER_SOB(pred,30,pred);
    zapusk++;
    return;
  }
fin1:
  //если предварительная выдана и выполнена
  if((zapusk==3)&&(fr3[pred][b_p]==0)&&(vtora==1))
  {
    sbros_time_tip(30);
    if(fr1[point][1]!=31)w(18,point,"");//ВЫДАНА КОМАНДА НА РАЗМЫКАНИЕ
    else w(fr1[point][6],999,"");
    form_first_kom(mark2);//выдать окончательную команду в ТУМС
    pooo[isp]=biostime(0,0);
    return;
  }
  else { zapusk=0;vtora=0;home(modi);return;}
}

//--------------------------------------------
sbros_all()
{
  int i,ijk;
#ifdef NALAD  
  nom_func("290");
#endif
	vspz=0;avap=0;vib_ma=0;vibeg=0;vih_vopr=0;osya=0;
	first_col=0;AVARI=0;maket=0;net_kontro=0;ot=0;vrem=0;
	zalet=0;vtora=0;zabeg=0;zapusk=0;
	puti=0;oppp=0;
	if(STATUS==1)
	{
		regs.x.ax=3; // получить информацию о координатах
		int86(0x33,&regs,&regs);
		X_m=regs.x.cx;
		Y_m=regs.x.dx;
		if(modi!=-1)
		{
			for(i=0;i<12;i++)line_old_gor_kurs[i]=0;
			for(i=0;i<40;i++)line_old_vert_kurs[i]=0;
		}
		move_mouse();
		old_modi=modi;
		modi_new=modi;
	}
	timer_set=0;
  menu_N=0;punkt_N=0;
  perezap=0;
  vkl_kno(VSPZ,8);vkl_kno(MAKET,8);vkl_kno(AViA,8);vkl_kno(0,8);
  zapretvybora=0;
  for(i=0;i<10;i++)BEDA[i]=0;
  Zdem_vibor_marshruta=0;
  finish_startMM();
  whole_finish();
  old_punkt=-1;
  zakr=0;
  sbros1=1;
  soob_for_oper=0;
  klaval=-1;
}
//------------------------------------------------------------
del_kursor(int gde)
{
  int xk,yk,D,lp,lp1,ele,i,j,probel_left,probel_right;
  char Imya[20]="";
#ifdef NALAD  
  nom_func("32");
#endif      
  for(xk=0;xk<20;xk++)Imya[xk]=0;
  if(gde!=-1)//если курсор не дома
  { xk=markery[gde][4];yk=markery[gde][5];
    if(markery[gde][7]<=6)
    { if(markery[gde][7]==1)// если стрелка 
      { D=strlen(pako[markery[gde][6]]);
        lp=0;
        while(pako[markery[gde][6]][lp]!=':') lp++;
        lp++;
        for(lp1=0;lp1<20;lp1++)Imya[lp1]=0;
        lp1=0;
        while(lp<D)
        { Imya[lp1]=pako[markery[gde][6]][lp];
          lp++;
          lp1++;
        }
        D=strlen(Imya);
      }
      else// если не стрелка 
      { if(markery[gde][7]==5)
        { ele=markery[gde][6];
          probel_left=strcspn(pako[ele]," ");//символ пробела слева 
          probel_right=strspn(pako[ele]," ");// символ пробела справа 
          if(probel_left<probel_right)// пробелы слева 
          {probel_left=probel_right-probel_left;probel_right=0;}
          else
          { if(probel_left>probel_right)
            { if(strlen(pako[ele])-probel_left+probel_right==0)
              {probel_left=0; probel_right=0;}
              else
              if(strlen(pako[ele])-probel_left+probel_right>0)
              {probel_right=0; probel_left=0;}
            }
          }
          xk=xk+(probel_left-probel_right)*7;//скорректировать координату на величину пробелов 
          strcpy(Imya,pako[markery[gde][6]]);
          j=0;
          for(i=0;i<20;i++)
          if(Imya[i]!=32){Imya[j]=Imya[i];j++;}
        }
        else strcpy(Imya,pako[markery[gde][6]]);//общий участок 
        D=strlen(Imya);
      }
      if(markery[gde][7]!=6)// не смена направления 
      { put_p(xk-1,yk-1,D);
        if(markery[gde][7]==2&&fr1[markery[gde][6]][11]!=9999)
        {setfillstyle(SOLID_FILL,cvv);bar(xk,yk,xk+D*7,yk+8);}
      }
      if(markery[gde][7]==1)// стрелка 
      { D=markery[gde][6];
        if(fr3[D][5]==1)setcolor(LIGHTCYAN);
        else
          if(fr3[D][0]==fr3[D][1]) setcolor(12);
          else
            if(fr3[D][0]==1&&fr3[D][1]==0) setcolor(LIGHTGREEN);
            else setcolor(YELLOW);
        //settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
        outtextxy(xk,yk,Imya);
      }
      else
      if(markery[gde][7]==2&&fr1[markery[gde][6]][11]!=9999)// сигнал
      { //settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
        setcolor(8); outtextxy(xk,yk,Imya);
      }
      else
      if((markery[gde][7]==4)||(markery[gde][7]==5))// путь или участок пути
      { D=markery[gde][6];
        if(fr4[D][2]==1) setcolor(LIGHTRED);
        else setcolor(8);
        //settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
        outtextxy(xk,yk,Imya);
      }
      else
      if(markery[gde][7]==6)// если смена направления 
      { setlinestyle(0,0,0); setcolor(7);
        rectangle(xk-28,yk-6,xk+28,yk+6);
        rectangle(xk-29,yk-7,xk+29,yk+7);
      }
    }
    else
    { if(markery[gde][7]>=7) // всякие кнопки 
      { if(gde==MAKET)
        { setlinestyle(0,0,0); setcolor(7);
          rectangle(xk-22,yk-6,xk+22,yk+6);
          rectangle(xk-23,yk-7,xk+23,yk+7);
        }
        else
          if((gde==VN1)
#ifdef KOL_SOO2
            ||(gde==VN2)
#endif
          )
          { setlinestyle(0,0,0);setcolor(7);
            rectangle(xk-10,yk-4,xk+10,yk+4);
            rectangle(xk-11,yk-5,xk+11,yk+5);
          }
          else
          { setlinestyle(0,0,0); setcolor(7);
            rectangle(xk-5,yk-5,xk+5,yk+5);
            rectangle(xk-6,yk-6,xk+6,yk+6);
          }
      }
    }
  }
//  else putimage(65,35,ukazat,1);
}
//---------------------------------------------------
#ifdef MOUSE
obnov_kur_mouse(int XX,int YY)
{
#ifdef NALAD  
  nom_func("189");
#endif 
  if(MOUSE_ON==0)return;
  setlinestyle(0,0,0);setcolor(15);//##
  X_m_old=XX;Y_m_old=YY;
  mem_mous_fon();//##
  line(XX-6,YY,XX+6,YY);line(XX,YY-4,XX,YY+4);//##
  getimage(XX-6,YY,XX+6,YY,line_gor_kurs);//##
  getimage(XX,YY-4,XX,YY+4,line_vert_kurs);//##
}
#endif
