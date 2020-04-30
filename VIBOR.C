#include "bla.h"
#include "opred.h"
#include <bios.h>
#include <graphics.h>
#include <stdio.h>
#include <dos.h>

//-----------------------------------------------
int str_Makst(int nom)
{
  int ro=0;
  for(ro=0;ro<kol_OB_UPR;ro++)
  { if(markery[ro][6]==nom) return(ro);
    if(ro>=Ok) return(0);
  }
  return(0);
}

//------------------------------------------------------
int strelka_v_makete()
{
  int ro;
       
  for(ro=0;ro<kol_OSN;ro++)if((fr4[ro][1]==1)&&(fr1[ro][0]==1))return(ro);
  return(0);
}

//-------------------------------------------------------
vkl_otkl_maket(int nom)
{
  int nomer;
#ifdef NALAD  
  nom_func("401");
#endif        
  if(DISK!=0)return;
  if(markery[nom][7]!=1)
  { w(17,999,"");//ЭТО НЕ СТРЕЛКА 
    maket=0;vkl_kno(MAKET,8);home(modi);
    return;
  }
  nomer=markery[nom][6];
  if(fr4[nomer][1]==0) vopros(3,nomer,73,"?");//УСТАНОВИТЬ НА МАКЕТ СТР.
  else vopros(3,nomer,74,"?");//СНЯТЬ С МАКЕТА СТР.
  point=nomer;
  maket=2;
  vih_vopr=1;
}

//-------------------------------------------------------
v_o_ma(int nom)
{
  int BUK,para;
  unsigned char BUKA;
#ifdef NALAD  
  nom_func("386");
#endif      
  if(DISK!=0)return;
  if(klaval==13)
  {
    //ТЕЛЕУПРАВЛЕНИЕ ОТКЛЮЧЕНО-КОМАНДЫ НЕ ВОЗМОЖНЫ
    if(TELEUP!=1){ w(58,999,"");return;}
    //ВКЛЮЧЕНО АВТОДЕЙСТВИЯ ПО 1П
    if(fr4[nom][0]&4){w(91,999,"");return;}
    if(fr1[nom][12]!=9999)
    { para=fr1[nom][12];
      //ВКЛЮЧЕНО АВТОДЕЙСТВИЯ ПО 1
      if(fr4[para][0]&4){w(91,999,"");return;}
    }
    //ВКЛЮЧЕНО АВТОДЕЙСТВИЯ ПО 2П
    if(fr4[nom][0]&2){w(90,999,"");return;}
    if(fr1[nom][12]!=9999)
    { para=fr1[nom][12];
      //ВКЛЮЧЕНО АВТОДЕЙСТВИЯ ПО  2П
      if(fr4[para][0]&2){w(90,999,"");return;}
    }
    //УСТАНАВЛИВАЕМ НА МАКЕТ СТРЕЛКУ
    if(fr4[nom][1]==0){fr4[nom][1]=1;w(112,nom,"");vkl_kno(MAKET,10);}
    //СНИМАЕМ С МАКЕТА СТРЕЛКУ
    else {fr4[nom][1]=0; w(75,nom,"");vkl_kno(MAKET,8);}
  }
  else return;
  BUK=fr4[nom][0];
  BUKA=fr4[nom][0]&1;
  if(fr4[nom][1]==1){BUK=BUK|0x200;BUKA=BUKA|2;}
  if(fr4[nom][2]==1)BUKA=BUKA|4;
  if(fr1[nom][12]==0)BUKA=BUKA|0x8;//установить признак неосновной
  ris_ogr_str(nom,BUK);
  okrasklav(nom);
  if(fr1[nom][12]!=9999)
  {
    TEST=2;
    para=poisk_ras(fr1[nom][2],nom);
    fr4[para][1]=fr4[nom][1];
    ris_ogr_str(para,BUK);
    okrasklav(para);
  }
  BUKA=BUKA|0x80;
  form_kom_str(nom,BUKA);
  maket=0;
}

//-----------------------------------------------------
otkl(int nomer)
{ int BUK,x23,y23,para,kudo,avtr,ui=0;
  unsigned char BUK1;
#ifdef NALAD  
  nom_func("205");
#endif       
  if(DISK!=0)return;
  home(modi);
  if((STATUS==0)||(STATUS==2))
  { w(140,999,"");
vsi:
    vkl_kno(VSPZ,8);// погасить кнопку макет 
    return;
  }
  if(TELEUP!=1) goto vsi;
  t(0);
  x23=fr2[nomer][0];y23=fr2[nomer][1];
  // найти парную стрелку 
  TEST=2;
  if(fr1[nomer][12]!=9999)para=poisk_ras(fr1[nomer][2],nomer);
  else para=0;
  if(punkt_N==3)// выбран нижний пункт меню:закрыть-открыть движение
  {
#ifdef AVTOD
    avtr=prov_ele_avtod(nomer);
    if(avtr==1){w(245,999,"");return;}
    if(avtr==2){w(244,999,"");return;}
#endif
    setlinestyle(0,0,3);
    if(fr4[nomer][2]==0)//если стрелка пока не закрыта для движения
    { fr4[nomer][2]=1; // установить признак закрытия для движения
      setcolor(LIGHTRED);
    }
    else // если стрелка закрыта для движения
    {
      fr4[nomer][2]=0;// снять закрытие для основной стрелки 
      setcolor(cvv);
    }
    if(fr1[nomer][7]==1)kudo=-1;// если вход нечетный
    else kudo=1;// если вход четный
    kudo=OBRAT*kudo; // учитываем ориентацию экрана
    x23=x23-2*kudo; // вычисляем точку оси X
    line(x23,y23-5,x23,y23-2);
    line(x23,y23+2,x23,y23+5);
  }
  else
  if(punkt_N==2)//выбран верхний пункт меню: включить-выключить управление
  { setlinestyle(0,0,0);
    // если не выключена из управления, то выключить 
    if((fr4[nomer][0]&1)==0)fr4[nomer][0]=fr4[nomer][0]|1;
    //если выключена из управления, то включить
    else fr4[nomer][0]=fr4[nomer][0]&0xfffe;

  }
  disco();
  BUK1=0;//код для передачи в соседнюю ПЭВМ
  BUK=fr4[nomer][0];//код для отрисовки 
  if((BUK&1)==1)BUK1=1;
  if(fr4[nomer][1]==1){BUK=BUK|0x200;BUK1=BUK1|2;}
  else BUK=BUK&0xfdff;
  if(fr4[nomer][2]==1)BUK1=BUK1|4;
  if(fr1[nomer][12]==0)BUK1=BUK1|0x8;//если не основная
  ris_ogr_str(nomer,BUK);
  okrasklav(nomer);
  if(para>0)
  { fr4[para][0]=fr4[nomer][0];
    fr4[para][1]=fr4[nomer][1];
    ris_ogr_str(para,BUK);
    okrasklav(para);
  }
  BUK1=BUK1|0x80;
  if(prorisovka==0)form_kom_str(nomer,BUK1);//отправить команду в соседнюю ПЭВМ
  return;
}

//-----------------------------------------------------------
nach_zakr(int nomer,int otkuda)
{
//otkuda=0-закрытие для движения
//otkuda=1-остальное
  int x13,y13,kudo,kuk=2,BUKA;
#ifdef NALAD  
  nom_func("178");
#endif
  if(ZAGRUZKA!=0)return;
  if((klo==1)||(help>0)||(nikuda==1))return;
  if(fr1[nomer][0]!=1) return;
  x13=fr2[nomer][0];
  y13=fr2[nomer][1];
  BUKA=fr4[nomer][0];
  if(fr4[nomer][1]==1)BUKA=BUKA|0x200;//если макет
  else BUKA=BUKA&0xfdff;
  ris_ogr_str(nomer,BUKA);
  if(fr4[nomer][2]==1)
  {
    setcolor(LIGHTRED);
    setlinestyle(0,0,3);
    if(fr1[nomer][7]==1) kudo=-1;
    else kudo=1;
    kudo=OBRAT*kudo;
    x13=x13-kuk*kudo;
    line(x13,y13-5,x13,y13-2);
    line(x13,y13+2,x13,y13+5);
  }
  else
  {
    if(otkuda==1)
    {
      setcolor(cvv);
      setlinestyle(0,0,3);
      if(fr1[nomer][7]==1) kudo=-1;
      else kudo=1;
      kudo=OBRAT*kudo;
      x13=x13-kuk*kudo;
      line(x13,y13-5,x13,y13-2);
      line(x13,y13+2,x13,y13+5);
    }
  }
  okrasklav(nomer);
}

//------------------------------------------------------
int test_mp()
{
  int aa,n_,ab,objekt;
  n_=nach_marsh;
  if((n_==0)||(end_marsh==0))return(0);
  objekt=markery[modi][6];
  //n_=markery[n_m][6];  //получить номера объектов
  aa=fr1[objekt][4];//получить характеристику сигнала

  if(End_vara==2)//если выбирался вариантный маршрут 
  {
    //если сигнал конца-совмещенный или принадлежит сквозному маршруту
    if((fr1[objekt][6]==2)||(fr1[objekt][4]==2))return(0);

     //если маршрут-маневровый и сигнал конца маршрута-маневровый
    if((mane==1)&&(fr1[objekt][2]==0))return(0);

    // если маршут-поездной и сигнал конца-поездной
    if((mane==0)&&(fr1[objekt][2]==1))return(0);

    return(1);// в других случаях для варианта  отказ 
  }
  // если выбирался не вариантный маршрут, начало от 2-х белых и нет конца 2-х белых 
  if((mane==0)&&(fr1[n_][6]==3)&&( fr1[objekt][4]!=3))return(1);
  if((mane==0)&&(fr1[objekt][6]==0))return(1);//маршрут-поездной,конец-маневровый
//  if((mane==1)&&(fr1[objekt][6]==1))return(1);//маршрут-маневровый,конец-поездной
  // если начало от поездного или совмещенного
  if(fr1[n_][6]>0)//если начало совмещенный или с двумя белыми
  { if(fr1[objekt][4]==fr1[n_][6])return(0);//если конец соответствует началу

    // если стоим на вариантной точке
    if(((fr1[objekt][4]==10)||(fr1[objekt][4]==11))&&(End_vara==0))return(0);
    if((mane==1)&&(aa==0))return(0);//если маневровый маршрут и вариантов нет
    if((mane==0)&&(aa==1)&&(manevro==0))return(0);//если поездной и сигнал у стрелки в пути
    if((mane==1)&&(aa==1)&&(manevro==0))return(2); //если маневровый и сигнал у стрелки в пути
    if((mane==1)&&(aa==1)&&(manevro==1))return(0);//если маневровый сигнал и маневровый маршрут и сигнал у стрелки в пути
  }
  else // если начало от маневрового
  {
    if(fr1[objekt][6]==2) return(0);//если конец совмещенный
    if((fr1[n_][5]==objekt)&&(End_vara==0)) return(0); //если вариант куда надо
    if(aa==1)
    {
      ab=fr1[objekt][2];//получить признак сигнала конца
      // если конец поездной
      // если маршрут маневровый,начало маневровый и второй проход
      // если первый вход
      if(ab==1)
      { if((mane==1)&&(manevro==1)&&(siv==1)){siv=0;return(0);}
        if(siv==0){siv=1;return(2);}
      }
    }
    if((manevro==1)&&(aa==0))return(0);

    if((manevro==0)&&(aa==1)&&( mane==0))return(0);

    if((aa==0)&&(mane==1))return(0);
  }
  return(0);
}
/*-----------------------------------------------------------------*/
/*процедура организации реакции системы на выбор оператором сигнала   */
/*-----------------------------------------------------------------*/
make_signal()
{
	int mp,ii;
	mp=markery[modi][6];
	if(fr3[mp][12]!=0){w(263,mp,"");return;}     
	if(DISK!=0)return;
#ifdef AVTOD
	mp=prov_si_avtod(markery[modi][6],0);
	if(mp==1){w(245,999,"");return;}
	if(mp==2){w(244,999,"");return;}
#endif
	if(komanda2[fr1[markery[modi][6]][13]-1]!=0){w(51,999,"");return;}
	if(vozvr==2)//если выбранный сигнал является вторым
	{
		if(End_vara==0)
		{ if((markery[modi][7]==7)||(Zdem_vibor_marshruta==0))vopr_mar();//если может быть вариант
			if(Zdem_vibor_marshruta==1)
			//переместить курсор к меню
			{
				regs.x.ax=4;regs.x.cx=630; regs.x.dx=50; int86(0x33,&regs,&regs);
				menu_N=5;
				punkt_N=1;
				klaval=-1;
				regs.x.ax=4;
				regs.x.cx=590;
        regs.x.dx=50;
        int86(0x33,&regs,&regs);
        X_m=590;
        Y_m=50;
        obnov_kur_mouse(590,50);
        menu1();
        return;
      }
    }
    //if((nach0_marsh==end_marsh)&&(end_marsh!=0))
    end_marsh=markery[i3][6];
    if(test_mp()!=0)//если нет соответствия конца,начала и категории маршрута
    { w(134,999,"");//ТОЧКА КОНЦА МАРШРУТА УКАЗАНА НЕВЕРНО 
      home(modi);//вернуть курсор
      soob_for_oper=1; sbros=1;
      whole_finish();
      return;
    }
    End_vara=0; povt2=1;
    marsh1();
    return;
  }
  if(uprav==0)//если раздельное управление
  { if(markery[modi][7]==7)return;//для вариантной точки 
    if(vrem==0)
    { point=markery[modi][6];
      if(fr1[point][6]!=1)//если не "поездной"
      { if(fr1[point][6]>0)//если не чисто маневровый
        { menu_N=1;//предложить выбор "поездной/маневровый"
          punkt_N=1;//предварительно выбрать отмену
          klaval=-1;
          //переместить курсор к меню
          regs.x.ax=4;//переместить курсор к меню
          regs.x.cx=590;
          regs.x.dx=50;
          int86(0x33,&regs,&regs);
          X_m=590;Y_m=50;
          obnov_kur_mouse(590,50);
          menu1();
          zapretvybora=0;vrem=1;
          return;
        }
        else//если маневровый
        {
          mane=1; vrem=1; puti=1; zapretvybora=1;
          otkrs();
          vrem=0;
        }
      }
      else//если поездной
      { mane=0; vrem=1; puti=1; zapretvybora=1;
        otkrs();
        vrem=0;
      }
    }
    else return;
  }
  else//если маршрутное управление
  { end_marsh=markery[modi][6];//назначить выбранный сигнал концом маршрута
    if((fr1[end_marsh][13]==1)&&(komanda2[0]!=0))
    { w(51,999,"");//ЕЩЕ НЕ ВЫПОЛНЕНА ПРЕДЫДУЩАЯ КОМАНДА 
      return;
    }
    if((fr1[end_marsh][13]==2)&&(komanda2[1]!=0))
    { w(51,999,"");//ЕЩЕ НЕ ВЫПОЛНЕНА ПРЕДЫДУЩАЯ КОМАНДА 
      return;
    }
    if(fr1[end_marsh][6]!=1)//если не "поездной"
    { if(fr1[end_marsh][6]>0)//если конец не чисто маневровый
      { //и выбраны первый или второй, то признак маневра скопировать 
        if((povt2==1)||(vozvr==2))manevro=mane;
        else//иначе
        { if(markery[modi][7]==7){home(modi);return;}
          point=end_marsh;//запомнить точку выбранного сигнала
          po_ma=1;//назначить признак совмещенного сигнала
          menu_N=1;//предложить выбор "поездной/маневровый"
          punkt_N=1;  klaval=-1;
          //переместить курсор к меню
          regs.x.ax=4;//переместить курсор к меню
          regs.x.cx=590;
          regs.x.dx=50;
          int86(0x33,&regs,&regs);
          X_m=590;Y_m=50;
          obnov_kur_mouse(590,50);
          regs.x.ax=7;//задать границы для мыши по горизонтали
      		regs.x.cx=590;
      		regs.x.dx=630;
      		int86(0x33,&regs,&regs);
      		regs.x.ax=8;//задать границы для мыши по вертикали
      		regs.x.cx=5;
      		regs.x.dx=50;
      		int86(0x33,&regs,&regs);
          menu1();
          zapretvybora=0;
          return;
        }
      }
      else mane=1;
    }
    else po_ma=0;//если ранее был признак "поездной/маневровый"
    vozvr=2;
    mp=test_mp();//проверить соответствие выбранной категории для сигналов ограничивающих
    if((povt2==1)&&(mp!=0))//если выбирается конец (а начало уже выбрано)
    { w(134,999,"");//ТОЧКА КОНЦА МАРШРУТА УКАЗАНА НЕВЕРНО
      //вернуться в исходное
      home(modi);
      soob_for_oper=1;
      sbros=1;
      whole_finish();
      return;
    }
    //проверить возможность установки маршрута
    if((nach_marsh==0)||(end_marsh==0))koni();
    //если конец маршрута не указан-затребовать указание конца
  }

  return;
}
//-----------------------------------------------------
make_put()
{ int nomer,avtr;
#ifdef NALAD  
  nom_func("159");
#endif
  if(DISK!=0)return;
#ifdef AVTOD
  avtr=prov_ele_avtod(nomer);
  if(avtr==1){w(245,999,"");return;}
  if(avtr==2){w(244,999,"");return;}
#endif
  if(uprav==1)poka=0;
  if(zakr==0)
  { puti=1;nomer=markery[modi][6];
    if(fr4[nomer][2]==0)vopros(3,nomer,68,"");//ЗАКРЫТЬ ПУТЬ ДЛЯ ДВИЖЕНИЯ?
    else vopros(3,nomer,69,"");//ОТКРЫТЬ ПУТЬ ДЛЯ ДВИЖЕНИЯ?
    zapretvybora=1;
    zakr=1;
  }
  else
  if(zakr==1)
  {
    zakroy(modi);
    zapretvybora=0;
    zakr=0;
    puti=0;
  }
    return;
}
/******************************************************************/
zakroy(int nn)
{
  int zoz=0,zo=0,xc,yc,nomer,BUK=0xC0,BUKn=0xCf;
#ifdef NALAD  
  nom_func("427");
#endif          
  if(DISK!=0)return;
  if(klaval==13)
  //НЕВОЗМОЖНА ВЫДАЧА КОМАНДЫ С РЕЗЕРВНОЙ ПЭВМ
  { if((STATUS==0)||(STATUS==2)){w(140,999,"");goto end;}
    if(TELEUP!=1)goto end;
    t(0);nomer=markery[nn][6];
#ifdef AVTOD
    if(fr4[nomer][2]==0)
    { if(na==1)
      { for(zo=0;zo<2;zo++)for(zoz=0;zoz<K_EL;zoz++)
        //ВКЛЮЧЕНО АВТОДЕЙСТВИЯ ПО 1П
        if(nomer==Avto_el[zo].Elems[zoz]){w(91,999,"");goto end;}
      }
      if(cha==1)
      { for(zo=2;zo<4;zo++)for(zoz=0;zoz<K_EL;zoz++)
        //ВКЛЮЧЕНО АВТОДЕЙСТВИЕ ПО 2П
        if(nomer==Avto_el[zo].Elems[zoz]){w(90,999,"");goto end;}
      }
    }
#endif
    if(fr1[nomer][8]>=1010){xc=markery[nn][4];yc=markery[nn][5];}
    moveto(xc,yc);
    if(fr4[nomer][2]==0)
    { fr4[nomer][2]=1;
      setcolor(LIGHTRED);
      //settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
      outtextxy(xc,yc,pako[nomer]);
      w(115,nomer,"");//ДВИЖЕНИЕ ЗАПРЕЩЕНО ПУТЬ N#
      if(fr4[nomer][0]==1)BUK=BUK|0x01;
      if(fr4[nomer][1]==1)BUK=BUK|0x02;
      BUK=BUK|0x04;
    }
    else
    { fr4[nomer][2]=0;
      setcolor(8);
      //settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
      outtextxy(xc,yc,pako[nomer]);
      w(114,nomer,"");//ДВИЖЕНИЕ РАЗРЕШЕНО ПУТЬ N#
      if(fr4[nomer][0]==0)BUKn=BUKn&0xCe;
      if(fr4[nomer][1]==0)BUKn=BUKn&0xCd;
      BUK=BUKn&0xCb;
    }
    disco();
    form_kom_put(nomer,BUK);
    add(0,'<');
  }
  else return;
end:
  home(nn);
  return;
}
/**********************************************************/
make_smena()
{
#ifdef NALAD  
  nom_func("162");
#endif     
  if(DISK!=0)return;
  if(uprav==1)poka=0;
  if(oppp==0)smen_napr(fr1[markery[modi][6]][9]);
  else smena(markery[modi][6]);
  return;
}
//-------------------------------------------------
make_razdelka()
{  // для резервной машины нет выполнения
#ifdef NALAD  
  nom_func("160");
#endif     
  if(DISK!=0)return;
  if(STATUS!=1){w(140,999,"");soob_for_oper=1;return;}
  if(TELEUP!=1)return;//при отключенном телеуправлении нет выполнения
  if((fr3[Start_R+WAZO][2]==1)&&(fr1[point][3]==9999))//если вкл.выдержка и объект = СП
  { //если включена выдержка на ИР
    if(fr3[Start_R+WAZO][2]==1)w(15,999,"");//КОМПЛЕКТ ИСК.РАЗМЫКАНИЯ ЗАНЯТ
    zalet=0;//сбросить флаг выдачи команды ИР
    was[markery[i3][7]-10]=0;//обнулить для этого объекта ячейку разделки
    fr3[point][9]=0;//сбросить элемент памяти для объекта 
    vtora=0; //сбросить признак ожидания выполнения предварительной команды
    home(modi);//курсор домой 
    return;
  }
  if(uprav==1) poka=0;
  if((all_null(i3)==1)&&(vtora==0))
  { w(51,999,"");//ЕЩЕ НЕ ВЫПОЛНЕНА ПРЕДЫДУЩАЯ КОМАНДА 
    home(modi);return;
  }
  //если вопрос не задавался, данный объект имеет разделку и она не начиналась
  if((zalet==0)&&(nashel(modi)!=1)&&(fr3[point][0]==0)&&(fr3[point][2]==0))
  { //задать вопрос о размыкании
    w(fr1[point][6],fr1[point][10],"?");//ИСКУССТВЕННОЕ РАЗМЫКАНИЕ ПО
    was[markery[i3][7]-10]=i3;//зафиксировать объект
    zalet=1; //установить признак задания вопроса
    zapretvybora=1; //зафиксировать курсоры
    return;
  }
  else
  {
    zalet=0;
    was[markery[i3][7]-10]=0;
    fr3[markery[i3][6]][9]=0;
    vtora=0;home(i3);return;
  }
}
//---------------------------------------------------------
//процедура инициализации выдаычи ответственной команды
make_otvetst()
{
  int isp,pred;//номера объекта исполнительного
  int bit_p,bit_i;//номера битов предварительной и исполнительной команд
#ifdef NALAD  
  nom_func("156");
#endif       
  if(DISK!=0)return;//при просмотре архива нет выполнения
  // для резервной машины нет выполнения
  if(STATUS!=1){w(140,999,"");soob_for_oper=1;return;}
  if(TELEUP!=1)return;//при отключенном телеуправлении нет выполнения
  pred=fr1[point][2];isp=fr1[point][3];
  bit_p=(fr1[point][4]&0xff00)>>8;
  bit_i=fr1[point][4]&0xff;
  if(uprav==1) poka=0;
  if(((fr3[pred][bit_p]+fr3[isp][bit_i])==0)&&(vtora==0))
  { w(229,999,"");//ОБЪЕКТ УПРАВЛЕНИЯ УЖЕ В ТРЕБУЕМОМ СОСТОЯНИИ
    home(modi);return;
  }
  if(((fr3[pred][bit_p]+fr3[isp][bit_i])==1)&&(vtora==0))
  { w(51,999,"");//ЕЩЕ НЕ ВЫПОЛНЕНА ПРЕДЫДУЩАЯ КОМАНДА 
    home(modi);return;
  }
  //если вопрос не задавался, данный объект имеет разделку и она не начиналась
  if((zalet==0)&&(fr3[pred][bit_p]==fr3[isp][bit_i]))
  { //задать вопрос о размыкании
    w(fr1[point][5],999,"?");//отключить(включить) объект ?
    zapusk=1; //установить признак задания вопроса 
    zapretvybora=1; //зафиксировать курсоры 
    return;
  }
  else
  { //если вопрос задавался 
    zapusk=0;vtora=0;home(i3);return;
  }
}
//-----------------------------------------------------
make_neotv()
{
#ifdef NALAD  
  nom_func("154");
#endif     
  if(DISK!=0)return;
  poka=0;
  if(oppp==0)
  {
    vkl_neot(markery[modi][6]);
    zapretvybora=1;
  }
  else
  {
    neot(markery[modi][6]);
    zapretvybora=0;
  }
}
//-------------------------------------------------------
vkl_neot(int nom)
{
#ifdef NALAD  
  nom_func("399");
#endif    
  if(fr1[nom][6]!=9999)//если есть текст
  {
    setfillstyle(1,14),setcolor(4);
    vopros(1,9999,fr1[nom][5],"?");
  }
  oppp=1;puti=1;return;
}
//-------------------------------------------------------------
neot(int nom)
{ unsigned int bit_akt,zn_akt,i,koda;
#ifdef NALAD  
  nom_func("184");
#endif 
	if(klaval == 13)
	{
		bit_akt = (fr1[nom][4]&0xff00)>>8;
		if(fr3[nom][bit_akt] == 1)
		{
			w(229,nom,"!");
			goto out;
		}
		else
			w(fr1[nom][6],999,"");
		koda = 'N';
		point = nom;//установить номер точки для выдачи команды
		if(form_kosig(koda) == 1)
			return;//если формирование команды не удалось - выход
		buf_ko[9] = check_sum(buf_ko);//добавить контрольную сумму
		pooo[nom] = biostime(0,0L);//зафиксировать время выдачи
		flagoutmsg = 1;//установить флаг-требование на передачу в ТУМС
out:
		oppp = 0;
		puti = 0;
		home(modi);
		return;
	}
	else
	return;
}
//------------------------------------------------------------------

make_pereezd()
{
#ifdef NALAD  
  nom_func("158");
#endif     
  if(DISK!=0)return;
  poka=0;
  if(oppp==0)
  {
    kom_per(markery[modi][6]);
    zapretvybora=1;
  }
  else
  {
    k_per(markery[modi][6]);
    zapretvybora=0;
  }
}
/**********************************************/
vkl_kno(int nom,int CCV)
{
  int to=0,too=0,D=0;
  int xc,yc;
  char klopo[6]="";
#ifdef NALAD  
  nom_func("396");
#endif      
  if((nikuda==1)||(klo==1)||(help>0))return;
  for(to=0;to<6;to++)klopo[to]=0;
  xc=markery[nom][4]-4;
  yc=markery[nom][5]-4;
  setfillstyle(SOLID_FILL,CCV);
  if((pusto&3)!=0)setfillstyle(SOLID_FILL,LIGHTCYAN);
  if(nom==MAKET)
  {
		setfillstyle(LTBKSLASH_FILL,CCV);
		bar(xc-17,yc,xc+25,yc+10);
		for(to=0;to<kol_OSN;to++)
		if((fr4[to][1]==1)&&(fr1[to][0]==1))
		{
			//settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
			setcolor(WHITE);
			too=2;
			while(pako[to][too]!=':')
			{
				klopo[too-2]=pako[to][too];
				too++;
			}
			D=strlen(klopo);
			D=D*4;
			outtextxy(xc+5-D,yc+2,klopo);
			break;
		}
	}
	else
	{
		setfillstyle(SOLID_FILL,CCV);
		bar(xc,yc,xc+8,yc+8);
	}
}
//-----------------------------------------------------
make_knopka()
{
#ifdef NALAD  
  nom_func("151");
#endif     
  if(DISK!=0)return;
  poka=0;
  if(oppp==0) { vkl_knop(markery[modi][6]); zapretvybora=1; }
  else { knopa(markery[modi][6]); zapretvybora=0;}
}
//-------------------------------------------------------
make_knpk2()
{
#ifdef NALAD  
  nom_func("152");
#endif     
  if(DISK!=0)return;
  poka=0;
  if(oppp==0) { vkl_knop(markery[modi][6]); zapretvybora=1; }
  else { knopa(markery[modi][6]); zapretvybora=0;}
}
//-------------------------------------------------------
make_nemarsh()
{
#ifdef NALAD  
  nom_func("153");
#endif     
  if(DISK!=0)return;
  poka=0;
  if(oppp==0)
  {
    vkl_nemarsh(markery[modi][6]);
    zapretvybora=1;
  }
  else
  {
    nemarsh(markery[modi][6]);
    zapretvybora=0;
  }
}
//----------------------------------------------------------
make_dn()
{
#ifdef NALAD  
  nom_func("149");
#endif   
  if(DISK!=0)return;
  if (uprav==1) poka=0;
  if(oppp==0)
  {
    vkl_dn(markery[modi][6]);
    zapretvybora=1;
  }
  else
  {
    dn_au(markery[modi][6]);
    zapretvybora=0;
  }
}
//----------------------------------------------------

make_opoveshenie()
{
#ifdef NALAD  
  nom_func("155");
#endif     
  if(DISK!=0)return;
  if (uprav==1) poka=0;
  if (oppp==0)
  {
    vkl_opoveshe(markery[modi][6]);
    zapretvybora=1;
  }
  else
  {
    opoveshe(markery[modi][6],0);
    zapretvybora=0;
  }
}
//--------------------------------------------
make_per_kompl()
{
#ifdef NALAD  
  nom_func("157");
#endif     
  if(DISK!=0)return;
  if (oppp==0)
  {
    perekl_komp(markery[modi][6]);
    zapretvybora=1;
  }
  else
  {
    prkl(markery[modi][6]);
    zapretvybora=0;
  }

}
//--------------------------------------------
#ifdef OGRAD
make_ograd()
{
  if(DISK!=0)return;
  if(oppp==0)
  {
    kom_ograd(markery[modi][6]);
    zapretvybora=1;
  }
  else
  {
    k_ograd(markery[modi][6]);
    zapretvybora=0;
  }
}
#endif
//--------------------------------------------------
make_gri()
{
  int IV,nn1,nn2;
#ifdef NALAD  
  nom_func("150");
#endif     
  if(DISK!=0)return;
  if(fr1[point][1]==301)
  {
    nn1=point;
    nn2=fr1[point][3];
    if((fr3[nn1][2]!=0)||(fr3[nn2][2]!=0)){ w(15,999,"");  return; }
  }
  if(gri==0)
  {
    if(uprav==1)poka=0;
    if(fr3[point][2]==0)
    { w(20,999,"?"); //включить выдержку времени ?
      zapretvybora=1; gri=1; vih_vopr=1;
      return;
    }
    else w(15,999,""); //комплект искусственного размыкания занят
  }
  home(modi);
  zapretvybora=0;
  gri=0;
  return;
}
#ifdef POLUAVTOMAT
//---------------------------------------------------------
make_dso(int nom)
{
  if(DISK!=0)return;
  if(oppp==0)
  {
    kom_dso(markery[modi][6]);
    zapretvybora=1;
  }
  else
  {
    k_dso(markery[modi][6]);
    zapretvybora=0;
  }
}
/********************************************/
make_fdp(int nom)
{
  if(DISK!-0)return;
  if(oppp==0)
  {
    kom_fdp(markery[modi][6]);
    zapretvybora=1;
  }
  else
  {
    k_fdp(markery[modi][6]);
    zapretvybora=0;
  }
}
#endif
/********************************************/
ris_ogr_str(int nbn,int BUKv)
{ //процедура изображения на имени ограничений наложенных на стрелку
  int x2_3,y2_3,in,im,len_str,ij,sp;
	char im_str[5];
#ifdef NALAD  
  nom_func("286");
#endif          
  in=0;im=0;
  while(pako[nbn][in]!=':')in++;//сместиться на имя стрелки
  in++;
  for(in=in;in<strlen(pako[nbn]);in++)im_str[im++]=pako[nbn][in];//взять имя
  im_str[im]=0;len_str=strlen(im_str);//получить длину имени
  x2_3=fr2[nbn][0];y2_3=fr2[nbn][1];//взять координаты вершины стрелки
  switch(fr1[nbn][9]) //переключение по направлению ветвления на экране
  { //ветвление вверх
    case 1: if(fr1[nbn][7]==0) // если вход четный
            { if(OBRAT==-1) goto ob2;
              //получить смещение для имени по X и по Y
ob1:          x2_3=x2_3-(len_str*7)-1; y2_3=y2_3-12;
            }
            else
            { // вход нечетный
              if(OBRAT==-1) goto ob1;
ob2:          x2_3=x2_3-1;y2_3=y2_3-12;
            }
            break;
    // ветвление вниз
    case 0: if(fr1[nbn][7]==1) // нечет 
            { if(OBRAT==-1) goto ob4;
ob3:          x2_3=x2_3-1;y2_3=y2_3+4;
            }
            else
            { if(OBRAT==-1) goto ob3;
ob4:          x2_3=x2_3-(len_str*7);y2_3=y2_3+4;
            }
            break;
  default: y2_3=y2_3;break;
	}
	if(fr2[nbn][0]==0)return;
  switch(BUKv)//переключатель по наложенным ограничениям
  {
    case 1: setcolor(14);setlinestyle(0,0,0);//отключена от управления
            rectangle(x2_3,y2_3,x2_3+len_str*7+1,y2_3+8);//взять в рамку
            break;
    case 0x200:
            setcolor(12);
            setlinestyle(0,0,0);// на макете
            rectangle(x2_3,y2_3,x2_3+len_str*7+1,y2_3+8);//взять в рамку
            break;
    case 0x201:
            setcolor(12);setlinestyle(0,0,0);// отключена от управления и на макете
            line(x2_3,y2_3,x2_3+len_str*4,y2_3);//рамка - 2-х цветная
            line(x2_3+len_str*7+1,y2_3,x2_3+len_str*7+1,y2_3+4);
            line(x2_3+len_str*4,y2_3+8,x2_3+len_str*7+1,y2_3+8);
            line(x2_3,y2_3+4,x2_3,y2_3+8);
            setcolor(14);
            line(x2_3+len_str*4,y2_3,x2_3+len_str*7+1,y2_3);
            line(x2_3+len_str*7+1,y2_3+4,x2_3+len_str*7+1,y2_3+8);
            line(x2_3,y2_3+8,x2_3+len_str*4,y2_3+8);
            line(x2_3,y2_3,x2_3,y2_3+4);
            break;
   case 0:  setcolor(7);// нет ограничений
            setlinestyle(0,0,0);
            rectangle(x2_3,y2_3,x2_3+len_str*7+1,y2_3+8); //стереть рамку
            break;
   default: if((BUKv&0x67)==0)
            {
              if((fr1[nbn][11]&128)!=128)
              {
                sp=findspu1(nbn,fr1[nbn][7]);
                if((sp!=-1)&&(fr3[sp][1]==1))setcolor(7);
                else setcolor(8);
              }
              else setcolor(8);
            }
            else setcolor(8);
            setlinestyle(0,0,0);//отключена от управления
            rectangle(x2_3,y2_3,x2_3+len_str*7+1,y2_3+8);//взять в рамку
            break;
  }
}
//------------------------------------------
okrasklav(int irs) /* одного из всех кнопок */
{
  int xz,zzc=9999;
  if((klo==1)||(help!=0)||(nikuda==1)) return;
  //settextstyle(DEFAULT_FONT,HORIZ_DIR,0);
  for(xz=0;xz<kol_OB_UPR;xz++)//пройти по всем объектам управления
  if(irs==markery[xz][6])// если найдено управление для заданной стрелки
  {
    zzc=xz;//взять номер объекта управления для заданной стрелки
    break;
  }
  if(zzc==9999) return;//если нет управления для стрелки - выход
  imena(zzc);//нарисовать имя для объекта
  if(fr1[irs][10]==11)//если стрелка с автовозвратом
  {
    for(xz=0;xz<kol_OB_UPR;xz++)//пройти по объектам управления
    if((irs+9999)==markery[xz][6]) //если виртуальная стрелка
    {
      zzc=xz;//взять для нее номер объекта управления
      break;
    }
    if(zzc==9999) return;//если нет управления-выход
    imena(zzc);//нарисовать имя
  }
}
//----------------------------------------------------------
set_timers()
{
  unsigned char vvod[2]={0,0};
  unsigned long tiki;
  struct dostime_t tt;
        
  if(DISK!=0)return;
  if(timer_set!=15)
  {
begin:
    setfillstyle(1,2);setcolor(15);bar(480,1,640,47);rectangle(481,2,639,46);
    outtextxy(494,4,"УСТАНОВКА ВРЕМЕНИ");
    outtextxy(484,16,"ЧАСЫ МИНУТЫ СЕКУНДЫ");
    outtextxy(600,30,"00");
    setfillstyle(1,7);bar(492,30,512,40);bar(540,30,560,40);
    outtextxy(493,30,"_");
    H_1=0xFF;H_0=0xFF;M_1=0xFF;M_0=0xFF;
    return;
  }
  else
  {
    vvod[0]=getch();
    if(vvod[0]==32)
    {
      timer_set=0;
      t(0);
      X_time=0;
      return;
    }
    if(vvod[0]==13)
    { if(((H_1*10+H_0)>23)||((M_1*10+M_0)>59))
      {
        if((H_1==0xFF)&&(H_0==0xFF)&&(M_1==0xFF)&&(M_0==0xFF))
        {
          t(0);
          X_time=0;
          timer_set=0;
          return;
        }
        putch(7);
        timer_set=15;
        t(0);
        X_time=0;
        goto begin;
      }
      else
      {
        rg.h.ch=H_1<<4;
        rg.h.ch=H_1|H_0;
        rg.h.cl=M_1<<4;
        rg.h.cl=rg.h.cl|M_0;
        rg.h.dh=0;
        rg.h.ah=0x2;
        int86(0x1A,&rg,&rg);
        tt.hour=H_1*10+H_0;
        tt.minute=M_1*10+M_0;
        tt.hsecond=0;
        tt.second=0;
        _dos_settime(&tt);
        add(0,'$');
        Init_TEST_SOOB(0);
        SEC_time=biostime(0,0L);
        FIR_time=SEC_time;
        second_time=FIR_time;
        first_time=second_time;
        //-TIME_FIX;
        X_time=0;
        timer_set=0;
        t(0);
        return;
      }
    }
    switch(X_time)
    {
      case 0: X_time=493;break;
      case 493: X_time=502;break;
      case 502: X_time=541;break;
      case 541: X_time=550;break;
      case 550: X_time=493;break;
    }

    if((vvod[0]>57)||(vvod[0]<48)){ putch(7); return;}
    else
    {
      setcolor(7);
      outtextxy(X_time,31,"█");
      setcolor(15);
      outtextxy(X_time,31,vvod);
      if(X_time==493)H_1=vvod[0]-48;
      if(X_time==502)H_0=vvod[0]-48;
      if(X_time==541)M_1=vvod[0]-48;
      if(X_time==550)M_0=vvod[0]-48;
      if(X_time==502)outtextxy(541,31,"_");
      if((X_time==493)||(X_time==541))outtextxy(X_time+9,31,"_");
    }
    if(vvod[0]==0)vvod[0]=getch();
  }
}
//-------------------------------------
make_vspom_otpr()
{
	if(DISK!=0)return;  //----------------------------------------- seg022:346D- seg022:3475
	if(uprav==1)poka=0; //---------------------------------------- seg022:347D- seg022:348A
//----------------------------------- seg022:3496- seg022:34A3 seg022:34C0 seg022:34CD
	if((klaval==13)&& (zabeg==1)&& (fr3[point][9]==0)&& (vtora==0))//с√ы Єюы№ъю тюяЁюё
	{ //т√фрЄ№ яЁхфтрЁшЄхы№эє■
		form_first_kom(modi);  //---------------------------- seg022:34DF
		zapretvybora = 1;     //----------------------------- seg022:34EA
		return;  //------------------------------------------ seg022:34F1
	}
	else
	//------------------------------------- seg022:34FC- seg022:351C seg022:353C
	if((zabeg==0)&& (fr3[point][2]==0)&& (fr3[point][3]==0))//эх с√ыю ъюьрэф√ шыш эх т√яюыэхэр  
	{
		if(fr3[point][9]==9) //------------------------------ seg022:3559
		{
			home(modi);return;//хёыш с√ыр т√фрэр яхЁтр  - т√їюф
		}
		w(219,999,otopri[fr1[point][12]]);// ┬╤╧╬╠. ╬╥╧╨.? -- seg022:3593
		outtext("?");  //------------------------------------ seg022:35A0
		zabeg=1; //------------------------------------------ seg022:35AC
		zapretvybora=1;  // //------------------------------- seg022:34EA
		return;
	}
	else
	if(zabeg!=0) //--------------------------------------- seg022:35BE
	{
		if(fr3[point][9]==9)  return; //-------------------- seg022:35DE
		if((zabeg==1)&& //---------------------------------- seg022:35EE
		(fr3[point][9]==0)&&  //---------------------------- seg022:360E
		(vtora==1)) //-------------------------------------- seg022:361E
		{
			if((fr3[point][2]==1)&& //------------------------ seg022:363E
			(fr3[point][3]==0)) //---------------------------- seg022:365E
			{
				zabeg=2; //------------------------------------- seg022:366E
				pooo[point]=biostime(0,0l); //------------------ seg022:3699
				if((klaval==13)&& //---------------------------- seg022:36A8
				(zabeg==2)&& //--------------------------------- seg022:36B5
				(fr3[point][9]==0)&& //------------------------- seg022:36D2
				(vtora==1)) //---------------------------------- seg022:36DF
				{
					w(233,999,"");//------------------------------ seg022:36F4
					form_second_kom(modi); //--------------------- seg022:3706
					zabeg=0; //-------------------------- seg022:3734
					zapretvybora=0; //------------------- seg022:3740
					fr3[point][9]=0; //------------------ seg022:375C
					vtora=0; //-------------------------- seg022:3768
					home(modi);//------------------------ seg022:3779
					return;
				}
				return;   //2 ++
			}
			else
			{
				zabeg=0; //--------------------------- seg022:3734
				zapretvybora=0; //-------------------- seg022:3740
				fr3[point][9]=0; //------------------- seg022:375C
				vtora=0; //--------------------------- seg022:3768
				home(modi);//------------------------- seg022:3779
				return;
			}
			//return;
		}
		else
		{
			zabeg=0; //---------------------------- seg022:3734
			zapretvybora=0; //--------------------- seg022:3740
			fr3[point][9]=0; //-------------------- seg022:375C
			vtora=0; //---------------------------- seg022:3768
			home(modi);//-------------------------- seg022:3779
			return;
		}
		//return; //1
	}
	else  
	{
		w(229,999,""); //------------------------------- seg022:3727
		zabeg=0; //--------------------------------- seg022:3734
		zapretvybora=0; 
		fr3[point][9]=0; 
		vtora=0; 
		home(modi);
		return;
	}
}
//===================================================================
make_vspom_priem()
{
	if(DISK!=0) //----------------------------------------------------- seg022:37A3
		return;
	if(uprav==1) //---------------------------------------------------- seg022:37B3
		poka=0;

	if((klaval==13)&& //----------------------------------------------- seg022:37CC
	(zabeg==1)&&  //--------------------------------------------------- seg022:37D9
	(fr3[point][9]==0)&&  //------------------------------------------- seg022:37F6
	(vtora==0)) //----------------------------------------------------- seg022:3803
  {
    form_first_kom(modi); //----------------------------------------- seg022:3815
    zapretvybora = 1;  //-------------------------------------------- seg022:3820
    return;
  }
	else
	{	
		if((zabeg==0)&&  //---------------------------------------- seg022:3832
		(fr3[point][2]==0)&&  //----------------------------------- seg022:3852
		(fr3[point][3]==0))  //------------------------------------ seg022:3872
		{ 
			if(fr3[point][2]!=0) return; //-------------------------- seg022:3892
			{
				if(fr3[point][9]==9)  //------------------------------- seg022:38B2
				{
					home(modi); //--------------------------------------- seg022:38C4
					return;
				}
			}	
			w(218,999,otopri[fr1[point][12]+1]);//┬╤╧╬╠╬├└╥┼╦▄═█╔ ╧╨╚┼╠ -- seg022:38FC 
			outtext("?"); //-------------------------------------------- seg022:3909
			zabeg = 1; //----------------------------------------------- seg022:3915 
			zapretvybora=1; //------------------------------------------ seg022:3820
			return;
		}
		else
		if(zabeg!=0)  //----------------------------------------------- seg022:3927
		{
			if(fr3[point][9]==9) return; //------------------------------ seg022:3947
			if((zabeg==1) &&//---------------------------------------------- seg022:3957
			(fr3[point][9]==0)&&  //-------------------------------- seg022:3977
			(vtora==1))            //----------------------------------- seg022:3987
			{
				if((fr3[point][2]==0)&& //-------------------------------- seg022:39A7
				(fr3[point][3]==1))     //-------------------------------- seg022:39C4
				//╧╬╤█╦└╥▄ ╬╩╬═╫└╥┼╦▄═╙▐ ╩╬╠└═─╙?
				{
					zabeg = 3;  //------------------------------------------ seg022:39D1
					//	w(12,999,"");
					pooo[point]=biostime(0,0l); //-------------------------- seg022:3A01
				}
				else
				{
					zabeg=0;  //---------------------------------------- seg022:3A0D
					fr3[point][9] = 0; //------------------------------- seg022:3A29
					vtora=0; //----------------------------------------- seg022:3A35
					home(modi); //-------------------------------------- seg022:3A46
				}
			}
			if((klaval == 13) &&  //---------------------------------- seg022:3A51
			(zabeg == 3) && //---------------------------------------- seg022:3A61
			(fr3[point][9]==0) && //---------------------------------- seg022:3A81
			(vtora==1)) //-------------------------------------------- seg022:3A91
			{
				w(232,999,""); //--------------------------------------- seg022:3AA6
				form_second_kom(modi); //------------------------------- seg022:3AB8
				zabeg=0; //--------------------------------------------- seg022:3AC3
				zapretvybora = 0; //------------------------------------ seg022:3ACF
				fr3[point][9]=0; //------------------------------------- seg022:3AEB
				vtora=0; //--------------------------------------------- seg022:3AF7
				home(modi);//------------------------------------------- seg022:3B08
				return; //1
			}
			else
			{
				zabeg = 0; //------------------------------------------- seg022:3B18
				fr3[point][9] = 0; //----------------------------------- seg022:3B34
				vtora = 0; //------------------------------------------- seg022:3B47
				home(modi); //------------------------------------------ seg022:3B51
				//return;  //2
			}
		}
		else
		{
			w(229,999,""); //---------------------------------------- seg022:3B66
			zabeg = 0; //-------------------------------------------- seg022:3B73
			fr3[point][9] = 0; //------------------------------------ seg022:3B8F
			vtora = 0; //-------------------------------------------- seg022:3B98
			home(modi); //------------------------------------------- seg022:3BAC
			//return;
		}
	}
	return;
}
