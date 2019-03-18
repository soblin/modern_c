#include "gtest/gtest.h"

extern "C"{
  #include "add.h"
}

namespace unit_test{

#include "add.c"

TEST(AddTest, onePlusTwoEqulsThree){
  EXPECT_EQ(3, add(1, 2));
}
} /* namespace unit_test */

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
