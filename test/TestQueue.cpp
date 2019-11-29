#include "../unity/src/unity.h"
#include "../src/Job.cpp"
#include "src/Queue.h"

void setUp(){}

void tearDown(){}

void test_insertJob(void){
    Queue* q = new Queue();
    Job* j1;
    q->insertJob(j1);
    TEST_ASSERT(j1 == q->getJobsInQueue()[0]);
    Job* j2;
    q->insertJob(j2);
    TEST_ASSERT(j2 == q->getJobsInQueue()[1]);
}

void test_nextJob(void){
    Queue* q = new Queue();
    Job* j1;
    q->insertJob(j1);
    Job* j2;
    q->insertJob(j2);
    TEST_ASSERT(j1 == q->nextJob());
}

void test_removeJob(void){
    Queue* q = new Queue();
    Job* j1;
    q->insertJob(j1);
    Job* j2;
    q->insertJob(j2);
    q->removeJob(0,0.2);
    TEST_ASSERT_EQUAL_INT(1,q->getJobsInQueue().size());
    TEST_ASSERT(j2 == q->getJobsInQueue()[0]);
    TEST_ASSERT_EQUAL_INT(0.2,j1->getTimeLeftQueue());
}
/*
void test_numJobsProcessed(void){
    Queue* q = new Queue();
    TEST_ASSERT_EQUAL_INT(0,q->getNumJobsProcessed());
    q->incrNumJobsProcessed();
    TEST_ASSERT_EQUAL_INT(1,q->getNumJobsProcessed());
}

void test_waitTime(void){
    TEST_ASSERT(true);
    Queue* q = new Queue();
    TEST_ASSERT_EQUAL_FLOAT(0, q->getTotalWaitTime());
    q->addWaitTime(30.2);
    TEST_ASSERT_EQUAL_FLOAT(30.2, q->getTotalWaitTime());
    q->addWaitTime(5);
    TEST_ASSERT_EQUAL_FLOAT(35.2, q->getTotalWaitTime());
}*/

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_insertJob);
    RUN_TEST(test_nextJob);
    RUN_TEST(test_removeJob);
    //RUN_TEST(test_numJobsProcessed);
    //RUN_TEST(test_waitTime);
    return UNITY_END();
}