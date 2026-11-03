#include "unity_fixture.h"

TEST_GROUP(example);

TEST_SETUP(example)
{
}

TEST_TEAR_DOWN(example)
{
}

TEST(example, StartHere)
{
    TEST_FAIL_MESSAGE("Start Here");
}