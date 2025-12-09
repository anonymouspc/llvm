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
//     constexpr default_sentinel_t end();

//   V moduels forward_range:
//     constexpr auto end() requires (!__simple_view<V>);
//     constexpr auto end() const requires forward_range<const V>;


#include <algorithm>
#include <cassert>
#include <concepts>
#include <iterator>
#include <ranges>
#include <vector>

#include "test_range.h"
#include "types.h"

constexpr bool test() {
  std::vector     vector             = {1, 2, 3, 4, 5, 6, 7, 8};
  std::span<int>  random_access_view = {vector.data(), 8};
  input_span<int> input_view         = {vector.data(), 8};

  // Test `chunk_view.end()` when V models only input_range
  {
    auto chunked = input_view | std::views::chunk(3);
    [[maybe_unused]] std::same_as<std::default_sentinel_t> auto it = chunked.end();
  }
  
  // Test `chunk_view.end()` when V models forward_range
  {
    auto chunked = random_access_view | std::views::chunk(3);
    std::random_access_iterator auto it = chunked.end();
    assert(std::ranges::equal(*--it, std::vector{7, 8})); 
    assert(std::ranges::equal(*--it, std::vector{4, 5, 6}));
    assert(std::ranges::equal(*--it, std::vector{1, 2,3 }));
    assert(it == chunked.begin());
    auto const_chunked = std::as_const(random_access_view) | std::views::chunk(3);
    std::random_access_iterator auto const_it = const_chunked.end();
    assert(std::ranges::equal(*--const_it, std::vector{7, 8}));
    assert(std::ranges::equal(*--const_it, std::vector{4, 5, 6}));
    assert(std::ranges::equal(*--const_it, std::vector{1, 2, 3}));
    assert(const_it == const_chunked.begin());
  }

  return true;
}

int main(int, char**) {
  test();
  static_assert(test());

  return 0;
}
