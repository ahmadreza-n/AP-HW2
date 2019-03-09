#include"libArr.h"

CLibArr::CLibArr()
{
}

CLibArr::~CLibArr()
{
    delete[] pArr;
}

int CLibArr::counter(int n){
    pArr = new int[n];
    int sum{};
    for(int i = 0; i < n; i++)
    {
        *(pArr + i) =  i;
        sum += *(pArr + i);
    }
    return sum;
}