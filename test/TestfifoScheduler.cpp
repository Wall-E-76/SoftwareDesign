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


void test_oldestCheck(void) {
	FIFOScheduler fifo;
	struct Curriculum curr {};
	curr.budget = 1000; curr.instResourceCap = 1000; curr.permission = { 0,1,0,0,0 }; curr.expoParameter = 10;
	User* dummy = new Student(curr);
	std::array<Queue*, 5> qs;
	for (int i = 0; i < 5; i++) {
		qs[i] = new Queue();
	}
	double t = 94; //10 hours out from weekend
	Job* short1 = new Job(dummy, 0, 16, 0, 1, 1);
	short1->setTimeEnteredQueue(93);
	//Job* med1 = new Job(dummy, 1, 16*4, 0, 8, 8);
	//med1->setTimeEnteredQueue(92);
	Job* lrg1 = new Job(dummy, 2, 16 * 40, 0, 16, 16);
	lrg1->setTimeEnteredQueue(84);
	Job* lrg2 = new Job(dummy, 2, 16 * 40, 0, 10, 10);
	lrg2->setTimeEnteredQueue(88);
	qs[0]->insertJob(short1, t); 
	//qs[1]->insertJob(med1, t); 
	qs[2]->insertJob(lrg1, t); qs[2]->insertJob(lrg2, t);
	
	double oldestTime = MAX_DOUBLE; //oldest time of next jobs in line, initialized to unreachable value
	int oldest = 3; //queues index of oldest job, initialized to unreachable value
	int nShort = 0; int nMedium = 0; int nLarge = 0;
	int state = 2; //need to check large queue for reserved times
	Job* temp;

	temp = fifo.oldestCheck(oldest, oldestTime, nShort, state, 4, WEEKENDCUTOFF, 0, t);
	TEST_ASSERT(qs[0]->getJobsInQueue().size() == 0); //should be no jobs left in this queue;
	TEST_ASSERT(oldest == 0);
	TEST_ASSERT(oldestTime == 93); //this is the time the one job entered the queue
	TEST_ASSERT(nShort == 0); //should be 0, index of first job in queue
	temp = fifo.oldestCheck(oldest, oldestTime, nMedium, state, 3, WEEKENDCUTOFF, 1, t);
	TEST_ASSERT(qs[1]->getJobsInQueue().size() == 0); //should be no jobs in this queue
	TEST_ASSERT(oldest == 0); //should still be unchanged because no jobs in this queue
	TEST_ASSERT(oldestTime == 93); //this is the time the one job entered the queue
	TEST_ASSERT(nMed == 0); //should be unchanged
	temp = fifo.oldestCheck(oldest, oldestTime, nLarge, state, 2, WEEKENDCUTOFF, 2, t);
	TEST_ASSERT(qs[2]->getJobsInQueue().size() == 1); //should have one left in queue
	TEST_ASSERT(oldest == 2); //should now be considered queue with oldest job
	TEST_ASSERT(oldestTime == 88); //should be the time the second job in line entered the queue
	TEST_ASSERT(nLarge == 1); //should be index of second job in queue

}

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
	double currentTime = 70; //well before weekend cutoff
	q->insertJob(first, currentTime);
	q->insertJob(second, currentTime);
	q->insertJob(third, currentTime);
	std::vector<Job*> results; //our return vector
	int state = 2; //start of in a state where there is no need to check time
	results = fifo.fillReserved(running, runningTotal, q, state, 3, WEEKENDCUTOFF, currentTime, medMin, currentTime);
	TEST_ASSERT(results.size() == 2); //should only have taken first two jobs
	TEST_ASSERT(q.getJobsInQueue().size()==1); //still one guy waiting in line
	TEST_ASSERT_EQUAL_INT(39, running); //should have increased nodes running to 39
	TEST_ASSERT_EQUAL_INT(39, runningTotal); //should have increased nodes running to 39
	running =30; runningTotal=30; //reset these to run new tests here
	state=3; //now needs to check times
	currentTime= 98; //6 hours before weekend cut off
	Job* fourth = new Job(dummy, 1, 16 * 10, 0, 4, 4);
	q->insertJob(fourth, currentTime);
	results = fifo.fillReserved(running, runningTotal, q, state, 3, WEEKENDCUTOFF, currentTime, medMin, currentTime);
	TEST_ASSERT(results.size() == 1); //should have just taken the one job this time
	TEST_ASSERT(q->getJobsInQueue().size()==1); //still one guy waiting in line
	TEST_ASSERT_EQUAL_INT(40, running); //should have increased nodes running to 36
	TEST_ASSERT_EQUAL_INT(40, runningTotal); //should have increased nodes running to 36
	
}


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_fillReserved);
    return UNITY_END();
}