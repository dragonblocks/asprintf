#ifndef _ASPINTF_H_
#define _ASPINTF_H_

#include <stdarg.h>

int vasprintf(char **str, const char *fmt, va_list ap);
int asprintf(char **str, const char *fmt, ...);

#endif // _ASPINTF_H_
