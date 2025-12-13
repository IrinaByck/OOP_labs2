#include <gtest/gtest.h>
#include "../include/decimal.h"

TEST(test_01, addition) 
{
    Decimal a("10");
    Decimal b("20");
    ASSERT_TRUE(a < b);
}

TEST(test_02, subtraction)
{
    Decimal a("50");
    Decimal b("30");
    ASSERT_TRUE(a > b);
}

TEST(test_03, equality)
{
    Decimal a("100");
    Decimal b("100");
    ASSERT_TRUE(a == b);
}
