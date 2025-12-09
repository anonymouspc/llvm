//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// REQUIRES: std-at-least-c++23

// <ranges>

// Test the libc++ extension that std::ranges::chunk_view::begin is marked as [[nodiscard]].

#include <ranges>
#include <utility>

void test() {
  int range[6] = {1, 3, 4, 6, 7, 9};
  auto view    = range | std::views::chunk(3);

  // clang-format off
  view.begin(); // expected-warning {{ignoring return value of function declared with 'nodiscard' attribute}}
  std::as_const(view).begin(); // expected-warning {{ignoring return value of function declared with 'nodiscard' attribute}}
  // clang-format on
}
