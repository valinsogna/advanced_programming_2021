//In ex1 to much repetition
//use forwarding ref!

#include <memory>

enum class method {push_back, push_front};

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
    void push_front(T&& x);{
      head = std::make_unique<node>(std::move(x), head.release())
    }
};

int main(){
    List<int> l;
    l.insert(3,method::push_front);// T has been already resolved

    return 0;
}