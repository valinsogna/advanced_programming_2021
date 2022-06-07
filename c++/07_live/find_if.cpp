#include <chrono>
#include <iostream>
#include <vector>
// FIND through smthing in a range has 2 checks:
// - check if you are sytill inside range
// _ check if you have found it
template <typename I, typename T>
// I is bidirectional iterator: first and one last-past last element
// returning an iterator is good since in std library there is only binary search
// that returns true/false but you may want to access the element.
I find(I first, I last, T value) {
  // FIRST ATTEMPT:
  // if (first == last)
  //   return last; //out of range
  // while (first != last && *first != value) //O(2n) worst case scenario for number of operations (2 checks)
  //   ++first;
  // return first;
  //If I know that the value is in the range I can miss the check 'first != last'
  // Then the time is reduced to O(n)!
  // How can then I be sure that the value is in the range?
  // SECOND ATTEMPT:
  // I put it in the last element of the range!!
  // Sentinel trick!
  --last;
  auto tmp = std::move(*last);
  if (tmp == value)
    return last;
  *last = value;

  while (*first != value)
    ++first;

  *last = std::move(tmp);

  if (first == last)
    return ++last; //one past the last elem

  return first;
}

template <typename T>
int bar(T x) {
  return *x + 76;
}

template <typename T>
void foo(T x) {
  std::cout << (bar(x) & 63) << std::endl;
}
int main() {
  std::vector<int> v;
  for (auto i = 0; i < 1'000'000'001; ++i)
    v.emplace_back(i);

  auto t0 = std::chrono::high_resolution_clock::now();
  auto x = find(v.begin(), v.end(), 834'794'723);
  auto t1 = std::chrono::high_resolution_clock::now();

  auto t = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
  std::cout << t.count() << std::endl;

  // foo(x);

  if (x == v.end())
    std::cout << "not found" << std::endl;
  else
    std::cout << "found " << *x << std::endl;
}
