/** \file  rcalc.h
    
    \brief Simple parser.

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
   $Revision: 112 $ $Author: coopht $
   $Date: 2009-03-15 17:36:36 +0300 (Вск, 15 Мар 2009) $
 **************************************************************************/
#ifndef _RCALC_H
#define _RCALC_H

#define IS_INDENT(v)    ((*v>='A' && *v<='Z') || (*v>='a' && *v<='z') || (*v>='0' && *v<='9'))
#define SKIP_BLANKS(v)  if(*v) while (strchr(" \n\t", **v)) (*v)++;

#define MAXVARLENGTH	33
typedef struct {
	char Name[MAXVARLENGTH];
	long Length;
	double Value;
} VariablesStruct;

double EXPORT fn_CalcExpr(ARG(char*, S), ARG(char*, inVar));
long EXPORT fn_ExprIsValid(ARG(char*, S), ARG(char*, inVar));

#endif /* _RCALC_H */
