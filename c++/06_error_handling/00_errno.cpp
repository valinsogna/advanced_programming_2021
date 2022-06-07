#include <cmath> // math.h equivalent in C
#include <iostream>
//std::sqrt is in cmath (=math.h in C)
//In C there is a global var errno (Error Number):
//This requires that the user must check error numbers! -> it's annoying: C++ cames with Exceptions

int main() {
  double d = std::sqrt(4);
  std::cout << d << " " << errno << std::endl;//2 0

  d = std::sqrt(-4);
  std::cout << d << " " << errno << std::endl;//-nan 33

  d = 0;

  errno = 0; // since errno doesn't reset to zero 
  // after being raised an error and passing a valid arg

  return 0;
}
