//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// REQUIRES: std-at-least-c++23

// <ranges>

//   V models only input_range:
//     constexpr __outer_iterator begin();

//   V models forward_range:
//     constexpr auto begin() requires (!__simple_view<V>);
//     constexpr auto begin() const requires forward_range<const V>;

#include <algorithm>
#include <cassert>
#include <ranges>
#include <vector>

#include "test_range.h"
#include "types.h"

constexpr bool test() {
  std::vector<int> vector = {1, 2, 3, 4, 5, 6, 7, 8};
  auto chunked            = vector | std::views::chunk(3);
  auto const_chunked      = std::as_const(vector) | std::views::chunk(3);
  auto input_chunked      = input_span<int>(vector.data(), 8) | std::views::chunk(3);

  // Test `chunk_view.begin()` when V models only input_range
  {
    auto it = input_chunked.begin();
    assert(std::ranges::equal(*it, std::vector{1, 2, 3}));
    assert(std::ranges::equal(*++it, std::vector{4, 5, 6}));
    assert(std::ranges::equal(*++it, std::vector{7, 8}));
    assert(++it == input_chunked.end());
  }

  // Test `chunk_view.begin()` when V models forward_range
  {
    auto it = chunked.begin();
    assert(std::ranges::equal(*it, std::vector{1, 2, 3}));
    assert(std::ranges::equal(*++it, std::vector{4, 5, 6}));
    assert(std::ranges::equal(*++it, std::vector{7, 8}));
    assert(++it == chunked.end());
    auto const_it = const_chunked.begin();
    assert(std::ranges::equal(*const_it, std::vector{1, 2, 3}));
    assert(std::ranges::equal(*++const_it, std::vector{4, 5, 6}));
    assert(std::ranges::equal(*++const_it, std::vector{7, 8}));
    assert(++const_it == const_chunked.end());
  }

  return true;
}

int main(int, char**) {
  test();
  static_assert(test());

  return 0;
}
