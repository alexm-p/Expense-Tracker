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
// This file contains tests adding, getting and deleting
// Category objects in the ExpenseTracker container.
// -----------------------------------------------------

#include "test.h"
#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/expensetracker.h"

SCENARIO("An empty ExpenseTracker can be constructed successfully", "[expensetracker]") {

  GIVEN("nothing") {

    WHEN("a new ExpenseTracker object is constructed") {

      ExpenseTracker w{};

      THEN("it will contain zero Categories") { REQUIRE(w.size() == 0); } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("Category objects can be added to and retrieved from a ExpenseTracker",
         "[expensetracker]") {

  GIVEN("a empty ExpenseTracker object") {

    ExpenseTracker etObj1{};

    REQUIRE(etObj1.size() == 0);

    AND_GIVEN("an empty Category with identifier '" + categoryIdent + "'") {

      Category cObj1{categoryIdent};

      REQUIRE(cObj1.size() == 0);

      WHEN("adding the Category") {

        THEN("true is returned") {

          REQUIRE(etObj1.addCategory(cObj1) == true);

          AND_THEN("the ExpenseTracker contains 1 Category") {

            REQUIRE(etObj1.size() == 1);
            REQUIRE_FALSE(etObj1.size() == 0);

            AND_THEN("getting the Category using the ident '" + categoryIdent +
                     "' will return the expected object") {

              REQUIRE(etObj1.getCategory(categoryIdent) == cObj1);

            } // AND_THEN

          } // AND_THEN

          AND_GIVEN("adding a second empty Category with the same ident, '" +
                    ident) {

            Category cObj2{categoryIdent};

            REQUIRE(cObj2.size() == 0);

            WHEN("adding the Category") {

              THEN("false is returned and the size of the ExpenseTracker will not "
                   "change") {

                REQUIRE_FALSE(etObj1.addCategory(cObj2));
                REQUIRE(etObj1.size() == 1);
                REQUIRE_FALSE(etObj1.size() == 0);

              } // THEN

            } // WHEN

          } // AND_GIVEN

          const std::string ident3 = "Test2";
          Category cObj3{ident3};

          AND_GIVEN("another empty Category with a different ident, '" +
                    ident3) {

            REQUIRE(cObj3.size() == 0);

            WHEN("the Category is added") {

              THEN("true is returned and the size of the ExpenseTracker will be 2") {

                REQUIRE(etObj1.addCategory(cObj3) == true);
                REQUIRE(etObj1.size() == 2);
                REQUIRE_FALSE(etObj1.size() == 0);

                AND_THEN("getting the Category using the ident '" + ident3 +
                         "' will return the expected object") {

                  REQUIRE(etObj1.getCategory(ident3) == cObj3);

                } // AND_THEN

              } // THEN

            } // WHEN

          } // AND_GIVEN

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO

SCENARIO("Category objects can be added to and deleted from a ExpenseTracker",
         "[expensetracker]") {

  GIVEN("an empty ExpenseTracker object") {

    ExpenseTracker etObj1{};

    REQUIRE(etObj1.size() == 0);

    WHEN("a Category with identifier '" + categoryIdent + "' can be added") {

      Category cObj1{categoryIdent};

      REQUIRE(cObj1.size() == 0);

      REQUIRE(etObj1.addCategory(cObj1) == true);

      THEN("the ExpenseTracker contains 1 Category") {

        REQUIRE(etObj1.size() == 1);
        REQUIRE_FALSE(etObj1.size() == 0);

      } // THEN

      THEN("the Category can be retrieved by the ident '" + categoryIdent + "'") {

        REQUIRE(etObj1.getCategory(categoryIdent) == cObj1);

      } // THEN

      THEN("deleting the existent Category ('" + ident +
           "') will leave the ExpenseTracker empty") {

        REQUIRE(etObj1.deleteCategory(categoryIdent));
        REQUIRE_THROWS_AS(etObj1.getCategory(categoryIdent), std::out_of_range);
        REQUIRE(etObj1.size() == 0);

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO
