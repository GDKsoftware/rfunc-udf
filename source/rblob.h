/*====================================================================
		rblob.h

		rFunc InterBase UDF library.
		Blob functions.

		Copyright 1998-2003 Polaris Software
		http://rfunc.sourceforge.net
		mailto:rFunc@mail.ru

	 This library is free software; you can redistribute it and/or
	 modify it under the terms of the GNU Lesser General Public
	 License as published by the Free Software Foundation; either
	 version 2.1 of the License, or (at your option) any later version.
	 See license.txt for more details.

====================================================================== */

#ifndef _RBLOB_H
#define _RBLOB_H

#include <ibase.h>
#include "rfunc.h"

/* Blob passing structure */

#if defined(IB_FIREBIRDSQL)
typedef BLOBCALLBACK BLOB;
#else
typedef struct blob {
    short	(*blob_get_segment)();
    int		*blob_handle;
    long	blob_number_segments;
    long	blob_max_segment;
    long	blob_total_length;
    void	(*blob_put_segment)();
    long	(*blob_seek)();
} *BLOB;
#endif // defined(IB_FIREBIRDSQL)

long EXPORT fn_b_number_segments (ARG(BLOB, b));
long EXPORT fn_b_max_segment (ARG(BLOB, b));
long EXPORT fn_b_total_length (ARG(BLOB, b));

long EXPORT fn_b_line_count (ARG(BLOB, b));
char* EXPORT fn_b_substr(ARG(BLOB, b), ARG(long*, m), ARG(long*, n));
char* EXPORT fn_b_longsubstr(ARG(BLOB, b), ARG(long*, m), ARG(long*, n));
char* EXPORT fn_b_line(ARG(BLOB, b), ARG(long*, l));
char* EXPORT fn_b_longline(ARG(BLOB, b), ARG(long*, l));

void EXPORT fn_b_put_segment(ARG(char*, s), ARG(BLOB, b));

short EXPORT fn_b_strcmp(ARG(BLOB, b1), ARG(BLOB, b2));
long EXPORT fn_b_strpos(ARG(char*, s), ARG(BLOB, b));
long EXPORT fn_b_textpos(ARG(char*, s), ARG(BLOB, b));

#endif /* _RBLOB_H */
