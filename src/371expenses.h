// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2119504>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// This file contains declarations for the helper functions used for
// initialising and running 371expenses.
// -----------------------------------------------------

#ifndef _371EXPENSES_H
#define _371EXPENSES_H

#include <string>

#include "lib_cxxopts.hpp"
#include "expensetracker.h"

namespace App {

// TODO: Enter your student number here!
const std::string STUDENT_NUMBER = "2119504";

// Enums (short for enumerations) are similar to their Java implementation. It
// is a user-defined type, used to assign names to internal constants in code,
// instead of simply passing in integers/strings etc.
//
// For example, functions can take a value/constant from a specific enum and use
// it in a switch statement, doing different things
//
// As such, it is a useful way for us to specify information in both a machine
// and human-readable format.
//
// Unlike Java, enums in C++ only map to integer values. You can either let the
// compiler generate the values automatically, in which it allocates a unique
// integer (0-indexed). Or, you can set the value by giving the name followed by
// = <value> (e.g. CREATE=0).
//
// This enum specifies the five different values we support in the action
// program argument.
enum Action { CREATE, SUM, JSON, DELETE, UPDATE };

int run(int argc, char *argv[]);

cxxopts::Options cxxoptsSetup();

App::Action parseActionArgument(cxxopts::ParseResult &args);

std::string getJSON(ExpenseTracker &et);
std::string getJSON(ExpenseTracker &et, const std::string &c);
std::string getJSON(ExpenseTracker &et, const std::string &c, const std::string &id);

} // namespace App

#endif // _371EXPENSES_H
