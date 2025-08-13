
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "libdmdll_impl.h"
#include <iostream>

// 包含非 Windows 平台所需的头文件
#ifndef _WIN32
#include <dlfcn.h>
#endif

DmdllImpl::DmdllImpl()
    : m_hModule(nullptr)
{
}

DmdllImpl::~DmdllImpl()
{
    // 在析构时确保资源被释放
    this->DMFreeLibrary();
}

void DmdllImpl::Release(void)
{
    delete this;
}

void DmdllImpl::Test(void)
{
    // 注意：这里的逻辑直接从您提供的 dmdll_module.cpp 迁移而来。
    // 它会尝试加载名为 "dmdll.dll" 的库，这可能是指它自身。
    // 如果您在测试此功能，请确保该动态库位于可查找的路径中。
    if (!this->DMLoadLibrary("libdmdll.dll"))
    {
        std::cout << "Failed to load dmdll.dll" << std::endl;
        return;
    }

    PFN_dmdllGetModule module = (PFN_dmdllGetModule)this->DMGetProcAddress("dmdllGetModule");
    if (nullptr == module)
    {
        std::cout << "Failed to get dmdllGetModule" << std::endl;
        this->DMFreeLibrary();
        return;
    }

    Idmdll* p = module();
    if (p)
    {
        // 使用完毕后应释放，防止内存泄漏
        p->Release();
    }
    
    // 释放 Test 函数中加载的库
    this->DMFreeLibrary();
}

bool DmdllImpl::DMLoadLibrary(const char* path)
{
    if (m_hModule != nullptr) {
        // 已经加载了模块，如果需要重新加载，请先调用 DMFreeLibrary
        return false;
    }

#ifdef _WIN32
    m_hModule = ::LoadLibraryA(path);
#else
    m_hModule = ::dlopen(path, RTLD_LAZY | RTLD_LOCAL);
#endif

    return (m_hModule != nullptr);
}

void DmdllImpl::DMFreeLibrary()
{
    if (m_hModule != nullptr)
    {
#ifdef _WIN32
        ::FreeLibrary(m_hModule);
#else
        ::dlclose(m_hModule);
#endif
        m_hModule = nullptr;
    }
}

void* DmdllImpl::DMGetProcAddress(const char* name)
{
    if (m_hModule == nullptr)
    {
        return nullptr;
    }

#ifdef _WIN32
    return (void*)::GetProcAddress(m_hModule, name);
#else
    return ::dlsym(m_hModule, name);
#endif
}

extern "C" DMEXPORT_DLL Idmdll* DMAPI dmdllGetModule()
{
    return new DmdllImpl();
}