/**
 * @file dimension.cpp
 * @author Haru-T (38246508+Haru-T@users.noreply.github.com)
 * @brief Test of dimension.hpp.
 * @version 0.1
 * @date 2020-11-18
 *
 * @copyright Copyright (c) 2020 Haru-T
 * This project is released under the MIT license.
 */

#include <cpp_quantity/dimension.hpp>

#include <catch2/catch.hpp>
#include <type_traits>

using namespace cpp_quantity;

template <class, class, class = std::void_t<>>
struct addable : std::false_type {};
template <class T, class U>
struct addable<T, U,
               std::void_t<decltype(std::declval<T>() + std::declval<U>())>>
    : std::true_type {};

template <class, class, class = std::void_t<>>
struct subtractable : std::false_type {};
template <class T, class U>
struct subtractable<
    T, U, std::void_t<decltype(std::declval<T>() - std::declval<U>())>>
    : std::true_type {};

TEST_CASE("dimension", "[dimension]") {
    SECTION("equality testing") {
        REQUIRE(dimension<1>{} == dimension<1>{});
        REQUIRE(dimension<-4>{} == dimension<-4>{});
        REQUIRE(dimension<1, 2, 3, 4, 5, 6, 7>{} ==
                dimension<1, 2, 3, 4, 5, 6, 7>{});
        REQUIRE(dimension<2>{} != dimension<3>{});
    }

    SECTION("valid add/subtract") {
        REQUIRE(dimension<1>{} + dimension<1>{} == dimension<1>{});
        REQUIRE(dimension<6, 5, 4, 3, 2, 1, 0>{} +
                    dimension<6, 5, 4, 3, 2, 1>{} ==
                dimension<6, 5, 4, 3, 2, 1, 0>{});

        REQUIRE(dimension<3>{} - dimension<3>{} == dimension<3>{});
        REQUIRE(dimension<1, -1, 2, -3, 5, -8, 13>{} -
                    dimension<1, -1, 2, -3, 5, -8, 13>{} ==
                dimension<1, -1, 2, -3, 5, -8, 13>{});
    }

    SECTION("invalid add/subtract") {
        REQUIRE(!addable<dimension<1>, dimension<-1>>::value);
        REQUIRE(!subtractable<dimension<1>, dimension<-1>>::value);
    }

    SECTION("multiplication/division") {
        REQUIRE(dimension<1>{} * dimension<2>{} == dimension<3>{});
        REQUIRE(dimension<1, 2, 3, 5, 8, 13, 21>{} *
                    dimension<1, -1, 2, -2, 3, -3, 4>{} ==
                dimension<1 + 1, 2 - 1, 3 + 2, 5 - 2, 8 + 3, 13 - 3, 21 + 4>{});

        REQUIRE(dimension<3>{} / dimension<2>{} == dimension<1>{});
        REQUIRE(dimension<>{} / dimension<5>{} == dimension<-5>{});
    }
}