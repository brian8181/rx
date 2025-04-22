// main.cpp
#include <cppunit/ui/text/TestRunner.h>
#include "TestCalculator.cpp" // Include test implementation

int main()
{
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(TestCalculator::suite());
    runner.run();
    return 0;
}
