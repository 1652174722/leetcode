
#include <iostream>
#include "gtest/gtest.h"

using namespace std;

int main(int argc, char* argv[])
{
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    cout << "file name:" << __FILE__ << " func name:" << __func__ << " line no:" << __LINE__ << endl;
    cout << "file name:" << __FILE__ << " func name:" << __func__ << " line no:" << __LINE__ << endl;
    int ret = RUN_ALL_TESTS();
    cout << "file name:" << __FILE__ << " func name:" << __func__ << " line no:" << __LINE__ << endl;
    return ret;
}