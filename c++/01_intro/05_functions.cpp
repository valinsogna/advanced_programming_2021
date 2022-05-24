#include <iostream>

//declaration: name of variable not important (signature) (first time you introduce a symbol)
void buggy_swap(int , int );
void swap_c(int* a, int* b);
void swap_cxx(int& a, int& b);

int main() {
  int a = 3;
  int b {7};
  buggy_swap(a, b);
  std::cout << "buggy:\texpected 7 3 --> " << a << " " << b << "\n";

  a = 3;
  b = 7;
  swap_c(&a, &b);
  std::cout << "c:\texpected 7 3 --> " << a << " " << b << "\n";

  a = 3;
  b = 7;
  swap_cxx(a, b);
  std::cout << "cxx:\texpected 7 3 --> " << a << " " << b << "\n";
}
//definitions: name important
void buggy_swap(int a, int b) { //passed by value
  int tmp = b;
  b = a;
  a = tmp;
}

void swap_c(int* a, int* b) { //by pointer
  int tmp = *b;
  *b = *a;
  *a = tmp;
}

void swap_cxx(int& a, int& b) {//by ref: automatic
  int tmp = b;
  b = a;
  a = tmp;
}
