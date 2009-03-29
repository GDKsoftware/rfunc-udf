/** \file  misc.h
    
    \brief Miscellaneous functions.

 **************************************************************************
 *                                                                        *
 *                  rfunc InterBase UDF library                           *
 *                                                                        *
 **************************************************************************
    \Copyright
      Copyright 2009 PoleSoft Technologies Group
      http://www.polesoft.ru/project/rfunc
      mailto:support@polesoft.ru

      This library is free software; you can redistribute it and/or
      modify it under the terms of the GNU Lesser General Public
      License as published by the Free Software Foundation; either
      version 2.1 of the License, or (at your option) any later version.
      See license.txt for more details.
      
 **************************************************************************
 Last Changes:
   $Revision$ $Author$
   $Date$
 **************************************************************************/
#ifndef _RMISC_H
#define _RMISC_H

#include "rfunc.h"

long	EXPORT fn_iif(ARG(long*, a), ARG(long*, b), ARG(long*, c));
double	EXPORT fn_dif(ARG(long*, a), ARG(double*, b), ARG(double*, c));
char* EXPORT fn_cif(ARG(long*, a), ARG(char*, b), ARG(char*, c));
ISC_QUAD*	EXPORT fn_dtif(ARG(long*, a), ARG(ISC_QUAD*, b), ARG(ISC_QUAD*, c));

long	EXPORT fn_iequal(ARG(long*, i1), ARG(long*, i2));
/*FIXME: ???long	EXPORT fn_dequal(ARG(double*, d1), ARG(double*, d2)); */
long	EXPORT fn_cequal(ARG(char*, str1), ARG(char*, str2));
long	EXPORT fn_dtequal(ARG(ISC_QUAD*, dt1), ARG(ISC_QUAD*, dt2));

#if defined WIN32
long	EXPORT fn_msgbox(ARG(char*, lpText), ARG(char*, lpCaption), ARG(long*, Flags));
#endif

short EXPORT fn_ean13cs(ARG(char*, s));
short EXPORT fn_bccheckdigit(ARG(char*, s));

#if defined RUSE_GUID
#define	SGUID_LEN	39
typedef struct _RGUID
{
    unsigned long D1;
    unsigned short D2;
    unsigned short D3;
    unsigned char D4[8];
} RGUID;

char*	EXPORT fn_CreateGUID();
#endif	/* RUSE_GUID */

#endif /* _RMISC_H */
