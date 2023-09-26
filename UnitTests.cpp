#include "UnitTests.h"
#include "UnitTests\CallablesTest.h"
#include "UnitTests\LEDBlinkerTest.h"

String result = "No result.";

void testStart()
{
    testCallables();
    testToggleLEDStart();
}

bool testEnd()
{
    if (!testCallablesEnd())
    {
        result = "testCallables failed";
        return false;
    }
    result = "Pass";
    return true;
}

String testResult()
{
    return result;
}