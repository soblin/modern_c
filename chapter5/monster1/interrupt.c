#include "hw.h"
#include "interrupt.h"

unsigned int isUsartInterruptOccurred(LowPriorityInterrupt *self){
  return PIR1bits.RCIF;
}

unsigned int isUsartOverrunOccurred(LowPriorityInterrupt *self){
  return RCSTAbits.OERR;
}

int isTimer3Overflow(LowPriorityInterrupt *self){
  return PIR2bits.TMR3IF != 0;
}

void disableTime3Interrupt(){
  PIE2bits.TMR3IE = 0;
}

void resetUserPort(void){
  // ポートをリセット
  RCSTAbits.CREN = 0;
  int c = USART_RECEIVE_CHAR();
  RCSTAbits.CREN = 1;
}

void onUsartInterrupt(LowPriorityInterrupt *self){
  if(isUsartOverrunOccurred(self)){
    resetUserPort();
  }
  else{
    int c = USART_RECEIVE_CHAR();
    PUT_CHAR_TO_RING_BUFFER(&ringBufferForReceive, (char)c);
  }  
}

void write1byteToLcd(int c){
  PORTBbits.RB2 = 0;
  PORTA = c >> 4;
  PORTBbits.RB1 = 1;
  PORTBbits.RB1 = 1;
  PORTBbits.RB1 = 1;
  PORTBbits.RB1 = 0;
  PORTBbits.RB1 = 0;

  PORTA = c & 0xf;
  PORTBbits.RB1 = 1;
  PORTBbits.RB1 = 1;
  PORTBbits.RB1 = 1;
  PORTBbits.RB1 = 0;  
}

void performLcdControl(int c){
  c = getCharFromRingBuffer(&ringBufferForLcd);

  PORTBbits.RB0 = 0; // control mode
  write1byteToLcd(c);
  
  PIR2bits.TMR3IF = 0;
  TMR3H = (65467u >> 8);
  TMR3L = (65467u & 0xff);  
}

void performLcdData(int c){
  PORTBbits.RB0 = 1; // data mode

  write1byteToLcd(c);
    
  PIR2bits.TMR3IF = 0;
  TMR3H = (65467u >> 8);
  TMR3L = (65467u & 0xff);  
}

void processLcdData(int c){
  if(c == (BYTE)0xFE){
    performLcdControl(c);
  }
  else{
    performLcdData(c);
  }
}

void onTimer3Interrupt(LowPriorityInterrupt *self){
  int c;
  if((c = getCharFromRingBuffer(&ringBufferForLcd)) != -1){
    processLcdData(c);
  }
  else{
    disableTime3Interrupt();
  }
}

static LowPriorityInterrupt lowPriorityInterrupt = {
  isUsartInterruptOccurred,
  onUsartInterrupt,
  isTimer3Overflow,
  onTimer3Interrupt
};

void lowPriorityISRCode(void){
  // デフォルトではこのlowPriorityInterruptを使う
  // だがテストする時は差し替えることも可能
  // テストする側ではperformLowPriorityInterruptの引数にmockを入れる
  performLowPriorityInterrupt(&lowPriorityInterrupt);
}

void performLowPriorityInterrupt(LowPriorityInterrupt *object){
  if(object->isUsartInterruptOccurred(object)){
    object->onUsartInterrupt(object);
  }
  else if(object->isTimer3Overflow(object)){
    object->onTimer3Interrupt(object);
  }
}
