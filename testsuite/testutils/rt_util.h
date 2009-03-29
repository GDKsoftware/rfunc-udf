/** \file  rtutil.h
    
    \brief a special library with usefull routines for rfunc testing.

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
#ifndef __RT_UTIL_H_
#define __RT_UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <ibase.h>

#define fatalError(x, y) _fatalError(x, y, __FILE__, __LINE__)
#define BEGIN(x) printf("Sub Test : %d\n", x)
#define END(x) printf("Sub Test : %d Passed\n", x)

extern void _fatalError (ISC_STATUS_ARRAY status, 
			 const char *operation, 
			 const char *file,
			 const int line);

extern char* rt_create_db ();

extern void rt_exec_query (isc_db_handle *db, const char *query);

extern void rt_reg_func (isc_db_handle *db, 
			 const char *name,
			 const char *params,
			 const char *returns,
			 const char *entry_point);

extern 
void rt_assert (isc_db_handle *db, const char *query, const char *control);

extern 
void rt_assert_double (isc_db_handle *db, const char *query, double control);

extern 
void rt_assert_int (isc_db_handle *db, const char *query, int control);

extern 
void rt_assert_blob (isc_db_handle *db, const char *query, const char *control);

extern 
XSQLDA *rt_create_text_blob (isc_db_handle *db,
			     isc_tr_handle *tr,
			     const char *Text,
			     ISC_QUAD    *blob_id);

#endif /* __RT_UTIL_H_*/
