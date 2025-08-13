
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

#ifndef __LIBDMDLL_IMPL_H_INCLUDE__
#define __LIBDMDLL_IMPL_H_INCLUDE__

#include "dmdll.h"

// 为跨平台定义模块句柄类型
#ifdef _WIN32
    #include <Windows.h>
    using DM_HMODULE = HMODULE;
#else
    using DM_HMODULE = void*;
#endif


class DmdllImpl : public Idmdll
{
public:
    DmdllImpl();
    virtual ~DmdllImpl();

    // Idmdll 接口实现
    virtual void DMAPI Release(void) override;
    virtual bool DMAPI DMLoadLibrary(const char* libraryPath) override;
    virtual void DMAPI DMFreeLibrary() override;
    virtual void* DMAPI DMGetProcAddress(const char* functionName) override;

private:
    DM_HMODULE m_moduleHandle;
};

#endif // __LIBDMDLL_IMPL_H_INCLUDE__