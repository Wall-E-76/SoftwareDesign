
#include <random>
#include "User.h"

User::User(int expoParameter, double budget, std::array<bool,5> permission):
        expoParameter(expoParameter),
        nextJobTime(0),
        budget(budget),
        spendings(0),
        permission({permission[0], permission[1], permission[2], permission[3], permission[4]}){
}

bool User::isTime(double time) {
    return ((*this).nextJobTime-time>0);
}

double User::getBudget() {
    return (*this).budget;
}

double User::getSpendings() {
    return (*this).spendings;
}

bool User::spend(double newSpendings) {
    if ((*this).spendings+newSpendings < (*this).budget){
        (*this).spendings += newSpendings;
        return true;
    }
    return false;
}

double User::generateNewTime() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<> d((*this).expoParameter);
    return d(gen);
}

std::array<bool,5> User::getPermission() {
    return (*this).permission;
}


