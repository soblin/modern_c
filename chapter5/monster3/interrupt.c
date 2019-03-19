#include "hw.h"
#include "interrupt.h"

unsigned int isUsarOverrunOccurred(){
  return PIR1bits.RCIF;
}

void resetUsartPort(void){
  enableUsartReceiveBuffer(false);
  clearUsartReceiveBuffer();
  enableUsartReceiveBuffer(true);
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

void disableTimer3Interrupt(void){
  PIE2bits.TMR3IE = 0;
}

void processLcdData(int c){
  if(c == (BYTE)0xFE){
    performLcdControl(c);
  }
  else{
    performLcdData(c);
  }
}

void lowPriorityISRCode(void){
  if(isUsartInterruptOccurred()) onUsartInterrupt();
  else if(isTimer3Overflow()) onTimer3Interrupt();
}

// テストしない時はこれがそのままi isUsartInterruptOccurred() になる
// だが若干ソースコードを汚している感じもある
unsigned int MOCKABLE(isUsartInterruptOccurred)(void){
  return PIR1bits.RCIF;
}

#ifdef UNIT_TEST
unsigned int (*pIsUsartInterruptOccurred)(void ) = MOCKABLE(isUsartInterruptOccurred);
unsigned int isUsartInterruptOccurred(void){
  return pIsUsartInterruptOccurred();
}
#endif

int MOCKABLE(isTimer3Overflow)(void){
  return PIR2bits.TMR3IF != 0;
}

#ifdef UNIT_TEST
int (*pIsTimer3Overflow)(void) = MOCKABLE(isTimer3Overflow);
int isTimer3Overflow(void){
  return pIsTimer3Overflow();
}
#endif

void MOCKABLE(onUsartInterrupt)(void){
  if(isUsartInterruptOccurred()) resetUsartPort();
  else{
    int c = USART_RECEIVE_CHAR();
    PUT_CHAR_TO_RING_BUFFER(&ringBufferForReceive, c);
  }
}

#ifdef UNIT_TEST
void (*pOnUsartInterrupt)(void) = MOCKABLE(onUsartInterrupt);
void onUsartInterrupt(void){
  return pOnUsartInterrupt();
}

#endif
void MOCKABLE(onTimer3Interrupt)(void){
  int c;
  if((c = getCharFromRingBuffer(&ringBufferForLcd)) != -1)
    processLcdData(c);
  else disableTimer3Interrupt();
}

#ifdef UNIT_TEST
void (*pOnTimer3Interrupt)(void) = MOCKABLE(onTimer3Interrupt);
void onTimer3Interrupt(void){
  return pOnTimer3Interrupt();
}
#endif

int main(){
  return 0;
}
