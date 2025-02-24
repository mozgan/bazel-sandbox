#ifndef _LIB_UTILITY_STR_HPP_
#define _LIB_UTILITY_STR_HPP_

#include <charconv>
#include <string_view>

#include "third_party/expected.hpp"
using tl::expected;
using tl::make_unexpected;

namespace details {

template <typename T>
  requires std::integral<T> || std::floating_point<T>
[[nodiscard]] constexpr auto convert_from_chars(const std::string_view& input,
                                                int base = 10) noexcept
    -> expected<T, std::string> {
  T value{};
  std::from_chars_result result{};

  if constexpr (std::integral<T>)
    result = std::from_chars(input.cbegin(), input.cend(), value, base);
  else
    result = std::from_chars(input.cbegin(), input.cend(), value);

  if (result.ec == std::errc{}) return value;

  return make_unexpected(
      "String Convertion Error: " + std::make_error_code(result.ec).message() +
      " [" + std::string(input) + "]");
}

}  // namespace details

template <typename T, typename S>
  requires std::integral<T> && std::convertible_to<S, std::string_view>
[[nodiscard]] constexpr auto string_to(S str, int base = 10) noexcept
    -> expected<T, std::string> {
  return details::convert_from_chars<T>(std::string_view{str}, base);
}

template <typename T, typename S>
  requires std::floating_point<T> && std::convertible_to<S, std::string_view>
[[nodiscard]] constexpr auto string_to(S str) noexcept
    -> expected<T, std::string> {
  return details::convert_from_chars<T>(std::string_view{str});
}

#endif