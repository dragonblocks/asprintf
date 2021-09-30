/*
 * Copyright (c) 2021 Elias Fleckenstein <eliasfleckenstein@web.de>
 *
 * Based on libressl-portable:
 * Copyright (c) 2004 Darren Tucker.
 *
 * Based originally on asprintf.c from OpenBSD:
 * Copyright (c) 1997 Todd C. Miller <Todd.Miller@courtesan.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <errno.h>
#include <limits.h> /* for INT_MAX */
#include <stdarg.h>
#include <stdio.h> /* for vsnprintf */
#include <stdlib.h>

#define INIT_SZ	128

int
vasprintf(char **str, const char *fmt, va_list ap)
{
	int ret;
	va_list ap2;
	char *string, *newstr;
	size_t len;

	if ((string = malloc(INIT_SZ)) == NULL)
		goto fail;

	va_copy(ap2, ap);
	ret = vsnprintf(string, INIT_SZ, fmt, ap2);
	va_end(ap2);
	if (ret >= 0 && ret < INIT_SZ) { /* succeeded with initial alloc */
		*str = string;
	} else if (ret == INT_MAX || ret < 0) { /* Bad length */
		free(string);
		goto fail;
	} else {	/* bigger than initial, realloc allowing for nul */
		len = (size_t)ret + 1;
		if ((newstr = realloc(string, len)) == NULL) {
			free(string);
			goto fail;
		}
		va_copy(ap2, ap);
		ret = vsnprintf(newstr, len, fmt, ap2);
		va_end(ap2);
		if (ret < 0 || (size_t)ret >= len) { /* failed with realloc'ed string */
			free(newstr);
			goto fail;
		}
		*str = newstr;
	}
	return (ret);

fail:
	*str = NULL;
	errno = ENOMEM;
	return (-1);
}

int asprintf(char **str, const char *fmt, ...)
{
	va_list ap;
	int ret;

	*str = NULL;
	va_start(ap, fmt);
	ret = vasprintf(str, fmt, ap);
	va_end(ap);

	return ret;
}
