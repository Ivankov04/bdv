#include "Console.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void applog (char *format, ...)
{
    va_list args;

    va_start (args, format);
        vprintf (format, args);
    va_end (args);

    printf("\n");
}
