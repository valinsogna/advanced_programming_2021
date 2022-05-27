#include <iostream>
#include <string>

struct Foo {
  int _i;
  double _d;
  std::string _s;
//Constractors are functions and do not have a return type 
//and their name is the same of the class
//They can be defined inside/outside the class
//Inside they must be inlined!
//Not 'Inlined' means that in executing instructions,
//the binary code of your functions jumps from 1 point and then returns back.
//For small functions better inline!
  Foo(const int i, const double d,
      const std::string& s);  // custom constructor

  Foo();  // default constructor

  ~Foo();  // destructor: function invoked when your object is out of scope
  //+ copy constructor and move constructor (since c++11)
};
//Outside fully qualified name without return type:
Foo::Foo(const int i, const double d, const std::string& s)
    : _i{i},//initilization space: we are calling the constructor of each elem
      _d{d},//faster to initialize members here then in the body!
      _s{s}
// _i, _d, _s must be initialized in the same order they have been declared
{//here those memebers at line 25-27 are been constructed!
//_i = i;
  std::cout << "custom ctor\n";
  // if you want/need you can use _i, _d, _s and change their value
  // with the usual notation +,-,=,*, call a function..
  // don't use {} because this notation is reserved for the
  // construction of the variables and at this point they have already
  // been constructed
}

Foo::Foo() {
  std::cout << "default ctor\n";  // what happens to our member variables?
}

Foo::~Foo() {
  std::cout << "dtor\n";
}

std::ostream& operator<<(std::ostream& os, const Foo& f) {
  os << f._i << " " << f._d << " " << f._s << std::endl;
  return os;
}

int main() {
  Foo f0;    // call default ctor
  Foo f1{};  // call default ctor
  // Foo f2(); // compiler error

  Foo f2{8, 2.2, "hello"}; // can have round parenthesis as well but older codes
  std::cout << "f0: " << f0 << "f1: " << f1 << "f2: " << f2 << std::endl;

  // the destructor is called when the variable goes out of scope
  return 0;
}
