#include "../unity/src/unity.h"
#include "src/Scheduler.cpp"
#include "src/fifoScheduler.h"
#include "src/Queue.cpp"
#include "src/Queue.h"
#include "src/Student.cpp"
#include "src/Job.cpp"
#include "src/User.cpp"

void setUp(){}

void tearDown(){}

void test_fillReserved(void){
    FIFOScheduler s = FIFOScheduler();
    Queue* q = new Queue();
    Student* student;
    Job* j = new Job(student,0,8,0,1,2);
    q->insertJob(j);
    for (int i = 0; i<5; i++){
        Job* j = new Job(student,0,16,0,1,2);
        q->insertJob(j);
    }
    //int& running;
    //int& runningTotal;
    //s.fillReserved(running,runningTotal,q,0,0,100,0.0,shortMin);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_fillReserved);
    return UNITY_END();
}