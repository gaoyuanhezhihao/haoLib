#include "gtest/gtest.h"
#include "Config.hpp"
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;
class ConfigUnitTEST: public ::testing::Test{
    protected:
        virtual void SetUp(){

        }

        virtual void TearDown(){

        }
};
int main(int argc, char **argv) {
      ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}

TEST_F(ConfigUnitTEST, init_file) {
    string fname("/tmp/test_config.txt");
    std::ofstream out(fname);
    out << "a = 1.0\n b = 1 \n c = hello\n" << std::endl;
    out.close();
    configs.init(fname.c_str());
    double a = configs["a"];
    int b = configs["b"];
    string c = configs["c"];
    EXPECT_EQ(a, 1.0);
    EXPECT_EQ(b, 1);
    EXPECT_EQ(c, "hello");
}
