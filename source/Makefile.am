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
#  $Revision: 114 $ $Author: coopht $
#  $Date: 2009-03-15 17:49:11 +0300 (Вск, 15 Мар 2009) $
##########################################################################
include $(top_srcdir)/Makefile.common

SUBDIRS = .

SRC= \
	myfunc.c \
	rblob.c \
	rcalc.c \
	rdatetime.c \
	rfunc.c \
	rmath.c \
	rmd5c.c \
	rmisc.c \
	rsecurity.c \
	rstring.c \
	win1251.c

HDRS=\
	rblob.h \
	rcalc.h \
	rdatetime.h \
	rfile.h \
	rmath.h \
	rmd5.h \
	rmisc.h \
	rsecurity.h \
	rstring.h \
	win1251.h

if R_USE_FILE
    SRC+= rfile.c
    HDRS+= rfunc.h
endif

lib_LTLIBRARIES = librfunc.la

librfunc_la_SOURCES = $(HDRS) $(SRC)
librfunc_la_CFLAGS = $(CFLAGS) $(FB_CFLAGS) $(RFUNC_DEFS)
librfunc_la_LIBADD = $(FB_LDFLAGS)
