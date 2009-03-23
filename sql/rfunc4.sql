/*====================================================================
		File rfunc4.sql

		rFunc InterBase UDF library.
		Install SQL-script for IB 4.2.

		Copyright 1998-2004 Polaris Software
		http://rfunc.sourceforge.net
		mailto:rFunc@mail.ru

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.
    See license.txt for more details.

====================================================================== */

/* Define valid path and password for your database */
/*CONNECT "c:\progra~1\borland\intrbase\examples\employee.gdb" USER "SYSDBA" PASSWORD "masterkey";*/

/* Version functions */

DECLARE EXTERNAL FUNCTION LIBNAME
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_libname'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LIBVERSION
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_libversion'  MODULE_NAME 'rfunc';

/* Date&Time functions */

DECLARE EXTERNAL FUNCTION YEAR
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_year'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MONTH
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_month'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DAY
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_day'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION YEARDAY
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_yearday'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION WEEKDAY
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_weekday'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION HOUR
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_hour'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MINUTE
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_minute'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION SECOND
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_second'  MODULE_NAME 'rfunc';

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

DECLARE EXTERNAL FUNCTION ISLEAPYEAR
   INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_isleapyear'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION QUARTER
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_quarter'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DATETOSTR
   DATE, CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_datetostr'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION ENCODEDATE
   INTEGER, INTEGER, INTEGER
   RETURNS DATE
  ENTRY_POINT 'fn_encodedate'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION ENCODEDATETIME
   INTEGER, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER
   RETURNS DATE
  ENTRY_POINT 'fn_encodedatetime'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTDATE
   DATE
   RETURNS DATE
  ENTRY_POINT 'fn_extractdate'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXTRACTTIME
   DATE
   RETURNS DATE
  ENTRY_POINT 'fn_extracttime'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DOW
   DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_dow'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DAYPERMONTH
   INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_daypermonth'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FIRSTDAYMONTH
   DATE
   RETURNS DATE
  ENTRY_POINT 'fn_firstdaymonth'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LASTDAYMONTH
   DATE
   RETURNS DATE
  ENTRY_POINT 'fn_lastdaymonth'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DAYSBETWEEN
   DATE, DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_daysbetween'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION INCDATE
   DATE, INTEGER, INTEGER, INTEGER
   RETURNS DATE
  ENTRY_POINT 'fn_incdate'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION INCDATETIME
   DATE, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER
   RETURNS DATE
  ENTRY_POINT 'fn_incdatetime'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MAXDATE
   DATE, DATE
   RETURNS DATE
  ENTRY_POINT 'fn_maxdate'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MINDATE
   DATE, DATE
   RETURNS DATE
  ENTRY_POINT 'fn_mindate'  MODULE_NAME 'rfunc';

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

/* Math functions */
DECLARE EXTERNAL FUNCTION ABS
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_abs'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MAXNUM
   DOUBLE PRECISION, DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_maxnum'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MINNUM
   DOUBLE PRECISION, DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_minnum'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION CEIL
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_ceil'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FLOOR
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_floor'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION POWER
   DOUBLE PRECISION, DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_power'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION ROUND
   DOUBLE PRECISION, INTEGER
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_round'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION SOFTROUND
   DOUBLE PRECISION, INTEGER
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_softround'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DIV
   INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_div'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MOD
   INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_mod'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION Z
   DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_z'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DZERO
   DOUBLE PRECISION, DOUBLE PRECISION, DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_dividezero'  MODULE_NAME 'rfunc';


DECLARE EXTERNAL FUNCTION INITRANDOM
   INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_initRandom'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION GETRANDOM
   INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_getRandom'  MODULE_NAME 'rfunc';


DECLARE EXTERNAL FUNCTION GETBIT
   INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_getBit'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION SETBIT
   INTEGER, INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_setBit'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION BITAND
   INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_bitAnd'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION BITOR
   INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_bitOr'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION BITXOR
   INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_bitXor'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION BITNOT
   INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_bitNot'  MODULE_NAME 'rfunc';

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

/* String functions */
DECLARE EXTERNAL FUNCTION CHR
   SMALLINT
   RETURNS CSTRING(2)
  ENTRY_POINT 'fn_chr'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION ORD
   CSTRING(2)
   RETURNS SMALLINT BY VALUE
  ENTRY_POINT 'fn_ord'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LTRIM
   CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_ltrim'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGLTRIM
   CSTRING(16384)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_ltrim'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION RTRIM
   CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_rtrim'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGRTRIM
   CSTRING(16384)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_rtrim'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION TRIM
   CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_trim'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION STRTRIM
   CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_trim'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGTRIM
   CSTRING(16384)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_trim'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION REPEATTRIM
   CSTRING(256), CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_repeattrim'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGREPEATTRIM
   CSTRING(16384), CSTRING(16384)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_repeattrim'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGSUBSTR
   CSTRING(16384), INTEGER, INTEGER
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_substr'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION STRREPEAT
   CSTRING(256), INTEGER
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_strrepeat'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGSTRREPEAT
   CSTRING(16384), INTEGER
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_longstrrepeat'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION STRSTUFF
   CSTRING(256), INTEGER, INTEGER, CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_strstuff'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGSTRSTUFF
   CSTRING(16384), INTEGER, INTEGER, CSTRING(16384)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_longstrstuff'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION STRREPLACE
   CSTRING(256), CSTRING(256), CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_strreplace'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGSTRREPLACE
   CSTRING(16384), CSTRING(8128), CSTRING(8128)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_longstrreplace'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION STRPOS
   CSTRING(16384), CSTRING(16384)
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_strpos'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION STRLEN
   CSTRING(16384)
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_strlen'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION STRCOUNT
   CSTRING(256), CSTRING(16384)
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_strcount'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION STRCMP
   CSTRING(16384), CSTRING(16384)
   RETURNS SMALLINT BY VALUE
  ENTRY_POINT 'fn_strcmp'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION WORDCOUNT
   CSTRING(16384),
   CSTRING(32),
   SMALLINT
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_wordcount'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION WORDNUM
   CSTRING(16384),
   INTEGER,
   CSTRING(32),
   SMALLINT
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_wordnum'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGWORDNUM
   CSTRING(16384),
   INTEGER,
   CSTRING(32),
   SMALLINT
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_wordnum'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION PADRIGHT
   CSTRING(256), SMALLINT, CSTRING(2)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_padright'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGPADRIGHT
   CSTRING(16384), SMALLINT, CSTRING(2)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_longpadright'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION PADLEFT
   CSTRING(256), SMALLINT, CSTRING(2)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_padleft'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGPADLEFT
   CSTRING(16384), SMALLINT, CSTRING(2)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_longpadleft'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION C
   CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_c'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGC
   CSTRING(16384)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_c'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION FLOATTOSTR
   DOUBLE PRECISION, CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_floattostr'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION INTTOSTR
   INTEGER, CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_inttostr'  MODULE_NAME 'rfunc';

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

/* Miscellaneous functions */
DECLARE EXTERNAL FUNCTION IIF
   INTEGER, INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_iif'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DIF
   INTEGER, DOUBLE PRECISION, DOUBLE PRECISION
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_dif'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION CIF
   INTEGER, CSTRING(256), CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_cif'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGCIF
   INTEGER, CSTRING(16384), CSTRING(16384)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_cif'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DTIF
   INTEGER, DATE, DATE
   RETURNS DATE
  ENTRY_POINT 'fn_dtif'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION IEQUAL
   INTEGER, INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_iequal'  MODULE_NAME 'rfunc';
/*
DECLARE EXTERNAL FUNCTION DEQUAL
   DOUBLE PRECISION, DOUBLE PRECISION
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_dequal'  MODULE_NAME 'rfunc';
*/
DECLARE EXTERNAL FUNCTION CEQUAL
   CSTRING(16384), CSTRING(16384)
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_cequal'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION DTEQUAL
   DATE, DATE
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_dtequal'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION MSGBOX
   CSTRING(16384),
   CSTRING(256),
   INTEGER
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_msgbox'  MODULE_NAME 'rfunc';

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

/* Simple parser */
DECLARE EXTERNAL FUNCTION CALCEXPR
   CSTRING(16384),
   CSTRING(16384)
   RETURNS DOUBLE PRECISION BY VALUE
  ENTRY_POINT 'fn_CalcExpr'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION EXPRISVALID
   CSTRING(16384),
   CSTRING(16384)
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_ExprIsValid'  MODULE_NAME 'rfunc';

/* Blob functions */
DECLARE EXTERNAL FUNCTION B_NUMBER_SEGMENTS
   BLOB
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_b_number_segments'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_MAX_SEGMENT
   BLOB
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_b_max_segment'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_TOTAL_LENGTH
   BLOB
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_b_total_length'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_LINE_COUNT
   BLOB
   RETURNS INTEGER BY VALUE
  ENTRY_POINT 'fn_b_line_count'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_SUBSTR
   BLOB, INTEGER, INTEGER
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_b_substr'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_LONGSUBSTR
   BLOB, INTEGER, INTEGER
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_b_longsubstr'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_LINE
   BLOB, INTEGER
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_b_line'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_LONGLINE
   BLOB, INTEGER
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_b_longline'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION B_PUT_SEGMENT
   CSTRING(16384),
   BLOB
   RETURNS PARAMETER 2
  ENTRY_POINT 'fn_b_put_segment'  MODULE_NAME 'rfunc';

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

/* Win1251 functions */
DECLARE EXTERNAL FUNCTION RUPPER
   CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_rupper'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGRUPPER
   CSTRING(16384)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_rupper'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION RLOWER
   CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_rlower'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGRLOWER
   CSTRING(16384)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_rlower'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION RLATIN
   CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_rlatin'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGRLATIN
   CSTRING(16384)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_rlatin'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION RTRANSLIT
   CSTRING(256)
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_rtranslit'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION LONGRTRANSLIT
   CSTRING(16384)
   RETURNS CSTRING(16384)
  ENTRY_POINT 'fn_longrtranslit'  MODULE_NAME 'rfunc';

DECLARE EXTERNAL FUNCTION SUBSTR
   CSTRING(16384), INTEGER, INTEGER
   RETURNS CSTRING(256)
  ENTRY_POINT 'fn_substr'  MODULE_NAME 'rfunc';

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

/* MD5 checksum functions */

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

COMMIT;
