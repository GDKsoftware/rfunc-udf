/*====================================================================
		File rfunc_45to6.sql

		rFunc InterBase UDF library.
		Update SQL-script for migrate DB from IB 4,5 to IB 6 or later.
                For InterBase 6 or later.

		Copyright 2003-2007, PSTG
		http://rfunc.sourceforge.net
		mailto:rFunc@mail.ru

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.
    See license.txt for more details.

====================================================================== */

/* ATTENTION!
   This script must be executed on IB 4.õ or 5.x servers
   BEFORE restoring database on IB 6 or later.
*/

/* Define valid path and password for your database */
/* 4.2 Windows local */
/*CONNECT 'c:\progra~1\borland\intrbase\examples\employee.gdb' USER 'SYSDBA' PASSWORD 'masterkey';*/
/* 5.x Windows local */
/*CONNECT 'c:\progra~1\interb~1\interb~1\examples\database\employee.gdb' USER 'SYSDBA' PASSWORD 'masterkey';*/
/* 5.x Linux remote */
/*CONNECT 'iblinux:/usr/local/interbase/examples/employee.gdb' USER 'SYSDBA' PASSWORD 'masterkey';*/

/* On IB 6 and FB: next functions has same names as reserved words.
   ATTENTION!
   All dependencies on followed XXX functions must be replaced with ExtractXXX functions
   BEFORE executing this script!
*/
DROP EXTERNAL FUNCTION YEAR;
DROP EXTERNAL FUNCTION MONTH;
DROP EXTERNAL FUNCTION DAY;
DROP EXTERNAL FUNCTION YEARDAY;
DROP EXTERNAL FUNCTION WEEKDAY;
DROP EXTERNAL FUNCTION HOUR;
DROP EXTERNAL FUNCTION MINUTE;
DROP EXTERNAL FUNCTION SECOND;


/* On IB 6 and FB: size of char parameters (CSTRING) need decrement */
update RDB$FUNCTION_ARGUMENTS fa
   set RDB$FIELD_LENGTH = RDB$FIELD_LENGTH - 1
 where RDB$FIELD_TYPE = 40 and 
       (RDB$FIELD_LENGTH IN (2, 9, 33, 39, 177, 256, 8192, 16384) or (RDB$FIELD_LENGTH = 32 and RDB$FUNCTION_NAME NOT LIKE 'MD5%')) and
       (SELECT RDB$MODULE_NAME FROM RDB$FUNCTIONS f WHERE f.RDB$FUNCTION_NAME=fa.RDB$FUNCTION_NAME) = 'rfunc';

COMMIT;
