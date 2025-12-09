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
// This file contains tests for suming up Item objects
// in Category and Expense Tracker containers.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"
#include "test.h"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/expensetracker.h"

SCENARIO("Category and ExpenseTracker objects can sum up the Items "
         "contained within them",
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

            AND_GIVEN("the item identifier '" + ident + "', description '" +
                      description + "', amount '" + std::to_string(amount) +
                      "', and valid date '" + std::to_string(year) + "', '" +
                      std::to_string(month) + "', '" + std::to_string(day) +
                      "' object") {

              WHEN("a new Item object is added to the category") {
                etObj1.getCategory(categoryIdent)
                    .newItem(ident, description, amount, date);

                THEN("The category will contain that item") {
                  REQUIRE(etObj1.getCategory(categoryIdent).size() == 1);
                  REQUIRE(etObj1.getCategory(categoryIdent)
                              .getItem(ident)
                              .getIdent() == ident);
                } // THEN

                AND_THEN(
                    "The category sum will equal the amount of the sole item") {
                  REQUIRE(etObj1.getCategory(categoryIdent).getSum() == amount);
                }

                AND_THEN("The expense tracker sum will also equal the amount "
                         "of the sole item") {
                  REQUIRE(etObj1.getSum() == amount);
                }

                AND_GIVEN("the different item identifier '" + ident2 +
                          "', description '" + description2 + "', amount '" +
                          std::to_string(amount2) + "', and valid date '" +
                          std::to_string(year) + "', '" +
                          std::to_string(month) + "', '" +
                          std::to_string(day2) + "' object") {

                  WHEN("That different Item object is added to the category") {
                    etObj1.getCategory(categoryIdent)
                        .newItem(ident2, description2, amount2, date2);

                    THEN("The category will also contain that item") {
                      REQUIRE(etObj1.getCategory(categoryIdent).size() == 2);
                      REQUIRE(etObj1.getCategory(categoryIdent)
                                  .getItem(ident2)
                                  .getIdent() == ident2);
                    } // THEN

                    AND_THEN(
                        "The category sum will equal the amount of the two "
                        "items") {
                      REQUIRE(etObj1.getCategory(categoryIdent).getSum() ==
                              amount + amount2);
                    }

                    AND_THEN(
                        "The expense tracker sum will also equal the amount "
                        "of the two items") {
                      REQUIRE(etObj1.getSum() == amount + amount2);
                    }

                  } // WHEN

                } // AND_GIVEN

              } // WHEN

            } // AND_GIVEN
          } // AND_THEN
        } // THEN
      } // WHEN
    } // AND_GIVEN
  } // GIVEN

} // SCENARIO