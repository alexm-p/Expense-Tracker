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
// argument and 'json' value of the action argument.
// This test works by capturing the stdout of your
// program.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/371expenses.h"

// Redirect std::cout to a buffer
// by Björn Pollex
// via https://stackoverflow.com/a/5419388
// licensed under CC BY-SA 3.0.
class CoutRedirect {
private:
  std::streambuf *old;

public:
  CoutRedirect(std::streambuf *new_buffer)
      : old(std::cout.rdbuf(new_buffer)) { /* do nothing */
  }

  ~CoutRedirect() { std::cout.rdbuf(old); }
};

SCENARIO("The database and action program arguments can be parsed correctly "
         "such that a file can be opened, json output printed, parsed, and "
         "output to stdout",
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
        filePath,
        "{ \"Studies\": { \"1\": { \"amount\": 999.99, \"date\": \"2024-12-25\", \"description\": \"Laptop\", "
        "\"tags\": [ \"computer\", \"programming\", "
        "\"uni\" ] }, \"2\": { \"amount\": 39.99, \"date\": \"2024-12-25\", \"description\": \"C++ Book\",  "
        "\"tags\": [ \"c++\", \"programming\", "
        "\"standard library\", \"uni\" ] } }, \"Travel\": { \"3\": { \"amount\": 164.0, \"date\": \"2024-12-30\", \"description\": \"Bus Pass\","
        "\"tags\": [ \"bus\", \"uni\"] } } }"));

    WHEN("the db program argument is '" + filePath +
         "' and the action program argument is 'json'") {

      Argv argvObj({"test", "--db", filePath.c_str(), "--action", "json"});
      auto **argv = argvObj.argv();
      auto argc = argvObj.argc();

      std::stringstream buffer;
      CoutRedirect originalBuffer{buffer.rdbuf()};

      THEN("the expected JSON output is printed to stdout") {

        REQUIRE_NOTHROW(App::run(argc, argv));

        std::string output = buffer.str();
        REQUIRE(output.find(
        "{\"Studies\":{\"1\":{\"amount\":999.99,\"date\":\"2024-12-25\",\"description\":\"Laptop\","
        "\"tags\":[\"computer\",\"programming\","
        "\"uni\"]},\"2\":{\"amount\":39.99,\"date\":\"2024-12-25\",\"description\":\"C++ Book\","
        "\"tags\":[\"c++\",\"programming\","
        "\"standard library\",\"uni\"]}},\"Travel\":{\"3\":{\"amount\":164.0,\"date\":\"2024-12-30\",\"description\":\"Bus Pass\","
        "\"tags\":[\"bus\",\"uni\"]}}}") == 0);

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO
