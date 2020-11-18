/**
 * @file dimension.hpp
 * @author Haru-T (38246508+Haru-T@users.noreply.github.com)
 * @brief Represents dimensions that physical quantities have.
 * @version 0.1
 * @date 2020-11-18
 *
 * @copyright Copyright (c) 2020 Haru-T
 * This project is released under the MIT license.
 */

#ifndef CPP_QUANTITY_DIMENSION_H_
#define CPP_QUANTITY_DIMENSION_H_

#include <concepts>

namespace cpp_quantity {

/**
 * @brief Unit of dimensions.
 *
 * dimension<t, l, ...> represents T^(t / DIM_UNIT) L^(l / DIM_UNIT) ...
 */
constexpr std::ptrdiff_t DIM_UNIT = 60;

/**
 * @brief Struct representing dimensions of a physical quantity.
 *
 * @tparam T Dimension of time.
 * @tparam L Dimension of length.
 * @tparam M Dimension of mass.
 * @tparam I Dimension of electric current.
 * @tparam Th Dimension of thermodynamic temprature.
 * @tparam N Dimension of amount of substance.
 * @tparam J Dimension of luminous intensity.
 */
template <std::ptrdiff_t T = 0, std::ptrdiff_t L = 0, std::ptrdiff_t M = 0,
          std::ptrdiff_t I = 0, std::ptrdiff_t Th = 0, std::ptrdiff_t N = 0,
          std::ptrdiff_t J = 0>
struct dimension;

namespace concepts {
/**
 * @brief Concept of Dimension.
 *
 * @tparam T Type to be tested.
 */
template <class T>
concept dimension = std::same_as<
    T, cpp_quantity::dimension<T::time, T::length, T::mass, T::current,
                               T::temprature, T::amount, T::intensity>>;
} // namespace concepts

template <std::ptrdiff_t T, std::ptrdiff_t L, std::ptrdiff_t M,
          std::ptrdiff_t I, std::ptrdiff_t Th, std::ptrdiff_t N,
          std::ptrdiff_t J>
struct dimension {
    //! Dimension of time.
    static constexpr std::ptrdiff_t time = T;
    //! Dimension of length.
    static constexpr std::ptrdiff_t length = L;
    //! Dimension of mass.
    static constexpr std::ptrdiff_t mass = M;
    //! Dimension of electrical current.
    static constexpr std::ptrdiff_t current = I;
    //! Dimension of thermodynamic temperature.
    static constexpr std::ptrdiff_t temprature = Th;
    //! Dimension of amount of substance.
    static constexpr std::ptrdiff_t amount = N;
    //! Dimension of luminous intensity.
    static constexpr std::ptrdiff_t intensity = J;

    static_assert(concepts::dimension<dimension<T, L, M, I, Th, N, J>>);
};

/**
 * @brief Addition operator representing the constraint that operands must
 * have the same dimensions.
 *
 * @tparam D0 Type of the 1st operand. Must be a dimension.
 * @tparam D1 Type of the 2nd operand. Must be a dimension.
 * @return D0
 */
template <concepts::dimension D0, std::same_as<D0> D1>
constexpr D0 operator+(D0, D1) {
    return {};
}

/**
 * @brief Subtraction operator representing the constraint that operands
 * must have the same dimensions.
 *
 * @tparam D0 Type of the 1st operand. Must be a dimension.
 * @tparam D1 Type of the 2nd operand. Must be a dimension.
 * @return D0
 */
template <concepts::dimension D0, std::same_as<D0> D1>
constexpr D0 operator-(D0, D1) {
    return {};
}

/**
 * @brief Multiplication operator.
 *
 * @tparam D0 Type of the 1st operand. Must be a dimension.
 * @tparam D1 Type of the 2nd operand. Must be a dimension.
 * @return dimension<D0::time + D1::time, D0::length + D1::length,
 * D0::mass + D1::mass, D0::current + D1::current,
 * D0::temprature + D1::temprature, D0::amount + D1::amount,
 * D0::intensity + D1::intensity>
 */
template <concepts::dimension D0, concepts::dimension D1>
constexpr auto operator*(D0, D1)
    -> dimension<D0::time + D1::time, D0::length + D1::length,
                 D0::mass + D1::mass, D0::current + D1::current,
                 D0::temprature + D1::temprature, D0::amount + D1::amount,
                 D0::intensity + D1::intensity> {
    return {};
}

/**
 * @brief Division operator.
 *
 * @tparam D0 Type of the 1st operand. Must be a dimension.
 * @tparam D1 Type of the 2nd operand. Must be a dimension.
 * @return dimension<D0::time - D1::time, D0::length - D1::length,
 * D0::mass - D1::mass, D0::current - D1::current,
 * D0::temprature - D1::temprature, D0::amount - D1::amount,
 * D0::intensity - D1::intensity>
 */
template <concepts::dimension D0, concepts::dimension D1>
constexpr auto operator/(D0, D1)
    -> dimension<D0::time - D1::time, D0::length - D1::length,
                 D0::mass - D1::mass, D0::current - D1::current,
                 D0::temprature - D1::temprature, D0::amount - D1::amount,
                 D0::intensity - D1::intensity> {
    return {};
}

/**
 * @brief Equal operator.
 *
 * @tparam D0 Type of 1st operand.
 * @tparam D1 Type of 2nd operand.
 * @return true 1st and 2nd operands are the same dimension.
 * @return false 1st and 2nd operands are different dimensions.
 */
template <concepts::dimension D0, concepts::dimension D1>
constexpr bool operator==(D0, D1) {
    return std::same_as<D0, D1>;
}

} // namespace cpp_quantity

#endif