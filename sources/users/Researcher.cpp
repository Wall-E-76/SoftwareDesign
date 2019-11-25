
#include "Researcher.h"

Researcher::Researcher(struct Group group, int grant) :
        User(group.expoParameter, group.budget, group.permission),
        grant(grant)
    {
}

char Researcher::whatAmI() {
    return 'R';
}



