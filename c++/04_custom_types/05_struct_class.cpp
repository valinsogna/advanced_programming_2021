#include <array>
#include <iostream>
#include <vector>
//Struct/Class define new types!
//They can have as memebers both functions and variables
//Plus, functions are called methods sometimes.
//What's the difference?
//It is in the default visibility of the symbols!
//Struct make them all public, instead class private!
//There are 3 level of visibility: public, private, protected
//Private visibility is for let the object remain in a valid state
//Interface of a class: set of public symbols, variables, functions (all public memebers)
//Functions can be implemented either inside a class or outside calling the full name

struct Point_s {
  double x;
  double y;
  void print();
};  // note ; at the end

void Point_s::print() {
  std::cout << "Structure. x = " << x << "; y = " << y << std::endl;
}
//In C++ you can access data by means of a pointer: this
//This is a pointer that points to the object that invoke the function 
/*
void Point_s::print() {
  std::cout << "Structure. x = " << this->x << "; y = " << this->y << std::endl;
}
*/

class Point_c {
  double x; 
  double y;

 public:
  void print() { // method can be defined INSIDE or OUTSIDE the class with fully qualified name (and just the declaration inside)
    std::cout << "Class. x = " << x << "; y = " << y << std::endl;
  }  // note no ; at the end
};   // note ; at the end

// The order in which you define members is not important!
// class Point_c {
//  public:
//   void print() {
//     std::cout << "Class. x = " << x << "; y = " << y << std::endl;
//   } 
//  private:
//   double x;
//   double y;
// };

int main() {
  Point_s ps;
  ps.x = 9.9;
  ps.y = 3. / 7;

  ps.print();

  Point_c pc;
  // pc.x =7.6; // error: only public memebers are visible from outside
  pc.print();  // I can access private data through public functions

  Point_s* p = &ps;
  p->x = 0.0; // use arrow (no point) to access members
  p->print();

  auto& pr = ps;
  ++pr.x;
  pr.print();

  Point_s array_of_structs[8];  // built-in array
  array_of_structs[0].x = 1;
  array_of_structs[0].y = 2;

  std::array<Point_s, 5> as;
  as[3].x = 3;

  std::vector<Point_s> vs;
  vs.push_back(ps);
  vs[0].x = 999;
  ps.x = 11;
  ps.print();
  vs[0].print();

  return 0;
}
