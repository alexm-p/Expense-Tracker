// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2119504>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// An Date class that contains the following member variables
// - year
// - month
// - day
// -----------------------------------------------------

#ifndef DATE_H
#define DATE_H

#include <string>
#include <stdexcept>

class Date
{
private:
   unsigned int year;
   unsigned int month;
   unsigned int day;

   // Private static helper functions for date validation
   static bool isValidDate(unsigned int y, unsigned int m, unsigned int d);
   static unsigned int getDaysInMonth(unsigned int y, unsigned int m);
   static bool isLeapYear(unsigned int y);
public:
    Date();                         
    Date(unsigned int y, unsigned int m, unsigned int d);      
    Date(const std::string& dateString);

    void setDate(unsigned int y, unsigned int m, unsigned int d);
    unsigned int getYear() const;
    unsigned int getMonth() const;
    unsigned int getDay() const;
    
    std::string str() const;

    bool operator==(const Date& other) const;
    bool operator<(const Date& other) const;
};

#endif // DATE_H
