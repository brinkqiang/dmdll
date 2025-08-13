#include "libdmdll_impl.h"
#include <iostream>

#ifndef _WIN32
#include <dlfcn.h>
#endif

DmdllImpl::DmdllImpl()
    : m_moduleHandle(nullptr)
{
}

DmdllImpl::~DmdllImpl()
{
    this->DMFreeLibrary();
}

void DmdllImpl::Release(void)
{
    delete this;
}

bool DmdllImpl::DMLoadLibrary(const char* libraryPath)
{
    if (m_moduleHandle) {
        return false; // 已加载
    }

#ifdef _WIN32
    m_moduleHandle = ::LoadLibraryA(libraryPath);
#else
    //m_moduleHandle = ::dlopen(libraryPath, RTLD_LAZY);
    m_moduleHandle = ::dlopen(lib_path, RTLD_LAZY | RTLD_LOCAL);

#endif

    if (!m_moduleHandle) {
        // 可以根据需要添加错误日志
    }
    return m_moduleHandle != nullptr;
}

void DmdllImpl::DMFreeLibrary()
{
    if (m_moduleHandle) {
#ifdef _WIN32
        ::FreeLibrary(m_moduleHandle);
#else
        ::dlclose(m_moduleHandle);
#endif
        m_moduleHandle = nullptr;
    }
}

void* DmdllImpl::DMGetProcAddress(const char* functionName)
{
    if (!m_moduleHandle) {
        return nullptr;
    }

#ifdef _WIN32
    return (void*)::GetProcAddress(m_moduleHandle, functionName);
#else
    return ::dlsym(m_moduleHandle, functionName);
#endif
}

// 工厂函数实现
extern "C" DMEXPORT_DLL Idmdll* DMAPI dmdllGetModule()
{
    return new DmdllImpl();
}