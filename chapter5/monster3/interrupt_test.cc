#include "gtest/gtest.h"

namespace unit_test{
#include "hw.h"
#include "hw.c"
#include "interrupt.h"
#include "interrupt.c"

TEST(ResetUsartPort, normalCase){
  usartReceiveBufferEnabledIdx = 0;
  clearUsartReceiveBufferCallCount = 0;

  resetUsartPort();

  EXPECT_EQ(1, clearUsartReceiveBufferCallCount);
  EXPECT_EQ(2, usartReceiveBufferEnabledIdx);
  EXPECT_EQ(false, usartReceiveBufferEnabled[0]);
  EXPECT_EQ(true, usartReceiveBufferEnabled[1]);
}
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
