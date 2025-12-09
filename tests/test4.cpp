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
// Items in the Category container.
// -----------------------------------------------------

#include "test.h"
#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/category.h"


SCENARIO("An empty Category can be constructed successfully", "[category]") {

  GIVEN("the category identifier '" + categoryIdent + "'") {

    WHEN("a new Category object is constructed") {

      Category cObj1{categoryIdent};

      THEN("it will contain zero Items") { REQUIRE(cObj1.size() == 0); } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("Items can be added to and retrieved from a Category", "[category]") {

  GIVEN("an empty Category object with identifier '" + categoryIdent + "'") {

    Category cObj1{categoryIdent};

    REQUIRE(cObj1.size() == 0);

    AND_GIVEN("the item identifier '" + ident + "', description '" +
              description + "', amount '" + std::to_string(amount) +
              "', and valid date '" + std::to_string(year) + "', '" +
              std::to_string(month) + "', '" + std::to_string(day) +
              "' object") {

      WHEN("a new Item object is constructed") {

        Item iObj1{ident, description, amount, date};

        REQUIRE(iObj1.numTags() == 0);

        AND_WHEN("adding the Item") {

          THEN("true is returned") {

            REQUIRE(cObj1.addItem(iObj1) == true);

            AND_THEN("the Category contains 1 Item") {

              REQUIRE(cObj1.size() == 1);

              AND_THEN("getting the Item using the ident '" + ident +
                       "' will return the expected object") {

                REQUIRE(cObj1.getItem(ident) == iObj1);
                REQUIRE_FALSE(cObj1.size() == 0);

              } // AND_THEN

            } // AND_THEN

            AND_GIVEN("another Item with the same identifier, '" + ident +
                      "'") {

              Item iObj2{ident, description, amount, date};

              REQUIRE(iObj2.numTags() == 0);

              WHEN("adding the Item") {

                THEN("false is returned and the size of the Category will not "
                     "change") {

                  REQUIRE(cObj1.addItem(iObj2) == false);
                  REQUIRE(cObj1.size() == 1);

                } // THEN

              } // WHEN

            } // AND_GIVEN

            const std::string ident3 = "Test2";

            AND_GIVEN("another empty Item with the a different ident, '" +
                      ident3 + "'") {

              Item iObj3{ident3, description, amount, date};

              REQUIRE(iObj3.numTags() == 0);

              WHEN("adding the Item") {

                THEN(
                    "true is returned and the size of the Category will be 2") {

                  REQUIRE(cObj1.addItem(iObj3) == true);
                  REQUIRE(cObj1.size() == 2);

                  AND_THEN("getting the Item using the ident '" + ident3 +
                           "' will return the expected object") {

                    REQUIRE(cObj1.getItem(ident3) == iObj3);

                  AND_THEN("The sum of the two Items in the category will return the expected result") {

                    REQUIRE(cObj1.getSum() == 2.0*amount);

                  } // AND_THEN

                  } // AND_THEN

                } // THEN

              } // WHEN

            } // AND_GIVEN

          } // THEN

        } // AND_WHEN
      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO

SCENARIO("Items can be added to and deleted from a Category", "[category]") {

  GIVEN("a empty Category object with identifier '" + categoryIdent + "'") {

    Category cObj1{categoryIdent};

    REQUIRE(cObj1.size() == 0);

    AND_GIVEN("the item identifier '" + ident + "', description '" +
              description + "', amount '" + std::to_string(amount) +
              "', and valid date '" + std::to_string(year) + "', '" +
              std::to_string(month) + "', '" + std::to_string(day) +
              "' object") {

      WHEN("a new Item object is constructed") {

        Item iObj1{ident, description, amount, date};

        REQUIRE(iObj1.numTags() == 0);

        AND_WHEN("the entry is added") {

          THEN("true is returned") {

            REQUIRE(cObj1.addItem(iObj1) == true);

            AND_THEN("the Category contains 1 Item") {

              REQUIRE(cObj1.size() == 1);

              WHEN("getting the Item using the ident '" + ident + "'") {

                THEN("the Item object is returned") {

                  REQUIRE(cObj1.getItem(ident) == iObj1);

                } // THEN

              } // WHEN

              WHEN("deleting a non-existent Item with ident '0'") {

                THEN(
                    "an std::out_of_range exception is thrown and the Category "
                    "will not change") {

                  REQUIRE_THROWS_AS(cObj1.deleteItem("0"), std::out_of_range);
                  REQUIRE(cObj1.getItem(ident) == iObj1);
                  REQUIRE(cObj1.size() == 1);

                } // THEN

              } // WHEN

              WHEN("deleting the added Item with ident '" + ident) {

                THEN("true is returned and the Category will be empty") {

                  REQUIRE(cObj1.deleteItem(ident) == true);
                  REQUIRE_THROWS_AS(cObj1.getItem(ident), std::out_of_range);
                  REQUIRE(cObj1.size() == 0);

                } // THEN

              } // WHEN
            } // AND_WHEN

          } // AND_THEN

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO
