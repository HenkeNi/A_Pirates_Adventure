#pragma once
#include <type_traits>
#include <iterator>
#include <string_view>

// Integral type (ex: int, long, short)
template <typename T>
concept Integral = std::is_integral_v<T>;

// Floating point type (ex: float, double, long double)
template <typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

// Integral or floating point (can be any number type)
template <typename T>
concept Numeric = Integral<T> || FloatingPoint<T>;

template <typename T>
concept StringLike = std::is_convertible_v<T, std::string_view>;

// Signed
template <typename T>
concept Signed = std::is_signed_v<T>;

// Unsigned
template <typename T>
concept Unsigned = std::is_unsigned_v<T>;

// Integral constant (i.e., type that holds a constant value)
template <typename T>
concept IntegralConstant = std::is_integral_v<T> && requires { T::value; };

// Pointer
template <typename T>
concept Pointer = std::is_pointer_v<T>;

// Lvalue reference
template <typename T>
concept LvalueReference = std::is_lvalue_reference_v<T>;

// Rvalue reference
template <typename T>
concept RvalueReference = std::is_rvalue_reference_v<T>;

// Callable (i.e., can be called with Args...)
template <typename T, typename... Args>
concept Callable = std::is_invocable_v<T, Args...>;

// Same type (checks if two types are the same)
template <typename T, typename U>
concept SameType = std::is_same_v<T, U>;

// Derived from
template <typename T, typename Base>
concept DerivedFrom = std::is_base_of_v<Base, T> && !std::is_same_v<Base, T>; // decay?

// Default constructible (i.e., takes no arguments)
template <typename T>
concept DefaultConstructible = std::is_default_constructible_v<T>;

// Copy constructible
template <typename T>
concept CopyConstructible = std::is_copy_constructible_v<T>;

// Move constructible
template <typename T>
concept MoveConstructible = std::is_move_constructible_v<T>;

// Copy assignable
template <typename T>
concept CopyAssignable = std::is_copy_assignable_v<T>;

// Move assignable
template <typename T>
concept MoveAssignable = std::is_move_assignable_v<T>;

// Destructible (i.e., has a destructor)
template <typename T>
concept Destructible = std::is_destructible_v<T>;

// Move-constructible and copy-constructible
template <typename T>
concept CopyOrMoveConstructible = CopyConstructible<T> || MoveConstructible<T>;

// Equality comparable (can use operator==)
template <typename T, typename U>
concept EqualityComparable = std::is_same_v<decltype(std::declval<T>() == std::declval<U>()), bool>;

// Totally ordered (can be compared using <, >, <=, >=)
template <typename T, typename U>
concept TotallyOrdered = std::is_same_v<decltype(std::declval<T>() < std::declval<U>()), bool>&&
    std::is_same_v<decltype(std::declval<T>() > std::declval<U>()), bool>&&
    std::is_same_v<decltype(std::declval<T>() <= std::declval<U>()), bool>&&
    std::is_same_v<decltype(std::declval<T>() >= std::declval<U>()), bool>;

// Range (can be iterated over, e.g., std::vector, arrays, etc.)
template <typename T>
concept Range = requires(T t) {
    { std::begin(t) } -> std::forward_iterator;
    { std::end(t) } -> std::forward_iterator;
};

// String-like type
template <typename T>
concept StringConvertible = std::convertible_to<T, std::string_view>;

// Class or Struct
template <typename T>
concept CustomType = std::is_class_v<T>;

template <typename T, typename Type>
concept IsExactly = std::is_same_v<T, Type>;

template <typename T>
concept ComponentType = std::is_class_v<T> /*&& std::is_standard_layout_v<T> *//*&& std::is_trivially_copyable_v<T>*/ /*&& std::is_trivially_default_constructible_v<T>*/; // rename? since ComponentType already exist in component manager?!
//concept ComponentType = std::is_trivial_v<T> && std::is_standard_layout_v<T> && std::is_class_v<T>; // rename? since ComponentType already exist in component manager?!