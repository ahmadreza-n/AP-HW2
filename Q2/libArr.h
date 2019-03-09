#if !defined(LIBARR_H)
#define LIBARR_H

class CLibArr
{
private:
    int* pArr; //for building dynamic array
public:
    CLibArr();
    ~CLibArr();

    int counter(int n);
};


#endif // LIBARR_H