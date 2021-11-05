#include <cstring>  // strcmp
#include <iostream>

int func1(const char* a);
int func2(const char* a);
void func3(const char* a);

int main() {
  int a{8};
  int* pi{&a};

  char** ppc; //pointer to a pointer to char: I might have an array of pointers which points int

  int* ap[7];

  void* pv{pi}; //void* can point to whatever!
  // *pv; // we cannot dereference void*
  // ++pv; // we cannot increment. Why can't I do math pointers? It doesn't now how big is the obj to which is pointing
  //To use pointer arithmetics once must previously cast conversion.
  //In c: (int*)pv; C doesn't have template
  //In C++: const cast, static cast, dynamic cast.
  int* pi2{static_cast<int*>(pv)};//static cast: performe at compile time
  //dynamic cast:to reverse hierarchy of object, then 

  pv = ppc;
  pv = ap;
  pv = pi;

  pi = nullptr;
  ppc = nullptr;
  // ap = nullptr;  // error, why? 
  //ap is name of a static array: so it's ike a const pointer, and I cannot chnage the address or the value
  ap[0] = nullptr;
  int** bbb;
  bbb = ap;
  pv = nullptr;
  pi2 = 0;  // older codes. gets the nullptr. please don't do it

  // pi = NULL; // please don't do it
  //NULL and nullptr are of different types: in some compiler NULL might not work.
  //In C NULL = 0 but in C++ nullptr it's a pointer of NULL elem which is !== 0(?)

  double* da{new double[5]{}};
  delete[] da;  // dangling pointer: points to an address location, but it's emptied
  da = nullptr; //This must be done
  //You can't dereference a nullptr!
  if (pi != nullptr)
    std::cout << "pi is not nullptr and I can dereference it " << *pi
              << std::endl;

  if (pi) //same as: pi != nullptr because each number different from 0 are implicetly converted to true
    std::cout << "pi is not nullptr and I can dereference it " << *pi
              << std::endl;

  if (pi == nullptr)
    std::cout << "pi is nullptr and I CANNOT dereference it \n";

  if (!pi)
    std::cout << "pi is nullptr and I CANNOT dereference it \n";

  // strings are special type of char[]
  //I can use char and not library std::string!
  char word[]{"Hello"};
  char word2[]{'H', 'e', 'l', 'l', 'o', 0};//Remember to add 0 to last element in a string.
  //In C last elem is \0
  if (strcmp(word, word2) == 0)  // word == word2 is
                                 // implementation-dependent (it might
                                 // compare the two pointers, i.e. the
                                 // two addresses of word and word2)
    std::cout << "same\n";
  else
    std::cout << "different\n";
//POINTER TO FUNCTION
  int (*fp)(const char*); //int (*fp) parentesi are mandatory!Otherwise it's a 
  fp = func1; //You can omit & for functions!

  fp("hello");

  fp = &func2;
  fp("world");

  // fp = func3; // error: wrong signature: it's a void
  auto xx = func3;

  xx("auto");
  
  //keyword that can be used inside template 
  decltype(&func3) x = func3;
  x("decltype");

  return 0;
}

int func1(const char* a) {
  std::cout << "1111: " << a << std::endl;
  return 1;
}

int func2(const char* a) {
  std::cout << "2222: " << a << std::endl;
  return 2;
}

void func3(const char* a) {
  std::cout << "3333: " << a << std::endl;
}
