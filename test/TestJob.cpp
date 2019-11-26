#include "unity.h"
#include "Job.h"
#include "users/Student.cpp"

void setUp(){

}

void tearDown(){

}

void test_getter(void){
    std::array <bool,5> p = {1,1,1,0,0};
    struct Curriculum c {
        20,
        5,
        5,
        p
    };
    Student* s = new Student(c);
    Job j = Job(s, 1, 15, 0, 20.1);
    TEST_ASSERT_EQUAL_HEX8(15, j.getCores());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_getter);
    return UNITY_END();
}