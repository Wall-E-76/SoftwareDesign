#pragma once

#include "User.h"

struct Group {
    double budget;
    int expoParameter;
    std::array<bool,5> permission;
};

class Researcher : public User {
private:
    double grant;
public:
    Researcher(struct Group group, double grant);
    char whatAmI() override;
};

