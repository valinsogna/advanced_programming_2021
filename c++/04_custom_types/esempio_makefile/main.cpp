#include "my_class.hpp" //compiler needs just signature
#include <iostream>

int main(){
    point p;
    p.print();

    return 0;
}

/*
g++ -c main.cpp
g++ -c my_class.cpp
g++ main.o my_class.o -o exe.x
./exe.x
*/