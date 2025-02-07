#ifndef IEME_PARSE_UTILITIES_HPP
#define IEME_PARSE_UTILITIES_HPP

#include <optional>
#include <string_view>
#include <utility>


namespace ieme {
namespace parse_utilities {


enum class sign : bool {
  negative,
  positive,
};


struct floating_point_string_scan_results {
  int base = 10;
  std::string_view whole;
  std::string_view fractional;
  int fractional_precision = 0;
  sign exponent_sign = sign::positive;
  std::string_view exponent;
};

constexpr std::optional<floating_point_string_scan_results>
scan_floating_point_string(std::string_view string) noexcept;

constexpr bool is_valid_digit_sequence(std::string_view sequence,
                                       int base) noexcept;

template <typename Int>
constexpr Int digit_sequence_to_int(std::string_view sequence,
                                    Int base) noexcept;


// =============================================================================


constexpr std::optional<floating_point_string_scan_results>
scan_floating_point_string(std::string_view const string) noexcept
{
  if (string.size() < 2)
    return std::nullopt;

  auto remaining_string = string;

  auto const last_pos = [&]() { return remaining_string.size() - 1; };

  floating_point_string_scan_results results;

  if (remaining_string.size() > 2)
  {
    auto const first_two = remaining_string.substr(0, 2);

    if (first_two == "0x" || first_two == "0X")
    {
      remaining_string.remove_prefix(2);
      results.base = 16;
    }
  }

  auto const radix_separator_pos = remaining_string.find('.');

  results.whole = remaining_string.substr(0, radix_separator_pos);

  auto const no_whole = results.whole.empty();

  if (!(no_whole || is_valid_digit_sequence(results.whole, results.base)))
    return std::nullopt;

  if (radix_separator_pos == last_pos())
  {
    if (results.base == 10)
      return results;

    return std::nullopt;
  }

  auto const no_radix_separator = radix_separator_pos == std::string_view::npos;

  if (!no_radix_separator)
    remaining_string.remove_prefix(radix_separator_pos + 1);

  auto const exponent_separator_pos = [&]() {
    auto const [lower, upper] = (results.base == 10) ? std::make_pair('e', 'E')
                                                     : std::make_pair('p', 'P');

    if (auto const lower_pos = remaining_string.find(lower);
        lower_pos != std::string_view::npos)
      return lower_pos;

    return remaining_string.find(upper);
  }();

  if (exponent_separator_pos == last_pos())
    return std::nullopt;

  auto const no_exponent_separator
    = exponent_separator_pos == std::string_view::npos;

  if (no_radix_separator && no_exponent_separator)
    return std::nullopt;

  if (results.base == 16 && no_exponent_separator)
    return std::nullopt;

  results.fractional = remaining_string.substr(0, exponent_separator_pos);

  auto const no_fractional = results.fractional.empty();

  if (no_whole && no_fractional)
    return std::nullopt;

  if (!(no_fractional
        || is_valid_digit_sequence(results.fractional, results.base)))
    return std::nullopt;

#ifdef __GNUC__
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

  results.fractional_precision = [&]() {
    auto result = 0U;

    for (auto const digit : results.fractional)
      if (digit != '\'')
        ++result;

    return result;
  }();

#ifdef __GNUC__
#  pragma GCC diagnostic pop
#endif

  if (no_exponent_separator)
    return results;

  remaining_string.remove_prefix(exponent_separator_pos + 1);

  switch (remaining_string.front())
  {
    case '-':
      results.exponent_sign = sign::negative;
      [[fallthrough]];
    case '+':
      remaining_string.remove_prefix(1);
      break;
    default:
      break;
  }

  results.exponent = remaining_string;

  if (!is_valid_digit_sequence(results.exponent, 10))
    return std::nullopt;

  return results;
}

constexpr bool is_valid_digit_sequence(std::string_view const sequence,
                                       int const base) noexcept
{
  auto digit_preceeded = false;

  for (auto const c : sequence)
  {
    if (c == '\'')
    {
      if (!digit_preceeded)
        return false;

      digit_preceeded = false;
    }
    else
    {
      if ((c < '0' || c > '9')
          && (((c < 'a' || c > 'f') && (c < 'A' || c > 'F')) || base != 16))
        return false;

      digit_preceeded = true;
    }
  }

  return digit_preceeded;
}

template <typename Int>
constexpr Int digit_sequence_to_int(std::string_view const sequence,
                                    Int const base) noexcept
{
  auto result = _0<Int>;
  auto base_power = _1<Int>;

  for (auto it = sequence.rbegin(); it != sequence.rend(); ++it)
  {
    if (*it == '\'')
      continue;

    auto const digit_as_int = [&]() {
      if (*it >= 'A' && *it <= 'F')
        return static_cast<Int>(*it - 'A' + 10);

      if (*it >= 'a' && *it <= 'f')
        return static_cast<Int>(*it - 'a' + 10);

      return static_cast<Int>(*it - '0');
    }();

    result += digit_as_int * base_power;
    base_power *= base;
  }

  return result;
}


}; // namespace parse_utilities
}; // namespace ieme


#endif
