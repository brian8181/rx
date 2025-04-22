// TestCalculator.cpp
#include <cppunit/extensions/HelperMacros.h>
#include "Calculator.h"

class TestCalculator : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestCalculator);
    CPPUNIT_TEST(testAdd);
    CPPUNIT_TEST(testSubtract);
    CPPUNIT_TEST_SUITE_END();

private:
    Calculator* calc;

public:
    void setUp() override
    {
        calc = new Calculator();
    }

    void tearDown() override
    {
        delete calc;
    }

    void testAdd()
    {
        CPPUNIT_ASSERT_EQUAL(5, calc->add(2, 3));
    }

    void testSubtract()
    {
        CPPUNIT_ASSERT_EQUAL(-1, calc->subtract(2, 3));
    }
};
