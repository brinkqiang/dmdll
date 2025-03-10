#include "libB.h"
#include "../libC/libC.h"

void DMAPI libBFunction(int value) {
    modifyGlobalVar(value);
}
