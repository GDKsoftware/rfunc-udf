/*====================================================================
		rstring.c

		rFunc InterBase UDF library.
		String functions.

		Copyright 1998-2003 Polaris Software
		http://rfunc.sourceforge.net
		mailto: rFunc@mail.ru

	 This library is free software; you can redistribute it and/or
	 modify it under the terms of the GNU Lesser General Public
	 License as published by the Free Software Foundation; either
	 version 2.1 of the License, or (at your option) any later version.
	 See license.txt for more details.

====================================================================== */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rfunc.h"
#include "rstring.h"
#include "rmath.h"

char *delims = " "; // empty delimiters

unsigned char* EXPORT fn_chr(ARG(short*, i))
ARGLIST(short *i)
{
	unsigned char *s = (unsigned char*) MALLOC (2);
	s[0] = (unsigned char) *i;
	s[1] = '\0';
	return s;
}

short EXPORT fn_ord(ARG(unsigned char*, s))
ARGLIST(unsigned char *s)
{
	return (short) s[0];
}

char* EXPORT fn_ltrim(ARG(char*, s))
ARGLIST(char *s)
{
	char *c;
	c = s;
	while (*c && strchr(delims, *c)) c++;
	return c;
}

char* EXPORT fn_rtrim(ARG(char*, s))
ARGLIST(char *s)
{
	long n;
	n = strlen(s);
	while (n && strchr(delims, s[n-1])) n--;
	s[n] = '\0';
	return s;
}

char* EXPORT fn_trim(ARG(char*, s))
ARGLIST(char *s)
{
	return fn_rtrim(fn_ltrim(s));
}

char*	EXPORT fn_repeattrim(ARG(char*, str1), ARG(char*, delim))
ARGLIST(char *str1)
ARGLIST(char *delim)
{
	char *s = str1, *d = str1;

//	while (*s == ' ') s++;
	if (delim[0])
		while (*s)
		{
			while (*s && (*s != delim[0])) *d++ = *s++;
			*d++ = *s++;
			while (*s == delim[0]) s++;
//			if (*s) *d++ = delim[0];
//			else *d++ = '\0';
		}
		*d = '\0';
	return str1;
}

char* EXPORT fn_substr(ARG(char*, s), ARG(long*, m), ARG(long*, n))
ARGLIST(char *s)
ARGLIST(long *m)
ARGLIST(long *n)
{
	long left, right;
	long len = strlen(s);

	left = (*m < 0) ? len + *m + 1 : *m;
	right = (*n < 0) ? left - 1 : left - 1 + *n - 1;
	left = (*n < 0) ? left + *n : left - 1;

	left = (left < 0) ? 0 : left;
	right = (right > len - 1) ? len - 1 : right;

	if (!*n || (left > len - 1) || (right < 0))
		return &s[len];

	s[right + 1] = '\0';
	return &s[left];
}

char* strnrepeat(ARG(char*, s), ARG(long*, c), ARG(long, maxlength))
ARGLIST(char *s)
ARGLIST(long *c)
ARGLIST(long maxlength)
{
	long i = 0;
	long j = 0;
	long l = strlen(s);
	long n = MIN(*c * l + 1L, maxlength);
	char *buffer = (char*) MALLOC (n);

	if (*s)
		while (i < n - 1L)
		{
			buffer[i++] = s[j++];
			if (!s[j]) j = 0;
		}
	buffer[i] = '\0';
	return buffer;
}

char* EXPORT fn_strrepeat(ARG(char*, s), ARG(long*, c))
ARGLIST(char *s)
ARGLIST(long *c)
{
	return strnrepeat(s, c, shortlen);
}

char* EXPORT fn_longstrrepeat(ARG(char*, s), ARG(long*, c))
ARGLIST(char *s)
ARGLIST(long *c)
{
	return strnrepeat(s, c, longlen);
}

char* strnstuff(ARG(char*, s), ARG(long*, spos), ARG(long*, dcount), ARG(char*, is), ARG(long, maxlength))
ARGLIST(char *s)
ARGLIST(long *spos)
ARGLIST(long *dcount)
ARGLIST(char *is)
ARGLIST(long maxlength)
{
	long i = 0;
	long j = 0;
	long l = 0;
	long slen = strlen(s), n, len;
	char *buffer;

	len = slen + strlen(is) + 1L;
	len = MIN(len, maxlength);
	buffer = (char*) MALLOC (len);

	n = (*spos > slen) ? slen : ((*spos > 0) ? *spos - 1 : 0);
	while (l < n) buffer[l++] = s[j++];
	while (is[i] && (l < len - 1L)) buffer[l++] = is[i++];
	j = MIN(j + *dcount, slen);
	while (s[j] && (l < len - 1L)) buffer[l++] = s[j++];

	buffer[l] = '\0';
	return buffer;
}

char* EXPORT fn_strstuff(ARG(char*, s), ARG(long*, spos), ARG(long*, dcount), ARG(char*, is))
ARGLIST(char *s)
ARGLIST(long *spos)
ARGLIST(long *dcount)
ARGLIST(char *is)
{
	return strnstuff(s, spos, dcount, is, shortlen);
}

char* EXPORT fn_longstrstuff(ARG(char*, s), ARG(long*, spos), ARG(long*, dcount), ARG(char*, is))
ARGLIST(char *s)
ARGLIST(long *spos)
ARGLIST(long *dcount)
ARGLIST(char *is)
{
	return strnstuff(s, spos, dcount, is, longlen);
}

char* strnreplace(ARG(char*, s), ARG(char*, froms), ARG(char*, tos), ARG(long, maxlength))
ARGLIST(char *s)
ARGLIST(char *froms)
ARGLIST(char *tos)
ARGLIST(long maxlength)
{
	long sn = strlen(froms);
	char *buffer = (char*) MALLOC (maxlength);
	char *sptr = s, *ptr = s, *bptr = buffer;

	while (ptr = strstr(ptr, froms))
	{
		while (sptr != ptr && (bptr-buffer<maxlength-1)) *bptr++ = *sptr++;
		sptr = tos;
		while (*sptr && (bptr-buffer<maxlength-1)) *bptr++ = *sptr++;
		ptr = ptr + sn;
		sptr = ptr;
	}
	while (*sptr && (bptr-buffer<maxlength-1))
		*bptr++ = *sptr++;
	*bptr = '\0';
	return buffer;
}

char* EXPORT fn_strreplace(ARG(char*, s), ARG(char*, froms), ARG(char*, tos))
ARGLIST(char *s)
ARGLIST(char *froms)
ARGLIST(char *tos)
{
	return strnreplace(s, froms, tos, shortlen);
}

char* EXPORT fn_longstrreplace(ARG(char*, s), ARG(char*, froms), ARG(char*, tos))
ARGLIST(char *s)
ARGLIST(char *froms)
ARGLIST(char *tos)
{
	return strnreplace(s, froms, tos, longlen);
}

long EXPORT fn_strpos(ARG(char*, str1), ARG(char*, str2))
ARGLIST(char *str1)
ARGLIST(char *str2)
{
	char *ptr;
	if (!*str1) return 0;
	ptr = strstr(str2, str1);
	return (ptr) ? (ptr-str2+1) : 0;
}

long EXPORT fn_strlen(ARG(char*, s))
ARGLIST(char *s)
{
	return strlen(s);
}

long EXPORT fn_strcount(ARG(char*, str1), ARG(char*, str2))
ARGLIST(char *str1)
ARGLIST(char *str2)
{
	char *ptr;
	long  r = 0;
	long  len = strlen(str1);

	if (!len || !*str2) return 0;
	ptr = str2;
	while (ptr = strstr(ptr, str1))
	{
		ptr += len;
		r++;
	}
	return r;
}

short EXPORT fn_strcmp(ARG(char*, str1), ARG(char*, str2))
ARGLIST(char *str1)
ARGLIST(char *str2)
{
	int r = strcmp(str1, str2);
	return (short) r;
}

long EXPORT fn_wordcount(ARG(char*, s), ARG(char*, delim), ARG(long*, flag))
ARGLIST(char *s)
ARGLIST(char *delim)
ARGLIST(long *flag)
{
	char *c = s;
	long r = 0;
	long d = 1;

	if (!*c) return r;
	while (*c)
		if (strchr(delim, *c++))
			d++; // counting words
		else {
			while (*c && !strchr(delim, *c)) c++;
			r++; // counting full words
		}
	if (*flag)
		return d;
	else
		return r;
}

char* EXPORT fn_wordnum(ARG(char*, s), ARG(long*, n), ARG(char*, delim), ARG(long*, flag))
ARGLIST(char *s)
ARGLIST(long *n)
ARGLIST(char *delim)
ARGLIST(long *flag)
{
	char *c = s, *ptr;
	long r = 1;

	if (!*c) return c;
	while (*c && r!=*n)
		if (strchr(delim, *c++)) {
			if (*flag)
				r++;
			else
				while (*c && strchr(delim, *c)) c++;
		} else {
			while (*c && !strchr(delim, *c)) c++;
			if (!*flag) r++;
		}
	if (!*flag)
		while (*c && strchr(delim, *c)) c++;
	ptr = c;
	while (*ptr && !strchr(delim, *ptr)) ptr++;
	*ptr = '\0';

	return c;
}

char* padnright(ARG(char*, s), ARG(short*, n), ARG(char*, c), ARG(long, maxlength))
ARGLIST(char *s)
ARGLIST(short *n)
ARGLIST(char *c)
ARGLIST(long maxlength)
{
	long i = 0;
	char *buffer;
	char *ptr = s;
	long len = MIN(*n + 1L, maxlength);

	buffer = (char*) MALLOC (len);
	while (*ptr && (i < len - 1L)) buffer[i++] = *ptr++;
	while ((i < *n) && (i < len - 1L)) buffer[i++] = *c;
	buffer[i] = '\0';
	return buffer;
}

char* EXPORT fn_padright(ARG(char*, s), ARG(short*, n), ARG(char*, c))
ARGLIST(char *s)
ARGLIST(short *n)
ARGLIST(char *c)
{ return padnright(s, n, c, shortlen); }

char* EXPORT fn_longpadright(ARG(char*, s), ARG(short*, n), ARG(char*, c))
ARGLIST(char *s)
ARGLIST(short *n)
ARGLIST(char *c)
{ return padnright(s, n, c, longlen); }

char* padnleft(ARG(char*, s), ARG(short*, n), ARG(char*, c), ARG(long, maxlength))
ARGLIST(char *s)
ARGLIST(short *n)
ARGLIST(char *c)
ARGLIST(long maxlength)
{
	long l = strlen(s), i = 0;
	char *buffer;
	char *ptr = s;
	long len = MIN(*n + 1L, maxlength);

	buffer = (char*) MALLOC (len);
	while ((i < *n - l) && (i < len - 1L)) buffer[i++] = *c;
	while (*ptr && (i < len - 1L)) buffer[i++] = *ptr++;
	buffer[i] = '\0';
	return buffer;
}

char* EXPORT fn_padleft(ARG(char*, s), ARG(short*, n), ARG(char*, c))
ARGLIST(char *s)
ARGLIST(short *n)
ARGLIST(char *c)
{ return padnleft(s, n, c, shortlen); }

char* EXPORT fn_longpadleft(ARG(char*, s), ARG(short*, n), ARG(char*, c))
ARGLIST(char *s)
ARGLIST(short *n)
ARGLIST(char *c)
{ return padnleft(s, n, c, longlen); }

char* EXPORT fn_c(ARG(char*, s))
ARGLIST(char *s)
{ return s; }

char* EXPORT fn_floattostr(ARG(double*, d), ARG(char*, fmt))
ARGLIST(double *d)
ARGLIST(char *fmt)
{
	char *buffer = (char *) MALLOC (shortlen);
	char	*s, slong[20];
	long	i;

	buffer[0] = '\0';
// Разбираем строку формата, пытаясь вычислить предполагаемы тип аргумента.
	// Каждый спецификатор преобразования начинается символом %
	if (s = strstr(fmt, "%"))
	{
		i = 1;
		while (strchr("+- #", s[i])) i++;
		while (strchr("0123456789", s[i])) i++;
		while (strchr(".", s[i])) i++;
		while (strchr("0123456789", s[i])) i++;
		if (strchr("diouxX", s[i]))
		{
			sprintf(slong, "%.0f", *d);
			i = atoi(slong);
			sprintf(buffer, fmt, i);
		}
		else
			sprintf(buffer, fmt, *d);
	}
	else
		sprintf(buffer, fmt, *d);
	return buffer;
}

char* EXPORT fn_inttostr(ARG(long*, l), ARG(char*, fmt))
ARGLIST(long *l)
ARGLIST(char *fmt)
{
	char *buffer = (char *) MALLOC (shortlen);

	sprintf(buffer, fmt, *l);
	return buffer;
}

char*	EXPORT fn_convertsymbols(ARG(char*, s), ARG(char*, source), ARG(char*, target))
ARGLIST(char *s)
ARGLIST(char *source)
ARGLIST(char *target)
{
	char	*c = s, *p;
	while (*c)
		if (p = strchr(source, *c))
			*c++ = target[p - source];
		else
			c++;
	return s;
}
