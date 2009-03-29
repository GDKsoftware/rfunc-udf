/** \file  rdatetime_test.c
    
    \brief test unit for rdatetime module

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
#include <ibase.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "rt_util.h"

int main (int argc, char *argv[])
{
  isc_db_handle   db_handle = 0;
  char *db_file_name;
  ISC_STATUS_ARRAY status;
 
  db_file_name = rt_create_db ();

   /* Connecting to newly created databse */
  if (isc_attach_database(status, 0, db_file_name, &db_handle, 0, NULL))
    fatalError (status, "attach_database");

  /* Declaring required function */
  rt_reg_func (&db_handle, 
	       "DATETOSTR", "DATE, CSTRING(256)", 
	       "CSTRING(256) FREE_IT",
	       "fn_datetostr");

  /* Creating new table */
  rt_exec_query (&db_handle, "CREATE TABLE test_table (D DATE)");

  BEGIN(1);

  /* Insert 1 row into the new table. */
  rt_exec_query (&db_handle, "INSERT INTO test_table VALUES ('01.01.1701')");

  rt_assert (&db_handle, 
	     "SELECT DATETOSTR (D ,'%d.%m.%y') from test_table",
	     "01.01.01");

  rt_assert (&db_handle, 
	     "SELECT DATETOSTR (D ,'%d.%m.%Y') from test_table",
	     "01.01.1701");
  
  END(1);

  BEGIN(2);

  /* Updating 1 row into the new table. */
  rt_exec_query (&db_handle, "UPDATE test_table SET D='10.10.1001'");

  rt_assert (&db_handle, 
	     "SELECT DATETOSTR (D ,'%d.%m.%y') from test_table",
	     "10.10.01");

  rt_assert (&db_handle, 
	     "SELECT DATETOSTR (D ,'%d.%m.%Y') from test_table",
	     "10.10.1001");
  
  END(2);

  BEGIN(2);

  /* Updating 1 row into the new table. */
  rt_exec_query (&db_handle, "UPDATE test_table SET D='29.02.2008'");

  rt_assert (&db_handle, 
	     "SELECT DATETOSTR (D ,'%d.%m.%y') from test_table",
	     "29.02.08");

  rt_assert (&db_handle, 
	     "SELECT DATETOSTR (D ,'%d.%m.%Y') from test_table",
	     "29.02.2008");
  
  END(2);


  free (db_file_name);  

  return 0;
}

