#include <iostream>
#include <string>

template <typename T>
class Vector {
  T* data;
  std::size_t _size; //known at run time

 public:
  Vector(const std::size_t size) : data{new T[size]}, _size{size} {}

  // automatically release the acquired memory
  ~Vector() { delete[] data; }

  // RAII - Resource Acquisition Is Initialization
  // In c++ by combination of ctor and dector

  // Try to remove the const and recompile:
  // if you call v.size() you will get an error since the compiler 
  // don't not know if the func is modifying the state of Vector v e.x. _size or not.
  // This const ON THE RIGHT is just for member funcs! (inside a class) <- IMPORTANT
  // It guarantees that the func won't change the member: e.x. return ++_size;
  std::size_t size() const { return _size; }

  // Subscripting operator with no bound checking
  // v.operator[](0) ===== v[0]
  /*
    int main(){
      Vector<int> v(10);
      v[5] = 99; // USE NON CONST OPERATOR[]
    }
  */
  T& operator[](const std::size_t i) { // no right const => can change data[i]!
    // ++i;
    return data[i];
  }

  // Try to comment this line and recompile:
  // if you call:
  /*
    template <typename T>
    void foo(const Vector<T>& v) {
      std::cout << v[0] << std::endl; // error: v[0] is not compliant with const Vector<T>& v
    // MUST USE NON CONST OPERATOR[]
    }
  */
  // We need also a const operator with const on the right to read the data:
  const T& operator[](const std::size_t i) const { return data[i]; }
  /*
  If I write:

  const T& operator[](const std::size_t i) const { data[0]= 99; return data[i]; }

  Am I changing the vector if I change one elem?
  In my mind yes!
  I am modifying the state of my object!
  So is not compliant with this const, but does it compile? Yes, why?

  How does compiler know if body of a func is compliant?
  He checks that the members don't change the state of the object
  But if we have raw ptr we cen put const on the left and on the right!
  Infact, when checking, the compiler puts the const on the right and not on the left of ptr:

  T* const data; -> const ptr to data => I can change data[0], I can't change data (the address)

  */

  //ATT: without left const there is a bug!
  /*
    T& operator[](const std::size_t i) const { return data[i]; }
    template <typename T>
    void foo(const Vector<T>& v) {
      v[0] = 88; // it compiles whilst it shouldn't!!
      // Compiler doesn't check on the return type: you must take care of it and insert const!!!
      std::cout << v[0] << std::endl; // const operator[]
    }

  */

  // OSS: template T is missing: const Vector<T>& v!
  // Inside a class you can omit it!
  // This is the best solution:
  // friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
  //   for (std::size_t i = 0; i < v.size(); ++i) 
  //     os << v[i] << " ";
  //   os << std::endl;
  //   return os;
  // }

  // Otherwise entiraly write it out (like now)

  // Or declarete inside as friend and define it outside: must pay attention to tempaltes though!
  // Use different types, otherwise compiler will not understand that they are the same func!
  /*
  INSIDE:
  template <typename TO>
  friend std::ostream& operator<<(std::ostream& os, const Vector<TO>& v);
  
  OUTSIDE:
  template <typename T>
  std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
    for (std::size_t i = 0; i < v.size(); ++i) 
      os << v[i] << " ";
    os << std::endl;
  return os;
  }
  */

 // To implement range-based for loop: for (auto& elem : v) { ... }
  const T* begin() const { return data; } // overloading so it can be invoked with >>operator
  T* begin() { return data; }

  const T* end() const { return data + _size; } // a ptr to a const T
  T* end() { return data + _size; } // one past the last element

  // Example:
  // friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
  //   os << v.data << ": ";
  //   for (auto& x : v)
  //     os << x << " ";
  //   os << std::endl;
  //   return os;
  // }
  // The compiler does:
  /*
      for (auto& x : v)
        os << x << " ";
        {
          auto first = v.begin();
          const auto last = v.end();
          for(; first != last; ++first){
            const auto& x = *first;
            os << x << " ";
          }
        }
  */
};

template <typename T>
void foo(const Vector<T>& x) {
  auto p = x.begin();
  ++p;
}

template <typename T> // must get the template!!
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  for (auto i = 0u; i < v.size(); ++i)
    os << "v[" << i << "] = " << v[i] << std::endl;
  return os;
}

int main() {
  Vector<double> v{10};

  for (auto i = 0u; i < v.size(); ++i)
    v[i] = i;

  std::cout << v << std::endl;

  Vector<double>* pv{&v};

  // first dereference the pointer, then I can use the defined operators
  (*pv)[0] = -99.999;

  pv->operator[](1) = 77777.3333;  // or I call the function by name

  std::cout << *pv << std::endl;

  Vector<double>& rv{v};

  rv[5] = 555;

  std::cout << v << std::endl;

  return 0;
}
