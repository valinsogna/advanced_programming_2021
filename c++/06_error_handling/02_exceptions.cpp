#include <cmath>
#include <iostream>
#include <string>
#include <utility>

// Implement a square root function that "deals with" negative
// numbers. Moreover according to the logic of the program, d should
// never be greater than 50
double square_root(const double d);
//Convention in C++:
//All exceptions should have a method const char* what()
struct Square_root_invalid {
  std::string message;
  Square_root_invalid(std::string s) : message{std::move(s)} {}
};

int main() {
  try {
    std::cout << "please insert a number\n";
    double number;
    std::cin >> number;
    auto d = square_root(number);
    std::cout << "square root of " << number << " is " << d << '\n';
    return 0;
  } catch (const Square_root_invalid& s) {
    std::cerr << s.message << std::endl; // not optimal since user should know the design .message
    return 1;
  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n";
    return 3;
  }
}

double square_root(const double d) {
  // test the pre-conditions
  if (d < 0)
    throw Square_root_invalid{"Cannot handle negative numbers. You gave me " +
                              std::to_string(d)};
  if (d > 50)
    throw Square_root_invalid{
        "The argument of square_root must be lower than 50. You gave me " +
        std::to_string(d)};
  return sqrt(d);
}
