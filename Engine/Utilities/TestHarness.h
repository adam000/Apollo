#ifndef __apollo_utilities_test_harness_h
#define __apollo_utilities_test_harness_h

#include <string>
#include <vector>

namespace TestHarness
{

bool InvokeTest ( const std::string& testName, const std::vector<std::string>& testParameters );

}

#endif