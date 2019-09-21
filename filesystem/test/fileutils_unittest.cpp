#include "gtest/gtest.h"
#include <string>
#include <algorithm>
#include <fstream>
#include "fileutils.hpp"
using namespace std;
class FileUtilsUnitTEST: public ::testing::Test{
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

TEST_F(FileUtilsUnitTEST, case0) {
    EXPECT_EQ("./a/b/c.txt", FileTools::join("./a/b", "c.txt"));
}

TEST_F(FileUtilsUnitTEST, case1) {
    EXPECT_EQ("/home/a/c.txt", FileTools::join("/home/a", "c.txt"));
}

TEST_F(FileUtilsUnitTEST, save_load_easy) {
    std::vector<int> a{1, 2, 3};
    {
        std::ofstream outf("./test.data", ios::out | ios::binary | ios::trunc);
        FileTools::save(outf, a);
        outf.close();
    }

    {
        std::ifstream in("./test.data", ios::in | ios::binary);
        vector<int> b;
        FileTools::load(in, b);
        ASSERT_EQ(a, b);
    }
}
