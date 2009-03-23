/** \file  rtutil.c
    
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
   $Revision: 119 $ $Author: coopht $
   $Date: 2009-03-16 17:35:37 +0300 (Пнд, 16 Мар 2009) $
 **************************************************************************/
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#include "rt_util.h"

void _fatalError (ISC_STATUS_ARRAY status, 
		  const char *operation, 
		  const char *file,
		  const int line)
{  
  fprintf (stderr, "Fatal error occured at %s, line %d\n", file, line);
  fprintf (stderr, "Operation: %s\n", operation);
  fprintf (stderr, "Reason: ");
  if (status != NULL)
    {
      isc_print_status (status);
      fprintf (stderr, "\n ERRNO = %s\n", strerror (errno));
    }  
  abort ();
}

char* rt_create_db ()
{
  char            *db_query;
  char      *fname = strdup (tmpnam (NULL));
  isc_db_handle    dbh = 0;
  isc_tr_handle    trh = 0;
  ISC_STATUS_ARRAY status;

  if (fname == NULL)
    fatalError (NULL, "generate temp file");
  
  db_query = malloc (19 + strlen (fname));

  if (db_query == NULL)
    fatalError (NULL, "memory allocation for db_query");
  
  if (sprintf(db_query, "CREATE DATABASE '%s'", fname) < 0)
    fatalError (NULL, "creating create db SQL");
  
  if (isc_dsql_execute_immediate (status, &dbh, &trh, 0, db_query, 1, NULL))
  {
    free (db_query);   
    fatalError (status, db_query);
  }

  isc_commit_transaction(status, &trh);
  printf("Created database '%s'.\n\n", fname);

  if (isc_detach_database(status, &dbh))
    fatalError (status, "isc_detach_database");    
    
  if (db_query)
    free (db_query);

  return fname;
}

void rt_exec_query (isc_db_handle *db, 
		    const char *query)
{
  isc_tr_handle    tr = 0;
  ISC_STATUS_ARRAY status;

  /* Starting transaction*/
  if (isc_start_transaction(status, &tr, 1, db, 0, NULL))
    fatalError(status, "isc_start_transaction");  
  
  /* executing query */
  if (isc_dsql_execute_immediate (status, db, &tr, 0, query, 1, NULL))
    fatalError(status, query);  

  /* commiting transaction */
  if (isc_commit_transaction (status, &tr))
    fatalError(status, "isc_commit_transaction");  
} 

void rt_reg_func (isc_db_handle *db, 
		  const char *name,
		  const char *params,
		  const char *returns,
		  const char *entry_point)
{
  /* length of 'DECLARE EXTERNAL FUNCTION' = 25 */
  /* length of 'RETURNS' = 7 */
  /* length of 'ENTRY_POINT' = 12 */
  /* length of 'MODULE_NAME' = 11 */
  /* total length 55 */

  /* size_t tot_len = 55 + */
  /*   strlen (name) + */
  /*   strlen (params) + */
  /*   strlen (returns) + */
  /*   strlen (entry_point) + */
  /*   strlen (module) + */
  /*   + 1; */

  /* char *decl_fn = (char*)malloc (tot_len); */

  /* if (decl_fn == NULL) */
  /*   fatalError (NULL, "Cannot allocate memory."); */

  char decl_fn [BUFSIZ];
  char *rfunc_path;
  
  rfunc_path = getenv ("RFUNC_PATH");
  if (rfunc_path == NULL)
    {
      fprintf (stderr, "Your RFUNC_PATH environment does not set.\
Futher test execution does not possible.");
      abort ();
    }
    
  sprintf 
    (decl_fn, 
     "DECLARE EXTERNAL FUNCTION %s %s RETURNS %s \
ENTRY_POINT '%s' MODULE_NAME '%s'",
     name, 
     params, 
     returns, 
     entry_point, 
     rfunc_path);

  printf ("\nFUNC = %s\n", decl_fn);
  
  rt_exec_query (db, decl_fn);
  
  /* free (decl_fn); */
}

/* This declaring structure representing SQL VARCHAR type */

void rt_assert (isc_db_handle *db, const char *query, const char *control)
{
  isc_tr_handle    tr = 0;
  isc_stmt_handle stmt = 0;                /* statement handle */
  ISC_STATUS_ARRAY status;
  long                    fetch_stat;
  XSQLDA  *               sqlda;
  short                   flag0 = 0;
  struct result_t
  {
    short vary_length; 
    char vary_string [256];
  } result;
  
  /* Starting transaction*/
  if (isc_start_transaction(status, &tr, 1, db, 0, NULL))    
    fatalError (status, "start transaction");    

  /* Cheking declared function */

  /* Allocate an output SQLDA. */
  sqlda = (XSQLDA *) malloc (XSQLDA_LENGTH(1));
  sqlda->sqln = 1;
  sqlda->version = 1;
  
  /* Allocate a statement. */
  if (isc_dsql_alloc_statement2 (status, db, &stmt))  
    fatalError (status, "isc_dsql_allocate_statement");  

  /* Prepare the statement. */
  if (isc_dsql_prepare (status, &tr, &stmt, 0, query, 1, sqlda))  
    fatalError (status, query);  
  
  /*
   *  Although selected column is of type varchar, the
   */  
  sqlda->sqlvar[0].sqldata = (char *)&result;
  sqlda->sqlvar[0].sqltype = SQL_VARYING + 1;
  sqlda->sqlvar[0].sqlind  = &flag0;

  /* Execute the statement. */
  if (isc_dsql_execute (status, &tr, &stmt, 1, NULL))
     fatalError (status, "isc_dsql_execute");   
            
  /*
   *    Fetch and print the records.
   *    Status is 100 after the last row is fetched.
   */  
  while ((fetch_stat = isc_dsql_fetch (status, &stmt, 1, sqlda)) == 0)      
      if ((strcmp (result.vary_string, control) != 0) || 
	(result.vary_length != strlen (control)))
	{
	  /* printf("\n%d : %s\n", result.vary_length, result.vary_string); */
	  fprintf (stderr, "\n !!! Assertion Faild !!! \n");
	  fprintf (stderr, "Expexted Value : %s\n", control);
	  fprintf (stderr, "Recieved Value : %s\n", result.vary_string);
	  abort ();
	}    
  
  if (fetch_stat != 100L)    
      fatalError (status, "fetch_stat");    
  
  /* Free statement handle. */
  if (isc_dsql_free_statement(status, &stmt, DSQL_close))    
      fatalError (status, "isc_dsql_free_statement");    
  
  if (isc_commit_transaction(status, &tr))    
      fatalError(status, "isc_commit_transaction");    

  free (sqlda);
}

void rt_assert_double (isc_db_handle *db, const char *query, double control)
{
  isc_tr_handle    tr = 0;
  isc_stmt_handle  stmt = 0;                /* statement handle */
  ISC_STATUS_ARRAY status;
  long             fetch_stat = 0;
  XSQLDA  *        sqlda = NULL;
  double           result = 0;
  short            flag0 = 0;
  
  /* Starting transaction */
  if (isc_start_transaction(status, &tr, 1, db, 0, NULL))    
    fatalError (status, "start transaction");    

  /* Cheking declared function */

  /* Allocate an output SQLDA. */
  sqlda = (XSQLDA *) malloc (XSQLDA_LENGTH(1));
  sqlda->sqld = 1;
  sqlda->sqln = 1;
  sqlda->version = 1;
 
  /* Allocate a statement. */
  if (isc_dsql_alloc_statement2 (status, db, &stmt))  
    fatalError (status, "isc_dsql_allocate_statement");  

  /*
   *  Although selected column is of type double.
   */  
  sqlda->sqlvar[0].sqldata = (char *)&result;
  sqlda->sqlvar[0].sqltype = SQL_DOUBLE + 1;
  sqlda->sqlvar[0].sqlind = &flag0;

  /* Prepare the statement. */
  if (isc_dsql_prepare (status, &tr, &stmt, 0, query, 1, sqlda))  
    fatalError (status, query);   

  /* Execute the statement. */
  if (isc_dsql_execute (status, &tr, &stmt, 1, NULL))
     fatalError (status, "isc_dsql_execute");   
            
  /*
   *    Fetch and print the records.
   *    Status is 100 after the last row is fetched.
   */  
  while ((fetch_stat = isc_dsql_fetch (status, &stmt, 1, sqlda)) == 0)          
      if (result != control)    
	{
	  fprintf (stderr, "\n !!! Assertion Faild !!! \n");
	  fprintf (stderr, "Expexted Value : %e\n", control);
	  fprintf (stderr, "Recieved Value : %e\n", result);
	  abort ();
	}    
  
  if (fetch_stat != 100L)    
      fatalError (status, "fetch_stat");    
  
  /* Free statement handle. */
  if (isc_dsql_free_statement(status, &stmt, DSQL_close))    
      fatalError (status, "isc_dsql_free_statement");    
  
  if (isc_commit_transaction(status, &tr))    
      fatalError(status, "isc_commit_transaction");    

  free (sqlda);
}

void rt_assert_int (isc_db_handle *db, const char *query, int control)
{
  isc_tr_handle    tr = 0;
  isc_stmt_handle  stmt = 0;                /* statement handle */
  ISC_STATUS_ARRAY status;
  long                    fetch_stat = 0;
  XSQLDA  *               sqlda = NULL;
  int result = 0;
  short                   flag0 = 0;
  
  /* Starting transaction */
  if (isc_start_transaction(status, &tr, 1, db, 0, NULL))    
    fatalError (status, "start transaction");    

  /* Cheking declared function */

  /* Allocate an output SQLDA. */
  sqlda = (XSQLDA *) malloc (XSQLDA_LENGTH(1));
  sqlda->sqld = 1;
  sqlda->sqln = 1;
  sqlda->version = 1;
 
  /* Allocate a statement. */
  if (isc_dsql_alloc_statement2 (status, db, &stmt))  
    fatalError (status, "isc_dsql_allocate_statement");  

  /*
   *  Although selected column is of type int.
   */  
  sqlda->sqlvar[0].sqldata = (char *)&result;
  sqlda->sqlvar[0].sqltype = SQL_SHORT + 1;
  sqlda->sqlvar[0].sqlind = &flag0;

  /* Prepare the statement. */
  if (isc_dsql_prepare (status, &tr, &stmt, 0, query, 1, sqlda))  
    fatalError (status, query);   

  /* Execute the statement. */
  if (isc_dsql_execute (status, &tr, &stmt, 1, NULL))
     fatalError (status, "isc_dsql_execute");   
            
  /*
   *    Fetch and print the records.
   *    Status is 100 after the last row is fetched.
   */  
  while ((fetch_stat = isc_dsql_fetch (status, &stmt, 1, sqlda)) == 0)
      if (result != control)    
	{
	  fprintf (stderr, "\n !!! Assertion Faild !!! \n");
	  fprintf (stderr, "Expexted Value : %d\n", control);
	  fprintf (stderr, "Recieved Value : %d\n", result);
	  abort ();
	}    
  
  if (fetch_stat != 100L)    
      fatalError (status, "fetch_stat");    
  
  /* Free statement handle. */
  if (isc_dsql_free_statement(status, &stmt, DSQL_close))    
      fatalError (status, "isc_dsql_free_statement");    
  
  if (isc_commit_transaction(status, &tr))    
      fatalError(status, "isc_commit_transaction");    

  free (sqlda);
}

XSQLDA *rt_create_text_blob (isc_db_handle *db,
			     isc_tr_handle *tr,
			     const char *Text,
			     ISC_QUAD    *blob_id)
{
  isc_blob_handle bh = 0; /*Declaring blob handler*/
  XSQLDA          *result;
  ISC_STATUS_ARRAY status;

  result = (XSQLDA*)malloc (XSQLDA_LENGTH (1));
  if (result == NULL)
    fatalError (NULL, "Cannot allocate memory");

  result->sqln = 1;
  result->sqld = 1;
  result->version = 1;
     
  result->sqlvar[0].sqldata = (char *) blob_id;
  result->sqlvar[0].sqltype = SQL_BLOB;
  result->sqlvar[0].sqllen = sizeof(ISC_QUAD);
  
  /* Creating new blob */
  if (isc_create_blob (status, db, tr, &bh, blob_id))
    fatalError(status, "isc_create_blob");

  /* Writing data to blob handle*/
  if (isc_put_segment (status, &bh, strlen (Text) + 1, Text))  
    fatalError(status, "isc_put_segment");

  /* closing blob */
  if(isc_close_blob (status, &bh))
    fatalError(status, "isc_close_blob");

  return result;
}

void rt_assert_blob (isc_db_handle *db,
		     const char *query,
		     const char *control)
{
  isc_tr_handle    tr = 0;
  isc_stmt_handle  stmt = 0;                /* statement handle */
  ISC_STATUS_ARRAY status;
  ISC_STATUS       b_status;
  long             fetch_stat = 0;
  XSQLDA          *sqlda;
  short            flag0 = 0;
  isc_blob_handle  bh = 0;
  ISC_QUAD         blob_id;
  char             blob_segment [80];
  unsigned short   actual_seg_len = 0; 


  /* Starting transaction*/
  if (isc_start_transaction(status, &tr, 1, db, 0, NULL))    
    fatalError (status, "start transaction");    

  /* Allocate an output SQLDA. */
  sqlda = (XSQLDA *) malloc (XSQLDA_LENGTH(1));
  sqlda->sqld = 1;
  sqlda->sqln = 1;
  sqlda->version = 1;

  sqlda->sqlvar[0].sqldata = (char *)&blob_id;
  sqlda->sqlvar[0].sqltype = SQL_BLOB + 1;
  sqlda->sqlvar[0].sqlind  = &flag0;
  
  /* Allocate a statement. */
  if (isc_dsql_allocate_statement(status, db, &stmt))
      fatalError (status, "isc_dsql_allocate_statement");  

  /* Prepare the statement. */
  if (isc_dsql_prepare (status, &tr, &stmt, 0, query, 1, sqlda))  
    fatalError (status, query);  

  /* Execute the statement. */
  if (isc_dsql_execute (status, &tr, &stmt, 1, NULL))
     fatalError (status, "isc_dsql_execute");   

  /* printf ("\nbh = %x\n", bh); */
            
  /*
   * Fetching data from table
   */  
  while ((fetch_stat = isc_dsql_fetch (status, &stmt, 1, sqlda)) == 0)      
    {
      if (isc_open_blob2 (status, db, &tr, &bh, &blob_id, 0, NULL))
	fatalError (status, "isc_open_blob2");    

      /* printf ("\nbh = %x\n", &bh); */

      /* Getting blob segment */
      b_status = 
	isc_get_segment 
	(status, &bh, &actual_seg_len, sizeof (blob_segment), blob_segment);

       /* printf ("\nb_status = %x\n", b_status); */
       blob_segment [actual_seg_len - 1] = '\0';
       /* printf("B_SEGMENT = %d:%s\n", */
       /* 	      actual_seg_len, blob_segment); */

      if ((strcmp (blob_segment, control) != 0) || 
	  (strlen (blob_segment) != strlen (control)))
	{
	  /* printf("\n%d : %s\n", result.vary_length, result.vary_string); */
	  fprintf (stderr, "\n !!! Assertion Faild !!! \n");
	  fprintf (stderr, 
		   "Expexted Value : %s, %d\n", 
		   control, 
		   (int)strlen (control));
	  fprintf (stderr, 
		   "Recieved Value : %s, %d\n", 
		   blob_segment, 
		   (int)strlen (blob_segment));
	  abort ();
	}    

      /* Walking through all segments of recieved blob */
      while (b_status == 0 || status [1] == isc_segment)
	{

	  b_status = 
	    isc_get_segment
	    (status, &bh, &actual_seg_len, sizeof(blob_segment), blob_segment);
	}

      /* Closing blob */
      if (isc_close_blob (status, &bh))
	fatalError (status, "isc_close_blob");    
    }  

  if (fetch_stat != 100L)
    fatalError (status, "fetch_stat");
    
  /* Free statement handle. */
  if (isc_dsql_free_statement(status, &stmt, DSQL_close))    
    fatalError (status, "isc_dsql_free_statement");    
  
  if (isc_commit_transaction(status, &tr))    
      fatalError(status, "isc_commit_transaction");    

  free (sqlda);
}
