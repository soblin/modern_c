#include "hw.h"
#include "interrupt.h"

void lowPriorityISRCode(void){
  if(PIR1bits.RCIF){
    if(RCSTAbits.OERR){
      int c;
      // ポートをリセット
      RCSTAbits.CREN = 0;
      c = USART_RECEIVE_CHAR();
      RCSTAbits.CREN = 1;
    }
    else{
      int c = USART_RECEIVE_CHAR();
      PUT_CHAR_TO_RING_BUFFER(&ringBufferForReceive, (char)c);
    }
  }
  else if(PIR2bits.TMR3IF != 0){
    int c;
    if((c = getCharFromRingBuffer(&ringBufferForLcd)) != -1){
      if(c == (BYTE)0xFE){
        c = getCharFromRingBuffer(&ringBufferForLcd);

        PORTBbits.RB0 = 0;
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

        PIR2bits.TMR3IF = 0;
        TMR3H = (65467u >> 8);
        TMR3L = (65467u & 0xff);
      }
      else{
        PORTBbits.RB0 = 1;
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

        PIR2bits.TMR3IF = 0;
        TMR3H = (65467u >> 8);
        TMR3L = (65467u & 0xff);        
      }
    }
    else{
      PIE2bits.TMR3IE = 0;
    }
  }
}

int main(){
  return 0;
}
