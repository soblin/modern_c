#ifndef INTERRUPT_H_
#define INTERRUPT_H_

typedef struct LowPriorityInterrupt{
  unsigned int (*const isUsartInterruptOccurred)(struct LowPriorityInterrupt *self);
  void (*const onUsartInterrupt)(struct LowPriorityInterrupt *self);
  int (*const isTimer3Overflow)(struct LowPriorityInterrupt *self);
  void (*const onTimer3Interrupt)(struct LowPriorityInterrupt *self);
} LowPriorityInterrupt;

void performLowPriorityInterrupt(LowPriorityInterrupt *object);

#endif /* INTERRUPT_H_ */
