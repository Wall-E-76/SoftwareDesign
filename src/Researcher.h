/*! \file

\class Researcher

\brief Inherited from User Class.

  Holds all the information for a Researcher type User.
  \sa User
*/
#pragma once

#include "User.h"

/// \brief Researcher Group data structure
struct Group {
	/// \brief machine-hours available to Researcher in this Group.
	double budget;
	/// \brief parameter for exponential distribution probability function that determies the frequency of Job submissions for Researcher in this Group.
	int expoParameter;
	/// \brief Queue permissions for Researcher in this Group.
	std::array<bool, 5> permission;
};

class Researcher : public User {
private:
	/// \brief endowment of extra machine-hours granted to specific Researcher.
    double grant;
public:
    Researcher(struct Group group, double grant);
	/// \brief getter used in Unit testing - returns grant of User.
    double getGrant();
	/// \brief verifies that the "newSpendings" of a Job request will not push the Researchers's total spendings over thier budget + possible grant. If it passes this case, "newSpendings" is added to the User spendings and method returns "true". Otherwise, returns "false".
    bool spend(double newSpendings) override ;
};

