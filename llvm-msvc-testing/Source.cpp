#include <Windows.h>
#include <stdio.h>
#include <lazy_importer/include/lazy_importer.hpp>

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

int
main()
{
    test_lazy_importer();
    test_conflict_section();
    printf("a_CodData=%x\n", a_CodData);
    system("pause");
    return 0;
}