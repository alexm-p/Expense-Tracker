// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2119504>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "date.h"
#include "lib_json.hpp"

#include <ctime>
#include <sstream>
#include <ostream>
#include <iomanip>

/**
 * @brief Default constructor that initializes the date to the current system date.
 *
 * Uses the C standard library to obtain the current time and sets the
 * year, month, and day accordingly.
 */
Date::Date() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    year = now->tm_year + 1900;
    month = now->tm_mon + 1;
    day = now->tm_mday;
}

/**
 * @brief Constructs a Date object with a specific year, month, and day.
 *
 * Validates the provided date values and throws an exception if the date is invalid.
 *
 * @param y Year component of the date.
 * @param m Month component of the date.
 * @param d Day component of the date.
 * @throws std::invalid_argument if the provided date is not valid.
 */
Date::Date(unsigned int y, unsigned int m, unsigned int d) {
    if (!isValidDate(y, m, d)) {
        throw std::invalid_argument("Invalid date");
    }
    year = y;
    month = m;
    day = d;
}

/**
 * @brief Constructs a Date object from a string in the format "YYYY-MM-DD".
 *
 * Parses the string to extract year, month, and day components, validates the date,
 * and initializes the Date object. Throws an exception if the format or values are invalid.
 *
 * @param dateString A string representing the date in "YYYY-MM-DD" format.
 * @throws std::invalid_argument if the date format is incorrect or the date is invalid.
 */
Date::Date(const std::string& dateString) {
    if (dateString.length() != 10 || dateString[4] != '-' || dateString[7] != '-') {
        throw std::invalid_argument("Invalid date format");
    }
    try {
        year = std::stoi(dateString.substr(0, 4));
        month = std::stoi(dateString.substr(5, 2));
        day = std::stoi(dateString.substr(8, 2));
        if (!isValidDate(year, month, day)) {
            throw std::invalid_argument("Invalid date");
        }
    } catch (const std::exception&) {
        throw std::invalid_argument("Invalid date format");
    }
}

/**
 * @brief Returns the date as a string in "YYYY-MM-DD" format.
 *
 * Uses string stream formatting to ensure that year, month, and day are zero-padded as needed.
 *
 * @return std::string The formatted date string.
 */
std::string Date::str() const {
    std::ostringstream os;
    os << std::setfill('0') << std::setw(4) << year << '-'
       << std::setw(2) << month << '-' << std::setw(2) << day;
    return os.str();
}

/**
 * @brief Sets the date to new values after validating them.
 *
 * Updates the year, month, and day if the provided values form a valid date.
 * Throws an exception if the date is not valid.
 *
 * @param y New year component.
 * @param m New month component.
 * @param d New day component.
 * @throws std::invalid_argument if the provided date is invalid.
 */
void Date::setDate(unsigned int y, unsigned int m, unsigned int d) {
    if (!isValidDate(y, m, d)) {
        throw std::invalid_argument("Invalid date");
    }
    year = y;
    month = m;
    day = d;
}

/**
 * @brief Gets the year component of the date.
 *
 * @return unsigned int The year value.
 */
unsigned int Date::getYear() const {
    return year;
}

/**
 * @brief Gets the month component of the date.
 *
 * @return unsigned int The month value.
 */
unsigned int Date::getMonth() const {
    return month;
}

/**
 * @brief Gets the day component of the date.
 *
 * @return unsigned int The day value.
 */
unsigned int Date::getDay() const {
    return day;
}

/**
 * @brief Compares this Date object with another for equality.
 *
 * Two Date objects are equal if their year, month, and day values match.
 *
 * @param other The Date object to compare against.
 * @return true if both dates are equal, false otherwise.
 */
bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day;
}

/**
 * @brief Compares this Date object with another to determine if it precedes the other.
 *
 * Comparison is done lexicographically: first by year, then month, and finally day.
 *
 * @param other The Date object to compare against.
 * @return true if this date is earlier than the other, false otherwise.
 */
bool Date::operator<(const Date& other) const {
    if (year < other.year) return true;
    if (year > other.year) return false;
    if (month < other.month) return true;
    if (month > other.month) return false;
    return day < other.day;
}

/**
 * @brief Validates whether the provided year, month, and day form a valid date.
 *
 * Checks for valid ranges in year, month, and day, and ensures that the day value
 * does not exceed the maximum days allowed for the given month.
 *
 * @param y Year component.
 * @param m Month component.
 * @param d Day component.
 * @return true if the date is valid, false otherwise.
 */
bool Date::isValidDate(unsigned int y, unsigned int m, unsigned int d) {
    if (y < 1 || m < 1 || m > 12 || d < 1) return false;
    unsigned int daysInMonth = getDaysInMonth(y, m);
    return d <= daysInMonth;
}

/**
 * @brief Returns the number of days in a given month for a specified year.
 *
 * Accounts for leap years when determining the number of days in February.
 *
 * @param y Year component.
 * @param m Month component.
 * @return unsigned int Number of days in the specified month.
 */
unsigned int Date::getDaysInMonth(unsigned int y, unsigned int m) {
    if (m == 2) return isLeapYear(y) ? 29 : 28;
    else if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    else return 31;
}

/**
 * @brief Determines whether a given year is a leap year.
 *
 * A leap year is divisible by 4 but not by 100, unless it is also divisible by 400.
 *
 * @param y The year to check.
 * @return true if the year is a leap year, false otherwise.
 */
bool Date::isLeapYear(unsigned int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}
