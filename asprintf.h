#ifndef _DRAGONPORT_ASPINTF_H_
#define _DRAGONPORT_ASPINTF_H_

#include <stdarg.h>

int vasprintf(char **str, const char *fmt, va_list ap);
int asprintf(char **str, const char *fmt, ...);

#endif _DRAGONPORT_ASPINTF_H_
