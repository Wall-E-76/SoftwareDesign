#pragma once

#include "User.h"
#include <utility>


struct Curriculum {
    double budget;
    int expoParameter;
    int instResourceCap;
    std::array<bool,5> permission;
};

class Student : public User {
private:
    int instResourceCap;

public:
    explicit Student(struct Curriculum curriculum);
    int getInstResourceCapt();
    bool spend(double newSpendings) override;
};


