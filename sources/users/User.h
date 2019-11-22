#pragma once


class User {
private:
    int expoParameter;
    double nextJobTime;
    int budget;
    int spendings;

public:
    bool isTime(double time);
    double generateNewTime();
    virtual char whatAmI()=0;
    int getBudget();
    int getSpendings();
    bool spend(int newSpendings);
};

