#include "unity_fixture.h"

TEST_GROUP_RUNNER(moonPhase)
{
    RUN_TEST_CASE(moonPhase, StartHere);
    RUN_TEST_CASE(moonPhase, GetMoonPhase);
}