#include "lib/googletest/include/gtest/gtest.h"
extern "C" {
#include "../source_lib/source.c"
}


TEST(SuiteName, TestName) {
    ASSERT_EQ(2, 2);
}
/*
class DateConverterFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {

    }

    virtual void TearDown() {

    }

};
 */