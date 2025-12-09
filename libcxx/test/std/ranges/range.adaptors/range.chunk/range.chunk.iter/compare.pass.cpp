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
  std::vector<int> vector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  // Test `chunk_view.__iterator.operator<=>`
  {
    auto view = vector | std::views::chunk(5);
    assert(view.begin() < view.end());
    assert(++view.begin() < view.end());
    assert(view.begin() + 3 == view.end());
    assert(view.begin() + 3 > view.end() - 1);
    assert((view.begin() <=> view.end()) == std::strong_ordering::less);
    assert((view.begin() + 1 <=> view.end() - 2) == std::strong_ordering::equal);
    assert((view.end() <=> view.begin()) == std::strong_ordering::greater);
  }

  return true;
}

int main(int, char**) {
  test();
  static_assert(test());

  return 0;
}
