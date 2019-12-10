/*! \file

\class User

\brief User class.

 The User class is an abstract class. Users are producers of requests. They are allowed to create only certain types of jobs, those permissions are defined at the creation of the user.
 Each User request leads to the creation of a job which characteristics fits the permissions.
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
    double getBudget();
    double getSpendings();
    int getExpoParameter();
    virtual bool spend(double newSpendings)=0;
    std::array<bool,5> getPermission();
};



