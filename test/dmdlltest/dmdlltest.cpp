
#include "dmdll.h"

int main( int argc, char* argv[] ) {

    Idmdll* module = dmdllGetModule();
    if (module)
    {
        module->Test();
        module->Release();
    }
    return 0;
}
