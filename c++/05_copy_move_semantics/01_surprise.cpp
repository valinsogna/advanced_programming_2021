#include <iostream>
#include <utility>
struct X { //no constructor nor destructor
  char member; //built in type
};

int main() {
  X x1;                 // default ctor: uninitializer
  X x2{x1};             // copy ctor
  X x3{std::move(x2)};  // move ctor: ++11
  X x4{};               // default ctor calling {} to each member
  x4 = x3;              // copy assignment
  X x5;                 // default ctor
  x5 = std::move(x4);   // move assignment
  std::cout << x5.member << std::endl;  // what do you expect?? Whatever
  //But if I choose 'X x1{}' for line 8, it returns empty char
  return 0;
}
//These code compiles beacuse if I don't specify a custom constructor,
// the compiler syntetize a default ctor, and the same for all move/copy ..
//If I define the constructor insted there is no difference between X x1 and X x1{}
