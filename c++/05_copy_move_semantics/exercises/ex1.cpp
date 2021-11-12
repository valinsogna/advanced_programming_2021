#include <memory>

enum class method {push_back, push_front};

template <typename T>
class List {
    struct node {
        T value;
        std::unique_ptr<node> next;
        node(const T& x, T*p): //ctor
        value{x}, // copy ctor invoked
        next{p} {} 

        //ctor for R value ref:
        node(T&& x, T*p): //ctor
        value{std::move(x)},
        next{p} {} 
    };
    std::unique_ptr<node> head;

 public:
  void insert(const T& x, method m){
    if(!head){  //head == nullptr (no need for head.get() == nullptr)
      //head.reset(new node{x,nullptr})
      head = std::make_unique<node>(x,nullptr)
      //make_unique it's a function that calls the default ctor
      //but if you specify <node> it calls your ctor
      //it takes the type of the unique_ptr
      //arguments should be passed altrim prende il default
      //make_unique returns a new unique_ptr, since the copt semantic has been deleted
      //the move semantics can be used
      return;
    }

    switch(m){
        case method::push_back:
            push_back(x);
            break;
        case method::push_front:
            push_front(x);
            break;
        default:
            std::cerr << "unknown insertion method" <<std:endl;
            break;
    }
  }

  void insert(T&& x, method m){}

 private:
  void push_back(const T& x){
      
  }
  void push_back(T&& x);
  void push_front(const T& x){
    //   auto tmp = new node{x, head.release()};
    //   head.reset(tmp);
    //These two lines casn be written in a more compact way:
    //head.reset(new node{x, head.release()});
    //or usign:
    head = std::make_unique<node>(x, head.release())
  }
  void push_front(T&& x);{ //not copy but a move! -> size_of() < area_of()
    //if I call:
    //head = std::make_unique<node>(x, head.release())//l-val or r-val ctor?
    //Since here I am giving a name 'x' to the obj => l-val
    //R value are passed to other functions as l-value!
    //Since there is no need to access x afterwards it's better to use:
    head = std::make_unique<node>(std::move(x), head.release())
    //what if you want to use x again??
  }
};