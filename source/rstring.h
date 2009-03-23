/*====================================================================
		rstring.h

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

#ifndef _RSTRING_H
#define _RSTRING_H

unsigned char*	EXPORT fn_chr(ARG(short*, i));

short	EXPORT fn_ord(ARG(unsigned char*, s));

char*	EXPORT fn_ltrim(ARG(char*, s));
char*	EXPORT fn_rtrim(ARG(char*, s));
char*	EXPORT fn_trim(ARG(char*, s));
char*	EXPORT fn_repeattrim(ARG(char*, str1), ARG(char*, delim));

char*	EXPORT fn_substr(ARG(char*, s), ARG(long*, m), ARG(long*, n));

char*	EXPORT fn_strrepeat(ARG(char*, s), ARG(long*, c));
char*	EXPORT fn_longstrrepeat(ARG(char*, s), ARG(long*, c));

char*	EXPORT fn_strstuff(ARG(char*, s), ARG(long*, spos), ARG(long*, dcount), ARG(char*, is));
char*	EXPORT fn_longstrstuff(ARG(char*, s), ARG(long*, spos), ARG(long*, dcount), ARG(char*, is));

char*	EXPORT fn_strreplace(ARG(char*, s), ARG(char*, froms), ARG(char*, tos));
char*	EXPORT fn_longstrreplace(ARG(char*, s), ARG(char*, froms), ARG(char*, tos));

long	EXPORT fn_strpos(ARG(char*, str1), ARG(char*, str2));

long	EXPORT fn_strlen(ARG(char*, s));

long	EXPORT fn_strcount(ARG(char*, str1), ARG(char*, str2));
short	EXPORT fn_strcmp(ARG(char*, str1), ARG(char*, str2));

long	EXPORT fn_wordcount(ARG(char*, s), ARG(char*, delim), ARG(long*, flag));
char*	EXPORT fn_wordnum(ARG(char*, s), ARG(long*, n), ARG(char*, delim), ARG(long*, flag));

char*	EXPORT fn_padright(ARG(char*, s), ARG(short*, n), ARG(char*, c));
char*	EXPORT fn_longpadright(ARG(char*, s), ARG(short*, n), ARG(char*, c));
char*	EXPORT fn_padleft(ARG(char*, s), ARG(short*, n), ARG(char*, c));
char*	EXPORT fn_longpadleft(ARG(char*, s), ARG(short*, n), ARG(char*, c));
char*	EXPORT fn_c(ARG(char*, s));
char*	EXPORT fn_floattostr(ARG(double*, d), ARG(char*, fmt));
char*	EXPORT fn_inttostr(ARG(long*, l), ARG(char*, fmt));

char*	EXPORT fn_convertsymbols(ARG(char*, s), ARG(char*, source), ARG(char*, target));

#endif /* _RSTRING_H */
