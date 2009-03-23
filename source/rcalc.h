/*====================================================================
		rcalc.h

		rFunc InterBase UDF library.
		Simple parser.

		Copyright 1998-2003 Polaris Software
		http://rfunc.sourceforge.net
		mailto: rFunc@mail.ru

	 This library is free software; you can redistribute it and/or
	 modify it under the terms of the GNU Lesser General Public
	 License as published by the Free Software Foundation; either
	 version 2.1 of the License, or (at your option) any later version.
	 See license.txt for more details.

====================================================================== */

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