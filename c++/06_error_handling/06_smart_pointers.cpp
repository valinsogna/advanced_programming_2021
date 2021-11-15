#include <iostream>
#include <memory>

#include "ap_error.hpp"

class Vector {
  std::unique_ptr<double[]> elem;

 public:
  Vector(const unsigned int l) : elem{new double[l]} {}
 //noexcept: keyword RIASCOLTA
 //copy semantics 'noexept' usually
  Vector(Vector&&) noexcept = default;
  Vector& operator=(Vector&&) noexcept = default;

  double& operator[](const unsigned int i) noexcept { return elem[i]; }

  const double& operator[](const unsigned int i) const noexcept {
    return elem[i];
  }
  ~Vector() noexcept { std::cout << "~Vector\n"; }

  //This impl of copy assignement is not exception safe: If new fails the destructor is called 2 times!
  // Vector& operator (const Vector& x){
  //   ~Vector();
  //   new(this) Vector {x};
  //   return *this;
};

class ManyResources {
  std::unique_ptr<double[]> ptr; //smart ptr
  Vector v;

 public:
  ManyResources() : ptr{new double[5]}, v{3} {
    std::cout << "ManyResources ctor\n";
    AP_ERROR(false) << "I am simulating something wrong.\n";
  }
  ~ManyResources() noexcept { std::cout << "~ManyResources\n"; }
};

int main() {
  try {
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
