#include <stdio.h>
#include "bla.h"
#include<dos.h>
#include <bios.h>
#include<graphics.h>
int findspu1(int ga,int tu)
{
  int shag,strelk_=0,perehod=0,up=0;
  if(tu>1){tu=tu-2;up=1;}

	nom_func("59");

  if(tu==0)shag=1;//если вход на стрелку четный
  else shag=-1; //если вход на стрелку нечетный
beg:
  ga=ga+shag;
  if(fr1[ga][0]==3)return(ga);//если вышли на СП - то дать его номер
  if((fr1[ga][0]==4)&&(up!=0))return(ga); //вышли на УП
  if((fr1[ga][0]!=1)&&(fr1[ga][0]<6))return(-1);
beg1:
  if(fr1[ga][0]==1)//если вышли на стрелку
  {
//    strelk_=1;
    if(perehod==1)
    {
      perehod=0;
      goto beg;
    }
		if((fr1[ga][7]==0)&&( shag==1))goto beg;//если вход на стрелку совпал с направлением
		if((fr1[ga][7]==1)&&( shag==-1))goto beg;
    else//если вход встречный
    {
      if(fr1[ga][1]==1)//если переход по плюсу - прямо
      {
        if(fr1[ga][4]==1)//если есть стык по плюсу
        {
          if(fr1[ga][5]==1)return(-1);//если есть стык по минусу
          else
          {
            strelk_=1;
            ga=fr1[ga][2];
            goto beg1;
          }
        }

      }
      else//переход по плюсу с отклонением 
      {
        if(fr1[ga][4]==1)//если есть стык по плюсу 
        {
          if(fr1[ga][5]==1)return(-1);//если есть стык по минусу
          else
          {
            strelk_=1;
            ga=fr1[ga][2];
            goto beg1;
          }
        }
        else
        {
          strelk_=1;
          ga=fr1[ga][2];
          goto beg1;
        }
      }
    }
  }
  if(fr1[ga][0]==6)//если вышли на переход
  {
    if((strelk_==1)||(perehod==1))//если пришли к переходу со стороны стрелки
    {
      strelk_=0;
      perehod=1;
      goto beg;
    }
    else
    {
      ga=fr1[ga][1];
      strelk_=0;
      perehod=1;
      goto beg1;
    }

  }
  else
  {
    strelk_=0;
    perehod=0;
    goto beg;
  }
}
//-----------------------------------------
void p_li(int nom)
{
  int gol=0,//переменная для радиуса "глаз" шлагбаума
  bit_iz,// номер бита для извещения
  bit_zak,//номер бита для закрытия переезда
  cvt_iz, //цвет для извещения
  cvt_zak,//цвет для закрытия
  l_p;//длина переезда
  
	nom_func("214");
    
  if((klo==1)||(help!=0)||(nikuda==1))return;
  l_p=fr1[nom][6];
  if(fr1[nom][2]!=9999)bit_iz=fr1[nom][2];
  else bit_iz=0xf;
  if(fr1[nom][3]!=9999)bit_zak=fr1[nom][3];
  else bit_zak=0xf;
  if(bit_iz!=0xf)
  {
    if(fr3[nom][bit_iz]==1)cvt_iz=14;
    else cvt_iz=8;
  }
  else cvt_iz=7;
  if(bit_zak!=0xf)
  {
    if(fr3[nom][bit_zak]==1){cvt_zak=12;cvt_iz=12;}
    else cvt_zak=7;
  }
  else cvt_zak=7;
  setfillstyle(1,cvt_zak);
  if(fr3[nom][5]==1)setfillstyle(1,11);
  bar(fr1[nom][4]-6,fr1[nom][5]-4,fr1[nom][4]+2,fr1[nom][5]-3);
  bar(fr1[nom][4]-6,fr1[nom][5]+l_p+3,fr1[nom][4]+2,fr1[nom][5]+l_p+4);
  if(fr3[nom][5]==1) setcolor(LIGHTCYAN);
  setcolor(8); setlinestyle(0,0,0);
  line(fr1[nom][4]-8,fr1[nom][5]-16,fr1[nom][4]-8,fr1[nom][5]-6);
  line(fr1[nom][4]-8-2,fr1[nom][5]-16,fr1[nom][4]-8+2,fr1[nom][5]-16);
  line(fr1[nom][4]-8-2,fr1[nom][5]-6-3,fr1[nom][4]-8+2,fr1[nom][5]-6-3);
  circle(fr1[nom][4]-8-2-3,fr1[nom][5]-6-3,3);
  circle(fr1[nom][4]-8+2+3,fr1[nom][5]-6-3,3);
  line(fr1[nom][4]+2,fr1[nom][5]+16+fr1[nom][6],fr1[nom][4]+2,fr1[nom][5]+6+fr1[nom][6]);
  line(fr1[nom][4]+2-2,fr1[nom][5]+16+fr1[nom][6],fr1[nom][4]+2+2,fr1[nom][5]+16+fr1[nom][6]);
  line(fr1[nom][4]+2-2,fr1[nom][5]+6+3+fr1[nom][6],fr1[nom][4]+2+2,fr1[nom][5]+6+3+fr1[nom][6]);
  circle(fr1[nom][4]+2-2-3,fr1[nom][5]+6+3+fr1[nom][6],3);
  circle(fr1[nom][4]+2+2+3,fr1[nom][5]+6+3+fr1[nom][6],3);
  setcolor(cvt_iz);
  if(fr3[nom][5]==1)setcolor(LIGHTCYAN);
  for(gol=0;gol<3;gol++)
  {
    circle(fr1[nom][4]-13,fr1[nom][5]-9,gol);
    circle(fr1[nom][4]-3,fr1[nom][5]-9,gol);
    circle(fr1[nom][4]-3,fr1[nom][5]+9+fr1[nom][6],gol);
    circle(fr1[nom][4]+7,fr1[nom][5]+9+fr1[nom][6],gol);
  }
}

//-----------------------------
picture()
{
  
	nom_func("222");
        
  pict1(1);
#ifdef KOL_SOO2
  pict1(2);
#endif
}
int pamjat;
/****************************/
void pict1(int WHO)//прорисовка объектов из стойки WHO
{
	int K,jt;
	int falsv;
	char bbb[15]="";

	nom_func("220");

	for(pamjat=0;pamjat<kol_VO;pamjat++)//проход по всем основным элементам
	{
		if((fr1[pamjat][13]==WHO)||(fr1[pamjat][13]>kol_OSN))//если объект не из другой стойки
		switch(fr1[pamjat][0])
		{
			case 5: if((fr1[pamjat][1]!=1)||(fr1[pamjat][2]!=1))//если путь
							{
								K=pamjat;
								displaypath(K,0);displaypath(K,1);displaypath(K,2);
								displaypath(K,3);displaypath(K,4);
							}
							break;
			case 1: K=pamjat; // если стрелка
							displaystrelka(K,0,0);//прорисовка стрелки К
							break;
			case 2: if(fr1[pamjat][2]<2)
							{
								displaysignal(pamjat,0);displaysignal(pamjat,2);
								displaysignal(pamjat,1);displaysignal(pamjat,3);
							}
							if(fr1[pamjat][8]==666)
							displaysignal(pamjat,0);//если смена направления
							break;
			case 4: displaypathuch(pamjat);//если участок пути
							break;
			case 3: if(fr1[pamjat][1]<2)//если СП
							{
								zap_matr(pamjat);cvet_matr();ris_sp_str();
							}
			default:	break;

		}
	}
	for(pamjat=kol_VO;pamjat<kol_VO;pamjat++)//проход по всем основным элементам
	{
		switch(fr1[pamjat][0])
		{
			case 1: K=pamjat; // если стрелка
							displaystrelka(K,0,0);//прорисовка стрелки К
							break;
			case 3: if(fr1[pamjat][1]<2)//если СП
							{
								zap_matr(pamjat);cvet_matr();ris_sp_str();
							}
			default:	break;

		}
	}

}
/*********************************************************/
#ifdef kol_STY
Styki()
{
  int i,j;
  
	nom_func("324");
          
  for(i=0;i<kol_STY;i++)
  {
      setlinestyle(0,0,0);setcolor(8);
      circle(styki[i][1],styki[i][2],3);
  }
}
#endif
//-------------------------------------------------------------
void kvadrat()
{
  
	nom_func("139");
 
  if(STATUS==2){setfillstyle(1,8);bar(10,45,32,50);}
  else
    if(STATUS==0){setfillstyle(1,14);bar(10,45,32,50);}
    else { setfillstyle(1,10); bar(10,45,32,50);}
	if(DSP_SHN == 0)
	{
		bar(4,44,42,51);
		moveto(4,44);
		outtext("арм_шн");
	}
	return;	
}
//---------------------------------------------------------
void whole_finish()
{
  
	nom_func("413");
        
   End_vara=0;
   mane=0;manevro=0;manevr=0;
   zapretvybora=0;first_col=0;povt1=0;povt2=0;poka=0;n_m=0;puti=0;
   vozvr=0;po_ma=0;END=0;
	 siv=0;osya=0;
   nach_marsh=end_marsh=half_marsh=nach0_marsh=0;
   ukaz_trass=0;
	 while(trassa[ukaz_trass]!=0xffff)
	 {
		 fr3[trassa[ukaz_trass]&0xfff][6]=0;
		 ukaz_trass++;
		 if(ukaz_trass>=100)break;
	 }
	 return;
}
//----------------------------------------------------------
int test_sost_(int ob)
{
  int ei,ej,KOKO;
  
	nom_func("352");
    
  for(ej=9;ej<=10;ej++)
  if(fr3[ob][ej]==1) return(1);
  return(0);
}
//----------------------------------------------------------
//seg006:0E70
int do_it(int puk,unsigned char bnf[11])
{ 
	int ccv1 = 0, yi;
	//seg006:0EA3 
	if(bnf[3]==D_kont[0][0]) //если получены данные по K1X - объед.групп
	{
		if(time_lu[puk] == 0l)
			time_lu[puk] = biostime(0,0L); //зафиксировать время события

		for(yi = 0;yi<=2;yi++) //seg006:0F2B loc_28E3B:
		{
			//seg006:0F0D
			lu[puk][yi] = bnf[yi+3];//обновить запакованные значения для байтов K1X
			ccv1 = ccv1 + obnov_lu(puk,yi,bnf);//раскидать распаковку полученных бит по массиву mas_lu
		}
		//seg006:0F30
		if(ccv1>0)
			slom_interf(4000+puk);//seg006:0F3C
		return;
	}
	else
	if(bnf[3]==D_kont[0][1])//если получены данные по O1X - обрыв групп seg006:0F54
	{
		if(time_lv[puk]==0l)
			time_lv[puk]=biostime(0,0L);
		for(yi=0;yi<=2;yi++)
		{
			lv[puk][yi] = bnf[yi+4];
			ccv1=ccv1+obnov_lv(puk,yi,bnf); //seg006:0FD8
		}
		if(ccv1>0)
			slom_interf(4010+puk);
		return;
	}
	else
	//seg006:0FF9 loc_28F09:
	if(bnf[3]==D_kont[0][2])//если получены данные по потере 0 D1X - M201-1
	{ if(time_ly[puk]==0l)time_ly[puk]=biostime(0,0L);
		//запись данных о потере
		for(yi=0;yi<=3;yi++)
		{ ly[puk][yi]=ly[puk][yi]|(bnf[yi+4]&0xff);
			ccv1=ccv1+obnov_ly(puk,yi,bnf,0);
		}
		if(ccv1>0)slom_interf(4020+puk);
		return;
	}
	else
	if(bnf[3]==D_kont[0][3]) //если получены данные по потере 0 D2X - M201-2
	{ if(time_lz[puk]==0l)time_lz[puk]=biostime(0,0L);
		for(yi=0;yi<=3;yi++)
		{ lz[puk][yi]=lz[puk][yi]|(bnf[yi+4]&0xff);
			ccv1=ccv1+obnov_lz(puk,yi,bnf,0);
		}
		if(ccv1>0)slom_interf(4030+puk);
		return;
	}
	else
	if(bnf[3]==D_kont[0][4])//если получены данные по потере нуля D3X - M201-3
	{
		if(time_lc[puk]==0l)time_lc[puk]=biostime(0,0L);
		for(yi=0;yi<=3;yi++)
		{
			lc[puk][yi]=lc[puk][yi]|(bnf[yi+4]&0xff);
			ccv1=ccv1+obnov_lc(puk,yi,bnf,0);
		}
		if(ccv1>0)slom_interf(4040+puk);
		return;
	}
	if(bnf[3]==D_kont[0][5])//если получены данные по потере нуля D4X - M201-4
	{
		if(time_ls[puk]==0l)time_ls[puk]=biostime(0,0L);
		for(yi=0;yi<=3;yi++)
		{
			ls[puk][yi]=ls[puk][yi]|(bnf[yi+4]&0xff);
			ccv1=ccv1+obnov_ls(puk,yi,bnf,0);
		}
		if(ccv1>0)slom_interf(4050+puk);
		return;
	}
//----------------------------------проверка правильности единиц
	if(bnf[3]==D_kont[0][6])//если получены данные по потере единиц D3X - M201-1
	{
		if(time_ly[puk]==0l)time_ly[puk]=biostime(0,0L);
		for(yi=0;yi<=3;yi++)
		{
			ly[puk][yi]=ly[puk][yi]|((bnf[yi+4]<<8)&0xff00);
			ccv1=ccv1+obnov_ly(puk,yi,bnf,1);
		}
		if(ccv1>0)slom_interf(4120+puk);
		return;
	}
	//seg006:13F3
	if(bnf[3]==D_kont[0][7])//если получены данные по потере единиц D3X - M201-2
	{
		if(time_lz[puk]==0l)
			time_lc[puk] = biostime(0,0L);
		for(yi=0;yi<=3;yi++)
		{
			lz[puk][yi] = lz[puk][yi]|((bnf[yi+4]<<8)&0xff00);
			ccv1 = ccv1+obnov_lz(puk,yi,bnf,1);
		}
		if(ccv1>0)slom_interf(4130+puk);
		return;
	}
	//seg006:14BF
	if(bnf[3]==D_kont[0][8])//если получены данные по потере единиц D3X - M201-3
	{
		if(time_lc[puk]==0l)
			time_lc[puk]=biostime(0,0L);//seg006:1501
		for(yi=0;yi<=3;yi++)//seg006:1506 loc_29416 - seg006:1565 loc_29475
		{
			lc[puk][yi] = lc[puk][yi]|((bnf[yi+4]<<8)&0xff00); //seg006:1543
			ccv1=ccv1+obnov_lc(puk,yi,bnf,1); //seg006:1561
		}
		if(ccv1>0) //seg006:156A
		slom_interf(4140+puk);  // seg006:1576
		return;
	}
}
//--------------------------------------------------------------
//seg006:1585
int obnov_lu(int pek,int ri,unsigned char blum[11])
{
	int i,jk;
	unsigned char  iok;

	nom_func("192");
     
  jk=0;
  if(ri>2)return;
  for(i=0;i<5;i++)
  { iok=blum[4+ri]&(1<<i);
    if(iok!=0)
    {
      mas_lu[pek][i+ri*5]++;
      if(mas_lu[pek][i+ri*5]==3)jk=1;
      if(mas_lu[pek][i+ri*5]>3)mas_lu[pek][i+ri*5]=4;
    }
    else mas_lu[pek][i+ri*5]=0;
  }
  return(jk);
}
//---------------------------------------------
obnov_lv(int pek,int ri,unsigned char blum[11])
{
  int i,jk;
  unsigned char iov;
  
	nom_func("193");
     
  jk=0;
  if(ri>2)return;
  for(i=0;i<5;i++)
  { iov=blum[4+ri]&(1<<i);
    if(iov!=0)
    {
      mas_lv[pek][i+ri*5]++;
      if(mas_lv[pek][i+ri*5]==3)jk=1;
      if(mas_lv[pek][i+ri*5]>3)mas_lv[pek][i+ri*5]=4;
    }
    else mas_lv[pek][i+ri*5]=0;
  }
  return(jk);
}
//---------------------------------------------------
obnov_ly(int pek,int ri,unsigned char blum[11],int tip)
{ int i,jk;
  unsigned char iok;
  
	nom_func("194");
     
  if(ri>3)return;
  jk=0;
  for(i=0;i<4;i++)
  { iok=blum[4+ri]&(1<<i);
    if(iok!=0)
    {
      if(tip==0)
      {
        mas_ly[pek][i+ri*4]++;
        if((mas_ly[pek][i+ri*4]&0xff)==3)jk=1;
        if((mas_ly[pek][i+ri*4]&0xff)>3)
        {
          mas_ly[pek][i+ri*4]=mas_ly[pek][i+ri*4]&0xff00;
          mas_ly[pek][i+ri*4]=mas_ly[pek][i+ri*4]|4;
        }
      }
      if(tip==1)
      {
        mas_ly[pek][i+ri*4]=mas_ly[pek][i+ri*4]+0x0100;
        if((mas_ly[pek][i+ri*4]&0xff00)==0x300)jk=1;
        if((mas_ly[pek][i+ri*4]&0xff00)>0x300)
        {
          mas_ly[pek][i+ri*4]=mas_ly[pek][i+ri*4]&0xff;
          mas_ly[pek][i+ri*4]=mas_ly[pek][i+ri*4]|0x400;
        }
      }
    }
    else
    {
      if(tip==0)mas_ly[pek][i+ri*4]=mas_ly[pek][i+ri*4]&0xff00;
      if(tip==1)mas_ly[pek][i+ri*4]=mas_ly[pek][i+ri*4]&0xff;
    }
  }
  return(jk);
}
//-----------------------------------------------------
obnov_lz(int pek,int ri,unsigned char blum[11],int tip)
{ int i,jk;
  unsigned char iok;
  
	nom_func("195");
     
  if(ri>3)return;
  jk=0;
  for(i=0;i<4;i++)
  { iok=blum[4+ri]&(1<<i);
    if(iok!=0)
    {
      if(tip==0)
      {
        mas_lz[pek][i+ri*4]++;
        if((mas_lz[pek][i+ri*4]&0xff)==3)jk=1;
        if((mas_lz[pek][i+ri*4]&0xff)>3)
        {
          mas_lz[pek][i+ri*4]=mas_lz[pek][i+ri*4]&0xff00;
          mas_lz[pek][i+ri*4]=mas_lz[pek][i+ri*4]|4;
        }
      }
      if(tip==1)
      {
        mas_lz[pek][i+ri*4]=mas_lz[pek][i+ri*4]+0x0100;
        if((mas_lz[pek][i+ri*4]&0xff00)==0x300)jk=1;
        if((mas_lz[pek][i+ri*4]&0xff00)>0x300)
        {
          mas_lz[pek][i+ri*4]=mas_lz[pek][i+ri*4]&0xff;
          mas_lz[pek][i+ri*4]=mas_lz[pek][i+ri*4]|0x400;
        }
      }

    }
    else
    {
      if(tip==0)mas_lz[pek][i+ri*4]=mas_lz[pek][i+ri*4]&0xff00;
      if(tip==1)mas_lz[pek][i+ri*4]=mas_lz[pek][i+ri*4]&0xff;
    }
  }
  return(jk);
}
//-----------------------------------------------------
obnov_lc(int pek,int ri,unsigned char blum[11],int tip)
{ int i,jk;
  unsigned char iok;
  
  nom_func("190");

  if(ri>3)return;
  jk=0;
  for(i=0;i<4;i++)
  { iok=blum[4+ri]&(1<<i);
    if(iok!=0)
    {
      if(tip==0)
      {
        mas_lc[pek][i+ri*4]++;
        if((mas_lc[pek][i+ri*4]&0xff)==3)jk=1;
        if((mas_lc[pek][i+ri*4]&0xff)>3)
        {
          mas_lc[pek][i+ri*4]=mas_lc[pek][i+ri*4]&0xff00;
          mas_lc[pek][i+ri*4]=mas_lc[pek][i+ri*4]|4;
        }
      }
      if(tip==1)
      {
        mas_lc[pek][i+ri*4]=mas_lc[pek][i+ri*4]+0x0100;
        if((mas_lc[pek][i+ri*4]&0xff00)==0x300)jk=1;
        if((mas_lc[pek][i+ri*4]&0xff00)>0x300)
        {
          mas_lc[pek][i+ri*4]=mas_lc[pek][i+ri*4]&0xff;
          mas_lc[pek][i+ri*4]=mas_lc[pek][i+ri*4]|0x400;
        }
      }
    }
    else
    {
      if(tip==0)mas_lc[pek][i+ri*4]=mas_lc[pek][i+ri*4]&0xff00;
      if(tip==1)mas_lc[pek][i+ri*4]=mas_lc[pek][i+ri*4]&0xff;
    }
  }
  return(jk);
}
//---------------------------------------------
obnov_ls(int pek,int ri,unsigned char blum[11],int tip)
{ int i,jk;
  unsigned char iok;
  
	nom_func("191");
   
  if(ri>3)return;
  jk=0;
  for(i=0;i<4;i++)
  { iok=blum[4+ri]&(1<<i);
    if(iok!=0)
    {
      if(tip==0)
      {
        mas_ls[pek][i+ri*4]++;
        if((mas_ls[pek][i+ri*4]&0xff)==3)jk=1;
        if((mas_ls[pek][i+ri*4]&0xff)>3)
        {
          mas_ls[pek][i+ri*4]=mas_ls[pek][i+ri*4]&0xff00;
          mas_ls[pek][i+ri*4]=mas_ls[pek][i+ri*4]|4;
        }
      }
      if(tip==1)
      {
        mas_ls[pek][i+ri*4]=mas_ls[pek][i+ri*4]+0x0100;
        if((mas_ls[pek][i+ri*4]&0xff00)==0x300)jk=1;
        if((mas_ls[pek][i+ri*4]&0xff00)>0x300)
        {
          mas_ls[pek][i+ri*4]=mas_ls[pek][i+ri*4]&0xff;
          mas_ls[pek][i+ri*4]=mas_ls[pek][i+ri*4]|0x400;
        }
      }
    }
    else
    {
      if(tip==0)mas_ls[pek][i+ri*4]=mas_ls[pek][i+ri*4]&0xff00;
      if(tip==1)mas_ls[pek][i+ri*4]=mas_ls[pek][i+ri*4]&0xff;
    }
  }
  return(jk);
}
//-------------------------------------------------
FILE *sfs;
void read_text1(int QQ)
{

  int kodd=0;
  
	nom_func("276");
          
  sfs=fopen("dat\\text1.img","r");
  if(sfs==NULL) return;
aa:
  fscanf(sfs,"%d",&kodd);
  while(fgetc(sfs)!='\n');
  switch(kodd)
  {
    case 999: break;
    case 1: read_slova(QQ);goto aa;
    case 22: electri_platf(QQ); goto aa;
    case 2: ramki(0);goto aa;
		case 6: elo_net(QQ); goto aa;	
    case 3: read_pereezd(QQ); goto aa;
    case 5: read_dzezli(QQ);  goto aa;
    case 4: read_smen(QQ); goto aa;
    case 7: figura(7); goto aa;
    case 8: figura(8); goto aa;
    case 9: ramki(1);goto aa;
    default:break;
  }
	if(sfs!=NULL)fclose(sfs);
	sfs=NULL;
}
/******************************************************************/
void read_slova(int SD)
{
  int symb=0;
  int x,y,sty,cv,gk;
  char slovo[60]="";
  char slo[60]="";
  
	nom_func("272");
         
  if((klo==1)||(help!=0)||(nikuda==1))return; 
  symb=fgetc(sfs);
  while(symb!='#')
  {
    fscanf(sfs,"%d%d%d%d",&x,&y,&sty,&cv);
    x=x+SD;
    for(gk=0;gk<60;gk++)slovo[gk]=0;
    for(gk=0;gk<20;gk++)slo[gk]=0;
    fscanf(sfs,"%s",slo);
    for(gk=0;gk<strlen(slo);gk++)
    if(slo[gk]=='_') slovo[gk]=' ';
    else slovo[gk]=slo[gk];
    moveto(x,y);
    if(sty==17)settextstyle(USER_FONT,1,0);
    if(sty==1)setusercharsize(1,1,2,3);
    setcolor(cv);outtext(slovo);
    settextstyle(USER_FONT,0,0);
    setusercharsize(1,1,1,1);
    fgetc(sfs);
    symb=fgetc(sfs);
    if(symb!='@') break;
  }
}
/*******************************************************/
void electri_platf(int SD)
{
  int xkv,ykv,dxkv,dykv,xgol,ygol,sty,cv,dxp,dxm,dym,dyp,symb=0;
  
	nom_func("48");

  if((klo==1)||(help!=0)||(nikuda==1))return;
  symb=fgetc(sfs);
  while(symb!='#')
  {
    fscanf(sfs,"%d %d %d %d %d %d %d %d %d %d %d %d",
    &sty,&cv,&xkv,&ykv,&dxkv,&dykv,&xgol,&ygol,&dxm,&dxp,&dym,&dyp);
    xkv=xkv+SD;xgol=xgol+SD;
    setcolor(cv);
    setlinestyle(0,0,sty);
    rectangle(xkv,ykv,xkv+dxkv,ykv+dykv);
    circle(xgol,ygol,1);
    circle(xgol,ygol,0);
    line(xgol+dxm,ygol+dym,xgol+dxp,ygol+dyp);
    fgetc(sfs);
    symb=fgetc(sfs);
    if(symb!='@') break;
  }
}
/*****************************************************************/
void ramki(int lines)
{
  int xkv,ykv,dxkv,dykv,sty,cv,wi;
  int symb=0;
  char znak;
  
	nom_func("261");
          
  if((klo==1)||(help!=0)||(nikuda==1))return;
  symb=fgetc(sfs);
  while(symb!='#')
  {
    fscanf(sfs,"%d %d %d %d %d %d %d",&wi,&sty,&cv,&xkv,&ykv,&dxkv,&dykv);
    setlinestyle(wi,0,sty);
    setcolor(cv);
    if(lines==0)rectangle(xkv,ykv,xkv+dxkv,ykv+dykv);
    else line(xkv,ykv,xkv+dxkv,ykv+dykv);
    while(znak!=10)znak=fgetc(sfs);
    symb=fgetc(sfs);
    if(symb!='@') break;
  }
}
//--------------------------------------------------------
/******************************************************\
* Процедура установки постоянных ограничений по данным        *
* из файла text1.img. Рисуется однократно при загрузке   *
\******************************************************/
void elo_net(int SD)
{
	int n_ob,n_fr4,cod;
	int symb=0;

	nom_func("49");

	if((klo==1)||(help!=0)||(nikuda==1))return;
	symb=fgetc(sfs);
	while(symb!='#')
	{
		fscanf(sfs,"%d %d %d",&n_ob,&n_fr4,&cod);
		fr4[n_ob][n_fr4] = cod;
		fgetc(sfs);
		symb=fgetc(sfs);
		if(symb!='@') break;
	}
	return;
}
/*****************************************************************/
void read_smen(int SD)
{
  int o,symb=0;
  
	nom_func("273");
          
  if((klo==1)||(help!=0)||(nikuda==1))return;
  symb=fgetc(sfs);
  while(symb!='#')
  {
   for(o=0;o<=13;o++)fscanf(sfs,"%d ",&left_up_left[o]);
   while(fgetc(sfs)!='@');
   for(o=0;o<=13;o++)fscanf(sfs,"%d ",&left_up_right[o]);
   while(fgetc(sfs)!='@');
   for(o=0;o<=13;o++)fscanf(sfs,"%d ",&right_up_left[o]);
   while(fgetc(sfs)!='@');
   for(o=0;o<=13;o++)fscanf(sfs,"%d ",&right_up_right[o]);
   fgetc(sfs);
   symb=fgetc(sfs);
   if(symb!='@') break;
  }
  if(SD!=0)
  {
    for(o=0;o<13;o=o+2)
    {
      left_up_left[o]=left_up_left[o]+SD;
      left_up_right[o]=left_up_right[o]+SD;
      right_up_left[o]=right_up_left[o]+SD;
      right_up_right[o]=right_up_right[o]+SD;
    }
  }
}
/*********************************************/
void read_dzezli()
{
  int x1,y1,o,symb=0;
  
	nom_func("267");
          
  if((klo==1)||(help!=0)||(nikuda==1))return;
  symb=fgetc(sfs);
  while(symb!='#')
  {
    fscanf(sfs,"%d %d %d ",&o,&x1,&y1);
    fr3[o][6]=x1; fr3[o][9]=y1;
    symb=fgetc(sfs);
    if(symb!='@') break;
  }
}
//--------------------------------------
void read_pereezd()
{
int symb=0,o,x1p,y1p,dli;
  
	nom_func("271");
        
if((klo==1)||(help!=0)||(nikuda==1))return;
symb=fgetc(sfs);
while(symb!='#')
  {
   fscanf(sfs,"%d %d %d %d ",&o,&x1p,&y1p,&dli);
    //o- объект с информацией о переезде
    //x1p - координата x
    //y1p - координата y
    //dli - длина переезда
   fr1[o][4]=x1p; fr1[o][5]=y1p; fr1[o][6]=dli;
   fgetc(sfs);
   symb=fgetc(sfs);
   if(symb!='@') break;
  }
}
//---------------------------------------------------------
void figura(int tip)
{
  int poli[20],cv,symb=0,i;
  
	nom_func("54");
  
  if((klo==1)||(help!=0)||(nikuda==1))return;
  symb=fgetc(sfs);
  while(symb!='#')
  {
    symb=fgetc(sfs);
    fscanf(sfs,"%d",&symb);
    for(i=0;i<2*symb;i++)fscanf(sfs,"%d",&poli[i]);
    fscanf(sfs,"%d",&cv);
    setcolor(cv);
    if(tip==8){setfillstyle(0,cv);drawpoly(symb,poli);}
    if(tip==7){setfillstyle(1,cv);fillpoly(symb,poli);}
    fgetc(sfs);
    symb=fgetc(sfs);
    if(symb!='@') break;
  }
}
//-------------------------------------------------------------
int get_str(int nm,int bt_)
{
//поиск измененного, но не зафиксированного бита
//и имени соответствующего объекта, при удачном поиске возвращает 0
//имя объекта в переменной chudo
  int g1,co_pro=0,h1,dlip=0,mn=0,i,cod;
  char loo[40]="",chu[20]="";

  nom_func("99");

  if(bt_==5)return(1);
  strcpy(loo,pako[nm]); //скопировать строку имен
  dlip=strlen(loo);//получить длину всей строки
  g1=0;//установить указатель в начало строки
  while(co_pro<bt_)//двигаться по строке, пока пробелов меньше номера бита
  { if(g1>dlip)return(1); //выход с неудачей, если строка кончилась
    if(loo[g1]==' ') co_pro++;//если найден пробел, добавить к счетчику
    g1++;
  }
  for(mn=0;mn<=19;mn++)chu[mn]=0;//очистить выходной массив
  strcpy(chudo,"");
  h1=0;
  while(1)//цикл заполнения выходного массива именем объекта
  { if(g1>dlip){strcpy(chudo,chu); goto fin;}//для последнего выход по размеру
    if(loo[g1]==' '){strcpy(chudo,chu);goto fin;}//для прочих выход по пробелу
    chu[h1]=loo[g1];h1++;g1++;//добавить одну букву и перейти к следующей
  }
fin:
    return(0);
}
