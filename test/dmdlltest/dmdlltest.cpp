
#include "dmdll.h"
#include "libA.h"
#include "libB.h"

int main( int argc, char* argv[] ) {

    Idmdll* LibAmodule = dmdllGetModule();
    Idmdll* LibBmodule = dmdllGetModule();    
    if (LibAmodule && LibBmodule)
    {
        LibAmodule->DMLoadLibrary("liblibA.so");

        LibBmodule->DMLoadLibrary("liblibB.so");

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
