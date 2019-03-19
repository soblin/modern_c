#include "hw.h"

void setLcdPortRW(int rw){
  PORTBbits.RB2 = rw;
}

PIR1bits_t PIR1bits;
RCSTAbits_t RCSTAbits;
PIR2bits_t PIR2bits;
PIE2bits_t PIE2bits;
BYTE PORTA;
BYTE TMR3H;
BYTE TMR3L;
PORTBbits_t PORTBbits;

RingBuffer ringBufferForReceive;
RingBuffer ringBufferForLcd;

int getCharFromRingBuffer(RingBuffer *p) {
    return 0;
}

int USART_RECEIVE_CHAR(void) {
    return 0;
}

void PUT_CHAR_TO_RING_BUFFER(RingBuffer *p, int c) {
}

#ifdef UNIT_TEST
int usartReceiveBufferEnabledIdx;
bool usartReceiveBufferEnabled[8];
#endif
void enableUsartReceiveBuffer(bool enable){
  #ifdef UNIT_TEST
  #include <assert.h>
  assert(usartReceiveBufferEnabledIdx <
         sizeof(usartReceiveBufferEnabled) / sizeof(usartReceiveBufferEnabled[0]));
  usartReceiveBufferEnabled[usartReceiveBufferEnabledIdx++] = enable;
  #else
  RCSTAbits.CREN = (enable)? 1 : 0;
  #endif
}

#ifdef UNIT_TEST
bool clearUsartReceiveBufferCallCount;
#endif
void clearUsartReceiveBuffer(void){
  #ifdef UNIT_TEST
  ++clearUsartReceiveBufferCallCount;
  #else
  int c = USART_RECEIVE_CHAR();
  #endif
}

#ifdef UNIT_TEST
int portAIdx;
int portAState[8];
#endif
void setPortA(int data){
  #ifdef UNIT_TEST
  #include <assert.h>
  assert(portAIdx <
         sizeof(portAState) / sizeof(portAState[0]));
  portAState[portAIdx++] = data;
  #else
  PORTA = data;
  #endif
}

#ifdef UNIT_TEST
int pulseLcdCECallCount;
#endif
void pulseLcdCE(void){
  #ifdef UNIT_TEST
  ++pulseLcdCECallCount;
  #else
  PORTBbits.RB1 = 1;
  PORTBbits.RB1 = 1;
  PORTBbits.RB1 = 1;
  PORTBbits.RB1 = 0;
  PORTBbits.RB1 = 0;
  #endif
}
