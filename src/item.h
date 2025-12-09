// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2119504>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// An Item class contains multiple 'tags' (e.g., a tag might be 'home' and
// another tag could be 'uni'). An Item also has a description (e.g. 'Costa
// Coffee'), a double amount (e.g. 2.55), and date associated with it. 
// -----------------------------------------------------

#ifndef ITEM_H
#define ITEM_H

#include "date.h"
#include <string>
#include <vector>
#include <stdexcept>


class Item 
{
private:
        std::string identifier;
        std::string description;
        double amount;
        Date date;
        //std::set<std::string> tags; 
        std::vector<std::string> tags;
public:

    Item(const std::string& id, const std::string& desc, double amt, const Date& d);

    std::string getIdent() const;
    std::string getDescription() const;

    void setDescription(const std::string& desc);

    const std::vector<std::string>& getTags() const; //
    bool addTag(const std::string& tag);
    bool deleteTag(const std::string& tag);
    unsigned int numTags() const;
    bool containsTag(const std::string& tag) const;

    double getAmount() const;
    void setAmount(double amt);
    Date getDate() const;
    void setDate(const Date& d);

    bool operator==(const Item& other) const;

    std::string str() const;
};

#endif // ITEM_H
