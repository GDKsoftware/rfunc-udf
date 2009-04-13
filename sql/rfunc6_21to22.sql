/*====================================================================
		File rfunc6_20to21.sql

		rFunc InterBase UDF library.
		Update SQL-script for migrate DB from rFunc 2.1 to 2.2.
                For InterBase 6 or later.

      		Copyright 2009 PoleSoft Technologies Group
		http://www.polesoft.ru/project/rfunc
		mailto:support@polesoft.ru

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.
    See license.txt for more details.

====================================================================== */

/* Define valid path and password for your database */
/* 6.x Windows local Firebird Dialect 1 */
/*CONNECT 'c:\progra~1\firebird\examples\v5\employee.gdb' USER 'SYSDBA' PASSWORD 'masterkey';*/
/* 6.x Windows local Borland Dialect 1 */
/*CONNECT 'c:\progra~1\borland\interbase\examples\database\employee.gdb' USER 'SYSDBA' PASSWORD 'masterkey';*/
/* 6.x Windows local Dialect 3 */
/*CONNECT 'c:\ib6\test\test6.gdb' USER 'SYSDBA' PASSWORD 'masterkey';*/
/* 6.x Linux remote Dialect 1 */
/*CONNECT 'iblinux:/opt/interbase/examples/employee.gdb' USER 'SYSDBA' PASSWORD 'masterkey';*/
/* 6.x Linux remote Dialect 3 */
/*CONNECT 'mlinux:/base/test6.gdb' USER 'SYSDBA' PASSWORD 'masterkey';*/

/* Bugfix: Input string for SUBSTR increased */

update RDB$FUNCTION_ARGUMENTS set RDB$field_length=16383 WHERE RDB$FUNCTION_name='SUBSTR' AND RDB$ARGUMENT_position=1;
/*update RDB$FUNCTION_ARGUMENTS set RDB$mechanism=-1 WHERE RDB$FUNCTION_name='CHR' AND RDB$ARGUMENT_position=0;*/
COMMIT;

DECLARE EXTERNAL FUNCTION FACT
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_fact'  MODULE_NAME 'rfunc';

/*String routines*/  
 
DECLARE EXTERNAL FUNCTION XML2STR
   CSTRING(255)
   RETURNS CSTRING(255) FREE_IT
  ENTRY_POINT 'fn_xmlencent'  MODULE_NAME 'rfunc';
  
DECLARE EXTERNAL FUNCTION LONGXML2STR
   CSTRING(16383)
   RETURNS CSTRING(16383) FREE_IT
  ENTRY_POINT 'fn_xmlencent'  MODULE_NAME 'rfunc';
  
DECLARE EXTERNAL FUNCTION STR2XML
   CSTRING(255)
   RETURNS CSTRING(255) FREE_IT
  ENTRY_POINT 'fn_xmldecent'  MODULE_NAME 'rfunc';
  
DECLARE EXTERNAL FUNCTION LONGSTR2XML
   CSTRING(16383)
   RETURNS CSTRING(16383) FREE_IT
  ENTRY_POINT 'fn_xmldecent'  MODULE_NAME 'rfunc';
  
DECLARE EXTERNAL FUNCTION STRNPOS
   CSTRING(16383), CSTRING(16383), INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_strnpos'  MODULE_NAME 'rfunc';
  
DECLARE EXTERNAL FUNCTION STRPOSR
   CSTRING(16383), CSTRING(16383)
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_strposr'  MODULE_NAME 'rfunc';
  
DECLARE EXTERNAL FUNCTION STRNPOSR
   CSTRING(16383), CSTRING(16383), INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_strnposr'  MODULE_NAME 'rfunc';
  
DECLARE EXTERNAL FUNCTION SUBSTRR
   CSTRING(16383), INTEGER, INTEGER
   RETURNS CSTRING(255) FREE_IT
  ENTRY_POINT 'fn_substrr'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGSUBSTRR
   CSTRING(16383), INTEGER, INTEGER
   RETURNS CSTRING(16383) FREE_IT
  ENTRY_POINT 'fn_substrr'  MODULE_NAME 'rfunc';
  
DECLARE EXTERNAL FUNCTION STRESC
   CSTRING(16383)
   RETURNS CSTRING(255) FREE_IT
  ENTRY_POINT 'fn_stresc'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGSTRESC
   CSTRING(16383)
   RETURNS CSTRING(16383) FREE_IT
  ENTRY_POINT 'fn_stresc'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION STRMIRROR
   CSTRING(16383)
   RETURNS CSTRING(255) FREE_IT
  ENTRY_POINT 'fn_strmirror'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGSTRMIRROR
   CSTRING(16383)
   RETURNS CSTRING(16383) FREE_IT
  ENTRY_POINT 'fn_strmirror'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION CR
   RETURNS CSTRING(1) FREE_IT
  ENTRY_POINT 'fn_cr'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LF
   RETURNS CSTRING(1) FREE_IT
  ENTRY_POINT 'fn_lf'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION CRLF
   RETURNS CSTRING(2) FREE_IT
  ENTRY_POINT 'fn_crlf'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION TAB
   RETURNS CSTRING(1) FREE_IT
  ENTRY_POINT 'fn_tab'  MODULE_NAME 'rfunc';
  
DECLARE EXTERNAL FUNCTION STR2HEX
   CSTRING(255)
   RETURNS CSTRING(255) FREE_IT
  ENTRY_POINT 'fn_str2hex'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGSTR2HEX
   CSTRING(16383)
   RETURNS CSTRING(16383) FREE_IT
  ENTRY_POINT 'fn_str2hex'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION HEX2STR
   CSTRING(255)
   RETURNS CSTRING(255) FREE_IT
  ENTRY_POINT 'fn_hex2str'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGHEX2STR
   CSTRING(16383)
   RETURNS CSTRING(16383) FREE_IT
  ENTRY_POINT 'fn_hex2str'  MODULE_NAME 'rfunc';

/*Blob routines*/

DECLARE EXTERNAL FUNCTION B_STRUPPER
   BLOB,
   BLOB
   RETURNS PARAMETER 2
  ENTRY_POINT 'fn_b_strupper'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_STRLOWER
   BLOB,
   BLOB
   RETURNS PARAMETER 2
  ENTRY_POINT 'fn_b_strlower'  MODULE_NAME 'rfunc';

  
  
COMMIT;