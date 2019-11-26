
#include "Student.h"
#include "User.cpp"

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


