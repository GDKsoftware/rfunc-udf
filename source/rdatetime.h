/*====================================================================
		rdatetime.h

		rFunc InterBase UDF library.
		Date&Time functions.

		Copyright 1998-2003 Polaris Software
		http://rfunc.sourceforge.net
		mailto:rFunc@mail.ru

	 This library is free software; you can redistribute it and/or
	 modify it under the terms of the GNU Lesser General Public
	 License as published by the Free Software Foundation; either
	 version 2.1 of the License, or (at your option) any later version.
	 See license.txt for more details.

====================================================================== */

#ifndef _RDATETIME_H
#define _RDATETIME_H

#ifndef isleap
#define isleap(y) (!((y) % 4) && ((y) % 100) || !((y) % 400))
#endif

#if (defined RUSE_DATETIME) || !(defined IB_6X)

long	EXPORT fn_year(ARG(ISC_QUAD*, d));
long	EXPORT fn_month(ARG(ISC_QUAD*, d));
long	EXPORT fn_day(ARG(ISC_QUAD*, d));
long	EXPORT fn_yearday(ARG(ISC_QUAD*, d));
long	EXPORT fn_weekday(ARG(ISC_QUAD*, d));

long	EXPORT fn_hour(ARG(ISC_QUAD*, d));
long	EXPORT fn_minute(ARG(ISC_QUAD*, d));
long	EXPORT fn_second(ARG(ISC_QUAD*, d));

#endif

#if (defined IB_6X)
long EXPORT fn_millisecond(ARG(ISC_QUAD*, d));
#endif

long	EXPORT fn_quarter(ARG(ISC_QUAD*, d));
long	EXPORT fn_isleapyear(ARG(long, *ayear));

/************************* Format strings **************************
%%  Character %
%a  Abbreviated weekday name
%A  Full weekday name
%b  Abbreviated month name
%B  Full month name
%c  Date and time
%d  Two-digit day of month (01 - 31)
%H  Two-digit hour (00 - 23)
%I  Two-digit hour (01 - 12)
%j  Three-digit day of year (001 - 366)
%m  Two-digit month as a decimal number (1 - 12)
%M  2-digit minute (00 - 59)
%p  AM or PM
%S  Two-digit second (00 - 59)
%U  Two-digit week number where Sunday is the first day of the week (00 - 53)
%w  Weekday where 0 is Sunday (0 - 6)
%W  Two-digit week number where Monday is the first day of week the week (00 - 53)
%x  Date
%X  Time
%y  Two-digit year without century (00 to 99)
%Y  Year with century
%Z  Time zone name, or no characters if no time zone
****************************************************/
char*	EXPORT fn_datetostr(ARG(ISC_QUAD*, d), ARG(char*, fmt));

ISC_QUAD*	EXPORT fn_encodedate(ARG(long*, d), ARG(long*, m), ARG(long*, y));
ISC_QUAD*	EXPORT fn_encodedatetime(ARG(long*, d), ARG(long*, m), ARG(long*, y), ARG(long*, hh), ARG(long*, mm), ARG(long*, ss));
ISC_QUAD*	EXPORT fn_extractdate(ARG(ISC_QUAD*, d));
ISC_QUAD*	EXPORT fn_extracttime(ARG(ISC_QUAD*, d));

long	EXPORT fn_dow(ARG(ISC_QUAD*, d));
long	EXPORT fn_daypermonth(ARG(long*, m), ARG(long*, y));

ISC_QUAD*	EXPORT fn_firstdaymonth(ARG(ISC_QUAD*, d));
ISC_QUAD*	EXPORT fn_lastdaymonth(ARG(ISC_QUAD*, d));

long	EXPORT fn_daysbetween(ARG(ISC_QUAD*, bdate), ARG(ISC_QUAD*, edate));
ISC_QUAD*	EXPORT fn_incdate(ARG(ISC_QUAD*, date), ARG(long*, d), ARG(long*, m), ARG(long*, y));
ISC_QUAD*	EXPORT fn_incdatetime(ARG(ISC_QUAD*, date), ARG(long*, days), ARG(long*, months), ARG(long*, years),
	ARG(long*, hours), ARG(long*, mins), ARG(long*, secs));

ISC_QUAD*	EXPORT fn_maxdate(ARG(ISC_QUAD*, dt1), ARG(ISC_QUAD*, dt2));
ISC_QUAD*	EXPORT fn_mindate(ARG(ISC_QUAD*, dt1), ARG(ISC_QUAD*, dt2));

double	EXPORT fn_timetodouble(ARG(ISC_QUAD*, dt));
double	EXPORT fn_datetodouble(ARG(ISC_QUAD*, dt));
ISC_QUAD*	EXPORT fn_doubletodate(ARG(double*, d));
ISC_QUAD*	EXPORT fn_doubletotime(ARG(double*, d));

#endif /* _RDATETIME_H */
