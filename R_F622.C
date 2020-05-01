#include"bla.h"
#include<graphics.h>
#include<dos.h>
#include<stdio.h>
#include<io.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
//---------------------------------------------
void vuhod()
{

	nom_func("4051");

//settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
setlinestyle(0,0,0);
setcolor(8);

line(8,464,630,464);

line(8,233,8,464);
line(13*8,233,13*8,464);
line(23*8,233,23*8,464);
line(50*8,233,50*8,464);
line(630,233,630,464);
setfillstyle(SOLID_FILL,cvv);
bar(15*8,472,15*8+250,480);
moveto(15*8,472);outtext("‚ëå®¤ - '");setcolor(MAGENTA);outtext("F6");
setcolor(8);outtext("',¢¯¥à¥¤ - '");setcolor(MAGENTA);outtext("PgDn");
setcolor(8);outtext("',­ § ¤ - '");setcolor(MAGENTA);outtext("PgUp");
setcolor(8);outtext("'");
}
//-----------------------------------------------------------
void vuhod1()
{

	nom_func("405");

//settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
setlinestyle(0,0,0);
setcolor(8);
line(8,464,630,464);
setfillstyle(SOLID_FILL,cvv);
bar(15*8,472,15*8+250,480);
moveto(15*8,472);outtext("‚ëå®¤ - '");setcolor(MAGENTA);outtext("F5");
setcolor(8);outtext("',¢¯¥à¥¤ - '");setcolor(MAGENTA);outtext("PgDn");
setcolor(8);outtext("',­ § ¤ - '");setcolor(MAGENTA);outtext("PgUp");
setcolor(8);outtext("'");
}
/*************************************************/
void shl()
{

	nom_func("302");

  setlinestyle(0,0,0); setcolor(8); line(8,213,630,213);
  moveto(4*8,220);outtext("„€’€");
  moveto(15*8,220);outtext("‚…ŒŸ");
  moveto(23*8,216);outtext(" „ˆ€ƒŽ‘’ˆŠ€ €€€’“› ’“Œ‘");
  moveto(56*8,216);outtext("…ˆ‘€‚Ž‘’ˆ");
  moveto(56*8,225);outtext("  ˆ’…”…‰‘€");
  line(8,213,8,233);line(13*8,213,13*8,234);
  line(23*8,213,23*8,234);line(50*8,213,50*8,234);
  line(630,213,630,234);line(8,234,630,234);
}
/*****************************************************/
void clear_half()
{

	nom_func("23");

	setfillstyle(SOLID_FILL,getbkcolor());
	bar(0,210,getmaxx(),getmaxy());
}
/******************************************************/
void fon_pic()
{
	char AAq[2]="";

	nom_func("69");

	/****     íâ® ä®­ ¤«ï ª àâ¨­ª¨     ************/
	setfillstyle(SOLID_FILL,getbkcolor());
	bar(32,5,getmaxx()-32,205);
	setfillstyle(CLOSE_DOT_FILL,YELLOW);
  bar(32,5,getmaxx()-32,205);
  setcolor(MAGENTA);
  setlinestyle(0,0,0);
  rectangle(36,7,getmaxx()-36,203);
  setlinestyle(0,0,3);
  rectangle(40,10,getmaxx()-40,200);

  setcolor(8);
  setlinestyle(0,0,0);
#ifdef KOL_SOO2
  rectangle(275,20,355,100);
  outtextxy(263,20,"’");
  outtextxy(263,28,"“");
  outtextxy(263,36,"Œ");
  outtextxy(263,44,"‘");
  outtextxy(263,52," ");
  outtextxy(263,58,"2");
  rectangle(282,25,347,50);
  rectangle(282,53,347,78);
#endif
  rectangle(275,118,355,195);
  outtextxy(263,150,"’");
  outtextxy(263,158,"“");
  outtextxy(263,166,"Œ");
	outtextxy(263,174,"‘");
  outtextxy(263,182," ");
  outtextxy(263,188,"1");
  rectangle(282,122,347,147);
  rectangle(282,150,347,175);
  setcolor(8);
  //settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
  moveto(468,70);
  outtext("‚Œ");
  if(NOMER_ARMA==1) outtext("2");
  else outtext("1");
  moveto(130,70);
	if(DSP_SHN == 0)
	{	
		outtext("€Œ ˜");
	}
	else
	{
		outtext("‚Œ");
		itoa(NOMER_ARMA,AAq,10);
		outtext(AAq);
	}	
  setcolor(8);
  setlinestyle(0,0,3);
  rectangle(467,87,507,133);
  rectangle(127,87,167,133);
}
/************************************************/
void sost_komplect(int KKS)
{
	char slovo1[10],slovo2[10];
	int color1=0,color2=0,cod;
	int smeo=0;

	nom_func("315");
          
	if(KKS==KS1) smeo=97;
  else smeo=0;
  cod=fr3[KKS][0]+fr3[KKS][1]*2+fr3[KKS][2]*4;
  switch(cod)
  {
    case 0: color1=10;color2=14;
            strcpy(slovo1,"ˆ‘AB");strcpy(slovo2,"ˆ‘€‚");
            break;
    case 1: color2=10;color1=14;
            strcpy(slovo1,"ˆ‘AB");strcpy(slovo2,"ˆ‘€‚");
            break;
    case 2: color2=14;color1=12;
            strcpy(slovo1,"…ˆ‘");strcpy(slovo2,"ˆ‘€‚");
            break;
    case 3: color2=10;color1=4;
            strcpy(slovo1,"…ˆ‘");strcpy(slovo2,"ˆ‘€‚");
            break;
    case 4: color2=4;color1=10;
            strcpy(slovo1,"ˆ‘€‚");strcpy(slovo2,"…ˆ‘");
            break;
    case 5: color2=12;color1=14;
            strcpy(slovo1,"ˆ‘€‚");strcpy(slovo2,"…ˆ‘");
            break;
    case 6: color2=4;color1=12;
            strcpy(slovo1,"…ˆ‘");strcpy(slovo2,"…ˆ‘");
            break;
		case 7: color2=12;color1=4;
            strcpy(slovo1,"…ˆ‘€‚");strcpy(slovo2,"ˆ‘€‚");
            break;
  }

x:
  if(((KKS==KS1)&&(otkaz_ts[0]==1))||((KKS==KS2)&&(otkaz_ts[1]==1))||(fr3[KKS][5]==1))color1=color2=3;
  setfillstyle(SOLID_FILL,color1);
  bar(283,26+smeo,346,49+smeo);
  if(((KKS==KS1)&&(otkaz_ts[0]==1))||((KKS==KS2)&&(otkaz_ts[1]==1))||(fr3[KKS][5]==1)) setcolor(3);
  else setcolor(8);
  outtextxy(290,38+smeo,slovo1);
  setfillstyle(SOLID_FILL,color2);
  bar(283,54+smeo,346,77+smeo);
  if(((KKS==KS1)&&(otkaz_ts[0]==1))||((KKS==KS2)&&(otkaz_ts[1]==1)))  setcolor(3);
  else setcolor(8);
  outtextxy(290,66+smeo,slovo2);
  setcolor(8);
  outtextxy(295,28+smeo,"‚Œ 1");
  outtextxy(295,56+smeo,"‚Œ 2");
}
//----------------------------------------
void kanal(int kakoi)
{
	int st1=0,st2=0,cl1=0,cl11=0,cl2=0,cl22=0;
	char  right[2]={'\x10'}, /* ts */
				left[2]={'\x11'}; /* ty */

	nom_func("114");

	if(kakoi==0)  /* á¢®© */
	{
		setcolor(7);
		setlinestyle(3,0,0);
#ifdef KOL_SOO2
    line(200,75,275,75);
    line(200,100,200,75);
    line(169,100,200,100);
#endif
    line(169,120,200,120);
    line(200,120,200,145);
    line(200,145,275,145);
    setcolor(8);
#ifdef KOL_SOO2
    if(otkaz_ts[1]==1){st1=3;cl1=RED;}
    else {st1=0;cl1=GREEN;}
    setlinestyle(st1,0,0);
    line(200,75,275,75);
    line(200,100,200,75);
    line(167,100,200,100);
    setcolor(cl1);   /* áâà¥«ª¨ á«¥¢  */
    outtextxy(215,72,left); //’‘ ¤«ï ’“Œ‘-2
    if((zapret[1]==0)&&(otkaz_tu[1]==0))cl2=GREEN;
    else cl2=RED;
    setcolor(cl2);
    outtextxy(250,72,right);  //’“ ¤«ï ’“Œ‘-2
#endif
    if(otkaz_ts[0]==0){cl11=GREEN;st2=0;}
    else {cl11=RED;st2=3;}
    setlinestyle(st2,0,0);
    line(167,120,200,120);
		line(200,120,200,145);
    line(200,145,275,145);
    setcolor(cl11);
    outtextxy(215,142,left); //’‘ ¤«ï ’“Œ‘-1
    if((zapret[0]==0)&&(otkaz_tu[0]==0))cl22=GREEN;
    else cl22=RED;
    setcolor(cl22);
    outtextxy(250,142,right);//’“ ¤«ï ’“Œ‘-1
//#endif
  }
  else  //á®á¥¤
  {
    if(NEISPRAVEN==0)
    {
#ifdef KOL_SOO2
      if(otkaz_sos[1]==0){cl1=GREEN;st1=0;}
      else {cl1=RED; st1=3;}
#endif
      if(otkaz_sos[0]==0){cl11=GREEN;st2=0;}
      else {cl11=RED;st2=3;}
    }
    else {cl1=cl11=8;st1=st2=3;}
    if(NEISPRAVEN==0)
    {
      if((otkaz_sos[0]==0)&&(otkaz_tu_sos[0]==0))cl22=GREEN;
      else cl22=RED;
#ifdef KOL_SOO2
      if((otkaz_sos[1]==0)&&(otkaz_tu_sos[1]==0))cl2=GREEN;
      else cl2=RED;
#endif
    }
    else cl2=cl22=8;
    setcolor(7);
    setlinestyle(3,0,0);
		line(355,145,430,145);
		line(430,145,430,120);
		line(430,120,466,120);
#ifdef KOL_SOO2
		line(355,75,430,75);
		line(430,75,430,100);
		line(430,100,466,100);
    setcolor(8);
    setlinestyle(st1,0,0);
    line(355,75,430,75);
    line(430,75,430,100);
    line(430,100,466,100);
    setcolor(cl1);
    outtextxy(410,72,right);
    setcolor(cl2);
    outtextxy(375,72,left);
#endif
    setcolor(8);
    setlinestyle(st2,0,0);
    line(355,145,430,145);
    line(430,145,430,120);
    line(430,120,466,120);
    setcolor(cl11);
    outtextxy(410,142,right);
    setcolor(cl22);
    outtextxy(375,142,left);
  }
}
//-----------------------------------
void PVM(int no,int is)
{
	char right[2]={'\x10'}, /* ts */
			left[2]={'\x11'}; /* ty */
	int Xp = 128;
	nom_func("258");
	if(no==0)
	{
		/* á¢®ï ‚Œ */
		if(STATUS==0) setfillstyle(SOLID_FILL,YELLOW);//¥á«¨ à¥§¥à¢­ ï
		else
			if(STATUS==2) setfillstyle(SOLID_FILL,8);//¥á«¨ ˜
			else setfillstyle(SOLID_FILL,GREEN);//¥á«¨ ®á­®¢­ ï
				bar(Xp,88,166,132);
	}
	else
	{
		/* á®á¥¤­ïï ‚Œ */
		if(is==1) setfillstyle(SOLID_FILL,RED);//¥á«¨ ­¥¨á¯à ¢­ 
		else
			if(STATUS==1) setfillstyle(SOLID_FILL,YELLOW);//¥á«¨ à¥§¥à¢­ ï
			else
				if(STATUS==2) setfillstyle(SOLID_FILL,8);//¥á«¨ ˜
				else setfillstyle(SOLID_FILL,GREEN);
		bar(Xp+340,88,Xp+378,132);

	}
	/* ª ­ « ‚Œ- ‚Œ */
	if(DSP_SHN != 0)
	{	
		setcolor(8);
		if(is==1)  setlinestyle(3,0,0);
		else setlinestyle(0,0,0);
		line(Xp+39,110,Xp+336,110);

		/* áâà¥«ª¨ ¬¥¦¤ã ‚Œ */	
		if(is==1) setcolor(RED);
		else setcolor(GREEN);
		outtextxy(Xp+122,107,left);
		setcolor(GREEN);
		outtextxy(Xp+249,107,right);
	}	
}
/***************************************************/
void kartina()
{
	char right[2]={'\x10'}, /* ts */
	left[2]={'\x11'}; /* ty */
  
	nom_func("117");
          
	if((nikuda==1)||(help!=0)) return;
  if(klo==0) fon_pic();
  /* á®áâ ‚Œ */
  PVM(0,0);
  PVM(1,NEISPRAVEN);
  /**/
  sost_komplect(KS1);
#ifdef KOL_SOO2
  sost_komplect(KS2);
#endif
  kanal(0); //ª ­ «ë ‚Œ 1
  kanal(1); //ª ­ «ë ‚Œ 2
  kps_osn(KVV1);
  kps_rez(KVV1);
  tel_vkl_vikl(TEL1);
  if(DISK!=0)tele(TEL1);
#ifdef KOL_SOO2
  kps_osn(KVV2);
  kps_rez(KVV2);
  tel_vkl_vikl(TEL2);
  if(DISK!=0)tele(TEL2);
#endif

}
//------------------------------------------------------------
void first_second(int nom)
{
	int nnom,jv,aoar;
  
	nom_func("63");
    
  if((nom==KS1)||(nom==KS2))
  {
    nnom=0;
    if(nom==KS1)nnom=0;
    else nnom=1;
    if(klo==1) kartina();
    aoar=fr3[nom][0]+fr3[nom][1]*2+fr3[nom][2]*4;
    if(aoar==old_aoar[nnom])return;
    switch(aoar)
    {
      //¨á¯à ¢­®¥ á®áâ®ï­¨¥ ¯¥à¢ë©- ®á­®¢­®©
      case 0: slom_interf(8000+nnom);break;//¢á¥ ¨á¯à ¢­® ®á­®¢­®© 1
      case 1: slom_interf(8010+nnom);break;//¢á¥ ¨á¯à ¢­® ®á­®¢­®© 2
      case 2: slom_interf(8020+nnom);break;//®á­®¢­®© 1 ­¥¨á¯à ¢¥­ 1
      case 3: slom_interf(8030+nnom);break;//®á­®¢­®© 2 ­¥¨á¯à ¢¥­ 1
			case 4: slom_interf(8040+nnom);break;//®á­®¢­®© 1 ­¥¨á¯à ¢¥­ 2
			case 5: slom_interf(8050+nnom);break;//®á­®¢­®© 2 ­¥¨á¯à ¢¥­ 2
			case 6: slom_interf(8060+nnom);break;//®á­®¢­®© 1 ­¥¨á¯à ¢¥­ 1 ¨ 2
			case 7: slom_interf(8070+nnom);break;//®á­®¢­®© 2 ­¥¨á¯à ¢¥­ 1 ¨ 2
		}
		old_aoar[nnom]=aoar;
	}
}
//----------------------------------
void fraza2(int inde)
{
	char AAq[2]="";

	nom_func("90");
        
  switch(inde)
  {
    case 7000: outtext("®âª § ’‘-1"); break;
    case 7001: outtext("®âª § ’‘-2"); break;
    case 7010: outtext("®âª § ’“-1"); break;
    case 7011: outtext("®âª § ’“-2"); break;
    case 7020: outtext("§ ¯à¥â ’“-1"); break;
    case 7021: outtext("§ ¯à¥â ’“-2"); break;

    case 7050: outtext("¢®ááâ ­®¢«¥­¨¥ ’‘-1"); break;
    case 7051: outtext("¢®ááâ ­®¢«¥­¨¥ ’‘-2"); break;
    case 7060: outtext("¢®ááâ ­®¢«¥­¨¥ ’“-1"); break;
    case 7061: outtext("¢®ááâ ­®¢«¥­¨¥ ’“-2"); break;
    case 7070: outtext("à §à¥è¥­¨¥ ’“-1"); break;
    case 7071: outtext("à §à¥è¥­¨¥ ’“-2"); break;

    case 7100: outtext("®âª § ’‘-1 á®á¥¤­¥© ‚Œ"); break;
    case 7101: outtext("®âª § ’‘-2 á®á¥¤­¥© ‚Œ"); break;
    case 7110: outtext("®âª § ’“-1 á®á¥¤­¥© ‚Œ"); break;
    case 7111: outtext("®âª § ’“-2 á®á¥¤­¥© ‚Œ"); break;
    case 7120: outtext("§ ¯à¥â ’“-1 á®á¥¤­¥© ‚Œ"); break;
    case 7121: outtext("§ ¯à¥â ’“-2 á®á¥¤­¥© ‚Œ"); break;

    case 7150: outtext("¢®ááâ.’‘-1 á®á¥¤­¥© ‚Œ"); break;
		case 7151: outtext("¢®ááâ.’‘-2 á®á¥¤­¥© ‚Œ"); break;
    case 7160: outtext("¢®ááâ.’“-1 á®á¥¤­¥© ‚Œ"); break;
		case 7161: outtext("¢®ááâ.’“-2 á®á¥¤­¥© ‚Œ"); break;
    case 7170: outtext("à §à¥è.’“-1 á®á¥¤­¥© ‚Œ"); break;
		case 7171: outtext("à §à¥è.’“-2 á®á¥¤­¥© ‚Œ"); break;
		case 7200: outtext("¢®ááâ. á¢ï§ì ‚Œ1=‚Œ2"); break;
		case 7300: outtext("­¥â á¢ï§¨ ‚Œ1-‚Œ2");break;
		case 7400: outtext("¤ ­­ ï ‚Œ-®á­®¢­ ï");break;
		case 7500: outtext("¤ ­­ ï ‚Œ-à¥§¥à¢­ ï");break;
		case 7600: outtext("­¥ ®¯à¥¤¥«¥­ áâ âãá ‚Œ "); break;
		case 7700: outtext("¢ë¤ ­ § ¯à®á ¢ ®á­®¢.‚Œ");break;
		case 7800: outtext("®âª § ­® ¢ ¯¥à¥¤ ç¥ ‚Œ");break;
		case 7900: outtext("¯®«ãç¥­ ®âª § ®â ‚Œ");break;
		case 7940: outtext("à¥ª®­ä¨£.1-£® ª ­. á®á¥¤­¥© ‚Œ");break;
		case 7950: outtext("à¥ª®­ä¨£.2-£® ª ­. á®á¥¤­¥© ‚Œ");break;
		default:  break;
	}
}
//------------------------------------------------
void fraza(int inde)
{
  
	nom_func("89");

  switch(inde)
  {
    case 8000: outtext("1© ¨ 2© ¨á¯à ¢­ë,®á­.Œ‘“1");break;
    case 8010: outtext("1© ¨ 2© ¨á¯à ¢­ë,®á­.Œ‘“2");break;
		case 8020: outtext("®âª § Œ‘“1, Œ‘“1-®á­.");break;
		case 8030: outtext("®âª § Œ‘“1, Œ‘“2-®á­.");  break;
		case 8040: outtext("®âª § Œ‘“2, Œ‘“1-®á­");break;
		case 8050: outtext("®âª § Œ‘“2, Œ‘“2-®á­.");break;
		case 8060: outtext("®âª § Œ‘“1 ¨ Œ‘“2,Œ‘“1-®á­.");break;
		case 8070: outtext("®âª § Œ‘“1 ¨ Œ‘“2,Œ‘“2-®á­."); break;
 }
}
//-------------------------------------------------------
char read_sode(int HNDL,int numbe,char STRK[50])
{
	char STr[17],bukv;
	int j;

	nom_func("274");

	if((numbe>=4000)&&(numbe<4010))//®¡ê¥¤¨­¥­¨¥ £àã¯¯
	{
		for(plo=0;plo<=14;plo++)
		{
			read(HNDL,&mlu[plo],1);  //--------------- seg018:136B  
			if(mlu[plo]==13)
				break;
		}
	}
	if((numbe>=4010)&&(numbe<4020))//®¡àë¢ £àã¯¯
	{
		for(plu=0;plu<=14;plu++)
		{
			read(HNDL,&mlv[plu],1);//--------------------  seg018:13D9
			if(mlv[plu]==13)break;
		}
	}
	if((numbe>=4020)&&(numbe<4030))//¯®â¥àï 0 201.1
	{
		for(plu=0;plu<=15;plu++)
		{
			read(HNDL,&mly[plu],1); //------------------------ seg018:1447
			if(mly[plu]==13)break;
		}
	}
	if((numbe>=4030)&&(numbe<4040))//¯®â¥àï 0 201.2
	{
		for(plu=0;plu<=15;plu++)
		{
			read(HNDL,&mlz[plu],1); //---------------------- seg018:14B5
			if(mlz[plu]==13)break;
		}
	}
	if((numbe>=4040)&&(numbe<4050))//¯®â¥àï 0 201.3
	{
		for(j=0;j<16;j++)
		{
			read(HNDL,&STr[j],1); //------------------- seg018:1515
			if((STr[j]==32) && (j>1))
				break;
		}
		for(plu=0;plu<=15;plu++)
		{
			read(HNDL,&mlc[plu],1); //--------------------------- seg018:1558
			if(mlc[plu]==13)break;
		}
	}
	if((numbe>=4050)&&(numbe<4060))//¯®â¥àï 0 201.4
	{
		for(j=0;j<16;j++)
		{
			read(HNDL,&STr[j],1);  //--------------------- seg018:15B8
			if((STr[j]==32)&&(j>1))break;
		}
		for(plu=0;plu<=15;plu++)
		{
			read(HNDL,&mls[plu],1); //--------------------- seg018:15FB
			if(mls[plu]==13)break;
		}
	}
	if((numbe>=4060)&&(numbe<4080))
	{
		for(j=0;j<16;j++)
		{
			read(HNDL,&bukv,1);
			STr[j]=bukv;
			if(((STr[j]==32)&&(j>1))||(STr[j]==13))break;
		}
		if(j==10)
			kot=0;
		else 
			{
				STr[j]=0;
				kot=atoi(STr);
			}
	}
	if((numbe>=4120)&&(numbe<4130))//¯®â¥àï 1 Œ201.1
	{
		for(plu=0;plu<=15;plu++)
		{
			read(HNDL,&mly[plu],1);
			if(mly[plu]==13)break;
		}
	}
	if((numbe>=4130)&&(numbe<4140))//¯®â¥àï 1 Œ201.2
	{
		for(j=0;j<16;j++)
		{
			read(HNDL,&STr[j],1);
			if(((STr[j]==32)&&(j>1))||(STr[j]==13))break;
		}
		if(j==10)kot=0;
		else {STr[j]=0;kot=atoi(STr);}
		for(plu=0;plu<=15;plu++)
		{
			read(HNDL,&mlz[plu],1);
			if(mlz[plu]==13)break;
		}
	}
	if((numbe>=4140)&&(numbe<4150))//¯®â¥àï 1 Œ201.3
	{
		for(j=0;j<16;j++)
		{
			read(HNDL,&STr[j],1);
			if(((STr[j]==32)&&(j>1))||(STr[j]==13))break;
		}
		if(j==10)kot=0;
		else {STr[j]=0;kot=atoi(STr);}
		for(plu=0;plu<=15;plu++)
		{
			read(HNDL,&mlc[plu],1);
			if(mlc[plu]==13)break;
		}
	}
}
//-------------------------------------------------------------------
