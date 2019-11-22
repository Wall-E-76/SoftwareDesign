#pragma once

#include "User.h"
#include <utility>


class Student : public User {
private:
    int instResourceCap;

public:
    Student(std::pair <int,int>group);
    char whatAmI();
    int getInstResourceCapt();
};


