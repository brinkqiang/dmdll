# dmdll

Copyright (c) 2013-2018 brinkqiang (brink.qiang@gmail.com)

[![dmdll](https://img.shields.io/badge/brinkqiang-dmdll-blue.svg?style=flat-square)](https://github.com/brinkqiang/dmdll)
[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://github.com/brinkqiang/dmdll/blob/master/LICENSE)
[![blog](https://img.shields.io/badge/Author-Blog-7AD6FD.svg)](https://brinkqiang.github.io/)
[![Open Source Love](https://badges.frapsoft.com/os/v3/open-source.png)](https://github.com/brinkqiang)
[![GitHub stars](https://img.shields.io/github/stars/brinkqiang/dmdll.svg?label=Stars)](https://github.com/brinkqiang/dmdll) 
[![GitHub forks](https://img.shields.io/github/forks/brinkqiang/dmdll.svg?label=Fork)](https://github.com/brinkqiang/dmdll)

## Build status
| [Linux][lin-link] | [Mac][mac-link] | [Windows][win-link] |
| :---------------: | :----------------: | :-----------------: |
| ![lin-badge]      | ![mac-badge]       | ![win-badge]        |

[lin-badge]: https://github.com/brinkqiang/dmdll/workflows/linux/badge.svg "linux build status"
[lin-link]:  https://github.com/brinkqiang/dmdll/actions/workflows/linux.yml "linux build status"
[mac-badge]: https://github.com/brinkqiang/dmdll/workflows/mac/badge.svg "mac build status"
[mac-link]:  https://github.com/brinkqiang/dmdll/actions/workflows/mac.yml "mac build status"
[win-badge]: https://github.com/brinkqiang/dmdll/workflows/win/badge.svg "win build status"
[win-link]:  https://github.com/brinkqiang/dmdll/actions/workflows/win.yml "win build status"

## Intro
dmdll
```cpp

#include "dmdll.h"
#include "libA.h"
#include "libB.h"

int main( int argc, char* argv[] ) 
{
    Idmdll* LibAmodule = dmdllGetModule();
    Idmdll* LibBmodule = dmdllGetModule();    
    if (LibAmodule && LibBmodule)
    {
#ifdef _WIN32
        LibAmodule->DMLoadLibrary("libA.dll");
#else
        LibAmodule->DMLoadLibrary("liblibA.so");
#endif

#ifdef _WIN32
        LibBmodule->DMLoadLibrary("libB.dll");
#else
        LibBmodule->DMLoadLibrary("liblibB.so");

#endif

        using libAFunctionType = decltype(libAFunction);
        using libAFunctionTypeP = libAFunctionType*; 
        libAFunctionTypeP a = (libAFunctionTypeP)LibAmodule->DMGetProcAddress("libAFunction");
        a(20);
        using libBFunctionType = decltype(libBFunction);
        using libBFunctionTypeP = libBFunctionType*; 
        libBFunctionTypeP b = (libBFunctionTypeP)LibBmodule->DMGetProcAddress("libBFunction");
        b(40);

        LibAmodule->Release();
        LibBmodule->Release();
    }
    return 0;
}
```
## Contacts

## Thanks
