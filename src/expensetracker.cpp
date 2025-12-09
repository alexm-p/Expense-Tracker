// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2119504>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
#include "expensetracker.h"
#include "lib_json.hpp"
#include <fstream>
#include <sstream>
#include <utility>

/**
 * @brief Default constructor for ExpenseTracker.
 *
 * Initializes an empty ExpenseTracker object.
 */
ExpenseTracker::ExpenseTracker() {}

/**
 * @brief Returns the number of categories in the ExpenseTracker.
 *
 * @return unsigned int The count of categories stored.
 */
unsigned int ExpenseTracker::size() const {
    return categories.size();
}

/**
 * @brief Retrieves or creates a new Category with the given identifier.
 *
 * If a category with the specified identifier already exists, it returns the existing Category.
 * Otherwise, it creates a new Category, inserts it into the container, and returns it.
 *
 * @param id The identifier for the category.
 * @return Category& Reference to the newly created or existing Category.
 * @throws std::runtime_error if the Category cannot be inserted.
 */
Category& ExpenseTracker::newCategory(const std::string& id) {
    auto it = categories.find(id);
    if (it != categories.end()) {
        // If category already exists, return the existing one
        return it->second;
    } else {
        // If it doesn't exist, create a new one and insert it
        auto result = categories.insert(std::make_pair(id, Category(id)));
        if (!result.second) {
            throw std::runtime_error("Failed to insert category");
        }
        return result.first->second;
    }
}

/**
 * @brief Adds a Category object to the ExpenseTracker.
 *
 * If a category with the same identifier already exists, the function merges the items
 * from the provided category into the existing one (using Category::addItem) and returns false.
 * If the category does not exist, it is inserted into the container and the function returns true.
 *
 * @param category The Category object to add.
 * @return true if the category was inserted as new, false if merged.
 * @throws std::runtime_error if the Category cannot be inserted.
 */
bool ExpenseTracker::addCategory(const Category& category) {
    auto it = categories.find(category.getIdent());
    if (it != categories.end()) {
        // Merge items from the incoming category with the existing one
        for (const auto& pair : category.getItems()) {
            it->second.addItem(pair.second);
        }
        return false;
    } else {
        categories.insert(std::make_pair(category.getIdent(), category));
        return true;
    }
}

/**
 * @brief Retrieves a constant reference to a Category by its identifier.
 *
 * Searches the ExpenseTracker for a Category with the specified identifier.
 *
 * @param id The identifier of the desired Category.
 * @return const Category& A constant reference to the found Category.
 * @throws std::out_of_range if no Category with the specified identifier exists.
 */
const Category& ExpenseTracker::getCategory(const std::string& id) const {
    auto it = categories.find(id);
    if (it != categories.end()) {
        return it->second;
    } else {
        throw std::out_of_range("Category not found");
    }
}

/**
 * @brief Retrieves a mutable reference to a Category by its identifier.
 *
 * Searches the ExpenseTracker for a Category with the specified identifier.
 *
 * @param id The identifier of the desired Category.
 * @return Category& A mutable reference to the found Category.
 * @throws std::out_of_range if no Category with the specified identifier exists.
 */
Category& ExpenseTracker::getCategory(const std::string& id) {
    auto it = categories.find(id);
    if (it != categories.end()) {
        return it->second;
    } else {
        throw std::out_of_range("Category not found");
    }
}

/**
 * @brief Deletes a Category from the ExpenseTracker.
 *
 * Searches for a Category with the given identifier and removes it from the container.
 *
 * @param id The identifier of the Category to delete.
 * @return true if the Category was successfully deleted.
 * @throws std::out_of_range if no Category with the specified identifier exists.
 */
bool ExpenseTracker::deleteCategory(const std::string& id) {
    auto it = categories.find(id);
    if (it != categories.end()) {
        categories.erase(it);
        return true;
    } else {
        throw std::out_of_range("Category not found");
    }
}

/**
 * @brief Computes the total sum of all expenses across all categories.
 *
 * Iterates over each Category in the ExpenseTracker and sums the expense amounts of all items.
 *
 * @return double The total sum of all expense amounts.
 */
double ExpenseTracker::getSum() const {
    double sum = 0.0;
    for (const auto& pair : categories) {
        sum += pair.second.getSum();
    }
    return sum;
}

/**
 * @brief Loads ExpenseTracker data from a JSON file.
 *
 * Opens the specified file, reads its contents, and populates the ExpenseTracker
 * container with Category and Item objects based on the JSON structure. The expected JSON format is:
 * {
 *   "Category1": {
 *      "ItemID1": { "amount": ..., "date": "...", "description": "...", "tags": [...] },
 *      ...
 *   },
 *   "Category2": { ... }
 * }
 *
 * @param filename The path to the JSON file containing the database.
 * @throws std::runtime_error if the file cannot be opened.
 */
void ExpenseTracker::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("File not found: " + filename);
    }
    nlohmann::json j;
    file >> j;
    file.close();
    // Process each category in the JSON
    for (const auto& categoryJson : j.items()) {
        // Create a temporary Category object to hold the items
        Category tempCategory(categoryJson.key());
        
        // Add all items to the temporary category
        for (const auto& itemJson : categoryJson.value().items()) {
            Date d = Date(itemJson.value()["date"].get<std::string>());
            Item i(itemJson.key(), 
                   itemJson.value()["description"].get<std::string>(), 
                   itemJson.value()["amount"].get<double>(), 
                   d);
            // Add tags to the item
            for (const auto& tag : itemJson.value()["tags"]) {
                i.addTag(tag);
            }
            tempCategory.addItem(i);
        }
        addCategory(tempCategory);
    }
}

/**
 * @brief Saves the ExpenseTracker data to a JSON file.
 *
 * Serializes the ExpenseTracker object to a JSON-formatted string and writes it to the specified file.
 *
 * @param filename The path of the file to which the data will be written.
 * @throws std::runtime_error if the file cannot be opened.
 */
void ExpenseTracker::save(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("File not found: " + filename);
    }
    file << str();
    file.close();
}

/**
 * @brief Equality operator overload for the ExpenseTracker class.
 *
 * Two ExpenseTracker objects are considered equal if they have exactly the same categories and data.
 *
 * @param other The ExpenseTracker object to compare with.
 * @return true if both ExpenseTracker objects are equal; false otherwise.
 */
bool ExpenseTracker::operator==(const ExpenseTracker& other) const {
    return categories == other.categories;
}

/**
 * @brief Returns the JSON representation of the ExpenseTracker data.
 *
 * Constructs a JSON-formatted string representing all categories and their contained items.
 *
 * @return std::string The JSON string representation of the ExpenseTracker.
 */
std::string ExpenseTracker::str() const {
    std::ostringstream os;
    os << "{";
    size_t count = 0;
    for (const auto& pair : categories) {
        if (count > 0) {
            os << ",";
        }
        os << "\"" << pair.first << "\":";
        os << pair.second.str();
        count++;
    }
    os << "}";
    return os.str();
}
