#include <gtest/gtest.h>

#include "../include/decimal.h"

TEST(test_01, addition_test)

{

    Decimal a("12");

    Decimal b("34");

    Decimal result = a + b;

    ASSERT_TRUE(a < b);  // 12 < 34

}

TEST(test_02, subtraction_test)

{

    Decimal a("50");

    Decimal b("30");

    Decimal result = a - b;


    ASSERT_TRUE(a > b);  // 50 > 30

}

TEST(test_03, equality_test)

{

    Decimal a("100");

    Decimal b("100");

    ASSERT_TRUE(a == b);  // 100 == 100

}

TEST(test_04, inequality_test)

{

    Decimal a("100");

    Decimal b("200");

    ASSERT_TRUE(a != b);  // 100 != 200

}

TEST(test_05, copy_test)

{

    Decimal a("123");

    Decimal b = a;

    ASSERT_TRUE(a == b);

}

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}
