#include <iostream>
#include <cstddef>
#include <memory>
//We are using plain pointer, no smart
template <typename T, typename Allocator=std::allocator<T> >
class vector{
    T* data{nullptr};
    std::size_t _size{0};
    std::size_t _capacity{0}; //how big is the array that I have allocated
    Allocator allocator;

    template <typename X>
    void _push_back(X&& x, ){
        if(_size == 0) reserve();
        check_capacity();
        data[_size] = std::forward<X>(x);
        ++_size;
    }
    void check_capacity(){//there may be cases in which I don't need to allocate a bigger array
        if(_size < _capacity) return;
        //_size = _capacity
        //_size != 0
        reserve(_size*2); //public function that preallocates your array
    }

    void clean_data(){
        for (std::size_t i{0}; i<_size; ++i)
            traits_alloc::construct(allocator, data+i);
        raits_alloc::deallocate(allocator, data, _capacity);
    }


    void move_data_to(T* tmp){
        //std::copy(data, data+_size, tmp);//Since C++14 BY COPY
        //Since C+++17 we have std::move
        //But let's do it by hand with a for loop;
        // for (std::size_t i{0}; i<_size; ++i)
        //     tmp[i] = std::move(data[i]); //BY MOVE

        //std::uninitialized_move(data, data+_size,tmp); //Since C++17
        //In C++14:
        for (std::size_t i{0}; i<_size; ++i)
            //new(tmp+i) T{std::move(data[i])}//placement new
            traits_alloc::construct(allocator, tmp+i, std::move(data[i]));

        //delete[] data;//MOVE DOESN'T DELETE!!!! Delet calls the structure ( destuctor )and then release the memory
        // for (std::size_t i{0}; i<_size; ++i)
        //     //new(tmp+i) T{std::move(data[i])}//placement new
        //     traits_alloc::construct(allocator, data+i);
        //     traits_alloc::deallocate(allocator, data, _capacity);
        clean_data();
        data = tmp;
    }

public:
    using traits_alloc = std::allocator_traits<Allocator>; //It's a type that provide unified interface for allocating/constrcting/destroing things
    vector()= default;
    ~vector(){
        if(data) delete[] data;
    }

    vector(Allocator a): allocator{std::move(a)} {};

    void reserve(std::size_t n){
        //auto tmp = new T[n]; //may invoke default ctors
        //NOW we simply want to allocate raw memory:
        auto tmp = traits_alloc(); //FINIRE
        move_data_to(tmp); 
        _capacity = n; //increase capacity to n
    }

    void push_back(const T& x){
        _push_back(x);
    }
    void push_back(T&& x){
        _push_back(std::move(x));
    }
    auto size() const { return _size;}
    auto capacity() const { return _capacity;}
};

int main(){
    vector<int> v;
    for(auto i=0; i<33: ++i){
        v.push_back(i);
        std::cout << v.capacity() << ',' << v.size() << std::endl;
    }
    return 0;
}

//We are using more synthetize ctor than std::vector!
//WHY? Because we are using std::move and line 42 (RIASCOLTA)
