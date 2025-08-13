#include "dmdll.h"

#include <iostream>

// libA.h 和 libB.h 不再需要，因为函数签名直接在模板中指定

int main(int argc, char* argv[])
{
    // 2. 使用 dmdllPtr 智能指针进行自动生命周期管理
    dmdllPtr libAModule(dmdllGetModule());
    dmdllPtr libBModule(dmdllGetModule());

    if (libAModule && libBModule)
    {
#ifdef _WIN32
        libAModule->DMLoadLibrary("libA.dll");
        libBModule->DMLoadLibrary("libB.dll");
#else
        libAModule->DMLoadLibrary("liblibA.so");
        libBModule->DMLoadLibrary("liblibB.so");
#endif

        // 3. 使用 DmDllFunction 创建类型安全的函数包装器
        //    假设 libAFunction 的签名为 void(int)
        DmDllFunction<void(int)> libAFunc(*libAModule, "libAFunction");

        // 4. 像普通函数一样直接调用，无需任何转换
        std::cout << "Calling libAFunction(20)..." << std::endl;
        libAFunc(20);

        // 对 libBFunction 执行同样的操作
        // 假设 libBFunction 的签名为 void(int)
        DmDllFunction<void(int)> libBFunc(*libBModule, "libBFunction");
        std::cout << "Calling libBFunction(40)..." << std::endl;
        libBFunc(40);
    }

    // 5. 无需手动调用 Release()，dmdllPtr 会在对象离开作用域时自动处理
    return 0;
}