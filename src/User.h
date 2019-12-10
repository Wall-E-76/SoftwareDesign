/*! \file

\class User

\brief User class.

 The User class is an abstract class. Users are producers of requests. They are allowed to create only certain types of Jobs up to a certain buget of machine-hours,
those permissions are defined at the creation of the User. Users are initialized with a generated nextJobTime, and generate a new one ecah time they submit a Job to the Queue. 
*/

#pragma once
#include <array>

class User {
protected:
	/// \brief parameter used in the exponential probability distribution function that determines the frequency at which the User will generate new Job requests.
    int expoParameter;
	/// \brief the time in the simulation that the User will generate their next Job request.
    double nextJobTime;
	/// \brief the total machine-hours a User can spend in the course of the simulation.
    double budget;
	/// \brief the total machine-hours spent by the User already in the course of the simulation.
    double spendings;
    // Permission are : short, medium, large, gpu, huge
	/// \brief indexed permissions as to which Queues the User can submit Jobs to - "1" for has permission, "0" for does not have permission.
    std::array<bool,5> permission;

public:
    User(int expoParameter, double budget, std::array<bool,5> permission);
	/// \brief returns "true" if nextJobTime is less than or equal to the "time" parameter, "false" otherwise.
    bool isTime(double time);
	/// \brief generates a new time in the future that the User will request their next Job, adds this to current systemTime and sets it to nextJobTime.
    void generateNewTime(double time);
	/// \brief getter used in Unit testing - returns User's machine-hour budget permission.
    double getBudget();
	/// \brief getter used in Unit testing - returns User's current spendings. 
    double getSpendings();
	/// \brief getter used in Unit testing - returns User's expoParameter.
    int getExpoParameter();
	/// \brief virtual method - increments User's spendings.
    virtual bool spend(double newSpendings)=0;
	/// \brief getter used in Unit testing - returns User's permissions attribute. 
    std::array<bool,5> getPermission();
};



