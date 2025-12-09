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
// This file contains tests loading JSON files into
// the ExpenseTracker.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <fstream>
#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/expensetracker.h"

#include "test.h"

SCENARIO("A ExpenseTracker object can load from a JSON file", "[expensetracker]") {

  const std::string filePath = "./tests/testdatabasealt.json";

  auto fileExists = [](const std::string &path) {
    std::cout << path;
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
        filePath,
        "{ \"Studies\": { \"1\": { \"amount\": 999.99, \"date\": \"2024-12-25\", \"description\": \"Laptop\", "
        "\"tags\": [ \"computer\", \"programming\", "
        "\"uni\" ] }, \"2\": { \"amount\": 39.99, \"date\": \"2024-12-25\", \"description\": \"C++ Book\",  "
        "\"tags\": [ \"c++\", \"programming\", "
        "\"standard library\", \"uni\" ] } }, \"Travel\": { \"3\": { \"amount\": 164.0, \"date\": \"2024-12-30\", \"description\": \"Bus Pass\","
        "\"tags\": [ \"bus\", \"uni\"] } } }"));

    WHEN("a new empty ExpenseTracker object is constructed") {

      ExpenseTracker etObj1{};
      REQUIRE(etObj1.size() == 0);

      AND_WHEN("the load function is called with the file path") {

        THEN("the file will be imported without an exception") {

          REQUIRE_NOTHROW(etObj1.load(filePath));
          REQUIRE(etObj1.size() == 2);

          REQUIRE_NOTHROW(etObj1.getCategory("Studies"));
          REQUIRE(etObj1.getCategory("Studies").size() == 2);

          REQUIRE_NOTHROW(
              etObj1.getCategory("Studies").getItem("1"));
          REQUIRE(etObj1.getCategory("Studies")
                      .getItem("1")
                      .numTags() == 3);

          REQUIRE(etObj1.getCategory("Studies")
                      .getItem("1")
                      .containsTag("programming"));

          REQUIRE(etObj1.getCategory("Studies").getItem("1").getAmount() ==
                  999.99);
          REQUIRE_NOTHROW(etObj1.getCategory("Studies")
                                  .getItem("1")
                                  .getDate());
          REQUIRE(etObj1.getCategory("Studies")
                                  .getItem("1")
                                  .getDate()
                                  .getDay() == day);
          REQUIRE(etObj1.getCategory("Studies")
                                  .getItem("1")
                                  .getDate()
                                  .getMonth() == month);
          REQUIRE(etObj1.getCategory("Studies")
                                  .getItem("1")
                                  .getDate()
                                  .getYear() == year);

          REQUIRE_NOTHROW(
              etObj1.getCategory("Studies").getItem("2"));
          REQUIRE(etObj1.getCategory("Studies")
                      .getItem("2")
                      .numTags() == 4);
          REQUIRE(etObj1.getCategory("Studies")
                            .getItem("2")
                            .getAmount() == 39.99);

          REQUIRE(etObj1.getCategory("Studies")
                            .getSum() == 1039.98);

          REQUIRE_NOTHROW(etObj1.getCategory("Travel"));
          REQUIRE(etObj1.getCategory("Travel").size() == 1);
          REQUIRE_NOTHROW(
              etObj1.getCategory("Travel").getItem("3"));
          REQUIRE(etObj1.getCategory("Travel")
                      .getItem("3")
                      .numTags() == 2);
          REQUIRE(etObj1.getCategory("Travel")
                      .getItem("3")
                      .getAmount() == 164.0);

        } // THEN

      } // AND_WHEN

    } // WHEN

  } // GIVEN

} // SCENARIO
