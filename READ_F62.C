#include"bla.h"
#include<graphics.h>
#include<stdio.h>
#include<io.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
void card()
{
	int k,i,j,god,mes,den;
	struct ftime d1,d2;
	unsigned char STROKA[50],DAT[12],byt;

	nom_func("16");

	if(iqw>=446)return;
	if(klo==0){GraphMode=VGAHI;clscreen();}//если начало просмотра неиспр.УВК
	if((klaval==81)||(klaval==73)||(klaval==55))
	{
		kartina();//изображение "шапки" и картинки состояния УВК
		clear_half();
		shl();
	}
//$$$
	if(BEG_TIM[0]>48)
	{
		moveto(23*8,205);outtext(BEG_TIM);outtext(" - ");outtext(END_TIM);
	}

	klaval=-1;
	if(bil_bil==1)goto rd_down;//продолжаем читать
	if(bil_bil==2)goto rd_up;//продолжаем читать
	//начинаем читать
	if(DISK==0)
	{
		n_1=open("result\\oblom1.fix",O_RDWR|O_BINARY);
		n_2=open("result\\oblom2.fix",O_RDWR|O_BINARY);
	}
	else
	{
		n_1=open("disk\\oblom1.fix",O_RDWR | O_BINARY);
		n_2=open("disk\\oblom2.fix",O_RDWR |O_BINARY);
	}
	i=0;
	if(n_1>0)//если есть первый файл
	{
		number=read_str(n_1,STROKA,DAT);
		den=atoi(DAT);
		k=0;
		for(i=strlen(DAT)-4;i<strlen(DAT);i++)STROKA[k++]=DAT[i];
		STROKA[k]=0;
		god=atoi(STROKA);
		k=0;
		for(i=strlen(DAT)-7;i<strlen(DAT)-4;i++)
		if(DAT[i]=='-')continue;
		else STROKA[k++]=DAT[i];
		STROKA[k]=0;
		mes=atoi(STROKA);
		i=((god-2000)*12+mes)*30+den;

		strcpy(BEG_TIM,DAT);strcat(BEG_TIM," ");strcat(BEG_TIM,TIME);
	}
	j=0;
	if(n_2>0)//если есть второй файл
	{
		number=read_str(n_2,STROKA,DAT);
		den=atoi(DAT);
		k=0;
		for(j=strlen(DAT)-4;j<strlen(DAT);j++)STROKA[k++]=DAT[j];
		STROKA[k]=0;
		god=atoi(STROKA);
		k=0;
		for(j=strlen(DAT)-7;j<strlen(DAT)-4;j++)
		if(DAT[j]=='-')continue;
		else STROKA[k++]=DAT[j];
		STROKA[k]=0;
		mes=atoi(STROKA);
		j=((god-2000)*12+mes)*30+den;
		strcpy(END_TIM,DAT);strcat(END_TIM," ");strcat(END_TIM,TIME);
	}
	if((i>j)&&(n_1>0)&&(n_2>0))//если первый файл позже и есть оба
	{
		strcpy(BEG_TIM,END_TIM);//переназначить начало
		for(i=5;i<100;i++)
		{
			j=lseek(n_1,-i,2);//встать в конец первого файла
			read(n_1,&byt,1);
			if(byt==13)break;
		 }
		number=read_str(n_1,STROKA,DAT);
		strcpy(END_TIM,DAT);strcat(END_TIM," ");strcat(END_TIM,TIME);
	}
	else//если нет двух
		if(n_1>0)//если есть только первый
		{
			for(i=5;i<100;i++)
			{
				j=lseek(n_1,-i,2);//встать в конец первого файла
				read(n_1,&byt,1);
				if(byt==13)break;
			}
			number=read_str(n_1,STROKA,DAT);
			strcpy(END_TIM,DAT);strcat(END_TIM," ");strcat(END_TIM,TIME);
		}
		else
			if(n_2>0)//если есть только второй
			{
				strcpy(BEG_TIM,END_TIM);
				for(i=5;i<100;i++)
				{
					j=lseek(n_2,-i,2);//встать в конец первого файла
					read(n_2,&byt,1);
					if(byt==13)break;
				}
				number=read_str(n_2,STROKA,DAT);
				strcpy(END_TIM,DAT);strcat(END_TIM," ");strcat(END_TIM,TIME);
			}
			else //если нет файлов
			{
				setcolor(12);moveto(23*8,205);
				outtext("НЕТ ДАННЫХ");
				bil_bil=0;
				return;
			}
	setcolor(8);
//$$$
	moveto(23*8,205);outtext(BEG_TIM);outtext(" - ");outtext(END_TIM);

	if((n_1!=-1)&&(n_2!=-1))//если есть оба файла
	{
		if(filelength(n_1)>40000)//если первый файл более 40кб
		{
			if(filelength(n_2)>40000)//если второй файл более 40кб
			{
				getftime(n_1,&d1);
				getftime(n_2,&d2);
				//проверка того, что файл oblom1.fix создан раньше
				if(max(d1.ft_year,d2.ft_year)!=d1.ft_year)goto r2;
				else
					if(max(d1.ft_month,d2.ft_month)!=d1.ft_month)goto r2;
					else
						if(max(d1.ft_day,d2.ft_day)!=d1.ft_day)goto r2;
						else
							if(max(d1.ft_hour,d2.ft_hour)!=d2.ft_hour)goto r2;
							else goto r1;
			}
			else goto r2;
		}
		else goto r1;
	}
	else //если одного файла нет
	{
		if(n_1!=-1)goto r1;//если есть первый файл
		else goto r2;
	}
r1://чтение первого файла
  qf=n_1;
  lseek(qf,0l,0);
  goto rd_down;
r2://чтение второго файла
	qf=n_2;
  lseek(qf,0l,0);
rd_down:
	number=read_str(qf,STROKA,DAT);
		if(number==-1)//если файл исчерпан
	{ i=lseek(qf,0l,0);
		if((qf==n_1)&&(n_2>0))qf=n_2;
		else
			if((qf==n_2)&&(n_1>0))qf=n_1;
    iqw=446;
		vuhod();
		return;
	}
  iqw=iqw+10;
	if(iqw==436)vuhod();
	if(number>0)
	{
		setcolor(8);
		moveto(16,iqw);
		outtext(DAT);
		moveto(14*8,iqw);
		outtext(TIME);
		rashifr(number,iqw);
	}
	bil_bil=1;
	return;
rd_up:
	if(tell(qf)<1000L)//если стоим близко к началу файла
	{
		lseek(qf,0l,0);
		if((qf==n_1)&&(n_2>0))qf=n_2;
		else
			if((qf==n_2)&&(n_1>0))qf=n_1;
		i=lseek(qf,-1000l,2);
		if(i<0)lseek(qf,0l,0);
    else  while(byt!=13)read(qf,&byt,1);
    goto rd_down;
  }
  else
  {
  	i=lseek(qf,-1000l,1);
    while(byt!=13)read(qf,&byt,1);
    goto rd_down;
	}
}
//-----------------------
void rashifr(int number,int iqw)
{
	int duk;
	char kod[4];

	nom_func("262");

  setlinestyle(0,0,0);
	if(qf==n_1)setcolor(1);
	if(qf==n_2)setcolor(5);
  if(number==9000){moveto(24*8,iqw);outtext("НАЧАЛО РАБОТЫ");return;}
  else
    if((number>=9100)&&(number<9110))
    { moveto(24*8,iqw);number=number-9100;
      itoa(number+1,kod,10);strcat(kod,":");outtext(kod);
      outtext(" ком. перекл. компл.");
      return;
    }
    else
      if((number>=9200)&&(number<9210))
      { moveto(24*8,iqw);number=number-9200;
        itoa(number+1,kod,10);strcat(kod,":");outtext(kod);
        outtext(" объединение групп");
        return;
      }
      else
        if((number>=9300)&&(number<9310))
        { moveto(24*8,iqw);number=number-9300;
          itoa(number+1,kod,10);strcat(kod,":");outtext(kod);
          outtext(" перезап / объед");
          return;
        }
        else
          if((number>=9400)&&(number<9410))
					{ moveto(24*8,iqw);number=number-9400;
            itoa(number+1,kod,10);strcat(kod,":");outtext(kod);
            outtext(" перезапуск ст.");
            return;
          }
          else
            if((number>=8000)&&(number<8010))
            { moveto(24*8,iqw);number=number-8000;
              itoa(number+1,kod,10);strcat(kod,":");outtext(kod);
              fraza(8000);
              return;
            }
            else
            if((number>=8010)&&(number<8200))
            { moveto(24*8,iqw);duk=number/10;number=number%10;
							itoa(number+1,kod,10);strcat(kod,":");outtext(kod);
              fraza(duk*10);
              return;
            }
              if((number>=7000)&&(number<8000)){moveto(24*8,iqw);fraza2(number);}
              else
                if((number>=8300)&&(number<8310))
                { moveto(24*8,iqw);number=number-8300;
                  itoa(number+1,kod,10);strcat(kod,":");outtext(kod);
                  outtext("ошибка в ПЗУ пр. МПСУ");
                  return;
                }
                else
                  if((number>=8400)&&(number<8410))
                  { moveto(24*8,iqw);number=number-8400;
                    itoa(number+1,kod,10);strcat(kod,":");outtext(kod);
                    outtext("ошибка в ПЗУ БД МПСУ");
                    return;
                  }
									else
                    if(number==8450){moveto(24*8,iqw);outtext("ош. записи в файл");}
                    else
                      if((number>=4000)&&(number<4010))
                      { moveto(24*8,iqw);
                        itoa(number-3999,kod,10);strcat(kod,":");outtext(kod);
                        outtext("о.г. ");
                        for(bi=0;bi<=14;bi++)
                        if(mlu[bi]!=0)
                        { sbis[0]=0;sbis[1]=0;itoa(bi+1,sbis,10);
                          outtext(sbis);outtext(" ");
                        }
                        return;
                      }
                      else
                        if((number>=4010)&&(number<4020))
												{ moveto(24*8,iqw);
                          itoa(number-4009,kod,10);strcat(kod,":");outtext(kod);
                          outtext("обр.г. ");
                          for(bi=0;bi<=14;bi++)
                          if(mlv[bi]!=0)
                          { sbis[0]=0; sbis[1]=0;itoa(bi+1,sbis,10);
                            outtext(sbis);outtext(" ");
                          }
                          return;
                        }
                        else
													if((number>=4020)&&(number<4030))
													{ moveto(24*8,iqw);
														itoa(number-4019,kod,10);strcat(kod,":");outtext(kod);
														sbis[0]=0; sbis[1]=0; itoa(kot,sbis,10);
														outtext("ЭВМ:"); outtext(sbis);
														outtext(" М201.1 нет 0");
														moveto(51*8,iqw);
														outtext("разр.");
														for(bi=0;bi<=15;bi++)
														if(mly[bi]!=0)
														{ sbis[0]=0; sbis[1]=0;
															itoa(bi+1,sbis,10); outtext(sbis); outtext(", ");
														}
														return;
													}
													else
														if((number>=4030)&&(number<4040))
														{ moveto(24*8,iqw);
															itoa(number-4029,kod,10);strcat(kod,":");
															outtext(kod);
															sbis[0]=0;sbis[1]=0;itoa(kot,sbis,10);
															outtext("ЭВМ:");
															outtext(sbis);outtext(" М201.2 нет 0");
															moveto(51*8,iqw);
															outtext("разр.");
															for(bi=0;bi<=15;bi++)
															if(mlz[bi]!=48)
															{
																sbis[0]=0; sbis[1]=0;itoa(bi+1,sbis,10);
																outtext(sbis);outtext(", ");
															}
															return;
														}
														else
															if((number>=4040)&&(number<4050))
															{ moveto(24*8,iqw);
																itoa(number-4039,kod,10);strcat(kod,":");outtext(kod);
																sbis[0]=0;sbis[1]=0;itoa(kot,sbis,10);
																outtext("ЭВМ:");outtext(sbis);
																outtext("М201.3 нет 0");
																moveto(51*8,iqw);
																outtext("разр.");
																for(bi=0;bi<=15;bi++)
																if(mlc[bi]!=0)
																{ sbis[0]=0;sbis[1]=0;itoa(bi+1,sbis,10);
																	outtext(sbis);outtext(", ");
																}
																return;
															}
															else
															if((number>=4050)&&(number<4060))
															{ moveto(24*8,iqw);
																itoa(number-4049,kod,10);strcat(kod,":");outtext(kod);
																sbis[0]=0;sbis[1]=0;itoa(kot,sbis,10);
																outtext("ЭВМ:");outtext(sbis);
																outtext(" М201.4 нет 0");
																moveto(51*8,iqw);
																outtext("разр.");
																for(bi=0;bi<=15;bi++)
																if(mls[bi]!=0)
																{ sbis[0]=0;sbis[1]=0;itoa(bi+1,sbis,10);
																	outtext(sbis);outtext(", ");
																}
																return;
															}
															else
																if((number>=4060)&&(number<4070))
																{
																	moveto(24*8,iqw);
																	itoa(number-4049,kod,10);strcat(kod,":");outtext(kod);
																	outtext("сообщ.вых.интерф.МПСУ ");
																	k=0;
																	for(i_s=0;i_s<40;i_s++)STRoka[i_s]=0;
																	while(pako[kot][k]!=32)
																	{
																		STRoka[k]=pako[kot][k++];
																		if(k>=40)
																		{
																			strcpy(STRoka,"неизв.объект");
																			break;
																		}
																	}
																	moveto(52*8,iqw);
																	outtext(STRoka);outtext("-1");
																	return;
																}
																else
																	if((number>=4070)&&(number<4080))
																	{
																		moveto(24*8,iqw);
																		itoa(number-4059,kod,10);strcat(kod,":");
																		outtext(kod);
																		outtext("сообщ.вых.интерф.МПСУ ");
																		k=0;
//																		read_sode(qf,number,STRoka);
																		for(i_s=0;i_s<40;i_s++)STRoka[i_s]=0;
																		while((pako[kot][k]!=32)&&(k<40))k++;
																		if(k>=40)k=0;
																		i_s=0;
																		while(pako[kot][k]!=0)
																		{
																			STRoka[i_s++]=pako[kot][k++];
																			if(k>=40)
																			{
																				strcpy(STRoka,"неизв.объект");
																				break;
																			}
																		}
																		moveto(52*8,iqw);
																		outtext(STRoka);
																		outtext("-2");
																		return;
																	}
																	else
																		if((number>=4120)&&(number<4130))
																		{ moveto(24*8,iqw);
																			itoa(number-4119,kod,10);strcat(kod,":");outtext(kod);
																			sbis[0]=0;sbis[1]=0;itoa(kot,sbis,10);
																			outtext("ЭВМ:");outtext(sbis);
																			outtext(" М201.1 нет 1");
																			moveto(51*8,iqw);
																			outtext("разр.");
																			for(bi=0;bi<=15;bi++)
																			if(mly[bi]!=0)
																			{ sbis[0]=0;sbis[1]=0;itoa(bi+1,sbis,10);
																				outtext(sbis);outtext(", ");
																			}
																			return;
																		}
																		else
																		 if((number>=4130)&&(number<4140))
																		 { moveto(24*8,iqw);
																			 itoa(number-4119,kod,10);strcat(kod,":");outtext(kod);
																			 sbis[0]=0;sbis[1]=0;itoa(kot,sbis,10);
																			 outtext("ЭВМ:");outtext(sbis);
																			 outtext(" М201.2 нет 1");
																			 moveto(51*8,iqw);
																			 outtext("разр.");
																			 for(bi=0;bi<=15;bi++)
																			 if(mlz[bi]!=0)
																			 { sbis[0]=0;sbis[1]=0;itoa(bi+1,sbis,10);
																				outtext(sbis);outtext(", ");
																			 }
																			 return;
																		 }
																		 else
																		 if((number>=4140)&&(number<4150))
																		 { moveto(24*8,iqw);
																			 itoa(number-4119,kod,10);strcat(kod,":");outtext(kod);
																			 sbis[0]=0;sbis[1]=0;itoa(kot,sbis,10);
																			 outtext("ЭВМ:");outtext(sbis);
																			 outtext(" М201.3 нет 1");
																			 moveto(51*8,iqw);
																			 outtext("разр.");
																			 for(bi=0;bi<=15;bi++)
																			 if(mlc[bi]!=0)
																			 { sbis[0]=0;sbis[1]=0;itoa(bi+1,sbis,10);
																				outtext(sbis);outtext(", ");
																			 }
																			 return;
																		 }
																			else
																			{
																				moveto(52*8,iqw);
																				if(fr1[number][13]==1) outtext("I:");
																				else outtext("II:");
																				if(fr1[number][0]==1)
																				{
																					for(i_s=0;i_s<40;i_s++)STRoka[i_s]=0;
																					i_s=0;
																					while(pako[number][i_s]!=':')
																					{
																						STRoka[i_s]=pako[number][i_s];
																						i_s++;
																						if(i_s>=40)
																						{
																							strcpy(STRoka,"неизв.объект");
																							break;
																						}
																					}
																					outtext(STRoka);
																				}
																				else outtext(pako[number]);
                            		        return;
                                  }
  }
//-----------------------------------------------
int read_str(int hndl,unsigned char STROKA[50],unsigned char DAT[12])
{
	int i,number,j;
	for(i=0;i<50;i++)
	{
		j=read(hndl,&STROKA[i],1);
		if(eof(hndl))return(-1);
		if(j<=0)return(-1);
		if(STROKA[i]<=13)i--;
		if(STROKA[i]==32)break;
	}
	STROKA[i]=0;
	if(i<12)strcpy(DAT,STROKA);
	for(i=0;i<50;i++)
	{
		read(hndl,&STROKA[i],1);
		if((STROKA[i]==32)&&(i>2))break;
	}
	STROKA[i]=0;
	if(i<25)strcpy(TIME,STROKA);
	for(i=0;i<50;i++)
	{
		read(hndl,&STROKA[i],1);
		if((STROKA[i]==32)&&(i>2))break;
		if(STROKA[i]==13)break;
	}
	STROKA[i]=0;
	number=atoi(STROKA);
	read_sode(hndl,number,STROKA);
	return(number);
}
