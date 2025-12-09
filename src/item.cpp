// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2119504>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "item.h"
#include "lib_json.hpp"
#include <sstream>
#include <ostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

/**
 * @brief Constructs an Item object with the given identifier, description, amount, and date.
 *
 * Initializes the item with its unique identifier, a textual description, a monetary amount, and the associated date.
 *
 * @param id The unique identifier for the item.
 * @param desc A description of the item.
 * @param amt The monetary amount associated with the item.
 * @param d The date associated with the item.
 */
Item::Item(const std::string& id, const std::string& desc, double amt, const Date& d) 
    : identifier(id), description(desc), amount(amt), date(d) {}

/**
 * @brief Retrieves the identifier of the item.
 *
 * @return std::string The unique identifier of the item.
 */
std::string Item::getIdent() const {
    return identifier;
}

/**
 * @brief Retrieves the description of the item.
 *
 * @return std::string The description text of the item.
 */
std::string Item::getDescription() const {
    return description;
}

/**
 * @brief Updates the description of the item.
 *
 * Sets a new description for the item.
 *
 * @param desc The new description to be assigned to the item.
 */
void Item::setDescription(const std::string& desc) {
    description = desc;
}

/**
 * @brief Retrieves the tags associated with the item.
 *
 * Provides a constant reference to the vector containing all tags.
 *
 * @return const std::vector<std::string>& The container of tags.
 */
const std::vector<std::string>& Item::getTags() const {
    return tags;
}

/**
 * @brief Adds a new tag to the item.
 *
 * Inserts a new tag into the item’s tags container. If the tag already exists, the function returns false.
 *
 * @param tag The tag string to add.
 * @return true if the tag was inserted; false if the tag already existed.
 */
bool Item::addTag(const std::string& tag) {
    auto it = std::find(tags.begin(), tags.end(), tag);
    if (it != tags.end()) {
        return false;
    }
    tags.push_back(tag);
    return true;
}

/**
 * @brief Deletes a tag from the item.
 *
 * Searches for the specified tag in the container and deletes it if found.
 * Throws an exception if the tag is not present.
 *
 * @param tag The tag string to remove.
 * @return true if the tag was successfully deleted.
 * @throws std::out_of_range if the tag does not exist.
 */
bool Item::deleteTag(const std::string& tag) {
    auto it = std::find(tags.begin(), tags.end(), tag);
    if (it == tags.end()) {
        throw std::out_of_range("Tag not found");
    }
    tags.erase(it);
    return true;
}

/**
 * @brief Returns the number of tags associated with the item.
 *
 * @return unsigned int The count of tags.
 */
unsigned int Item::numTags() const {
    return tags.size();
}

/**
 * @brief Checks whether the item contains a specific tag.
 *
 * Searches the tags container for the specified tag.
 *
 * @param tag The tag string to check.
 * @return true if the tag exists in the item; false otherwise.
 */
bool Item::containsTag(const std::string& tag) const {
    return std::find(tags.begin(), tags.end(), tag) != tags.end();
}

/**
 * @brief Retrieves the monetary amount associated with the item.
 *
 * @return double The current amount of the item.
 */
double Item::getAmount() const {
    return amount;
}

/**
 * @brief Updates the monetary amount associated with the item.
 *
 * @param amt The new amount to be assigned.
 */
void Item::setAmount(double amt) {
    amount = amt;
}

/**
 * @brief Retrieves the date associated with the item.
 *
 * @return Date The date object of the item.
 */
Date Item::getDate() const {
    return date;
}

/**
 * @brief Updates the date associated with the item.
 *
 * @param d The new date to assign to the item.
 */
void Item::setDate(const Date& d) {
    date = d;
}

/**
 * @brief Equality operator overload for the Item class.
 *
 * Two Item objects are considered equal only if they have the same identifier, date,
 * amount, description, and tags.
 *
 * @param other The Item object to compare with.
 * @return true if both items are equal; false otherwise.
 */
bool Item::operator==(const Item& other) const { 
    return identifier == other.identifier && 
           date == other.date && 
           amount == other.amount && 
           description == other.description && 
           tags == other.tags;
}

/**
 * @brief Converts the Item object to its JSON representation.
 *
 * Constructs a JSON-formatted string containing the amount, date, description, and tags.
 * The amount is formatted with one decimal place if it is an exact integer.
 *
 * @return std::string The JSON string representing the item.
 */
std::string Item::str() const {
    std::ostringstream os;
    os << "{";
    os << "\"amount\":";
    
    // Check if 'amount' is an exact integer.
    if (std::floor(amount) == amount) {
        // If it's an integer, force one decimal place.
        os << std::fixed << std::setprecision(1) << amount;
    } else {
        // Otherwise, print normally.
        os << amount;
    }
    
    os << ",";
    os << "\"date\":\"" << date.str() << "\",";
    os << "\"description\":\"" << description << "\",";
    os << "\"tags\":[";
    for (auto it = tags.begin(); it != tags.end(); ++it) {
        os << "\"" << *it << "\"";
        if (std::next(it) != tags.end()) {
            os << ",";
        }
    }
    os << "]";
    os << "}";
    return os.str();
}
