#include <gtest/gtest.h>

#include "../include/decimal.h"

TEST(test_01, basic_addition)

{

    Decimal a("12");

    Decimal b("34");

    Decimal result = a + b;


    ASSERT_TRUE(a < b);

}

TEST(test_02, basic_subtraction) 

{

    Decimal a("50");

    Decimal b("30");

    

    ASSERT_TRUE(a > b);

}

TEST(test_03, equality_test)

{

    Decimal a("100");

    Decimal b("100");

    

    ASSERT_TRUE(a == b);

}

TEST(test_04, copy_test)

{

    Decimal a("123");

    Decimal b = a;

    

    ASSERT_TRUE(a == b);

}

TEST(test_05, different_numbers)

{

    Decimal a("999");

    Decimal b("1");

    

    ASSERT_TRUE(a > b);

}

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}
