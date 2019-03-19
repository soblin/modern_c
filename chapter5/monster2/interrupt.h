#ifndef INTERRUPT_H_
#define INTERRUPT_H_

unsigned int isUsartInterruptOccurred(void);
void onUsartInterrupt(void);
int isTimer3Overflow(void);
void onTimer3Interrupt(void);

#ifdef UNIT_TEST
#define MOCKABLE(method) mockable##method
#else
#define MOCKABLE(method) method
#endif

#ifdef UNIT_TEST
extern unsigned int MOCKABLE(isUsartInterruptOccurred)(void);
extern unsigned int (*pIsUsartInterruptOccurred)(void);

void MOCKABLE(onUsartInterrupt)(void);
extern void (*pOnUsartInterrupt)(void);

int MOCKABLE(isTimer3Overflow)(void);
extern int (*pIsTimer3Overflow)(void);

void MOCKABLE(onTimer3Interrupt)(void);
extern void (*pOnTimer3Interrupt)(void);

#endif
#endif /* INTERRUPT_H_ */
