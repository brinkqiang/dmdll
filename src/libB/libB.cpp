#include "libB.h"
#include "../libC/libC.h"

void libBFunction(int value) {
    modifyGlobalVar(value);
}
