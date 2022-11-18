#include <Windows.h>
#include <lazy_importer/include/lazy_importer.hpp>

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
    system("pause");
    return 0;
}