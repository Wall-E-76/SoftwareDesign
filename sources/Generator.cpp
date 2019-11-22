
#include "Generator.h"
#include <random>

Generator::Generator() {
     //TODO convert input into generator data
}

void Generator::addQueue(std::array<Queue, 5> &queues) {
    (*this).queues = queues;
}

int Generator::randomCategory(int i) {
    int sum;
    // We find the number of possible category
    std::array<bool,5> permission = (*this).users.at(i).getPermission();
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
    owner = &(*this).users.at(i);
    int category = (*this).randomCategory(i);
    bool GPU = false;
    if (category == 3)
        GPU = true;
    std::random_device rd{};
    std::mt19937 generator{rd()};
    int cores;
    int coreMax = (*this).property.at(category).nodeMax*16;
    if (GPU){
        std::normal_distribution<double> norm(128/2);
        cores = floor(norm(generator));
    }
    else {
        std::normal_distribution<double> norm(coreMax/2);
        cores = floor(norm(generator));
    }
    if (cores>coreMax)
        cores = coreMax;
    else if (cores<1)
        cores = 1;
    double runtime;
    double timeMax = (*this).property.at(category).timeMax;
    std::uniform_int_distribution<int> norm(timeMax/2);
    runtime = norm(generator);
    if (runtime>timeMax)
        runtime = timeMax;
    else if (runtime<0.1) // ???? what value to put? (ideally the smallest time step) i'm assuming the time step is in hour
        runtime=0.1;
    return {owner, category, cores, GPU, runtime};

}

void Generator::check(Job *job) {
    double priceJob;
    if (job->getCategory()==3)
        priceJob = job->getRuntime()*MACHINE_COST_GPU*job->getCores();
    else
        priceJob = job->getRuntime()*MACHINE_COST*job->getCores();
    double newSpending = job->getOwner()->getSpendings()+priceJob;
    if (newSpending < job->getOwner()->getBudget()){
        job->getOwner()->spend(newSpending);
        (*this).queues.at(job->getCategory());
    }
}

void Generator::lookForJobs(int currentTime) {
    int n = (*this).users.size();
    for (int i=0; i<n;i++) {
        if ((*this).users.at(i).isTime(currentTime)) {
            (*this).users.at(i).generateNewTime();
            Job newJob = createJob(i);
            check(&newJob);
        }
    }
}





