
#include "MockScheduler.h"

MockScheduler::MockScheduler() : Scheduler(){}

std::vector<Job*> MockScheduler::getJobs(int status, std::array <int,5> &running, int &runningTotal, double currentTime){
    std::vector<Job*> nextJobs;
    for (int i =0; i<5;i++){
        while ((*this).queues[i]->nextJob()!=nullptr){
            nextJobs.push_back((*this).queues[i]->nextJob());
            running[(*this).queues[i]->nextJob()->getCategory()] += (*this).queues[i]->nextJob()->getNodes();
            runningTotal += (*this).queues[i]->nextJob()->getNodes();
            (*this).queues[i]->removeJob(0,0);


        }
    }
    return nextJobs;
}