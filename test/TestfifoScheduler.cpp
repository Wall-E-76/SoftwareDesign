#include "../unity/src/unity.h
#include "src/Scheduler.cpp"
#include "src/fifoScheduler.h"
#include "src/Queue.cpp"
#include "src/Queue.h"
#include "src/Student.cpp"
#include "src/Job.cpp"
#include "src/User.cpp"

void setUp(){}
void tearDown(){}

void test_fillReserved(void) {
	FIFOScheduler fifo;
	Queue* q = new Queue();
	struct Curriculum curr {};
	curr.budget = 1000;
	curr.instResourceCap = 1000;
	curr.permission = { 0,1,0,0,0 };
	curr.expoParameter = 10;
	int running = 30;  //only looking at medium queue, which we will intialize to say is runnning 30 nodes of the 40 reserved nodes
	User* dummy = new Student(curr);
	Job* first = new Job(dummy, 1, 16 * 6, 0, 8, 8);
	Job* second = new Job(dummy, 1, 16 * 12, 0, 8, 8);
	q->insertJob(first);
	q->insertJob(second);
	std::vector<Job*> results; //our return vector
	int state = 2; //start of in a state where there is no need to check time
	double currentTime = 70; //well before weekend cutoff
	results = fifo.fillReserved(running, running, q, state, 3, WEEKENDCUTOFF, currentTime, medMin, currentTime);
	TEST_ASSERT(results.size == 1); //should only have taken that first job
	TEST_ASSERT_EQUAL_INT(36, running); //should have increased nodes running to 36
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_fillReserved);
    return UNITY_END();
}