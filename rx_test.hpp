#ifndef _RX_TEST_H
#define _RX_TEST_H

#include <cppunit/Test.h>

class RxTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(RxTest);
    CPPUNIT_TEST(testNoOptions);
    CPPUNIT_TEST(testOptionHelp);
    CPPUNIT_TEST(testOptionHelpLong);
    CPPUNIT_TEST(testOptionVerbose);
    CPPUNIT_TEST(testOptionVerboseLong);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

protected:
    void testNoOptions(void);
    void testOptionHelp(void);
    void testOptionHelpLong(void);
    void testOptionVerbose(void);
    void testOptionVerboseLong(void);
       
   
private:

    int m_argc;
    char* m_argv[10];
    
};

#endif