#include <iostream>

template <typename T>
void print_sentinel(const T* a, const std::size_t l);

int main() {
  int a{8}, b{7};
  int* pi{&a};

//Const before/after the star of a pointer: line 11/15
//Pointers have access to two varibales: the value of ptr (the address of the first variable) and the content(value) of the variable
  //Pointer to a const int
  int const* pc{&a}; //OR const int * pc
  // *pc = 7; 	// error
  a = 15;  // I can obviously change a

  //Const pointer
  int* const cp{&a};
  a = b;
  *cp = 33;
  // cp = &b;   // error

  const int* const cpc{&a};

  // *cpc = 0;  // error
  // cpc = &n;  // error
  a = 99;

  int aa[4]{};
  print_sentinel(aa, 4);

  return 0;
}
//Pointer arithmetics: ptr + 2 make to jumps to the size of ptr type
template <typename T>
void print_sentinel(const T* a, const std::size_t l) { // a is the ptr to the first elem
  //a it's a pointer to a constant: one past the last element!
  const T* const end{a + l};
  for (; a != end; ++a)//I increment of 1 jump the value of pointer a
    std::cout << *a << std::endl;
}

/*
0    1     2     3     4      
a   a+1   a+2   a+3   a+4
                last  past to last
                elem  elem
*/
