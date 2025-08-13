#ifndef __DMDLLFUNCTION_H_INCLUDE__
#define __DMDLLFUNCTION_H_INCLUDE__

#include "dmdll.h"
#include <utility> // For std::forward

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

#endif // __DMDLLFUNCTION_H_INCLUDE__