#include <MsTimer2.h>  
#include <Wire.h> 
#include <DS3231.h> 
#include <GyverButton.h>
#include "AnalogKey.h"
#define NUM_KEYS 3
AnalogKey<A0, 3> keys;
GButton btn1, btn2, btn3;
int adc_key_val[NUM_KEYS] = { 170, 350, 520,};

DS3231 myRTC;

bool h12Flag;
bool pmFlag;

bool menu = 0;

int counter;

bool flag_tick = 0;
bool flag_vubor = 1;

unsigned long time_ = 0;
int an, segm,times,i,hour,minute;
byte a [ 4 ] ;
 
void setup ( ) { 
  Wire.begin ( ) ;
  MsTimer2:: set ( 5 , to_Timer ) ;
  MsTimer2:: start( ) ;
  myRTC.setHour(0);
  myRTC.setMinute(5);

  keys.attach(0, 170);
  keys.attach(1, 350);
  keys.attach(2, 520);
  
  pinMode ( 9 , OUTPUT ) ;  // D9 === A0 
  pinMode ( 10 , OUTPUT ) ; // D10 === A1 
  pinMode ( 11 , OUTPUT ) ; // D11 === A2 
  pinMode ( 12 , OUTPUT ) ; // D12 === A3 
  pinMode (2 , OUTPUT ) ;  // D2 === a 
  pinMode ( 3 , OUTPUT ) ;  // D3 === b 
  pinMode ( 4 , OUTPUT ) ;  // D4 === c 
  pinMode ( 5 , OUTPUT ) ;  // D5 === d 
  pinMode ( 6 , OUTPUT ) ;  // D6 === e 
  pinMode ( 7 , OUTPUT ) ;  // D7 === f 
  pinMode ( A0 , INPUT ) ;  // D8 === g
  time_ = millis();
}
 
void loop ( ) {  
  
  btn1.tick(keys.status(0));
  btn2.tick(keys.status(1));
  btn3.tick(keys.status(2));
  
 if (btn1.isHolded()) 
 {
   menu = !menu;
 }

  if(menu)
  {
    if(millis()-time_>1000)
    {    
      flag_tick = !flag_tick; 
      time_ = millis(); 
    }

    if(btn1.isClick())
    {
      flag_vubor =! flag_vubor;
    }

    if(flag_vubor)
    {
        if(flag_tick)
      {
        a [ 3 ] = 10;
        a [ 2 ] = 10;
      }
      else
      {
        a [ 3 ] = hour / 10;
        a [ 2 ] = hour % 10;
      }
      a [ 1 ] = minute / 10;
      a [ 0 ] = minute % 10;

      if(btn2.isClick())
      {
        if(hour<24)
        {
          hour++;
        }
        else
        {
          hour = 0;
        }
        myRTC.setHour(hour);
      }
       if(btn3.isClick())
      {
        if(hour > 0)
        {
          hour--;
        }
        else
        {
          hour = 23;
        }
        myRTC.setHour(hour);
      }
    }
    else
    {
      if(flag_tick)
      {
        a [ 1 ] = 10;
        a [ 0 ] = 10;
      }
      else
      {
        a [ 1 ] = minute / 10;
        a [ 0 ] = minute % 10;
      }
      a [ 3 ] = hour / 10;
      a [ 2 ] = hour % 10;

      if(btn2.isClick())
      {
        if(minute<60)
        {
          minute++;
        }
        else
        {
          minute = 0;
        }
        myRTC.setMinute(minute);
      }
       if(btn3.isClick())
      {
        if(minute > 0)
        {
          minute--;
        }
        else
        {
          minute = 59;
        }
        myRTC.setMinute(minute);
      }
    }
  }
  
  if(millis()-time_>500 && !menu)
  {    
    hour =  myRTC.getHour(h12Flag, pmFlag);
    minute = myRTC.getMinute();
    
    a [ 3 ] = hour / 10;
    a [ 2 ] = hour % 10;
    a [ 1 ] = minute / 10;
    a [ 0 ] = minute % 10;
 
    time_ = millis();
  }
  

} // loop
 
void to_Timer ( ) {  
  switch ( i ) { 
    case  0 : segm = a [ 0 ] ; an = 0 ; anod ( ) ; segment ( ) ; delay ( 1 ) ; break ;
    case  1 : segm = a [ 1 ] ; an = 1 ; anod ( ) ; segment ( ) ; delay ( 1 ) ; break ;
    case  2 : segm = a [ 2 ] ; an = 2 ; anod ( ) ; segment ( ) ; delay ( 1 ) ; break ;
    case  3 : segm = a [ 3 ] ; an = 3 ; anod ( ) ; segment ( ) ; delay ( 1 ) ; break ; } 
    i++; 
    if ( i > 3 ) { i = 0 ; } }
 
 
void segment ( ) { 
  switch ( segm ) {                                                                  
             // ABCDEFG   
    case  0 : ch ( 2 , 0 ) ; ch ( 3 , 0 ) ; ch ( 4 , 0 ) ; ch ( 5 , 0 ) ; ch ( 6 , 0 ) ; ch ( 7 , 0 ) ; ch ( 8 , 1 ) ; break ; // 0 
    case  1 : ch ( 2 , 1 ) ; ch ( 3 , 0 ) ; ch ( 4 , 0 ) ; ch ( 5 , 1 ) ; ch ( 6 , 1 ) ; ch ( 7 , 1 ) ; ch ( 8 , 1 ) ; break ; // 1 
    case  2 : ch ( 2 , 0 ) ; ch ( 3 , 0 ) ; ch ( 4 , 1 ) ; ch ( 5 , 0 ) ; ch ( 6 , 0 ) ; ch ( 7 , 1 ) ; ch ( 8 , 0 ) ; break ; // 2 
    case  3 : ch ( 2 , 0 ) ; ch ( 3 , 0 ) ; ch ( 4 , 0 ) ; ch ( 5 , 0 ) ; ch ( 6 , 1 ) ; ch ( 7 , 1 ) ; ch ( 8 , 0 ) ; break ; // 3    
    case  4 : ch ( 2 , 1 ) ; ch ( 3 , 0 ) ; ch ( 4 , 0 ) ; ch ( 5 , 1 ) ; ch ( 6 , 1 ) ; ch ( 7 , 0 ) ; ch ( 8 , 0 ) ; break ; // 4 
    case  5 : ch ( 2 , 0 ) ; ch ( 3 , 1 ) ; ch ( 4 , 0 ) ; ch ( 5 , 0 ) ; ch ( 6 , 1 ) ; ch ( 7 , 0 ) ; ch ( 8 , 0 ) ; break ; // 5 
    case  6 : ch ( 2 , 0 ) ; ch ( 3 , 1 ) ; ch ( 4 , 0 ) ; ch ( 5 , 0 ) ; ch ( 6 , 0 ) ; ch ( 7 , 0 ) ; ch ( 8 , 0 ) ; break ; // 6 
    case  7 : ch ( 2 , 0 ) ; ch ( 3 , 0 ) ; ch ( 4 , 0 ) ; ch ( 5 , 1 ) ; ch ( 6 , 1 ) ; ch ( 7 , 1 ) ; ch ( 8 , 1 ) ; break ; // 7 
    case  8 : ch ( 2 , 0 ) ; ch ( 3 , 0 ) ; ch ( 4 , 0 ) ; ch ( 5 , 0 ) ; ch ( 6 , 0 ) ; ch ( 7 , 0 ) ; ch ( 8 , 0 ) ; break ; // 8 
    case  9 : ch ( 2 , 0 ) ; ch ( 3 , 0 ) ; ch ( 4 , 0 ) ; ch ( 5, 0 )  ; ch ( 6 , 1 ) ; ch ( 7 , 0 ) ; ch ( 8 , 0 ) ; break ; // 9 
    case  10 : ch ( 2 , 1 ) ; ch ( 3 , 1 ) ; ch ( 4 , 1 ) ; ch ( 5, 1 )  ; ch ( 6 , 1 ) ; ch ( 7 , 1 ) ; ch ( 8 , 1 ) ; break ; // 9   
  } } 
void anod ( ) { 
  switch ( an ) {                                                              
    case  0 : ch ( 9 , 0 ) ; ch ( 10 , 1 ) ; ch ( 11 , 1 ) ; ch ( 12 , 1 ) ; break ;  
    case  1 : ch ( 9 , 1 ) ; ch ( 10 , 0 ) ; ch ( 11 , 1 ) ; ch ( 12 , 1 ) ; break ; 
    case  2 : ch ( 9 , 1 ) ; ch ( 10 , 1 ) ; ch ( 11 , 0 ) ; ch ( 12 , 1 ) ; break ;
    case  3 : ch ( 9 , 1 ) ; ch ( 10 , 1 ) ; ch ( 11 , 1 ) ; ch ( 12 , 0 ) ; break ;
  } }
 
inline void ch ( int pin, int logic ) { digitalWrite ( pin, logic ) ; }
