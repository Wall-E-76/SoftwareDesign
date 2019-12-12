#include "Generator.h"
#include <random>
#include "Researcher.h"

#define THRESHOLD std::array<int,5> {700,700,15,650,3}


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

Generator::Generator() : Generator(128) {
}

std::vector<User*> Generator::getUsers() {
	return (*this).users;
}

std::array<PropertyQueue, 5> Generator::getProperty() {
	return (*this).property;
}

std::array<Queue*, 5> Generator::getQueues() {
	return (*this).queues;
}

void Generator::addUser(User* user) {
	(*this).users.push_back(user);
}

void Generator::addQueues(std::array<Queue*, 5> queues) {
	(*this).queues = queues;
}

int Generator::randomCategory(int i) {
	std::array<int,5> distribution = {0,0,0,0,0};
    std::array<bool, 5> permission = (*this).users.at(i)->getPermission();
	for (int j = 0; j<5;j++){
	    if (permission.at(j)){
	        if ((*this).getQueues()[j]->getSizeQueue()>THRESHOLD[j]){
                distribution[j] = 1;
            }
	        else{
                distribution[j] = 20;
            }
	    }
	}
	std::random_device rd;
	std::mt19937 gen(rd());
    std::discrete_distribution<> d(distribution.begin(), distribution.end());
    int category = d(gen);
	return category;
}

Job* Generator::createJob(int i) {
	User* owner;
	owner = (*this).users.at(i);
	int category = (*this).randomCategory(i);
	bool GPU = (category == 3);
	std::random_device rd{};
	std::mt19937 generator{ rd() };
	int cores;
	int coreMax = (*this).property.at(category).nodeMax * 16;
	int coreMin = (*this).property.at(category).nodeMinExclusive * 16;
	coreMin++;
	std::normal_distribution<double> norm((coreMax + coreMin) / 2, (coreMax - coreMin) / 2);
	cores = floor(norm(generator));
	if (cores > coreMax)
		cores = coreMax;
	else if (cores < coreMin)
		cores = coreMin;
	double reservedTime;
	double timeMax = (*this).property.at(category).timeMax;
	std::normal_distribution<double> normTime(timeMax / 2);
	reservedTime = roundUp(normTime(generator));
	if (reservedTime > timeMax)
		reservedTime = timeMax;
	else if (reservedTime < 2 * TIMESTEP)
		reservedTime = 2 * TIMESTEP;
	double runtime;
	std::normal_distribution<double> normRuntime(3 * reservedTime / 4, reservedTime / 4);
	runtime = roundUp(normRuntime(generator));
	if (runtime > reservedTime)
		runtime = reservedTime;
	else if (runtime < TIMESTEP)
		runtime = TIMESTEP;
	Job* job = new Job(owner, category, cores, GPU, runtime, reservedTime);
	return job;
}

void Generator::check(Job* job, double systemTime) {
	double priceJob;
	if (job->getCategory() == 3)
		priceJob = job->getRuntime() * MACHINE_COST_GPU * job->getNodes();
	else
		priceJob = job->getRuntime() * MACHINE_COST * job->getNodes();
	if (job->getOwner()->spend(priceJob)) {
		(*this).queues.at(job->getCategory())->insertJob(job, systemTime);
		job->getOwner()->generateNewTime(systemTime);
	}
	else {
		delete job;
	}
}

void Generator::lookForJobs(double systemTime) {
	int n = (*this).users.size();
	for (int i = 0; i < n; i++) {
		if ((*this).users.at(i)->isTime(systemTime)) {
			Job* newJob = (*this).createJob(i);
			(*this).check(newJob, systemTime);
		}
	}
}

double Generator::roundUp(double time) {
	double a = time - floor(time);
	double b = floor(a / TIMESTEP);
	double c = a - b;
	double roundUp = time - a + b * TIMESTEP;
	if (c >= TIMESTEP / 2) {
		roundUp += TIMESTEP;
	}
	return roundUp;
}