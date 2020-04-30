#include <graphics.h>
#include "bla.h"
#include <dos.h>
#include <alloc.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <bios.h>
add(int kk,unsigned char ob)
{
	unsigned char ZAPIS[35],nom[5];
	unsigned int ito;
#ifdef NALAD
	nom_func("1");
#endif
	if(DISK!=0)return;
	file_arc=open(NAME_FILE,O_APPEND|O_RDWR,O_BINARY);
	if(file_arc<0)
	{
		clscreen();moveto(10,100);setcolor(14);
		outtext("Нарушение файловой структуры при открытии,работа невозможна");
		getch();FINAL_();
	}
//	itoa(file_arc,nom,10);
//	setcolor(7);outtextxy(620,5,"███");
//	setcolor(15);outtextxy(620,5,nom);
	for(ito=0;ito<30;ito++)ZAPIS[ito]=0;
  strcpy(ZAPIS,TIME);
  strncat(ZAPIS,&ob,1);
  if((ob=='S')||(ob==175)||(ob==162)||(ob=='>')||(ob=='<')||(ob==0xF))
  {
    if(kk<2)
    {
      if(ob=='>')strncat(ZAPIS,buf_zap_disk,11);
      if(ob=='<')strncat(ZAPIS,buf_ko_p,11);
      if((ob!='>')&&(ob!='<'))strncat(ZAPIS,bu[kk],11);
    }
    if(kk==2)strcat(ZAPIS,BUF_COM_PVM);
    if(kk==3)strcat(ZAPIS,REG_COM);
    if(kk==4)strcat(ZAPIS,BUF_FR4);
    if(kk==5)strcat(ZAPIS,REG_FR4);
  }
  if(kk==10)strncat(ZAPIS,REG_COM,11);
  ZAPIS[strlen(ZAPIS)]=0xd;
  ZAPIS[strlen(ZAPIS)]=0;
  ito=write(file_arc,ZAPIS,strlen(ZAPIS));
	if(file_arc>0)ito=close(file_arc);
	else ito=0;
  if(ito!=0)
  {
    clscreen();
    moveto(10,100);
    setcolor(14);
    outtext("Нарушение файловой структуры при закрытии,работа невозможна");
		getch();
		FINAL_();
	}
	file_arc=0;
}
/***********************************************************/
out_time()
{
  char vre[10]="",chas[3]="",min[3]="";
#ifdef NALAD
  nom_func("213");
#endif
  if(help!=0)return;
  setlinestyle(0,0,0);setcolor(MAGENTA);rectangle(2,2,48,13);
  setfillstyle(SOLID_FILL,WHITE);bar(3,3,47,12);
  itoa(ho_ur,chas,10);
  itoa(mi_n,min,10);
  setcolor(MAGENTA);
  if(ho_ur<10){strcpy(vre,"0");strcat(vre,chas);}
  else strcpy(vre,chas);
  if(dv==0){strcat(vre,":");dv=1;}
  else {strcat(vre," ");dv=0;}
  if(mi_n<10)strcat(vre,"0");
  strcat(vre,min);
  outtextxy(4,4,vre);
}
//---------------------
read_t(int smena_t)
{
  char h_0,h_1,m_0,m_1,s_0,s_1;
  int hu;
	// #ifdef NALAD   nom_func("275"); #endif
	//процедура чтения текущего времени из таймера реального времени
	hu = ho_ur;
	rg.h.ah = 0x2c;
	int86(0x21,&rg,&rg);
	h_0 = rg.h.ch%10;
	h_1 = rg.h.ch/10;
	m_0 = rg.h.cl%10;
	m_1 = rg.h.cl/10;
	s_0 = rg.h.dh%10;
	s_1 = rg.h.dh/10;
	ho_ur = h_0 + h_1*10;
	mi_n = m_0 + m_1*10;
	se_c = s_0 + s_1*10;
	TIME[0] = 0x20;
	TIME[1] = h_1|0x30;
	TIME[2] = h_0|0x30;
	TIME[3] = 0x3a;
	TIME[4] = m_1|0x30;
	TIME[5] = m_0|0x30;
	TIME[6] = 0x3a;
	TIME[7] = s_1|0x30;
	TIME[8] = s_0|0x30;
	TIME[9] = 0x20;
	TIME[10] = 0;
}
//--------------------------------------------------------------
int test_time1(long const_)
{
	int i,j;
#ifdef NALAD  
	nom_func("355");
#endif    
	SEC_time=biostime(0,0l);
	if(labs(SEC_time-FIR_time)>const_)
	{
		if(SEC_time<=18l)
		{
			TIME_OUT_PVM=SEC_time;
			j=peek(0,0x470);
			if(j!=1)
			{
				rg.x.cx=yearr_;
				rg.h.dh=monn_;
				rg.h.dl=dayy_;
				rg.h.ah=0x2b;
				int86(0x21,&rg,&rg);
			}
		}
    if((SEC_time>=1572462)&&(SEC_time<=1572480))
    {

      FIR_time=SEC_time;
      second_time=SEC_time;
      first_time=SEC_time;
      dayy_++;
      if((monn_==1)||(monn_==3)||(monn_==5)||(monn_==7)||(monn_==8)||(monn_==10)||(monn_==12))
      {if(dayy_>31){dayy_=1;monn_++;if(monn_>12){monn_=1;yearr_++;}}}
        else
        if(monn_==4||monn_==6||monn_==9||monn_==11)
          {if(dayy_>30){dayy_=1;monn_++;}}
        else
          if(monn_==2)
          {
            if((yearr_%4)==0){if(dayy_>29){dayy_=1;monn_++;}}
            else  if(dayy_>28){dayy_=1;monn_++;}
          }
      dat.day=dayy_;
      dat.month=monn_;
      dat.year=yearr_;
      for(i=0;i<17;i++)NAME_FILE[i]=0;
      strcpy(NAME_FILE,"RESULT//");
      if(dayy_<10){NAME_FILE[8]=0x30;NAME_FILE[9]=dayy_|0x30;}
      else {NAME_FILE[8]=(dayy_/10)|0x30;NAME_FILE[9]=(dayy_%10)|0x30;}
      if(monn_<10){NAME_FILE[10]=0x30;NAME_FILE[11]=monn_|0x30;}
      else{NAME_FILE[10]=(monn_/10)|0x30;NAME_FILE[11]=(monn_%10)|0x30;}
      strcat(NAME_FILE,".ogo");
      NAME_FILE[16]=0;
			if(file_arc>0)close(file_arc);
			file_arc=0;
			file_arc=open(NAME_FILE,O_CREAT|O_TRUNC|O_APPEND|O_WRONLY,S_IREAD|S_IWRITE|O_BINARY);
			if(file_arc<0)
			{
				clscreen();moveto(100,100);setcolor(14);
				outtext("Нарушение файловой структуры,работа невозможна");
				getch();FINAL_();exit(1);
			}
			if(file_arc>0)close(file_arc);
			file_arc=0;
      FIR_time=SEC_time;
      return(0);
    }
    else
    {
      read_t(0);
      return(1);
    }
  }
  else return(0);
}
//--------------------------------------------------------
disco()
{
#ifdef NALAD  
  nom_func("36");
#endif    
  if(DISK==0)pointer=creat("result\\ogr.fr4",O_BINARY|S_IWRITE);
  else pointer=creat("disk\\ogr.fr4",O_BINARY|S_IWRITE);
  write(pointer,fr4,len);
	if(pointer>0)close(pointer);
	pointer=0;
}
//-----------------------------------------------
clscreen()
{
#ifdef NALAD  
  nom_func("26");
#endif  
  setfillstyle(1,7);
  bar(0,0,640,480);
}
//--------------------------------------------------------
zvuk_vkl(int tip1,int dlit1)
{
#ifdef NALAD  
  nom_func("439");
#endif       
  if((STATUS!=1)||(TELEUP!=1)||(DU==1)){nosound();return;}
  if(prorisovka==1)return;
  zvuk_sig.time_begin=biostime(0,0L);
  zvuk_sig.dlit=dlit1;
  zvuk_sig.tip=tip1;
  if(tip1!=3)sound(600);
  else sound(800);
}
//--------------------------------------------------
nom_func(char *txt)
{
//  if(atoi(txt)<100)return;
//  if((_doserrno==0)||(_doserrno==0x57))return;
  setcolor(7);
  if(Y_txt>0)outtextxy(25,Y_txt-10,"█");
  outtextxy(0,Y_txt,"███");
  setcolor(15);
  outtextxy(0,Y_txt,txt);outtextxy(25,Y_txt,"+");
  Y_txt=Y_txt+10;
  if(Y_txt==480)Y_txt=0;
}
