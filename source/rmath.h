/** \file  rmath.h
    
    \brief Math functions.

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
#ifndef _RMATH_H
#define _RMATH_H

#define SIGN(x)	x ? (x > 0 ? 1: -1) : 0;
#define ROUND(x, n) x>=0 ? floor((x*pow(10,n)+0.500000001))*pow(10,n*(-1)) : ceil((x*pow(10,n)-0.500000001))*pow(10,n*(-1));

double EXPORT fn_abs(ARG(double*, x));
double EXPORT fn_maxnum(ARG(double*, x), ARG(double*, y));
double EXPORT fn_minnum(ARG(double*, x), ARG(double*, y));

double EXPORT fn_ceil(ARG(double*, x));
double EXPORT fn_floor(ARG(double*, x));
double EXPORT fn_power(ARG(double*, x), ARG(double*, y));

double EXPORT fn_round(ARG(double*, x), ARG(long*, n));
double EXPORT fn_softround(ARG(double*, x), ARG(long*, n));

long ndiv(ARG(long, q), ARG(long, r));
long nmod(ARG(long, q), ARG(long, r));
long EXPORT fn_div(ARG(long*, q), ARG(long*, r));
long EXPORT fn_mod(ARG(long*, q), ARG(long*, r));

double EXPORT fn_z(ARG(double*, a));
double EXPORT fn_dividezero(ARG(double*, a), ARG(double*, b), ARG(double*, def));

long EXPORT fn_initRandom(ARG(long *, num));
long EXPORT fn_getRandom(ARG(long *, num));

long EXPORT fn_getBit(ARG(long *, num), ARG(long *, shift));
long EXPORT fn_setBit(ARG(long *, num), ARG(long *, shift), ARG(long *, val));
long EXPORT fn_bitAnd(ARG(long *, a), ARG(long *, b));
long EXPORT fn_bitOr(ARG(long *, a), ARG(long *, b));
long EXPORT fn_bitXor(ARG(long *, a), ARG(long *, b));
long EXPORT fn_bitNot(ARG(long *, num));

short EXPORT fn_sign(ARG(double*, d));

double EXPORT fn_acos(ARG(double*, x));
double EXPORT fn_asin(ARG(double*, x));
double EXPORT fn_atan(ARG(double*, x));
double EXPORT fn_atan2(ARG(double*, y), ARG(double*, x));
/* Функция  atan2() вычисляет арктангенс двух переменных: x и */
/* y.   Это  похоже  на  вычисление  арктангенса  y  /  x  за */
/* сключением  того,  что знак обоих аргументов используется */
/* для определения квадранта результата. */

/* ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ */
/* Функция  atan2()   возвращает   результат   вычисления   в */
/* радианах,  который  находится  в  диапазоне  от  -Пи до Пи */
/* включительно. */
double EXPORT fn_cos(ARG(double*, x));
double EXPORT fn_cosh(ARG(double*, x));
double EXPORT fn_exp(ARG(double*, x));
/* Функция exp() возвращает  значение  числа  'e'  (основание */
/* натурального логарифма), возведенного в степень x. */
double EXPORT fn_log(ARG(double*, x), ARG(double*, y));
/* Функция log() возвращает логарифм x по основанию y. */
double EXPORT fn_ln(ARG(double*, x));
/* Функция ln() возвращает натуральный логарифм x. */
double EXPORT fn_log10(ARG(double*, x));
/* Функция log10() возвращает десятичный логарифм x. */
double EXPORT fn_sin(ARG(double*, x));
double EXPORT fn_sinh(ARG(double*, x));
double EXPORT fn_sqrt(ARG(double*, x));
double EXPORT fn_tan(ARG(double*, x));
double EXPORT fn_tanh(ARG(double*, x));

/* Constants rounded for 21 decimals. */
double	EXPORT fn_e ();
double	EXPORT fn_pi();

double EXPORT fn_fact (ARG(double*, x));

#endif /* _RMATH_H */
