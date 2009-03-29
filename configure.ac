##########################################################################
#
#                rfunc UDF library
#
##########################################################################
#
#  <Copyright>
#      Copyright 2009 PoleSoft Technologies Group
#      http://www.polesoft.ru/project/rfunc
#      mailto:support@polesoft.ru
#
#      This library is free software; you can redistribute it and/or
#      modify it under the terms of the GNU Lesser General Public
#      License as published by the Free Software Foundation; either
#      version 2.1 of the License, or (at your option) any later version.
#      See license.txt for more details.
#
#  <Unit> configure.ac
#    <Purpose>
#    <Effects>
#    <Perfomance>
##########################################################################
#  $Revision$ $Author$
#  $Date$
##########################################################################
AC_PREREQ(2.57)
AC_INIT(rfunc,2.2.0.1)
AM_MAINTAINER_MODE

if test "$USE_MAINTAINER_MODE" = "yes" ; then
   # Проверка того, что каталог сборки отличается от каталога
   # исходных текстов.
   if test "`cd ${srcdir} && pwd`" = "`cd . && pwd`" ; then
       AC_MSG_ERROR([Building in the source directory not supported in maintainer mode.])
    fi
fi

AM_INIT_AUTOMAKE([foreign 1.10])
AC_ENABLE_SHARED(yes)
AC_ENABLE_STATIC(no)
AC_PROG_CXX
AC_PROG_LIBTOOL

AC_SUBST(SED)

AC_FBA_CHECK

USE_RFUNC_ARGS

# generating output files
AC_CONFIG_FILES([
	Makefile
	doc/Makefile
	doc/img/Makefile
	doc/rus/Makefile
	source/Makefile
	sql/Makefile
])

if test "$USE_MAINTAINER_MODE" = "yes" ; then
  AC_CONFIG_FILES([
	testsuite/Makefile
	testsuite/testutils/Makefile
	testsuite/rblob/Makefile
	testsuite/rdatetime/Makefile
	testsuite/rstring/Makefile
	testsuite/rmath/Makefile
])
fi
AC_OUTPUT
