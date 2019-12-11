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

void test_fillReserved(void) {
	FIFOScheduler fifo;
	Queue* q = new Queue();
	struct Curriculum curr {};
	curr.budget = 1000;
	curr.instResourceCap = 1000;
	curr.permission = { 0,1,0,0,0 };
	curr.expoParameter = 10;
	int running = 30;  int runningTotal=30;//only looking at medium queue, which we will intialize to say is runnning 30 nodes of the 40 reserved nodes
	User* dummy = new Student(curr);
	Job* first = new Job(dummy, 1, 16 * 5, 0, 8, 8);
	Job* second = new Job(dummy, 1, 16 * 4, 0, 8, 8);
	Job* third = new Job(dummy, 1, 16 * 12, 0, 8, 8);
	q->insertJob(first);
	q->insertJob(second);
	q->insertJob(third);
	std::vector<Job*> results; //our return vector
	int state = 2; //start of in a state where there is no need to check time
	double currentTime = 70; //well before weekend cutoff
	results = fifo.fillReserved(running, runningTotal, q, state, 3, WEEKENDCUTOFF, currentTime, medMin, currentTime);
	TEST_ASSERT(results.size() == 2); //should only have taken first two jobs
	TEST_ASSERT(q.size()==1); //still one guy waiting in line
	TEST_ASSERT_EQUAL_INT(39, running); //should have increased nodes running to 39
	TEST_ASSERT_EQUAL_INT(39, runningTotal); //should have increased nodes running to 39
	running =30; running=30; //reset these to run new tests here
	state=3; //now needs to check times
	currentTime= 98; //6 hours before weekend cut off
	Job* fourth = new Job(dummy, 1, 16 * 10, 0, 4, 4);
	q->insertJob(fourth);
	results = fifo.fillReserved(running, runningTotal, q, state, 3, WEEKENDCUTOFF, currentTime, medMin, currentTime);
	TEST_ASSERT(results.size() == 1); //should have just taken the one job this time
	TEST_ASSERT(q.size()==1); //still one guy waiting in line
	TEST_ASSERT_EQUAL_INT(40, running); //should have increased nodes running to 36
	TEST_ASSERT_EQUAL_INT(40, runningTotal); //should have increased nodes running to 36
	
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_fillReserved);
    return UNITY_END();
}