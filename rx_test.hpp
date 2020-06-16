#ifndef _RX_TEST_H
#define _RX_TEST_H

#include <cppunit/Test.h>

class RxTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(RxTest);
    CPPUNIT_TEST(testAddition);
    CPPUNIT_TEST(testMultiply);
    CPPUNIT_TEST(testParseOptionHelp);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

protected:
    void testAddition(void);
    void testMultiply(void);
    void testParseOptionHelp(void);

private:

    //CBasicMath *mTestObj;
    int m_argc;
    char* m_argv[3];
    
};

#endif