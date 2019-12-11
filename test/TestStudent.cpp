#include "../unity/src/unity.h"
#include "../src/Student.h"
#include "../src/User.cpp"

void setUp(){}

void tearDown(){}

void test_getter(void){
    struct Curriculum c = {5,10,60,{1,1,1,0,1}};
    Student* s = new Student(c);
    TEST_ASSERT_EQUAL_INT(60,s->getInstResourceCapt());
}

void test_spend(void){
    struct Curriculum c = {60,10,40,{1,1,1,0,1}};
    Student* s = new Student(c);
    TEST_ASSERT(s->spend(30));
    TEST_ASSERT_EQUAL_INT(30,s->getSpendings());
    TEST_ASSERT(!s->spend(50));
    TEST_ASSERT_EQUAL_INT(30,s->getSpendings());
    TEST_ASSERT(!s->spend(31));
    TEST_ASSERT_EQUAL_INT(30,s->getSpendings());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_getter);
    RUN_TEST(test_spend);
    return UNITY_END();
}