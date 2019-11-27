#include "../unity/src/unity.h"
#include "../src/Generator.h"
#include "../src/Job.cpp"
#include "../src/User.cpp"
#include "../src/Queue.cpp"
#include "../src/Student.cpp"
#include <iostream>

void setUp(){}

void tearDown(){}

void test_constructor(){
    Generator g = Generator();
    std::array<PropertyQueue,5> p = g.getProperty();
    TEST_ASSERT_EQUAL_INT(SHORTMAXNODES, p[0].nodeMax);
    TEST_ASSERT_EQUAL_INT(0, p.at(0).nodeMinExclusive);
    TEST_ASSERT_EQUAL_FLOAT(1,p.at(0).timeMax);
    TEST_ASSERT_EQUAL_INT(MEDIUMMAXNODES, p.at(1).nodeMax);
    TEST_ASSERT_EQUAL_INT(SHORTMAXNODES, p.at(1).nodeMinExclusive);
    TEST_ASSERT_EQUAL_FLOAT(8,p.at(1).timeMax);
    TEST_ASSERT_EQUAL_INT(LARGEMAXNODES, p.at(2).nodeMax);
    TEST_ASSERT_EQUAL_INT(MEDIUMMAXNODES, p.at(2).nodeMinExclusive);
    TEST_ASSERT_EQUAL_FLOAT(16,p.at(2).timeMax);
    TEST_ASSERT_EQUAL_INT(GPUMAXNODES, p.at(3).nodeMax);
    TEST_ASSERT_EQUAL_INT(0, p.at(3).nodeMinExclusive);
    TEST_ASSERT_EQUAL_FLOAT(8,p.at(3).timeMax);
    TEST_ASSERT_EQUAL_INT(HUGEMAXNODES, p.at(4).nodeMax);
    TEST_ASSERT_EQUAL_INT(15, p.at(4).nodeMinExclusive);
    TEST_ASSERT_EQUAL_FLOAT(64,p.at(4).timeMax);
}

void test_addUser(void){
    Generator g = Generator();
    struct Curriculum c = {5,10,60,{1,1,1,0,1}};
    Student* s = new Student(c);
    g.addUser(s);
    TEST_ASSERT(s==g.getUsers()[0]);
}

void test_randomCategory(void){
    Generator g = Generator();
    struct Curriculum c = {5,10,60,{1,1,1,0,1}};
    Student* s = new Student(c);
    g.addUser(s);
    int n =0;
    int randomNum1 = g.randomCategory(0);
    std::cout <<"Random num 1 :" << randomNum1<< std::endl;
    TEST_ASSERT(randomNum1 == 0||randomNum1==1||randomNum1==2||randomNum1==3||randomNum1==4);
    int randomNum2 = g.randomCategory(0);
    std::cout <<"Random num 2 :" << randomNum2<< std::endl;
    while (randomNum1==randomNum2 & n<30){
        n++;
        randomNum2 = g.randomCategory(0);
        std::cout <<"Random num 2 :" << randomNum2<< std::endl;
    }
    TEST_ASSERT_MESSAGE(n!=30, "randomCategory test went out of bound");
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_randomCategory);
    RUN_TEST(test_addUser);
    RUN_TEST(test_constructor);
    return UNITY_END();
}