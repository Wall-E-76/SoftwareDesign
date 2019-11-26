
#include "Generator.h"
#include <random>

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
	GPUQueue.timeMax = 8; //TODO change the value to a sensible one
	struct PropertyQueue hugeQueue {};
	hugeQueue.nodeMax = HUGEMAXNODES;
	hugeQueue.nodeMinExclusive = 15; //lets say Huge jobs cant run jobs  on fewer than 16 nodes
	hugeQueue.timeMax = 64; //TODO change the value to a sensible one

	(*this).property = { shortQueue, medQueue, largeQueue, GPUQueue, hugeQueue };
}

Generator::Generator() {
     Generator(128); //legal?
}


void Generator::addUser(User *user) {
    (*this).users.push_back(user);
}

int Generator::randomCategory(int i) {
    int sum=0;
    // We find the number of possible category
    std::array<bool,5> permission = (*this).users.at(i)->getPermission();
    for (int j = 0; j<5; j++){
        if(permission.at(i)) sum++;
    }
    // Among the possible categories, we choose one randomly
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(1,sum);

    int random_integer = uni(rng);

    //We translate the random number into the real category number
    int category = -1;
    while (random_integer>0){
        if (permission.at(category)) {
            random_integer--;
        }
        category++;
    }
    return category;
}

Job Generator::createJob(int i) {
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
  
    std::normal_distribution<double> norm((coreMax/2)-coreMin);
    cores = floor(norm(generator));
    
    if (cores>coreMax)
        cores = coreMax;
    else if (cores<1)
        cores = 1;
    double reservedTime;
    double timeMax = (*this).property.at(category).timeMax;
    std::normal_distribution<double> norm(timeMax/2);
    reservedTime = roundUp(norm(generator));
    if (reservedTime>timeMax)
        reservedTime = timeMax;
    else if (reservedTime<2*TIMESTEP)
        reservedTime=2*TIMESTEP;
    double runtime;
    std::normal_distribution<double> normRuntime(3*reservedTime/4,reservedTime/4);
   runtime = roundUp(normRuntime(generator));
    if (runtime>timeMax)
        runtime = timeMax;
    else if (runtime<TIMESTEP)
        runtime=TIMESTEP;
    return {owner, category, cores, GPU, runtime, reservedTime};
}

void Generator::check(Job *job) {
    double priceJob;
    if (job->getCategory()==3)
        priceJob = job->getRuntime()*MACHINE_COST_GPU*job->getNodes();
    else
        priceJob = job->getRuntime()*MACHINE_COST*job->getNodes();
    double newSpending = job->getOwner()->getSpendings()+priceJob;
    if (newSpending < job->getOwner()->getBudget()){
        job->getOwner()->spend(newSpending);
        (*this).queues.at(job->getCategory());
    }
}

void Generator::lookForJobs(double currentTime) {
    int n = (*this).users.size();
    for (int i=0; i<n;i++) {
        if ((*this).users.at(i)->isTime(currentTime)) {
            (*this).users.at(i)->generateNewTime();
            Job newJob = createJob(i);
            check(&newJob);
        }
    }
}

double Generator::roundUp(double time){
    double a = time - floor(time);
    double b = floor(a/TIMESTEP);
    double c = a - b;
    double roundUp =  a+ b*TIMESTEP;
    if (c > TIMESTEP/2){
        roundUp += TIMESTEP;
    }
    return roundUp;
}







