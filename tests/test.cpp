#include <gtest/gtest.h>
#include "../include/polynomial.h"

TEST(PolynomialCreationTests, PolynomialCreationTestBase)
{
    double c[3]{1,2,2};
    Polynomial p(c, 2);
    ASSERT_TRUE(p.get_degree() == 2);
    ASSERT_TRUE(p.get_coef(0) == 1);
    ASSERT_TRUE(p.get_coef(1) == 2);
    ASSERT_TRUE(p.get_coef(2) == 2);
}

TEST(PolynomialCreationTests, PolynomialCreationTestDefault)
{
    Polynomial p;
    ASSERT_TRUE(p.get_degree() == -1);
}

TEST(PolynomialAddTests, PolynomialAddTestBase)
{
    double c[3]{1,2,2};
    Polynomial p1(c, 2), p2(c, 2);
    p1.add(p2);
    ASSERT_TRUE(p1.get_degree() == 2);
    ASSERT_TRUE(p1.get_coef(0) == 2);
    ASSERT_TRUE(p1.get_coef(1) == 4);
    ASSERT_TRUE(p1.get_coef(2) == 4);
}

TEST(PolynomialAddTests, PolynomialAddTestDifferentSize)
{
    double c[3]{1,2,2};
    Polynomial p1(c, 1), p2(c, 2);
    p1.add(p2);
    ASSERT_TRUE(p1.get_degree() == 2);
    ASSERT_TRUE(p1.get_coef(0) == 2);
    ASSERT_TRUE(p1.get_coef(1) == 4);
    ASSERT_TRUE(p1.get_coef(2) == 2);
}

TEST(PolynomialCopyTests, PolynomialCopyTestBase)
{
    double c[3]{1,2,2};
    Polynomial p1(c, 2);
    Polynomial p2(p1);
    ASSERT_TRUE(p2.get_degree() == 2);
    ASSERT_TRUE(p2.get_coef(0) == 1);
    ASSERT_TRUE(p2.get_coef(1) == 2);
    ASSERT_TRUE(p2.get_coef(2) == 2);
}

TEST(PolynomialCopyTests, PolynomialCopyTestOperator)
{
    double c[3]{1,2,2};
    Polynomial p1(c, 2);
    Polynomial p2 = p1;
    ASSERT_TRUE(p2.get_degree() == 2);
    ASSERT_TRUE(p2.get_coef(0) == 1);
    ASSERT_TRUE(p2.get_coef(1) == 2);
    ASSERT_TRUE(p2.get_coef(2) == 2);
}

TEST(PolynomialCopyTests, PolynomialCopyTestSelf)
{
    double c[3]{1,2,2};
    Polynomial p1(c, 2);
    p1 = p1;
    ASSERT_TRUE(p1.get_degree() == 2);
    ASSERT_TRUE(p1.get_coef(0) == 1);
    ASSERT_TRUE(p1.get_coef(1) == 2);
    ASSERT_TRUE(p1.get_coef(2) == 2);
}

TEST(PolynomialMoveTests, PolynomialMoveTestBase)
{
    double c[3]{1,2,2};
    Polynomial p1(c, 2);
    Polynomial p2(std::move(p1));
    ASSERT_TRUE(p1.get_degree() == -1);
    ASSERT_TRUE(p2.get_degree() == 2);
    ASSERT_TRUE(p2.get_coef(0) == 1);
    ASSERT_TRUE(p2.get_coef(1) == 2);
    ASSERT_TRUE(p2.get_coef(2) == 2);
}

TEST(PolynomialMoveTests, PolynomialMoveTestOperator)
{
    double c[3]{1,2,2};
    Polynomial p1(c, 2);
    Polynomial p2 = std::move(p1);
    ASSERT_TRUE(p1.get_degree() == -1);
    ASSERT_TRUE(p2.get_degree() == 2);
    ASSERT_TRUE(p2.get_coef(0) == 1);
    ASSERT_TRUE(p2.get_coef(1) == 2);
    ASSERT_TRUE(p2.get_coef(2) == 2);
}

TEST(PolynomialMoveTests, PolynomialMoveTestSelf)
{
    double c[3]{1,2,2};
    Polynomial p1(c, 2);
    p1 = std::move(p1);
    ASSERT_TRUE(p1.get_degree() == 2);
    ASSERT_TRUE(p1.get_coef(0) == 1);
    ASSERT_TRUE(p1.get_coef(1) == 2);
    ASSERT_TRUE(p1.get_coef(2) == 2);
}

TEST(PolynomialEqualTests, PolynomialEqualTestBase)
{
    double c1[3]{1,2,2}, c2[3]{1,2,2};
    Polynomial p1(c1, 2), p2(c2, 2);
    ASSERT_TRUE(p1.is_equal(p2));
}

TEST(PolynomialEqualTests, PolynomialEqualTestDifferentSize)
{
    double c1[3]{1,2,0}, c2[2]{1,2};
    Polynomial p1(c1, 2), p2(c2, 1);
    ASSERT_TRUE(p1.is_equal(p2));
    ASSERT_TRUE(p2.is_equal(p1));
}

TEST(PolynomialEqualTests, PolynomialEqualTestEdgeEps)
{
    double c1[3]{1,2,1e-10}, c2[2]{1,2};
    Polynomial p1(c1, 2), p2(c2, 1);
    ASSERT_TRUE(p1.is_equal(p2, 1e-9));
    ASSERT_TRUE(p2.is_equal(p1, 1e-9));
}

TEST(PolynomialTrimTests, PolynomialTrimTestBase)
{
    double c[3]{1,2,0};
    Polynomial p(c, 2);
    p.trim();
    ASSERT_TRUE(p.get_degree() == 1);
}

TEST(PolynomialTrimTests, PolynomialTrimTestEdgeEps)
{
    double c[3]{1,2,1e-10};
    Polynomial p(c, 2);
    p.trim(1e-11);
    ASSERT_TRUE(p.get_degree() == 2);
    p.trim(1e-9);
    ASSERT_TRUE(p.get_degree() == 1);
}

TEST(PolynomialTrimTests, PolynomialTrimTestToZero)
{
    double c[3]{0,0,0};
    Polynomial p(c, 2);
    p.trim();
    ASSERT_TRUE(p.get_degree() == -1);
}

TEST(PolynomialMulTests, PolynomialMulTestBase)
{
    double c1[2]{1,2};
    Polynomial p1(c1, 1), p2(c1, 1);
    p1.mul(p2);
    ASSERT_TRUE(p1.get_degree() == 2);
    EXPECT_NEAR(p1.get_coef(0), 1, 1e-5);
    EXPECT_NEAR(p1.get_coef(1), 4, 1e-5);
    EXPECT_NEAR(p1.get_coef(2), 4, 1e-5);
}

TEST(PolynomialMulTests, PolynomialMulTestZero)
{
    double c1[2]{1,2}, c2[1]{0};
    Polynomial p1(c1, 1), p2(c2, 0);
    p1.mul(p2);
    ASSERT_TRUE(p1.get_degree() == 1);
    EXPECT_NEAR(p1.get_coef(0), 0, 1e-5);
    EXPECT_NEAR(p1.get_coef(1), 0, 1e-5);
}

TEST(PolynomialEvalTests, PolynomialEvalTestBase)
{
    double c[2]{1,2};
    Polynomial p(c, 1);
    ASSERT_TRUE(p.evaluate(1) == 3);
}

TEST(PolynomialEvalTests, PolynomialEvalTestZero)
{
    double c[2]{1,2};
    Polynomial p(c, 1);
    ASSERT_TRUE(p.evaluate(0) == 1);
}