#if !defined(LIBVEC_H)
#define LIBVEC_H
#include<vector>

class CLibVec
{
private:
    std::vector<int> vec;
public:
    CLibVec();
    ~CLibVec();
    int counter(int n);

};


#endif // LIBVEC_H