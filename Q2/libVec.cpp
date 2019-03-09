#include"libVec.h"

CLibVec::CLibVec()
{
}

CLibVec::~CLibVec()
{
}

int CLibVec::counter(int n){
    int sum{};
    for(int i = 0; i < n; i++)
    {
        vec.push_back(i);
        sum += vec[i];
    }
    return sum;
}