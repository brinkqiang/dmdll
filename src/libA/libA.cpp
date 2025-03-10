#include "libA.h"
#include "../libC/libC.h"

void libAFunction(int value) {
    modifyGlobalVar(value);
}
