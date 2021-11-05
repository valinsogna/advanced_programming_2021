#include <array> //Since C++11, in standard type
#include <iostream>
//Two template var:
// template <class T, std::size_t N> size must be know at compile time like static array (and must be const)
// struct array;

//They live in stack and do not return the addressto the first element!
//You can pass them by reference
template <typename T, std::size_t N>
void print_array_two(const std::array<T, N>& a);

template <typename T>
void print_array_one(const T& a);

int main() {
  std::array<int, 4> a{1, 2, 3, 4};
  std::array<int, 4> b{a};  // I can copy element-wise from another std::array 
                            // this is not possible with plain built-in arrays
  // auto b = a 
  b = a;
  for (auto& x : a) //range based for loop like Python
    std::cout << x << " ";
  std::cout << std::endl;

  for (auto x : b)
    std::cout << x << " ";
  std::cout << std::endl;

  a[0] = 0;  // same subscripting operator without bound checking

  for (const auto x : a)
    std::cout << x << " ";
  std::cout << std::endl;

  for (const auto x : b)
    std::cout << x << " ";
  std::cout << std::endl;

  for (auto& x : a)
    x *= 10;

  for (auto i = 0u; i < a.size(); ++i)
    std::cout << "a[" << i << "] = " << a[i] << std::endl;

  b.at(90);  // bound checking at run-time b.at(2);

  return 0;
}

template <typename T, std::size_t N>
void print_array_two(const std::array<T, N>& a) {
  for (const auto& x : a)
    std::cout << x << " ";
  std::cout << std::endl;
}

template <typename T>
void print_array_one(const T& a) {
  for (const auto& x : a)
    std::cout << x << " ";
  std::cout << std::endl;
}

/*
Which one is better? From developing types the second is better,
but if you want to express the idea that this functionshould accept only an std::array the frist is useful

Since C++20 there are concepts wich are constexpr func that returns a boolean and is able to do a check on type of var
*/

//What if the size it is not unkown at compile time or the size is too big: I cannot use std::array! I use std:vector!