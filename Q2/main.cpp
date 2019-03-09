#include"libArr.h"
#include"libVec.h"
#include<iostream>
#include<chrono>
#include<ctime>

template<typename T>
double runTime(int (T::*& f)(int), int& n);

using currentTime = std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::nanoseconds>;

int main()
{    
    int (CLibArr::* pfArr) (int) {&CLibArr::counter}; //pointer to a function from class CLibArr
    int (CLibVec::* pfVec) (int) {&CLibVec::counter};
    
    for(int i = 1; i <= 10e6; i *= 10)
    {
        std::cout << "arr time for i = " << i << " is: " << runTime(pfArr, i) << "ms" << std::endl;
        std::cout << "vec time for i = " << i << " is: " << runTime(pfVec, i) << "ms" << std::endl;
        std::cout << std::endl;
    }
    return 0;
}

template<typename T>
double runTime(int (T::*& f)(int), int& n) {
    T dataType{}; //creat an object

    currentTime start{std::chrono::system_clock::now()};
    (dataType.*f)(n);
    currentTime end{std::chrono::system_clock::now()};

    std::chrono::duration<double> duration = end-start;
    return static_cast<double>(duration.count()) * 1000;
}