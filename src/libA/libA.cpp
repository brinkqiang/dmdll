#include "libA.h"
#include "../libC/libC.h"

void DMAPI libAFunction(int value) {
    modifyGlobalVar(value);
}
