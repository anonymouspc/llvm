//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// REQUIRES: std-at-least-c++23

// XFAIL: msvc

// <ranges>

// This test ensures that we use `[[no_unique_address]]` in `chunk_view`.

#include <cstddef>
#include <ranges>
#include <string>
#include <type_traits>

#include "test_iterators.h"
#include "test_range.h"

using input_view = std::views::all_t<test_range<cpp20_input_iterator>>;
static_assert(std::ranges::input_range<input_view> && !std::ranges::forward_range<input_view>);

struct forward_view : std::ranges::view_base {
  std::string* begin() const;
  std::string* end() const;
};
static_assert(std::ranges::forward_range<forward_view>);
static_assert(std::is_reference_v<std::ranges::range_reference_t<forward_view>>);

template <class View>
struct Test {
  [[no_unique_address]] View view;
  unsigned char pad;
};

using CV1 = std::ranges::chunk_view<input_view>;
// Expected CV1 (with View == input) layout:
// [[no_unique_address]] _View __base_                                         // offset: 0
// [[no_unique_address]] range_difference_t<_View> __n_                        // offset: sizeof(std::ptrdiff_t)
// [[no_unique_address]] range_difference_t<_View> __remainder_                // offset: sizeof(std::ptrdiff_t)
// [[no_unique_address]] __non_propagating_cache<iterator_t<_View>> __current_ // offset: ?
// TODO: hmmm I'm a new C++ learner (having been exposed to C++ 2 years) 
//       and I do not know about the memory layout here too...
//       What is the layout like?

using CV2 = std::ranges::chunk_view<forward_view>;
// Expected CV2 (with View >= forward) layout:
// [[no_unique_address]] _View __base_             // offset: 0
// [[no_unique_address]] range_difference_t<_View> // offset: sizeof(std::ptrdiff_t)
static_assert(sizeof(CV2) == sizeof(std::ptrdiff_t));
static_assert(sizeof(Test<CV2>) == sizeof(std::ptrdiff_t) * 2);
