/*====================================================================
		File rfunc4_20to21.sql

		rFunc InterBase UDF library.
		Update SQL-script for migrate DB from rFunc 2.0 to 2.1.
                For InterBase 4.2.

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
/*CONNECT "c:\progra~1\borland\intrbase\examples\employee.gdb" USER "SYSDBA" PASSWORD "masterkey";*/

/* New functions */

DECLARE EXTERNAL FUNCTION LIBNAME
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_libname'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LIBVERSION
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_libversion'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION TIMETODOUBLE
   DATE
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_timetodouble'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DATETODOUBLE
   DATE
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_datetodouble'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DOUBLETODATE
   DOUBLE PRECISION
   RETURNS DATE
  ENTRY_POINT 'fn_doubletodate'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DOUBLETOTIME
   DOUBLE PRECISION
   RETURNS DATE
  ENTRY_POINT 'fn_doubletotime'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MAXDATE
   DATE, DATE
   RETURNS DATE
  ENTRY_POINT 'fn_maxdate'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MINDATE
   DATE, DATE
   RETURNS DATE
  ENTRY_POINT 'fn_mindate'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION IEQUAL
   INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_iequal'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DTEQUAL
   DATE, DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_dtequal'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FLOATTOSTR
   DOUBLE PRECISION, CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_floattostr'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION INTTOSTR
   INTEGER, CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_inttostr'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTYEAR
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_year'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTMONTH
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_month'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTDAY
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_day'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTYEARDAY
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_yearday'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTWEEKDAY
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_weekday'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTHOUR
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_hour'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTMINUTE
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_minute'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTSECOND
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_second'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION INCDATETIME
   DATE, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER
   RETURNS DATE
  ENTRY_POINT 'fn_incdatetime'  MODULE_NAME 'rfunc';

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

/* Constants rounded for 21 decimals */
DECLARE EXTERNAL FUNCTION E
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_e'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION PI
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_pi'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION NUMINWORDS
   INTEGER, CSTRING(2)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_numinwords'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION CONVERTSYMBOLS
   CSTRING(256), CSTRING(256), CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_convertsymbols'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGCONVERTSYMBOLS
   CSTRING(16384), CSTRING(256), CSTRING(256)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_convertsymbols'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION REPEATTRIM
   CSTRING(256), CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_repeattrim'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGREPEATTRIM
   CSTRING(16384), CSTRING(16384)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_repeattrim'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION STRCMP
   CSTRING(16384), CSTRING(16384)
   RETURNS SMALLINT BY VALUE
  ENTRY_POINT 'fn_strcmp'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION C
   CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_c'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGC
   CSTRING(16384)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_c'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION CEQUAL
   CSTRING(16384), CSTRING(16384)
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_cequal'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EAN13CS
   CSTRING(256)
   RETURNS SMALLINT BY VALUE
  ENTRY_POINT 'fn_ean13cs'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION BCCHECKDIGIT
   CSTRING(256)
   RETURNS SMALLINT BY VALUE
  ENTRY_POINT 'fn_bccheckdigit'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION CREATEGUID
   RETURNS CSTRING(39)
  ENTRY_POINT 'fn_CreateGUID'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_STRCMP
   BLOB, BLOB
   RETURNS SMALLINT BY VALUE
  ENTRY_POINT 'fn_b_strcmp'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_STRPOS
   CSTRING(16384),
   BLOB
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_b_strpos'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_TEXTPOS
   CSTRING(16384),
   BLOB
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_b_textpos'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MD5SUM
   CSTRING(16384)
   RETURNS CSTRING(33)
  ENTRY_POINT 'fn_md5sum'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MD5INIT
   RETURNS CSTRING(177)
  ENTRY_POINT 'fn_md5init'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MD5UPDATE
   CSTRING(177), CSTRING(16384), INTEGER
   RETURNS CSTRING(177)
  ENTRY_POINT 'fn_md5update'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MD5FINAL
   CSTRING(177)
   RETURNS CSTRING(33)
  ENTRY_POINT 'fn_md5final'  MODULE_NAME 'rfunc';

/* File functions */
DECLARE EXTERNAL FUNCTION FCREATE
   CSTRING(256), INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fcreate' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FOPEN
   CSTRING(256), INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fopen' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FREAD
   INTEGER, INTEGER
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_fread' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGFREAD
   INTEGER, INTEGER
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_fread' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FWRITE
   INTEGER, CSTRING(16384)
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
   CSTRING(256)
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_fremove' MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FSIZE
   CSTRING(256)
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
