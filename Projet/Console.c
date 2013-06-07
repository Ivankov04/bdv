#include "Console.h"
#include "../Event/Event.h"
#include "./BureauDeVote.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void applog (char *who, char *format, ...)
{
    va_list args;
    char buffer[1024];

    clock_t now = bdv_get_ticks();

    snprintf(buffer, sizeof(buffer), "%.2f - (%s) : %s", now / 1000.0, who, format);

    va_start (args, format);
        vprintf (buffer, args);
    va_end (args);

    printf("\n");
}
