//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// REQUIRES: std-at-least-c++23

// std::views::chunk

#include <ranges>

#include <algorithm>
#include <cassert>
#include <vector>

#include "test_range.h"

constexpr bool test() {
  std::vector<int> full_vector  = {1, 1, 1, 2, 2, 2, 3, 3};
  std::vector<int> empty_vector = {};

  // Test `chunk_view.begin()`
  {
    auto view = full_vector | std::views::chunk(3);
    auto it   = view.begin();
    assert(std::ranges::equal(*it, std::vector{1, 1, 1}));
    assert(std::ranges::equal(*++it, std::vector{2, 2, 2}));
    assert(std::ranges::equal(*++it, std::vector{3, 3})); // The last chunk has only 2 elements.
    assert(++it == view.end());                           // Reaches end.

    view = full_vector | std::views::chunk(5);
    it   = view.begin();
    assert(std::ranges::equal(*it, std::vector{1, 1, 1, 2, 2}));
    assert(std::ranges::equal(*++it, std::vector{2, 3, 3}));
  }

  // Test `empty_chunk_view.begin()`
  {
    auto view = empty_vector | std::views::chunk(3);
    assert(view.size() == 0);
    assert(view.begin() == view.end());
  }

  // Test `small_view_with_big_chunk.begin()`
  {
    auto view = full_vector | std::views::chunk(314159);
    assert(view.size() == 1);
    assert(std::ranges::equal(*view.begin(), full_vector));
    assert(++view.begin() == view.end());
  }

  return true;
}

int main(int, char**) {
  test();
  static_assert(test());

  return 0;
}
