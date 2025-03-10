
#ifndef __DMDLLLOADER_H__
#define __DMDLLLOADER_H__


#ifndef _WIN32
typedef void* HMODULE;
#else
#include <Windows.h>
#endif

/**
 * 动态链接/共享库包装类
 */
class DMDllLoader {

public:
	/**
	 * 构造函数
	 */
	DMDllLoader();

	/**
	 * 析构函数
	 */
	virtual ~DMDllLoader();

	/**
	 * 加载模块。重复加载前务必
	 * 调用Free()释放已加载模块。
	 *
	 * @param path
	 *        模块的绝对路径
	 */
	bool DMLoadLibrary(const char* path);

	/**
	 * 释放模块
	 */
	void DMFreeLibrary();

	/**
	 * 获取函数入口
	 *
	 * @param name
	 *        导出函数的名称
	 * @return 返回加载的函数指针。
	 */
	void* DMGetProcAddress(const char* name);

private:
	/**
	 * 绝对不需要拷贝使用!
	 */
	DMDllLoader(const DMDllLoader&) = delete;
	DMDllLoader operator=(const DMDllLoader&) = delete;

protected:
	/**
	 * 模块句柄
	 */
	HMODULE m_hModule;

};

#endif // __DMDLLLOADER_H__
