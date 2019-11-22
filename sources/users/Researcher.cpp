
#include "Researcher.h"

Researcher::Researcher(struct Group group, int grant) {
    (*this).grant = grant;
    (*this).expoParameter = group.expoParameter;
    (*this).budget = group.budget;
    (*this).spendings = 0;
    (*this).nextJobTime = 0;
    (*this).permission = {group.permission[0],group.permission[1],group.permission[2],group.permission[3],group.permission[4]};
}

char Researcher::whatAmI() {
    return 'R';
}



