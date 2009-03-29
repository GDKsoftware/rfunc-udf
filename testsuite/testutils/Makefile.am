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

SRC= rt_util.c
HDRS= rt_util.h

lib_LTLIBRARIES = librtutils.la

librtutils_la_SOURCES = $(HDRS) $(SRC)
librtutils_la_CFLAGS = $(CFLAGS) $(FB_CFLAGS)
librtutils_la_LIBADD = $(FB_LDFLAGS)
