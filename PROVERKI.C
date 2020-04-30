#include"bla.h"
#include <bios.h>
int ZA_SI,pusya;
//---------------------------------------------------
int test_time()
{
#ifdef NALAD  
  nom_func("354");
#endif  
  second_time=biostime(0,0);
  if((second_time-first_time)>=TIME_FIX)
  { Init_TEST_SOOB(0);//сбросить ячейки 10-минутной новизны
    Init_TEST_SOOB(1);
    return(1);
  }
	else return(0);
}
//------------------------------------------------------
int avto_marsh(int kkp)
//проверка возможности задания маршрута автодействия номер kkp
{ int ij,SEKC,tst;
	unsigned char aa[2];
#ifdef NALAD
	nom_func("12");
#endif
	nach_avto=Avto_el[kkp].Beg_s;//взять начало маршрута
	end_avto=Avto_el[kkp].End_s;//взять конец маршрута
	SEKC=Avto_el[kkp].N_sek; //взять защитный участок
	ij=0;
	while(Avto_el[kkp].Elems[ij]!=nach_avto)ij++; //найти начало автомаршрута
	if((fr1[nach_avto][1]==0)&&(cha==1))//если четный сигнал и четное автодействие
	{ //если сигнал начала еще не закрыт, то выйти
		if((fr3[nach_avto][0]!=0)||(fr3[nach_avto][1]!=0)||
		(fr3[nach_avto][2]!=0)||(fr3[nach_avto][3]!=0))goto end;
		for(ij=0;ij<=K_EL;ij++)//если закрыт двигаться по трассе автодействия
		{
/*			aa[0]=ij+48;aa[1]=0;
			setcolor(14);moveto(0,ij*8);outtext(aa);
			if((ij==14)&&(fr3[Avto_el[kkp].Elems[ij]][0]==0)&&
			(fr3[Avto_el[kkp].Elems[ij]][1]==0))
			aa[0]=48;
			*/
			//если элемент не в норме
			tst=test_elem(Avto_el[kkp].Elems[ij],2);
			if(tst==1)goto end;
			if(tst==7)//надо включить РОН/РОЧ
			{ knopa(fr1[Avto_el[kkp].Elems[ij]][6]&0xfff,2);
        klaval=13;
        goto end;
      }

			if(Avto_el[kkp].Elems[ij]==SEKC)
			break;//защитная секция - выйти
    }
    if(MAR_GOT[fr1[nach_avto][13]-1]==64)goto end;//стойка занята - выйти
    return(1);//все в порядке - выход
  }
  if((fr1[nach_avto][1]==1)&&(na==1))//нечетные сигнал и автодействие
  {
    //если сигнал начала не закрыт, то выйти
    if((fr3[nach_avto][0]!=0)||(fr3[nach_avto][1]!=0)||
    (fr3[nach_avto][2]!=0)||(fr3[nach_avto][3]!=0))goto end;
    for(ij=0;ij<=K_EL;ij++)//сигнал закрыт - двигаться по трассе автодействия
    {
      //если элемент не в норме
      tst=test_elem(Avto_el[kkp].Elems[ij],1);
      if(tst==1)goto end;
      if(tst==7)//если надо включить РОН/РОЧ
      {
        knopa(fr1[Avto_el[kkp].Elems[ij]][6]&0xfff,1);
        klaval=13;
        goto end;
      }
			if(Avto_el[kkp].Elems[ij]==SEKC)
			break;//защитная секция - выйти
    }
    if(MAR_GOT[fr1[nach_avto][13]-1]==64)goto end;//стойка занята - выйти
    return(1);//все в порядке - выйти
  }
end:
  if((fr1[Avto_el[kkp].Elems[ij]][0]==7)&&(nach_avto==91))
  tst=ij;
  return(0); //нельзя включать автодействие
}
//-----------------------------------------------------------
int find_end()
{
  int mo=end_marsh;
#ifdef NALAD
  nom_func("58");
#endif
  //если концом маршрута является попутный сигнал, то оставить его
  if(fr1[end_marsh][1]==fr1[nach_marsh][1]) return(end_marsh);
  else
  while(1)
  {
    if((mo<0)||(mo>kol_OSN))return(9999); //если поиск вывел за пределы базы
    if(fr1[mo][0]==2)//если вышли на сигнал
    {
      if(fr1[mo][1]!=fr1[nach_marsh][1])goto konec;//если сигнал встречный
      else//если сигнал попутный
      {
        if(mane==0) //если маршрут поездной
        { //если маршрут четный и у сигнала есть конец четного поездного
          if((fr1[nach_marsh][1]==0)&&((fr1[mo][11]&64)==64))
          {
            if(fr1[nach_marsh][1]==1)mo--;//вернуться на шаг
            else mo++;
            return(mo);
          }
          //если маршрут нечетный и у сигнала есть конец нечетного поездного
          if((fr1[nach_marsh][1]==1)&&((fr1[mo][11]&16)==16))
          {
            if(fr1[nach_marsh][1]==1) mo--;//вернуться на шаг
            else mo++;
            return(mo);
          }
        }
      }
    }
konec:
    if(fr1[nach_marsh][1]==1) mo++;//продвинуться дальше
    else mo--;
    if(mane!=0)//если маршрут маневровый
    {
      if((fr1[mo][0]!=6)&&(fr1[mo][0]!=7))return(mo);
    }
    else if((fr1[mo][0]==5)&&(fr1[mo][7]<8888))return(mo);
  }
  return(mo);
}
//--------------------------------------------------------
form_kom_knopka(int nnn,int inver )
{
  //процедура формирования команды для индивидуальной выдачи на объекты,
  //управляемые экранными кнопками
  int koda=0;
#ifdef NALAD  
  nom_func("75");
#endif      
  koda=form_koda(nnn,inver);//получение кода команды
  if(koda==9999) return;//если получение кода не состоялось - выход
  point=nnn;//установить номер точки для выдачи команды
  if(form_kosig(koda)==1) return;//если формирование команды не удалось - выход
  buf_ko[9]=check_sum(buf_ko);//добавить контрольную сумму
  pooo[nnn]=biostime(0,0L);//зафиксировать время выдачи
  flagoutmsg=1;//установить флаг-требование на передачу в ТУМС
}
//----------------------------------------------------------------
form_kom_nemarsh(int nnn)
{
  //процедура формирования команды для индивидуальной выдачи на объекты,
  //управляемые экранными кнопками
  int koda=0,nobi=0;
  int nomer,podgr,i18,j18,SDVIG=0,FN=0,FIN=0,n=0;
#ifdef NALAD  
  nom_func("76");
#endif      
  nobi=fr1[nnn][11];
  switch(nobi)
  {
    case 0:   if(fr3[nnn][nobi]==0)koda='A';
              else koda='M';
              break;
    case 1:   if(fr3[nnn][nobi]==0)koda='B';
              else koda='N';
              break;
    default: return;
  }
  point=nnn;//установить номер точки для выдачи команды
  n=point;//зафиксировать объект выбранный оператором
  if(fr1[n][13]==1)//если объект из первой стойки
  {
    buf_ko[1]=ZAGO_MPSU(0x61);//заголовок 
    SDVIG=STR1;FN=0;FIN=SIG1;//сдвиг и граница
  }
#ifdef KOL_SOO2
  else//для второй стойки - аналогично
  {
    buf_ko[1]=ZAGO_MPSU(0x62);
    SDVIG=STR2;FN=SIG1;FIN=FN+SIG2;
  }
#endif
  nomer=9999;
  //пройти по подгруппам + пройти по объектам подгруппы
  if((koda=='A')||(koda=='B'))
  { buf_ko[2]='d'; nomer=9999; n=fr1[nnn][2]; //взять первый сигнал
    //пройти по подгруппам + пройти по объектам подгрупп
    for (i18=FN;i18<FIN;i18++)for(j18=0;j18<=4;j18++)
    if(spsig[i18][j18]==n) //если найден объект
    { podgr=podgruppa[i18+SDVIG-FN];//зафиксировать подгруппу
      nomer=j18; //зафиксировать порядковый номер объекта в подгруппе
      break;
    }
    if(nomer==9999) return; //если не найден объект - выйти
    buf_ko[3]=podgr;
    buf_ko[4]='@'+nomer;
    n=fr1[nnn][7];//взять второй сигнал
    //пройти по подгруппам + пройти по объектам подгруппы
    nomer=9999;
    for (i18=FN;i18<FIN;i18++)for(j18=0;j18<=4;j18++)
    if(spsig[i18][j18]==n) //если найден объект
    { podgr=podgruppa[i18+SDVIG-FN];//зафиксировать подгруппу
      nomer=j18; //зафиксировать порядковый номер объекта в подгруппе
      break;
    }
    if(nomer==9999)return;
    buf_ko[5]=podgr;buf_ko[6]='@'+nomer;buf_ko[7]=124;buf_ko[8]=124;
  }
  if(koda=='N')
  { buf_ko[2]='E';//заполнить группу
    nomer=9999;
    for (i18=FN;i18<FIN;i18++)for(j18=0;j18<=4;j18++)
    if(spsig[i18][j18]==n) //если найден объект
    { podgr=podgruppa[i18+SDVIG-FN];//зафиксировать подгруппу
      nomer=j18; //зафиксировать порядковый номер объекта в подгруппе
      break;
    }
    if(nomer==9999)return;
    for (j18=0;j18<=4;j18++)
    {
      buf_ko[j18+4]=124;// для прочих вписать заполнитель
      if(j18==nomer)buf_ko[j18+4]=koda;//для найденного объекта - заполнить код
    }
    buf_ko[3]=podgr; // заполнить подгруппу
  }
  buf_ko[9]=check_sum(buf_ko);//добавить контрольную сумму
  pooo[nnn]=biostime(0,0L);//зафиксировать время выдачи
  flagoutmsg=1;//установить флаг-требование на передачу в ТУМС
}
//--------------------------------------------------------------
form_kom_nk_chk(int nnn)
{
  int koda=0;
#ifdef NALAD  
  nom_func("77");
#endif      
  koda=form_koda(nnn,0);
  point=nnn;
  if(form_kosig(koda)==1) return;
  buf_ko[9]=check_sum(buf_ko);
  pooo[nnn]=biostime(0,0);
  flagoutmsg=1;
}
//--------------------------------------------------------------
form_kom_prkl(int nno)
{ //процедура формирования команды для переключения комплектов ТУМС
  int i11,n=0;
#ifdef NALAD  
  nom_func("78");
#endif      
  n=nno;
  if(fr1[n][13]==1)///если переключается первая стойка
  {
    buf_ko[1]=ZAGO_MPSU(0x61);//сформировать заголовок
    slom_interf(11200);//зафиксировать на диске
    buf_ko[3]=kompl_1;//установить байт подгруппы
  }
#ifdef KOL_SOO2
  else//если переключается вторая стойка
  {
    buf_ko[1]=ZAGO_MPSU(0x62);//установить заголовок
    slom_interf(11201);//записать на диск
    buf_ko[3]=kompl_2;//записать байт подгруппы
  }
#endif
  buf_ko[2]='L';//установить код группы
  for (i11=7;i11<=8;i11++)buf_ko[i11]=124;//записать заполнители
  buf_ko[5]='D';//записать код команды
  buf_ko[4]=124;//записать заполнители
  buf_ko[6]=124;//записать заполнители 
  buf_ko[9]=check_sum(buf_ko);//дополнить команду контрольной суммой
  pooo[nno]=biostime(0,0L);//зафиксировать время 
  flagoutmsg=1;//выставить флаг-требование на передачу в ТУМС
  PRKL=1;//установить признак выполнения переключения
}
//------------------------------------------------------------
form_kom_smen(int nnn)
{ //процедура формирования команды для смены направления 
  int koda=0;
#ifdef NALAD  
  nom_func("80");
#endif      
  if(fr1[nnn][11]==1) koda='B';  //если управление сменой направления в ДПС 
  else
    if(fr1[nnn][11]==0) koda='A';//если управление сменой направления в ДМС 
    else return;
  point=nnn; //задать объект
  if(form_kosig(koda)==1) return;//если формирование команды неудачное - выход 
  buf_ko[9]=check_sum(buf_ko);//дополнить команду контрольной суммой
  pooo[nnn]=biostime(0,0L);// зафиксировать время выдачи
  flagoutmsg=1;//выставить флаг - требование на передачу в ТУМС
}
//---------------------------------------------------------
#ifdef OGRAD
kom_ograd(int ob_sogl)
{ int ob_zapros,ob_ogr,bit_zapros,bit_sogl,bit_ogr,put;
  put=fr1[ob_sogl][4];
  ob_zapros=fr1[ob_sogl][2]; bit_zapros=fr1[ob_zapros][3];
  ob_ogr=fr1[ob_sogl][3]; bit_ogr=fr1[ob_ogr][5];
  bit_sogl=fr1[ob_sogl][12];
  if(nikuda==1||klo==1||help!=0)return;
  if((fr3[ob_zapros][bit_zapros]==1)/* если есть запрос ограждения */
  &&(fr3[ob_ogr][bit_ogr]==0)/* и ограждение не установлено */
  &&(fr3[ob_sogl][bit_sogl]==0))/* и согласие не установлено */
  // ВЫДАТЬ СОГЛАСИЕ НА ОГРАЖДЕНИЕ ПУТЬ ##?
  { vopros(1,put,105,"?");oppp=1;zapretvybora=1;return;}
  else
  if(fr3[ob_ogr][bit_ogr==1])
  // ОГРАЖДЕНИЕ УСТАНОВЛЕНО ПУТЬ ##
  { w(141,put,"");oppp=0;zvuk_vkl(1,10);home(modi);return;}
  else
    if(fr3[ob_sogl][bit_sogl]==1)
    // СОГЛАСИЕ НА ОГРАЖДЕНИЕ ВЫДАНО,ПУТЬ ##
    {w(34,put,"");oppp=0;zvuk_vkl(1,10);home(modi);return;}
    else
      if(fr3[ob_zapros][bit_zapros]==0)
      // ЗАПРОСА НА ОГРАЖДЕНИЕ НЕ БЫЛО,ПУТЬ ##
      { w(155,put,"");oppp=0;zvuk_vkl(1,10);home(modi);return;}
}
#endif
//-------------------------------------------------------
koni()
{
#ifdef NALAD  
  nom_func("130");
#endif          
  vopros(1,9999,121,"");//УКАЖИТЕ КОНЕЦ МАРШРУТА
  zapretvybora=0;first_col=0;manevro=0;
}
//--------------------------------------------------
int may_be(int ako,int nap_dvi)
{ int ii,pred;
#ifdef NALAD  
  nom_func("166");
#endif       
  //трассировка маршрута для маршрутного управления
  //предварительная очистка трассы
  //END=find_end();
  if(TEST==0)//если формируется задаваемый маршрут, то очистить основную трассу
  for(ukaz_trass=0;ukaz_trass<100;ukaz_trass++)
  {
    trassa[ukaz_trass]=0xFFFF;
  }
  else//если формируется эталонный маршрут,то очистить эталонную трассу
  for(ukaz_trass=0;ukaz_trass<100;ukaz_trass++)trassa_osn[ukaz_trass]=0xFFFF;
  ukaz_trass=0;//указатель объекта в начало трассы
  if(TEST==1)//если формируется эталонный маршрут, то взять основной конец 
  goto aa;//уйти на цикл трассировки
  half_marsh=nach0_marsh;
  if(half_marsh>0&&ZAHOD==0)//если задается вариантный маршрут 
  {
    if(half_marsh>kol_OSN)half_marsh=fr1[half_marsh][2];//взять вариантную
    nach0_marsh=end_marsh;//запомнить основной конец 
    END=half_marsh;//вариантную точку назначить концом
    half_marsh1=half_marsh;//запомнить промежуточную точку
    NE=fra[END][0];//взять номер блок-линии конца 
    NM=fra[nach_marsh][0];//взять номер блок-линии начала
    ZAHOD=1;//флаг захода установит в 1
  }
aa:
  while(1)//"бесконечный" цикл трассировки 
  {
    if(ako==END)//если дошли до конца маршрута
    { if(TEST==0)trassa[ukaz_trass++]=ako;//запомнить элемент трассы
      else trassa_osn[ukaz_trass++]=ako;
      if(TEST==1)return(0);
      if(END!=half_marsh)//если конец не является промежуточным
      { if(tst_sigogo(ako)==0)return(0);//если тест пройден можно  задавать
        else return(1); //иначе нельзя
      }
      else//если конец промежуточный
      { ukaz_trass--;
        END=nach0_marsh;//установить основной конец
        half_marsh=0;//очистить для дальнейшего движения по главному направлению
        NE=fra[END][0];//запомнить блок-линию основного конца
      }
    }
    if((fr1[ako][0]==7)||   //если попали на ДЗ или
    ((fr1[ako][0]>1)&&(fr1[ako][0]<4)))//на сигнал или СП
    { if(TEST==0)trassa[ukaz_trass++]=ako;//зафиксировать в трассе и пройти далее
      else trassa_osn[ukaz_trass++]=ako;
      pred=ako;
      if((fr1[nach_marsh][3]!=7)||(fr1[end_marsh][3]!=7))
      {
	      if((fr1[ako][0]==2)&&(fr1[ako][2]!=0)&&(fr1[ako][1]==nap_dvi))
  	    if(ukaz_trass!=1)
				goto revers;
      }
      if(nap_dvi==0) ako--;
      else ako++;
      if(ako<0)return(1);
    }
    else
    if(fr1[ako][0]==4)//если попали на УП
    {
      if(nap_dvi==1&&fr1[ako][4]==1)goto revers;//вернутьcя к послед. стрелке
      //если направление четное и есть граница станции в четном направлении

      if(nap_dvi==0&&fr1[ako][3]==1)goto revers;//вернуться к послед. стрелке

      if(TEST==0)trassa[ukaz_trass++]=ako;//зафиксировать в трассе и пройти далее
      else trassa_osn[ukaz_trass++]=ako;
      pred=ako;
       if(nap_dvi==0) ako--;
      else ako++;
       if(ako<0)return(1);
    }
    else
    if(fr1[ako][0]==5)//если попали на путь
    { if(TEST==0)trassa[ukaz_trass++]=ako;//взять следующий элемент в трассу
      else trassa_osn[ukaz_trass++]=ako;
      if((mane==1)||(manevr==1))//если идем от маневрового или хотим маневровый
      if(ako!=END)//если не дошли до конца
      if((ako==end_marsh-1&&//если точно перед концом маршрута
      nap_dvi==1)||(ako==end_marsh+1&&nap_dvi==0))
      if(fr1[nach_marsh][1]==fr1[end_marsh][1])//если начало и конец одного направления
      if(fr1[ako][1]==0&&fr1[ako][2]==0)//нет границы станции с обеих сторон
      { w(100,999,"");//НЕВОЗМОЖЕН МАНЕВРОВЫЙ МАРШРУТ ЧЕРЕЗ ПУТЬ
        return(2);
      }
      //если участок приближения
      if(fr1[ako][7]!=9999)goto revers;
      //если напр.нечетное и есть граница станции в нечетном направлении
      if(nap_dvi==1&&fr1[ako][1]==1)goto revers;//вернутьcя к послед. стрелке
      //если направление четное и есть граница станции в четном направлении
      if(nap_dvi==0&&fr1[ako][2]==1)goto revers;//вернуться к послед. стрелке
      if(fra[ako][0]==NE)//если находимся на блок-линии конца
      {
aga:    if(TEST==0)trassa[ukaz_trass++]=ako;//то,запомнить элемент и продвинуться далее
        else trassa_osn[ukaz_trass++]=ako;
        pred=ako;
        if(nap_dvi==0) ako--;
        else ako++;
        if(ako==0)return(1);
        if(fra[ako][0]!=fra[pred][0])return(1);
      }
      else//если не находимся на блок-линии конца
      {
        if(uprav==1&&//если управление маршрутное и...
        ((fr1[nach_marsh][13]!=fr1[end_marsh][13])||(skoko_stoek==1)))//начало и конец в разных ТУМС
        { pred=ako;
          if(nap_dvi==0) ako--;//сделать шаг вперед
          else ako++;
          if(ako==0)return(1);
          if(fra[ako][0]!=fra[pred][0])return(1);
        }
        else //иначе
        {
revers:   if(TEST==0)
          {
            while((fr1[trassa[ukaz_trass]][0]!=1)||   //найти пройденный элемент-стрелку
            (fr3[trassa[ukaz_trass]][6]!=1)||
            (nap_dvi!=fr1[trassa[ukaz_trass]][7]))//с входом по маршруту
            { if(fr3[trassa[ukaz_trass]][6]==2)//если по стрелке было 2 прохода
              fr3[trassa[ukaz_trass]][6]=0;//сброс счета проходов
              trassa[ukaz_trass]=0xFFFF;//исключить из трассы
              ukaz_trass--;//вернуться на предыдущий
              if(ukaz_trass==0)return(1);
              if(trassa[ukaz_trass]==nach_marsh)return(1);//если вышли в начало - нет маршрута
            }
          }
          else
          { while((fr1[trassa_osn[ukaz_trass]][0]!=1)||  //найти пройденный элемент-стрелку
            (fr3[trassa_osn[ukaz_trass]][6]!=1)||
            (nap_dvi!=fr1[trassa_osn[ukaz_trass]][7]))//с входом по маршруту
            { if(fr3[trassa_osn[ukaz_trass]][6]==2)//если по стрелке было 2 прохода
              fr3[trassa_osn[ukaz_trass]][6]=0;//сброс счета проходов
              trassa_osn[ukaz_trass]=0xFFFF;//исключить из трассы
              ukaz_trass--;//вернуться на предыдущий
              if(ukaz_trass<=0)return(1);
              if(trassa_osn[ukaz_trass]==nach_marsh)return(1);//если вышли в начало - нет маршрута
            }
          }
          if(TEST==0)ako=trassa[ukaz_trass];//запомнить объект, на котором остановились
          else ako=trassa_osn[ukaz_trass];
        }
      }
    }
    else//если попали не на путь
    { r=nap_dvi;
      if(TEST==0)trassa[ukaz_trass++]=ako;//взять следующий элемент в трассу
      else trassa_osn[ukaz_trass++]=ako;
			switch(fr1[ako][0])
      {
        case 1: ako=strelka(ako,nap_dvi);break;//если стрелка - пройти через нее
        case 6: //если переход и на него вышли по строке
                if(TEST==0)//если трассируется задаваемый маршрут
								{
									if((fr1[trassa[ukaz_trass-2]][0]!=6)&&
									(fra[trassa[ukaz_trass-2]][0]==fra[ako][0]))//если вышли по строке
									ako=fr1[ako][1];//следующий элемент по переходу
									else //если вышли со стрелки или перехода (с другой строки)
									{ pred=ako;
										if(nap_dvi==0) ako--;//пройти на следующий по направлению
										else ako++;
										if(ako==0)return(1);
										if(fra[ako][0]!=fra[pred][0])return(1);
									}
								}
								else//если трассируется эталонный
								{ if((fr1[trassa_osn[ukaz_trass-2]][0]!=6)&&
									(fra[trassa_osn[ukaz_trass-2]][0]==fra[ako][0]))//если вышли по строке
									ako=fr1[ako][1];//следующий элемент по переходу
									else //если вышли со стрелки или перехода (с другой строки)
									{ pred=ako;
										if(nap_dvi==0) ako--;//пройти на следующий по направлению
										else ako++;
										if(ako==0)return(1);
										if(fra[ako][0]!=fra[pred][0])return(1);
									}
								}
								break;

        default: return(1); //если нет такого элемента - маршрут невозможен
      }
      nap_dvi=r;
    }

    if(ako<0)//если вышли за пределы базы
    { if(TEST==0)for(ukaz_trass=ukaz_trass;ukaz_trass>=0;ukaz_trass--)trassa[ukaz_trass]=0;
      else for(ukaz_trass=ukaz_trass;ukaz_trass>=0;ukaz_trass--)trassa_osn[ukaz_trass]=0;
      return(1);//маршрут невозможен
    }
  }
}
//--------------------------------------------------
//процедура набора цепочки элементов при раздельном открытии сигнала 
otkrsi()
{
  int napa,Snext,moni,Spred;
#ifdef NALAD
  nom_func("209");
#endif
  napa=fr1[point][1];//направление маршрута
  if((manevro==1)||(mane==1)) moni=1;//признак того,что хотим открыть маневровый
  else moni=0;
  ZA_SI=0;
  Spred=point;//предыдущий и следующий элемент устанавливаем вместе
  Snext=point; //на текущую точку=выбранный объект
  trassa[ukaz_trass++]=Snext;//запомнить текущую точку
  if(napa==0) Snext--;//если направление четное, идем по базе назад
  else Snext++;//иначе вперед
  while(1)//бесконечный цикл
  {
    trassa[ukaz_trass]=Snext;//запоминаем следующий эл-т
    switch (fr1[Snext][0])//переключатель по типу объекта
    {
      case 5: if((mane==1)||(manevro==1)||(fr1[Snext][7]!=9999))return;
              else
              {
                if((fr1[Snext][1]==1)&&(fr1[Snext][2]==1))return;
                if((fr1[Snext][1]==1)&&(napa==1))return;
                if((fr1[Snext][2]==1)&&(napa==0))return;
                Spred=Snext;//совмещаем указатели пред./след.
                if(napa==0) Snext--;//если направление четное-идем назад
                else Snext++;//для нечетного вперед
                break;
              }
      case 7: Spred=Snext;// если ДЗ, то совмещаем указатели пред./след.
              if(napa==0) Snext--;//если направление четное-идем назад
              else Snext++;//для нечетного вперед
              break;
      case 3: //if(ZA_SI==1)//если СП и был проход за сигнал
              //если открываем поездной и нет стрелки в пути
              //if((moni==0)&&(s_v_p==0)) return;//то выйти
							//если есть признак корыта
              Spred=Snext;//иначе перейти на следующий
              if(napa==0) Snext--;
              else Snext++;
               break;
      case 4: if((fr1[Snext][3]==1)&&(fr1[Snext][4]==1))return;
							//если направление маршрута четное и УП на четной границе
              if((napa==0)&&(fr1[Snext][3]==1))return;
              if((napa!=0)&&(fr1[Snext][4]==1))return;
              Spred=Snext;//иначе перейти к следующему
              if(napa==0) Snext--;
              else Snext++;
              break;
strelo:
      case 1: if(fr3[Snext][0]==fr3[Snext][1]) return;//если стрелка без контроля-выйти
              //если пред. не стрелка и не переход
              if((fr1[Spred][0]!=1)&&(fr1[Spred][0]!=6))
              {
                Spred=Snext;
                // если вход на стрелку не соответствует направлению
                if(fr1[Snext][7]!=fr1[point][1])
                {
                  if(napa==0) Snext--;//пройти на следующий элемент
                  else Snext++;
                }
                //если вход на стрелку по направлению движения
                else
                {
                  if(fr1[Snext][1]==1)//если по стрелке переход по плюсу прямой
                  {
                    if((fr3[Snext][0]==1)&&(fr3[Snext][1]==0))//стрелка в плюсе 

                      if(napa==0) Snext--;//перейти на следующий объект
                      else Snext++;
                    else //если стрелка в минусе
                    {
                      FLAG_PO=1;//установить флаг поворота
                      trassa[ukaz_trass++]=Snext;
                      Snext=poisk_ras(fr1[Snext][2],Snext);//найти объект за ответвлением
                      FLAG_PO=0;//сбросить флаг поворота
                    }
                  }
                  else //переход по отклонению прямой
                  {
                    if((fr3[Snext][0]==0)&&(fr3[Snext][1]==1))//стрелка в минусе
                      if(napa==0) Snext--;//перейти на следующий объект
                      else Snext++;
                    else //если стрелка в плюсе
                    {
                      FLAG_PO=1;//установить флаг поворота
                      trassa[ukaz_trass++]=Snext;
                      Snext=poisk_ras(fr1[Snext][2],Snext);//найти объект за поворотом
                      FLAG_PO=0;//сбросить флаг поворота
                    }
                  }
                }
							}
              else//если предшествует стрелка или переход
              {
                Spred=Snext;
                if(fr1[Snext][7]!=fr1[point][1])
                //если вход на стрелку не по направлению
                {
                  if(napa==0) Snext--;//пройти на следующий объект
                  else Snext++;
                }
                else//если вход на стрелку по направлению
                {
                  if(fr1[Snext][1]==1)//если переход по плюсу прямой
                  {
                    if((fr3[Snext][0]==1)&&(fr3[Snext][1]==0))//если стрелка в плюсе

                      if(napa==0) Snext--; //перейти на следующий объект
                      else Snext++;
                    else //если стрелка в минусе
                    {
                      FLAG_PO=1;//установить флаг поворота
                      trassa[ukaz_trass++]=Snext;
                      Snext=poisk_ras(fr1[Snext][2],Snext);//найти объект за поворотом
                      FLAG_PO=0;//снять флаг поворота
                    }
                  }
                  else//если прямой переход по минусу
                  {
                    if((fr3[Snext][0]==0)&&(fr3[Snext][1]==1))//если стрелка в минусе
                      if(napa==0) Snext--;//пройти на следующий объект
                      else Snext++;
                    else//если стрелка в плюсе
                    {
                      FLAG_PO=1;//установить флаг поворота
                      trassa[ukaz_trass++]=Snext;
                      Snext=poisk_ras(fr1[Snext][2],Snext);//найти объект за поворотом
                      FLAG_PO=0;//снять флаг поворота
                    }
                  }
                }
              }
              break;
preho:
			case 6: //pusya=ukaz_trass; //если попали на переход,запомнить текущий адрес КК
							if(uze(Snext,napa)==0)// если нет дублирования перехода
							{

								Spred=Snext;
								FLAG_PO=1;//установить флаг поворота
								Snext=poisk_ras(fr1[Snext][1],Snext);//найти объект за поворотом
								FLAG_PO=0;//снять флаг поворота
							}
							else //если переход уже зафиксирован
							{
								Spred=Snext;//выполнить переход на следующий объект
								if(napa==0) Snext--;
								else Snext++;
							}
							//ukaz_trass=pusya;//восстановить адрес КК
							//pusya=0;
              break;
      case 2: Spred=Snext;//если попали на сигнал
              if(fr1[Snext][2]==5) goto ss;//для смены направления - переход
              if((moni==0)&&  //если открываем поездной и
              (fr1[Snext][2]==0))// попался маневровый
              {
ss:             if(napa==0) Snext--;//перейти на следующий объект
                else Snext++;
                break;
              }
              else
              if((moni==1)&& //если открываем маневровый и 
              (fr1[Snext][2]==1)&&  //встретился поездной сигнал и 
              (fr1[Snext][6]!=2))//сигнал не совмещенный 
              {
                if(napa==0) Snext--;//идем дальше
                else Snext++;
                break;
              }
              if(fr1[point][1]==fr1[Snext][1])//если сигналы в одном напр.
              return;//выход
              else//если сигналы встречные 
              {
                if(napa==0) Snext--;//идем дальше
                else Snext++;
                ZA_SI=1;//устанавливаем признак прохода за сигнал
                break;
              }
      default:  return;//если что-то непредвиденное
    }
    if(trassa[ukaz_trass]!=0xFFFF)ukaz_trass++;
  } /* while */
}
//--------------------------------------------------------------
plus_minus()//процедура анализа и запоминания требуемого положения стрелки 
{
#ifdef NALAD  
  nom_func("225");
#endif        
  // если  по прямой
  if((fra[(trassa[ukaz_trass-1]&0xFFF)][0]==fra[(trassa[ukaz_trass+1]&0xFFF)][0])&&
  (fr1[trassa[ukaz_trass]][1]==1))
  {
    trassa[ukaz_trass]=trassa[ukaz_trass]&0x7fff;// если для стрелки проход по нити плюсом
    fr3[trassa[ukaz_trass]][10]=fr3[trassa[ukaz_trass]][10]&0x7fff;
  }
  else
  if((fra[trassa[ukaz_trass-1]][0]==fra[trassa[ukaz_trass+1]][0])&&
  (fr1[trassa[ukaz_trass]][1]==0))
  {
    trassa[ukaz_trass]=trassa[ukaz_trass]|0x8000;// если для стрелки проход по нити плюсом
    fr3[trassa[ukaz_trass]][10]=fr3[trassa[ukaz_trass]][10]|0x8000;
  }
  else
  if((fra[trassa[ukaz_trass-1]][0]!=fra[trassa[ukaz_trass+1]][0])&&
  (fr1[trassa[ukaz_trass]][1]==1))
  {
    trassa[ukaz_trass]=trassa[ukaz_trass]|0x8000;// если для стрелки проход по нити плюсом
    fr3[trassa[ukaz_trass]][10]=fr3[trassa[ukaz_trass]][10]|0x8000;
  }
  else
  if((fra[trassa[ukaz_trass-1]][0]!=fra[trassa[ukaz_trass+1]][0])&&
  (fr1[trassa[ukaz_trass]][1]==0))
  {
    trassa[ukaz_trass]=trassa[ukaz_trass]&0x7fff;// если для стрелки проход по нити плюсом
    fr3[trassa[ukaz_trass]][10]=fr3[trassa[ukaz_trass]][10]&0x7FFF;
  }
  fr3[trassa[ukaz_trass]][6]=0;
}
//--------------------------------------------------------------
//Процедура подтверждения выдачи команды при ненормальностях
podtver()
{
#ifdef NALAD  
  nom_func("228");
#endif        
  setfillstyle(1,14);bar(495,30,639,43);
  moveto(498,33);setcolor(RED);outtext("Выдавать команду?");
  setlinestyle(0,0,0);rectangle(494,31,638,42);
}
//---------------------------------------------------
int prov_avail()
{
  unsigned int i;
#ifdef NALAD  
  nom_func("242");
#endif          
  //nach_marsh - начало маршрута для простого маршрута или вариантная точка 
  //end_marsh - сигнал конца маршрута
  //nach0_marsh - 0 для простого маршрута или начало для вариантного 
  if(fra[nach_marsh][0]==fra[END][0])//если начало и конец в одной строке
  { if((fr1[nach_marsh][1]==1)&&(fra[nach_marsh][1]>fra[END][1]))return(1);
    if((fr1[nach_marsh][1]==0)&&(fra[nach_marsh][1]<fra[END][1]))return(1);
  }
  if(fra[nach0_marsh][0]==fra[END][0])//если начало и конец в одной строке
  { if((fr1[nach_marsh][1]==1)&&(fra[nach0_marsh][1]>fra[END][1]))return(1);
    if((fr1[nach_marsh][1]==0)&&(fra[nach0_marsh][1]<fra[END][1]))return(1);
  }
  i=fr1[end_marsh][11];
  if(nach0_marsh!=0)//если вариантный маршрут 
  { if((mane==1)||(fr1[nach0_marsh][6]==3))//если маневровый или 2 белых 
    { if(fr1[nach_marsh][1]==0)//если четный маршрут 
      { //если есть конец четного маневрового 
        if(((i&4)!=4)||((i&8)!=0x0))return(1);
        else return(0);
      }
      if(fr1[nach_marsh][1]==1)//если нечетный маршрут 
      { //если есть конец нечетного маневрового
        if(((i&1)!=1)||((i&2)!=0x0))return(1);
        else return(0);
      }
    }
    if((mane==0)&&(fr1[nach0_marsh][6]!=3))//если поездной
    { if(fr1[nach_marsh][1]==0)//если четный маршрут 
      { //если есть конец четного поездного 
        if(((i&64)!=64)||((i&128)!=0x0))return(1);
        else return(0);
      }
      if(fr1[nach_marsh][1]==1)//если нечетный маршрут 
      { //если есть конец нечетного поездного 
        if(((i&16)!=16)||((i&32)!=0x0))return(1);
        else return(0);
      }
    }
  }
  if(nach0_marsh==0)//если простой маршрут 
  { if((mane==1)||(fr1[nach_marsh][6]==3))//если маневровый сигнал начала или 2 белых 
    { if(fr1[nach_marsh][1]==0x0)//если четный маршрут 
      { //если есть конец четного маневрового 
        if(((i&4)!=4)||((i&8)!=0))return(1);
        else return(0);
      }
      if(fr1[nach_marsh][1]==1)//если нечетный маршрут 
      { //если есть конец нечетного маневрового 
        if(((i&1)!=1)||((i&2)!=0x0))return(1);
        else return(0);
      }
    }
    if((mane==0)&&(fr1[nach_marsh][6]!=3))//если поездной
    { if(fr1[nach_marsh][1]==0)//если четный маршрут 
      { //если есть конец четного поездного
        if(((i&64)!=64)||((i&128)!=0x0))return(1);
        else return(0);
      }
      if(fr1[nach_marsh][1]==1)//если нечетный маршрут 
      { //если есть конец нечетного поездного 
        if(((i&16)!=16)||((i&32)!=0x0))return(1);
        else return(0);
      }
    }
    if((mane==0)&&(manevro==1))//если поездной сигнал начала и маневровый маршрут 
    { if(fr1[nach_marsh][1]==0)//если четный маршрут 
      { //если есть конец четного маневрового 
        if(((i&4)!=4)||((i&8)!=0x0))return(1);
        else return(0);
      }
      if(fr1[nach_marsh][1]==1)//если нечетный маршрут 
      { //если есть конец нечетного маневрового 
        if(((i&1)!=1)||((i&2)!=0x0))return(1);
        else return(0);
      }
    }
  }
  return(1);
}
//---------------------------------------------------------
int prov_negabarit(int nom,int avt)
{//проверка состояния негабаритного участка
  int nnom=0;
#ifdef NALAD  
  nom_func("247");
#endif          
  nnom=fr1[nom][2];
  if(fr3[nnom][0]==1)
  {
    if(avt==0)w(130,nnom,"");// ЗАНЯТ НЕГАБАРИТНЫЙ УЧАСТОК
    return(1);
  }
  else return(0);
}
//---------------------------------------------------
int prov_negabarit_ohr_pl_mi(int nom,int avt)
{
  int nnom=0,
			nnom1=0,
			pn1=0,
			pn2=0,
			sparen=0,
			kod,
			put=0,
			stoika,
			k;
#ifdef NALAD
  nom_func("248");
#endif
  stoika = fr1[nach_marsh][13];//получить номер стойки
  nnom = fr1[nom][2]; //получить номер для СП
  nnom1=fr1[nom][3];//получить номер для стрелки
  pn1=fr1[nom][4]; //требуемое положение для плюсового контроля
  pn2=fr1[nom][5]; //требуемое положение для минусового контроля
ag:
  if(((fr3[nnom1][0]!=pn1)||(fr3[nnom1][1]!=pn2))// если стрелка стоит не так
  &&((mane==0)||(fr1[nom][1]==14)))//если в любых маршрутах
  { //если раздельное управление,то выдать текст "НЕ ПО МАРШРУТУ СТРЕЛКА"
    if(uprav==0){for(k=0;k<10;k++)BEDA[k]=0;w(126,nnom1,"");return(1);}
    //если маршрутное управление и стрелка без контроля,то
    //выдать текст "НЕ ИМЕЕТ КОНТРОЛЯ СТРЕЛКА"
    if((uprav==1)&&(fr3[nnom1][0]==fr3[nnom1][1])){w(127,nnom1,"");return(1);}
   //если отключена от управления,то выдать текст "ОТКЛ. ОТ УПРАВЛ. СТРЕЛКА"
    if(fr4[nnom1][0]==1){if(avt==0)w(67,nnom1,"");return(1);}
    if(fr4[nnom1][1]==1){if(avt==0)w(99,nnom1," ВКЛЮЧЕНА НА МАКЕТ"); return(1);}
    // ЗАНЯТ УЧАСТОК
    if(fr3[nnom][0]==1){if(avt==0)w(94,nnom,"");return(1);}
    // ЗАМКНУТ В МАРШРУТЕ УЧАСТОК
    if(fr3[nnom][1]==1){if(avt==0)w(96,nnom,"");return(1);}
    // ВКЛЮЧЕНО ИСКУССТВЕННОЕ РАЗМЫКАНИЕ
    if(fr3[nnom][2]==1){if(avt==0)w(98,nnom,"");return(1);}
    // НЕИСПРАВЕН УЧАСТО
    if(fr3[nnom][5]==1)
		{if(avt==0)w(104,nnom,"");
		return(-1);}
    if(tst_chet(nnom)==0)//если стрелка четная
    {
      if(fr3[RZ_CHET][RZ_CHET_BIT]==1)//если включено замыкание ручное четное
      {
        w(166,nnom1,"");
				return(1);
      }
    }
    else //если стрелка нечетная стойке
    {
      if(fr3[RZ_NECHET][RZ_NECHET_BIT]==1)//если замыкание ручное нечетное
      {
        w(166,nnom1,"");
				return(1);
      }
    }
    if(sparen==0)
    if(fr1[nnom1][13]!=fr1[nach_marsh][13])//если стрелка в другой стойке
    { if(pn1==1)oper='I';//для перевода в плюс с реверсом
      if(pn1==0)oper='J';//аналогично для перевода в минус
      //если ранее не был запомнен маршрут
      if((marshrut[stoika-1][0]==0)||(marshrut[stoika-1][0]==nach_marsh))
      { marshrut[stoika-1][0]=nach_marsh;
        marshrut[stoika-1][1]=end_marsh;
        marshrut[stoika-1][2]=half_marsh;
        return(22);
      }
      //если не закончена работа с ранее заданным маршрутом
      //"ЕЩЕ НЕ ВЫПОЛНЕНА ПРЕДЫДУЩАЯ КОМАНДА"
      else {if(avt==0)w(51,999,"");return(1);}
    }
    if(sparen==0&&fr1[nnom1][12]!=9999)
    { sparen=1;
      TEST=2;
      nnom1=poisk_ras(fr1[nnom1][2],nnom1);
      nnom=findspu1(nnom1,fr1[nnom1][7]);
      goto ag;
    }
  }
  else//если стрелка по маршруту
  {
    if((mane==0)&&(fr1[nom][1]==15)&&(fr3[nnom1][5]==1))
		{
			w(72,nnom1,""); //-------------------------------- seg014:2ECA
			return(-1);
		}
		if((fr1[nom][1]==15)&&(fr1[nach_marsh][3]==7)&&(sparen==0))
    { // ЗАНЯТ УЧАСТОК
      if(fr3[nnom][0]==1)
			{
				if(avt==0)
				w(94,nnom,""); //-------------------- seg014:2F3E 
				return(1);
			}
      // ЗАМКНУТ В МАРШРУТЕ УЧАСТОК
      if(fr3[nnom][1]==1)  //------------ seg014:2F57  
			{
				if(avt==0)
				w(96,nnom,"");  //--------------- seg014:2F6F 
				return(1);
			}
			// ВКЛЮЧЕНО ИСКУССТВЕННОЕ РАЗМЫКАНИЕ
			if(fr3[nnom][2]==1) //-------------- seg014:2F88 
			{
				if(avt==0)
				w(98,nnom,"");  //------------------- seg014:2FA0 
				return(1);
			}
			
			// НЕИСПРАВЕН УЧАСТОК
			if(fr3[nnom][5]==1) //---------------- seg014:2FB9
			{
				if(avt==0)
				w(104,nnom,"");
				return(-1);
			}
    }
		//------------- seg014:2FDF loc_436FF:
    if((sparen==0)&&(fr1[nnom1][12]!=9999))
    { sparen=1;
      TEST=2;
      nnom1=poisk_ras(fr1[nnom1][2],nnom1);
      nnom=findspu1(nnom1,fr1[nnom1][7]);
      goto ag;
    }
  }
  //если поездной маршрут и д.з. только для поездных
  if(mane==0)
  {
		if((fr1[nach_marsh][3]==7)||(fr1[nach0_marsh][3]==7))//если прием
    { if((uprav==1)&&(fr1[nnom1][13]!=fr1[end_marsh][13]))//и стрелка в другой стойке
      { if(sparen==0)
        if((fr3[nnom1][0]!=pn1)&&(fr3[nnom1][1]!=pn2))
        { point=nnom1;
          if(pn1==1)oper='I';
          if(pn1==0)oper='J';
          if(marshrut[stoika][0]==0)
          { marshrut[stoika-1][0]=nach_marsh;
            marshrut[stoika-1][1]=end_marsh;
            marshrut[stoika-1][2]=half_marsh;
          }
          return(22);
        }
      }
    }
  }
  return(0);
}
//-------------------------------------------------------------------
int prov_negabarit_pl_mi(int nom,int avt)
{
  int nnom=0,nnom1=0,pn1=0,pn2=0;
#ifdef NALAD  
  nom_func("249");
#endif          
  nnom=fr1[nom][2];//СП для охранной стрелки
  nnom1=fr1[nom][3];//охранная стрелка
  pn1=fr1[nom][4];//требуемое состояние плюсового контроля
  pn2=fr1[nom][5];//требуемое состояние минусового контроля

  if((fr3[nnom1][0]!=pn1&&fr3[nnom1][1]!=pn2)||  //если положение стрелки не то
  (fr3[nnom1][0]==fr3[nnom1][1]))//или стрелка без контроля
    if(fr3[nnom][0]==1)//если СП занято
    {
      if(avt==0)w(130,nnom,"");//ЗАНЯТ НЕГАБАРИТНЫЙ УЧАСТОК
      return(1);
    }
    else
      if(fr3[nnom][1]==1) //если СП замкнуто
      {
        if(avt==0)w(96,nnom,"");//ЗАМКНУТ В МАРШРУТЕ УЧАСТОК
        return(1);
      }
      else
        if(fr3[nnom][2]==1)//если СП в разделке
        {
          if(avt==0)w(98,nnom,""); //ВКЛЮЧЕНО ИСКУССТВЕННОЕ РАЗМЫКАНИЕ
          return(1);
        }
        else
          if(fr3[nnom][5]==1)//если по СП непарафазность
          {
            if(avt==0)w(104,nnom,"");//НЕИСПРАВЕН УЧАСТОК
            return(1);
          }
          else return(0);
}
//----------------------------------------------------------
int prov_negabarit_pl_mi2(int nom,int av)
{
  int nnom=0,nnom1=0,pn1=0,pn2=0;
#ifdef NALAD  
  nom_func("250");
#endif          
  nnom=fr1[nom][2];//получить номер СП для проверки
  nnom1=fr1[nom][3];//получить номер стрелки для проверки
  pn1=fr1[nom][4];//требуемое положение по плюсу
  pn2=fr1[nom][5];//требуемое положение по минусу
  if((fr3[nnom1][0]!=pn1&&//если плюсовой контроль не такой и
  fr3[nnom1][1]!=pn2)||  //минусовой контроль не такой или
  (fr3[nnom1][0]==fr3[nnom1][1]))//стрелка без контроля
  //если СП занят
  if(fr3[nnom][0]==1){if(av==0)w(130,nnom,"");return(1);}
  return(0);
}
//-----------------------------------------------------------
#ifdef OGRAD
int prov_ograd(int nom,int avto)//проверяет наличие ограждения пути
{
  int nnom=0,bt_=0,put=0;
  nnom=fr1[nom][2];//датчик запроса ограждения
  bt_=fr1[nom][3];
  put=fr1[nnom][8];//датчик ограждения
  if(fr3[nnom][bt_]==1)
  {
    if(avto==0)w(141,put,"");//ВКЛЮЧЕНО ОГРАЖДЕНИЕ, ПУТЬ...
    return(1);
  }
  else return(0);
}
#endif
//------------------------------------------------
sbros_time_tip(int tip)
{
  int i,ob1;
#ifdef NALAD  
  nom_func("294");
#endif          
  for(i=0;i<25;i++)
  {
    if(TIMER_N[i][1]==tip)
    {
      ob1=TIMER_N[i][0]=0;
      if(pooo[ob1]!=2)pooo[ob1]=0L;
      TIMER_N[i][0]=0;
      TIMER_N[i][1]=0;
      TIMER_N[i][2]=0;
    }
  }
}
//--------------------------------------------------
int sogl_otkr(int NUMB)
{
  int okop=0,BBA=0;
#ifdef NALAD  
  nom_func("314");
#endif          
  switch(fr1[NUMB][0])
  {
    case 1: return(tst_str1(NUMB));
    case 2: if(fr1[NUMB][2]==5) return(0);
            return(tst_sig(NUMB,0));
    case 3: return(tst_spu(NUMB,0));
    case 4: okop=tst_uch(NUMB,0);return(okop);
    case 5: BBA=tst_put(NUMB,0);return(BBA);
    case 6: return(0);
    case 7: return(tst_dz(NUMB,0));
    default:return(1);
  }
}
//-------------------------------------------------
int strelka(int aks,int nd)
{//процедура трассировки маршрута через стрелку 
  int Zahod,ist,PREOB;
#ifdef NALAD  
  nom_func("321");
#endif          
  Zahod=0;
  if(fr3[aks][6]==0)Zahod=1;
  if(fr3[aks][6]==1)Zahod=2;
  PREOB=fr1[aks][10]&96;
  if(fr1[aks][7]==fr1[nach_marsh][1])//если вход на стрелку по напр.маршрута
  { if(Zahod==1)//если 1-ый заход на стрелку 
    { fr3[aks][6]=1;
      if((PREOB&32)==32&&(fra[aks][0]!=fra[END][0]))
      //если стрелка имеет преобладание по минусу
      {
metka_a:
        FLAG_PO=1;//установить флаг отклонения маршрута от прямой
        aks=poisk_ras(fr1[aks][2],aks);//найти объект за поворотом 
        FLAG_PO=0;//сбросить флаг поворота
        return(aks);//вернуть номер объекта 
      }
      else
      {
metka_b:
        if(nd==0) aks--; //перейти на следующий 
        else aks++;
        return(aks);
      }
    }
    if(Zahod==2)//если второй заход 
    { fr3[aks][6]=2;
      //если стрелка имеет преобладание по минусу
      if((PREOB&32)==32)goto metka_b; 
      else
        //если стрелка имеет преобладание по плюсу 
        if((PREOB&64)==64)goto metka_a;
        else goto metka_a;// стрелка не имеет преобладания
    }
    else return(-1);//при попытке третьего захода - стрелка непроходима 
  }
  else goto metka_b;//если вход на стрелку не совпадает с напр.движения
}
//-----------------------------------------
int t_dz(int no) //проверка ДЗ при включении автодействия
{ int nnnn1,bit1,znach1,nnnn2,bit2,znach2;
#ifdef NALAD  
  nom_func("326");
#endif        
  if(fr1[no][1]==7)//если проверка направления для автоблокировки
  { nnnn1=fr1[no][4];
    if(fr3[nnnn1][1]==0)//если нет направления на отправление 
    { //НЕ УСТАНОВЛЕНО НАПРАВЛЕНИЕ ДВИЖЕНИЯ НА ОТПРАВЛЕНИЕ 
      w(230,999);
      return(1);
    }
    else return(0);
  }
#ifdef POLUAVTOMAT
  if(fr1[no][1]==5)//если проверка для полуавтоматики
  { nnnn1=fr1[no][3];//первый объект направления 
    bit1=fr1[no][4];//бит первого объекта 
    znach1=fr1[no][5];//значение бита для отправления 
    nnnn2=fr1[no][6];//второй объект
    bit2=fr1[no][7];//бит второго объекта 
    znach2=fr1[no][8];//значение бита для отправления 
    if((fr3[nnnn1][bit1]!=znach1)||(fr3[nnnn2][bit2]!=znach2))
    { w(230,999);//НЕ УСТАНОВЛЕНО НАПРАВЛЕНИЕ ДВИЖЕНИЯ НА ОТПРАВЛЕНИЕ 
      return(1);
    }
    else return(0);
  }
  if(fr1[no][1]==6)//для полуавтоматики
  { nnnn1=fr1[no][3];//номер объекта перегона по отправлению 
    bit1=fr1[no][4];// номер бита
    znach1=fr1[no][5];//значение бита для свободности 
    if(fr3[nnnn1][bit1]!=znach1)
    { w(77,999,""); //ЗАНЯТ ПЕРЕГОН 
      return(1);
    }
    else return(0);
  }
#endif
  return(0);
}
//-------------------------------------------------------
int t_put(int no)//проверка пути при установке автодействия
{
#ifdef NALAD  
  nom_func("328");
#endif        
  if(fr4[no][2]==1)//если закрыт для движения
  { w(115,no,"");//"ДВИЖЕНИЕ ЗАПРЕЩЕНО ПУТЬ..."
    return(1);
  }
  if(fr3[no][5]==1)//если непарафазность
  { w(116,no,"");//"НЕИСПРАВЕН ПУТЬ..."
    return(1);
  }
  if(fr3[no][0]==1)//если занят 
  { w(106,no,"");//"ЗАНЯТ ПУТЬ..."
    return(1);
  }
  if((fr1[no][1]==1)||(fr1[no][2]==1))return(0);//если нет границ станции 
  if((fr3[no][1]==1)&&( markery[modi][7]-777==0)) return(0);//если НИ для нечетного 
  if((fr3[no][2]==1)&&( markery[modi][7]-777==1))return(0);//если ЧИ для четного 
  else //иначе вывести на экран текст 
  { w(143,no,"");//"НЕ ГОТОВ МАРШРУТ - ПУТЬ..."
    return(1);
  }
}
//---------------------------------------------------------
int t_sig(int no) //проверка сигнала при включении автодействия
{
  int uksp,bt_uks;
#ifdef NALAD
  nom_func("329");
#endif
  uksp=fr2[no][9]&0xfff;
  if(uksp!=0)
  {
    bt_uks=(fr2[no][9]&0xf000)>>12;
    if(fr3[uksp][bt_uks]==1){w(169,999," УКСПС");return(1);}
  }
  uksp=fr2[no][10]&0xfff;
  if(uksp!=0)
  {
    bt_uks=(fr2[no][10]&0xf000)>>12;
    if(fr3[uksp][bt_uks]==1){w(169,999," УКСПС");return(1);}
  }
  if(fr3[no][5]==1)//если непарафазность
  { w(88,no,"");return(1);} //"НЕИСПРАВЕН СИГНАЛ..."
  if(fr1[no][2]==0)//если маневровый
  { if(fr3[no][0]==1)//если сигнал открыт
    {w(78,no,"");return(1);} //"ОТКРЫТ СИГНАЛ..."
    else return(0);
  }
  else//если не маневровый
  { if(markery[modi][7]-777==0)//если включается нечетное автодействие
    { if((fr1[no][1]==0)&&( fr3[no][1]==1))//если сигнал четный и открыт поездной
      { w(78,no,""); return(1);} //"ОТКРЫТ СИГНАЛ..."
      else return(0);
    }
    if(markery[modi][7]-777==1)//если включается четное автодействие
    { if((fr1[no][1]==1)&&( fr3[no][1]==1))//если сигнал нечетный и открыт поездной
      { w(78,no,"");return(1);} //"ОТКРЫТ СИГНАЛ..."
      else return(0);
    }
  }
}
//-------------------------------------------------------------
int t_spu(int no)//процедура проверки СП при установке автодействия
{ 
#ifdef NALAD  
  nom_func("330");
#endif          
  if(fr3[no][5]==1)//если непарафазность
  { w(104,no,""); //вывести на экран текст "НЕИСПРАВЕН УЧАСТОК..."
    return(1);
  }
  //если только замкнут 
  if((fr3[no][0]==0)&&(fr3[no][1]==1)&&(fr3[no][2]==0))return(0);
  if(fr3[no][0]==1)//если занят 
  { w(94,no,"");//"ЗАНЯТ УЧАСТОК..."
    return(1);
  }
  if(fr3[no][2]==1)//если в разделке
  { w(98,no,"");//"ВКЛЮЧЕНО ИСКУССТВЕННОЕ РАЗМЫКАНИЕ..."
    return(1);
  }
  if(fr3[no][1]==0)//если не замкнут 
  { w(142,no,"");//"НЕ УСТАНОВЛЕНО ЗАМЫКАНИЕ ПО УЧАСТКУ..."
    return(1);
  }
}
//-----------------------------------------------------------
int t_uch(int no)//проверка участка пути при установке автодействия
{ 
#ifdef NALAD  
  nom_func("332");
#endif          
  if(fr4[no][2]==1)//если участок закрыт для движения
  { w(115,no,""); //"ДВИЖЕНИЕ ЗАПРЕЩЕНО ПУТЬ..."
    return(1);
  }
  if(fr3[no][5]==1)//если непарафазность
  { w(104,no,"");//"НЕИСПРАВЕН УЧАСТОК..."
    return(1);
  }
  //если только замкнут   
  if((fr3[no][0]==0)&&( fr3[no][1]==1)&&( fr3[no][2]==0))return(0);
  if(fr3[no][0]==1)//если занят 
  { w(94,no,"");//"ЗАНЯТ УЧАСТОК..."
    return(1);
  }
  if(fr3[no][2]==1)//если в разделке
  { w(98,no,"");//"ВКЛЮЧЕНО ИСКУССТВЕННОЕ РАЗМЫКАНИЕ..."
    return(1);
  }
  if(fr3[no][1]==0)//если не замкнут 
  { w(142,no,"");//"НЕ УСТАНОВЛЕНО ЗАМЫКАНИЕ ПО УЧАСТКУ..."
    return(1);
  }
}
//----------------------------------------------------------
int test_elem(int element,int fl)
{ //переключатель программ проверок элементов маршрута
//  fl1=0 для обычных проверок
//  fl1=1 для проверок перед включением автодействия
  int otvet,pologen,tst;
#ifdef NALAD  
  nom_func("339");
#endif           
	otvet=1;

	switch(fr1[element][0])
	{ //проверка стрелок (при норме возвращает 0)
		case 1: if((trassa[ukaz_trass]&0x8000)==0)pologen=1;
						else pologen=-1;
						if((fl==0)&&(tst_str(element,pologen)==0)){otvet=0;goto konec;}
						if((fl!=0)&&(tst_str_av(element,1)==0)){otvet=0;goto konec;}
						break;
    //проверка сигналов
    case 2: if(fr1[element][2]==5){otvet=0;goto konec;}//смену направлен.не проверять
            //проверка открытости сигнала и его исправности
            otvet=tst_sig(element,fl);
            goto konec;
    // проверка СП
    case 3: otvet=tst_spu(element,fl);
            goto konec;
    // проверка УП
    case 4: otvet=tst_uch(element,fl);
            goto konec;
    //проверка пути
    case 5: if(fr1[element][1]==1&&fr1[element][2]==1)return(0);
            otvet=tst_put(element,fl);
            goto konec;
    case 6: return(0);
    case 7: otvet=tst_dz(element,fl);
            goto konec;
    default:otvet=1;goto konec;
  }
konec:
    if(otvet==1)
      tst=otvet;
      return(otvet);
}
//----------------------------------------------------
int tst_dz(int D,int avto)
{ int nnnn=0,nnnn1,bit1,znach1,nnnn2,bit2,znach2,a,b,c,ron_roch,b_ron_roch;
#ifdef NALAD  
  nom_func("362");
#endif
  /* если это ДЗ - ограждение пути */
#ifdef OGRAD
  if(fr1[D][1]==77)return(prov_ograd(D,avto));
#endif
  if(fr1[D][1]==111)
  { if(prov_negabarit(D,avto)==0&&prov_negabarit_pl_mi(D,avto)==0)return(0);
    else return(1);
  }
  if(fr1[D][1]==1)return(prov_negabarit(D,avto));
  if(fr1[D][1]==101)return(prov_negabarit_pl_mi(D,avto));
	if((fr1[D][1]==14)||(fr1[D][1]==15))return(prov_negabarit_ohr_pl_mi(D,avto));
  if(fr1[D][1]==112)return(prov_negabarit_pl_mi2(D,avto));
#ifdef POLUAVTOMAT
  if(fr1[D][1]==5)
  { nnnn1=fr1[D][3]; bit1=fr1[D][4]; znach1=fr1[D][5];
    nnnn2=fr1[D][6]; bit2=fr1[D][7]; znach2=fr1[D][8];
    if((mane==0)&&(manevro==0)&&(manevr==0)&&
    ((fr3[nnnn1][bit1]!=znach1)||(fr3[nnnn2][bit2]!=znach2)))
    { //НЕ УСТАНОВЛЕНО НАПРАВЛЕНИЕ ДВИЖЕНИЯ НА ОТПРАВЛЕНИЕ
      if(avto==0)w(230,999,"");
      return(1);
    }
    return(0);
  }
  if(fr1[D][1]==6)
  { nnnn1=fr1[D][3]; bit1=fr1[D][4]; znach1=fr1[D][5];
    nnnn2=fr1[D][6]; bit2=fr1[D][7]; znach2=fr1[D][8];
    if((mane==0)&&(manevro==0)&&(manevr==0)&&
    ((fr3[nnnn1][bit1]!=znach1)||(fr3[nnnn2][bit2]!=znach2)))
    { if(avto==0)w(77,999,""); // ЗАНЯТ ПЕРЕГОН
      return(1);
    }
    return(0);
  }
#endif
  if(fr1[D][1]==7)//если проверка направления для 2-х путной автоблокировки
  {
    if((mane==1)||(manevro==1)||(manevr==1))return(0);
    nnnn1=fr1[D][4];//получить объект для смены направления перегона
    nnnn2=fr1[D][5];//получить объект для реле В
    a=fr3[nnnn2][1];//состояние реле В
    b=fr3[nnnn2][7];//состояние направления перегона с учетом переключения
    c=fr3[nnnn1][1];//установленное направление
    if((b!=0xffff)&&((b==0xf0f0)||((a==1)&&(c==1))))
    {
      ron_roch=fr1[D][6];
      if(ron_roch!=9999)//если есть РОН/РОЧ
      {
        ron_roch=fr1[D][6]&0xfff;
        b_ron_roch=(fr1[D][6]&0xf000)>>12;
        if(fr3[ron_roch][b_ron_roch]==0)//если нет РОН/РОЧ
        {
          if((avto!=1)&&(avto!=2))//если нет автодействия
          {
            get_str(ron_roch,b_ron_roch);
            w(264,999,chudo);
            return(1);
          }
          else return(7);
        }
      }
      return(0);
    }
    else
    {
    //НЕ УСТАНОВЛЕНО НАПРАВЛЕНИЕ ДВИЖЕНИЯ НА ОТПРАВЛЕНИЕ
      if(avto==0)w(230,999,"");
      return(1);
    }

  }
  if(fr1[D][1]==6)//если проверка направления для однопутной автоблокировки
  {
    if((mane==1)||(manevro==1)||(manevr==1))return(0);
    nnnn1=fr1[D][2]&0xfff;//объект для состояния перегона
    a=(fr1[D][2]&0xf000)>>12;//бит для состояния перегона
    nnnn2=fr1[D][3]&0xfff;//объект для направления перегона
    b=(fr1[D][3]&0xf000)>>12;//бит для направления перегона
    if((fr3[nnnn2][b]==0)&&(fr3[nnnn1][a]==1))//если прием и перегон занят
    {
      w(5,999," ПРИБЫВАЕТ ПОЕЗД");
      return(1);
    }
    else return(0);
  }
}
//----------------------------------------------------------------
//проверка наличия сигнала конца маршрута вдоль установленных стрелок
int tst_nal_sig()
{
#ifdef NALAD
  nom_func("365");
#endif
  ukaz_trass=1;//поставить в начало
  // выполнить пока не дойдем до конца
  while(trassa[ukaz_trass]!=0xFFFF)
  { if(fr1[trassa[ukaz_trass]][0]==2)// если в цепочке найден сигнал
    { if(fr1[trassa[ukaz_trass]][2]==5)goto fi; // если смена направления
      if(trassa[ukaz_trass]==markery[modi][6])goto fi; //если на этом сигнале маркер
      if(mane==1)manevro=1;
      switch(manevro)//переключатель по типу маршрута
      {//поездн.маршрут
        case 0: if(fr1[point][1]==0)//если четный маршрут
        				{ //если у сигнала нет конца четного поездного - прервать
                	if((fr1[trassa[ukaz_trass]][11]&64)!=64)break;
								}
                else//если нечетный маршрут
                  //есдт у сигнала нет конца нечетного поездного - прервать
                	if((fr1[trassa[ukaz_trass]][11]&16)!=16)break;                {

								}
                //если поездной сигнал или входной, то выход
								if((fr1[trassa[ukaz_trass]][2]==1)||
                (fr1[trassa[ukaz_trass]][3]==7))return(0);
								//если маршрут с 2-умя белыми-и есть конец для двух белых
                if((fr1[point][6]==3)&&(fr1[trassa[ukaz_trass]][4]==3))return(0);
                break;
        //маневр.маршрут
        case 1:
                if(fr1[point][1]==1)//если нечетный маршрут
        				{
                  //если у сигнала нет конца нечетного маневрового-прервать
                	if((fr1[trassa[ukaz_trass]][11]&1)!=1)break;
								}
                else//если четный маршрут
                  //если у сигнала нет конца четного маневрового-прервать
                	if((fr1[trassa[ukaz_trass]][11]&4)!=4)break;                {
								}
                //если сигнал манавровый или
								if((fr1[trassa[ukaz_trass]][2]==0)||
                //или сигнал совмещенный
								(fr1[trassa[ukaz_trass]][6]==2)||
                //или сигнал выходной
								(fr1[trassa[ukaz_trass]][3]==7))return(0);
                break;
        default: break;
      }
    }
fi:
    ukaz_trass++;//если не сигнал,то идти дальше
  }
  //если дошли до конца, а сигнала не было
  if((manevro==0)&&(mane==0))w(82,999,"");//ДЛЯ ПОЕЗДНОГО МАРШРУТА СТРЕЛКИ НЕ УСТАНОВЛЕНЫ
  else w(83,999,""); // МАРШРУТ НЕ СУЩЕСТВУЕТ
  return(1);
}
//----------------------------------

int tst_put(int P,int avto)
{ int OPP=0;
#ifdef NALAD  
  nom_func("367");
#endif  
  if(uprav==0)
  { OPP=point;
    if((fr1[P][1]==1)&&(fr1[P][2]==1)&&(mane==0)&&(manevro==0))
    {
//    if(avto=0)
    w(83,999,"!"); return(1);}//МАРШРУТ НЕ СУЩЕСТВУЕТ
  }
  else OPP=nach_marsh;
  if(avto!=0)OPP=nach_avto;
  if(fr4[P][2]==1)
  {
    if(avto==0)w(115,P,""); //ДВИЖЕНИЕ ЗАПРЕЩЕНО ПУТЬ
    if(uprav==1)return(1);
    else return(2);
  }
  if(fr3[P][5]==1){if(avto==0)w(116,P,"");return(1);}//НЕИСПРАВЕН ПУТЬ
  if(zanyato(P,avto)==1) return(1);
  if(zamknuto(P,OPP,avto)==1) return(1);
  return(0);
}
//-------------------------------------------------------------
int tst_sig(int S,int av)
{//проверка сигнала в трассе заданного маршрута
 //S - сигнал
 //av - признак автодействия (0-нет,1-нечетное,2-четное)
  int gul;
#ifdef NALAD
  nom_func("368");
#endif
  //если управление маршрутное - взять начало
  if(uprav==1)gul=nach_marsh;
  //для раздельного взять то, что хотим открыть
  else gul=point;

  if(av!=0)gul=nach_avto; //для автодействия взять свое начало

  //если непарафазность-НЕИСПРАВЕН СИГНАЛ
  if(fr3[S][5]==1){if(av==0)w(88,S,"");return(1);}
  //если все закрыто
  if((fr3[S][0]==0)&&(fr3[S][1]==0)&&(fr3[S][2]==0)&&(fr3[S][3]==0))return(0);
  if(fr1[S][1]==fr1[gul][1])//если сигнал попутный
  {
    if(S!=end_marsh)//если не конец маршрута
    {
      if(av==0)w(78,S,"");//если сигнал не конец - ОТКРЫТ СИГНАЛ
      else return(0);
      return(1);
    }
  }
  else//если враждебный сигнал
  {
    if(av==0)w(128,S,"");//ОТКРЫТ ВРАЖДЕБНЫЙ СИГНАЛ
    return(1);
  }
  return(0);
}
//--------------------------------------------------------
int tst_sigogo(int sip)
{ //процедура продолжения маршрута за встречный сигнал
  int mo=sip;
#ifdef NALAD
  nom_func("369");
#endif    
  //если сигнал попутный - разрешить
  if(fr1[sip][1]==fr1[nach_marsh][1])return(0);
  while((fr1[mo][0]==1)||//пока стрелка или
  (fr1[mo][0]==2)||  //сигнал или
  (fr1[mo][0]==6)||  //переход или
  (fr1[mo][0]==7))//ДЗ
  {
    if((mo<0)||(mo>kol_OSN))return(1);//если вышли за пределы базы - нет маршрута
    if(fr1[nach_marsh][1]==1)mo++;//продвинуться на следующий элемент маршрута
    else mo--;
    trassa[ukaz_trass++]=mo;
  }
  END=mo;//если вышли на СП,УП или путь - назначить этот элемент концом
  return(0);//вернуть разрешение
}
//-------------------------------------------------
int tst_str_av(int S,int polog)
{
  int U;
#ifdef NALAD  
  nom_func("373");
#endif     
  if(fr3[S][5]==1){w(72,S,""); return(1);} // неисправна стрелка
  if(fr3[S][0]==fr3[S][1]){w(127,S,"");return(1);}//НЕ ИМЕЕТ КОНТРОЛЯ СТРЕЛКА
  if(fr4[S][2]==1){w(71,S,"");return(1);}//ЗАПРЕЩЕНО ДВИЖЕНИЕ ПО СТРЕЛКЕ
  if(fr4[S][0]!=0)
  {
    if(fr3[S][0]==0&&fr3[S][1]==1&&polog==-1)return(0);
    if(fr3[S][0]==1&&fr3[S][1]==0&&polog==1)return(0);
    w(67,S,"");//ОТКЛ. ОТ УПРАВЛ. СТРЕЛКА
    return(1);
  }
  if(fr4[S][1]==1){w(99,S," ВКЛЮЧЕНА НА МАКЕТ");return(1);}
  if(fr3[S][0]==0&&fr3[S][1]==1&&polog==-1)return(0);
  if(fr3[S][0]==1&&fr3[S][1]==0&&polog==1)return(0);
  w(126,S,"");//НЕ ПО МАРШРУТУ СТРЕЛКА
  return(1);
}
//---------------------------------------------------
int tst_str1(int S)
{
#ifdef NALAD
  nom_func("372");
#endif
   if(fr3[S][5]==1)
	 {
	 	w(72,S,"");
    vibeg=0;
		return(-1);
	 } // неисправна стрелка

  if((fr4[S][1]==1)&&(maka==0)){w(99,S," ВКЛЮЧЕНА НА МАКЕТ"); return(5);}

  if(fr3[S][0]==fr3[S][1]){w(127,S,"");return(1);}//НЕ ИМЕЕТ КОНТРОЛЯ СТРЕЛКА

  if(fr4[S][2]==1){w(71,S,"");return(2);}//ЗАПРЕЩЕНО ДВИЖЕНИЕ ПО СТРЕЛКЕ

  if(fr1[point][1]==fr1[S][7])return(0);//если вход на стрелку совпал с напр.

  if((fr1[trassa[ukaz_trass-1]][0]==1)||//если перед стрелкой стрелка или...
  (fr1[trassa[ukaz_trass-1]][0]==6)||   //если перед стрелкой переход или ...
  (fr1[trassa[ukaz_trass-1]][0]==7))// если перед стрелкой ДЗ
  { //если по + прямо и стрелка в плюсе или ...
    if(((fr1[S][1]==1)&&(fr3[S][0]==1)&&(fr3[S][1]==0))||//или
    //если прямо по - и стрелка в минусе
    ((fr1[S][1]==0)&&(fr3[S][0]==0)&&(fr3[S][1]==1)))
    { // если при заходе на стрелку другая нить
			if(fra[trassa[ukaz_trass-1]][0]!=fra[S][0])
      { w(126,S,"");//НЕ ПО МАРШРУТУ СТРЕЛКА
        return(1);
      } else return(0);
    }
    else
    { // если по плюсу прямо и стрелка в минусе
			if(((fr1[S][1]==1)&&(fr3[S][0]==0)&&(fr3[S][1]==1))|| //или
      //если по минусу прямо, а стрелка в плюсе
      ((fr1[S][1]==0)&&(fr3[S][0]==1)&&(fr3[S][1]==0)))
      {
        // если одинаковые нити
				if(fra[trassa[ukaz_trass-1]][0]==fra[S][0])
        { w(126,S,"");//НЕ ПО МАРШРУТУ СТРЕЛКА
          return(1);
        } else return(0);
      }
    }
  }
  else//если переход по плюсу прямой и стрекла в минусе
  if(((fr1[S][1]==1)&&(fr3[S][0]==0)&&(fr3[S][1]==1))||
  ((fr1[S][1]==0)&&(fr3[S][0]==1)&&(fr3[S][1]==0)))
  { w(126,S,"");//НЕ ПО МАРШРУТУ СТРЕЛКА 
    return(1);
  }
  else return(0);
}
//------------------------------------------------------
int tst_strelok(int S)
//проверка возможности перевода стрелки
{ int U,UU;
#ifdef NALAD  
  nom_func("374");
#endif
  if(((tst_chet(S)==0)&&(fr3[RZ_CHET][RZ_CHET_BIT]==1))||  //если стрелка замкнута
  ((tst_chet(S)==1)&&(fr3[RZ_NECHET][RZ_NECHET_BIT]==1)))//ручным замыканием
  //ВКЛЮЧЕНО РУЧНОЕ ЗАМЫКАНИЕ СТРЕЛОК
  {w(166,S,"");return(1);}
  if(((fr1[S][13]==CHET)&&(fr3[AVAch][AV_bch]==1))||//если нажата вспом.перевод четный
  ((fr1[S][13]==NECHET)&&(fr3[AVAn][AV_bn]==1)))//если нажата вспом.перевод нечетный
  //Нажата кнопка вспомогательного перевода
  {w(111,S,"");return(1);}
  //если стрелка отключена от управления-"ОТКЛ. ОТ УПРАВЛ. СТРЕЛКА"
  if(((fr4[S][0]&7)!=0)&&(DU==0)){w(67,S,"");return(1);}
  if(((fr4[S][0]&0xf8)!=0)&&(osya==0))
  {
    w(240,999,"");
    if(uprav==0)return(2);
    else return(1);
  }
  if((hod==1)&&(uprav==0))goto sparka;
  U=findspu1(S,fr1[S][7]);//найти СП
  if(U==-1)
	{
		hod=1;
		if(uprav==1)goto spr2;
		else goto sparka;
	}
	if(uprav==0)//если управление раздельное
	{ UU=tst_spu(U,0);//проверить СП
		if(UU==10) return(10);
		if(UU==1)
			if(osya==0){osya=2;return(2);}
			else {osya++;return(osya);}
		if(fr1[S][12]!=9999)//если стрелка спаренная
		{ osya=0;
			hod=1;
sparka:
			TEST=2;
			U=poisk_ras(fr1[S][2],S);//найти парную
			if((fr1[U][11]&128)!=128)
			{
				U=findspu1(U,fr1[U][7]);//найти СП для парной стрелкой
				UU=tst_spu(U,0);//проверить состояние СП
				if(UU==10) return(10);
				if(UU==1)
				if(osya==0){osya=2;return(2);}
				else {osya++; return(osya);}
			}
			else return(0);
		}
	}
	else//если управление маршрутное
	{ if(tst_spu(U,0)==1) return(1);//проверить СП
		if(fr1[S][12]!=9999)//если стрелка спаренная
		{
spr2:	TEST=2;
			U=poisk_ras(fr1[S][2],S);
			if((fr1[U][11]&128)==128)return(0);
			U=findspu1(U,fr1[U][7]);
			if(tst_spu(U,0)==1) return(1);
			return(0);
		}
	}
	return(0);
}
//-------------------------------------------------------------
int tst_uch(int P,int avto)
{
	int Test;
#ifdef NALAD
	nom_func("375");
#endif
	//НЕИСПРАВЕН УЧАСТО  //ДВИЖЕНИЕ ЗАПРЕЩЕНО ПУТЬ
  if(fr4[P][2]==1)
	{
	 w(115,P,"");soob_for_oper=1;
   if(uprav==1)return(1);
   else return(2);
	}
  for(k=0;k<10;k++)if((BEDA[k]&0xfff)==P)break;
  if(k==10)for(k=0;k<10;k++)if(BEDA[k]==0)break;
  if(k==10)for(k=0;k<10;k++)BEDA[k]=0;
  if(fr3[P][5]==1){w(104,P,"");return(1);}//НЕИСПРАВЕН УЧАСТОК
  if((uprav==0)&&(avto==0))
  {
    if(mane==0)
    {
			Test=P|0x1000;
    	if((Test&BEDA[k])!=Test)
    	if((osya<2)&&(zanyat(P,avto)==1))goto brak;
    }
    Test=P|0x2000;
    if((Test&BEDA[k])!=Test)
    if((osya<3)&&(zamknut(P,avto)==1))
    { if(AVARI==1){home(modi);finish_strelok();klaval=0;return(10);}
      goto brak;
    }
    Test=P|0x4000;
    if((Test&BEDA[k])!=Test)
    if((osya<4)&&(razdelan(P,avto)==1))
    { if(AVARI==1){home(modi);finish_strelok();klaval=0;return(10);}
      goto brak;
    }
    return(0);
  }
  else
  { if(zanyat(P,avto)==1) return(1);
    if(zamknut(P,avto)==1) return(1);
    if(razdelan(P,avto)==1) return(1);
    return(0);
  }
brak:
  BEDA[k]=BEDA[k]|Test;
  soob_for_oper=0;
  return(1);
}
//----------------------------------------------------
int zamknuto(int pu,int PPU,int avt)
{
  int chkm,nkm,bit_ch,bit_n;
#ifdef NALAD  
  nom_func("430");
#endif          
  if((fr3[pu][1]==0)&&(fr3[pu][2]==0))return(0);//если путь разомкнут
  else//если путь замкнут
    if((manevro==0)&&(mane==0))//если поездной
    {
      if(avt==0)w(217,pu,"");//ЗАДАН МАРШРУТ НА ПУТЬ
      return(1);
    }
    else//если маневровый маршрут
    {
      chkm=fr1[pu][11]&0xFFF;//объект для ЧКМ
      nkm=fr1[pu][12]&0xFFF;//объект для НКM
      bit_ch=(fr1[pu][11]&0xF000)>>12;//
      bit_n=(fr1[pu][12]&0xF000)>>12;
      if((fr3[pu][1]==1)||(fr3[pu][2]==1))//если ЧИ или НИ под током
      {
        if((fr3[chkm][bit_ch]==0)&&(fr3[nkm][bit_n]==0))
        {
          if(avt==0)w(8,pu,"");//ЗАДАН ПОЕЗДНОЙ МАРШРУТ НА ПУТЬ
          return(1);
        }
      }
      return(0);
    }
}
//----------------------------------------
int zanyato(int pu,int avt)
{ int op=pu;
#ifdef NALAD  
  nom_func("432");
#endif       
  if(fr3[pu][0]==0) return(0);//если путь свободен
  if((mane==1)||(manevro==1))//если задается маневровый маршрут
  { if(pu==END)return(0);//если путь является концом маршрута
    if(fr1[nach_marsh][1]==fr1[end_marsh][1])//если сигналы попутные
    { if(fr1[nach_marsh][1]==1) op=pu+1;//если маршрут нечетный - вперед по базе
      else op=pu-1;//если маршрут четный по базе назад
      if(op==END) return(0);//если ближайший сигнал - конец - можно
    }
    else//если хотят ехать за сигнал ограничивающий путь
    { if(avt==0)w(100,pu,"");//НЕВОЗМОЖЕН МАНЕВРОВЫЙ МАРШРУТ ЧЕРЕЗ ПУТЬ
      return(1);
    }
  }
  else//если поездной
  { if(fr1[pu][0]==4)w(94 ,pu,"");//если хотят на занятый УП - ЗАНЯТ УЧАСТОК
    else
      if((fr1[pu][1]==0)&&(fr1[pu][2]==0))//если путь приемо-отправочный
      {
        if(avt==0)w(106,pu,"");//ЗАНЯТ ПУТЬ
      }
      else if(avt==0)w(107,pu,"");//ЗАНЯТ УЧАСТОК УДАЛЕНИЯ
    return(1);
  }
}
//-------------------------------------------
//---------------------------------------------
form_kom_avtod()
{ //процедура формирования команды на установку автодействия для передачи в
  //резервную ПЭВМ
  int i11;
  unsigned char kod;
#ifdef NALAD  
  nom_func("74");
#endif      
  if(DISK!=0)return;
  mane=0;
  manevro=0;
  //'@'-все откл.; 'A'-вкл.нечет.(откл. чет.)
  //'B'-вкл.чет.(откл.нечет.);'C'-вкл.четн. и нечет.
  kod='@'+cha*2+na;
  if(buf_ko_p[0]!=0)//если первый буфер команд не пустой
  {
    buf_ko_p2[0]='(';//начать заполнение второго буфера
    buf_ko_p2[1]='Z';//начать заполнение второго буфера
    buf_ko_p2[2]='A'; //автодействие
    buf_ko_p2[3]=kod;//записать в буфер код (включение/отключение
    for (i11=4;i11<=8;i11++)buf_ko_p2[i11]=124;//в свободные байты - заполнитель
    buf_ko_p2[9]=check_sum(buf_ko_p2);//получить и записать контрольную сумму
    buf_ko_p2[10]=')';
    flms=2;
  }
  else//если первый буфер пустой - то все то же самое для первого буфера
  {
    buf_ko_p[0]='(';//начать заполнение второго буфера
    buf_ko_p[1]='Z';
    buf_ko_p[2]='A';
    buf_ko_p[3]=kod;
    for (i11=4;i11<=8;i11++)buf_ko_p[i11]=124;
    buf_ko_p[9]=check_sum(buf_ko_p);//получить и записать контрольную сумму
    buf_ko_p[10]=')';
    flms=1;//установить признак-требование передачи сообщения в соседнюю ПЭВМ
  }
   kom_v_bufer_pvm(1,"");
}
//------------------------------------------------------------
formkps(int kod)
{
  int nomer,podgr,i18,j18,n=0,SDVIG=0,FN=0,FIN=0,kkol=0;
#ifdef NALAD
  nom_func("86");
#endif
  if(DISK!=0)return;
  if(buf_ko[2]==0)
  {
  	buf_ko[2]='C';
  	if(Opred()<0)return;//найти стрелку, входящую в сообщения (имеет смысл для спаренных)
  	n=point;
  	if(fr1[n][13]==1){buf_ko[1]=ZAGO_MPSU(0x61);SDVIG=0;FN=0;FIN=STR1;}
#ifdef KOL_SOO2
  	else {buf_ko[1]=ZAGO_MPSU(0x62);SDVIG=0;FN=STR1;FIN=FN+STR2;}
#endif
  	nomer=0xAAAA;
  	for(i18=FN;i18<FIN;i18++)for(j18=0;j18<5;j18++)
  	if(spstr[i18][j18]==n){podgr=podgruppa[i18+SDVIG-FN];nomer=j18;break;}
  	if(nomer==0xAAAA) return;
  	buf_ko[3]=podgr;
  	kkol=kod;
  	if(fr4[point][1]==1)kkol=kkol|0x04;//если стрелка на макете
  	if(AVARI==1)kkol=kkol|0x10;//если аварийный перевод
  	else
    	if((AVARIIN==1)&&(fr4[point][1]==0))kkol=kkol|0x08;
  	for (j18=0;j18<5;j18++)
  	if(j18==nomer)buf_ko[j18+4]=kkol;
  	else  buf_ko[j18+4]=124;
  	buf_ko[9]=check_sum(buf_ko);
  	buf_ko[0]='(';
  	buf_ko[10]=')';
  	if(AVARI==1)
  	{
    	for(i18=1;i18<10;i18++){buf_ko_vsp[i18]=buf_ko[i18];buf_ko[i18]=0;}
    	buf_ko_vsp[0]=point;
      if(tst_chet(point)==0)TIMER_SOB(AVAch,1,AV_bch);
      else TIMER_SOB(AVAn,1,AV_bn);
    	return;
  	}
  	flagoutmsg=1;
  	pooo[point]=biostime(0,0l);
  }
  else
  {
  	buf_ko_mm[2]='C';
  	if(Opred()<0)return;//найти стрелку, входящую в сообщения (имеет смысл для спаренных)
  	n=point;
  	if(fr1[n][13]==1){buf_ko_mm[1]=ZAGO_MPSU(0x61);SDVIG=0;FN=0;FIN=STR1;}
#ifdef KOL_SOO2
  	else {buf_ko_mm[1]=ZAGO_MPSU(0x62);SDVIG=0;FN=STR1;FIN=FN+STR2;}
#endif
  	nomer=0xAAAA;
  	for(i18=FN;i18<FIN;i18++)for(j18=0;j18<5;j18++)
  	if(spstr[i18][j18]==n){podgr=podgruppa[i18+SDVIG-FN];nomer=j18;break;}
  	if(nomer==0xAAAA) return;
  	buf_ko_mm[3]=podgr;
  	kkol=kod;
  	if(fr4[point][1]==1)kkol=kkol|0x04;//если стрелка на макете
  	if(AVARI==1)kkol=kkol|0x10;//если аварийный перевод
  	else
    	if((AVARIIN==1)&&(fr4[point][1]==0))kkol=kkol|0x08;
  	for (j18=0;j18<5;j18++)
  	if(j18==nomer)buf_ko_mm[j18+4]=kkol;
  	else  buf_ko_mm[j18+4]=124;
  	buf_ko_mm[9]=check_sum(buf_ko_mm);
  	buf_ko_mm[0]='(';
  	buf_ko_mm[10]=')';
 		flagoutmsg=11;
  	pooo[point]=biostime(0,0l);
  }
}
//--------------------------------------------------------------
form_kom_vsp()
{
  //процедура формирования команды для вспомогательного перевода стрелки
  int i18=0;
#ifdef NALAD
  nom_func("82");
#endif        
  if(DISK!=0)return;
  if(AVARI==1)//если установлен признак аварийного перевода стрелки 
  {
    for(i18=0;i18<=8;i18++)
    {
      buf_ko[i18+1]=buf_ko_vsp[i18+1];//перезаписать команду в исполнительный буфер 
      buf_ko_vsp[i18+1]=0;//вспомогательный буфер освободить
    }
    flagoutmsg=1;//установить флаг-требование на пересылку команды в ТУМС
    w(123,buf_ko_vsp[0],"");//"ПОСЫЛАЕМ КОМАНДУ НА ПЕРЕВОД СТРЕЛКИ"
    buf_ko_vsp[0]=0;
  }
}
//-----------------------------------------------------------------
int kom_v_bufer_pvm(int tip_oper, unsigned char WCHAR)
{
  int i;
#ifdef NALAD  
  nom_func("128");
#endif          
  if(DISK!=0)return;
  if(pust_pvm>1)return(-1);//если потеряна связь с соседней ПЭВМ
  if(tip_oper==0)// если информация
  {
    REG_INF[0]=0x1e;
    REG_INF[1]=WCHAR;REG_INF[2]=WCHAR;
    REG_INF[3]=0x1f;
    MY_INF=1;
    return(0);
  }
  if(tip_oper==1)// если команда 
  {
    if(flms==2)for(i=0;i<11;i++)REG_COM[i]=buf_ko_p2[i];
    else
      if(flms==1)for(i=0;i<11;i++)REG_COM[i]=buf_ko_p[i];
      else for(i=0;i<11;i++)REG_COM[i]=buf_ko[i];
    MY_COM=1;
    flms=0;
    return(1);
  }
}
//--------------------------------------------------------------
int uze(int noper,int naps)
{
	int j;
#ifdef NALAD
  nom_func("385");
#endif
  j=ukaz_trass;
  j--;
  if(fr1[trassa[j]][0]==6)return(-1);
  while(j!=0)
  { if(trassa[j]==noper)
    { if(naps==1) return(1);
      else
        if(noper!=0) return(1);
    }
    j--;
  }
  return(0);
}
