//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: c++03, c++11, c++14, c++17

// std::views::chunk

#include <ranges>

#include <algorithm>
#include <cassert>
#include <vector>

#include "test_range.h"

constexpr bool test() {
  std::vector<int> vector = {1, 2, 3, 4, 5, 6, 7, 8};

  // Test `chunk_view.__iterator.operator++`
  {
    auto view = vector | std::views::chunk(2);
    assert(std::ranges::equal(*(++view.begin()), std::vector{3, 4}));
  }

  // Test `chunk_view.__iterator.operator+`
  {
    auto view = vector | std::views::chunk(3);
    assert(view.begin() + 3 == view.end());
    assert((view.begin() += 3) == view.end());
    assert(std::ranges::equal(*(view.begin() + 2), std::vector{7, 8}));
  }

  return true;
}

int main(int, char**) {
  test();
  static_assert(test());

  return 0;
}