#include <gtest/gtest.h>

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    // testing::FLAGS_gtest_filter = "BSearch1ParamTest.MR1";
    return RUN_ALL_TESTS();
}