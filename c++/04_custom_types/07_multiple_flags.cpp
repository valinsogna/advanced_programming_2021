#include <iostream>
//enum by default are int, but you can change the type  
enum class flags : unsigned int {
  //two powers since they are represented with just one bit equal to 1
  flag1 = 1, //1*2^0 -> 001
  flag2 = 2, //1*2^1 -> 010
  flag3 = 4,  //1*2^2 -> 100
  // flag4 = 8 | flag1 | flag2, // imply flag1 and flag2 easy to implement, but
  // difficult to compare..
  flag4 = 8,   // additional functions needed
  flag5 = 16,  // imply flag3

  // useful combinations: I know which option is selected
  comb1 = flag1 | flag2, // flag1 OR flag2 -> 01 OR 10 -> 11 -> 1*2^1+1*2^0 = 3
  comb2 = flag1 | flag3, // flag1 OR flag3 -> 001 OR 100 -> 101 -> 1*2^2+1*2^0 = 5
  comb3 = comb1 | flag3, // comb1 OR flag3 -> 011 OR 100 -> 111 -> 1*2^2+1*2^1+1*2^0 = 7
};

void do_complicated_stuff(flags flags);

//bit-wise OR operator overloading
flags operator|(const flags f1, const flags f2);

//bit-wise AND operator overloading
unsigned int operator&(const flags f1, const flags f2);

// augmented bit-wise OR operator overloading
flags& operator|=(flags& f1, const flags f2);

int main() {
  std::cout << "testing flag1 and flag3\n"
            << "expected  flag1 and flag3 \n\n";
  // User enables all the following flags:
  do_complicated_stuff(flags::flag1 | flags::flag3 | flags::flag1 |
                       flags::flag1); 

  std::cout << "--------------\n\n"
            << "testing comb3\n"
            << "expected  flag1, flag2 and flag3 \n\n";
  // User enables all the following flags:
  do_complicated_stuff(flags::comb3);

  std::cout << "--------------\n\n"
            << "testing flag4\n"
            << "expected  flag1, flag2 and flag4 \n\n";
  // User enables all the following flags:
  do_complicated_stuff(flags::flag4);

  std::cout << "--------------\n\n"
            << "testing flag5\n"
            << "expected flag3 and flag5 \n\n";
  // User enables all the following flags:
  do_complicated_stuff(flags::flag5);

  return 0;
}

flags operator|(const flags f1, const flags f2) {
  return static_cast<flags>(static_cast<unsigned int>(f1) |
                            static_cast<unsigned int>(f2));
}

// Why no flags& operator& definition? implicit conversion to bool
/*
flags& operator&(flags& f1, const flags f2) {
  f1 = f1 & f2; // Implicit conversion to bool for built-in type (unsigned int)
  return f1;
}
*/
unsigned int operator&(const flags f1, const flags f2) {
  return static_cast<unsigned int>(static_cast<unsigned int>(f1) &
                                   static_cast<unsigned int>(f2));
}

flags& operator|=(flags& f1, const flags f2) {
  f1 = f1 | f2;
  return f1;
}
// Suppose: flag4 implies flag1 and flag2
void compute_multiple_flags(flags& f) { // f are all the flags enabled by the user
  if (f & flags::flag4)  // f4 implies flag1 and flag2
    f |= (flags::flag1 | flags::flag2);
  if (f & flags::flag5)  // f5 implies flag3
    f |= flags::flag3;
}

// I have to understand which flags has been enabled by the user:
// maybe there are some flags that trigger others or
// there are some flags that cannot be enabled at the same time,
// so this is checked by func compute_multiple_flags.
// Then you implement the relations between the flags.
void do_complicated_stuff(flags flags) { // flags are all the flags enabled by the user
  // update flags correctly
  compute_multiple_flags(flags);

  if (flags & flags::flag1)
    std::cout << "flag 1 selected\n";
  if (flags & flags::flag2)
    std::cout << "flag 2 selected\n";
  if (flags & flags::flag3)
    std::cout << "flag 3 selected\n";
  if (flags & flags::flag4)
    std::cout << "flag 4 selected\n";
  if (flags & flags::flag5)
    std::cout << "flag 5 selected\n";
}
