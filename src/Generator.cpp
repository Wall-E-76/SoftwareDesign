
#include "Generator.h"
#include <random>
#include <src/Researcher.h>


Generator::Generator(int totlNodes) {
	struct PropertyQueue shortQueue {};
	shortQueue.nodeMax = SHORTMAXNODES;
	shortQueue.nodeMinExclusive = 0;
	shortQueue.timeMax = 1;
	struct PropertyQueue medQueue {};
	medQueue.nodeMax = MEDIUMMAXNODES;
	medQueue.nodeMinExclusive = SHORTMAXNODES;
	medQueue.timeMax = 8;
	struct PropertyQueue largeQueue {};
	largeQueue.nodeMax = LARGEMAXNODES;
	largeQueue.nodeMinExclusive = MEDIUMMAXNODES;
	largeQueue.timeMax = 16;
	struct PropertyQueue GPUQueue {};
	GPUQueue.nodeMax = GPUMAXNODES;
	GPUQueue.nodeMinExclusive = 0;
	GPUQueue.timeMax = 8;
	struct PropertyQueue hugeQueue {};
	hugeQueue.nodeMax = HUGEMAXNODES;
	hugeQueue.nodeMinExclusive = 15; //lets say Huge jobs cant run jobs  on fewer than 16 nodes
	hugeQueue.timeMax = 64;

	(*this).property = { shortQueue, medQueue, largeQueue, GPUQueue, hugeQueue };
}

Generator::Generator(): Generator(128) {
}

std::vector<User *> Generator::getUsers() {
    return (*this).users;
}

std::array<PropertyQueue,5> Generator::getProperty() {
    return (*this).property;
}

std::array<Queue *, 5> Generator::getQueues() {
    return (*this).queues;
}

void Generator::addUser(User *user) {
    (*this).users.push_back(user);
}

void Generator::addQueues(std::array<Queue*,5> queues) {
    (*this).queues = queues;
}


int Generator::randomCategory(int i) {
    int sum=0;
    // We find the number of possible category
    std::array<bool,5> permission = (*this).users.at(i)->getPermission();
    for (int j = 0; j<5; j++){
        if(permission.at(j)) sum++;
    }
    // Among the possible categories, we choose one randomly
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(1,sum);

    int random_integer = uni(rng);

    //We translate the random number into the real category number
    int category = -1;
    while (random_integer>0){
        if (permission.at(category+1)) {
            random_integer--;
        }
        category++;
    }
    return category;
}

Job* Generator::createJob(int i) {
    User *owner;
    owner = (*this).users.at(i);
    int category = (*this).randomCategory(i);
    bool GPU = false;
    if (category == 3)
        GPU = true;
    std::random_device rd{};
    std::mt19937 generator{rd()};
    int cores;
    int coreMax = (*this).property.at(category).nodeMax*16;
	int coreMin = (*this).property.at(category).nodeMinExclusive * 16;
	coreMin++; //so now it will need to use mininum the # of nodes above the specficied nodeMinExclusive
  
    std::normal_distribution<double> norm((coreMax+coreMin)/2, (coreMax - coreMin) / 2);
    cores = floor(norm(generator));
    
    if (cores>coreMax)
        cores = coreMax;
    else if (cores<coreMin)
        cores = coreMin;
    double reservedTime;
    double timeMax = (*this).property.at(category).timeMax;
    std::normal_distribution<double> normTime(timeMax/2);
    reservedTime = roundUp(normTime(generator));
    if (reservedTime>timeMax)
        reservedTime = timeMax;
    else if (reservedTime<2*TIMESTEP)
        reservedTime=2*TIMESTEP;
    double runtime;
    std::normal_distribution<double> normRuntime(3*reservedTime/4,reservedTime/4);
   runtime = roundUp(normRuntime(generator));
    if (runtime>reservedTime)
        runtime = reservedTime;
    else if (runtime<TIMESTEP)
        runtime=TIMESTEP;
    Job* job = new Job(owner, category, cores, GPU, runtime, reservedTime);
    return job;
}

void Generator::check(Job *job, double currentTime) {
    double priceJob;
    if (job->getCategory()==3)
        priceJob = job->getRuntime()*MACHINE_COST_GPU*job->getNodes();
    else
        priceJob = job->getRuntime()*MACHINE_COST*job->getNodes();
    double newSpending = job->getOwner()->getSpendings()+priceJob;
    if (job->getOwner()->spend(newSpending)) {
        (*this).queues.at(job->getCategory())->insertJob(job);
        job->getOwner()->generateNewTime(currentTime);
    }
   else {
        delete job;
    }
}

void Generator::lookForJobs(double currentTime) {
    int n = (*this).users.size();
    for (int i=0; i<n;i++) {
        if ((*this).users.at(i)->isTime(currentTime)) {
            Job* newJob = (*this).createJob(i);
            (*this).check(newJob, currentTime);
        }
    }
}

double Generator::roundUp(double time){
    double a = time - floor(time);
    double b = floor(a/TIMESTEP);
    double c = a - b;
    double roundUp = time - a+ b*TIMESTEP;
    if (c >= TIMESTEP/2){
        roundUp += TIMESTEP;
    }
    return roundUp;
}











