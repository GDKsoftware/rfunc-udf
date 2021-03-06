/*====================================================================
		File rfunc6_20to21.sql

		rFunc InterBase UDF library.
		Update SQL-script for migrate DB from rFunc 2.0 to 2.1.
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

/* Bugfix: FREE_IT added */

update RDB$FUNCTION_ARGUMENTS set RDB$MECHANISM = -1 where RDB$FUNCTION_NAME = 'ENCODEDATE' AND RDB$ARGUMENT_POSITION = 0;
update RDB$FUNCTION_ARGUMENTS set RDB$MECHANISM = -1 where RDB$FUNCTION_NAME = 'ENCODEDATETIME' AND RDB$ARGUMENT_POSITION = 0;
update RDB$FUNCTION_ARGUMENTS set RDB$MECHANISM = -1 where RDB$FUNCTION_NAME = 'CHR' AND RDB$ARGUMENT_POSITION = 0;
update RDB$FUNCTION_ARGUMENTS set RDB$MECHANISM = -1 where RDB$FUNCTION_NAME = 'B_SUBSTR' AND RDB$ARGUMENT_POSITION = 0;
update RDB$FUNCTION_ARGUMENTS set RDB$MECHANISM = -1 where RDB$FUNCTION_NAME = 'B_LONGSUBSTR' AND RDB$ARGUMENT_POSITION = 0;
update RDB$FUNCTION_ARGUMENTS set RDB$MECHANISM = -1 where RDB$FUNCTION_NAME = 'B_LINE' AND RDB$ARGUMENT_POSITION = 0;
update RDB$FUNCTION_ARGUMENTS set RDB$MECHANISM = -1 where RDB$FUNCTION_NAME = 'B_LONGLINE' AND RDB$ARGUMENT_POSITION = 0;

COMMIT;

/* New functions */

DECLARE EXTERNAL FUNCTION LIBNAME
   RETURNS CSTRING(255) FREE_IT
  ENTRY_POINT 'fn_libname'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LIBVERSION
   RETURNS CSTRING(255) FREE_IT
  ENTRY_POINT 'fn_libversion'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION TIMETODOUBLE
   TIMESTAMP
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_timetodouble'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DATETODOUBLE
   TIMESTAMP
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_datetodouble'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DOUBLETODATE
   DOUBLE PRECISION
   RETURNS TIMESTAMP FREE_IT
  ENTRY_POINT 'fn_doubletodate'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DOUBLETOTIME
   DOUBLE PRECISION
   RETURNS TIMESTAMP FREE_IT
  ENTRY_POINT 'fn_doubletotime'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MAXDATE
   TIMESTAMP, TIMESTAMP
   RETURNS TIMESTAMP
  ENTRY_POINT 'fn_maxdate'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MINDATE
   TIMESTAMP, TIMESTAMP
   RETURNS TIMESTAMP
  ENTRY_POINT 'fn_mindate'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION INCDATETIME
   TIMESTAMP, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER
   RETURNS TIMESTAMP
  ENTRY_POINT 'fn_incdatetime'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION IEQUAL
   INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_iequal'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DTEQUAL
   TIMESTAMP, TIMESTAMP
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_dtequal'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FLOATTOSTR
   DOUBLE PRECISION, CSTRING(255)
   RETURNS CSTRING(255) FREE_IT
  ENTRY_POINT 'fn_floattostr'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION INTTOSTR
   INTEGER, CSTRING(255)
   RETURNS CSTRING(255) FREE_IT
  ENTRY_POINT 'fn_inttostr'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTYEAR
   TIMESTAMP
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_year'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTMONTH
   TIMESTAMP
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_month'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTDAY
   TIMESTAMP
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_day'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTYEARDAY
   TIMESTAMP
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_yearday'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTWEEKDAY
   TIMESTAMP
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_weekday'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTHOUR
   TIMESTAMP
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_hour'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTMINUTE
   TIMESTAMP
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_minute'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTSECOND
   TIMESTAMP
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_second'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTMILLISECOND
   TIMESTAMP
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_millisecond'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION SIGN
   DOUBLE PRECISION
   RETURNS SMALLINT BY VALUE
  ENTRY_POINT 'fn_sign'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION ACOS
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_acos'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION ASIN
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_asin'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION ATAN
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_atan'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION ATAN2
   DOUBLE PRECISION, DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_atan2'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION COS
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_cos'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION COSH
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_cosh'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXP
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_exp'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LOG
   DOUBLE PRECISION, DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_log'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LN
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_ln'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LOG10
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_log10'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION SIN
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_sin'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION SINH
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_sinh'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION SQRT
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_sqrt'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION TAN
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_tan'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION TANH
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_tanh'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION E
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_e'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION PI
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_pi'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION NUMINWORDS
   INTEGER, CSTRING(1)
   RETURNS CSTRING(255) FREE_IT
  ENTRY_POINT 'fn_numinwords'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION CONVERTSYMBOLS
   CSTRING(255), CSTRING(255), CSTRING(255)
   RETURNS CSTRING(255)
  ENTRY_POINT 'fn_convertsymbols'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGCONVERTSYMBOLS
   CSTRING(16383), CSTRING(255), CSTRING(255)
   RETURNS CSTRING(16383)
  ENTRY_POINT 'fn_convertsymbols'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION REPEATTRIM
   CSTRING(255), CSTRING(255)
   RETURNS CSTRING(255)
  ENTRY_POINT 'fn_repeattrim'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGREPEATTRIM
   CSTRING(16383), CSTRING(16383)
   RETURNS CSTRING(16383)
  ENTRY_POINT 'fn_repeattrim'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION STRCMP
   CSTRING(16383), CSTRING(16383)
   RETURNS SMALLINT BY VALUE
  ENTRY_POINT 'fn_strcmp'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION C
   CSTRING(255)
   RETURNS CSTRING(255)
  ENTRY_POINT 'fn_c'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGC
   CSTRING(16383)
   RETURNS CSTRING(16383)
  ENTRY_POINT 'fn_c'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION CEQUAL
   CSTRING(16383), CSTRING(16383)
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_cequal'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EAN13CS
   CSTRING(255)
   RETURNS SMALLINT BY VALUE
  ENTRY_POINT 'fn_ean13cs'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION BCCHECKDIGIT
   CSTRING(255)
   RETURNS SMALLINT BY VALUE
  ENTRY_POINT 'fn_bccheckdigit'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION CREATEGUID
   RETURNS CSTRING(38) FREE_IT
  ENTRY_POINT 'fn_CreateGUID'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_STRCMP
   BLOB, BLOB
   RETURNS SMALLINT BY VALUE
  ENTRY_POINT 'fn_b_strcmp'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_STRPOS
   CSTRING(16383),
   BLOB
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_b_strpos'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_TEXTPOS
   CSTRING(16383),
   BLOB
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_b_textpos'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MD5SUM
   CSTRING(16383)
   RETURNS CSTRING(32) FREE_IT
  ENTRY_POINT 'fn_md5sum'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MD5INIT
   RETURNS CSTRING(176) FREE_IT
  ENTRY_POINT 'fn_md5init'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MD5UPDATE
   CSTRING(176), CSTRING(16383), INTEGER
   RETURNS CSTRING(176)
  ENTRY_POINT 'fn_md5update'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MD5FINAL
   CSTRING(176)
   RETURNS CSTRING(32) FREE_IT
  ENTRY_POINT 'fn_md5final'  MODULE_NAME 'rfunc';

/* File functions */
DECLARE EXTERNAL FUNCTION FCREATE
   CSTRING(255), INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fcreate' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FOPEN
   CSTRING(255), INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fopen' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FREAD
   INTEGER, INTEGER
   RETURNS CSTRING(255) FREE_IT
  ENTRY_POINT 'fn_fread' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGFREAD
   INTEGER, INTEGER
   RETURNS CSTRING(16383) FREE_IT
  ENTRY_POINT 'fn_fread' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FWRITE
   INTEGER, CSTRING(16383)
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fwrite' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FSEEK
   INTEGER, INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fseek' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FCLOSE
   INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fclose' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FREMOVE
   CSTRING(255)
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fremove' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FSIZE
   CSTRING(255)
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fsize' MODULE_NAME 'rfunc';

/* File bit mask constants */
DECLARE EXTERNAL FUNCTION FSEEK_CUR
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fseek_cur' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FSEEK_END
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fseek_end' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FSEEK_SET
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fseek_set' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FO_RDONLY
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fo_rdonly' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FO_WRONLY
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fo_wronly' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FO_RDWR
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fo_rdwr' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FO_CREAT
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fo_creat' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FO_TRUNC
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fo_trunc' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FO_EXCL
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fo_excl' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FO_APPEND
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fo_append' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FS_IREAD
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fs_iread' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FS_IWRITE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fs_iwrite' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FS_IEXEC
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fs_iexec' MODULE_NAME 'rfunc';

COMMIT;
