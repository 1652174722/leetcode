
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

int main(int argc, char* argv[])
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}