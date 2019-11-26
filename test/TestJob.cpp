#include "unity.h"
#include "Job.h"
#include "users/Student.h"

void setUp(){

}

void tearDown(){

}

void test_getter(void){
    std::array <bool,5> p = {1,1,1,0,0};
    struct Curriculum c {20, 5, 5, p};
    Student* s = new Student(c);
    Job j = Job(s, 1, 16, 0, 20.1, 25);
    TEST_ASSERT_EQUAL_INT(1, j.getNodes());
    TEST_ASSERT_EQUAL_INT(1,j.getCategory());
    TEST_ASSERT(j.needsGPU());
    TEST_ASSERT_EQUAL_FLOAT(20.1,j.getRuntime());
    j.setTimeEnteredQueue(0.2);
    TEST_ASSERT_EQUAL_FLOAT(0.2, j.getTimeEnteredQueue());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_getter);
    return UNITY_END();
}