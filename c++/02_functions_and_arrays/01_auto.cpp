#include <cmath>
#include <iostream>

template <typename T>
void debug(T);

int main() {
  auto b = true;          // a bool
  auto ch = 'x';          // a char
  auto i = 123;           // an int
  auto d = 1.2;           // a double
  auto z = std::sqrt(d);  // z has the type of whatever sqrt(d) returns
  auto ui = 0u;           // unsigned int
  auto llui = 0llu;       // long long unsigned int

  auto& j = i;  // int&

  for (auto i = 0; i < 7; ++i)
    std::cout << i << std::endl;

  auto pb = &b;  // guess what.. How can I know? By forcing an error 
  debug(pb);
  //It's a pointer to a boolean

  auto s = "hello";  // watch out! Not a string, but "char const *"
  debug(s);

  return 0;
}
