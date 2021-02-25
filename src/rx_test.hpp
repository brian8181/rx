#ifndef _RX_TEST_H
#define _RX_TEST_H

#include <cppunit/Test.h>

class RxTest : public CppUnit::TestFixture
{
  
private:
    CPPUNIT_TEST_SUITE(RxTest);
    CPPUNIT_TEST(testNoOption);
    CPPUNIT_TEST(testOptionHelp);
    CPPUNIT_TEST(testOptionHelpLong);
    CPPUNIT_TEST(testOptionVerbose);
    CPPUNIT_TEST(testOptionVerboseLong);
    CPPUNIT_TEST(testFileOption);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);    

protected:
    void testNoOption(void);
    void testOptionHelp(void);
    void testOptionHelpLong(void);
    void testOptionVerbose(void);
    void testOptionVerboseLong(void);  
    void testFileOption(void);
      
private:
    int m_argc;
    char* m_argv[10];
    
};
