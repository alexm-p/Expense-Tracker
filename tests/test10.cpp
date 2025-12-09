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
// This file tests 371expenses output for the database
// argument and 'create' value of the action argument.
// This test works by calling on your program to create
// a category, item, and a tag, and each time
// calls upon your program to load the JSON file to
// check the category/item/tag exists.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/371expenses.h"

SCENARIO(
    "The database and action program arguments can be parsed correctly "
    "such that a file can be opened, read, parsed, data added, and written to",
    "[args]") {

  const std::string filePath = "./tests/testdatabasealt.json";

  auto fileExists = [](const std::string &path) {
    return std::ifstream(path).is_open();
  };

  auto writeFileContents = [](const std::string &path,
                              const std::string &contents) {
    // Not a robust way to do this, but here it doesn't matter so much, if it
    // goes wrong we'll fail the test anyway…
    std::ofstream f{path};
    f << contents;
  };

  GIVEN("a valid path to a reset database JSON file") {

    // Reset the file...
    REQUIRE(fileExists(filePath));
    REQUIRE_NOTHROW(writeFileContents(
        filePath, "{ \"Studies\": { \"1\": { \"amount\": 999.99, \"date\": "
                  "\"2024-12-25\", \"description\": \"Laptop\", "
                  "\"tags\": [ \"computer\", \"programming\", "
                  "\"uni\" ] }, \"2\": { \"amount\": 39.99, \"date\": "
                  "\"2024-12-25\", \"description\": \"C++ Book\",  "
                  "\"tags\": [ \"c++\", \"programming\", "
                  "\"standard library\", \"uni\" ] } }, \"Travel\": { \"3\": { "
                  "\"amount\": 164.0, \"date\": \"2024-12-30\", "
                  "\"description\": \"Bus Pass\","
                  "\"tags\": [ \"bus\", \"uni\"] } } }"));

    const std::string testCategory = "TestCategory";
    const std::string testItemId = "TestItem";
    const std::string testItemDesc = "TestDesc";
    const double testItemAmount = 1.99;

    const std::string testDate = "2024-12-25";
    const std::string testTag = "TestTag";

    WHEN("the db program argument is '" + filePath +
         "', the action program argument is 'create'") {

      AND_WHEN("and the category program argument is '" + testCategory + "'") {

        Argv argvObj({"test", "--db", filePath.c_str(), "--action", "create",
                      "--category", testCategory.c_str()});
        auto **argv = argvObj.argv();
        auto argc = argvObj.argc();

        THEN("no exception is thrown") {

          REQUIRE_NOTHROW(App::run(argc, argv));

          AND_WHEN("loading the saved file into a new ExpenseTracker object") {

            ExpenseTracker etObj1{};
            REQUIRE(etObj1.size() == 0);
            REQUIRE_NOTHROW(etObj1.load(filePath));

            THEN("the new ExpenseTracker will contain the Category object") {

              REQUIRE_NOTHROW(etObj1.getCategory(testCategory));
              REQUIRE(etObj1.getCategory(testCategory).size() == 0);

            } // THEN

            AND_WHEN("the item identifier argument is '" + testItemId +
                     "', description argument is '" + testItemDesc +
                     "', amount argument is '" +
                     std::to_string(testItemAmount) + "', tag argument is '" +
                     testTag + "', and date argument is '" + testDate + "'.") {

              Argv argvObj({
                  "test",
                  "--db",
                  filePath.c_str(),
                  "--action",
                  "create",
                  "--category",
                  testCategory.c_str(),
                  "--item",
                  testItemId.c_str(),
                  "--amount",
                  std::to_string(testItemAmount).c_str(),
                  "--description",
                  testItemDesc.c_str(),
                  "--date",
                  testDate.c_str(),
                  "--tag",
                  testTag.c_str(),
              });
              auto **argv = argvObj.argv();
              auto argc = argvObj.argc();

              THEN("no exception is thrown") {

                REQUIRE_NOTHROW(App::run(argc, argv));

                AND_WHEN(
                    "loading the saved file into a new ExpenseTracker object") {

                  ExpenseTracker etObj2{};
                  REQUIRE(etObj2.size() == 0);
                  REQUIRE_NOTHROW(etObj2.load(filePath));

                  THEN("the new ExpenseTracker will contain the Category and "
                       "Item "
                       "objects") {

                    REQUIRE_NOTHROW(etObj2.getCategory(testCategory));
                    REQUIRE(etObj2.getCategory(testCategory).size() == 1);
                    REQUIRE_NOTHROW(
                        etObj2.getCategory(testCategory).getItem(testItemId));
                    REQUIRE(etObj2.getCategory(testCategory)
                                .getItem(testItemId)
                                .numTags() == 1);

                  } // THEN

                  AND_WHEN("loading the saved file into a new ExpenseTracker "
                           "object") {

                    ExpenseTracker etObj3{};
                    REQUIRE(etObj3.size() == 0);
                    REQUIRE_NOTHROW(etObj3.load(filePath));

                    THEN("the new ExpenseTracker will contain the Category and "
                         "Item objects and tag") {

                      REQUIRE_NOTHROW(etObj3.getCategory(testCategory));
                      REQUIRE(etObj3.getCategory(testCategory).size() == 1);
                      REQUIRE_NOTHROW(
                          etObj3.getCategory(testCategory).getItem(testItemId));
                      REQUIRE(etObj3.getCategory(testCategory)
                                  .getItem(testItemId)
                                  .numTags() == 1);
                      REQUIRE(etObj3.getCategory(testCategory)
                                  .getItem(testItemId)
                                  .containsTag(testTag));

                    } // THEN

                  } // AND_WHEN

                } // AND_WHEN

              } // THEN

            } // AND_WHEN

          } // AND_WHEN

        } // THEN

      } // AND_WHEN

    } // WHEN

  } // GIVEN

} // SCENARIO
