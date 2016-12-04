//Author: Leo
//Date: 2016.12.04
//IDE Ver.: 1.0.3
//website: github.com/leolite
//MCU: ATMEL ATTINY13
//Programmer: usbtinyisp(@Ladyada https://learn.adafruit.com/usbtinyisp/drivers)
//hardware core: core13(@smeezekitty http://sourceforge.net/projects/ard-core13/)

//       ATMEL ATTINY13 / ARDUINO
//
//                      +-\/-+
// [RST]ADC0 (D 5) PB5 1|    |8 Vcc
//      ADC3 (D 3) PB3 2|    |7 PB2 (D 2) ADC1[SCK]
//      ADC2 (D 4) PB4 3|    |6 PB1 (D 1) PWM1[MISO] Left
//                 GND 4|    |5 PB0 (D 0) PWM0[MOSI] Right
//                      +----+

/*
 ADC0 = pin-1
 ADC1 = Pin-7
 ADC2 = Pin=3
 ADC3 = Pin-2
 */


#include <avr/interrupt.h>
//#include <EEPROM.h>
/* EEPROM Control Register */
#define EECR  _SFR_IO8(0x1C)

/* EEPROM Data Register */
#define EEDR  _SFR_IO8(0x1D)

/* EEPROM Address Register */
#define EEAR  _SFR_IO16(0x1E)
#define EEARL _SFR_IO8(0x1E)
#define EEARH _SFR_IO8(0x1F)

/* EEPROM Control Register */
#define    EEPM1        5
#define    EEPM0        4
#define    EERIE        3
#define    EEMWE        2
#define    EEWE         1
#define    EERE         0


char addressConfigValue; //Config value
char addressConfigValueLimit = 6;

int pinOut[] = {
  0,1,2,3,4};
int countOut = 5;
int timerOut = 200;
int countLed = 0;
boolean ledON = HIGH;

void setup()
{
  //Serial.begin(9600);
  iniPin();
  iniConfig();
  hmiConfig(); //Blink mode times
  //Serial.println("Done! ");

}

void loop()
{
  //Mode 1: LED ONx5
  if(addressConfigValue <= 1 || addressConfigValue > addressConfigValueLimit){
    for (int i =0; i<countOut; i++){ 
      digitalWrite(pinOut[i], ledON);  
    }
    delay(100);
  }

  //Mode 2: Water LED 4xOFF + 1xON
  if(addressConfigValue == 2){
    for (int i =0; i<countOut; i++){ 
      digitalWrite(pinOut[i], !ledON);  
    }
    digitalWrite(pinOut[countLed], ledON);
    countLed ++;
    if( countLed >= 5) countLed = 0;
    delay(timerOut);
  }

  //Mode 3: Water LED 4xON + 1xOFF
  if(addressConfigValue == 3) {
    for (int i =0; i<countOut; i++){ 
      digitalWrite(pinOut[i], ledON);  
    }
    digitalWrite(pinOut[countLed], !ledON);
    countLed ++;
    if( countLed >= 5) countLed = 0;
    delay(timerOut); 
  }


  //Mode 4: BLINK
  if(addressConfigValue == 4) {
    PORTB |= _BV(1); //HIGH
    delay(1000);
    PORTB &= ~_BV(1); //LOW
    delay(1000);
  }

  //Mode 5: LED ONx5 BLINK
  if(addressConfigValue == 5){
    PORTB = 0B11111;
    delay(1000); 
    PORTB = 0B00000;
    delay(1000); 
  }

  //Mode 6: FADE
  if(addressConfigValue == 6){
    // fade in from min to max in increments of 5 points:
    for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
      // sets the value (range from 0 to 255):
      analogWrite(pinOut[0], fadeValue);         
      // wait for 30 milliseconds to see the dimming effect    
      delay(30);                            
    } 

    // fade out from max to min in increments of 5 points:
    for(int fadeValue = 255 ; fadeValue >= 0; fadeValue -=5) { 
      // sets the value (range from 0 to 255):
      analogWrite(pinOut[0], fadeValue);         
      // wait for 30 milliseconds to see the dimming effect    
      delay(30);                            
    }
    delay(2000);  
  } 
}

//for Tiny updated Done!
void iniPin(){
  DDRB = 0B111111; //ALL is output
  //TCCR0A = 0x03; //关闭PWM 
}

//-----------------------------------------Input function-----------------------------------------//
void iniConfig(){
  addressConfigValue = eeprom_read(0);
  addressConfigValue++;  
  if(addressConfigValue > addressConfigValueLimit) addressConfigValue = 0;
  eeprom_write(0, addressConfigValue);
}

//for Tiny updated Done! 2014.06.29
//Delay time maybe need Update
void hmiConfig(){
  //digitalWrite(3, LOW);
  PORTB &= ~_BV(3); //LOW
  delay(500);
  for(char i =0; i< addressConfigValue ; i++){
    PORTB |= _BV(3); //HIGH
    delay(200);
    PORTB &= ~_BV(3); //LOW
    delay(200);
  }
}



//EEPROM operation
//向EEPROM地址写一个字节的数据 
void eeprom_write(unsigned char addr,unsigned char wdata) 
{ 
  cli();
  while(EECR&(1<<EEWE));//等待上一次写操作完成 
  EECR=(0<<EEPM1)|(0>>EEPM0);
  EEAR=addr;//写地址寄存器 
  EEDR=wdata;//写数据寄存器 
  EECR|=(1<<EEMWE);// 
  EECR|=(1<<EEWE);//（两个分开写才能写进）启动写操作 
  sei();

} 

//向EEPROM读出一个字节的数据 
unsigned char eeprom_read(unsigned char addr) 
{ 
  while(EECR&(1<<EEWE));//等待上一次写完成 
  EEAR=addr; 
  EECR|=(1<<EERE);//启动 
  return EEDR;//返回读出的数据 
}








