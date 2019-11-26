
#include "Student.h"


Student::Student(struct Curriculum curriculum) :
        User(curriculum.expoParameter, curriculum.budget, curriculum.permission),
        instResourceCap(curriculum.instResourceCap)
        {
}

char Student::whatAmI() {
    return 'S';
}

int Student::getInstResourceCapt() {
    return (*this).instResourceCap;
}

bool Student::spend(double newSpendings) {
    if ((*this).spendings+newSpendings < (*this).budget){
        (*this).spendings += newSpendings;
        return true;
    }
    return false;
}

