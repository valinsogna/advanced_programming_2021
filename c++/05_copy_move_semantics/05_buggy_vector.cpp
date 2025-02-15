#include <iostream>
#include <memory> //-> smart pointers
//SMART POINTER: unique_ptr
//See Q
// Interaface:
// - T* get()
// - void reset(T* p)
// - T* release()  => copy semantics must be defined by the user (also with raw ptr)
// Why? Since default copy ctor calls for release() which is a deleted function -> error
template <typename T>
class Vector {
  std::unique_ptr<T[]> elem;
  std::size_t _size;

 public:
  explicit Vector(const std::size_t length)
      : elem{new T[length]{}}, _size{length} {}

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return elem.get(); }
  T* begin() { return elem.get(); }

  const T* end() const { return elem.get() + _size; }
  T* end() { return elem.get() + _size; }
};

int main() {
  Vector<double> v1{7};
  // Vector<double> v2{v1}; // default copy ctor calls a deleted function
  return 0;
}
