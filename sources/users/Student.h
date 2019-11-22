#pragma once

#include "User.h"
#include <utility>


struct Curriculum {
    int budget;
    int expoParameter;
    int instResourceCap;
    bool permission[5];
};

class Student : public User {
private:
    int instResourceCap;

public:
    Student(struct Curriculum curriculum, int expoParameter);
    char whatAmI() override;
    int getInstResourceCapt();
};


