#include <cmath>
#include <iostream>
//Exceptions: exceptional events. Errors are exc events, but not all exp events are errors!
//Aim: how to signal that an exceptional event occurred
//Exceptions can be custom types: es. struct

// Implement a square root function that "deals with" negative
// numbers. Moreover according to the logic of the program, d should
// never be greater than 50
double square_root(const double d);

struct Negative_number {};

struct Bigger_than_expected {};

//How to catch these balls?
//Should enclose the main body inside a try/catch block!
//If an except raised inside a try block, it's value is compared in the catch blcok

int main() {
  //Try is like a switch statements for exception
  //You have this in java, javascript, etc..
  //At which level do you want to hadle the exception?
  //If at main you put it there, otherwise somewhereelse
  //Try block can be nested
  try {
    std::cout << "please insert a number\n";
    double number;
    std::cin >> number;
    auto d = square_root(number);
    std::cout << "square root of " << number << " is " << d << '\n';
    return 0;
  } catch (const Negative_number) {
    std::cerr << "The square root of a negative number is a complex number.\n"
                 "square_root() is "
              << "limited to handle positive double numbers.\n";
    return 1;
  } catch (const Bigger_than_expected) {
    std::cerr << "The function square_root has been called with a parameter "
                 "greater than 50.\n"
              << "This means there is a bug in the algorithm that generated "
                 "this number.\n";
    return 2;
  } catch (...) { // can catch whatever type of exception
    std::cerr << "Unknown exception. Aborting.\n";
    return 3;
  }
}
//throw: keyword to signal smthing
//You throw a different type of ball (an except event)
//You throw an object of a type!!
double square_root(const double d) {
  // test the pre-conditions
  if (d < 0)
    throw Negative_number{};//named type
  if (d > 50)
    throw Bigger_than_expected{};
  return std::sqrt(d);
}
