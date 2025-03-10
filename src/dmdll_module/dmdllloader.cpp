#include <stdio.h>
#include <assert.h>

/**
* 封装assert宏，提供运行时级别的友好的错误信息
*/

#define ASSERT_STRING(_Expression, ...) \
	(void)((!!(_Expression)) || (printf(__VA_ARGS__), printf("\n"), 0) || (assert(_Expression), 0))

#include "dmdllloader.h"

#ifndef _WIN32
#include <dlfcn.h>
#endif

namespace /* 匿名命名空间保护本文件内部函数 */ {

	HMODULE DMLoadDll(const char* path) {
#ifdef _WIN32
		return ::LoadLibraryA(path);
#else
		return dlopen(path, RTLD_LAZY | RTLD_LOCAL);
#endif
	}

	void DMFree(HMODULE hModule) {
#ifdef _WIN32
		::FreeLibrary(hModule);
#else
		dlclose(hModule);
#endif
	}

	void* DMGetProc(HMODULE hModule, const char* procName) {
		void* addr =
#ifdef _WIN32
			::GetProcAddress(hModule, procName);
#else
			dlsym(hModule, procName);
#endif
		return addr;
	}
}

DMDllLoader::DMDllLoader() :
	m_hModule(nullptr) {
}

DMDllLoader::~DMDllLoader(void) {
	DMFreeLibrary();
}

bool DMDllLoader::DMLoadLibrary(const char* path) {
	if (m_hModule == nullptr) {
		m_hModule = ::DMLoadDll(path);
	} else {
		ASSERT_STRING(false, "already load, please use Free() before.");
	}
	return (m_hModule != nullptr);
}

void DMDllLoader::DMFreeLibrary() {
	if (m_hModule != nullptr) {
		::DMFree(m_hModule);
		m_hModule = nullptr;
	}
}

void* DMDllLoader::DMGetProcAddress(const char* name) {
	if (m_hModule == nullptr) {
		return nullptr;
	}
	return ::DMGetProc(m_hModule, name);
}