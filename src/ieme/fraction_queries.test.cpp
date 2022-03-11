#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <ieme/fraction_queries.hpp>

#include <ieme/fraction_literals.hpp>


using namespace ieme;
using namespace ieme::fraction_literals;


TEST_CASE("A fraction can be queried about whether or not it's a defined value",
          "[fraction]")
{
  REQUIRE(is_defined(10 / 5_fr));
  REQUIRE_FALSE(is_undefined(10 / 5_fr));

  REQUIRE_FALSE(is_defined(10 / 0_fr));
  REQUIRE(is_undefined(10 / 0_fr));
}

TEST_CASE("A fraction's sign can be queried", "[fraction]")
{
  REQUIRE(is_positive(12 / 32_fr));
  REQUIRE(is_non_negative(12 / 32_fr));
  REQUIRE_FALSE(is_zero(12 / 32_fr));
  REQUIRE_FALSE(is_non_positive(12 / 32_fr));
  REQUIRE_FALSE(is_negative(12 / 32_fr));

  REQUIRE_FALSE(is_positive(-5 / 2_fr));
  REQUIRE_FALSE(is_non_negative(-5 / 2_fr));
  REQUIRE_FALSE(is_zero(-5 / 2_fr));
  REQUIRE(is_non_positive(-5 / 2_fr));
  REQUIRE(is_negative(-5 / 2_fr));

  REQUIRE_FALSE(is_positive(0 / 1_fr));
  REQUIRE(is_non_negative(0 / 1_fr));
  REQUIRE(is_zero(0 / 1_fr));
  REQUIRE(is_non_positive(0 / 1_fr));
  REQUIRE_FALSE(is_negative(0 / 1_fr));
}

TEST_CASE("A fraction can be queried about whether or not it's an integer",
          "[fraction]")
{
  REQUIRE(is_integer(4 / 1_fr));
  REQUIRE_FALSE(is_integer(5 / 2_fr));
}

TEST_CASE("A fraction can be queried about whether or not it's a unit fraction",
          "[fraction]")
{
  REQUIRE(is_unit_fraction(1 / 2_fr));
  REQUIRE_FALSE(is_unit_fraction(3 / 4_fr));
}

TEST_CASE("A fraction can be queried about whether or not it's reduced",
          "[fraction]")
{
  REQUIRE(is_reduced_ignore_signs(3 / 4_fr));
  REQUIRE(is_reduced(3 / 4_fr));

  REQUIRE(is_reduced_ignore_signs(-3 / -4_fr));
  REQUIRE_FALSE(is_reduced(-3 / -4_fr));

  REQUIRE_FALSE(is_reduced_ignore_signs(2 / 4_fr));
  REQUIRE_FALSE(is_reduced(2 / 4_fr));
}

TEST_CASE("A fraction can be queried about whether or not it's proper",
          "[fraction]")
{
  REQUIRE(is_proper(3 / 4_fr));
  REQUIRE_FALSE(is_improper(3 / 4_fr));

  REQUIRE_FALSE(is_proper(3 / 2_fr));
  REQUIRE(is_improper(3 / 2_fr));
}

TEST_CASE("Two raw fractions can be identically compared", "[raw_fraction]")
{
  REQUIRE(are_identical(-7 / 15_fr, -7 / 15_fr));
  REQUIRE_FALSE(are_different(-7 / 15_fr, -7 / 15_fr));

  REQUIRE_FALSE(are_identical(-7 / 15_fr, 7 / -15_fr));
  REQUIRE(are_different(-7 / 15_fr, 7 / -15_fr));
}
