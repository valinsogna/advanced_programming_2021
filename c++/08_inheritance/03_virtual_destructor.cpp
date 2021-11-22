#include <iostream>

struct Base {
  Base() { std::cout << "Base\n"; }
  /*virtual*/~Base() { std::cout << "~Base\n"; } //now will work -> size 8,8 (ptr to VFT) otherwise 1,1
};//1,1 e non 0,0 perché lo standard vieta di mettere oggetti diversi in indirizzi ugauli: li mette inindirizzi diversi

struct Derived : public Base {
  Derived() { std::cout << "Derived\n"; }
  ~Derived() { std::cout << "~Derived\n"; }
};

int main() {
  { Derived d; }//It is constructed from the Parent and then to the child and first destroys the child and then the parent (it's in a scope)

  std::cout << "\n\npointers\n";
  Base* p = new Derived; //dynamic polymorphism
  delete p; //You discover the type at run time then! p is a pointer of Base, so destruct the parent only!

  std::cout << sizeof(Base) << ", " << sizeof(Derived) << std::endl;

  return 0;
}
