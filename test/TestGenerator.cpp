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

void test_roundUp(void){
    Generator g = Generator();
    TEST_ASSERT_EQUAL_FLOAT(TIMESTEP*5, g.roundUp(TIMESTEP*5-TIMESTEP*0.1));
    TEST_ASSERT_EQUAL_FLOAT(TIMESTEP*4, g.roundUp(TIMESTEP*5-TIMESTEP*0.6));
    TEST_ASSERT_EQUAL_FLOAT(TIMESTEP*5, g.roundUp(TIMESTEP*5-TIMESTEP*0.5));
    TEST_ASSERT_EQUAL_FLOAT(TIMESTEP*5, g.roundUp(TIMESTEP*5));
}

void test_createJob(){
    Generator g = Generator();
    struct Curriculum c = {5,10,60,{0,1,1,0,0}};
    Student* s1 = new Student(c);
    Student* s2 = new Student(c);
    g.addUser(s1);
    g.addUser(s2);
    Job j = g.createJob(1);
    TEST_ASSERT(j.getOwner() == s2);
    TEST_ASSERT_EQUAL_FLOAT(0,j.getTimeLeftQueue());
    TEST_ASSERT(j.getCategory() == 2 || j.getCategory() == 1);
    TEST_ASSERT(!j.needsGPU());
    TEST_ASSERT_GREATER_OR_EQUAL(j.getReservedTime(),g.getProperty()[j.getCategory()].timeMax);
    TEST_ASSERT_GREATER_OR_EQUAL(j.getNodes(),g.getProperty()[j.getCategory()].nodeMax);
    TEST_ASSERT_LESS_OR_EQUAL(j.getNodes(),g.getProperty()[j.getCategory()].nodeMinExclusive);
    TEST_ASSERT_GREATER_OR_EQUAL(j.getRuntime(),j.getReservedTime());
    TEST_ASSERT(!j.doneRunning(1.0));
    TEST_ASSERT_EQUAL_FLOAT(0,j.getTimeEnteredQueue());
    Job j2 = g.createJob(1);
    TEST_ASSERT(j.getNodes()!=j2.getNodes()||j.getCategory() != j2.getCategory()||j.getReservedTime()!=j2.getReservedTime()||j.getRuntime()!=j2.getRuntime());
}

void test_addQueues(void){
    Generator g = Generator();
    std::array<Queue*,5> queues;
    for (int i =0; i<5;i++){
        Queue* q = new Queue();
        queues[i] = q;
    }
    g.addQueues(queues);
    for (int i =0; i<5;i++){
        TEST_ASSERT_EQUAL(g.getQueues()[i], queues[i]);
    }

}

void test_check(){
    Generator g = Generator();
    std::array<Queue*,5> queues;
    for (int i =0; i<5;i++){
        Queue* q = new Queue();
        queues[i] = q;
    }
    g.addQueues(queues);
    struct Curriculum c = {5,10,60,{1,0,1,0,0}};
    Student* s = new Student(c);
    g.addUser(s);
    TEST_ASSERT_EQUAL_FLOAT(0,s->getSpendings());
    Job j = {s, 0, 1, 0, g.roundUp(0.8),g.roundUp(1.6)};
    g.check(&j,0.5);
    TEST_ASSERT_EQUAL_FLOAT(MACHINE_COST*j.getRuntime()*j.getNodes(), s->getSpendings());
    TEST_ASSERT(&j==g.getQueues().at(j.getCategory())->nextJob());
    double spendings = s->getSpendings();
    Job j2 = {s, 0, 1, 0, g.roundUp(0.8),g.roundUp(1.6)};
}

void test_lookForJobs(){

}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_randomCategory);
    RUN_TEST(test_addUser);
    RUN_TEST(test_constructor);
    RUN_TEST(test_roundUp);
    RUN_TEST(test_createJob);
    RUN_TEST(test_addQueues);
    RUN_TEST(test_check);
    RUN_TEST(test_lookForJobs);

    return UNITY_END();
}