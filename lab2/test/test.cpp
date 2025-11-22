#include <gtest/gtest.h>
#include "../include/decimal.h"

TEST(test_01, basic_test_set)
{
    Decimal d1("123");
    Decimal d2("45");
    Decimal result = d1 + d2;
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    
    ASSERT_TRUE(output == "168");
}

TEST(test_02, basic_test_set)
{
    Decimal d1("456");
    Decimal d2("123");
    Decimal result = d1 - d2;
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    
    ASSERT_TRUE(output == "333");
}

TEST(test_03, basic_test_set)
{
    Decimal d1("123");
    Decimal d2("456");
    
    ASSERT_TRUE(d1 < d2);
}

TEST(test_04, basic_test_set)
{
    Decimal d1("456");
    Decimal d2("123");
    
    ASSERT_TRUE(d1 > d2);
}

TEST(test_05, basic_test_set)
{
    Decimal d1("123");
    Decimal d2("123");
    
    ASSERT_TRUE(d1 == d2);
}

TEST(test_06, basic_test_set)
{
    Decimal d1("999");
    Decimal d2("1");
    Decimal result = d1 + d2;
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    
    ASSERT_TRUE(output == "1000");
}

TEST(test_07, basic_test_set)
{
    Decimal d1("100");
    Decimal d2("50");
    Decimal result = d1 - d2;
    
    testing::internal::CaptureStdout();
    result.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    
    ASSERT_TRUE(output == "50");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
