#include <iostream>
#include <sstream>
#include <string>
//OR char** argv
//argc argv stores the command line arguments
//argv[0] = name of the executable
//command line !== standard input
//Command line reads always as strings!

int main(int argc, char* argv[]) {
  for (auto i = 0; i < argc; ++i)
    std::cout << "argv[" << i << "] = " << argv[i] << std::endl;

  unsigned int a;
  {
    std::istringstream s{argv[1]};  //before C++11: char '3' is converted to un unsigned int
    s >> a;
  }
  std::cout << "a is " << a << std::endl;
//Since C++11:
  // std::stoi int
  // std::stol long int
  // std::stoll long long int
  // std::stof float
  // std::stod double
  // std::stoull unsigned long long int
  a = std::stoul(argv[1]);
  std::cout << "a is " << a << std::endl;
  return 0;
}
