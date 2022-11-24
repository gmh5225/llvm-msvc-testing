#include <Windows.h>
#include <stdio.h>
#include <intrin.h>
#include <lazy_importer/include/lazy_importer.hpp>

void
test_ctor_1();

///////////////////////////////////////////////////////////////////////////////////
#pragma comment(linker, "/SECTION:.CODE,ERW")
__declspec(allocate(".CODE")) int a_CodData{0xAA};

#pragma code_seg(push, label, ".CODE")
DECLSPEC_NOINLINE
void
test_conflict_section()
{
    printf("hi\n");
}
#pragma code_seg(pop, label)

void
test_lazy_importer()
{
    LI_FN(OutputDebugStringA)("hello world");
    LI_FN(VirtualProtect).cached();
}

#define Np_memcpy(dst, src, size) __movsb((BYTE *)dst, (const BYTE *)src, size)
#define Np_memset(dst, val, size) __stosb((BYTE *)dst, val, size)
#define Np_ZeroMemory(dst, size) __stosb((BYTE *)dst, 0, size)

#ifdef __clang__
__attribute((force_align_arg_pointer))
#endif
void
test_memset()
{
    char pTempDll[250]; // = { 0 };
    Np_ZeroMemory(pTempDll, sizeof(pTempDll));
    for (int i = 0; i < 250; ++i)
    {
        printf("%d\n", pTempDll[i]);
    }
    unsigned char temp2[2] = {0xaa, 0xbb};
    Np_memcpy(pTempDll, temp2, 2);
    for (int i = 0; i < 10; ++i)
    {
        printf("%d\n", pTempDll[i]);
    }
}

#define PRTOUT(X)
int
main()
{
    test_memset();
    test_lazy_importer();
    test_conflict_section();
    printf("a_CodData=%x\n", a_CodData);
    test_ctor_1();
    int rs = 2;
    PRTOUT("xx:0x%08X", rs);
    system("pause");
    return 0;
}