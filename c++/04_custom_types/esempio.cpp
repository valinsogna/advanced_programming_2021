/*
We are trying to replicate the std type vector as a class
*/
#include <iostream>
#include <string>

template <typename T>
class Vector{
    T* data; //T& data; DONT USE REF AS MEMBER TYPE
    std::size_t _size;
    
public:
//Resource Aquisition Is Initialization RAII:
//In C++ is implemented by defining Constructor and Destructor
    Vector(const std::size_t size): data{new T[size]}, _size{size} {}
    ~Vector(){ delete[] data; }
    // If I us the destructor there won't be memory leak;
    // The user can touch data, size_t
    auto size() const { return _size; }
    //Only member func can have a const on the right
    //Const on the right means I can't modifiy the state 
    //(and not that the returned type of func size is const!)
    //The compiler is like he is making const:
    //    const T* data; -> actually T* const data;! Meaning that 
    //if I change the ref of the data my compiler will complain, 
    //but if I change the values won't. -> use less rough pointers!
    //    const std::size_t _size;
    //and than he checks whether line 16 is ok
    
    T& operator[](const std::size_t i) { return data[i]; }
    const T& operator[](const std::size_t i) const { return data[i]; }

    T* begin() { return data; } // a begin when I can modify elements as well
    const T* begin() const { return data; } //a begin when I have a const ref to the top
    
    T* end() { return data + size_t; } // a begin when I can modify elements as well
    const T* end() const { return data + size_t; }
    //When you are inside the class you can omit <T>!
    //Instead of Vector<T>&, Vector&
    friend std::ostream& operator<<(std::ostream& os, const Vector& v){
        os << v.data << ": ";
        // for(std::size_t i{0}; i < v.size(); ++i)
        //     os << v[i] << " ";
        //RANGE BASED FOR LOOP
        for(const auto& x : v) //BASED ON SENTINEL APPROCH: begin/end
            os << x << " ";
        //This is what the compilers do in range based loop for:
        // {
        //     auto first = v.begin();
        //     const auto last = v.end();
        //     for(; first != last; ++first){
        //         const auto& x = *first;
        //         os << x << " ";

        //     }
        // }
        os << std::endl;
        return os;
    }
    // template <typename OT>
    // friend std::ostream& operator<<(std::ostream& os, const Vector<OT>& v);
};

int main(){
    Vector<int> v{7};

    v[5] = 99;//non-const operator
    std::cout << v;
    return 0;
}


// template <typename T>
// std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {} 

template <typename T>
void foo(const Vector<T>& v){
    v.size(); //doesn't compile if size is not const on the roght
    //because for the compiler the func 
    //size could modify the Vector
    std::cout << v[0] << std::endl; //does it compile? 
    //NO the invocation of this function isn't in compliance with the fact that he may change my private memebrs
    // It's like using: v.operator[](0)
    //What do we do then? Func overloading line 26 so now it compiles

}
