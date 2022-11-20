#include <Windows.h>
#include <stdio.h>

class myclass1
{
public:
    virtual unsigned int get() const { return 1; }
};

class myclass2 : public myclass1
{
public:
    virtual unsigned int get() const override { return 2; }

public:
    myclass2(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
    {
        printf("111:a=%d,b=%d,c=%d,d=%d\n", a, b, c, d);
    }

    // crashed in this function
    myclass2(unsigned int a, unsigned int b, unsigned int c) : myclass2(a, b, get(), c)
    {
        printf("222:a=%d,b=%d,c=%d\n", a, b, c);
    }
};

void
test_ctor_1()
{
    printf("test_ctor_1 begin\n");
    myclass2 m(1, 2, 3);
    printf("%d\n", m.get());
    printf("test_ctor_1 end\n");
}