====================================================================
      File readmeeng.txt

      rFunc UDF Library for InterBase.
      Description.

      Copyright 1998-2001 Polaris Software
      http://polesoft.da.ru
      mailto: rFunc@mail.ru

      Version 2.0.1.2
====================================================================

Maximize window and turn mode your program to Word wrap for best 
viewing this document.

CONTENTS

1. The brief description
2. Compilation
3. Installing the library
4. Distribution
5. List of files
6. Gratitude

----------------------------------------------

1. The Brief Description
------------------------

The rFunc functions library (further - library) is intended for the extension of possibilities a DBMS InterBase. Includes in itself more 90 string, numerical, bit functions, operation with dates, BLOBами, users etc. functions.
Also library contains parser (calculator of expressions), which allows to execute numerical expressions given as string, with transmission of parameters. It is possible to calculate and trigonometrical functions. 

List of functions:
  > Numeric: Abs Ceil Floor MaxNum MinNum Power Round SoftRound Z IIf DIf DZero Div Mod InitRandom GetRandom
  > Parser: CalcExpr ExprIsValid
  > String: Chr Ord StrReplace StrStuff LTrim RTrim StrLen StrPos StrRepeat SubStr Trim CIf StrCount WordCount WordNum RLower RUpper PadLeft PadRight RLatin RTranslit
  > Date&Time: DateToStr DayPerMonth Dow EncodeDate EncodeDateTime ExtractDate Day Month Year Hour Minute Second WeekDay YearDay Quarter FirstDayMonth LastDayMonth IsLeapYear DaysBetween DtIf IncDate
  > BLOB: B_Line B_Line_Count B_Max_Segment B_Number_Segments B_Put_Segment B_SubStr B_Total_Length
  > Bit: BitAnd BitNot BitOr BitXor GetBit SetBit
  > Users: Add_User Modify_User Delete_User (only for IB 5.x and later)
  > Other: MsgBox (only Windows)

The returned strings in string functions have maximum length of 255 characters. For return of long strings use functions with the prefix Long (length up to 16K).
Full the description of functions is reduced in a directory doc.

The library is written on C ++, is delivered with the completely open source code (directory source). It allows to compile it on any platform supported Interbase.

In a directory sql the set of scripts for creating, droping and testing of functions in your database is delivered. Scripts for deleting and the testings are not divided for different versions IB. Errors of their execution are accepted.

Supported platforms:
  for Windows: IB Borland 4.2, 5.x, 6.0, Firebird 0.9,
    for Linux: IB Borland      5.x, 6.0, Firebird 0.9.

Remark: Further in the text IB6 will mean IB Borland 6.0 or Firebird 0.9.

2. Compilation
--------------

For convenience of compilation the make-files with names makefileN.win and makefileN.linux (N - version IB) for Windows and Linux accordingly are included in archive.

For Windows:

1. Install one of compilers Borland C++.
2. Extract files from archive with the library in any folder.
3. Open the source folder.
4. Edit make-file makefileN.win: path of IB (IBASE parameter), С++ (BCDIR parameter), Windows system dir (SYSDIR parameter).
5. Run following command
     <BC++ folder>\bin\make -f makefileN.win all

The compilation was tested with Free Borland C++ Compiler 5.5 on Windows 2000 Pro SP1.

For Linux:

1. Extract files from archive with the library by mc program or commands
     gzip -d rfunc.tar.gz
     tar xvf rfunc.tar
2. Open the source directory.
3. Edit make-file makefileN.linux: path by IB (IBASE parameter).
4. Run following command
     make -f makefileN.linux rfunc

The compilation was tested on RH 6.2 kernel 2.2.14, Mandrake 8.0 kernel 2.4.4.

For FreeBSD:

The compilation by the developers was not tested, but, by recalls, special problems does not cause.


3. Installing the library
-------------------------

With the distribution kit the compilated rFunc library only for IB6 is delivered. For other versions IB it is necessary independently скомпилировать it or, by becoming the registered user, to receive it from us.

For Windows:

1. The RFUNC.DLL file is necessary for copying in a folder
   variant 1: <IB path>\Bin (for IB6 - <IB path>\UDF), where <IB path> is path to a folder, in which Interbase is installed (is recommended).
   variant 2: Windows\System (for Windows 9x) or WinNT\System32 (Windows NT, 2k).
2. only for IB 5.x: copy ib_util.dll file from <IB path>\Lib to <IB path>\Bin.

If on one computer some versions of servers Interbase are installed, it is necessary to use the rFunc library, appropriate to the installed client IB (GDS32.DLL).
It is recommended before start of the Interbase server to substitute GDS32.DLL on appropriate to the version of the server.

For Linux:

IB 5.x
variant 1: Copy the rfunc file into directory /usr/lib.
variant 2: Copy the rfunc file into any directory, for example, /home/rFunc. Create the reference on the library by "ln -s /home/rFunc/rfunc /usr/lib/rfunc" command. User should have the right to creation of the references in a directory /usr/lib.

IB6
Copy the rfunc file into directory <IB directory>\UDF.


4. Distribution
---------------

All problems connected to use and distribution of the library, are regulated GNU Lesser General Public License.
The text of the license is in the license.txt file.

The library is a FREEWARE product and the technical support by us is not guaranteed.
There is a possibility UNESSENTIAL paid (10 $) registration. It for those who wants to receive technical support, to have the right to prime reviewing of your problems and inclusion in the library of required functions.


5. List of files
----------------

Folder/Files             Description
------------------------------------------------------------
bin/                     compiled library
rfunc.dll                for IB6 (Windows)
rfunc                    for IB6 (Linux)

doc/                     description
*.html                   functions description page (from our website)
*eng.html                functions description page (from our english website)
*.gif, polesoft.css      images and style sheet for html
rfunc.txt                functions description (win1251)
rfunceng.txt             functions description (english)
rfunc.linux              functions description (koi8)

source/                  sources
makefile*.*              make-files for compilation for various versions IB and for Windows and Linux
rblob.*                  functions of operation with BLOB
rcalc.*                  parser
rdatetime.*              functions of operation with dates
rfunc.h                  header-file for rfunc
rfunc*.rc                resource file with VersionInfo for various versions IB (only for Windows)
rmath.*                  math functions
rmisc.*                  other functions 
rsecurity.*              functions of operation with the users
rstring.*                string functions
win1251.h                arrays of characters for functions rUpper, rLower, rLatin, rTranslit

sql/                     scripts
rdrop.sql                deleting of functions from the database
rfunc*.sql               creating of functions in the database for various versions IB
rtest.sql                testing of functions

changes.txt              changes history (win1251)
changeseng.txt           changes history (english)
changes.linux            changes history (koi8)
license.txt              license (english)
readme.txt               description (win1251)
readmeeng.txt            description (english)
readme.linux             description (koi8)


6. Gratitude
------------

Khazatsky Alexander,
Software developer
Storm International CS B.V.

----------------------------------------------

24.07.2001

Best regards,
Polaris Software, Russia, Krasnodar

Thank for interest to our products.