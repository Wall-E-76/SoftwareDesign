
#include "Researcher.h"

Researcher::Researcher(struct Group group, double grant) :
        User(group.expoParameter, group.budget, group.permission),
        grant(grant)
    {
}

double Researcher::getGrant() {
    return (*this).grant;
}

bool Researcher::spend(double newSpendings) {
    if ((*this).spendings+newSpendings < ((*this).budget)+(*this).grant){
        (*this).spendings += newSpendings;
        return true;
    }
    return false;
}

