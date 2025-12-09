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
// This file contains tests saving JSON files from a
// the ExpenseTracker.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <fstream>
#include <sstream>
#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/expensetracker.h"

SCENARIO("A ExpenseTracker object can save to a JSON file", "[expensetracker]") {

  const std::string filePath = "./tests/testdatabasealt.json";

  auto fileExists = [](const std::string &path) {
    return std::ifstream(path).is_open();
  };

  auto readFileContents = [](const std::string &path) {
    // Not a robust way to do this, but here it doesn't matter so much, if it
    // goes wrong we'll fail the test anyway…
    std::stringstream ss{std::stringstream::out};
    ss << std::ifstream(path).rdbuf();
    return ss.str();
  };

  auto writeFileContents = [](const std::string &path,
                              const std::string &contents) {
    // Not a robust way to do this, but here it doesn't matter so much, if it
    // goes wrong we'll fail the test anyway…
    std::ofstream f{path};
    f << contents;
  };

  GIVEN("a valid path to an empty database JSON file") {

    // Reset the file...
    REQUIRE(fileExists(filePath));
    REQUIRE_NOTHROW(writeFileContents(filePath, "{}"));

    WHEN("a new empty ExpenseTracker object is constructed") {

      ExpenseTracker etObj1{};
      REQUIRE(etObj1.size() == 0);

      const std::string cIdent1 = "Studies";
      const std::string cIdent2 = "Travel";

      const std::string iIdent1 = "1";
      const std::string iIdent2 = "2";

      const std::string iDesc1 = "C++ Book";
      const std::string iDesc2 = "Bus Pass";

      const double amount1 = 39.99;
      const double amount2 = 164.0;

      const std::string tag1 = "uni";
      const std::string tag2 = "programming";

      const int year = 2024;
      const int month = 12;
      const int day = 25;
      const int day2 = day + 1;
      const Date date1 = Date(year, month, day);
      const Date date2 = Date(year, month, day2);

      AND_WHEN("the ExpenseTracker object is populated with dummy data") {

        Item iObj1{iIdent1, iDesc1, amount1, date1};
        Item iObj2{iIdent2, iDesc2, amount2, date2};

        iObj1.addTag(tag1);
        iObj1.addTag(tag2);
        iObj2.addTag(tag1);

        REQUIRE(iObj1.numTags() == 2);
        REQUIRE(iObj2.numTags() == 1);

        Category cObj1{cIdent1};
        Category cObj2{cIdent2};

        cObj1.addItem(iObj1);
        cObj1.addItem(iObj1);
        cObj2.addItem(iObj2);

        REQUIRE(cObj1.size() == 1);
        REQUIRE(cObj2.size() == 1);

        etObj1.addCategory(cObj1);
        etObj1.addCategory(cObj2);

        REQUIRE(etObj1.size() == 2);

        THEN("the saving to file will not throw an exception") {

          REQUIRE_NOTHROW(etObj1.save(filePath));

          AND_THEN("the file contents will be correct") {

            REQUIRE(
                readFileContents(filePath).find(
                    "{\"Studies\":{\"1\":{\"amount\":39.99,\"date\":\"2024-12-25\","
                    "\"description\":\"C++ Book\","
                    "\"tags\":[\"uni\","
                    "\"programming\"]}},\"Travel\":"
                    "{\"2\":{\"amount\":164.0,\"date\":\"2024-12-26\",\"description\":\"Bus "
                    "Pass\","
                    "\"tags\":[\"uni\"]}}}") == 0);
          } // AND_THEN

        } // THEN

      } // AND_WHEN

    } // WHEN

  } // GIVEN

} // SCENARIO
