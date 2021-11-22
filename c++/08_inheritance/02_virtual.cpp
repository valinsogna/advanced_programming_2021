#include <ap_error.hpp>
#include <iostream>
//virtual add 1 or more elements to your class
//It adds at least a pointer to a virtual function table that scorre sulle right implementations: varie animal::info, snake::info, dog::info,etc..
//So at least 2 jumps in memory when calling a virtual func, take the prt, go to vft, look which func use (at run time depends on the obj ID),
//then I jump to the implementation of the func of the right obj
//Virtual takes long!
struct Animal {
  unsigned int age;
  double weight;

  Animal(const unsigned int a, const double w) : age{a}, weight{w} {
    AP_ERROR(!(weight < 0)) << "invalid weight!\n";
  }

  Animal() : Animal{0, 0} {}  // delegating constructor
  //DINAMIC BINDING: virtual on the function that can be overwritten
  //It is different than function overloading!
  //It is function overwriting: same func, same arg, different classes!
  virtual void speak() const = 0;  // pure virtual function ==> abstract class
  virtual void info() const noexcept {
    std::cout << "age:\t" << age << '\n' << "weight:\t" << weight << '\n';
  }

  virtual ~Animal() {}  // why? see file 03_virtual_destructor.cc: virtual function
  //A class with at least pure virtual func, is a virtual class!Then:
  //I can't instanciate an obj Animal
  //You're forcing children to overwrite func tal dei tali
  //Why mark a dctor as virtual?
  //If your func has at least one virtual func, you should mark your dector as virtual
};

struct Dog : public Animal {
  //override (from C++11) double checks if it's virtual in the base class
  //otherwise prima c'era anche qui virtual ma poi era poco chiaro
  void speak() const noexcept override { std::cout << "Bau\n"; } 
  Dog() = default;
  Dog(const unsigned int a, const double d) : Animal{a, d} {}
};

struct Snake : public Animal {
  bool dangerous;
  //Ctor first generates the parent and then add the things for the child
  Snake(const unsigned int a, const double w, const bool b)
      : Animal{a, w}, dangerous{b} {} 
  explicit Snake(const bool b) : Animal{}, dangerous{b} {}
  void info() const noexcept override {
    Animal::info();
    std::cout << "dangerous:\t" << (dangerous ? "true" : "false") << std::endl;
  }
  void speak() const noexcept override { std::cout << "ssss\n"; }
};

void print_animal(const Animal& a) noexcept {
  std::cout << "throught ref\n";
  a.info();
  a.speak();
}

int main() {
  try {
    Snake s{true};
    s.info();
    s.speak();

    std::cout << std::endl;

    Animal* p = new Snake{1, 2.3, false};

    std::cout << "through pointer\n";
    p->info();
    p->speak();

    delete p;

    std::cout << std::endl;

    print_animal(s);

    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
