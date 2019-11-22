#pragma once
#include <array>


class User {
protected:
    int expoParameter;
    double nextJobTime;
    int budget;
    int spendings;
    std::array<bool,5> permission;

public:
    bool isTime(double time);
    double generateNewTime();
    virtual char whatAmI()=0;
    int getBudget();
    int getSpendings();
    bool spend(int newSpendings);
    std::array<bool,5> getPermission();
};



