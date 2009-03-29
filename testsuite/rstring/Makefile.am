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

TESTS= rstring_test

check_PROGRAMS=	rstring_test

rstring_test_SOURCES = rstring_test.c
rstring_test_CFLAGS = $(CFLAGS) $(FB_CFLAGS) -I$(top_srcdir)/testsuite/testutils/
rstring_test_LDADD = $(FB_LDFLAGS) $(top_builddir)/testsuite/testutils/librtutils.la

