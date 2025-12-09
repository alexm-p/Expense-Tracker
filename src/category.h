// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2119504>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// A Category contains one or more Expense Items, each with
// their own identifier ('ident').
// -----------------------------------------------------

#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <map>
#include "item.h"
#include <stdexcept>

class Category  
{
private:
    std::string ident;
    std::map<std::string, Item> items;
public:
    Category(const std::string& id);

    unsigned int size() const;
    std::string getIdent() const;

    void setIdent(const std::string& id);

    Item& newItem(const std::string& id, const std::string& desc, double amt, const Date& d);

    bool addItem(const Item& item);

    const Item& getItem(const std::string& id) const;

    Item& getItem(const std::string& id);

    const std::map<std::string, Item>& getItems() const;

    double getSum() const;

    bool deleteItem(const std::string& id);

    bool operator==(const Category& other) const;

    std::string str() const;


};

#endif // CATEGORY_H
