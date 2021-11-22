#include <iostream>

template <typename T>
struct Base {
  void foo() const { std::cout << "base foo" << std::endl; }
};

template <typename T>
struct Derived : public Base<T> {
  void bar() const { this->foo(); }//this is needed when the parent class is templated:
  // to resolves types correctly, otherwise the compiler won't work
};

int main() {
  Derived<int> d;
  d.bar();
}
