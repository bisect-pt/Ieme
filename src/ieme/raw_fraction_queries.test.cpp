#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <ieme/raw_fraction_queries.hpp>


using namespace ieme;


TEST_CASE(
  "A raw fraction can be queried about whether or not it's a defined value",
  "[raw_fraction]")
{
  auto const rf1 = raw_fraction<int>(10, 5);

  REQUIRE(is_defined(rf1));
  REQUIRE_FALSE(is_undefined(rf1));

  auto const rf2 = raw_fraction(-5, 2);

  REQUIRE(is_defined(rf2));
  REQUIRE_FALSE(is_undefined(rf2));

  auto const rf3 = raw_fraction<int>(0, 1);

  REQUIRE(is_defined(rf3));
  REQUIRE_FALSE(is_undefined(rf3));

  auto const rf4 = raw_fraction<int>(1, 0);

  REQUIRE_FALSE(is_defined(rf4));
  REQUIRE(is_undefined(rf4));
}

TEST_CASE("A raw fraction's sign can be queried", "[raw_fraction]")
{
  auto const rf1 = raw_fraction(12, 32);

  REQUIRE(is_positive(rf1));
  REQUIRE(is_non_negative(rf1));
  REQUIRE_FALSE(is_zero(rf1));
  REQUIRE_FALSE(is_non_positive(rf1));
  REQUIRE_FALSE(is_negative(rf1));

  auto const rf2 = raw_fraction(-5, 2);

  REQUIRE_FALSE(is_positive(rf2));
  REQUIRE_FALSE(is_non_negative(rf2));
  REQUIRE_FALSE(is_zero(rf2));
  REQUIRE(is_non_positive(rf2));
  REQUIRE(is_negative(rf2));

  auto const rf3 = raw_fraction<int>(0, 1);

  REQUIRE_FALSE(is_positive(rf3));
  REQUIRE(is_non_negative(rf3));
  REQUIRE(is_zero(rf3));
  REQUIRE(is_non_positive(rf3));
  REQUIRE_FALSE(is_negative(rf3));

  auto const rf4 = raw_fraction<int>(1, 0);

  REQUIRE_FALSE(is_positive(rf4));
  REQUIRE_FALSE(is_non_negative(rf4));
  REQUIRE_FALSE(is_zero(rf4));
  REQUIRE_FALSE(is_non_positive(rf4));
  REQUIRE_FALSE(is_negative(rf4));
}

TEST_CASE("A raw fraction can be queried about whether or not it's an integer",
          "[raw_fraction]")
{
  auto const rf1 = raw_fraction<int>(10, 5);

  REQUIRE(is_integer(rf1));

  auto const rf2 = raw_fraction(-5, 2);

  REQUIRE_FALSE(is_integer(rf2));

  auto const rf3 = raw_fraction<int>(0, 1);

  REQUIRE(is_integer(rf3));

  auto const rf4 = raw_fraction<int>(1, 0);

  REQUIRE_FALSE(is_integer(rf4));
}

TEST_CASE(
  "A raw fraction can be queried about whether or not it's a unit fraction",
  "[raw_fraction]")
{
  auto const rf1 = raw_fraction<int>(5, 10);

  REQUIRE(is_unit_fraction(rf1));

  auto const rf2 = raw_fraction(-5, 2);

  REQUIRE_FALSE(is_unit_fraction(rf2));

  auto const rf3 = raw_fraction<int>(0, 1);

  REQUIRE_FALSE(is_unit_fraction(rf3));

  auto const rf4 = raw_fraction<int>(1, 0);

  REQUIRE_FALSE(is_unit_fraction(rf4));
}

TEST_CASE("A raw fraction can be queried about whether or not it's reduced",
          "[raw_fraction]")
{
  auto const rf1 = raw_fraction(3, 4);

  REQUIRE(is_reduced_ignore_signs(rf1));
  REQUIRE(is_reduced(rf1));

  auto const rf2 = raw_fraction(-5, 2);

  REQUIRE(is_reduced_ignore_signs(rf2));
  REQUIRE(is_reduced(rf2));

  auto const rf3 = raw_fraction(-3, -4);

  REQUIRE(is_reduced_ignore_signs(rf3));
  REQUIRE_FALSE(is_reduced(rf3));

  auto const rf4 = raw_fraction(6, 8);

  REQUIRE_FALSE(is_reduced_ignore_signs(rf4));
  REQUIRE_FALSE(is_reduced(rf4));

  auto const rf5 = raw_fraction(-6, -8);

  REQUIRE_FALSE(is_reduced_ignore_signs(rf5));
  REQUIRE_FALSE(is_reduced(rf5));
}

TEST_CASE("A raw fraction can be queried about whether or not it's proper",
          "[raw_fraction]")
{
  auto const rf1 = raw_fraction(3, 4);

  REQUIRE(is_proper(rf1));
  REQUIRE_FALSE(is_improper(rf1));

  auto const rf2 = raw_fraction(-3, 4);

  REQUIRE(is_proper(rf2));
  REQUIRE_FALSE(is_improper(rf2));

  auto const rf3 = raw_fraction(3, -4);

  REQUIRE(is_proper(rf3));
  REQUIRE_FALSE(is_improper(rf3));

  auto const rf4 = raw_fraction(-3, -4);

  REQUIRE(is_proper(rf4));
  REQUIRE_FALSE(is_improper(rf4));

  auto const rf5 = raw_fraction(5, 4);

  REQUIRE_FALSE(is_proper(rf5));
  REQUIRE(is_improper(rf5));

  auto const rf6 = raw_fraction(-5, 4);

  REQUIRE_FALSE(is_proper(rf6));
  REQUIRE(is_improper(rf6));

  auto const rf7 = raw_fraction(5, -4);

  REQUIRE_FALSE(is_proper(rf7));
  REQUIRE(is_improper(rf7));

  auto const rf8 = raw_fraction(-5, -4);

  REQUIRE_FALSE(is_proper(rf8));
  REQUIRE(is_improper(rf8));
}

TEST_CASE("Two raw fractions can be identically compared", "[raw_fraction]")
{
  auto const rf1 = raw_fraction(3, 4);
  auto const rf2 = raw_fraction(-3, 4);
  auto const rf3 = raw_fraction(3, -4);
  auto const rf4 = raw_fraction(-3, -4);

  REQUIRE(are_identical(rf1, rf1));
  REQUIRE_FALSE(are_different(rf1, rf1));

  REQUIRE_FALSE(are_identical(rf1, rf2));
  REQUIRE(are_different(rf1, rf2));

  REQUIRE_FALSE(are_identical(rf1, rf3));
  REQUIRE(are_different(rf1, rf3));

  REQUIRE_FALSE(are_identical(rf1, rf4));
  REQUIRE(are_different(rf1, rf4));

  REQUIRE_FALSE(are_identical(rf2, rf3));
  REQUIRE(are_different(rf2, rf3));

  REQUIRE_FALSE(are_identical(rf2, rf4));
  REQUIRE(are_different(rf2, rf4));

  REQUIRE_FALSE(are_identical(rf3, rf4));
  REQUIRE(are_different(rf3, rf4));
}
