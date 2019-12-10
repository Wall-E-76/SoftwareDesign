#include "../unity/src/unity.h"
#include "src/Scheduler.cpp"
#include "src/fifoScheduler.h"
#include "src/Queue.cpp"
#include "src/Queue.h"
#include "src/Student.cpp"
#include "src/Job.cpp"
#include "src/User.cpp"

void setUp(){}

void tearDown(){}

void test_fillReserved(void){
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_fillReserved);
    return UNITY_END();
}