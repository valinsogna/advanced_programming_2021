#include <iostream>
#include <vector>

#include "ap_error.hpp"
// Stack unwinding:
// Severl stack frames: if you have an exception in 1 of the frame,
// you begin stack winding (coming backwords deleting the objects)
class Foo {
 public:
  Foo() { std::cout << "Foo" << std::endl; }//do not use noexept because cout uses a buffer!
  ~Foo() { std::cout << "~Foo" << std::endl; }
};

class Bar {
 public:
  Bar() { std::cout << "Bar" << std::endl; }
  ~Bar() { std::cout << "~Bar" << std::endl; }
};

class Vector {
  double* elem;

 public:
  Vector(const unsigned int l) : elem{new double[l]} {
    std::cout << "Vector" << std::endl;
  }
  ~Vector() {
    delete[] elem;
    std::cout << "~Vector" << std::endl;
  }
};

class ManyResources {
  double* ptr;
  Vector v;

 public:
 //What happen if ManyResources ctor fails? 
 //At line 43 the ctor is called but the destructor is not invoked, 
 // so I have to clean it (delete[] ptr)!! 
  ManyResources() : ptr{nullptr}, v{3} {
    std::cout << "Manyresources" << std::endl;
    try {
      ptr = new double[5];  // new(std::nothrow) double[5] could be better
      AP_ERROR(false) << "Error in ManyResources ctor." << std::endl;
    } catch (...) {
      delete[] ptr;  // <----
      throw;         // re-throw
    }
  }

  ~ManyResources() {
    std::cout << "~Manyresources" << std::endl;
    delete[] ptr;  // <----
  }
};

int main() {
  Foo f;//it's construct but not destruct since is not in the try
  //raw_ptr is outside the try block: why? I would have a memory leak!
  int* raw_ptr = new int[7];  // do not use raw ptr, 
  //but use CLASSES THAT IMPLIMENT RAII for each resource one at the time! 
  //So in this case smart ptr!
  try {
    // int * raw_ptr=new int[7]; // wrong because raw_ptr would not be visible
    // inside the catch-clause but only in the try scope!
    ManyResources mr;//Has an exp: it's construct but not destruct
    Bar b;//It's not construct

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;

    delete[] raw_ptr;  // <--- try to comment this and run valgrind or use the
                       // sanitize library
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;

    delete[] raw_ptr;  // <---
    return 2;
  }

  delete[] raw_ptr;  // <---
  return 0;
}
