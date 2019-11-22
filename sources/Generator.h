#pragma once

#include "users/User.h"
#include "Job.h"
#include <vector>

class Generator {
private:
    std::vector <User> users;

public:
    Generator();
    Job createJob();
    void check(Job* job);
    void lookForJobs();
};


