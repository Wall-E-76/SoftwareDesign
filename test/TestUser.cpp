#include "../unity/src/unity.h"
#include "../src/User.h"
#include "../src/Student.cpp"

void setUp(){}

void tearDown(){}

void test_getter(void){
    std::array<bool,5> p = {1,1,1,0,1};
    struct Curriculum c = {5.1,10,60,p};
    Student* s = new Student(c);
    TEST_ASSERT_EQUAL_FLOAT(5.1,s->getBudget());
    TEST_ASSERT_EQUAL_INT(0,s->getSpendings());
    for (int i =0; i<5; i++){
        TEST_ASSERT_EQUAL_INT(p[i],s->getPermission()[i]);
    }
    TEST_ASSERT_EQUAL_INT(10,s->getExpoParameter());
}

void test_time(void){
    struct Curriculum c = {5,10,60,{1,1,1,0,1}};
    Student* s = new Student(c);
    TEST_ASSERT(s->isTime(1.0));
    s->generateNewTime(2);
    TEST_ASSERT(!s->isTime(2));
    TEST_ASSERT(s->isTime(13));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_getter);
    RUN_TEST(test_time);
    return UNITY_END();
}