#include <cmath>
#include <iostream>

#include "ap_error.hpp"

// implment a square root function that "deals with" negative
// numbers. Moreover according to the logic of the program, d should
// never be greater than 50

//So far we learn Static Polymorphism like templates 
// (templates are const exp: the type must be known at compile time)
//Dynamic Polymorfism: at runn time (we will see it)!
double square_root(const double d);

struct Square_root_invalid {
  std::string message;
  Square_root_invalid(std::string s) : message{std::move(s)} {}//s undefined behaviour, puoi liberare risorse
  // C++ convention:
  const char* what() const { return message.c_str(); }
};

int main() {
  try {
    std::cout << "please insert a number\n";
    double number;
    std::cin >> number;
    double d = square_root(number);
    std::cout << "square root of " << number << " is " << d << '\n';
    return 0;
  } catch (const Square_root_invalid& e) {
    std::cerr << e.what() << std::endl;
    return 2;
  } catch (const std::exception& e) {// to catch all std exceptions since exception is a parent class and must catch it by REF (for DYNAMIC POLYmorphism)
    std::cerr << e.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n";
    return 3;
  }
}
//EX: 90
/*
please insert a number
90

------------------------------------------------------------------
A runtime exception has been thrown

       file: 03_error.cpp
       line: 44                                                        -> WHERE
   function: double square_root(const double)
------------------------------------------------------------------

In our library the argument must be positive and less or equal than 50. -> WHY

You passed 90.
*/

double square_root(const double d) {
// test the pre-conditions
//Define your own MACRO(handled by preprocessor)
//If (d >= 0 && d <= 50) = TRUE nothing happens
//Otherwise I throw a type: Square_root_invalid
  AP_ERROR(d >= 0 && d <= 50, Square_root_invalid)
      << "In our library the argument must be positive and less or equal than "
         "50.\n\nYou passed "
      << d << ".\n";
//Why AP_ERROR is a MACRO and not a func?
//If it's a function, it will give me info of where the error took place 
//everytime there's that error, so we need a MACRO!

  // AP_ERROR(d >= 0 && d <= 50) << "In our library the argument must be
  // positive "
  //                                "and less or equal than 50.\n";

  // AP_ERROR_GE(d, 0) << "Cannot handle negative numbers.\n";

  // AP_ERROR_LE(d, 50) << "According to the implemented algorithm, the argument
  // "
  //                       "must be less than 50.\n";

  // AP_ERROR_IN_RANGE(d,0,50);

  return sqrt(d);
}
