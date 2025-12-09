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
// entries in the tag container of the Item class.
// -----------------------------------------------------
#include "test.h"
#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/item.h"

SCENARIO("An item can be constructed successfully", "[item]") {


  GIVEN("the item identifier '" + ident + "', description '" + description +
        "', amount '" + std::to_string(amount) + "', and valid date '" + std::to_string(year) +
        "', '" + std::to_string(month) + "', '" + std::to_string(day) +
        "' object") {

    WHEN("a new Item object is constructed") {

      Item iObj1{ident, description, amount, date};

        THEN("it will have no tags") {
          REQUIRE(iObj1.numTags() == 0);
        } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("Tags can be added to and retrieved from a Item", "[item]") {

  GIVEN("the item identifier '" + ident + "', description '" + description +
        "', amount '" + std::to_string(amount) + "', and valid date '" + std::to_string(year) +
        "', '" + std::to_string(month) + "', '" + std::to_string(day) +
        "' object") {

    WHEN("a new Item object is constructed") {

      Item iObj1{ident, description, amount, date};

      std::string tag = "tagName";

      AND_GIVEN("a tag called '" + tag + "'") {

        WHEN("the tag is added") {

          THEN("true is returned") {

            REQUIRE(iObj1.addTag(tag));

            AND_THEN("it will have one tag(s)") {
              REQUIRE(iObj1.numTags() == 1);

              AND_THEN("The item contains the tag '" + tag + "'") {

                REQUIRE(iObj1.containsTag(tag));

              } // AND_THEN

            } // AND_THEN

            AND_GIVEN("another tag with the same name, '" + tag + "'") {

              WHEN("adding the tag") {

                THEN("false is returned and the number of the Tags will not "
                     "change") {

                  REQUIRE_FALSE(iObj1.addTag(tag));
                  REQUIRE(iObj1.numTags() == 1);

                } // THEN

              } // WHEN

            } // AND_GIVEN

            std::string tag2 = "tag2";

            AND_GIVEN("another tag with a different name: '" + tag2 + "'") {

              WHEN("adding the tag") {

                THEN("true is returned and the number of the tags will be 2") {

                  REQUIRE(iObj1.addTag(tag2) == true);
                  REQUIRE(iObj1.numTags() == 2);

                  AND_THEN("The item contains the tag '" + tag + "'") {

                    REQUIRE(iObj1.containsTag(tag));

                  } // AND_THEN

                } // THEN

              } // WHEN

            } // AND_GIVEN

          } // THEN

        } // WHEN

      } // AND_GIVEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("Tags can be added to and deleted from a Item", "[item]") {

  GIVEN("the item identifier '" + ident + "', description '" + description +
        "', amount '" + std::to_string(amount) + "', and valid date '" + std::to_string(year) +
        "', '" + std::to_string(month) + "', '" + std::to_string(day) +
        "' object") {

    WHEN("a new Item object is constructed") {

      Item iObj1{ident, description, amount, date};

      std::string tag = "tagName";

      AND_GIVEN("a tag called '" + tag + "'") {

        WHEN("the tag is added") {

          THEN("true is returned") {

            REQUIRE(iObj1.addTag(tag));

            AND_THEN("it will have one tag(s)") {
              REQUIRE(iObj1.numTags() == 1);

              AND_THEN("The item contains the tag '" + tag + "'") {

                REQUIRE(iObj1.containsTag(tag));

              } // WHEN

              WHEN("deleting a non-existent entry with key 'blah'") {

                THEN("the Item will not change") {

                  REQUIRE_THROWS_AS(iObj1.deleteTag("blah"), std::out_of_range);
                  REQUIRE(iObj1.containsTag(tag));
                  REQUIRE(iObj1.numTags() == 1);

                } // THEN

              } // WHEN

              WHEN("deleting the added entry with tag '" + tag + "'") {

                THEN("the tags will be empty") {

                  REQUIRE(iObj1.deleteTag(tag));
                  REQUIRE(iObj1.numTags() == 0);

                } // THEN

              } // WHEN

            } // AND_THEN

          } // THEN

        } // WHEN

      } // AND_GIVEN

    } // WHEN

  } // GIVEN
} // SCENARIO
