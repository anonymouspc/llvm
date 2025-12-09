//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// REQUIRES: std-at-least-c++23

// <ranges>

//   constexpr V base() const& requires copyy_constructible<V>;
//   constexpr V base() &&;

#include <array>
#include <cassert>
#include <concepts>
#include <ranges>
#include <span>
#include <utility>

#include "test_range.h"

constexpr bool test() {
  std::array array = {1, 2, 3, 4, 5, 6, 7, 8};
  std::span<int> view = {array.data(), 8};

  // Test `chunk_view.base()`
  {
    auto chunked = view | std::views::chunk(3);
    std::same_as<std::span<int>::iterator> decltype(auto) begin = chunked.begin().base();
    std::same_as<std::span<int>::iterator> decltype(auto) end = chunked.end().base();
    assert(begin == view.begin());
    assert(end == view.end());

    auto const_chunked = std::as_const(view) | std::views::chunk(4);
    std::same_as<std::span<int>::iterator> decltype(auto) const_begin = const_chunked.begin().base();
    std::same_as<std::span<int>::iterator> decltype(auto) const_end = const_chunked.end().base();
    assert(const_begin == std::as_const(view).begin());
    assert(const_end == std::as_const(view).end());
  }

  return true;
}

int main(int, char**) {
  test();
  static_assert(test());

  return 0;
}
