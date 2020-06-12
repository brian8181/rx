#ifndef _RX_TEST_H
#define _RX_TEST_H

#include <cppunit/Test.h>

//-----------------------------------------------------------------------------

class RxTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(RxTest);
    CPPUNIT_TEST(testAddition);
    CPPUNIT_TEST(testMultiply);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

protected:
    void testAddition(void);
    void testMultiply(void);

private:

    //CBasicMath *mTestObj;
};


#endif