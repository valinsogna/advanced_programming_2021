#include <iostream>
//namespace it's a named scope
//scope can be nested
namespace choose_a_name {

  int variable;

  namespace nested {

    void hello1();
    void hello2();
    void hello3();

  }  // namespace nested
}  // namespace choose_a_name

int main() {
  // variable = 42; // error
  choose_a_name::variable = 42; //scope resolution operator ::
  // hello1(); // error
  choose_a_name::nested::hello1();
  choose_a_name::nested::hello2();
  choose_a_name::nested::hello3();
  return 0;
}

void choose_a_name::nested::hello1() {
  std::cout << "hello1 from nested\n"
            << "variable is " << choose_a_name::variable << std::endl;
}
//I reopen the namespace choose_a_name
//I can incrementaly add symbols to a namespace 
namespace choose_a_name {
  namespace nested { //THE SAME nested namespace!!!!
    void hello2() {
      std::cout << "hello2 from nested\n"
                << "variable is " << variable << std::endl;
    }
  }  // namespace nested
}  // namespace choose_a_name

using namespace choose_a_name; // not raccomanded

void nested::hello3() {
  std::cout << "hello3 from nested\n"
            << "variable is " << variable << std::endl;
}
