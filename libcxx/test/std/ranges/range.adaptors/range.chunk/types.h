//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef TEST_STD_RANGES_RANGE_ADAPTORS_RANGE_CHUNK_TYPES_H
#define TEST_STD_RANGES_RANGE_ADAPTORS_RANGE_CHUNK_TYPES_H

#include <iterator>
#include <ranges>
#include <vector>

// input_span

template <class T>
struct input_span : std::span<T> {
  struct iterator : std::span<T>::iterator {
    using iterator_concept = std::input_iterator_tag;
    constexpr iterator()   = default;
    constexpr iterator(std::span<T>::iterator i) : std::span<T>::iterator(i) {}
    constexpr auto operator*() const { return std::span<T>::iterator::operator*(); }
    friend constexpr auto operator+(iterator, auto)      = delete;
    friend constexpr auto operator+(auto, iterator)      = delete;
    friend constexpr auto operator-(iterator, auto)      = delete;
    friend constexpr auto operator-(auto, iterator) = delete;
    friend constexpr iterator& operator++(iterator& self) {
      ++static_cast<std::span<T>::iterator&>(self);
      return self;
    }
    friend constexpr void operator++(iterator& self, int) { ++self; }
    friend constexpr iterator& operator--(iterator&) = delete;
    friend constexpr void operator--(iterator&, int) = delete;
  };
  
  using std::span<T>::span;
  constexpr iterator begin() { return iterator(std::span<T>::begin()); }
  constexpr iterator end() { return iterator(std::span<T>::end()); }
};

template <class T>
inline constexpr bool std::ranges::enable_view<input_span<T>> = true;

static_assert( std::ranges::input_range<input_span<int>> &&
              !std::ranges::forward_range<input_span<int>> && 
               std::ranges::view<input_span<int>>);

// // not_sized_view

// template <class View>
//   requires std::ranges::random_access_range<View> &&
//            std::ranges::view<View>
// struct not_sized_view : View, std::ranges::view_interface<not_sized_view<View>> {
//   template <class Iterator>
//   struct not_sized_iterator : Iterator {
//     using iterator_concept = std::bidirectional_iterator_tag;
//     constexpr not_sized_iterator()   = default;
//     constexpr not_sized_iterator(Iterator i) : Iterator(i) {}
//     friend constexpr void operator-(not_sized_iterator, not_sized_iterator) = delete;
//     friend constexpr not_sized_iterator& operator++(not_sized_iterator& self) {
//       self.Iterator::operator++();
//       return self;
//     }
//     friend constexpr not_sized_iterator operator++(not_sized_iterator& self, int) { return ++self; }
//     friend constexpr not_sized_iterator& operator--(not_sized_iterator& self) {
//       self.Iterator::operator--();
//       return self;
//     }
//     friend constexpr not_sized_iterator operator--(not_sized_iterator& self, int) { return --self; }
//   };

//   constexpr std::bidirectional_iterator auto begin(this auto&& self) { return iterator(self.View::begin()); }
//   constexpr std::bidirectional_iterator auto end(this auto&& self) { return iterator(self.View::end()); }
//   constexpr auto size() const = delete;
// };

// template <std::ranges::view View>
// not_sized_view(View) -> not_sized_view<View>;

// template <std::ranges::view View>
// inline constexpr bool std::ranges::enable_view<not_sized_view<View>> = true;

// template <std::ranges::view View>
// inline constexpr bool std::ranges::disable_sized_range<not_sized_view<View>> = true;

#endif
