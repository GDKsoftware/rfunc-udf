/*====================================================================
		rfunc.c

		rFunc InterBase UDF library.
		Version functions.

		Copyright 1998-2003 Polaris Software
		http://rfunc.sourceforge.net
		mailto:rFunc@mail.ru

	 This library is free software; you can redistribute it and/or
	 modify it under the terms of the GNU Lesser General Public
	 License as published by the Free Software Foundation; either
	 version 2.1 of the License, or (at your option) any later version.
	 See license.txt for more details.

====================================================================== */

#include <string.h>
#include "rfunc.h"

char*	EXPORT fn_libname()
{
	char *buffer = (char*) MALLOC (6);
	strcpy(buffer, "rfunc");
	return buffer;
}

char*	EXPORT fn_libversion()
{
	char *buffer = (char*) MALLOC (8);
	strcpy(buffer, "2.1.3.2");
	return buffer;
}
