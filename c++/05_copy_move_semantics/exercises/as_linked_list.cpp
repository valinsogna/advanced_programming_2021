#include <algorithm> //std::find
#include <iostream>
#include <iterator>
#include <memory> //unique_ptr

enum class method { push_back, push_front };

// Implement to types for const and non iterators with one class!!!!
template <typename node, typename T>
class _iterator { // node is private and defined inside class List => template it!
  node* current;

 public:
 // From <iterator> we must specify:
  using value_type = T; 
  using reference = value_type&;
  using pointer = value_type*;
  using difference_type = std::ptrdiff_t; //#include <iterator>
  // There are several types of iterators:
  // - ones that go only forwards
  // - bidirectional iterators
  // - random access iterators

  // #include <iterator>:
  using iterator_category = std::forward_iterator_tag; // we didn't implement operator--, only ++

  explicit _iterator(node* x) : current{x} {} //ctor
  //const on right for status not changing assurance:
  reference operator*() const { return current->value; } //old: T&
  _iterator& operator++() {  // pre-increment ++i
    current = current->next.get();
    return *this;
  }
  _iterator operator++(int) {  // post-increment i++
    auto tmp = *this;
    ++(*this); // i++ is slower than ++i since it first return the copy and then increment it!
    return tmp;
  }
  friend bool operator==(const _iterator& x, const _iterator& y) {
    return x.current == y.current;
  }

  friend bool operator!=(const _iterator& x, const _iterator& y) {
    return !(x == y); // We can call the operator== since it is friend instead of:
    // x.current != y.current;
  }
};

template <typename T>
class List {
  struct node { // Useful nested since the template is the same!
    T value;
    std::unique_ptr<node> next; // l-value ctor
    node(const T& x, node* p) // ctor
        : value{x},  // copy ctor
          next{p} {}

    node(T&& x, node* p) // r-value ctor
        : value{std::move(x)},  // move ctor
          next{p} {}
    // a custom ctor
    explicit node(const std::unique_ptr<node>& p) : value{p->value} {
      if (p->next)
        next = std::make_unique<node>(p->next);
    }
  };
  std::unique_ptr<node> head; // at the begin of the list

 public:
  using iterator = _iterator<node, T>; // ref returned
  using const_iterator = _iterator<node, const T>; //const ref returned

  //With move semantics in C++11 is not a bad idea to pass by REF
  // Avoid code duplication:
  void insert(const T& x, method m) { _insert(x, m); } 
  void insert(T&& x, method m) { _insert(std::move(x), m); }

  List() = default; // Fine since there are NO raw ptr so everything is initialzed
  List(List&&) = default; // same
  List& operator=(List&&) = default; // move assign (no raw ptr)

  List(const List& that) { // copy ctor
  // Not default one since the default deletes the list because
  // it will invoke a copy ctor at each memeber but the ptr is unique -> error
    if (that.head) // I am in public BUT I can access private data of the same object of my type!
      head = std::make_unique<node>(that.head); // it calls the ctor of node explicit node
  }

  List& operator=(const List& x) { //copy assign
    head.reset();
    auto tmp = x;
    (*this) = std::move(tmp);
    return *this;
  }

  // Range-based for loop
  // We can't use raw ptr otherwise when ++ptr we won't go to the next node,
  // but to the next address. (const T* begin() const)
  // Iterator is an augmented ptr! Like a generalization of a ptr!
  auto begin() { return iterator{head.get()}; }
  auto end() { return iterator{nullptr}; }

  // We need a const operator (another type), but why?
  // We use const on the right for assuring compiler that
  // the memeber will not chnage the state of the obj List!
  // But in this case we are not trying to change the state:
  // we are defining a new type: a const iterator.
  auto begin() const { return const_iterator{head.get()}; } // But without const_iterator (just iterator) the bug *it = 77 is not spotted!
  auto end() const { return const_iterator{nullptr}; }

  // They return a const iterator too, but they are useful when calling
  // a ram iterator (that has right-access to my data) is better!
  auto cbegin() const { return const_iterator{head.get()}; }
  auto cend() const { return const_iterator{nullptr}; }

  // Since C++11 we can initialize our containers with a set of values immediatly:
  explicit List(std::initializer_list<T> l) {
    for (auto&& x : l)
      insert(std::move(x), method::push_back);
  }
  //OSS. std::initializer_list has HIGHER PRIORITY than any custom ctor that take same num of args
  //ex. List<int> l{4} -> calls 117 ctor 
 private:
  // X is != T
  // When X is deduced and when T?
  // T has been already deduced when calling in main 
  // l.insert(3,method::push_front) since insert() is invoked.
  // When _insert() is invoked instead, X will be deduced by the args passed to the function
  template <typename X>
  void _insert(X&& x, method m) {  // forwarding ref. (!= std::move) can accept r and l value ref!
  // Check if the list is empty
  /*
  To check if a `std::unique_ptr<T> p` is different from `nullptr`
  you can simply use `if(p)` (there is no need to write `if (p.get())`)
  */
    if (!head) {                   // head == nullptr
      // head.reset(new node{x,nullptr});
      // Recall:
      // void reset(T* ptr=nullptr)` deletes `current_ptr` (if any) and set `current_ptr = ptr`.
      
      // BUT BETTER USE make_unique!
      head = std::make_unique<node>(std::forward<X>(x), nullptr);
      // func make_unique takes as arg the constructor of the object!
      // and returns a unique_ptr to the newly created object.
      // You can pass no args => deafult ctor
      // Or custom ctors!
      
      return; // exit from the function
    }
    switch (m) {
      case method::push_back:
        push_back(std::forward<X>(x));
        break;
      case method::push_front:
        push_front(std::forward<X>(x));
        break;
      default:
        std::cerr << "unknown insertion method" << std::endl;
        break;
    };
  }

  node* last_node() { 
    auto tmp = head.get();
    //since we don't know how long is the list we perfrom a while loop (not a for)
    while (tmp->next)  // tmp->next != nullptr
      tmp = tmp->next.get(); // we can safely access tmp next since in insert() we already checked it
    return tmp;
  }

  void push_back(const T& x) {
    auto tmp = last_node();
    tmp->next = std::make_unique<node>(x, nullptr);
  }
  void push_back(T&& x) {
    last_node()->next = std::make_unique<node>(std::move(x), nullptr);
  }

  void push_front(const T& x) {
    // I must change the head ptr to the new pushed node!
    // / not .get() otherwise 2 ptr pointing same node! NO uniqueness!
    // So use .release()!
    /* Recall:
      - `T* release()` Releases the ownership of the managed object 
        if any. `get()` returns `nullptr` after the call.
      - `void reset(T* ptr=nullptr)` Delete `current_ptr` (if any) and set `current_ptr = ptr`.
    */

    // auto tmp = new node{x,head.release()}; // tmp is a RAW ptr, not a smart one!
    // head.reset(tmp); // must delete it since head is gonna be another ptr to the new head!

    // These 2 lines csn be rewritten in 1 short:
    // head.reset(new node{x,head.release()});

    // OR using make_unique:
    head = std::make_unique<node>(x, head.release());

    // auto tmp = std::make_unique<node>(x,head.release());
    // head.swap(std::make_unique<node>(x,head.release())); //move swap same things!
  }
  void push_front(T&& x) { //R-value 
    // head = std::make_unique<node>(x,head.release()); // calls l-val ctor: x has a name!
    // R-value ref are passed byt other func as l-values since they have a name!
    head = std::make_unique<node>(std::move(x), head.release());  // calls r-val ctor
    // Why not simply x but std::move(x)? We wanted the ctor like that!
    /*
    Recall:
    It changes an expression from being an l-value (such as a named variable)
     to being an r-value.
    You're allowing the compiler to cannibalize x.
    */
  }
};

template <typename T>
void foo(const List<T>& x) {
  auto it = x.begin();
  // *it = 77; is it a bug if we are without begin() const implementation? 
  // No, cause even though the dereference operator of iterator class is const,
  // the compiler isn't smart enough to do a check on the iterator!
  // So we must implement a class for const iterators that (only difference)
  // when it is dereferenced returns a const reference (not a reference).
  
  // How to build this other class?
  // We could template the existing class on the returned value.

  // Now "*it = 77;" is illegal,
  // since we are passing a const List that has infact a const iterator that
  // when dereferenced, returns a const iterator.
}

int main() {
  List<int> l{4, 5, 6, 7, 7}; //thanks to ctor line 117

  // Vector has a couple of ctors:
  // - std::vector<double> v{5, 0.0}  ->  {number of elem, default value for each elemx}
  // - std::vector<int> v{5,0} -> Conflict: is it calling ther same or plain vector with 2 elem?
  // It's a vector with 2 elem, but if I want to choose the other I must use ():
  // std::vector<int> v(5,0);
  std::vector<double> v{5, 0.0}; // No conflict: 
  // std::initializer_list<T> wants tinghs of the same type!

  // l.insert(3,method::push_front);
  // l.insert(4,method::push_front);
  // l.insert(5,method::push_back);

  // foo(l);
  
  // Let's use an algorithm:
  auto it = std::find(l.cbegin(), l.cend(), 43);
  // OSS. Must specify the type of iterator used for range based loop:
  // iterator_category = std::forward_iterator_tag; and those 4 lines.
  // If we comment it than find() won't work! Why?
  // Since algorithm funcs have been specalized on thew type of iterators we have!

  //How to check is it found smthing:
  if (it != l.cend()) {
    // found!!
  }

  for (auto x : l)
    std::cout << x << std::endl;
}

// Type-dispatch mechanism:
// We write a func with the categories of the opertor 
// that we have got

template <typename I>
void foo(I first, I last, std::forward_iterator_tag) {}

template <typename I>
void foo(I first, I last, std::random_access_iterator_tag) {}

template <typename I>
void foo(I first, I last) {
  // when you have a scoped type and templates u must prepend it!
  foo(first, last, typename I::iterator_category{});
}
