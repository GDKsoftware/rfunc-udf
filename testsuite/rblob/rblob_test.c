/** \file  rblob_test.c
    
    \brief test unit for rblob module

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
#include "rt_util.h"
#include <string.h>

int main (int argc, char *argv[])
{
  isc_db_handle   db_handle = 0;
  ISC_QUAD    blob_id;
  ISC_STATUS_ARRAY status;
  char *db_file_name;
  const char *create_tbl = "CREATE TABLE test_table (B BLOB (50,1))";
  unsigned char btext[] = /*"qWeRtYuI*AbV*";*/
    {0x71,0x57,0x65,0x52,0x74,0x59,0x75,0x49,0xc0,0xe1,0xc2,0};
  unsigned char utext[] = /*"QWERTYUI*ABV*";*/
    {0x51,0x57,0x45,0x52,0x54,0x59,0x55,0x49,0xc0,0xc1,0xc2,0};
  unsigned char ltext[] = /*"qwertyui*abv*";*/
    {0x71,0x77,0x65,0x72,0x74,0x79,0x75,0x69,0xe0,0xe1,0xe2,0};
  unsigned char in_rus[]=  /*123456AbVGdE1111*/
    {0x31,0x32,0x33,0x34,0x35,0x36,0xc0,0xe1,0xc2,
     0xc3,0xe4,0xc5,0x31,0x31,0x31,0x31,0x27,0};
  unsigned char str_rus1[]={0xc0,0xe1,0xc2,0}; /*AbV */
  unsigned char str_rus2[]={0xe1,0xc2,0xc3,0}; /*bVG */
  unsigned char str_rus3[]={0xc3,0xe4,0xc5,0}; /*GdE */
  unsigned char text_rus1[]={0xe0,0xe1,0xe2,0}; /*abv */
  unsigned char text_rus2[]={0xc1,0xc2,0xc3,0}; /*BVG */
  unsigned char text_rus3[]={0xe3,0xc4,0xc5,0}; /*gDE */
  char *upd= malloc(50);
  char *sel= malloc(50);
  char *blobtext= malloc(50);
  char *uppertext= malloc(50);
  char *lowertext= malloc(50);
  
  isc_tr_handle   tr = 0;  
  const char *ins = "INSERT INTO test_table VALUES (?)";
  
  XSQLDA *insql;

  memset (sel,0,50);
  blobtext = strcat(blobtext,(char*)(btext));
  memset (uppertext,0,50);
  uppertext = strcat(uppertext,(char*)(utext));
  memset (lowertext,0,50);
  lowertext = strcat(lowertext,(char*)(ltext));
  
  db_file_name = rt_create_db ();
  
  /* Connecting to newly created databse */
  if (isc_attach_database(status, 0, db_file_name, &db_handle, 0, NULL))
    fatalError (status, "attach_database");

  /* Creating new table */
  rt_exec_query (&db_handle, create_tbl);
  
  rt_reg_func (&db_handle,
	       "BSTRUPPER", "BLOB, BLOB", "PARAMETER 2",
	       "fn_b_strupper");

  rt_reg_func (&db_handle,
	       "BSTRLOWER", "BLOB, BLOB", "PARAMETER 2",
	       "fn_b_strlower");
 
  rt_reg_func (&db_handle,
	       "BTEXTPOS", "CSTRING(16384), BLOB", "INTEGER BY VALUE",
	       "fn_b_textpos");
  rt_reg_func (&db_handle,
	       "BSTRPOS", "CSTRING(16384), BLOB", "INTEGER BY VALUE",
	       "fn_b_strpos");

  /* Starting transaction*/
  if (isc_start_transaction(status, &tr, 1, &db_handle, 0, NULL))
    fatalError(status, "isc_start_transaction");  
  
  /* Creating text blob*/
  insql = rt_create_text_blob (&db_handle, &tr, blobtext, &blob_id);

  /* Inserting blob into table*/
  if (isc_dsql_execute_immediate(status, &db_handle,  &tr, 0, ins, 1, insql))
    fatalError (status, "isc_dsql_execute_immediate");

  /* commiting transaction */
  if (isc_commit_transaction (status, &tr))
    fatalError(status, "isc_commit_transaction");

    
  BEGIN(1);
  rt_assert_blob(&db_handle,
  		 "SELECT BSTRUPPER (B) FROM test_table",
  		 uppertext);
  END(1);

  BEGIN(2);
  rt_assert_blob(&db_handle,
  		 "SELECT BSTRLOWER (B) FROM test_table",
  		 lowertext);
  END(2);

  BEGIN(3);
  memset (upd,0,50);
  upd = strcat(upd,"UPDATE test_table SET B='");
  upd = strcat(upd,(char*)(in_rus));
  
  memset (sel,0,50);
  sel = strcat(sel,"SELECT BSTRPOS ('");
  sel = strcat(sel,(char*)(str_rus1));
  sel = strcat(sel,"',B) FROM test_table");
  
  rt_exec_query
    (&db_handle, upd);   
  
  rt_assert_int(&db_handle, sel, 7);
  END(3);

  BEGIN(4);
  memset (sel,0,50);
  sel = strcat(sel,"SELECT BSTRPOS ('");
  sel = strcat(sel,(char*)(str_rus2));
  sel = strcat(sel,"',B) FROM test_table");

  rt_assert_int(&db_handle, sel, 8);

  END(4);

  BEGIN(5);
  memset (sel,0,50);
  sel = strcat(sel,"SELECT BSTRPOS ('");
  sel = strcat(sel,(char*)(str_rus3));
  sel = strcat(sel,"',B) FROM test_table");

  rt_assert_int(&db_handle, sel, 10);

  END(5);

  BEGIN(6);
  memset (sel,0,50);
  sel = strcat(sel,"SELECT BTEXTPOS ('");
  sel = strcat(sel,(char*)(text_rus1));
  sel = strcat(sel,"',B) FROM test_table");
  
  rt_assert_int(&db_handle, sel, 7);
  END(6);

  BEGIN(7);
  memset (sel,0,50);
  sel = strcat(sel,"SELECT BTEXTPOS ('");
  sel = strcat(sel,(char*)(text_rus2));
  sel = strcat(sel,"',B) FROM test_table");
  
  rt_assert_int(&db_handle, sel, 8);
  END(7);

  BEGIN(8);
  memset (sel,0,50);
  sel = strcat(sel,"SELECT BTEXTPOS ('");
  sel = strcat(sel,(char*)(text_rus3));
  sel = strcat(sel,"',B) FROM test_table");
  
  rt_assert_int(&db_handle, sel, 10);
  END(8);

  isc_detach_database(status, &db_handle);
  free (upd);
  free (sel);
  free (db_file_name);
  free (insql);
  free (blobtext);
  free (uppertext);
  free (lowertext);

  return 0;
}
