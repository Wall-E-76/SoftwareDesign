#include "../unity/src/unity.h"
#include "../src/Job.h"
#include "src/Student.h"
#include "src/User.h"

void setUp(){}

void tearDown(){}

void test_getter(void){
    std::array <bool,5> p = {1,1,1,0,0};
    struct Curriculum c {20, 5, 5, p};
    Student* s;
    Job j = Job(s, 1, 16, 1, 20.1, 25.1);
    TEST_ASSERT_EQUAL_INT(1, j.getNodes());
    TEST_ASSERT_EQUAL_INT(1,j.getCategory());
    TEST_ASSERT(j.needsGPU());
    TEST_ASSERT_EQUAL_FLOAT(20.1,j.getRuntime());
    TEST_ASSERT_EQUAL_FLOAT(25.1,j.getReservedTime());
    j.setTimeEnteredQueue(0.2);
    TEST_ASSERT_EQUAL_FLOAT(0.2, j.getTimeEnteredQueue());
    j.setTimeLeftQueue(10.4);
    TEST_ASSERT_EQUAL_FLOAT(10.4, j.getTimeLeftQueue());
    TEST_ASSERT(s == j.getOwner());
}

void test_doneRunning(void){
    std::array <bool,5> p = {1,1,1,0,0};
    struct Curriculum c {20, 5, 5, p};
    Student* s;
    Job j = Job(s, 1, 16, 1, 20.1, 25.1);
    j.setTimeEnteredQueue(0.2);
    TEST_ASSERT(!j.doneRunning(15));
    TEST_ASSERT(j.doneRunning(30.6));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_getter);
    RUN_TEST(test_doneRunning);
    return UNITY_END();
}