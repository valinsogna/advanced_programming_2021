#include <iostream>
#include <memory>

#include "ap_error.hpp"
//If you plan to combine Python with C++ don't use exeptions
//since Python core is written in C and C doesn't have exceptions!  
class Vector {
  std::unique_ptr<double[]> elem;

 public:
  Vector(const unsigned int l) : elem{new double[l]} {}
 // noexcept: keyword for assuring compiler that the code won't raise exceptions
 // so compiler won't wrap additional code to handle exceptions!

 //copy semantics 'noexcept' usually
 //move semantics is always 'noexcept'

  Vector(Vector&&) noexcept = default; //here we are not acquiring any additional resource so I can use noexcept
  //noexcept: I promise it will never throw an exception and also the func invoked internally
  //If I lied then the programnmm crashes: no stack unwinding
  
  Vector& operator=(Vector&&) noexcept = default;

  double& operator[](const unsigned int i) noexcept { return elem[i]; }

  const double& operator[](const unsigned int i) const noexcept {//è una funz const. Quindi è const safe
    return elem[i];
  }
  ~Vector() noexcept { std::cout << "~Vector\n"; }

  // Copy assignment
  // for many years, copy assignment was written as follows
  // Vector& operator=(const Vector& x){
  //   ~Vector();
  //   new (this) Vector{x}; // placement-new on my self using copy ctor
  //   return *this;
  // }
  // Can you imagine why it has been changed? It is not exception safe!
  // What happens if inside copy ctor an exception is thrown?
  // If new fails the destructor is called 2 times!
  // Therefore:
  // Vector& operator=(const Vector& x){
  //   //clean resources:
  //   auto tmp = x; //copy ctor
  //   (*this) = std:move(x);
  //   return *this;
  // }
};

class ManyResources {
  std::unique_ptr<double[]> ptr; //smart ptr: RAII. Stack unwinding automatically release the resources!
  Vector v;

 public:
 //no try-catch block
  ManyResources() : ptr{new double[5]}, v{3} {
    std::cout << "ManyResources ctor\n";
    AP_ERROR(false) << "I am simulating something wrong.\n";
  }
  ~ManyResources() noexcept { std::cout << "~ManyResources\n"; }
};

int main() {
  try {
    //ptr can be placed inside 
    std::unique_ptr<int[]> up{new int[7]};  // RAII
    ManyResources mr;

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;
    return 2;
  }

  return 0;
}
