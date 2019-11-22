
#include "User.h"

bool User::isTime(double time) {
    return ((*this).nextJobTime-time>0);
}

int User::getBudget() {
    return (*this).budget;
}

int User::getSpendings() {
    return (*this).spendings;
}

bool User::spend(int newSpendings) {
    if ((*this).spendings+newSpendings < (*this).budget){
        (*this).spendings += newSpendings;
        return true;
    }
    return false;
}
