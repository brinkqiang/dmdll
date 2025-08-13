
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

#ifndef __DMDLL_H_INCLUDE__
#define __DMDLL_H_INCLUDE__

#include "dmos.h"
#include "dmmoduleptr.h"
#include <utility> // For std::forward

class Idmdll;
typedef DmModulePtr<Idmdll> dmdllPtr;

/**
 * @brief 动态库加载与管理接口
 */
class Idmdll
{
public:
    virtual ~Idmdll(){}
    virtual void DMAPI Release(void) = 0;

    // 恢复为原始接口命名
    virtual bool DMAPI DMLoadLibrary(const char* libraryPath) = 0;
    virtual void DMAPI DMFreeLibrary() = 0;
    virtual void* DMAPI DMGetProcAddress(const char* functionName) = 0;
};


// 恢复为原始工厂函数命名
extern "C" DMEXPORT_DLL Idmdll* DMAPI dmdllGetModule();
typedef Idmdll* (DMAPI* PFN_dmdllGetModule)();


/**
 * @brief C++风格的函数调用约定
 */
enum class DmCallConvention {
    Cdecl,
    Stdcall
};

// 主模板声明
template<typename T>
class DmDllFunction;

/**
 * @brief 类型安全的动态库函数封装器 (可变参数模板特化版本)
 * @tparam R 函数返回类型
 * @tparam Args 函数参数类型包
 */
template<typename R, typename... Args>
class DmDllFunction<R(Args...)>
{
public:
    using CdeclPtr = R(__cdecl*)(Args...);
    using StdcallPtr = R(__stdcall*)(Args...);

    DmDllFunction(Idmdll& manager, const char* functionName, DmCallConvention convention = DmCallConvention::Cdecl)
        : m_manager(manager),
          m_functionName(functionName),
          m_callConvention(convention) {}

    R operator()(Args... args)
    {
        if (!m_functionPtr) {
            m_functionPtr = m_manager.DMGetProcAddress(m_functionName);
        }

        if (!m_functionPtr) {
            return R{};
        }

        if (m_callConvention == DmCallConvention::Cdecl) {
            return (reinterpret_cast<CdeclPtr>(m_functionPtr))(std::forward<Args>(args)...);
        } else {
            return (reinterpret_cast<StdcallPtr>(m_functionPtr))(std::forward<Args>(args)...);
        }
    }

private:
    Idmdll& m_manager;
    const char* m_functionName;
    DmCallConvention m_callConvention;
    void* m_functionPtr = nullptr;
};

#endif // __DMDLL_H_INCLUDE__