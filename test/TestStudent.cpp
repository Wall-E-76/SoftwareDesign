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

void test_whatAmI(void){
    struct Curriculum c = {5,10,60,{1,1,1,0,1}};
    Student* s = new Student(c);
    TEST_ASSERT_EQUAL(s->whatAmI(),'S');
}

void test_spend(void){
    struct Curriculum c = {5,10,60,{1,1,1,0,1}};
    Student* s = new Student(c);
    TEST_ASSERT(s->spend(3));
    TEST_ASSERT_EQUAL_INT(3,s->getSpendings());
    TEST_ASSERT(!s->spend(10));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_getter);
    RUN_TEST(test_whatAmI);
    return UNITY_END();
}