#include "libC.h"
#include <stdio.h>
int g_globalVar = 0;

void modifyGlobalVar(int value) {
    g_globalVar = value;

    printf("Global variable is now: %d, %p\n", g_globalVar, &g_globalVar);
}
