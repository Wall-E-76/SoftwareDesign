#pragma once
#include <array>


class User {
protected:
    int expoParameter;
    double nextJobTime;
    double budget;
    double spendings;
    // Permission are : short, medium, large, gpu, huge
    std::array<bool,5> permission;

public:
    User(int expoParameter, double budget, std::array<bool,5> permission);
    bool isTime(double time);
    double generateNewTime();
    virtual char whatAmI()=0;
    double getBudget();
    double getSpendings();
    bool spend(double newSpendings);
    std::array<bool,5> getPermission();
};



