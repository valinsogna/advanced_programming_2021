#include <chrono>
#include <iostream>
//If your code inside your function it is not known at compile time,
constexpr std::size_t fib(const unsigned int x) {
  return (x < 2) ? x : fib(x - 1) + fib(x - 2); //recursion + C++14 syntax
  // if (x < 2) return x;
  // else {
  //   return fib(x-1) + fib(x-2);
  // }
}

std::size_t fib_rt(const std::size_t x) {
  if (x < 2)
    return x;
  return fib(x - 1) + fib(x - 2);
}
//With template we can force this to evaluate at compiled time
//Template must be known at compile time
template <unsigned i> //NOT everythig can be used as <> in a template, only: unknown types or integer types
constexpr std::size_t fib_t() {
  return fib_t<i - 1>() + fib_t<i - 2>();
}

template <>
constexpr std::size_t fib_t<0>() {
  return 0;
}

template <>
constexpr std::size_t fib_t<1>() {
  return 1;
}

//MACRO: preprocessor instr
//Long int
#if __cplusplus > 201700L 

template <unsigned i>
constexpr std::size_t fib_t17() {
  if constexpr (i < 2) //C++17 syntax + if statement is evaluated at run time
    return i;
  else {  //<- very important, otherwise and infinite recursion 
  //(instead for normal if condition you don't need to specify else if you are exiting the function)
    return fib_t17<i - 1>() + fib_t17<i - 2>();
  }
}
#endif

constexpr unsigned int num{24};

int main() {
  {//scope: so t0,t1,elapsed are confined in the scope
    auto t0 = std::chrono::high_resolution_clock::now();
    constexpr auto x = fib(num);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    std::cout << "constexpr: " << x << " [" << elapsed.count() << " us]"
              << std::endl;
  }

  {
    auto t0 = std::chrono::high_resolution_clock::now();
    auto x = fib_rt(num);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    std::cout << "run time: " << x << " [" << elapsed.count() << " us]"
              << std::endl;
  }

  {
    auto t0 = std::chrono::high_resolution_clock::now();
    auto x = fib_t<num>();
    auto t1 = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    std::cout << "template: " << x << " [" << elapsed.count() << " us]"
              << std::endl;
  }

#if __cplusplus > 201700L
  {
    auto t0 = std::chrono::high_resolution_clock::now();
    auto x = fib_t17<num>();
    auto t1 = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    std::cout << "c++17: " << x << " [" << elapsed.count() << " us]"
              << std::endl;
  }

#endif

  return 0;
}
