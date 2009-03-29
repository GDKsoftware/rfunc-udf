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
#  <Unit> Makefile.am
#    <Purpose>
#    <Effects>
#    <Perfomance>
##########################################################################
#  $Revision$ $Author$
#  $Date$
##########################################################################
include $(top_srcdir)/Makefile.common

SUBDIRS = .

TESTS= rdatetime_test

check_PROGRAMS=	rdatetime_test

rdatetime_test_SOURCES = rdatetime_test.c
rdatetime_test_CFLAGS = $(CFLAGS) $(FB_CFLAGS) -I$(top_srcdir)/testsuite/testutils/
rdatetime_test_LDADD = $(FB_LDFLAGS) $(top_builddir)/testsuite/testutils/librtutils.la

