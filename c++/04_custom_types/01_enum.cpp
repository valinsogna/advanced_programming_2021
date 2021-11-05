#include <iostream>
//Enum defines const expressions with different values compolsury
enum color { red, yellow, green };
// enum color{red=0, yellow=1, green=2}; // equivalent
//But what if I define:
//enum t {blue, red, green} -> This name clashing has been resolved with scope enum in C++11
void dwim(const color c) {
  //SWITCH works only with enum, char, (unsigned/short)int. Not with strings or double!
  switch (c) {
    case red:
      std::cout << "option 1: red\n";
      break;//exit from the inner scope/loop
    case yellow:
      std::cout << "option 2: yellow\n";
      break;
    case green:
      std::cout << "option 3: green\n";
      break;
    default:
      std::cout << "unknown option\n";  // should I exit the program?
      break;
  }
}

int main() {
  color opt{red};//named color variable of typew color
  // opt = 3; // cannot assign int to enum
  int a{opt};  // but they implicitly convert to integers

  dwim(opt);

  dwim(yellow);

  // dwim(2); // error
  dwim(color(2));  // works but why you may want to write this?

  dwim(color(6));  // ???

  return 0;
}
