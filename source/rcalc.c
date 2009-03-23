/** \file  rcalc.c
    
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
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "rfunc.h"
#include "rcalc.h"

double Addend(char **S, VariablesStruct *Vars, long *P);
double Multiplier(char **S, VariablesStruct *Vars, long *P);
double Func(char **S, VariablesStruct *Vars, long *P);
double Expr(char **S, VariablesStruct *Vars, long *P);
double Param(char **S, VariablesStruct *Vars, long *P);

double Expr(char **S, VariablesStruct *Vars, long *P)
{
	double Result;
	double r;

	Result = Addend(S, Vars, P);
	if (*P) return 0;
	SKIP_BLANKS(S);
	while ((**S=='+') || (**S=='-'))
	{
		switch (**S)
		{
			case '+':
				(*S)++;
				r = Addend(S, Vars, P);
				if (*P) return 0;
				Result = Result+r;
				break;
			case '-':
				(*S)++;
				r = Addend(S, Vars, P);
				if (*P) return 0;
				Result = Result-r;
				break;
		}
		SKIP_BLANKS(S);
	}

	return Result;
}

double Addend(char **S, VariablesStruct *Vars, long *P)
{
	double Result = Multiplier(S, Vars, P);
	double r;

	if (*P) return 0;
	SKIP_BLANKS(S);
	while ((**S=='*') || (**S=='/'))
	{
		switch (**S)
		{
			case '*':
				(*S)++;
				r = Multiplier(S, Vars, P);
				if (*P) return 0;
				Result = Result*r;
				break;
			case '/':
				(*S)++;
				r = Multiplier(S, Vars, P);
				if (*P) return 0;
				if (!r) { *P = 101; return 0; }
				Result = Result/r;
				break;
		}
		SKIP_BLANKS(S);
	}
	return Result;
}

double Multiplier(char **S, VariablesStruct *Vars, long *P)
{
	double Result;
	char *endptr;

	SKIP_BLANKS(S);
	switch (**S)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			Result = strtod(*S, &endptr);
			*S = endptr;
			break;
		case '-':
			(*S)++;
			Result = -Multiplier(S, Vars, P);
			if (*P) return 0;
			break;
		case '[':
			(*S)++;
			Result = Expr(S, Vars, P);
			if (*P) return 0;
			SKIP_BLANKS(S);
			if (**S!=']') { *P = 1; return 0; }
			Result = (long)Result;
			if (Result<0) Result--;
			(*S)++;
			break;
		case '(':
			(*S)++;
			Result = Expr(S, Vars, P);
			if (*P) return 0;
			SKIP_BLANKS(S);
			if (**S!=')') { *P = 2; return 0; }
			(*S)++;
			break;
		case ':':
			(*S)++;
			Result = Param(S, Vars, P);
			if (*P) return 0;
			break;
		default:
			if (**S>='A' && **S<='Z')
			{
				Result = Func(S, Vars, P);
				if (*P) return 0;
			} else {
				*P = 3;
				return 0;
			}
	}
	return Result;
}

long BoolExpr(char **S, VariablesStruct *Vars, long *P)
{
	double A, B, C;
	long T, T2;

	A = Expr(S, Vars, P);
	if (*P) return 0;
	SKIP_BLANKS(S);
	if (!**S) { *P = 4; return 0; }
	switch (**S)
	{
		case '=':
			if ((*S)[1]=='=') (*S)++;
			T = 1;
			break;
		case '>':
			switch ((*S)[1])
			{
				case '=': T = 2; (*S)++; break;
				case '<': T = 5; (*S)++; break;
				default: T = 3;
			}
			break;
		case '<':
			switch ((*S)[1])
			{
				case '=': T = 4; (*S)++; break;
				case '>': T = 5; (*S)++; break;
				default: T = 6; break;
			}
			break;
		case '!':
			if ((*S)[1] == '=') { T = 5; (*S)++; }
			else { *P = 5; return 0; }
			break;
		default:
			*P = 5;
			return 0;
	}
	(*S)++;
	B = Expr(S, Vars, P);
	SKIP_BLANKS(S);
	if ((**S=='<') && (T==4 || T==6))
	{
		if ((*S)[1]=='=') { (*S)++; T2 = 6; }
		else T2 = 4;
		(*S)++;
		C = Expr(S, Vars, P);
		switch (T+10*T2)
		{
			case 44: if ((A< B) && (B< C)) return 1; break;
			case 46: if ((A<=B) && (B< C)) return 1; break;
			case 64: if ((A< B) && (B<=C)) return 1; break;
			case 66: if ((A<=B) && (B<=C)) return 1; break;
		}
	} else
		switch (T)
		{
			case 1:if (A==B) return 1; break;
			case 2:if (A>=B) return 1; break;
			case 3:if (A> B) return 1; break;
			case 4:if (A<=B) return 1; break;
			case 5:if (A!=B) return 1; break;
			case 6:if (A< B) return 1; break;
		}
	return 0;
}

double Func(char **S, VariablesStruct *Vars, long *P)
{
	double Result;
	char *N;
	long Bl;
	double D, ISN;

	N = *S;
	SKIP_BLANKS(S);
	while (IS_INDENT(*S)) (*S)++;
	SKIP_BLANKS(S);
	if (**S=='(')
	{
		if (!strncmp("IF", N, 2))
		{
			(*S)++;
			Bl = BoolExpr(S, Vars, P);
			if (*P) return 0;
			SKIP_BLANKS(S);
			if (**S!=',') { *P = 6; return 0; }
			(*S)++;
			D = Expr(S, Vars, P);
			if (*P) return 0;
			SKIP_BLANKS(S);
			if (**S!=',') { *P = 6; return 0; }
			(*S)++;
			ISN = Expr(S, Vars, P);
			if (*P) return 0;

			Result = Bl ? D : ISN;
		} else
		{
			(*S)++;
			Result = Expr(S, Vars, P);
			if (*P) return 0;
			if (!strncmp("SIN", N, 3))
				Result = sin(Result);
			else
			if (!strncmp("COS", N, 3))
				Result = cos(Result);
			else
			if (!strncmp("TG", N, 2))
				Result = tan(Result);
			else
			if (!strncmp("CTG", N, 3))
			{
				if (!Result) { *P = 102; return 0; }
				if (!cos(Result))
					Result = 0;
				else
					Result = 1/tan(Result);
			} else
			if (!strncmp("ARCCOS", N, 6))
				Result = acos(Result);
			else
			if (!strncmp("ARCSIN", N, 6))
				Result = asin(Result);
			else
			if (!strncmp("ARCTG", N, 5))
				Result = atan(Result);
			else
			if (!strncmp("EXP", N, 3))
				Result = exp(Result);
			else
			if (!strncmp("LN", N, 2)) {
				if (Result<=0) { *P = 103; return 0; }
				Result = log(Result);
			} else
			if (!strncmp("LG", N, 2)) {
				if (Result<=0) { *P = 103; return 0; }
				Result = log10(Result);
			} else
			if (!strncmp("SQRT", N, 4))
				Result = sqrt(Result);
			else
			if (!strncmp("SQR", N, 3))
				Result = Result*Result;
			else
			if (!strncmp("ABS", N, 3))
				Result = fabs(Result);
			else
			if (!strncmp("SH", N, 2))
				Result = sinh(Result);
			else
			if (!strncmp("CH", N, 2))
				Result = cosh(Result);
			else
			if (!strncmp("TH", N, 2))
				Result = tanh(Result);
			else
			if (!strncmp("SGN", N, 3))
				Result = (Result>0) ? 1 : ((Result<0) ? -1 : 0);
			else
/*
			if (!strncmp("ARSH", N, 4))
				Result = ArcSinh(Result);
			else
			if (!strncmp("ARCH", N, 4))
				Result = ArcCosh(Result);
			else
			if (!strncmp("ARTH", N, 4))
				Result = ArcTanh(Result);
			else
*/
			if (!strncmp("LOG", N, 3))
			{
				SKIP_BLANKS(S);
				if (**S!=',') { *P = 6; return 0; }
				(*S)++;
				D = Expr(S, Vars, P);
				if (*P) return 0;
				if ((D==1) || (D<=0) || (Result<=0)) { *P = 103; return 0; }
				Result = log(Result)/log(D);
			} else
			if (!strncmp("POWER", N, 5))
			{
				SKIP_BLANKS(S);
				if (**S!=',') { *P = 6; return 0; }
				(*S)++;
				D = Expr(S, Vars, P);
				if (*P) return 0;
				if (Result==0)
					Result = 1;
				else
					Result = exp(D*log(Result));
			} else
			if (!strncmp("MAX", N, 3))
			{
				SKIP_BLANKS(S);
				while (**S==',')
				{
					(*S)++;
					D = Expr(S, Vars, P);
					if (*P) return 0;
					if (D>Result) Result = D;
					SKIP_BLANKS(S);
				}
			} else
			if (!strncmp("MIN", N, 3))
			{
				SKIP_BLANKS(S);
				while (**S==',')
				{
					(*S)++;
					D = Expr(S, Vars, P);
					if (*P) return 0;
					if (D<Result) Result = D;
					SKIP_BLANKS(S);
				}
			} else
			if (!strncmp("SUM", N, 3))
			{
				SKIP_BLANKS(S);
				while (**S==',')
				{
					(*S)++;
					D = Expr(S, Vars, P);
					if (*P) return 0;
					Result += D;
					SKIP_BLANKS(S);
				}
			} else
			if (!strncmp("AVG", N, 3))
			{
				SKIP_BLANKS(S);
				Bl = 1;
				while (**S==',')
				{
					(*S)++;
					D = Expr(S, Vars, P);
					if (*P) return 0;
					Result += D;
					Bl++;
					SKIP_BLANKS(S);
				}
				Result = Result/Bl;
			} else
			{
				*P = 7;
				return 0;
			}
		}
		SKIP_BLANKS(S);
		if (**S!=')')
		{
			*P = 8;
			return 0;
		}
		(*S)++;
	} else
	if (!strncmp("PI", N, 2))
		Result = 4*atan(1);
	else
	{
		*P = 7;
		return 0;
	}

	return Result;
}

double Param(char **S, VariablesStruct *Vars, long *P)
{
	double Result;
	char *N = *S;
	long j = 0;
	long n;

	SKIP_BLANKS(S);
	while ((**S>='A' && **S<='Z') || (**S>='0' && **S<='9')) (*S)++;
	n = *S - N;
	while (Vars[j].Length)
	{
		if ((Vars[j].Length == n) && !strncmp(Vars[j].Name, N, Vars[j].Length))
		{
			Result = Vars[j].Value;
			return Result;
		}
		j++;
	}
	if (!Vars[j].Length) *P = 10;
	return 0;
}

VariablesStruct *MakeVars(char *inVar)
{
	long Len = 1, j = 0, k;
	char *ptr = inVar;
	VariablesStruct *Vars;

	if (*ptr) Len++;
	while ((ptr = strchr(ptr, ';'))) { Len++; ptr++; }
	Vars = (VariablesStruct*) malloc (sizeof(VariablesStruct)*Len);
	while (*inVar && (j<Len-1))
	{
		SKIP_BLANKS(&inVar);
		k = 0;
		while ((k < MAXVARLENGTH) && IS_INDENT(inVar)) Vars[j].Name[k++] = (char) toupper(*inVar++);
		while (IS_INDENT(inVar)) inVar++;
		Vars[j].Name[k] = '\0';
		Vars[j].Length = k;
		SKIP_BLANKS(&inVar);
		if (*inVar == '=') inVar++;
		if (*inVar == ';')
			Vars[j].Value = 0;
		else
		{
			Vars[j].Value = strtod(inVar, &ptr);
			inVar = ptr;
		}
		SKIP_BLANKS(&inVar);
		if (*inVar == ';') inVar++;
		j++;
	}
	Vars[j].Name[0] = '\0';
	Vars[j].Value = 0;
	Vars[j].Length = 0;

	return Vars;
}

double EXPORT fn_CalcExpr(ARG(char*, S), ARG(char*, inVar))
ARGLIST(char *S)
ARGLIST(char *inVar)
{
	long P = 0;
	double r;
	VariablesStruct *Vars = MakeVars(inVar);

	char *ptr = S;

	while(*ptr)
	{
		if (isalpha(*ptr))
			*ptr = (char) toupper(*ptr);
		ptr++;
	}

	r = Expr(&S, Vars, &P);
	free(Vars);

	if (P) r = 0;
	return r;
}

long EXPORT fn_ExprIsValid(ARG(char*, S), ARG(char*, inVar))
ARGLIST(char *S)
ARGLIST(char *inVar)
{
	long P = 0;
	VariablesStruct *Vars = MakeVars(inVar);
	char *ptr = S;

	while(*ptr)
	{
		if (isalpha(*ptr))
			*ptr = (char) toupper(*ptr);
		ptr++;
	}

	Expr(&S, Vars, &P);
	free(Vars);

	return P;
}

