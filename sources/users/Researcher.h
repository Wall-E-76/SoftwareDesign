#pragma once


#include "User.h"

struct Group {
    int budget;
    int expoParameter;
    std::array<bool,5> permission;
};

class Researcher : public User {
private:
    int grant;
public:
    Researcher(struct Group group, int grant);
    char whatAmI() override;
};

