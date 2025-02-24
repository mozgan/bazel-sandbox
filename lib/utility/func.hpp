#ifndef _LIB_UTILITY_FUNC_HPP_
#define _LIB_UTILITY_FUNC_HPP_

#include <memory>
#include <new>
#include <type_traits>
#include <utility>

template <typename T>
void clear(T& value) noexcept {
  if constexpr (std::is_pointer_v<T>) {
    if (value != nullptr) clear(*value);
  } else {
    using ValueType = std::remove_const_t<T>;
    ValueType& ref = const_cast<ValueType&>(value);

    if constexpr (std::is_const_v<T>) {
      if constexpr (!std::is_move_constructible_v<ValueType>) {
        std::destroy_at(&ref);
        ::new (&ref) ValueType{};
      } else if constexpr (std::is_swappable_v<ValueType>) {
        ValueType empty{};
        std::swap(ref, empty);
      } else {
        ValueType empty{};
        std::swap(ref, empty);
      }
    } else {
      if constexpr (std::is_move_constructible_v<ValueType>) {
        ref = ValueType{};
      } else if constexpr (std::is_swappable_v<ValueType>) {
        ValueType empty{};
        std::swap(ref, empty);
      } else {
        std::destroy_at(&ref);
        ::new (&ref) ValueType{};
      }
    }
  }
}

#endif