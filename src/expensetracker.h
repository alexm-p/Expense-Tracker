// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2119504>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// The root object that holds all data for 371expenses. This
// class contains Categories, which in turn hold Expense Items,
// which have a description, amount, and date
// -----------------------------------------------------

#ifndef EXPENSETRACKER_H
#define EXPENSETRACKER_H

#include "category.h"
#include <map>
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>


class ExpenseTracker {
private:
    std::map<std::string, Category> categories;

public:
    ExpenseTracker();
    unsigned int size() const;
    Category& newCategory(const std::string& id);
    bool addCategory(const Category& category);
    const Category& getCategory(const std::string& id) const;
    Category& getCategory(const std::string& id);
    bool deleteCategory(const std::string& id);
    double getSum() const;
    void load(const std::string& filename);
    void save(const std::string& filename) const;
    std::string str() const;

    bool operator==(const ExpenseTracker& other) const;
};

#endif // EXPENSETRACKER_H
