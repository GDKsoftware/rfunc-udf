/*====================================================================
      File rext.sql

      rFunc InterBase UDF library.
      Install SQL-script.

      Copyright 1998-2003 Polaris Software
      http://rfunc.sourceforge.net
      mailto:rFunc@mail.ru

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

/* Extended functions */

DECLARE EXTERNAL FUNCTION num_extr
    CSTRING(16384)
RETURNS INTEGER BY VALUE
ENTRY_POINT 'fn_num_extr' MODULE_NAME 'rfunc';
