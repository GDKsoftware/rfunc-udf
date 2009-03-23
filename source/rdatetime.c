/*====================================================================
		rdatetime.c

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

#include <ibase.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "rfunc.h"
#include "rdatetime.h"
#include "rmath.h"
#include "win1251.h"

const double msec_in_day = 24. * 60. * 60. * ISC_TIME_SECONDS_PRECISION;

#if (defined RUSE_DATETIME) || !(defined IB_6X)

long EXPORT fn_year(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	struct tm tm1;
	isc_decode_date(d, &tm1);
	return (tm1.tm_year + IB_START_YEAR);
}

long EXPORT fn_month(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	struct tm tm1;
	isc_decode_date(d, &tm1);
	return (tm1.tm_mon + 1);
}

long EXPORT fn_day(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	struct tm tm1;
	isc_decode_date(d, &tm1);
	return tm1.tm_mday;
}

long EXPORT fn_yearday(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	struct tm tm1;
	isc_decode_date(d, &tm1);
	return tm1.tm_yday;
}

long EXPORT fn_weekday(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	struct tm tm1;
	isc_decode_date(d, &tm1);
	return tm1.tm_wday;
}

long EXPORT fn_hour(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	struct tm tm1;
	isc_decode_date(d, &tm1);
	return tm1.tm_hour;
}

long EXPORT fn_minute(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	struct tm tm1;
	isc_decode_date(d, &tm1);
	return tm1.tm_min;
}

long EXPORT fn_second(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	struct tm tm1;
	isc_decode_date(d, &tm1);
	return tm1.tm_sec;
}

#endif

#if (defined IB_6X)
long EXPORT fn_millisecond(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	div_t x;
	x = div(d->gds_quad_low, ISC_TIME_SECONDS_PRECISION);
	return x.rem;
}
#endif

long EXPORT fn_quarter(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	struct tm tm1;
	div_t x;

	isc_decode_date(d, &tm1);
	x = div(tm1.tm_mon, 3);
	return x.quot+1;
}

long	EXPORT fn_isleapyear(ARG(long, *ayear))
ARGLIST(long* ayear)
{
	return (long) isleap(*ayear);
}

char* EXPORT fn_datetostr(ARG(ISC_QUAD*, d), ARG(char*, fmt))
ARGLIST(ISC_QUAD *d)
ARGLIST(char *fmt)
{
	char *buffer = (char *) MALLOC (shortlen);
	struct tm tm1;
	isc_decode_date(d, &tm1);
#if defined(RLOCALE)
	setlocale(LC_ALL, "");
#endif
	if (!strftime(buffer, shortlen - 1, fmt, &tm1)) buffer[0] = '\0';
	return buffer;
}

ISC_QUAD* EXPORT fn_encodedate(ARG(long*, d), ARG(long*, m), ARG(long*, y))
ARGLIST(long *d)
ARGLIST(long *m)
ARGLIST(long *y)
{
	ISC_QUAD *bufquad = (ISC_QUAD *) MALLOC (sizeof(ISC_QUAD));
	struct tm tm1;
	tm1.tm_sec = 0;
	tm1.tm_min = 0;
	tm1.tm_hour = 0;
	tm1.tm_year = *y - IB_START_YEAR;
	tm1.tm_mon = *m - 1;
	tm1.tm_mday = *d;
	isc_encode_date(&tm1, bufquad);
	return bufquad;
}

ISC_QUAD* EXPORT fn_encodedatetime(ARG(long*, d), ARG(long*, m), ARG(long*, y), ARG(long*, hh), ARG(long*, mm), ARG(long*, ss))
ARGLIST(long *d)
ARGLIST(long *m)
ARGLIST(long *y)
ARGLIST(long *hh)
ARGLIST(long *mm)
ARGLIST(long *ss)
{
	ISC_QUAD *bufquad = (ISC_QUAD *) MALLOC (sizeof(ISC_QUAD));
	struct tm tm1;
	tm1.tm_sec = *ss;
	tm1.tm_min = *mm;
	tm1.tm_hour = *hh;
	tm1.tm_year = *y - IB_START_YEAR;
	tm1.tm_mon = *m - 1;
	tm1.tm_mday = *d;
	isc_encode_date(&tm1, bufquad);
	return bufquad;
}

ISC_QUAD* EXPORT fn_extractdate(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	d->gds_quad_low = 0;
	return d;
}

ISC_QUAD*	EXPORT fn_extracttime(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	d->gds_quad_high = 0;
	return d;
}

long	EXPORT fn_dow(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	struct tm tm1;
	isc_decode_date(d, &tm1);
	return tm1.tm_wday==0 ? 7 : tm1.tm_wday;
}

long	EXPORT fn_daypermonth(ARG(long*, m), ARG(long*, y))
ARGLIST(long *m)
ARGLIST(long *y)
{
	short daysinmonth[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if ((*m < 1 ) || (*m > 12)) return 0;
	return ((*m==2) && isleap(*y))
				 ? daysinmonth[*m-1]+1 : daysinmonth[*m-1] ;
}

ISC_QUAD*	EXPORT fn_firstdaymonth(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	struct tm tm1;

	isc_decode_date(d, &tm1);
	tm1.tm_hour = 0;
	tm1.tm_min = 0;
	tm1.tm_sec = 0;
	tm1.tm_mday = 1;
	isc_encode_date(&tm1, d);

	return d;
}

ISC_QUAD*	EXPORT fn_lastdaymonth(ARG(ISC_QUAD*, d))
ARGLIST(ISC_QUAD *d)
{
	struct tm tm1;

	isc_decode_date(d, &tm1);
	tm1.tm_hour = 0;
	tm1.tm_min = 0;
	tm1.tm_sec = 0;
	tm1.tm_mon++;
	tm1.tm_mday = 0;
	isc_encode_date(&tm1, d);

	return d;
}

long	EXPORT fn_daysbetween(ARG(ISC_QUAD*, bdate), ARG(ISC_QUAD*, edate))
ARGLIST(ISC_QUAD *bdate)
ARGLIST(ISC_QUAD *edate)
{
	return edate->gds_quad_high - bdate->gds_quad_high;
}

struct tm * _incdate(struct tm* tm1, long d, long m, long y)
{
	div_t x;
	long dd, mm, yy, dsign, dpm;

	dd = tm1->tm_mday;
	mm = tm1->tm_mon + 1;
	yy = tm1->tm_year += IB_START_YEAR;

	dpm = fn_daypermonth(&mm, &yy) - dd;
	// ГОД
	yy += y;

	// МЕСЯЦ
	// Прибавляем или вычитаем года
	dsign = (mm + m < 1) ? -1 : 1;

	x = div(dsign * (mm + m - 1), 12);

	yy = yy + dsign * x.quot;

	if (dsign+1)
		mm = x.rem + 1;
	else
	{
		yy = yy - 1;
		mm = 12 - x.rem + 1;
	}

	// ДЕНЬ
	// Если день был последним днем в месяце - он должен и остаться последним
	// днем после изменения года и месяца.
	if (!dpm)
		dd = fn_daypermonth(&mm, &yy);
	else
		dd = tm1->tm_mday;
	// Если дата вываливается за конец месяца после изменения года и месяца -
	// ставим последнее число месяца.
	dd = (dd > fn_daypermonth(&mm, &yy)) ? fn_daypermonth(&mm, &yy) : dd;

	// Прибавить дни или вычесть?
	dd += d;
	dsign = (dd < 0) ? 0 : 1;
	// З.Ы. Было бы неплохо сразу проверять на 365 дней, чтобы проскакивать год
	// при необходимости
	if (dsign==1)
	{
		while ((dpm = fn_daypermonth(&mm, &yy)) < dd)
		{
			dd -= dpm;
			if (++mm > 12)
			{
				yy++;
				mm = 1;
			}
		}
	}
	else
	{
		while (dd <= 0)
		{
			if (!--mm)
			{
				yy--;
				mm = 12;
			}
			dd += dpm = fn_daypermonth(&mm, &yy);
		}
	}

	tm1->tm_mday = dd;
	tm1->tm_mon = mm - 1;
	tm1->tm_year = yy - IB_START_YEAR;

	return tm1;
}

ISC_QUAD*	EXPORT fn_incdate(ARG(ISC_QUAD*, dt), ARG(long*, d), ARG(long*, m), ARG(long*, y))
ARGLIST(ISC_QUAD *dt)
ARGLIST(long *d)
ARGLIST(long *m)
ARGLIST(long *y)
{
	struct tm tm1;

	isc_decode_date(dt, &tm1);

	_incdate(&tm1, *d, *m, *y);

	isc_encode_date(&tm1, dt);

	return dt;
}

ISC_QUAD*	EXPORT fn_incdatetime(ARG(ISC_QUAD*, dt), ARG(long*, days), ARG(long*, months), ARG(long*, years),
	ARG(long*, hours), ARG(long*, mins), ARG(long*, secs))
ARGLIST(ISC_QUAD *dt)
ARGLIST(long *days)
ARGLIST(long *months)
ARGLIST(long *years)
ARGLIST(long *hours)
ARGLIST(long *mins)
ARGLIST(long *secs)
{
	div_t x;
	struct tm tm1;
	long dd;

	isc_decode_date(dt, &tm1);

	_incdate(&tm1, *days, *months, *years);

	tm1.tm_hour += *hours;
	tm1.tm_min += *mins;
	tm1.tm_sec += *secs;
// Высчитаем количество прибавляемых дней.
	// Прибавляем или вычитаем секунды
	x = div(tm1.tm_sec, 60);
	if (x.rem < 0)
	{
		tm1.tm_min += x.quot - 1;
		tm1.tm_sec = 60 + x.rem;
	}
	else
	{
		tm1.tm_min += x.quot;
		tm1.tm_sec = x.rem;
	}
// минуты в часы
	x = div(tm1.tm_min, 60);
	if (x.rem < 0)
	{
		tm1.tm_hour += x.quot - 1;
		tm1.tm_min = 60 + x.rem;
	}
	else
	{
		tm1.tm_hour += x.quot;
		tm1.tm_min = x.rem;
	}
// часы в сутки
	x = div(tm1.tm_hour, 24);
	if (x.rem < 0)
	{
		dd = x.quot - 1;
		tm1.tm_hour = 60 + x.rem;
	}
	else
	{
		dd = x.quot;
		tm1.tm_hour = x.rem;
	}

	_incdate(&tm1, dd, 0, 0);

	isc_encode_date(&tm1, dt);

	return dt;
}

ISC_QUAD*	EXPORT fn_maxdate(ARG(ISC_QUAD*, dt1), ARG(ISC_QUAD*, dt2))
ARGLIST(ISC_QUAD *dt1)
ARGLIST(ISC_QUAD *dt2)
{
	dt1 = (dt1->gds_quad_high > dt2->gds_quad_high) ||
		((dt1->gds_quad_high == dt2->gds_quad_high) && (dt1->gds_quad_low > dt2->gds_quad_low))
		? dt1 : dt2;

	return dt1;
}

ISC_QUAD*	EXPORT fn_mindate(ARG(ISC_QUAD*, dt1), ARG(ISC_QUAD*, dt2))
ARGLIST(ISC_QUAD *dt1)
ARGLIST(ISC_QUAD *dt2)
{
	dt1 = (dt1->gds_quad_high < dt2->gds_quad_high) ||
		((dt1->gds_quad_high == dt2->gds_quad_high) && (dt1->gds_quad_low < dt2->gds_quad_low))
		? dt1 : dt2;

	return dt1;
}

double	EXPORT fn_timetodouble(ARG(ISC_QUAD*, dt))
ARGLIST(ISC_QUAD *dt)
{
	return (double) dt->gds_quad_low / msec_in_day;
}

double	EXPORT fn_datetodouble(ARG(ISC_QUAD*, dt))
ARGLIST(ISC_QUAD *dt)
{
	return dt->gds_quad_high +
		(double) dt->gds_quad_low / msec_in_day;
}

ISC_QUAD*	EXPORT fn_doubletodate(ARG(double*, d))
ARGLIST(double *d)
{
	ISC_QUAD *bufquad = (ISC_QUAD *) MALLOC (sizeof(ISC_QUAD));
	bufquad->gds_quad_high = *d;
	*d = (*d - bufquad->gds_quad_high) * msec_in_day;
	bufquad->gds_quad_low = ROUND(*d, 0);

	return bufquad;
}

ISC_QUAD*	EXPORT fn_doubletotime(ARG(double*, d))
ARGLIST(double *d)
{
	ISC_QUAD *bufquad = (ISC_QUAD *) MALLOC (sizeof(ISC_QUAD));
	bufquad->gds_quad_high = *d;
	*d = (*d - bufquad->gds_quad_high) * msec_in_day;
	bufquad->gds_quad_high = 0;
	bufquad->gds_quad_low = ROUND(*d, 0);

	return bufquad;
}
