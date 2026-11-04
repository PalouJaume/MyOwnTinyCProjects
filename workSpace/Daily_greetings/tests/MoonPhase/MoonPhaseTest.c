#include "unity.h"
#include "unity_fixture.h"
#include "moonPhase.h"

TEST_GROUP(moonPhase);

TEST_SETUP(moonPhase)
{
}

TEST_TEAR_DOWN(moonPhase)
{
}

TEST(moonPhase, StartHere)
{
    //TEST_FAIL_MESSAGE("Start Here");
}

TEST(moonPhase, GetMoonPhase)
{
    TEST_ASSERT_EQUAL_STRING("new", moon_phase(2026, 10, 9));
}