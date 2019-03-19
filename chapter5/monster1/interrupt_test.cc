#include "gtest/gtest.h"

namespace unit_test{
#include "hw.h"
#include "hw.c"
#include "interrupt.h"
#include "interrupt.c"

static unsigned int usartOverrunOccurred;
static unsigned int mockIsUsartOverrunOccurred(LowPriorityInterrupt *self){
  return usartOverrunOccurred;
}

static int onUsartInterruptCallCount;
static void mockOnUsartInterrupt(LowPriorityInterrupt *self){
  ++onUsartInterruptCallCount;
}

static int timer3Overflow;
static int mockIsTimer3Overflow(LowPriorityInterrupt *self){
  return timer3Overflow;
}

static int onTimer3InterruptCallCount;
static void mockOnTimer3Interrupt(LowPriorityInterrupt *self){
  ++onTimer3InterruptCallCount;
}

TEST(InterruptTest, usartInterrupt){
  LowPriorityInterrupt interrupt = {
    mockIsUsartOverrunOccurred,
    mockOnUsartInterrupt,
    mockIsTimer3Overflow,
    mockOnTimer3Interrupt
  };

  usartOverrunOccurred = 1;
  onUsartInterruptCallCount = 0;

  performLowPriorityInterrupt(&interrupt);
  EXPECT_EQ(1, onUsartInterruptCallCount);
}
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
