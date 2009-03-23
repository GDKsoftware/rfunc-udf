/** \file  rstring_test.c
    
    \brief test unit for rstring module

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
   $Revision: 117 $ $Author: sandro $
   $Date: 2009-03-16 13:48:11 +0300 (Пнд, 16 Мар 2009) $
 **************************************************************************/
#include <ibase.h>
#include "rt_util.h"
#include <string.h>

int main (int argc, char *argv[])
{
  isc_db_handle   db_handle = 0;
  ISC_STATUS_ARRAY status;
  char *db_file_name;
  const char *create_tbl = "CREATE TABLE test_table (XML VARCHAR (256))";

  db_file_name = rt_create_db ();

   /* Connecting to newly created databse */
  if (isc_attach_database(status, 0, db_file_name, &db_handle, 0, NULL))
    fatalError (status, "attach_database");

  /* Creating new table */
  rt_exec_query (&db_handle, create_tbl);

  rt_reg_func (&db_handle, 
	       "XML_ENC_ENT", "CSTRING(256)", "CSTRING(256) FREE_IT",
	       "fn_xmlencent");

  rt_reg_func (&db_handle,
	       "XML_DEC_ENT", "CSTRING(256)",  "CSTRING(256) FREE_IT",
	       "fn_xmldecent");

  rt_reg_func (&db_handle,
	       "STR_N_POS", "CSTRING(256), CSTRING(256), INTEGER, INTEGER",  
	       "INTEGER BY VALUE",
	       "fn_strnpos");

  rt_reg_func (&db_handle,
	       "STR_POS_R", "CSTRING(256), CSTRING(256)", "INTEGER BY VALUE",
	       "fn_strposr");

  rt_reg_func (&db_handle,
	       "STR_N_POS_R", "CSTRING(256), CSTRING(256), INTEGER, INTEGER",  
	       "INTEGER BY VALUE",
	       "fn_strnposr");

  rt_reg_func (&db_handle,
	       "SUBSTR_R", "CSTRING(256), INTEGER, INTEGER",  
	       "CSTRING(256) FREE_IT",
	       "fn_substrr");

  rt_reg_func (&db_handle,
	       "STR_MIRROR", "CSTRING(256)", "CSTRING(256) FREE_IT",
	       "fn_strmirror");

  rt_reg_func (&db_handle,
	       "STR_ESC", "CSTRING(256)", "CSTRING(256) FREE_IT",
	       "fn_stresc");

  BEGIN(1);
  /* Insert 1 row into the new table. */
  rt_exec_query ( &db_handle,
		  "INSERT INTO test_table VALUES ('<A>\"B\"''C''&D&')");

  rt_assert (&db_handle,
  	     "SELECT XML_ENC_ENT (XML) from test_table",
  	     "&lt;A&gt;&quot;B&quot;&apos;C&apos;&amp;D&amp;");
  
  END(1);

  BEGIN(2);

  /* Updating testing value */
  rt_exec_query
    (&db_handle,
     "UPDATE test_table SET XML='&lt;A&gt;&quot;B&quot;&apos;C&apos;&amp;D&amp;'");

  rt_assert (&db_handle,
  	     "SELECT XML_DEC_ENT (XML) from test_table",
  	     "<A>\"B\"'C'&D&");
  END(2);

  BEGIN(3);

  rt_assert_int (&db_handle,
  		 "SELECT STR_N_POS ('&', XML, 7, 3) from test_table",
  		 23);
  END(3);

  BEGIN(4);

  rt_assert_int (&db_handle,
  		 "SELECT STR_POS_R ('apos', XML) from test_table",
  		 16);

  END(4);

  BEGIN(5);

  rt_assert_int (&db_handle,
  		 "SELECT STR_N_POS_R ('&', XML, 7, 3) from test_table",
  		 24);

  END(5);

  BEGIN(6);

  rt_assert (&db_handle,
	     "SELECT SUBSTR_R (XML, 4, 14) from test_table",
	     "C&apos;&amp;D&");
  END(6);

  BEGIN(7);

  rt_assert (&db_handle,
	     "SELECT STR_MIRROR (XML) from test_table",
	     ";pma&D;pma&;sopa&C;sopa&;touq&B;touq&;tg&A;tl&");
  END(7);

  BEGIN(8);
  /* Updating testing value */
  rt_exec_query
    (&db_handle,
     "UPDATE test_table SET XML='\\110\\t\\115\\t\\070\\n'");

  rt_assert (&db_handle,
	     "SELECT STR_ESC (XML) from test_table",
	     "n\ts\tF\n");
  END(8);

BEGIN(9);
  /* Updating testing value */
  rt_exec_query
    (&db_handle,
     "UPDATE test_table SET XML='123&#38;#60;&#62;&#38;#38;&#39;&#34;&#38;#38;&#38;#60;'");

  rt_assert (&db_handle,
	     "SELECT XML_DEC_ENT (XML) from test_table",
	     "123<>&\'\"&<");
  END(9);

  isc_detach_database(status, &db_handle);
  free (db_file_name);

  return 0;
}
