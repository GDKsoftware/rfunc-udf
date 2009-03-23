/** \file  rmath_test.c
    
    \brief test unit for rmath module

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
   $Revision: 111 $ $Author: coopht $
   $Date: 2009-03-15 17:36:24 +0300 (Вск, 15 Мар 2009) $
 **************************************************************************/
#include <ibase.h>

#include "rt_util.h"

int main (int argc, char *argv[])
{
  isc_db_handle   db_handle = 0;
  ISC_STATUS_ARRAY status;
  char *db_file_name;
  const char *create_t  = "CREATE TABLE test_table (v_double DOUBLE PRECISION)";
 
  db_file_name = rt_create_db ();

   /* Connecting to newly created databse */
  if (isc_attach_database(status, 0, db_file_name, &db_handle, 0, NULL))
    fatalError (status, "attach_database");

  /* Creating new table */
  rt_exec_query (&db_handle, create_t);
  
  /* Registring function */
  rt_reg_func (&db_handle,
	       "FN_FACT", "DOUBLE PRECISION",  "DOUBLE PRECISION BY VALUE",
	       "fn_fact");
  rt_exec_query ( &db_handle, "INSERT INTO test_table VALUES (8)");

  BEGIN(1);

  rt_assert_double 
    (&db_handle, "SELECT FN_FACT (v_double) from test_table", 40320);

  END(1);

  isc_detach_database(status, &db_handle);
  free (db_file_name);

  return 0;
}
