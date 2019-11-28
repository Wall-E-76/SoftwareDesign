#include "../unity/src/unity.h"
#include "../src/Scheduler.h"
#include "../src/Queue.cpp"
#include "../src/Job.cpp"
#include "MockScheduler.cpp"

void setUp(){}

void tearDown(){}

void test_addQueues(void){
    Scheduler* s = new MockScheduler();
    std::array<Queue*,5> queues;
    Queue* q4 = new Queue();
    queues[4] = q4;
    for (int i =0; i<4;i++){
        Queue* q = new Queue();
        queues[i] = q;
    }
    s->addQueues(queues);
    TEST_ASSERT(s->getQueues().at(4)==q4);
}



int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_addQueues);
    return UNITY_END();
}