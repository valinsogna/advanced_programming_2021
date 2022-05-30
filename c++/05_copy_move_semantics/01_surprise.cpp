#include <iostream>
#include <utility> //std::move
struct X { //no constructor nor destructor
  char member; //built-in type
};

//OSS
// for built-on types there is a difference in calling:
// default ctor **syntethized** by the compiler:
//    - X x1; -> whatever char
//    - X x1{}; -> empty char

// otherwise, if not sinthesized, the compiler calls the ctor written by the user!
//If I define the constructor insted there is no difference between X x1 and X x1{}

//OSS2
// struct X { 
//  char member = 'a'; // => no difference btw syntethized ctors: X x1; and X x1{};
// };
int main() {
  X x1;                 // default ctor: uninitializer // But if I choose 'X x1{}' for line 8, it returns empty char
  X x2{x1};             // copy ctor
  X x3{std::move(x2)};  // move ctor: ++11
  X x4{};               // default ctor calling {} to each member
  x4 = x3;              // copy assignment
  X x5;                 // default ctor
  x5 = std::move(x4);   // move assignment
  std::cout << x5.member << std::endl;  // what do you expect, does it compile?? Whatever char!
  // It shouldn't since I didn't implement any of these callers! 
  // THIS CODE ACTUALLY COMPILES! Why?
  // If I don't write ctor or dector, the compiler automatically generates several ctors!
  
  // If I don't write      Compiler construct
  // custom ctor           default ctor
  // copy ctor             copy ctor, copy assign, move ctor, move assign
  // destructor            destructor
  return 0;
}

