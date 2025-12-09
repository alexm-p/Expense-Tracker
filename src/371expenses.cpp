// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2119504>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "371expenses.h"
#include "lib_cxxopts.hpp"
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <iostream>

/**
 * @brief Main application entry point.
 *
 * This function sets up the command line options, parses the arguments, loads the ExpenseTracker database,
 * and then performs one of several actions (create, json, update, delete, sum) based on the parsed action argument.
 * After performing the requested action, any changes to the database are saved.
 *
 * The function also performs error checking for missing or invalid arguments and prints appropriate error messages.
 *
 * @param argc The number of command line arguments.
 * @param argv Array of command line argument strings.
 * @return int Returns 0 on successful execution; non-zero value indicates an error.
 */
int App::run(int argc, char *argv[]) {
  // Setup and parse command line options using cxxopts.
  auto options = App::cxxoptsSetup();
  auto args = options.parse(argc, argv);

  // If help flag is present, print help message and exit.
  if (args.count("help")) {
    std::cout << options.help() << '\n';
    return 0;
  }

  // Retrieve the database filename from the command line arguments.
  const std::string db = args["db"].as<std::string>();

  // Construct an ExpenseTracker object and load the database.
  ExpenseTracker etObj{};
  etObj.load(db);

  // Parse the action argument to decide what action to perform.
  const Action a = parseActionArgument(args);
  switch (a) {
    case Action::CREATE:
      if (args.count("category")) {
        std::string category = args["category"].as<std::string>();
        etObj.newCategory(category);  // Create or ensure the category exists.        
        if (args.count("item")) {
          std::string item = args["item"].as<std::string>();
          if (args.count("description")) {
            std::string description = args["description"].as<std::string>();
            if (args.count("amount")) {
              double amount = std::stod(args["amount"].as<std::string>());
              Date date;
              if (args.count("date")) {
                date = Date(args["date"].as<std::string>());
              }
              etObj.getCategory(category).newItem(item, description, amount, date);
      
              if (args.count("tag")) {
                std::string tag = args["tag"].as<std::string>();
                etObj.getCategory(category).getItem(item).addTag(tag);
              }
            } else {
              std::cerr << "Error: missing amount argument(s)." << std::endl;
              return 1;
            }
          } else {
            std::cerr << "Error: missing description argument(s)." << std::endl;
            return 1;
          }
        }
      } else {
        std::cerr << "Error: missing category, item, amount, description argument(s)." << std::endl;
        return 1;
      }
      break;


    case Action::JSON:
      // If an item is specified, output the JSON representation for that item.
      if (args.count("item")) {
        if (!args.count("category")) {
          std::cerr << "Error: missing category argument(s)." << std::endl;
          return 1;
        }
        std::string category = args["category"].as<std::string>();
        try {
          // Attempt to output the JSON for the category.
          getJSON(etObj, category);
        } catch (const std::out_of_range& e) {
          std::cerr << "Error: invalid category argument(s)." << std::endl;
          return 1;
        }
        std::string item = args["item"].as<std::string>();
        try {
          // Attempt to output the JSON for the specified item.
          std::cout << getJSON(etObj, category, item) << std::endl;
        } catch (const std::out_of_range& e) {
          std::cerr << "Error: invalid item argument(s)." << std::endl;
          return 1;
        }
      }
      // If only a category is specified, output the JSON for the category.
      else if (args.count("category")) {
        std::string category = args["category"].as<std::string>();
        try {
          std::cout << getJSON(etObj, category) << std::endl;
        } catch (const std::out_of_range& e) {
          std::cerr << "Error: invalid category argument(s)." << std::endl;
          return 1;
        }
      }
      // If neither category nor item are specified, output the entire database JSON.
      else {
        try {
          std::cout << getJSON(etObj) << std::endl;
        } catch (...) {
          std::cerr << "Error: invalid JSON." << std::endl;
          return 1;
        }
      }
      break;

    case Action::UPDATE:
      if (args.count("item")) {
        if (!args.count("category")) {
          throw std::invalid_argument("Category must be specified with item");
        }
        std::string category = args["category"].as<std::string>();
        std::string item = args["item"].as<std::string>();
        try {
          // Validate the existence of the category and item.
          getJSON(etObj, category);
          try {
            getJSON(etObj, category, item);
          } catch (const std::out_of_range& e) {
            std::cerr << "Error: invalid item argument(s)." << std::endl;
            return 1;
          }
        } catch (const std::out_of_range& e) {
          std::cerr << "Error: invalid category argument(s)." << std::endl;
          return 1;
        }
        // Update the expense item attributes if provided.
        if (args.count("description")) {
          etObj.getCategory(category).getItem(item).setDescription(args["description"].as<std::string>());
        }
        if (args.count("amount")) {
          etObj.getCategory(category).getItem(item).setAmount(std::stod(args["amount"].as<std::string>()));
        }
        if (args.count("date")) {
          etObj.getCategory(category).getItem(item).setDate(Date(args["date"].as<std::string>()));
        }
        if (args.count("tag")) {
          std::string tag = args["tag"].as<std::string>();
          etObj.getCategory(category).getItem(item).addTag(tag);
        }
      } else {
        throw std::invalid_argument("Category, item, or tag must be specified with update");
      }
      break;

    case Action::DELETE:
      // Deletion based on tag, item, or category.
      if (args.count("tag")) {
        if (!args.count("category")) {
          throw std::invalid_argument("Category must be specified with tag");
        }
        std::string category = args["category"].as<std::string>();
        if (!args.count("item")) {
          throw std::invalid_argument("Item must be specified with tag");
        }
        std::string item = args["item"].as<std::string>();
        if (!args.count("tag")) {
          throw std::invalid_argument("Tag must be specified with tag");
        }
        std::string tag = args["tag"].as<std::string>();
        etObj.getCategory(category).getItem(item).deleteTag(tag);
      } else if (args.count("item")) {
        if (!args.count("category")) {
          throw std::invalid_argument("Category must be specified with item");
        }
        std::string category = args["category"].as<std::string>();
        std::string item = args["item"].as<std::string>();
        etObj.getCategory(category).deleteItem(item);
      } else if (args.count("category")) {
        std::string category = args["category"].as<std::string>();
        etObj.deleteCategory(category);
      } else {
        throw std::invalid_argument("Category, item, or tag must be specified with delete");
      }
      break;

    case Action::SUM:
      // Sum expenses for a specific category or overall if no category is specified.
      if (args.count("category")) {
        std::string category = args["category"].as<std::string>();
        try {
          double sum = etObj.getCategory(category).getSum();
          std::cout << sum << std::endl;
        } catch (const std::out_of_range& e) {
          std::cerr << "Error: invalid category argument(s)." << std::endl;
          return 1;
        }
      } else {
        double sum = etObj.getSum();
        std::cout << sum << std::endl;
      }
      break;

    default:
      throw std::runtime_error("unknown action");
  }
  // Save any changes to the database.
  etObj.save(db);
  return 0;
}

/**
 * @brief Configures and returns a cxxopts::Options instance for parsing command line arguments.
 *
 * This function defines the available command line options (such as db, action, category, description, amount,
 * item, date, tag, and help) and their expected types, as well as default values where appropriate.
 *
 * @return cxxopts::Options A configured cxxopts::Options object.
 */
cxxopts::Options App::cxxoptsSetup() {
  cxxopts::Options cxxopts("371expenses", "Student ID: " + STUDENT_NUMBER + "\n");

  cxxopts.add_options()(
      "db", "Filename of the 371expenses database",
      cxxopts::value<std::string>()->default_value("database.json"))(

      "action",
      "Action to take, can be: 'create', 'json', 'update', 'delete', 'sum'.",
      cxxopts::value<std::string>())(

      "category",
      "Apply action (create, json, update, delete, sum) to a category. If you "
      "want to add a category, set the action argument to 'create' and the "
      "category argument to your chosen category identifier.",
      cxxopts::value<std::string>())(

      "description",
      "Apply action (create, update) to an expense description. If you want to "
      "add an expense item, set the action argument to 'create', the category "
      "argument to your chosen category identifier and the description "
      "argument to the expense description and the amount argument to the "
      "expense amount, and the id argument to the unique expense id.",
      cxxopts::value<std::string>())(

      "amount",
      "Apply action (create, update) to an expense amount. If you want to add "
      "an expense item, set the action argument to 'create', the category "
      "argument to your chosen category identifier and the description "
      "argument to the expense description and the amount argument to the "
      "expense amount, and the id argument to the unique expense id.",
      cxxopts::value<std::string>())(

      "item",
      "Apply action (create, update, json, delete) to an expense item "
      "identified by its id. If you want to update an expense item, set the "
      "action argument to 'update', the id argument to the expense identifier, "
      "the description argument to the updated expense description, and the "
      "amount argument to the updated expense amount.",
      cxxopts::value<std::string>())(

      "date",
      "When creating or updating an expense item, set the date flag to change "
      "the expense item's date to the one specified as an argument (e.g. "
      "'2024-11-23'). If the date argument is ommitted set the expense date "
      "to today's date when creating an expense item, and leave the date "
      "unchanged if omitted when updating an expense item.",
      cxxopts::value<std::string>())(

      "tag",
      "Apply action (create or delete) to a tag.  If you want to add a tag, "
      "set the action argument to 'create', the category argument to your "
      "chosen category identifier, the item argument to your chosen item "
      "identifier, and the tag argument to a single tag 'tag' or comma "
      "seperated list of tags: 'tag1,tag2'). The action update/sum/json are "
      "unsupported here.",
      cxxopts::value<std::string>())(

      "h,help", "Print usage.");

  return cxxopts;
}

/**
 * @brief Parses the action argument from the command line in a case-insensitive manner.
 *
 * This function converts the provided action argument to lowercase and matches it against known actions
 * ("create", "json", "update", "delete", "sum"). If the argument does not match any valid action,
 * an std::invalid_argument exception is thrown.
 *
 * @param args The cxxopts::ParseResult containing the command line arguments.
 * @return App::Action The corresponding action enum value.
 * @throws std::invalid_argument if an invalid action string is provided.
 */
App::Action App::parseActionArgument(cxxopts::ParseResult &args) {
  std::string input = args["action"].as<std::string>();
  // Convert the input string to lowercase.
  transform(input.begin(), input.end(), input.begin(), ::tolower); 
  if (input == "create") return Action::CREATE;
  if (input == "json") return Action::JSON;
  if (input == "update") return Action::UPDATE;
  if (input == "delete") return Action::DELETE;
  if (input == "sum") return Action::SUM;
  throw std::invalid_argument("action");
}

/**
 * @brief Returns the JSON representation of the entire ExpenseTracker.
 *
 * This function serializes the ExpenseTracker object to a JSON-formatted string.
 *
 * @param etObj The ExpenseTracker object.
 * @return std::string The JSON string representation of the ExpenseTracker.
 */
std::string App::getJSON(ExpenseTracker &etObj) {
  return etObj.str();
}

/**
 * @brief Returns the JSON representation of a specific Category within the ExpenseTracker.
 *
 * Retrieves the specified category from the ExpenseTracker and returns its JSON representation.
 *
 * @param etObj The ExpenseTracker object.
 * @param c The identifier of the category.
 * @return std::string The JSON string representation of the specified Category.
 */
std::string App::getJSON(ExpenseTracker &etObj, const std::string &c) {
  auto cObj = etObj.getCategory(c);
  return cObj.str();
}

/**
 * @brief Returns the JSON representation of a specific ExpenseItem within a Category.
 *
 * Retrieves the specified item from the given category in the ExpenseTracker and returns its JSON representation.
 *
 * @param etObj The ExpenseTracker object.
 * @param c The identifier of the category.
 * @param id The identifier of the expense item.
 * @return std::string The JSON string representation of the specified ExpenseItem.
 */
std::string App::getJSON(ExpenseTracker &etObj, 
                         const std::string &c,
                         const std::string &id) {
  auto iObj = etObj.getCategory(c).getItem(id);
  return iObj.str();
}
