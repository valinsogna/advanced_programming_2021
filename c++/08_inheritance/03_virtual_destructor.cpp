#include <iostream>

struct Base {
  Base() { std::cout << "Base\n"; }
  /*virtual*/~Base() { std::cout << "~Base\n"; } //now dyn poly will work with virtual
};

struct Derived : public Base {
  Derived() { std::cout << "Derived\n"; }
  ~Derived() { std::cout << "~Derived\n"; }
};

int main() {
  { Derived d; }//It is constructed from the Parent and then to the child and first destroys the child and then the parent (it's in a scope)

  std::cout << "\n\npointers\n";
  //dynamic polymorphism is achived by: inheritance + virtual functions (dynamic binding)
  Base* p = new Derived; // just inheritance is not enough!
  delete p; //You discover the type at run time then! p is a pointer of Base, so destruct the parent only!

  std::cout << sizeof(Base) << ", " << sizeof(Derived) << std::endl; // -> "1,1"
  // Why 1,1 e non 0,0? Perché lo standard vieta di mettere oggetti diversi
  // in indirizzi uguali: li mette in indirizzi diversi. 
  // Sennò se fossero uguali a zero starebbero allo stesso indirizzo.
  // OSS. con virtual-> size 8,8 (ptr to VFT) otherwise 1,1!

  return 0;
}
