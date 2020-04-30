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

			//�᫨ ��ꥪ� ᮡ�⢥���� �㦤 ����஫���
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
				if(bu[kanal][3] == D_kont[0][jj])//�᫨ ��ꥪ� ᮡ�⢥���� �㦤 
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
{ //��楤�� �ᯠ����� ᮮ�饭�� ��� ��⥩
  int Z=5,kh=0,M,l;
  unsigned int tst_bit,tst;
  unsigned char kop=0;
  int iv,jv,tester=999,reza=0,FIN=0,FN=0;
#ifdef NALAD
  nom_func("257");
#endif
  tester=999;
#ifdef KOL_SOO2
  if(kim==2)//�᫨ �⮩�� 2
  {
    FN=PUT1;
    FIN=FN+PUT2;
  }
#endif
  if(kim==1) //�᫨ �⮩�� 1
  {
    FIN=PUT1;
    FN=0;
  }
  for(iv=FN;iv<FIN;iv++) //�ன� �� �����㯯��
  if(bufpu[3]==podgruppa[iv+Smo-sto])//�᫨ ��諨 �� �����㯯�
  {
    tester=iv;
    break;
  }
  if(tester==999) return(tester);//�᫨ �����㯯� �� ������� - ������ 999
  for(jv=0;jv<Z;jv++)//�ன� �� ��ꥪ⠬ �����㯯�
  {
    vysv=0;
    kh=spputi[tester][jv]; //����� ����� ��ꥪ�
    if(kh==1111) goto Bbreak; //�᫨ ��ꥪ� ���⮩ - �ய�����
    l=1;
    n=jv+4;
    for(M=0;M<=5;M++)//�ன� �� ��⠬
    {
      kop=bufpu[n]&l; //������� ���祭�� ���
      if(kop==0)//�᫨ ��� ᫥��� �����
      {
        if(fr3[kh][M]==0)goto nono;
        else// �᫨ ࠭�� ��� �� ��⠭�����
        {
          if(fr1[kh][7]<9999)goto met0;//�᫨ ���⮪ �ਡ�������
          else
#ifdef PUTI_IN_2
          if(fr1[kh][13]!=9999)
          goto met0;
          else
          {
            if(CHET==2)
            {
              if((FN>0)&&//�᫨ ���� �⮩�� �
              (M==2)&&(fr1[kh][8]==1010))//��� �� � �ਥ��-��ࠢ���
              goto nono;//� ��
              if((FN==0)&&(M==1)&&(fr1[kh][8]==1010)&&(skoko_stoek==2))goto nono;// �᫨ ��,� �⮩�� 1
              if(FN==0)tst_bit=1<<(M*2);//�᫨ ��ࢠ� �⮩��, � ���-��� �����
              else tst_bit=2<<(M*2);//�᫨ ���� �⮩��, � ���-��� ���
              tst_bit=~tst_bit;//������� ���-���
            }
            else
            {
              if((FN>0)&&//�᫨ ���� �⮩�� �
              (M==1)&&(fr1[kh][8]==1010))//��� �� � �ਥ��-��ࠢ���
              goto nono;//� ��
              if((FN==0)&&(M==2)&&(fr1[kh][8]==1010)&&(skoko_stoek==2))goto nono;// �᫨ ��,� �⮩�� 1
              if(FN==0)tst_bit=2<<(M*2);//�᫨ ��ࢠ� �⮩��, � ���-��� �����
              else tst_bit=1<<(M*2);//�᫨ ���� �⮩��, � ���-��� ���
              tst_bit=~tst_bit;//������� ���-���
            }
          }
          fr3[kh][6]=fr3[kh][6]&tst_bit;//���뢠��� ��� � ᫮�� �離�
          tst_bit=3<<(M*2);//�ନ஢���� ���-��� �� ��� ࠧ�鸞
          if((fr3[kh][6]&tst_bit)==0)
#endif
met0:     fr3[kh][M]=0;//�᫨ ��� ࠧ�鸞 �離� ����� ���� ��� � 0
          if((ZAGRUZKA==0)||(DISK!=0))
          {
            if(fr1[kh][0]==4)displaypathuch(kh);
            else displaypath(kh,M);//�᫨ �� ����㧪� -���ᮢ��� ����
          }
          vysv=1;//��⠭����� �ਧ���� ����祭�� ���������
          reza=1;
        }
      }
      else//�᫨ ��� ᫥��� ��⠭�����
      {
        if(fr3[kh][M]!=1) // �᫨ ࠭�� �� ��襭
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
    if(vysv==0&&ZAGRUZKA==0)time20sec(kh);//�᫨ ��� ����� ������ �� ��ꥪ��
Bbreak:;
  }
  return(reza);//������ �ਧ��� ������ ����� ������ �� ��ꥪ��
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
      if(kop==0)//���� ��� ���� ��������
      {
        //���� ��� ������ �� ������ �� � �� �������� � ������
				if((fr1[kh][1]<3)&&(fr1[kh][2]<3)&&((fr1[kh][4]&1)==1))
				{
					if(fr3[kh][M]!=0){vysv=1;reza=1;}
					krest(kh,M,0);
					l=l*2;
					continue;
				}
				if(fr3[kh][M]!=0)// � ��� ��� ����������
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
			else//���� ��� ���� ����������
			{
				if((fr1[kh][1]<3)&&(fr1[kh][2]<3)&&((fr1[kh][4]&1)==1))
				{
					if(fr3[kh][M]!=1){vysv=1;reza=1;}
					krest(kh,M,1);
					l=l*2;
					continue;
				}
				if(fr3[kh][M]!=1)//� ��� ��� �������
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
						sp_s=(fr1[kh][6]&0xff00)>>8;  //�������� ������ ��� ��
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
  for (jv=0;jv<Z;jv++)//�ன� �� �ᥬ ��ꥪ⠬ �����㯯�
  { kh=spkont[tester][jv];//����� ��।��� ��ꥪ�
    if(kh==1111) goto BReak;//�᫨ ��ꥪ� �� ᬮ����, � �ய�����
    if(fr1[kh][1]==9999)goto BReak;//�᫨ ��ꥪ� ���⮩, � �ய�����
    l=1; n=jv+4; //��⠭����� ���-��� � ��室���,����� �� ���� ��ࢮ�� ��ꥪ�
    for(M=0;M<=5;M++)// �ன� �� ��⠬ ����
    { kop=bufde[n]&l;//������� ���祭�� ��।���� ���
      if(kop==0)// �᫨ �� ��ꥪ�� �ந��襫 ��� ���
      { //�᫨ ����⨫� ��㯯���� ��� ��ꥪ⭮�
        if((fr1[kh][1]>=1000)&&(M<=1))
        {
          if((ZAGRUZKA==0)||(DISK!=0))
          { if(fr3[kh][M]!=0)reza=1;//�᫨ �� �� ��� ५� �뫮 ��� ⮪��
            fr3[kh][M+6]=fr3[kh][M];//��������� ࠭�� ����襥�� ���祭�� ��� ���
          }
          fr3[kh][M]=0;//��⠭����� ⥪�饥 ���祭��
          //�஢���� ���४⭮��� ��宦����� �������
          if((ZAGRUZKA==0)||(DISK!=0))
          test_deshifr(kh,M);
          goto kiv;
        }
      //����� ��� ��ꥪ⮢ �� ��㯯���� � �� ��ꥪ��� ५�
        if(fr3[kh][M]!=0)//�᫨ ��ꥪ� �� � ���ﭨ� 1
        { fr3[kh][M]=0; //��⠭����� ��� � 0
          if((ZAGRUZKA==0)||(DISK!=0))
          {vysv=1;reza=1;}  //��䨪�஢��� 䠪� ���������
        }
      }
      else //�᫨ �� ��ꥪ�� �ந��諠 ��⠭���� ���
      {
        //�᫨ �ࠡ�⠫� ��㯯���� ��� ��ꥪ⭮�
        if((fr1[kh][1]>=1000)&&(M<=1))
        {
          if((ZAGRUZKA==0)||(DISK!=0))
          { if(fr3[kh][M]!=1)reza=1;//��䨪�஢��� 䠪� ��������� ��ꥪ�
            fr3[kh][M+6]=fr3[kh][M];//��������� �।��饥 ���ﭨ� ���
          }
          fr3[kh][M]=1;
          if((ZAGRUZKA==0)||(DISK!=0))
          {test_deshifr(kh,M);vysv=1;reza=1;}
          goto kiv;
        }
      //����� ��� ��ꥪ⮢ �� ��㯯���� � �� ��ꥪ��� ५�
        if(fr3[kh][M]!=1)
        { fr3[kh][M]=1;
          if((ZAGRUZKA==0)||(DISK!=0))
          {vysv=1;reza=1;}
        }
      }
kiv:
      if((ZAGRUZKA==0)||(DISK!=0))
      { if((fr1[kh][1]==911)&&(vysv==1))//�᫨ �஡���� � �������
        { Pam(kh,M);
          vysv=0;
          vs=1;
        }
        //�� �����㦥��� �訡�� ࠡ��� ��室���� ����䥩�
        if((fr1[kh][1]>=1000)&&(vysv==1)&&(M>1))
        { dispdatch(kh,M);
          vysv=0;
          vs=1;
        }
        //��� ��ꥪ� KVV (����� �뢮��)
        if((fr1[kh][1]==11)&&(vysv==1))
        { kvv(kh,M);
          if(M>0){ vs=1; reza=1;}
          else { vs=0;reza=0;}
          vysv=0;
        }
        //��� ��ꥪ� �� �� ��⠢� KS
        if((fr1[kh][1]==13)&&(M==2))
        {
#ifdef KOL_SOO2
          if(kim==2) KOKS=KS2;
          else
#endif
          KOKS=KS1;
        }
        //�᫨ ����祭� ��������� �� ��ꥪ�� KS (���� �,��,�� ��� �����䠧�����)
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
    ;//���室 �� ᫥���騩 ��ꥪ� (�᫨ �� �� ��᫥����
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
      if(kop==0)//�᫨ ��� ���뢠����
      {
				if(fr3[kh][M]!=0)//�᫨ ��� �� ��⠭�����
				{ fr3[kh][M]=0;
					pooo[kh]=0;
					if((ZAGRUZKA==0)||(DISK!=0))displaysignal(kh,M);
					vysv=1;reza=1;
				}
			}
			else//�᫨ ��� ��⠭����������
			{ if(fr3[kh][M]!=1)//�᫨ ��� �� ��襭
				{ fr3[kh][M]=1;
					pooo[kh]=0;
					if(M<4)//�᫨ ��⠭���������� �� ��� ���뢠���� ᨣ���
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
			{ if(fr2[kh][8]!=0)sp=fr2[kh][8];//�᫨ ���� ��,����� ��� �����
				if(fr2[kh][3]!=0)//�᫨ ��� ᨣ���� ���� ��५�� � ���
				for(i_str=3;i_str<8;i_str++)
				{ if(fr2[kh][i_str]==0)break;//�᫨ ��।��� ��५�� ���
					str=fr2[kh][i_str]&0xfff;//������� ����� ��� ��५��
					p=(fr2[kh][i_str]&0xf000)>>12;//������� ⨯ ���몠���
					kod=(fr3[kh][0]|fr3[kh][2])*2;//�஢���� �����஢�
					kod=kod+(fr3[kh][1]|fr3[kh][3]);//�������� �������
					switch(p)//��४��祭�� �� ⨯� ���몠���
					{
						case 0: break;
						//�⭮� ��������
						case 2: if(fr1[kh][1]==0)//�᫨ ᨣ��� ���
										{
											if((kod==1)||(kod==3))//�᫨ �������� ᨣ��� �����
											{
												if(fr3[sp][1]==1)//�᫨ �� �������
												fr4[str][0]=fr4[str][0]|8;
											}
											else//�᫨ �������� ᨣ��� ������
											{
												if(fr3[sp][1]==0)//�᫨ �� ࠧ������
												fr4[str][0]=fr4[str][0]&0xfff7;
											}
										}
										break;
							//�⭮� ��
							case 3: if(fr1[kh][1]==0)//�᫨ ᨣ��� ���
											{
												if(kod!=0)//�᫨ �����-���� ᨣ��� �����
												{
													if(fr3[sp][1]==1)//�᫨ �� �������
													fr4[str][0]=fr4[str][0]|8;
												}
												else //�᫨ �� ᨣ���� �������
												{
													if(fr3[sp][1]==0)//�᫨ �� ࠧ������
													fr4[str][0]=fr4[str][0]&0xfff7;
												}
											}
											break;
							//���⭮� ��������
							case 4: if(fr1[kh][1]==1)//�᫨ ᨣ��� �����
											{
												if((kod==1)||(kod==3))//�᫨ �������� ᨣ��� �����
												{
													if(fr3[sp][1]==1)//�᫨ �� �������
													fr4[str][0]=fr4[str][0]|0x10;
												}
												else //�᫨ �������� ᨣ��� ������
												{
													if(fr3[sp][1]==0)//�᫨ �� ࠧ������
													fr4[str][0]=fr4[str][0]&0xffef;
												}
											}
											break;
							//���⭮� ��
							case 5: if(fr1[kh][1]==1)//�᫨ ᨣ��� �����
											{
												if(kod!=0)//�᫨ �����-���� ᨣ��� �����
												{
													if(fr3[sp][1]==1)//�᫨ �� �������
													fr4[str][0]=fr4[str][0]|0x10;
												}
												else //�᫨ �� ᨣ���� �������
												{
													if(fr3[sp][1]==0)//�᫨ �� ࠧ������
													fr4[str][0]=fr4[str][0]&0xffef;
												}
											}
											break;
							//�⭮� - ���⭮� �������
							case 6:   if((kod==1)||(kod==3))//�᫨ �������� ᨣ��� �����
												{
													if(fr3[sp][1]==1)//�᫨ �� �������
													fr4[str][0]=fr4[str][0]|0x18;
												}
												else //�᫨ �������� ᨣ��� ������
												{
													if(fr3[sp][1]==0)//�᫨ �� ࠧ������
													fr4[str][0]=fr4[str][0]&0xffe7;
												}

												break;
						//�⭮� -   ���⭮� ��
							case 7:   if(kod!=0)//�᫨ �� ᨣ��� �����
												{
													if(fr3[sp][1]==1)//�᫨ �� �������
													fr4[str][0]=fr4[str][0]|0x18;
												}
												else //�᫨ ᨣ���� �������
												{
													if(fr3[sp][1]==0)//�᫨ �� ࠧ������
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
      add(0,'�');
      SBROS_BIT_TEST_SOOB(0,bu[0][3]);
      prv[0]=0;
    }
#ifdef KOL_SOO2
    if((prv[1]==1)&&(knl==1))
    {
      /*outportb(0x2F8,0x62);*/
      add(1,'�');
      SBROS_BIT_TEST_SOOB(1,bu[1][3]);
      prv[1]=0;
    }
#endif
  }
}
//-----------------------------
//��楤�� ��뢠���� �� ������⢨� ��������� ��� ⥪�饣� ��ꥪ�
//�।�����祭� ��� ������� ����祭�� ��������� �� ��ꥪ⠬ � �������
//���ࢠ� �६��� ��᫥ �뤠� �������
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
		TIME_CC=1400L;//��� ᨣ����� - 80 ᥪ
	else 
		TIME_CC=360L; //��� ��㣨� ��ꥪ⮢ - 20 ᥪ
  
	if(pooo[numba]!=0l)//�᫨ ��� ��ꥪ� ����祭 ⠩���
  {
    vmv = fr1[numba][13] - 1;
    //���४�� � ��⮬ ��������� ��।� ��ꥪ⮢
    if(t_com[vmv]!=0l)
			pooo[numba] = t_com[vmv];
		
    vr = biostime(0,0l);  //��䨪�஢��� ⥪�饥 �६�
    if((vr - pooo[numba]) >= TIME_CC) //�᫨ ��諮 ����� ���������
    {
#ifdef KOL_SOO2
      if(flagoutmsg==12)//�᫨ ����� ᪢����� �������
      {
        if((fr1[numba][0]==2)&&(fr1[numba][1]==1))//�᫨ ����� �������

        {
          for(vmv=0;vmv<1;vmv++)//�ன� �� ����� ������⠬
          if(Skvo[vmv].B2_s==numba)//�᫨ �� ᨣ��� ��砫� ��ன ��������
          {
            fin_kom();//����� �������
            break;
          }
        }
        else //�᫨ ��� �������
        {
          for(vmv=1;vmv<2;vmv++) //�ன� �� ��� ������⠬
          if(Skvo[vmv].B2_s==numba)//�᫨ �� ᨣ��� ��砫� ��ன ��������
          {
            fin_kom();//����� �������
            break;
          }
        }
      }
#endif
      //zvuk_vkl(1,30);//���� ��㪮��� ᨣ���
      //if(fr1[numba][1]!=18)
			//	w(239,numba," ��� ��������� �� ��������");
      
			if(pooo[numba]!=0l)
				pooo[numba]=0l;//����� 䨪��� �६���
      
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
  //�᫨ �ᯮ����⥫쭠� ᬥ�� ���ࠢ����� 
  if((fr1[nemba][0]==2)&&( fr1[nemba][1]>=400)&&( fr1[nemba][1]<=600))
  {
    fr3[nemba][9]=0;//��� 䫠�� ������� 
    vtora=0;//��� �ਧ���� ��� �뤠� ��ன �������� ������� 
    if((nikuda==0)&&(klo==0)&&(help==0))
    {
      if((otv_kom==1)&&(i3==modi))home(modi);//����� �� ���� 
      t(0);//������ ��ப� ���ࠪ⨢� 
    }
    zabeg=0;//��� 䫠���
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
  fr3[nemba][9]=0;//��� 䫠�� �뤠� �������

}
/**********************************************************/
test_ra_fini(int nemba)
{
#ifdef NALAD  
  nom_func("351");
#endif  
  if((fr1[nemba][0]==3)||(fr1[nemba][0]==4))//�᫨ �� ��� ��
  if((fr1[nemba][1]>=200)&&(fr1[nemba][1]<=300))//��ꥪ� ࠧ����� (��)
  {
    fr3[nemba][9]=0;//����� ���� �������
    was[markery[fr1[nemba][5]][7]-10]=0;//����� 䫠� � ���ᨢ� ���
    if((klo==0)&&(nikuda==0)&&(help==0))//�᫨ ��⥬� � ���筮� ���ﭨ�
    {
      if((otv_kom==1)&&(i3==modi)&&(fr1[nemba][5]==modi))//�᫨ �� � ��થ� �� ��ꥪ�
      {
        t(0); //����� ���� ���ࠪ⨢�
        zalet=0;vtora=0;//����� 䫠��
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
  if(komanda2[j]==0)return;//�᫨ �� �뫮 ������� - �� �������஢���
  //�᫨ ������� �뤠�� ������� �� �������஢���
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
  if(komanda2[i]!=0)//�᫨ ��ꥪ� �� ������ �⮩��
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
  int str_l, //����� ������� ��
  str_p, //������ ������� ��
  sp_l,//����� ����� ��
  sp_p; //������ ����� ��
  str_l=(fr1[ob][3]&0xff00)>>8;//����� ����� �������
  str_p=fr1[ob][3]&0xff;//����� ������ �������
  sp_l=(fr1[str_l][6]&0xff00)>>8;//����� �� ��� ����� �������
  sp_p=(fr1[str_p][6]&0xff00)>>8;//����� �� ��� ������ �������
  if((fr3[str_l][0]==1)&&(fr3[str_l][1]==0))//���� ����� � �����
  {
    if((fr3[str_p][0]==1)&&(fr3[str_p][1]==0))//���� ������ � �����
    {
      fr3[sp_l][6]=0;
      fr3[sp_p][6]=0;
    }
    if((fr3[str_p][0]==0)&&(fr3[str_p][1]==1))//���� ������ � ������
    {
      fr3[sp_l][6]=1;//��������� �������� ����� ���
      fr3[sp_p][6]=0;
    }
  }
  else
    if((fr3[str_l][0]==0)&&(fr3[str_l][1]==1))//���� ����� � ������
    {
      if((fr3[str_p][0]==1)&&(fr3[str_p][1]==0))//���� ������ � �����
      {
        fr3[sp_l][6]=0;
        fr3[sp_p][6]=1;//��������� �������� ������ ���
      }
      if((fr3[str_p][0]==0)&&(fr3[str_p][1]==1))//���� ������ � ������
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
  if(param==0)//���� ������� 0
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
  //���� �������� 1
  if((fr3[str_l][0]==2)||(fr3[str_p][0]==2))
  {
    fr3[sp_l][BT]=1;
    fr3[sp_p][BT]=1;
    goto ris;
  }

  fr3[sp_l][BT]=1;
  fr3[sp_p][BT]=1;
  goto ris;
  if((fr3[str_l][0]==1)&&(fr3[str_l][1]==0))//���� ����� � �����
  {
    if((fr3[str_p][0]==1)&&(fr3[str_p][0]==0))//���� ������ � �����
    {
      if((fr3[sp_l][BT]!=1)||(fr3[sp_p][BT]!=1))vysv=1;
      fr3[sp_l][BT]=1;
      fr3[sp_p][BT]=1;
    }
    else//���� ������ �� � �����
    if((fr3[str_p][0]==0)&&(fr3[str_p][1]==1))//���� ������ � ������
    {
      if((fr3[sp_l][BT]==1)||(fr3[sp_p][BT]==0))vysv=1;
      fr3[sp_l][BT]=0;
      fr3[sp_p][BT]=1;
    }
    else //���� ������ ��� ��������
    {
      fr3[sp_l][BT]=1;
      fr3[sp_p][BT]=1;
    }
  }
  else //���� ����� �� � �����
    if((fr3[str_l][0]==0)&&(fr3[str_l][1]==1))//���� ����� � ������
    {
      if((fr3[str_p][0]==1)&&(fr3[str_p][1]==0))//���� ������ � �����
      {
        if((fr3[sp_l][BT]==0)||(fr3[sp_p][BT]==1))vysv=1;
        fr3[sp_l][BT]=1;
        fr3[sp_p][BT]=0;
      }
      else //���� ������ �� � �����
      if((fr3[str_p][0]==0)&&(fr3[str_p][1]==1))//���� ������ � ������
      {
        if((fr3[sp_l][BT]==0)||(fr3[sp_p][BT]==0))vysv=1;
        fr3[sp_l][BT]=1;
        fr3[sp_p][BT]=1;
      }
    }
    else //���� ����� ��� ��������
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
