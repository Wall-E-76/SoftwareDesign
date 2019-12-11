#include "../unity/src/unity.h"
#include <chrono>
#include "src/Simulation.h"
#include "MockScheduler.cpp"
#include "src/Queue.cpp"
#include "src/Generator.cpp"
#include "src/Job.cpp"
#include "src/Machine.cpp"
#include "src/Scheduler.cpp"
#include "src/Researcher.cpp"
#include "src/Student.cpp"
#include "src/User.cpp"
#include "src/fifoScheduler.cpp"


void setUp(){}

void tearDown(){}

void test_initialization(void){
    Simulation sim = Simulation(128,4);
    MockScheduler* s = new MockScheduler();
    sim.addScheduler(s);
    TEST_ASSERT(s==sim.getScheduler());
    std::array<Queue*,5> queues;
    Queue* q4 = new Queue();
    queues[4]=q4;
    for (int i =0; i<4;i++){
        Queue* q = new Queue();
        queues[i] = q;
    }
    sim.addQueues(queues);
    TEST_ASSERT(q4 == sim.getQueues()[4]);
    Generator* g = new Generator();
    sim.addGenerator(g);
    TEST_ASSERT(g == sim.getGenerator());
}

void test_setupFile(void){
    Simulation s (128,1);
    s.setupFile("./test/inputData.txt");
    std::vector<User*> users = s.getGenerator()->getUsers();
    TEST_ASSERT_EQUAL_INT(8, users.size());
    for (int i = 0; i<3;i++){
        Researcher* r;
        r = (Researcher*) users[i];
        TEST_ASSERT_EQUAL_FLOAT(5000,r->getBudget());
        TEST_ASSERT_EQUAL_INT(40,r->getExpoParameter());
        std::array<int,5> p = {0,0,0,0,1};
        for (int j = 0; j<5; j++){
            TEST_ASSERT_EQUAL_INT(p[j],r->getPermission()[j]);
        }
        if (i == 0) TEST_ASSERT_EQUAL_INT(14, r->getGrant());
        if (i == 1) TEST_ASSERT_EQUAL_INT(4, r->getGrant());
    }
    for (int i = 3; i<5;i++){
        Researcher* r;
        r = (Researcher*) users[i];
        TEST_ASSERT_EQUAL_FLOAT(5000,r->getBudget());
        TEST_ASSERT_EQUAL_INT(20,r->getExpoParameter());
        std::array<int,5> p = {0,0,1,0,0};
        for (int j = 0; j<5; j++){
            TEST_ASSERT_EQUAL_INT(p[j],r->getPermission()[j]);
        }
    }
    for (int i = 5; i<7;i++){
        Student* r;
        r = (Student*) users[i];
        TEST_ASSERT_EQUAL_FLOAT(200,r->getBudget());
        TEST_ASSERT_EQUAL_INT(40,r->getExpoParameter());
        TEST_ASSERT_EQUAL_FLOAT(20, r->getInstResourceCapt());
        std::array<int,5> p = {1,1,1,1,0};
        for (int j = 0; j<5; j++){
            TEST_ASSERT_EQUAL_INT(p[j],r->getPermission()[j]);
        }
    }
    for (int i = 7; i<8;i++){
        Student* r;
        r = (Student*) users[i];
        TEST_ASSERT_EQUAL_FLOAT(3000,r->getBudget());
        TEST_ASSERT_EQUAL_INT(78,r->getExpoParameter());
        TEST_ASSERT_EQUAL_FLOAT(50, r->getInstResourceCapt());
        std::array<int,5> p = {1,1,1,0,0};
        for (int j = 0; j<5; j++){
            TEST_ASSERT_EQUAL_INT(p[j],r->getPermission()[j]);
        }
    }
}

void test_scenario(void){
    Simulation s (128,3);
    s.setupFile("./test/SimpleScenario.txt");
    s.computeTimeSteps();
    TEST_ASSERT_GREATER_OR_EQUAL(1,s.getMachine()->getProcessedByQueue()[0]);
    for (int i = 1; i<5; i++){
        TEST_ASSERT_EQUAL_INT(0,s.getMachine()->getProcessedByQueue()[i]);
    }
    TEST_ASSERT_GREATER_OR_EQUAL(0,s.getMachine()->getMachineHoursConsumed()/(double(WEEKDAYCUTOFF) * totalNodes));
    TEST_ASSERT_LESS_OR_EQUAL(0,s.getMachine()->getMachineHoursConsumed()/(double(WEEKDAYCUTOFF) * totalNodes));
    TEST_ASSERT_GREATER_OR_EQUAL(0,s.getMachine()->getPricePaid());
    TEST_ASSERT_LESS_OR_EQUAL(6*MACHINE_COST, s.getMachine()->getPricePaid());
    TEST_ASSERT_GREATER_OR_EQUAL(0, s.getMachine()->getMachineHoursConsumed());
    TEST_ASSERT_LESS_OR_EQUAL(6, s.getMachine()->getMachineHoursConsumed());
    for (int i = 0; i<5; i++){
        TEST_ASSERT_EQUAL_FLOAT(0,s.getMachine()->getWaitTimeByQueue()[i]);
    }
    TEST_ASSERT_EQUAL_FLOAT(1, s.getMachine()->getTurnaroundRatioSummed()/s.getMachine()->getProcessedByQueue()[0]);
    s.getMachine()->resetMetrics();
    s.setWeekCounter(2);

    s.computeTimeSteps();
    TEST_ASSERT_GREATER_OR_EQUAL(0,s.getMachine()->getProcessedByQueue()[0]);
    TEST_ASSERT_LESS_OR_EQUAL(8,s.getMachine()->getProcessedByQueue()[0]);
    for (int i = 1; i<5; i++){
        TEST_ASSERT_EQUAL_INT(0,s.getMachine()->getProcessedByQueue()[i]);
    }
    TEST_ASSERT_GREATER_OR_EQUAL(0,s.getMachine()->getMachineHoursConsumed()/(double(WEEKDAYCUTOFF) * totalNodes));
    TEST_ASSERT_LESS_OR_EQUAL(1,s.getMachine()->getMachineHoursConsumed()/(double(WEEKDAYCUTOFF) * totalNodes));
    TEST_ASSERT_GREATER_OR_EQUAL(0,s.getMachine()->getPricePaid());
    TEST_ASSERT_LESS_OR_EQUAL(8*MACHINE_COST, s.getMachine()->getPricePaid());
    TEST_ASSERT_GREATER_OR_EQUAL(0, s.getMachine()->getMachineHoursConsumed());
    TEST_ASSERT_LESS_OR_EQUAL(8, s.getMachine()->getMachineHoursConsumed());
    for (int i = 1; i<5; i++){
        TEST_ASSERT_EQUAL_FLOAT(0,s.getMachine()->getWaitTimeByQueue()[i]);
    }
    if (s.getMachine()->getProcessedByQueue()[0] != 0){
        TEST_ASSERT_LESS_OR_EQUAL(64,s.getMachine()->getWaitTimeByQueue()[0]/(s.getMachine()->getProcessedByQueue()[0]+1));
        TEST_ASSERT_LESS_OR_EQUAL(128, s.getMachine()->getTurnaroundRatioSummed()/s.getMachine()->getProcessedByQueue()[0]);
    }
    else {
        TEST_ASSERT_LESS_OR_EQUAL(0,s.getMachine()->getWaitTimeByQueue()[0]);
    }

}

void test_performance(void){
    double time =0;
    Simulation s (128,10);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    s.run();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::seconds> (end - begin).count();
    TEST_ASSERT_LESS_OR_EQUAL(5, time/10);
}

void test_Volume(void){
    double time = 0;
    Simulation s (128,3);
    s.setupFile("./test/StressScenario.txt");
    for (int i = 0; i< 10; i++){
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        s.computeTimeSteps();
        s.getMachine()->resetMetrics();
        s.setWeekCounter(i+1);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        time += std::chrono::duration_cast<std::chrono::seconds> (end - begin).count();
    }
    TEST_ASSERT_LESS_OR_EQUAL(5, time/10);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_initialization);
    RUN_TEST(test_setupFile);
    RUN_TEST(test_scenario);
    RUN_TEST(test_performance);
    RUN_TEST(test_Volume);
    return UNITY_END();
}