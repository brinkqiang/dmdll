#include "libC.h"

int g_globalVar = 0;

void modifyGlobalVar(int value) {
    g_globalVar = value;
}
