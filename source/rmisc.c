/** \file  rmisc.c
    
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
#include <stdlib.h>
#include <stdio.h>
#include "rfunc.h"
#include "rmisc.h"
#include <string.h>
#if defined WIN32
#include <windows.h>
#include <winuser.h>
#else
#if defined RUSE_GUID
#include <uuid/uuid.h>
#endif	/* RUSE_GUID */
#endif

long	EXPORT fn_iif(ARG(long*, a), ARG(long*, b), ARG(long*, c))
ARGLIST(long *a)
ARGLIST(long *b)
ARGLIST(long *c)
{ return (*a) ? *b : *c; }

double	EXPORT fn_dif(ARG(long*, a), ARG(double*, b), ARG(double*, c))
ARGLIST(long *a)
ARGLIST(double *b)
ARGLIST(double *c)
{ return (*a) ? *b : *c; }

char*	EXPORT fn_cif(ARG(long*, a), ARG(char*, b), ARG(char*, c))
ARGLIST(long *a)
ARGLIST(char *b)
ARGLIST(char *c)
{ return (*a) ?  b :  c; }

ISC_QUAD* EXPORT fn_dtif(ARG(long*, a), ARG(ISC_QUAD*, b), ARG(ISC_QUAD*, c))
ARGLIST(long *a)
ARGLIST(ISC_QUAD *b)
ARGLIST(ISC_QUAD *c)
{
	if (*a)
		return b;
	else
		return c;
}


long	EXPORT fn_iequal(ARG(long*, i1), ARG(long*, i2))
ARGLIST(long *i1)
ARGLIST(long *i2)
{ return (*i1 == *i2) ? 1 : 0; }

/* ???dEqual(d1, d2) */
/* ???long	EXPORT fn_dequal(ARG(double*, d1), ARG(double*, d2)) */
/* ???ARGLIST(double *d1) */
/* ???ARGLIST(double *d2) */
/* ???{ return (*d1 == *d2) ? 1 : 0; } */

long	EXPORT fn_cequal(ARG(char*, str1), ARG(char*, str2))
ARGLIST(char *str1)
ARGLIST(char *str2)
{ return (strcmp(str1, str2)) ? 0 : 1; }

long	EXPORT fn_dtequal(ARG(ISC_QUAD*, dt1), ARG(ISC_QUAD*, dt2))
ARGLIST(ISC_QUAD *dt1)
ARGLIST(ISC_QUAD *dt2)
{ return (dt1->gds_quad_high == dt2->gds_quad_high) && (dt1->gds_quad_low == dt2->gds_quad_low) ? 1 : 0; }


#if defined WIN32
long	EXPORT fn_msgbox(ARG(char*, lpText), ARG(char*, lpCaption), ARG(long*, Flags))
ARGLIST(char *lpText)
ARGLIST(char *lpCaption)
ARGLIST(long *Flags)
{ return MessageBoxA(NULL, lpText, lpCaption, *Flags); }
#endif

short EXPORT fn_ean13cs(ARG(char*, s))
ARGLIST(char *s)
{
	long i = strlen(s);
	long c = 0, a;

	if (i != 12 || atoi(s) == 0) return -1;
	for ( i=0; i<12; i++ )
	{
		a = ((short) s[i]) - 48;
		if (a < 0 || a > 9) return -1;
		c = c + (i%2 ? 3 : 1)*a;
	}
	c = (10 - c % 10) % 10;
	return (short) c;
}

short EXPORT fn_bccheckdigit(ARG(char*, s))
ARGLIST(char *s)
{
	long i = strlen(s);
	long c = 0, a, j;

	for (j = 0; j < i; j++ )
	{
		a = ((short) s[i-j-1]) - 48;
		if (a < 0 || a > 9) return -1;
		c = c + (j%2 ? 1 : 3)*a;
	}
	c = (10 - c % 10) % 10;
	return (short) c;
}

#if defined RUSE_GUID
char*	EXPORT fn_CreateGUID()
{
	RGUID	pguid;
	char	*sguid = (char *) MALLOC (SGUID_LEN);
#if !defined(WIN32)
	uuid_t  uu;
#endif

#if defined WIN32
	CoCreateGuid((GUID *) &pguid);

#else
	uuid_generate_time(uu);
	memcpy(&pguid, uu, sizeof(uu));
#endif /* WIN32 */

	sprintf(sguid,
#if defined RGUID_WIN_STYLE
		"{%.8X-%.4X-%.4X-%.2X%.2X-%.2X%.2X%.2X%.2X%.2X%.2X}",
#else
		"%.8lx-%.4x-%.4x-%.2x%.2x-%.2x%.2x%.2x%.2x%.2x%.2x",
#endif /* RGUID_WIN_STYLE */
		pguid.D1, pguid.D2, pguid.D3, pguid.D4[0], pguid.D4[1], pguid.D4[2], pguid.D4[3],
    	pguid.D4[4], pguid.D4[5], pguid.D4[6], pguid.D4[7]);

	return sguid;
}
#endif	/* RUSE_GUID */
