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
COMMIT;