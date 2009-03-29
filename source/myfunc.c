/** \file  myfunc.c
    
    \brief Extended functions.

 **************************************************************************
 *                                                                        *
 *                          rfunc UDF library                             *
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
#include "rfunc.h"
#include <stdio.h>
#include <ctype.h>

long EXPORT fn_num_extr(ARG(char*, s))
ARGLIST(char *s)
{
	char *c = s;
	long res = 0;

	while(*c && !isdigit(*c)) c++;
	sscanf(c, "%ld", &res);

	return res;
}
