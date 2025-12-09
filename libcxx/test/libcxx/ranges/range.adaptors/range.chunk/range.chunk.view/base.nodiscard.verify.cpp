//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// REQUIRES: std-at-least-c++23

// <ranges>

// Test the libc++ extension that std::ranges:chunk_view::base is marked as [[nodiscard]].

#include <ranges>
#include <utility>

void test() {
  int range[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto view = range | std::views::chunk(3);

  // clang-format off
  view.base(); // expected-warning {{ignoring return value of function declared with 'nodiscard' attribute}}
  std::as_const(view).base(); // expected-warning {{ignoring return value of function declared with 'nodiscard' attribute}}
  std::move(std::as_const(view)).base(); // expected-warning {{ignoring return value of function declared with 'nodiscard' attribute}}
  std::move(view).base(); // expected-warning {{ignoring return value of function declared with 'nodiscard' attribute}}
  // clang-format on
}
