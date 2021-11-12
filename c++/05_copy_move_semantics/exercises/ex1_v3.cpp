//In ex1 to much repetition
//use forwarding ref!
#include <iostream>
#include <memory>

enum class method {push_back, push_front};

template <typename node, typename T>
class iterator {
  node* current;
  public:
  using value_type = T;
  using reference = value_type&;
  using pointer = value_type*;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;

  //Iterartor types:
  //Forward it
  //Bidirectional it (Forward and Backwords)
  //Random access it ex.std::array[i]


  explicit iterator(node * x): current {x};
  reference operator*() const { return current->value; }
  _iterator& operator++(){ //pre-increment
    current = current->next.get();
    return *this;
  }
  _iterator operator++(int){
    auto tmp = *this;
    ++(*this);
    return tmp;
  }

  friend bool operator==(const iterator& x, const iterator& y){
    return x.current = y.current;
  }

  friend bool operator!=(const iterator& x, const iterator& y){
    return !(x = y);
  }
};

template <typename T>
class List {
    struct node {
        T value;
        std::unique_ptr<node> next;
        node(const T& x, T*p):
        value{x},
        next{p} {} 

        node(T&& x, T*p):
        value{std::move(x)},
        next{p} {} 
    };
    std::unique_ptr<node> head;

 public:
    void insert(const T& x, method m){ _insert(x,m); }   
    void insert(T&& x, method m){ _insert(std::move(x),m);}

    List() = default;
    List(List&&) = default;
    List& operator=(List&&) = default;

    List(const List& that){
      if(that.head)
        head = std::make_unique<node>(that.head);
    }

    List& operator=(const List& x){
      head.reset();
      auto tmp = x;
      (*this) = std::move(tmp);
      return *this;
    }

    auto begin() const{ const_iterator{ }}
    iterator begin(){}
      const_iterator end() const{}
    iterator end(){}


 private:
    //forwarding ref
    template <typename X>
    //When the type of X is deduced compared to T?
    //T is deduced when we create the List!
    //So line 34 this is a R-value ref since T has already been deduced but on the other hand,
    //when the func _insert is invoked, X will be deduced on the type of arguments passing to it
    void _insert(X&& x, method m){//X is deduced depending on the arg passed to func
        if(!head){
            head = std::make_unique<node>(std::forward<X>(x),nullptr)
        return;
        }
        switch(m){
            case method::push_back:
                push_back(std::forward(x));
                break;
            case method::push_front:
                push_front(std::forward(x));
                break;
            default:
                std::cerr << "unknown insertion method" <<std:endl;
                break;
        }
    }
    T* last_node(){
      auto tmp = head.get();
      while(tmp->next)
       tmp = tmp->next.get();
      return tmp;
    }
    void push_back(const T& x){
      auto tmp = last_node();
      tmp->next = std::make_unique<node>(x,nullptr);
    }
    void push_back(T&& x){
      last_node()->next = std::make_unique<node>(std::move(x),nullptr);
    }
    void push_front(const T& x){
      head = std::make_unique<node>(x, head.release())
    }
    void push_front(T&& x){
      head = std::make_unique<node>(std::move(x), head.release())
    }
};

template <typename T>
void foo(const List<int>& x){ //I will not change the list x
  auto it = x.begin();
  *it = 77; //Is it ok? It's returning the object, not a const object
  //I need const iterator: when it's derefernece retunrs a const reference and not just a ref

}

int main(){
  //In conflict between my custom ctor and the synthetize ctor,
  //Last one always wins!
  //Etc. std::vector<int> v(5,0) != std::vector<int> v{5,0}
  //         vector of 5 elem =0  1=   vector of 2 elem:5,0

  //OSS. std::vector<double> v(5,0.0) = std::vector<int> v{5,0.0}
  // 
    List<int> l;
    l.insert(3,method::push_front);// T has been already resolved
    l.insert(4,method::push_front);
    l.insert(5,method::push_front);

    for ( auto x:l)
        std::cout << x <<std::endl;
    return 0;
}