/** \file  win1251.h
    
    \brief Russian WIN1251 upper & lower case character sets.

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
/*
	 If you want use rUpper & rLower functions
	 override this line with your character set.
 */

#ifndef _WIN1251_H
#define _WIN1251_H

#if defined(RLOCALE)
#include <ctype.h>
#include <locale.h>
#endif /* RLOCALE */

extern unsigned char upper_win1251[];
extern unsigned char lower_win1251[];

unsigned char*	EXPORT fn_rupper(ARG(unsigned char*, s));
unsigned char*	EXPORT fn_rlower(ARG(unsigned char*, s));
unsigned char*	EXPORT fn_rlatin(ARG(unsigned char*, s));
unsigned char*	EXPORT fn_rtranslit(ARG(unsigned char*, s));
unsigned char*	EXPORT fn_longrtranslit(ARG(unsigned char*, s));

char* EXPORT fn_numinwords(ARG(long*, Sum), ARG(char*, sGender));

#endif /* _WIN1251_H */
