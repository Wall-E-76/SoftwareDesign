#include "../unity/src/unity.h"
#include "../src/Researcher.h"
#include "../src/User.cpp"

void setUp(){}

void tearDown(){}

void test_getter(void){
    struct Group g = {5,10,{1,1,1,0,1}};
    Researcher* r = new Researcher(g,15);
    TEST_ASSERT_EQUAL_INT(15,r->getGrant());
}

void test_spend(void){
    struct Group g = {5,10,{1,1,1,0,1}};
    Researcher* r = new Researcher(g,15);
    TEST_ASSERT(r->spend(10))
    TEST_ASSERT_EQUAL_FLOAT(10,r->getSpendings());
    TEST_ASSERT(r->spend(8.1));
    TEST_ASSERT_EQUAL_FLOAT(18.1,r->getSpendings());
    TEST_ASSERT(!r->spend(10));
    TEST_ASSERT_EQUAL_FLOAT(18.1,r->getSpendings());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_getter);
    RUN_TEST(test_spend);
    return UNITY_END();
}