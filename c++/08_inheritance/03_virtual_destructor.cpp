#include <iostream>

struct Base {
  Base() { std::cout << "Base\n"; }
  /*virtual*/~Base() { std::cout << "~Base\n"; } //now will work
};

struct Derived : public Base {
  Derived() { std::cout << "Derived\n"; }
  ~Derived() { std::cout << "~Derived\n"; }
};

int main() {
  { Derived d; }//It is constructed from the Parent and then to the child and first destroys the child and then the parent (it's in a scope)

  std::cout << "\n\npointers\n";
  Base* p = new Derived; //dynamic polymorphism
  delete p; //You discover the type at run time then! p is a pointer of Base, so destruct the parent only!

  return 0;
}
