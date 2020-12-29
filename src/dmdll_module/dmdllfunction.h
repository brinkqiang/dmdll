
#ifndef __DMDLLFUNCTION_H__
#define __DMDLLFUNCTION_H__

#include "dmdllloader.h"

/**
 * ������������
 */
enum DllFuncType {
	DTF_CDECL,
	DTF_STDCALL
};

#include "dmargutil.h"

/**
 * ������װ����
 */
template<class _Fty> class DllFunc : public _Get_Base_Impl<_Fty>::_Type, public DMDllLoader {

	typedef typename _Get_Base_Impl<_Fty>::_Type DllFuncBase;

public:
	DllFunc(const char* name, DllFuncType type = DllFuncType::DTF_CDECL)
		: _name(name), _type(type) {
	}

	DllFunc(const char* path, const char* name, DllFuncType type = DllFuncType::DTF_CDECL)
		: _name(name), _type(type) {
		DMLoadLibrary(path);
	}

	template<class... Arg>
	typename DllFuncBase::_R operator() (Arg... arg) {

		if (callback == nullptr) {
			callback = DMGetProcAddress(_name);
		}

		if (callback != nullptr) {
			if (_type == DllFuncType::DTF_CDECL) {
				return ((_cdecl_ptr)callback)(arg...);
			}
			if (_type == DllFuncType::DTF_STDCALL) {
				return ((_stdcall_ptr)callback)(arg...);
			}
		}

		return DllFuncBase::_R();
	}

private:
	/**
	 * ������������
	 */
	DllFuncType _type;

	/**
	 * ����ָ��
	 */
	void* callback = nullptr;

	/**
	 * ��������
	 */
	const char* _name = nullptr;

};

#endif // __DMDLLFUNCTION_H__
