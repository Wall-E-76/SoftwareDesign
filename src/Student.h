/*! \file

\class Student

\brief Inherited from User Class.

  Holds all the information for a Student type User. Inlcudes instant resource cap.
  \sa User
*/
#pragma once

#include "User.h"
#include <utility>


/// \brief Student Curriculum data structure
struct Curriculum {
	/// \brief machine-hours available to Student in this Curriculum
    double budget;
	/// \brief parameter for exponential distribution probability function that determies the frequency of Job submissions for Student in this Curriculum.
    int expoParameter;
	/// \brief machine-hour limit of single Job request Student in this Curriculum can make.
    int instResourceCap;
	/// \brief Queue permissions for Student in this Curriculum
    std::array<bool,5> permission;
};

class Student : public User {
private:
	/// \brief machine-hour limit of single Job request.
    int instResourceCap;

public:
    explicit Student(struct Curriculum curriculum);
	/// \brief returns instResourceCap of Student.
    int getInstResourceCapt();
	/// \brief verifies that the "newSpendings" of a Job request will not push the Student's total spendings over thier budget. Also ensures that "newSpendings" does not exceed instResouceCap. If it passes both cases, "newSpendings" is added to the User spendings and method returns "true". Otherwise, returns "false".
    bool spend(double newSpendings) override;
};


