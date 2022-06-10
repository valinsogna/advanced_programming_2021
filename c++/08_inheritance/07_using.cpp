#include <iostream>
//I do the overload of a parent function inside a children class
struct foo {
  void f(int x) { std::cout << "int " << x << std::endl; }
};

struct bar : public foo {
  //using foo::f;  // brings all foo::f to this scope
  void f(char x) { std::cout << "char " << x << std::endl; }
};

int main() {
  bar b;
  b.f(33);//doesn't call func at line 4! 
  //Function overloading is not resolved across the hierarchy!
  //But with line 8 yes!
}
