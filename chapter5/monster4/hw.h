#ifndef _HW_H_
#define _HW_H_

#define LCD_PORT_READ (0)
#define LCD_PORT_WRITE (1)

void setLcdPortRW(int rw);

typedef unsigned char BYTE;

typedef union {
    struct {
        unsigned RCIF                   :1;
    };
} PIR1bits_t;

extern PIR1bits_t PIR1bits;

typedef union {
    struct {
        unsigned OERR                   :1;
        unsigned CREN                   :1;
    };
} RCSTAbits_t;

extern RCSTAbits_t RCSTAbits;

typedef struct {
    unsigned TMR3IF: 1;
} PIR2bits_t;

extern PIR2bits_t PIR2bits;

typedef struct {
    unsigned TMR3IE: 1;
} PIE2bits_t;

extern PIE2bits_t PIE2bits;

extern BYTE PORTA;
extern BYTE TMR3H;
extern BYTE TMR3L;

typedef struct {
    unsigned RB0: 1;
    unsigned RB1: 1;
    unsigned RB2: 1;
    unsigned RB3: 1;
} PORTBbits_t;

extern PORTBbits_t PORTBbits;

typedef struct {
} RingBuffer;

extern RingBuffer ringBufferForReceive;
extern RingBuffer ringBufferForLcd;

int getCharFromRingBuffer(RingBuffer *p);
int USART_RECEIVE_CHAR(void);
void PUT_CHAR_TO_RING_BUFFER(RingBuffer *p, int c);

#include <stdbool.h>

#ifdef UNIT_TEST
extern bool usartReceiveBufferEnabled[8];
#endif
void enableUsartReceiveBuffer(bool enable);

#ifdef UNIT_TEST
extern int clearUsartReceiveCallCount;
#endif
void clearUsartReceiveBuffer(void);

#ifdef UNIT_TEST
extern int portAIdx;
extern int portAState[];
#endif

void setPortA(int data);

#ifdef UNIT_TEST
extern int pulseLcdCECallCount;
#endif

void pulseLcdCE(void);
#endif
