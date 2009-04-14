/*====================================================================
    File rtest.sql

    rFunc InterBase UDF library.
    SQL-script for testing rFunc.

    Copyright 2009 PoleSoft Technologies Group
    http://www.polesoft.ru/project/rfunc
    mailto:support@polesoft.ru

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.
    See license.txt for more details.

====================================================================== */

SET NAMES win1251;

/* Define valid path and password for your database */
/* 4.2 Windows local */
/*CONNECT 'c:\progra~1\borland\intrbase\examples\employee.gdb' USER 'SYSDBA' PASSWORD 'masterkey';*/
/* 5.x Windows local */
/*CONNECT 'c:\progra~1\interb~1\interb~1\examples\database\employee.gdb' USER 'SYSDBA' PASSWORD 'masterke';*/
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

DROP TABLE R_TEST_RFUNC;
CREATE GENERATOR R_TEST_RFUNC;
SET GENERATOR R_TEST_RFUNC TO 0;
CREATE TABLE R_TEST_RFUNC (R_ID INTEGER NOT NULL PRIMARY KEY, R_COMMAND VARCHAR(127), R_RESULT VARCHAR(255), R_PROBABLYRESULT VARCHAR(255));

SET TERM ^;

/* valid only for IB for Windows */
CREATE TRIGGER T_BI_COMMAND FOR R_TEST_RFUNC
ACTIVE BEFORE INSERT POSITION 0
AS
  DECLARE VARIABLE I INTEGER;
BEGIN
  IF (StrPos('Add_User', NEW.R_COMMAND) = 1) THEN
    IF (NEW.R_RESULT = '0') THEN
      i = MsgBox('User added!!!', 'rFunc test', 0);
    ELSE
      i = MsgBox('User NOT added!!!', 'rFunc test', 0);
  ELSE IF (StrPos('Modify_User', NEW.R_COMMAND) = 1) THEN
    IF (NEW.R_RESULT = '0') THEN
      i = MsgBox('User modified!!!', 'rFunc test', 0);
    ELSE
      i = MsgBox('User NOT modified!!!', 'rFunc test', 0);
  ELSE IF (StrPos('Delete_User', NEW.R_COMMAND) = 1) THEN
    IF (NEW.R_RESULT = '0') THEN
      SELECT MsgBox('User deleted!!!', 'rFunc test', 0) FROM RDB$DATABASE INTO I;
    ELSE
      SELECT MsgBox('User NOT deleted!!!', 'rFunc test', 0) FROM RDB$DATABASE INTO I;
END ^

CREATE TRIGGER T_BI_COMMAND2 FOR R_TEST_RFUNC
ACTIVE BEFORE INSERT POSITION 1
AS
BEGIN
  IF (StrLen(Trim(NEW.R_COMMAND)) = 0) THEN
    NEW.R_COMMAND = 'Unknown command';
  IF (Z(NEW.R_ID) = 0) THEN
    NEW.R_ID = GEN_ID(R_TEST_RFUNC, 1);
END ^

CREATE PROCEDURE R_RFUNC_TEST_BLOB
AS
  DECLARE VARIABLE B BLOB SUB_TYPE TEXT SEGMENT SIZE 40;
BEGIN
  /* Select T_BI_COMMAND2 trigger body */
  SELECT RDB$TRIGGER_SOURCE
    FROM RDB$TRIGGERS
   WHERE RDB$TRIGGER_NAME = 'T_BI_COMMAND2'
    INTO B;
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B_Number_Segments(B) [B is T_BI_COMMAND2 trigger body]', b_number_segments(:B), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B_Max_Segment(B)', b_max_segment(:B), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B_Total_Length(B)', b_total_length(:B), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B_Line_Count(B)', b_line_count(:B), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B_Substr(B, 1, 7)', b_substr(:B, 1, 7), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B_Substr(B, 20, 10)', b_substr(:B, 20, 10), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B_Line(B, 1)', b_line(:B, 1), '');
  /* Check old T_BI_COMMAND2 trigger body */
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B_Line(B, 4)', b_line(:B, 4), '');
/*  INSERT INTO R_TEST_RFUNC VALUES ('', '[trigger test]');*/
  INSERT INTO R_TEST_RFUNC VALUES (0, 'LongStrReplace(B_LongSubstr(B, 1, B_Total_Length(B)), ''Unknown'', ''BAD'')',
                                   LongStrReplace(B_LongSubstr(:B, 1, B_Total_Length(:B)), 'Unknown', 'BAD'), '');
  /* Change T_BI_COMMAND2 trigger body */
  UPDATE RDB$TRIGGERS SET RDB$TRIGGER_SOURCE = B_Put_Segment(LongStrReplace(B_LongSubstr(:B, 1, B_Total_Length(:B)), 'Unknown', 'BAD'))
   WHERE RDB$TRIGGER_NAME = 'T_BI_COMMAND2';
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B = B_Put_Segment(LongStrReplace(B_LongSubstr(B, 1, B_Total_Length(B)), ''Unknown'', ''BAD'')',
                                   '[change T_BI_COMMAND2 trigger]', '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B_StrCmp(B1, B2)',
     b_strcmp(:B, (SELECT RDB$TRIGGER_SOURCE FROM RDB$TRIGGERS WHERE RDB$TRIGGER_NAME = 'T_BI_COMMAND2')), '');
  /* Check new T_BI_COMMAND2 trigger body */
  SELECT RDB$TRIGGER_SOURCE
    FROM RDB$TRIGGERS
   WHERE RDB$TRIGGER_NAME = 'T_BI_COMMAND2'
    INTO B;
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B_Line(B, 4)', b_line(:B, 4), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B_StrPos(''beg'', B)', b_strpos('beg', :B), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B_TextPos(''beg'', B)', b_textpos('beg', :B), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B_StrUpper(B)', b_strupper(:B), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'B_StrLower(B)', b_strlower(:B), '');
END ^

CREATE PROCEDURE R_RFUNC_TEST_MD5
AS
  DECLARE VARIABLE S VARCHAR(8191);
  DECLARE VARIABLE context CHAR(176);
  DECLARE VARIABLE i INTEGER;
  DECLARE VARIABLE step INTEGER;
  DECLARE VARIABLE s2 VARCHAR(127);
BEGIN
  SELECT B_LONGSUBSTR(RDB$TRIGGER_SOURCE, 1, 8191)
    FROM RDB$TRIGGERS
   WHERE RDB$TRIGGER_NAME = 'T_BI_COMMAND2'
    INTO S;
  INSERT INTO R_TEST_RFUNC VALUES (0, 'MD5Sum(S)', md5sum(:S), '31F679C4086E4A523D75867A36CE354B');
  context = md5init();
  step = 10;
  i = 1;
  WHILE (i <= StrLen(S)) DO BEGIN
    s2 = SubStr(S, i, step);
    context = md5update(context, s2, StrLen(s2));
    i = i + step;
  END
  INSERT INTO R_TEST_RFUNC VALUES (0, 'MD5Init-MD5Update-MD5Final', md5final(:context), '31F679C4086E4A523D75867A36CE354B');
END ^

CREATE PROCEDURE R_RFUNC_TEST_FILE
AS
  DECLARE VARIABLE fn VARCHAR(30);
  DECLARE VARIABLE h INTEGER;
  DECLARE VARIABLE h2 INTEGER;
BEGIN
  fn = '/rfunc_test';
  h = fcreate(fn, FS_IREAD()+FS_IWRITE());
  INSERT INTO R_TEST_RFUNC VALUES (0, 'h = FCreate('''||:fn||''', FS_IREAD()+FS_IWRITE())', :h, '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FWrite(h, ''=== rFunc UDF Library test file ==='')||chr(13)||chr(10)', fwrite(:h, '=== rFunc UDF Library test file ==='||chr(13)||chr(10)), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FWrite(h, ''Only test...  nothing interesting...'')', fwrite(:h, 'Only test...  nothing interesting...'), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FClose(h)', fclose(:h), '');
  h = fopen(fn, FO_RDONLY(), 0);
  INSERT INTO R_TEST_RFUNC VALUES (0, 'h = FOpen('''||:fn||''', FO_RDONLY(), 0)', :h, '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FRead(h, 7)', fread(:h, 7), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FSeek(h, 3, FSEEK_CUR())', fseek(:h, 3, FSEEK_CUR()), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FRead(h, 7)', fread(:h, 7), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FSeek(h, -14, FSEEK_END())', fseek(:h, -14, FSEEK_END()), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FRead(h, 11)', fread(:h, 11), '');
  h2 = fopen(fn, FO_WRONLY(), 0);
  INSERT INTO R_TEST_RFUNC VALUES (0, 'h2 = FOpen('''||:fn||''', FO_WRONLY(), 0)', :h2, '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FSeek(h2, 3, FSEEK_SET())', fseek(:h2, 3, FSEEK_SET()), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FWrite(h2, ''!'')', fwrite(:h2, '!'), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FSeek(h, 0, FSEEK_SET())', fseek(:h, 0, FSEEK_SET()), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FRead(h, 7)', fread(:h, 7), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FClose(h2)', fclose(:h2), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FSize('''||:fn||''')', fsize(:fn), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FClose(h)', fclose(:h), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FRemove('''||:fn||''')', fremove(:fn), '');

  h2 = fopen(fn, FO_CREAT()+FO_WRONLY(), FS_IREAD()+FS_IWRITE());
  INSERT INTO R_TEST_RFUNC VALUES (0, 'h2 = FOpen('''||:fn||''', FO_CREAT()+FO_WRONLY(), FS_IREAD()+FS_IWRITE())', :h2, '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'Save R_TEST_RFUNC to file...', (select count(*)+1 from R_TEST_RFUNC) || ' records', '');
  h = FWrite(h2, ' No. ' || PadRight('Command', 51, ' ') || 'Result' || chr(13)||chr(10));
  h = FWrite(h2, StrRepeat('=', 5+51+100) || chr(13)||chr(10));
  FOR
    SELECT FWrite(:h2, PadLeft(R_ID, 3, ' ') || '. ' || PadRight(Substr(R_COMMAND, 1, 50), 50, ' ') || 
                      ' ' || R_RESULT || chr(13)||chr(10))
      FROM R_TEST_RFUNC
     ORDER BY R_ID
      INTO h
  DO
    h = h;
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FClose(h2)', fclose(:h2), '');
  INSERT INTO R_TEST_RFUNC VALUES (0, 'FSize('''||:fn||''')', fsize(:fn), '');
END ^

SET TERM ;^

/* Date&Time functions */

INSERT INTO R_TEST_RFUNC VALUES (0, 'DateTime functions', '----------------', '----------------');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ExtractYear(''NOW'')', extractyear('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ExtractMonth(''NOW'')', extractmonth('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Quarter(''NOW'')', quarter('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ExtractDay(''NOW'')', extractday('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ExtractYearDay(''NOW'')', extractyearday('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ExtractWeekDay(''NOW'')', extractweekday('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DOW(''NOW'')', dow('NOW') , '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ExtractHour(''NOW'')', extracthour('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ExtractMinute(''NOW'')', extractminute('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ExtractSecond(''NOW'')', extractsecond('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ExtractMillisecond(''NOW'')', extractmillisecond('NOW'), '-');

INSERT INTO R_TEST_RFUNC VALUES (0, 'ExtractDate(''NOW'')', extractdate('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ExtractTime(''NOW'')', extracttime('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DayPerMonth(ExtractMonth(''NOW''), ExtractYear(''NOW''))', daypermonth(extractmonth('NOW'), extractyear('NOW')), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DayPerMonth(2, 1996)', daypermonth(2, 1996), '29');
INSERT INTO R_TEST_RFUNC VALUES (0, 'FirstDayMonth(''NOW'')', firstdaymonth('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'LastDayMonth(''NOW'')', lastdaymonth('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'IsLeapYear(ExtractYear(''NOW''))', isleapyear(extractyear('NOW')), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'IsLeapYear(1996)', isleapyear(1996), '1');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DaysBetween(FirstDayMonth(''NOW''), ''NOW'')', daysbetween(FirstDayMonth('NOW'), 'NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DaysBetween(''NOW'', FirstDayMonth(''NOW''))', daysbetween('NOW', FirstDayMonth('NOW')), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'IncDate(''NOW'', 0, 2, 0)', incdate('NOW', 0, 2, 0), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'IncDateTime(''NOW'', 0, 2, 0, 1, 2, 3)', incdatetime('NOW', 0, 2, 0, 1, 2, 3), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'IncDate(''NOW'', -1, 2, -2)', incdate('NOW', -1, 2, -2), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'IncDateTime(''NOW'', -1, 2, -2, -1, 2, -3)', incdatetime('NOW', -1, 2, -2, -1, 2, -3), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'MaxDate(''NOW'', ''TODAY'')', maxdate('NOW', 'TODAY'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'MinDate(''NOW'', ''TODAY'')', mindate('NOW', 'TODAY'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DtEqual(''NOW'', ''TODAY'')', dtequal('NOW', 'TODAY'), '-');
COMMIT;

/* Math functions */

INSERT INTO R_TEST_RFUNC VALUES (0, 'Math functions', '----------------', '----------------');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Abs(-23)', abs(-23), '23.00000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'MaxNum(23, 45)', maxnum(23, 45), '45.00000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'MinNum(23, 45)', minnum(23, 45), '23.00000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Ceil(23.5)', ceil(23.5), '24.00000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Floor(23.5)', floor(23.5), '23.00000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Power(256, 0)', power(256, 0), '1.000000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Power(256, 0.5)', power(256, 0.5), '16.00000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Power(256, 2)', power(256, 2), '65536.00000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Power(256, -1)', power(256, -1), '0.003906250000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Power(-2, 2)', power(-2, 2), '4.000000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Round(23.45, 0)', round(23.45, 0), '23.00000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Round(23.45, 1)', round(23.45, 1), '23.50000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Round(23.45, -1)', round(23.45, -1), '20.00000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Round(0.45, 0)', round(0.45, 0), '0.0000000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SoftRound(0.45, 0)', softround(0.45, 0), '0.4500000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Div(7, 2)', div(7, 2), '3');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Mod(7, 2)', mod(7, 2), '1');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Z(NULL)', z(CAST(NULL AS INTEGER)), '0.0000000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Z(23.4)', z(23.4), '23.40000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DZero(5, 2, -1)', dzero(5, 2, -1), '2.500000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DZero(5, 0, -1)', dzero(5, 0, -1), '-1.000000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'InitRandom(1000)', initrandom(1000), '1');
INSERT INTO R_TEST_RFUNC VALUES (0, 'GetRandom(1000)', getrandom(1000), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'GetRandom(1000)', getrandom(1000), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'GetRandom(1000)', getrandom(1000), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'IEqual(10, 10)', iequal(10, 10), '1');
INSERT INTO R_TEST_RFUNC VALUES (0, 'IEqual(1, 10)', iequal(1, 10), '0');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Sign(12.5)', sign(12.5), '1');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Sign(0)', sign(0), '0');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Sign(-12)', sign(-12), '-1');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Sqrt(16)', sqrt(16), '4.000000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Exp(2)', exp(2), '7.389056098930650');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Log(16, 2)', log(16, 2), '4.000000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Log10(100)', log10(100), '2.000000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Ln(3)', ln(3), '1.098612288668110');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Ln(E())', ln(e()), '1.000000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'E()', e(), '2.718281828459045');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Fact()', Fact(10), '3628800.000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Trigonometric functions', '----------------', '----------------');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ACos(1)', acos(1), '0.0000000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ASin(1)', asin(1), '1.570796326794897');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ATan(1)', atan(1), '0.7853981633974483');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ATan2(1, 2)', atan2(1, 2), '0.4636476090008061');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Cos(Pi())', cos(Pi()), '-1.000000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'CosH(Pi())', cosh(Pi()), '11.59195327552152');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Sin(Pi())', sin(Pi()), '1.224606353822377e-016');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SinH(Pi())', sinh(Pi()), '11.54873935725775');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Tan(Pi())', tan(Pi()), '-1.224606353822377e-016');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Tanh(Pi())', tanh(Pi()), '0.9962720762207500');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Pi()', Pi(), '3.141592653589793');

INSERT INTO R_TEST_RFUNC VALUES (0, 'Bit functions', '----------------', '----------------');
INSERT INTO R_TEST_RFUNC VALUES (0, 'GetBit(5,2) || GetBit(5,1) || GetBit(5,0)', getbit(5, 2)||getbit(5, 1)||getbit(5, 0), '101');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SetBit(5, 1, 1) [101 -> 111]', setbit(5, 1, 1), '7');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SetBit(5, 0, 0) [101 -> 100]', setbit(5, 0, 0), '4');
INSERT INTO R_TEST_RFUNC VALUES (0, 'BitAnd(5, 9) [0101 AND 1001 = 0001]', bitand(5, 9), '1');
INSERT INTO R_TEST_RFUNC VALUES (0, 'BitOr(5, 9)  [0101 OR  1001 = 1101]', bitor(5, 9), '13');
INSERT INTO R_TEST_RFUNC VALUES (0, 'BitXor(5, 9) [0101 XOR 1001 = 1100]', bitxor(5, 9), '12');
INSERT INTO R_TEST_RFUNC VALUES (0, 'BitNot(5)', bitnot(5), '-6');
COMMIT;

/* String functions */

INSERT INTO R_TEST_RFUNC VALUES (0, 'String functions', '----------------', '----------------');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Chr(65)', chr(65), 'A');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Ord(''A'')', ord('A'), '65');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Trim(''  rFunc  '')', '['||trim('  rFunc  ')||']', '[rFunc]');
INSERT INTO R_TEST_RFUNC VALUES (0, 'LTrim(''  rFunc  '')', '['||ltrim('  rFunc  ')||']', '[rFunc  ]');
INSERT INTO R_TEST_RFUNC VALUES (0, 'RTrim(''  rFunc  '')', '['||rtrim('  rFunc  ')||']', '[  rFunc]');
INSERT INTO R_TEST_RFUNC VALUES (0, 'RUpper(''Ѕиблиотека rFunc'') [it is on russian]', rupper('Ѕиблиотека rFunc'), 'Ѕ»ЅЋ»ќ“≈ ј RFUNC');
INSERT INTO R_TEST_RFUNC VALUES (0, 'RLower(''Ѕиблиотека rFunc'') [it is on russian]', rlower('Ѕиблиотека rFunc'), 'библиотека rfunc');
INSERT INTO R_TEST_RFUNC VALUES (0, 'RLatin(''rFunc - хороша€ библиотека :)'') [it is on russian]', rlatin('rFunc - хороша€ библиотека :)'), 'rFunc - horosaj biblioteka :)');
INSERT INTO R_TEST_RFUNC VALUES (0, 'RTranslit(''rFunc - хороша€ библиотека :)'') [it is on russian]', rtranslit('rFunc - хороша€ библиотека :)'), 'rFunc - khoroshaya biblioteka :)');
INSERT INTO R_TEST_RFUNC VALUES (0, 'RLatin(''й.ц.ш.щ.х.ф.ы.ж.€.ч.ь.ъ.ю.Є'') [it is on russian]', rlatin('й.ц.ш.щ.х.ф.ы.ж.€.ч.ь.ъ.ю.Є'), 'j.c.s.s.h.f.i.j.j.c._._.u.e');
INSERT INTO R_TEST_RFUNC VALUES (0, 'RTranslit(''й.ц.ш.щ.х.ф.ы.ж.€.ч.ь.ъ.ю.Є'') [it is on russian]', rtranslit('й.ц.ш.щ.х.ф.ы.ж.€.ч.ь.ъ.ю.Є'), 'y.ts.sh.sch.kh.f.y.zh.ya.ch...yu.yo');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SubStr(''rFunc'', 2, 1)', substr('rFunc', 2, 1), 'F');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SubStr(''rFunc'', 2, 10)', substr('rFunc', 2, 10), 'Func');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SubStr(''rFunc'', 2, -1)', substr('rFunc', 2, -1), 'F');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SubStr(''rFunc'', -2, 1)', substr('rFunc', -2, 1), 'n');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SubStr(''rFunc'', -2, -1)', substr('rFunc', -2, -1), 'n');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SubStr(''rFunc'', -2, -10)', substr('rFunc', -2, -10), 'rFun');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrRepeat(''rFunc'', 2)', strrepeat('rFunc', 2), 'rFuncrFunc');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrStuff(''rFunc'', 2, 0, ''us'') [insert]', strstuff('rFunc', 2, 0, 'us'), 'rusFunc');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrStuff(''rFunc'', 2, 1, '''') [delete]', strstuff('rFunc', 2, 1, ''), 'runc');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrStuff(''rFunc'', 2, 1, ''Tr'') [delete & insert]', strstuff('rFunc', 2, 1, 'Tr'), 'rTrunc');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrReplace(''rFunc Fun'', ''Fun'', ''Pro'')', strreplace('rFunc Fun', 'Fun', 'Pro'), 'rProc Pro');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrPos(''Fu'', ''rFunc'')', strpos('Fu', 'rFunc'), '2');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrPos(''Fi'', ''rFunc'')', strpos('Fi', 'rFunc'), '0');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrLen(''rFunc'')', strlen('rFunc'), '5');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrCount(''un'', ''rFunc Fun'')', strcount('un', 'rFunc Fun'), '2');
INSERT INTO R_TEST_RFUNC VALUES (0, 'WordCount(''rFunc-Fun'', ''-'',  0)', wordcount('rFunc Fun', ' ', 0), '2');
INSERT INTO R_TEST_RFUNC VALUES (0, 'WordCount(''rFunc-Fun'', ''-F'', 0)', wordcount('rFunc Fun', ' F', 0), '3');
INSERT INTO R_TEST_RFUNC VALUES (0, 'WordCount(''rFunc-Fun'', ''-F'', 1)', wordcount('rFunc Fun', ' F', 1), '4');
INSERT INTO R_TEST_RFUNC VALUES (0, 'WordNum(''rFunc-Fun'', 1, ''-'',  0)', wordnum('rFunc Fun', 1, ' ', 0), 'rFunc');
INSERT INTO R_TEST_RFUNC VALUES (0, 'WordNum(''rFunc-Fun'', 3, ''-F'', 0)', wordnum('rFunc Fun', 3, ' F', 0), 'un');
INSERT INTO R_TEST_RFUNC VALUES (0, 'WordNum(''rFunc-Fun'', 3, ''-F'', 1)', wordnum('rFunc Fun', 3, ' F', 1), '');
INSERT INTO R_TEST_RFUNC VALUES (0, 'PadLeft(''rFunc'', 10, ''?'')', padleft('rFunc', 10, '?'), '?????rFunc');
INSERT INTO R_TEST_RFUNC VALUES (0, 'PadRight(''rFunc'', 10, ''!'')', padright('rFunc', 10, '!'), 'rFunc!!!!!');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrCmp(''rFunc'', ''rFunc'')', strcmp('rFunc', 'rFunc'), '0');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrCmp(''rFUnc'', ''rFunc'')', strcmp('rFUnc', 'rFunc'), '-32');
INSERT INTO R_TEST_RFUNC VALUES (0, 'C(NULL)', c(CAST(NULL AS VARCHAR(1))), '');
INSERT INTO R_TEST_RFUNC VALUES (0, 'C(''rFunc'')', c('rFunc'), 'rFunc');
INSERT INTO R_TEST_RFUNC VALUES (0, 'CEqual(''rFunc'', ''rFunc'')', cequal('rFunc', 'rFunc'), '1');
INSERT INTO R_TEST_RFUNC VALUES (0, 'CEqual(''rFUnc'', ''rFunc'')', cequal('rFUnc', 'rFunc'), '0');
INSERT INTO R_TEST_RFUNC VALUES (0, 'RepeatTrim(''rFunnnc is a finne library'', ''n'')', repeattrim('rFunnnc is a finne library', 'n'), 'rFunc is a fine library');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ConvertSymbols(''rPunk is a fine library'', ''Pk'', ''Fc'')', convertsymbols('rPunk is a fine library', 'Pk', 'Fc'), 'rFunc is a fine library');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrNPos(''r'', ''rFunc library'', 1, 2)', strnpos('r', 'rFunc library', 1, 2), '10');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrNPos(''r'', ''rFunc library'', 1, 3)', strnpos('r', 'rFunc library', 1, 3), '12');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrNPosR(''r'', ''rFunc library'', 1, 2)', strnposr('r', 'rFunc library', 1, 2), '4');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrNPosR(''r'', ''rFunc library'', 1, 3)', strnposr('r', 'rFunc library', 1, 3), '14');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrPosR(''r'', ''rFunc library'')', strposr('r', 'rFunc library'), '2');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SubStrR(''rFunc library'', 1, 7)', substrr('rFunc library', 1, 7), 'library');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SubStrR(''rFunc library'', 1, 15)', substrr('rFunc library', 1, 15), 'rFunc library');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SubStrR(''rFunc library'', 7, -7)', substrr('rFunc library', 7, -7), 'library');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SubStrR(''rFunc library'', -5, 5)', substrr('rFunc library', -5, 5), 'rFunc');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SubStrR(''rFunc library'', -2, 1)', substrr('rFunc library', -2, 1), 'F');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SubStrR(''rFunc library'', -2, -1)', substrr('rFunc library', -2, -1), 'F');
INSERT INTO R_TEST_RFUNC VALUES (0, 'SubStrR(''rFunc library'', -2, -10)', substrr('rFunc library', -2, -8), 'Func lib');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrEsc(''\171rFunc\187\tgood library\n\123rFunc\125\tfast library'')', stresc('\171rFunc\187\tgood library\n\123rFunc\125\tfast library'), 'ЂrFuncї  good library
{rFunc}  fast library');
INSERT INTO R_TEST_RFUNC VALUES (0, 'StrMirror(''rFunc lib'')', strmirror('rFunc lib'), 'bil cnuFr');
INSERT INTO R_TEST_RFUNC VALUES (0, 'cr()||''rFunc''||lf()||''rFunc''||crlf()||tab()||''rFunc''', cr()||'rFunc'||lf()||'rFunc'||crlf()||tab()||'rFunc', '
rFunc
rFunc
  rFunc');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Str2Hex(''rFunc lib'')', str2hex('rFunc lib'), '7246756e63206c6962');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Hex2Str(''7246756e63206c6962'')', hex2str('7246756e63206c6962'), 'rFunc lib');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Xml2Str(''<rFunc>ІІgood&fast</rFunc>'')', xml2str('<rFunc>ІІgood&fast</rFunc>'), '&lt;rFunc&gt;ІІgood&amp;fast&lt;/rFunc&gt;');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Str2Xml(''&lt;rFunc&gt;&#167;&#xA7;good&amp;fast&lt;/rFunc&gt;'')', str2xml('&lt;rFunc&gt;&#167;&#xA7;good&amp;fast&lt;/rFunc&gt;'), '<rFunc>ІІgood&fast</rFunc>');
COMMIT;

/* Datatypes conversion functions */

INSERT INTO R_TEST_RFUNC VALUES (0, 'Datatypes conversion functions', '----------------', '----------------');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DateToStr(''NOW'', ''%d.%m.%y'')', datetostr('NOW', '%d.%m.%y'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DateToStr(''NOW'', ''%d %B %Y, %X'')', datetostr('NOW', '%d %B %Y, %X'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'EncodeDate(3, 5, 2001)', encodedate(3, 5, 2001), '3-MAY-2001');
INSERT INTO R_TEST_RFUNC VALUES (0, 'EncodeDate(0, 5, 2001)', encodedate(0, 5, 2001), '30-APR-2001');
INSERT INTO R_TEST_RFUNC VALUES (0, 'EncodeDateTime(3, 5, 2001, 12, 14, 35)', encodedatetime(3, 5, 2001, 12, 14, 35), '3-MAY-2001 12:14:35.0000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'EncodeDateTime(3, 5, 99, 12, 14, 66)', encodedatetime(3, 5, 99, 12, 14, 66), '3-MAY-99 12:15:06.0000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'TimeToDouble(''NOW'')', timetodouble('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DateToDouble(''NOW'')', datetodouble('NOW'), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DoubleToTime(TimeToDouble(''NOW''))', doubletotime(timetodouble('NOW')), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DoubleToDate(DateToDouble(''NOW''))', doubletodate(datetodouble('NOW')), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'FloatToStr(13.5, ''%7.3e'')', floattostr(13.5, '%7.3e'), '1.350e+01');
INSERT INTO R_TEST_RFUNC VALUES (0, 'FloatToStr(13.5, ''%+7.3f'')', floattostr(13.5, '%+7.3f'), '+13.500');
INSERT INTO R_TEST_RFUNC VALUES (0, 'FloatToStr(13.5345, ''%.5g'')', floattostr(13.5345, '%.5g'), '13.534');
INSERT INTO R_TEST_RFUNC VALUES (0, 'FloatToStr(13.5345, ''%.5f'')', floattostr(13.5345, '%.5f'), '13.53450');
INSERT INTO R_TEST_RFUNC VALUES (0, 'IntToStr(13, ''%05X'')', inttostr(13, '%05X'), '0000D');
INSERT INTO R_TEST_RFUNC VALUES (0, 'IntToStr(13, ''%#04x'')', inttostr(13, '%#04x'), '0x0d');
INSERT INTO R_TEST_RFUNC VALUES (0, 'IntToStr(13, ''%5d'')', inttostr(13, '%5d'), '   13');
INSERT INTO R_TEST_RFUNC VALUES (0, 'NumInWords(12341, ''M'')||''рубль'' [it is on russian]', numinwords(12341, 'M')||'рубль', 'двенадцать тыс€ч триста сорок один рубль');
INSERT INTO R_TEST_RFUNC VALUES (0, 'NumInWords(1000341, ''F'')||''крона'' [it is on russian]', numinwords(1000341, 'F')||'крона', 'один миллион триста сорок одна крона');
INSERT INTO R_TEST_RFUNC VALUES (0, 'NumInWords(1100341, ''N'')||''песо'' [it is on russian]', numinwords(1100341, 'N')||'песо', 'один миллион сто тыс€ч триста сорок одно песо');
INSERT INTO R_TEST_RFUNC VALUES (0, 'NumInWords(341, ''P'')||''ножницы'' [it is on russian]', numinwords(341, 'P')||'ножницы', 'триста сорок одни ножницы');
COMMIT;

/* Special functions */

INSERT INTO R_TEST_RFUNC VALUES (0, 'Special functions', '----------------', '----------------');
INSERT INTO R_TEST_RFUNC VALUES (0, 'LibVersion()', libversion(), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'LibName()', libname(), 'rfunc');
INSERT INTO R_TEST_RFUNC VALUES (0, 'EAN13cs(''123456789012'')', ean13cs('123456789012'), '8');
INSERT INTO R_TEST_RFUNC VALUES (0, 'CreateGUID()', createguid(), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'MD5 functions', '----------------', '----------------');
EXECUTE PROCEDURE R_RFUNC_TEST_MD5;
COMMIT;

/* Miscellaneous functions */

INSERT INTO R_TEST_RFUNC VALUES (0, 'Misc functions', '----------------', '----------------');
INSERT INTO R_TEST_RFUNC VALUES (0, 'IIf( 0, 11, 12)', iif(0, 11, 12), '12');
INSERT INTO R_TEST_RFUNC VALUES (0, 'IIf( 2, 11, 12)', iif(2, 11, 12), '11');
INSERT INTO R_TEST_RFUNC VALUES (0, 'IIf(-2, 11, 12)', iif(-2, 11, 12), '11');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DIf( 0, 1.1, 1.2)', dif(0, 1.1, 1.2), '1.200000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DIf( 1, 1.1, 1.2)', dif(1, 1.1, 1.2), '1.100000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'CIf( 0, ''A'', ''B'')', cif(0, 'A', 'B'), 'B');
INSERT INTO R_TEST_RFUNC VALUES (0, 'CIf( 1, ''A'', ''B'')', cif(1, 'A', 'B'), 'A');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DtIf( 0, ''NOW'', ''NOW''-1)', dtif(0, 'NOW', CAST('NOW' AS DATE)-1), '-');
INSERT INTO R_TEST_RFUNC VALUES (0, 'DtIf( 1, ''NOW'', ''NOW''-1)', dtif(1, 'NOW', CAST('NOW' AS DATE)-1), '-');
COMMIT;

/* valid only for IB for Windows */
INSERT INTO R_TEST_RFUNC VALUES (0, 'MsgBox( , , 0)', msgbox('rFuncLib MsgBox(,,0)'||chr(13)||'It is working!!!', 'rFunc test', 0), '1');
INSERT INTO R_TEST_RFUNC VALUES (0, 'MsgBox( , , 1)', msgbox('rFuncLib MsgBox(,,1)'||chr(13)||'It is working!!!', 'rFunc test', 1), '2');
COMMIT;

/* User manipulations */
/* valid only for IB 5.x or later */

INSERT INTO R_TEST_RFUNC VALUES (0, 'User functions', '----------------', '----------------');

/* Define valid protocol (1-TCP, 2-NetBEUI, 4-local) and server name */
INSERT INTO R_TEST_RFUNC VALUES (0, 'Add_User()', add_user(4, '', 'RFUNC', 'qwerty', '', 'rFunc', 'UDF', 'Library', 'SYSDBA', 'masterke'), '0');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Modify_User()', modify_user(4, '', 'RFUNC', '123', '', 'rFunc', 'UDF', 'Library!!!', 'SYSDBA', 'masterke'), '0');
INSERT INTO R_TEST_RFUNC VALUES (0, 'Delete_User()', delete_user(4, '', 'RFUNC', 'SYSDBA', 'masterke'), '0');
COMMIT;

/* Simple parser */

INSERT INTO R_TEST_RFUNC VALUES (0, 'Parser functions', '----------------', '----------------');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ExprIsValid(''Sin(Pi*:p11/3)*:P2'', ''P11=2;P2=10'')', exprisvalid('Sin(Pi*:p11/3)*:P2', 'P11=2;P2=10'), '0');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ExprIsValid(''SinFFF(Pi*:p11/3)*:P2'', ''P11=2;P2=10'')', exprisvalid('SinFFF(Pi*:p11/3)*:P2', 'P11=2;P2=10')||' [known bug]', '0 [known bug]');
INSERT INTO R_TEST_RFUNC VALUES (0, 'ExprIsValid(''Sin(Pi*:p11/*3)*:P2'', ''P11=2;P2=10'')', exprisvalid('Sin(Pi*:p11/*3)*:P2', 'P11=2;P2=10'), '3');
INSERT INTO R_TEST_RFUNC VALUES (0, 'CalcExpr(''Sin(Pi*:p11/3)*:P2'', ''P11=2;P2=10'')', calcexpr('Sin(Pi*:p11/3)*:P2', 'P11=2;P2=10'), '8.660254037844387');
INSERT INTO R_TEST_RFUNC VALUES (0, 'CalcExpr(''SinFFF(Pi*:p11/3)*:P2'', ''P11=2;P2=10'')', calcexpr('SinFFF(Pi*:p11/3)*:P2', 'P11=2;P2=10'), '8.660254037844387');
INSERT INTO R_TEST_RFUNC VALUES (0, 'CalcExpr(''Avg(0, :p1, :P2)'', ''P1=2;P2=10'')', calcexpr('Avg(0, :p1, :P2)', 'P1=2;P2=10'), '4.000000000000000');
INSERT INTO R_TEST_RFUNC VALUES (0, 'CalcExpr(''Max(0, :p1, :p2, :p1*:p2)'', ''P1=2;P2=10'')', calcexpr('Max(0, :p1, :p2, :p1*:p2)', 'P1=2;P2=10'), '20.00000000000000');
COMMIT;

/* Blob functions */

INSERT INTO R_TEST_RFUNC VALUES (0, 'BLOB functions', '----------------', '----------------');
EXECUTE PROCEDURE R_RFUNC_TEST_BLOB;
COMMIT;

/* File functions */

INSERT INTO R_TEST_RFUNC VALUES (0, 'File functions', '----------------', '----------------');
EXECUTE PROCEDURE R_RFUNC_TEST_FILE;
COMMIT;

DROP PROCEDURE R_RFUNC_TEST_BLOB;
DROP TRIGGER T_BI_COMMAND;
DROP TRIGGER T_BI_COMMAND2;
DROP PROCEDURE R_RFUNC_TEST_MD5;
DROP PROCEDURE R_RFUNC_TEST_FILE;
DELETE FROM RDB$GENERATORS WHERE RDB$GENERATOR_NAME = 'R_TEST_RFUNC';
COMMIT;


