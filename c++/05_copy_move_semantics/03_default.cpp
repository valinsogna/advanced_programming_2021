#include <iostream>
//X() = default : compilers generates all 6 func
struct X {
  int a = 5;  // in-class initialization
  double b;
  char c = 'a';
  X() = default;  // in-class initializers are used by the constructors
};

//Here struct C doesn't have a default constuctor
struct C {
  int a = 5;  // in-class initialization
  double b;
  char c = 'a';
  C(int a): a{a} {}
  //C() = default; 
};
//If the user has defined a custom ctor => default ctor is not generated
//"" cpt ctor =>  default move ctor, move assign, copy assign are not generated
// "" move ctor => default copy semantic is not generated

struct Y {
  int a = 77;
  double b;
  char c = 'a';
  Y() : a{5} {}  // what it is written here wins the in-class initialization
  Y(const Y&) = delete;//since C++11 unique pointers
};

int main() {
  X x1;    // compiler-generated default ctor
  X x2{};  // compiler-generated default ctor calls {} on uninitialized vars
  std::cout << x1.a << "--" << x1.b << "--" << x1.c << "\n";
  std::cout << x2.a << "--" << x2.b << "--" << x2.c << "\n\n";

  Y y1;    // default ctor
  Y y2{};  // default ctor
  std::cout << y1.a << "--" << y1.b << "--" << y1.c << "\n";
  std::cout << y2.a << "--" << y2.b << "--" << y2.c << "\n";

  // Y y3{y2}; // error: call a deleted function

  return 0;
}
