/** \file  rmath.c
    
    \brief Date&Math functions.

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
   $Revision: 112 $ $Author: coopht $
   $Date: 2009-03-15 17:36:36 +0300 (Вск, 15 Мар 2009) $
 **************************************************************************/
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "rfunc.h"
#include "rmath.h"

double EXPORT fn_abs(ARG(double*, x))
ARGLIST(double *x)
{
	return (*x < 0.0) ? -*x : *x;
}

double EXPORT fn_maxnum(ARG(double*, x), ARG(double*, y))
ARGLIST(double *x)
ARGLIST(double *y)
{
	return (*x > *y) ? *x : *y;
}

double EXPORT fn_minnum(ARG(double*, x), ARG(double*, y))
ARGLIST(double *x)
ARGLIST(double *y)
{
	return (*x < *y) ? *x : *y;
}

double EXPORT fn_ceil(ARG(double*, x))
ARGLIST(double *x)
{
	return ceil(*x);
}

double EXPORT fn_floor(ARG(double*, x))
ARGLIST(double *x)
{
	return floor(*x);
}

double EXPORT fn_power(ARG(double*, x), ARG(double*, y))
ARGLIST(double *x)
ARGLIST(double *y)
{
	return pow(*x,*y);
}

double EXPORT fn_round(ARG(double*, x), ARG(long*, n))
ARGLIST(double *x)
ARGLIST(long *n)
{
	 return ROUND(*x, *n);
}

double EXPORT fn_softround(ARG(double*, x), ARG(long*, n))
ARGLIST(double *x)
ARGLIST(long *n)
{
	 return (*x*pow(10,*n))>=1 ? fn_round(x, n) : *x;
}

long ndiv(ARG(long, q), ARG(long, r))
ARGLIST(long q)
ARGLIST(long r)
{
	div_t x;
	x = div(q, r);
	return x.quot;
}

long EXPORT fn_div(ARG(long*, q), ARG(long*, r))
ARGLIST(long *q)
ARGLIST(long *r)
{
	return ndiv(*q, *r);
}

long nmod(ARG(long, q), ARG(long, r))
ARGLIST(long q)
ARGLIST(long r)
{
	div_t x;
	x = div(q, r);
	return x.rem;
}

long EXPORT fn_mod(ARG(long*, q), ARG(long*, r))
ARGLIST(long *q)
ARGLIST(long *r)
{
	return nmod(*q, *r);
}

double EXPORT fn_z(ARG(double*, a))
ARGLIST(double *a)
{ return *a; }

double EXPORT fn_dividezero(ARG(double*, a), ARG(double*, b), ARG(double*, def))
ARGLIST(double *a)
ARGLIST(double *b)
ARGLIST(double *def)
{ return (*b) ? (*a / *b) : *def; }

long EXPORT fn_initRandom(ARG(long *, num))
ARGLIST(long* num)
{
#if defined WIN32
	randomize();
#else
	srandom(*num);
#endif
	return 1;
}

long EXPORT fn_getRandom(ARG(long *, num))
ARGLIST(long* num)
{
#if defined WIN32
	return random(*num);
#else
	div_t x;
	x = div(random(), *num);
	return x.rem;
#endif
}

long EXPORT fn_getBit(ARG(long *, num), ARG(long *, shift))
ARGLIST(long* num)
ARGLIST(long* shift)
{
	if ((*shift<0) || (*shift>31))
		return -1;
	if(((1<<*shift)&(*num))==0)
		return 0;
	else
		return 1;
}

long EXPORT fn_setBit(ARG(long *, num), ARG(long *, shift), ARG(long *, val))
ARGLIST(long* num)
ARGLIST(long* shift)
ARGLIST(long* val)
{
	if((*shift<0) || (*shift>31) || (*val<0) || (*val>1))
		return *num;
	else
	{
		if(*val==1)
			return (*num) | (1<<*shift);
		else
			return (*num) & (~(1<<*shift));
	}
}

long EXPORT fn_bitAnd(ARG(long *, a), ARG(long *, b))
ARGLIST(long* a)
ARGLIST(long* b)
{
	return (*a & *b);
}

long EXPORT fn_bitOr(ARG(long *, a), ARG(long *, b))
ARGLIST(long* a)
ARGLIST(long* b)
{
	return (*a | *b);
}

long EXPORT fn_bitXor(ARG(long *, a), ARG(long *, b))
ARGLIST(long* a)
ARGLIST(long* b)
{
	return (*a ^ *b);
}

long EXPORT fn_bitNot(ARG(long *, num))
ARGLIST(long* num)
{
	return ~(*num);
}

short EXPORT fn_sign(ARG(double*, d))
ARGLIST(double *d)
{
	int s = SIGN(*d);
	return (short) s;
}

double EXPORT fn_acos(ARG(double*, x))
ARGLIST(double *x)
{ return acos(*x); }

double EXPORT fn_asin(ARG(double*, x))
ARGLIST(double *x)
{ return asin(*x); }

double EXPORT fn_atan(ARG(double*, x))
ARGLIST(double *x)
{ return atan(*x); }

double EXPORT fn_atan2(ARG(double*, y), ARG(double*, x))
ARGLIST(double *y)
ARGLIST(double *x)
{ return atan2(*y, *x); }

double EXPORT fn_cos(ARG(double*, x))
ARGLIST(double *x)
{ return cos(*x); }

double EXPORT fn_cosh(ARG(double*, x))
ARGLIST(double *x)
{ return cosh(*x); }

double EXPORT fn_exp(ARG(double*, x))
ARGLIST(double *x)
{ return exp(*x); }

double EXPORT fn_log(ARG(double*, x), ARG(double*, y))
ARGLIST(double *x)
ARGLIST(double *y)
{ return log(*x) / log(*y); }

double EXPORT fn_ln(ARG(double*, x))
ARGLIST(double *x)
{ return log(*x); }

double EXPORT fn_log10(ARG(double*, x))
ARGLIST(double *x)
{ return log10(*x); }

double EXPORT fn_sin(ARG(double*, x))
ARGLIST(double *x)
{ return sin(*x); }

double EXPORT fn_sinh(ARG(double*, x))
ARGLIST(double *x)
{ return sinh(*x); }

double EXPORT fn_sqrt(ARG(double*, x))
ARGLIST(double *x)
{ return sqrt(*x); }

double EXPORT fn_tan(ARG(double*, x))
ARGLIST(double *x)
{ return tan(*x); }

double EXPORT fn_tanh(ARG(double*, x))
ARGLIST(double *x)
{ return tanh(*x); }

/* Constants rounded for 21 decimals. */
double	EXPORT fn_e (){ return M_E;  }
double	EXPORT fn_pi(){ return M_PI; }

double EXPORT fn_fact (ARG (double*, x))
ARGLIST(double *x)
{
  double i = 2;
  double result = 0;

  if (*x < 0)
    return result;

  result = 1;

  for (i = 2; i <= *x; i++)
    result = result * i;

  return result;
}
