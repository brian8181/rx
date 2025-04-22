// TestCalculator.cpp

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "test.hpp"

class rx_test_test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(rx_test_test);
    CPPUNIT_TEST(testAdd);
    CPPUNIT_TEST(testSubtract);
    CPPUNIT_TEST_SUITE_END();

private:

public:
    void setUp() override
    {

    }

    void tearDown() override
    {

    }

    void testAdd()
    {
        CPPUNIT_ASSERT_EQUAL(5, add(2, 3));
    }

    void testSubtract()
    {
        CPPUNIT_ASSERT_EQUAL(-1, subtract(2, 3));
    }
};

int main()
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(rx_test_test::suite());
    runner.run();
    return 0;
}
