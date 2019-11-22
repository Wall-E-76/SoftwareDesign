
#include "Student.h"

Student::Student(struct Curriculum curriculum, int expoParameter) {
    (*this).expoParameter = curriculum.expoParameter;
    (*this).budget = curriculum.budget;
    (*this).spendings = 0;
    (*this).nextJobTime = 0;
    (*this).permission = {curriculum.permission[0],curriculum.permission[1],curriculum.permission[2],curriculum.permission[3],curriculum.permission[4]};
    (*this).instResourceCap = curriculum.instResourceCap;
}

char Student::whatAmI() {
    return 'S';
}

int Student::getInstResourceCapt() {
    return (*this).instResourceCap;
}


