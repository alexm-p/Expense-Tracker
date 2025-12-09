// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2119504>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "category.h"
#include "lib_json.hpp"
#include <sstream>
#include <ostream>

/**
 * @brief Constructs a new Category object with the given identifier.
 * 
 * @param id The identifier for the category.
 */
Category::Category(const std::string& id) : ident(id) {}

/**
 * @brief Returns the number of items in the category.
 * 
 * @return unsigned int The size (number of items) contained in the category.
 */
unsigned int Category::size() const {
    return items.size();
}

/**
 * @brief Gets the identifier of the category.
 * 
 * @return std::string The current category identifier.
 */
std::string Category::getIdent() const {
    return ident;
}

/**
 * @brief Sets a new identifier for the category.
 * 
 * @param id The new identifier to assign to the category.
 */
void Category::setIdent(const std::string& id) {
    ident = id;
}

/**
 * @brief Adds a new item to the category or updates an existing one.
 * 
 * If an item with the same identifier already exists, its description, amount, and date are updated.
 * 
 * @param id The identifier for the new or existing item.
 * @param desc The description for the item.
 * @param amt The amount associated with the item.
 * @param d The date associated with the item.
 * @return Item& Reference to the newly inserted or updated item.
 * @throws std::runtime_error If the item cannot be inserted.
 */
Item& Category::newItem(const std::string& id, const std::string& desc, double amt, const Date& d) {
    try {
        Item newItem(id, desc, amt, d);
        auto result = items.insert(std::make_pair(id, newItem));
        if (!result.second) {
            // If key already exists, overwrite the value
            result.first->second = newItem;
        }
        return result.first->second;
    } catch (...) {
        throw std::runtime_error("Failed to insert item");
    }
}

/**
 * @brief Adds an item to the category, merging data if the item already exists.
 * 
 * If the item is already present in the category, the function updates the existing item's description, amount,
 * date, and merges its tags with those of the new item. Otherwise, the item is inserted as a new entry.
 * 
 * @param item The item to be added.
 * @return true if the item was inserted as new, false if the existing item was updated.
 */
bool Category::addItem(const Item& item) {
    auto it = items.find(item.getIdent());
    if (it != items.end()) {
        // Item already exists, merge tags and update description, amount, and date
        for (const auto& tag : item.getTags()) {
            it->second.addTag(tag);
        }
        it->second.setDescription(item.getDescription());
        it->second.setAmount(item.getAmount());
        it->second.setDate(item.getDate());
        return false;
    } else {
        // Item does not exist, insert it
        items.insert({item.getIdent(), item});
        return true;
    }
}

/**
 * @brief Retrieves a reference to an item by its identifier.
 * 
 * Searches for the item with the given identifier in the category.
 * 
 * @param id The identifier of the item to retrieve.
 * @return Item& Reference to the found item.
 * @throws std::out_of_range If the item is not found.
 */
Item& Category::getItem(const std::string& id) {
    auto it = items.find(id);
    if (it != items.end()) {
        return it->second;
    } else {
        throw std::out_of_range("Item not found");
    }
}

/**
 * @brief Retrieves a constant reference to an item by its identifier.
 * 
 * Searches for the item with the given identifier in the category (read-only access).
 * 
 * @param id The identifier of the item to retrieve.
 * @return const Item& Const reference to the found item.
 * @throws std::out_of_range If the item is not found.
 */
const Item& Category::getItem(const std::string& id) const {
    auto it = items.find(id);
    if (it != items.end()) {
        return it->second;
    } else {
        throw std::out_of_range("Item not found");
    }
}

/**
 * @brief Computes the sum of the amounts of all items in the category.
 * 
 * Iterates through each item in the category and accumulates the total amount.
 * 
 * @return double The total sum of all item amounts.
 */
double Category::getSum() const {
    double sum = 0.0;
    for (const auto& pair : items) {
        sum += pair.second.getAmount();
    }
    return sum;
}

/**
 * @brief Deletes an item from the category by its identifier.
 * 
 * Searches for the item by its identifier and removes it from the category.
 * 
 * @param id The identifier of the item to delete.
 * @return true if the item was successfully found and deleted.
 * @throws std::out_of_range If the item is not found.
 */
bool Category::deleteItem(const std::string& id) {
    auto it = items.find(id);
    if (it != items.end()) {
        items.erase(it);
        return true;
    } else {
        throw std::out_of_range("Item not found");
    }
}

/**
 * @brief Equality operator for the Category class.
 * 
 * Two Category objects are considered equal only if they have the same identifier and contain the same items.
 * 
 * @param other The Category object to compare against.
 * @return true if both categories have the same identifier and items, false otherwise.
 */
bool Category::operator==(const Category& other) const {
    return ident == other.ident && items == other.items;
}

/**
 * @brief Converts the category data into a JSON-formatted string.
 * 
 * Constructs a JSON string where each key is the item identifier and the corresponding value is the 
 * JSON representation of that item, as provided by the item's str() function.
 * 
 * @return std::string The JSON representation of the category.
 */
std::string Category::str() const {
    std::ostringstream os;
    os << "{";
    size_t count = 0;
    for (const auto& pair : items) {
        if (count > 0) {
            os << ",";
        }
        os << "\"" << pair.first << "\":" << pair.second.str();
        count++;
    }
    os << "}";
    return os.str();
}

/**
 * @brief Retrieves a constant reference to the internal map of items.
 * 
 * Provides access to the complete map of items within the category. This is useful for operations 
 * that need to iterate over or inspect all items.
 * 
 * @return const std::map<std::string, Item>& A constant reference to the map of items.
 */
const std::map<std::string, Item>& Category::getItems() const {
    return items;
}
