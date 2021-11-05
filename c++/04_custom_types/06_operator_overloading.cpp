#include <array>
#include <iostream>
#include <vector>
//Operators are functions
// '<<' PUT O OPERATOR is a binary operator = 2 args
// but we can invoke operator multiple times

struct Point_s {
  double x;
  double y;
};  // note ; at the end

std::ostream& operator<<(std::ostream& os, const Point_s& p) {
  os << "Struct. x = " << p.x << "; y = " << p.y << std::endl;
  return os;
}
//In C++ you can access data by means of a pointer: this

class Point_c {
  double x;
  double y;

  friend std::ostream& operator<<(std::ostream& os, const Point_c& p) {
    os << "Class. x = " << p.x << "; y = " << p.y << std::endl;
    return os;
  }
  //without friend, the compiler complains saying that operator has 3 arguments:
  //it is reffering to the pointer this!
  //So this is being passed inside the class automatically and there is no need to pass Pointc_& p!
  //This is way he prefwers to define it outside!
  //friend makes this function NOT A MEMBER function, and it gives acces to external functions to private data

};  // note ; at the end

int main() {
  Point_s ps;
  ps.x = 9.9;
  ps.y = 3. / 7;

  std::cout << ps;

  Point_c pc;
  // pc.x =7.6; // error
  std::cout << pc;

  Point_s* p = &ps;
  p->x = 0.0;
  std::cout << *p;  // operator overloading does not work with pointers

  return 0;
}
