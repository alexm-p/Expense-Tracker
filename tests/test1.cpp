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
// This file contains tests for the action program
// argument.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/371expenses.h"

SCENARIO("The action program argument can be parsed correctly", "[args]") {

  GIVEN("a --action program argument and value") {

    WHEN("the value of the action argument is not an expected action "
         "('invalid')") {

      Argv argvObj({"test", "--action", "invalid"});
      auto **argv = argvObj.argv();
      auto argc = argvObj.argc();

      auto cxxopts = App::cxxoptsSetup();
      auto args = cxxopts.parse(argc, argv);

      const std::string exceptionMessage = "action";

      THEN("a std::invalid_argument exception is thrown with the message '" +
           exceptionMessage + "'") {

        REQUIRE_THROWS_AS(App::parseActionArgument(args),
                          std::invalid_argument);
        REQUIRE_THROWS_WITH(App::parseActionArgument(args), exceptionMessage);

      } // THEN

    } // WHEN

    WHEN("the value of the program argument is 'create'") {

      Argv argvObj({"test", "--action", "create"});
      auto **argv = argvObj.argv();
      auto argc = argvObj.argc();

      auto cxxopts = App::cxxoptsSetup();
      auto args = cxxopts.parse(argc, argv);

      THEN("the argument value is parsed without exception") {

        REQUIRE_NOTHROW(App::parseActionArgument(args));

        AND_THEN("the response is Action::CREATE") {

          REQUIRE(App::parseActionArgument(args) == App::Action::CREATE);

        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN("the value of the program argument is 'json'") {

      Argv argvObj({"test", "--action", "json"});
      auto **argv = argvObj.argv();
      auto argc = argvObj.argc();

      auto cxxopts = App::cxxoptsSetup();
      auto args = cxxopts.parse(argc, argv);

      THEN("the argument value is parsed without exception") {

        REQUIRE_NOTHROW(App::parseActionArgument(args));

        AND_THEN("the response is Action::JSON") {

          REQUIRE(App::parseActionArgument(args) == App::Action::JSON);

        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN("the value of the program argument is 'update'") {

      Argv argvObj({"test", "--action", "update"});
      auto **argv = argvObj.argv();
      auto argc = argvObj.argc();

      auto cxxopts = App::cxxoptsSetup();
      auto args = cxxopts.parse(argc, argv);

      THEN("the argument value is parsed without exception") {

        REQUIRE_NOTHROW(App::parseActionArgument(args));

        AND_THEN("the response is Action::UPDATE") {

          REQUIRE(App::parseActionArgument(args) == App::Action::UPDATE);

        } // AND_THEN

      } // THEN

    } // WHEN

    WHEN("the value of the program argument is a 'delete'") {

      Argv argvObj({"test", "--action", "delete"});
      auto **argv = argvObj.argv();
      auto argc = argvObj.argc();

      auto cxxopts = App::cxxoptsSetup();
      auto args = cxxopts.parse(argc, argv);

      THEN("the argument value is parsed without exception") {

        REQUIRE_NOTHROW(App::parseActionArgument(args));

        AND_THEN("the response is Action::DELETE") {

          REQUIRE(App::parseActionArgument(args) == App::Action::DELETE);

        } // AND_THEN

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO