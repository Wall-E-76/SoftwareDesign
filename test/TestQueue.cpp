#include "../unity/src/unity.h"
#include "../src/Job.cpp"
#include "../src/Student.h"
#include "src/Queue.h"

void setUp(){}

void tearDown(){}

void test_insertJob(void){
    Queue* q = new Queue();
    Student* student;
    Job* j1 = new Job(student,0,5,0,1.2,1.3);
    q->insertJob(j1,0.1);
    TEST_ASSERT(j1 == q->getJobAt(0));
    TEST_ASSERT_EQUAL_FLOAT(0.1, j1->getTimeEnteredQueue());
    Job* j2 = new Job(student,0,5,0,1.2,1.3);
    q->insertJob(j2,3.1);
    TEST_ASSERT(j2 == q->getJobAt(1));
    TEST_ASSERT_EQUAL_FLOAT(3.1,j2->getTimeEnteredQueue());
}

void test_accessJob(void){
    Queue* q = new Queue();
    Student* student;
    Job* j1 = new Job(student,0,5,0,1.2,1.3);
    q->insertJob(j1,0.1);
    Job* j2 = new Job(student,0,5,0,1.2,1.3);
    q->insertJob(j2,3);
    TEST_ASSERT(j1 == q->nextJob());
    TEST_ASSERT_EQUAL_INT(1,q->nextJobT(2.3));
    TEST_ASSERT_EQUAL_INT(-1,q->nextJobT(0.5));

    TEST_ASSERT(j1 == q->getJobAt(0))
    TEST_ASSERT(j2 == q->getJobAt(1));
}

void test_removeJob(void){
    Queue* q = new Queue();
    Student* student;
    Job* j1 = new Job(student,0,5,0,1.2,1.3);
    q->insertJob(j1,0.1);
    Job* j2 = new Job(student,0,5,0,1.2,1.3);
    q->insertJob(j2,3);
    q->removeJob(0,0.2);
    TEST_ASSERT_EQUAL_INT(1,q->getJobsInQueue().size());
    TEST_ASSERT(j2 == q->getJobAt(0));
    TEST_ASSERT_EQUAL_INT(0.2,j1->getTimeLeftQueue());
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_insertJob);
    RUN_TEST(test_accessJob);
    RUN_TEST(test_removeJob);
    return UNITY_END();
}