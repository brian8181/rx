#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>
#include "rx_test.hpp"
#include "rx.hpp"

using namespace CppUnit;
using namespace std;


void RxTest::setUp(void)
{
    m_argc = 3;
    m_argv[0] = "/src/rx";
    m_argv[1] = "a{3}b{2}c"; 
    m_argv[2] = "aaabbc";

//     char*
//     params[] = {
//       "Zara Ali",
//       "Hina Ali",
//       "Nuha Ali",
//       "Sara Ali"
//    }; 

   //m_argv[0] = params[0];

    //mTestObj = new CBasicMath();
    //char* m_argv = new char[3];

}

void RxTest::tearDown(void)
{
    //delete mTestObj;
}

void RxTest::testAddition(void)
{
    CPPUNIT_ASSERT(1);
    CPPUNIT_ASSERT(1);
    CPPUNIT_ASSERT(1);
    CPPUNIT_ASSERT(1);
    CPPUNIT_ASSERT(2);
}

void RxTest::testMultiply(void)
{
    CPPUNIT_ASSERT(1);
}

void RxTest::testParseOptionHelp(void)
{
    //parse_options(3, m_argv);
    CPPUNIT_ASSERT(add(5, 2) == 7);
    CPPUNIT_ASSERT(parse_options(3, m_argv) == 0);
}


CPPUNIT_TEST_SUITE_REGISTRATION( RxTest );

int main(int argc, char* argv[])
{
    // informs test-listener about testresults
    CPPUNIT_NS::TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
    testrunner.run(testresult);

    // output results in compiler-format
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write ();

    // Output XML for Jenkins CPPunit plugin
    ofstream xmlFileOut("cppRxTestResults.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}