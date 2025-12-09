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
// This file contains tests for creating and setting
// Date objects.

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/date.h"

SCENARIO("A date can be set", "[date]") {

  unsigned int year = 2024;
  unsigned int month = 12;
  unsigned int day = 25;

    GIVEN("a year '" + std::to_string(year) + "' and month '" +
              std::to_string(month) + "'" + "' and day '" +
              std::to_string(day) + "'") {

      WHEN("the date object is constructed year with those parameters") {
        Date dObj1 = Date(year, month, day);

        THEN("getting the year will return the expected value '" +
             std::to_string(year) + "'") {

          REQUIRE(dObj1.getYear() == year);

          AND_THEN("getting the month will return the expected value '" +
                   std::to_string(month) + "'") {

            REQUIRE(dObj1.getMonth() == month);

            AND_THEN("getting the day will return the expected value '" +
                     std::to_string(day) + "'") {

              REQUIRE(dObj1.getDay() == day);

            } // AND_THEN

          } // AND_THEN

          } // THEN

      } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("The < operator on Date evaluates its contents correctly", "[date]") {

  unsigned int year = 2024;
  unsigned int month = 12;
  unsigned int day = 25;


  GIVEN("a year '" + std::to_string(year) + "' and month '" +
        std::to_string(month) + "'" + "' and day '" + std::to_string(day) +
        "'") {

    AND_GIVEN("Two Date objects constructed with same paramenters") {

      Date dObj1 = Date(year, month, day);
      Date dObj2 = Date(year, month, day);

          THEN("getting the year will return the expected value '" +
                   std::to_string(year) + "'") {

            REQUIRE(dObj1.getYear() == year);
            REQUIRE(dObj2.getYear() == year);

            AND_THEN("getting the month will return the expected value '" +
                     std::to_string(month) + "'") {

              REQUIRE(dObj1.getMonth() == month);
              REQUIRE(dObj2.getMonth() == month);

              AND_THEN("getting the day will return the expected value '" +
                       std::to_string(day) + "'") {

                REQUIRE(dObj1.getDay() == day);
                REQUIRE(dObj2.getDay() == day);

              } // AND_THEN

              AND_THEN("The two date objects equal and not less than one or "
                       "the other") {
                REQUIRE_FALSE(dObj1 < dObj2);
                REQUIRE_FALSE(dObj2 < dObj1);
              } // AND_THEN

              auto day2 = day + 1;
              AND_GIVEN("A third date object set to a different a year '" +
                        std::to_string(year) + "' and month '" +
                        std::to_string(month) + "'" + "' and day '" +
                        std::to_string(day2) + "'") {
                Date dObj3 = Date(year, month, day2);
                AND_THEN(
                    "The first two objects are less than the third object") {
                  REQUIRE(dObj1 < dObj3);
                  REQUIRE(dObj2 < dObj3);
                  REQUIRE_FALSE(dObj3 < dObj2);
                  REQUIRE_FALSE(dObj3 < dObj1);
                } // AND_THEN
              } // AND_GIVEN

            } // AND_THEN

          } // THEN

        } // AND_GIVEN

      } // GIVEN

    } // SCENARIO

SCENARIO("The == operator on Date evaluates its contents correctly", "[date]") {

  unsigned int year = 2024;
  unsigned int month = 12;
  unsigned int day = 25;

  GIVEN("a year '" + std::to_string(year) + "' and month '" +
        std::to_string(month) + "'" + "' and day '" + std::to_string(day) +
        "'") {

    AND_GIVEN("Two Date objects constructed with those paramenters") {

      Date dObj1 = Date(year, month, day);
      Date dObj2 = Date(year, month, day);

            THEN("getting the year will return the expected value '" +
                     std::to_string(year) + "'") {

              REQUIRE(dObj1.getYear() == year);
              REQUIRE(dObj2.getYear() == year);

              AND_THEN("getting the month will return the expected value '" +
                       std::to_string(month) + "'") {

                REQUIRE(dObj1.getMonth() == month);
                REQUIRE(dObj2.getMonth() == month);

                AND_THEN("getting the day will return the expected value '" +
                         std::to_string(day) + "'") {

                  REQUIRE(dObj1.getDay() == day);
                  REQUIRE(dObj2.getDay() == day);

                } // AND_THEN

                AND_THEN("The two date objects are equal") {
                  REQUIRE(dObj1 == dObj2);
                } // AND_THEN

                auto day2 = day - 1;
                AND_GIVEN("A third date object set to a different a year '" +
                          std::to_string(year) + "' and month '" +
                          std::to_string(month) + "'" + "' and day '" +
                          std::to_string(day2) + "'") {
                  Date dObj3 = Date(year, month, day2);

                  AND_THEN("The third objects does not equal, the first two") {
                    REQUIRE_FALSE(dObj1 == dObj3);
                    REQUIRE_FALSE(dObj3 == dObj2);
                  } // AND_THEN
                } // AND_GIVEN

              } // AND_THEN

            } // THEN

          } // AND_GIVEN

        } // GIVEN

      } // SCENARIO

SCENARIO(
    "An properly formatted but invalid date can not be set from date string",
    "[date]") {

    unsigned int year = 2024;
    unsigned int month = 22;
    unsigned int day = 22;
    const std::string dateString = std::to_string(year) + "-" +
                                   std::to_string(month) + "-" +
                                   std::to_string(day);

    GIVEN("an invalid date string in the form of '" + dateString + "'") {

      WHEN("A date is constructed with an invalid dateString parameter") {
        THEN("An exception is thrown") {
          REQUIRE_THROWS(Date(dateString));
        } // THEN

      } // WHEN

    } // GIVEN

} // SCENARIO

SCENARIO(
    "An improperly formatted date can not be set from date string",
    "[date]") {

    const std::string dateString = "2024,11,10";

    GIVEN("an invalid date string in the form of '" + dateString + "'") {

      WHEN("A date is constructed with an  improperly formatted dateString parameter") {
        THEN("An exception is thrown") {
          REQUIRE_THROWS(Date(dateString));
        }

      } // WHEN

    } // GIVEN

} // SCENARIO
SCENARIO("A custom date can be set from a date string", "[date]") {


    unsigned int year = 2024;
    unsigned int month = 12;
    unsigned int day = 25;
    const std::string dateString = std::to_string(year) + "-" +
                                   std::to_string(month) + "-" +
                                   std::to_string(day);

    GIVEN("a date string in the form of '" + dateString + "'") {

      WHEN("A date object is constructed with that parameter") {
        Date dObj1 = Date(dateString);

          THEN("getting the year will return the expected value '" +
                   std::to_string(year) + "'") {

            REQUIRE(dObj1.getYear() == year);

            AND_THEN("getting the month will return the expected value '" +
                     std::to_string(month) + "'") {

              REQUIRE(dObj1.getMonth() == month);

              AND_THEN("getting the day will return the expected value '" +
                       std::to_string(day) + "'") {

                REQUIRE(dObj1.getDay() == day);

              } // AND_THEN

            } // AND_THEN

        } // THEN

      } // WHEN

  } // GIVEN

} // SCENARIO