/*====================================================================
		File rdrop.sql

		rFunc InterBase UDF library.
		Uninstall SQL-script for IB.

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
/* 4.2 Windows local */
/*CONNECT 'c:\progra~1\borland\intrbase\examples\employee.gdb' USER 'SYSDBA' PASSWORD 'masterkey';*/
/* 5.x Windows local */
/*CONNECT 'c:\progra~1\interb~1\interb~1\examples\database\employee.gdb' USER 'SYSDBA' PASSWORD 'masterkey';*/
/* 5.x Linux remote */
/*CONNECT 'iblinux:/usr/local/interbase/examples/employee.gdb' USER 'SYSDBA' PASSWORD 'masterkey';*/
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

/* Version functions */
DROP EXTERNAL FUNCTION LIBNAME;
DROP EXTERNAL FUNCTION LIBVERSION;

/* Date&Time functions */
DROP EXTERNAL FUNCTION YEAR;
DROP EXTERNAL FUNCTION MONTH;
DROP EXTERNAL FUNCTION DAY;
DROP EXTERNAL FUNCTION YEARDAY;
DROP EXTERNAL FUNCTION WEEKDAY;
DROP EXTERNAL FUNCTION HOUR;
DROP EXTERNAL FUNCTION MINUTE;
DROP EXTERNAL FUNCTION SECOND;

DROP EXTERNAL FUNCTION EXTRACTYEAR;
DROP EXTERNAL FUNCTION EXTRACTMONTH;
DROP EXTERNAL FUNCTION EXTRACTDAY;
DROP EXTERNAL FUNCTION EXTRACTYEARDAY;
DROP EXTERNAL FUNCTION EXTRACTWEEKDAY;
DROP EXTERNAL FUNCTION EXTRACTHOUR;
DROP EXTERNAL FUNCTION EXTRACTMINUTE;
DROP EXTERNAL FUNCTION EXTRACTSECOND;

DROP EXTERNAL FUNCTION EXTRACTMILLISECOND;

DROP EXTERNAL FUNCTION ISLEAPYEAR;
DROP EXTERNAL FUNCTION QUARTER;

DROP EXTERNAL FUNCTION DATETOSTR;
DROP EXTERNAL FUNCTION ENCODEDATE;
DROP EXTERNAL FUNCTION ENCODEDATETIME;
DROP EXTERNAL FUNCTION EXTRACTDATE;
DROP EXTERNAL FUNCTION EXTRACTTIME;

DROP EXTERNAL FUNCTION DOW;
DROP EXTERNAL FUNCTION DAYPERMONTH;

DROP EXTERNAL FUNCTION FIRSTDAYMONTH;
DROP EXTERNAL FUNCTION LASTDAYMONTH;

DROP EXTERNAL FUNCTION DAYSBETWEEN;
DROP EXTERNAL FUNCTION INCDATE;
DROP EXTERNAL FUNCTION INCDATETIME;

DROP EXTERNAL FUNCTION MAXDATE;
DROP EXTERNAL FUNCTION MINDATE;

DROP EXTERNAL FUNCTION TIMETODOUBLE;
DROP EXTERNAL FUNCTION DATETODOUBLE;
DROP EXTERNAL FUNCTION DOUBLETODATE;
DROP EXTERNAL FUNCTION DOUBLETOTIME;

/* Math functions */
DROP EXTERNAL FUNCTION ABS;
DROP EXTERNAL FUNCTION MAXNUM;
DROP EXTERNAL FUNCTION MINNUM;
DROP EXTERNAL FUNCTION CEIL;
DROP EXTERNAL FUNCTION FLOOR;
DROP EXTERNAL FUNCTION POWER;
DROP EXTERNAL FUNCTION ROUND;
DROP EXTERNAL FUNCTION SOFTROUND;
DROP EXTERNAL FUNCTION DIV;
DROP EXTERNAL FUNCTION MOD;
DROP EXTERNAL FUNCTION Z;
DROP EXTERNAL FUNCTION DZERO;

DROP EXTERNAL FUNCTION INITRANDOM;
DROP EXTERNAL FUNCTION GETRANDOM;

DROP EXTERNAL FUNCTION GETBIT;
DROP EXTERNAL FUNCTION SETBIT;
DROP EXTERNAL FUNCTION BITAND;
DROP EXTERNAL FUNCTION BITOR;
DROP EXTERNAL FUNCTION BITXOR;
DROP EXTERNAL FUNCTION BITNOT;

DROP EXTERNAL FUNCTION SIGN;

DROP EXTERNAL FUNCTION ACOS;
DROP EXTERNAL FUNCTION ASIN;
DROP EXTERNAL FUNCTION ATAN;
DROP EXTERNAL FUNCTION ATAN2;
DROP EXTERNAL FUNCTION COS;
DROP EXTERNAL FUNCTION COSH;
DROP EXTERNAL FUNCTION EXP;
DROP EXTERNAL FUNCTION LOG;
DROP EXTERNAL FUNCTION LN;
DROP EXTERNAL FUNCTION LOG10;
DROP EXTERNAL FUNCTION SIN;
DROP EXTERNAL FUNCTION SINH;
DROP EXTERNAL FUNCTION SQRT;
DROP EXTERNAL FUNCTION TAN;
DROP EXTERNAL FUNCTION TANH;
/* Constants rounded for 21 decimals */
DROP EXTERNAL FUNCTION E;
DROP EXTERNAL FUNCTION PI;

/* String functions */
DROP EXTERNAL FUNCTION CHR;
DROP EXTERNAL FUNCTION ORD;
DROP EXTERNAL FUNCTION LTRIM;
DROP EXTERNAL FUNCTION LONGLTRIM;
DROP EXTERNAL FUNCTION RTRIM;
DROP EXTERNAL FUNCTION LONGRTRIM;
DROP EXTERNAL FUNCTION TRIM;
DROP EXTERNAL FUNCTION STRTRIM;
DROP EXTERNAL FUNCTION LONGTRIM;
DROP EXTERNAL FUNCTION REPEATTRIM;
DROP EXTERNAL FUNCTION LONGREPEATTRIM;
DROP EXTERNAL FUNCTION RUPPER;
DROP EXTERNAL FUNCTION LONGRUPPER;
DROP EXTERNAL FUNCTION RLOWER;
DROP EXTERNAL FUNCTION LONGRLOWER;
DROP EXTERNAL FUNCTION RLATIN;
DROP EXTERNAL FUNCTION LONGRLATIN;
DROP EXTERNAL FUNCTION RTRANSLIT;
DROP EXTERNAL FUNCTION LONGRTRANSLIT;

DROP EXTERNAL FUNCTION SUBSTR;
DROP EXTERNAL FUNCTION LONGSUBSTR;
DROP EXTERNAL FUNCTION STRREPEAT;
DROP EXTERNAL FUNCTION LONGSTRREPEAT;
DROP EXTERNAL FUNCTION STRSTUFF;
DROP EXTERNAL FUNCTION LONGSTRSTUFF;
DROP EXTERNAL FUNCTION STRREPLACE;
DROP EXTERNAL FUNCTION LONGSTRREPLACE;
DROP EXTERNAL FUNCTION STRPOS;
DROP EXTERNAL FUNCTION STRLEN;
DROP EXTERNAL FUNCTION STRCOUNT;
DROP EXTERNAL FUNCTION STRCMP;
DROP EXTERNAL FUNCTION WORDCOUNT;
DROP EXTERNAL FUNCTION WORDNUM;
DROP EXTERNAL FUNCTION LONGWORDNUM;
DROP EXTERNAL FUNCTION PADRIGHT;
DROP EXTERNAL FUNCTION LONGPADRIGHT;
DROP EXTERNAL FUNCTION PADLEFT;
DROP EXTERNAL FUNCTION LONGPADLEFT;
DROP EXTERNAL FUNCTION C;
DROP EXTERNAL FUNCTION LONGC;
DROP EXTERNAL FUNCTION FLOATTOSTR;
DROP EXTERNAL FUNCTION INTTOSTR;
DROP EXTERNAL FUNCTION NUMINWORDS;
DROP EXTERNAL FUNCTION CONVERTSYMBOLS;
DROP EXTERNAL FUNCTION LONGCONVERTSYMBOLS;

/* Miscellaneous functions */
DROP EXTERNAL FUNCTION IIF;
DROP EXTERNAL FUNCTION DIF;
DROP EXTERNAL FUNCTION CIF;
DROP EXTERNAL FUNCTION LONGCIF;
DROP EXTERNAL FUNCTION DTIF;

DROP EXTERNAL FUNCTION IEQUAL;
/*DROP EXTERNAL FUNCTION DEQUAL;*/
DROP EXTERNAL FUNCTION CEQUAL;
DROP EXTERNAL FUNCTION DTEQUAL;

DROP EXTERNAL FUNCTION MSGBOX;
DROP EXTERNAL FUNCTION EAN13CS;
DROP EXTERNAL FUNCTION BCCHECKDIGIT;

DROP EXTERNAL FUNCTION CREATEGUID;

/* User manipulations */
DROP EXTERNAL FUNCTION ADD_USER;
DROP EXTERNAL FUNCTION MODIFY_USER;
DROP EXTERNAL FUNCTION DELETE_USER;

/* Simple parser */
DROP EXTERNAL FUNCTION CALCEXPR;
DROP EXTERNAL FUNCTION EXPRISVALID;

/* Blob functions */
DROP EXTERNAL FUNCTION B_NUMBER_SEGMENTS;
DROP EXTERNAL FUNCTION B_MAX_SEGMENT;
DROP EXTERNAL FUNCTION B_TOTAL_LENGTH;
DROP EXTERNAL FUNCTION B_LINE_COUNT;
DROP EXTERNAL FUNCTION B_SUBSTR;
DROP EXTERNAL FUNCTION B_LONGSUBSTR;
DROP EXTERNAL FUNCTION B_LINE;
DROP EXTERNAL FUNCTION B_LONGLINE;
DROP EXTERNAL FUNCTION B_PUT_SEGMENT;
DROP EXTERNAL FUNCTION B_STRCMP;
DROP EXTERNAL FUNCTION B_STRPOS;
DROP EXTERNAL FUNCTION B_TEXTPOS;

/* File functions */
DROP EXTERNAL FUNCTION FCREATE;
DROP EXTERNAL FUNCTION FOPEN;
DROP EXTERNAL FUNCTION FREAD;
DROP EXTERNAL FUNCTION LONGFREAD;
DROP EXTERNAL FUNCTION FWRITE;
DROP EXTERNAL FUNCTION FSEEK;
DROP EXTERNAL FUNCTION FCLOSE;
DROP EXTERNAL FUNCTION FREMOVE;
DROP EXTERNAL FUNCTION FSIZE;

/* File bit mask constants */
DROP EXTERNAL FUNCTION FSEEK_CUR;
DROP EXTERNAL FUNCTION FSEEK_END;
DROP EXTERNAL FUNCTION FSEEK_SET;
DROP EXTERNAL FUNCTION FO_RDONLY;
DROP EXTERNAL FUNCTION FO_WRONLY;
DROP EXTERNAL FUNCTION FO_RDWR;
DROP EXTERNAL FUNCTION FO_CREAT;
DROP EXTERNAL FUNCTION FO_TRUNC;
DROP EXTERNAL FUNCTION FO_EXCL;
DROP EXTERNAL FUNCTION FO_APPEND;
DROP EXTERNAL FUNCTION FS_IREAD;
DROP EXTERNAL FUNCTION FS_IWRITE;
DROP EXTERNAL FUNCTION FS_IEXEC;

/* MD5 checksum functions */
DROP EXTERNAL FUNCTION MD5SUM;

DROP EXTERNAL FUNCTION MD5INIT;
DROP EXTERNAL FUNCTION MD5UPDATE;
DROP EXTERNAL FUNCTION MD5FINAL;

COMMIT;