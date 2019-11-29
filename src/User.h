/*! \file

\class User

\brief User class.

!!!!!!!!!!!!!!!.........describe here......!!!!!!!!!!!!!!!!!!!
*/

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
    void generateNewTime(double time);
    virtual char whatAmI()=0;
    double getBudget();
    double getSpendings();
    virtual bool spend(double newSpendings)=0;
    std::array<bool,5> getPermission();
};



