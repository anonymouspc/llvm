//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// REQUIRES: std-at-least-c++23

// <ranges>

// Test the libc++ extension that std::ranges::chunk::iterator<Const>::iter_move is marked as [[nodiscard]].

#include <ranges>
#include <utility>

void test() {
  long range[2] = {0L, 2L};
  auto view     = range | std::views::chunk(1);

  // clang-format off
  std::ranges::iter_move(view.begin()); // expected-warning {{ignoring return value of function declared with 'nodiscard' attribute}}
  std::ranges::iter_move(std::as_const(view).begin()); // expected-warning {{ignoring return value of function declared with 'nodiscard' attribute}}
  // clang-format on
}
