
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

class Idmdll
{
public:
    virtual ~Idmdll(){}
    virtual void DMAPI Release(void) = 0;
	
    virtual void DMAPI Test(void) = 0;

    virtual bool DMAPI LoadLibrary(const char* path) = 0;
    virtual void DMAPI FreeLibrary() = 0;
    virtual void* DMAPI GetProcAddress(const char* name) = 0;
};

Idmdll* DMAPI dmdllGetModule();

typedef Idmdll* (DMAPI* PFN_dmdllGetModule)();
#endif // __DMDLL_H_INCLUDE__