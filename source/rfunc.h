/*====================================================================
		rfunc.h

		rFunc InterBase UDF library.


		Copyright 1998-2003 Polaris Software
		http://rfunc.sourceforge.net
		mailto:rFunc@mail.ru

	 This library is free software; you can redistribute it and/or
	 modify it under the terms of the GNU Lesser General Public
	 License as published by the Free Software Foundation; either
	 version 2.1 of the License, or (at your option) any later version.
	 See license.txt for more details.

====================================================================== */

#ifndef _RFUNC_H
#define _RFUNC_H

#if defined IB_6X
#define IB_5X
#endif

#if defined(IB_6X) || defined(IB_5X)
#include <ib_util.h>
#define MALLOC ib_util_malloc
#else
#include <malloc.h>
#define MALLOC malloc
#endif

#ifndef IB_START_YEAR
#define IB_START_YEAR 1900
#endif

#ifndef ISC_TIME_SECONDS_PRECISION
#define ISC_TIME_SECONDS_PRECISION          10000L
#endif

#include <ibase.h>

#if defined __STDC__ || defined __BORLANDC__ || defined _MSC_VER
#define PROTO(args) args
#define ARG(type, arg) type arg
#define ARGLIST(arg)
#else
#define PROTO(args) ()
#define ARG(type, arg) arg
#define ARGLIST(arg) arg;
#endif

#if defined __BORLANDC__ && defined __WIN32__
#define EXPORT _export
#else
#define EXPORT
#endif

#define MIN(x, y) (x < y) ? x : y
#define MAX(x, y) (x > y) ? x : y

#define ERREXIT(status, rc) {isc_print_status(status); return rc;}

#define BADVAL -9999L

#define shortlen 256
#define longlen 16384

char*	EXPORT fn_libname();
char*	EXPORT fn_libversion();

#endif /* _RFUNC_H */
