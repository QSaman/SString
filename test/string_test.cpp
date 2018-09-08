#include <gtest/gtest.h>
#include "sstring.h"
#include <string>
#include <iostream>


TEST(SString, DefaultConstructor)
{
    saman::SString str;
    EXPECT_EQ(str[0], '\0');
    char ch;
    ch = str[0];
}

TEST(SString, ConversionConstructor)
{
    saman::SString str{"s"};
    EXPECT_EQ(str[0], 's');
    EXPECT_EQ(str[1], '\0');
}

TEST(SString, MoveConstructor)
{
    saman::SString str{"s"};
    saman::SString s2(std::move(str));
    EXPECT_EQ(s2[0], 's');
    EXPECT_EQ(s2[1], '\0');
    EXPECT_EQ(&str[0], nullptr);
    EXPECT_EQ(str.length(), 0);
}

TEST(SString, CopyAssignment)
{
    saman::SString str{"s"};
    saman::SString str2;
    str2 = str;
    str[0] = 'm';
    EXPECT_EQ(str[0], 'm');
    EXPECT_EQ(str[1], '\0');

    EXPECT_EQ(str2[0], 's');
    EXPECT_EQ(str2[1], '\0');
}

TEST(SString, MoveAssingment)
{
    saman::SString s1{"s"};
    saman::SString s2{"m"};
    s2 = std::move(s1);
    EXPECT_EQ(s2[0], 's');
    EXPECT_EQ(s2[1], '\0');

    EXPECT_EQ(s1[0], 'm');
    EXPECT_EQ(s1[1], '\0');
}

TEST(SString, CompareOperator)
{
    saman::SString s1{"string1"};
    saman::SString s2{"string1"};
    EXPECT_EQ(s1, s2);
}

TEST(SString, OperatorPlus)
{
    saman::SString s1{"abc"};
    saman::SString s2{"1234567"};
    auto res = s1 + s2;
    saman::SString tmp{"abc1234567"};
    EXPECT_EQ(10, res.length());
    EXPECT_EQ(res[10], '\0');
    EXPECT_TRUE("abc1234567" == res);
}
TEST(SString, OperatorPlusEqual)
{
    saman::SString s1{"abc"};
    saman::SString s2{"1234567"};
    s1 += s2;
    EXPECT_TRUE(s1 == "abc1234567");
}

TEST(SString, Substr)
{
    saman::SString str{"saman"};
    EXPECT_TRUE("ama" == str(1, 3));
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
