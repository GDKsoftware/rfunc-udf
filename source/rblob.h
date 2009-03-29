/** \file  rblob.h
    
    \brief Blob functions.

 **************************************************************************
 *                                                                        *
 *                          rfunc UDF library                             *
 *                                                                        *
 **************************************************************************
    \Copyright
      Copyright 2009 PoleSoft Technologies Group
      http://www.polesoft.ru/project/rfunc
      mailto:support@polesoft.ru

      This library is free software; you can redistribute it and/or
      modify it under the terms of the GNU Lesser General Public
      License as published by the Free Software Foundation; either
      version 2.1 of the License, or (at your option) any later version.
      See license.txt for more details.
      
 **************************************************************************
 Last Changes:
   $Revision$ $Author$
   $Date$
 **************************************************************************/
#ifndef _RBLOB_H
#define _RBLOB_H

#include <ibase.h>
#include "rfunc.h"

/* Blob passing structure */

#if defined(IB_FIREBIRDSQL)
typedef BLOBCALLBACK BLOB;
#else
#if defined(_LP64) || defined(__LP64__) || defined(__arch64__)
typedef struct blob {
  short	(*blob_get_segment)();
  void	*blob_handle;
  int	blob_number_segments;
  int	blob_max_segment;
  int	blob_total_length;
  void	(*blob_put_segment)();
  int	(*blob_seek)();
} *BLOB;
#else
typedef struct blob {
  short	(*blob_get_segment)();
  void	*blob_handle;
  long	blob_number_segments;
  long	blob_max_segment;
  long	blob_total_length;
  void	(*blob_put_segment)();
  long	(*blob_seek)();
} *BLOB;
#endif
#endif /* defined(IB_FIREBIRDSQL) */

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
int EXPORT fn_b_strpos(ARG(char*, s), ARG(BLOB, b));
int EXPORT fn_b_textpos(ARG(char*, s), ARG(BLOB, b));
void EXPORT fn_b_strupper(ARG(BLOB, b), ARG(BLOB, out));
void EXPORT fn_b_strlower(ARG(BLOB, b), ARG(BLOB, out));

#endif /* _RBLOB_H */
