// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: Thomas Reitmaier
//         thomas.reitmaier@swansea.ac.uk
//         Martin Porcheron (adapted from)
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// Catch2 — https://github.com/catchorg/Catch2
// Catch2 is licensed under the BOOST license
// -----------------------------------------------------
// This file contains tests for the action program
// argument.
// -----------------------------------------------------
#ifndef TEST_H
#define TEST_H
#include "../src/date.h"

const int year = 2024;
const int month = 12;
const int day = 25;
const int day2 = 31;

const Date date = Date(year, month, day);
const Date date2 = Date(year, month, day2);

const std::string dateStr1 = "2024-12-25";
const std::string dateStr2 = "2024-12-31";

const std::string ident = "1";
const std::string description = "Test Description";
const double amount = 3.50;

const std::string ident2 = "2";
const std::string description2 = "Second Description";
const double amount2 = 3.99;

const std::string categoryIdent = "Category";

#endif // TEST_H