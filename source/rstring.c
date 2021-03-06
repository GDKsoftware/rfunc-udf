/** \file  rstring.c
    
    \brief String functions.

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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "rfunc.h"
#include "rstring.h"
#include "rmath.h"

char *delims = " "; /* empty delimiters */

unsigned char* EXPORT fn_chr(ARG(short*, i))
ARGLIST(short *i)
{
	unsigned char *s = (unsigned char*) MALLOC (2);
	s[0] = (unsigned char) *i;
	s[1] = '\0';
	return s;
}

short EXPORT fn_ord(ARG(unsigned char*, s))
ARGLIST(unsigned char *s)
{
	return (short) s[0];
}

char* EXPORT fn_ltrim(ARG(char*, s))
ARGLIST(char *s)
{
	char *c;
	c = s;
	while (*c && strchr(delims, *c)) c++;
	return c;
}

char* EXPORT fn_rtrim(ARG(char*, s))
ARGLIST(char *s)
{
	size_t n;
	n = strlen(s);
	while (n && strchr(delims, s[n-1])) n--;
	s[n] = '\0';
	return s;
}

char* EXPORT fn_trim(ARG(char*, s))
ARGLIST(char *s)
{
	return fn_rtrim(fn_ltrim(s));
}

char*	EXPORT fn_repeattrim(ARG(char*, str1), ARG(char*, delim))
ARGLIST(char *str1)
ARGLIST(char *delim)
{
	char *s = str1, *d = str1;

	/* while (*s == ' ') s++; */
	if (delim[0])
		while (*s)
		{
			while (*s && (*s != delim[0])) *d++ = *s++;
			*d++ = *s++;
			while (*s == delim[0]) s++;
			/* if (*s) *d++ = delim[0]; */
			/* else *d++ = '\0'; */
		}
		*d = '\0';
	return str1;
}

char* EXPORT fn_substr(ARG(char*, s), ARG(long*, m), ARG(long*, n))
ARGLIST(char *s)
ARGLIST(long *m)
ARGLIST(long *n)
{
	size_t left, right;
	size_t len = strlen(s);

	left = (*m < 0) ? len + *m + 1 : *m;
	right = (*n < 0) ? left - 1 : left - 1 + *n - 1;
	left = (*n < 0) ? left + *n : left - 1;

	left = (left < 0) ? 0 : left;
	right = (right > len - 1) ? len - 1 : right;

	if (!*n || (left > len - 1) || (right < 0))
		return &s[len];

	s[right + 1] = '\0';
	return &s[left];
}

char* strnrepeat(ARG(char*, s), ARG(long*, c), ARG(long, maxlength))
ARGLIST(char *s)
ARGLIST(long *c)
ARGLIST(long maxlength)
{
	long i = 0;
	long j = 0;
	size_t l = strlen(s);
	size_t n = MIN(*c * l + 1L, maxlength);
	char *buffer = (char*) MALLOC (n);

	if (*s)
		while (i < n - 1L)
		{
			buffer[i++] = s[j++];
			if (!s[j]) j = 0;
		}
	buffer[i] = '\0';
	return buffer;
}

char* EXPORT fn_strrepeat(ARG(char*, s), ARG(long*, c))
ARGLIST(char *s)
ARGLIST(long *c)
{
	return strnrepeat(s, c, shortlen);
}

char* EXPORT fn_longstrrepeat(ARG(char*, s), ARG(long*, c))
ARGLIST(char *s)
ARGLIST(long *c)
{
	return strnrepeat(s, c, longlen);
}

char* strnstuff(ARG(char*, s), ARG(long*, spos), ARG(long*, dcount), ARG(char*, is), ARG(long, maxlength))
ARGLIST(char *s)
ARGLIST(long *spos)
ARGLIST(long *dcount)
ARGLIST(char *is)
ARGLIST(long maxlength)
{
	long i = 0;
	long j = 0;
	long l = 0;
	size_t slen = strlen(s);
	long n;
	size_t len;
	char *buffer;

	len = slen + strlen(is) + 1L;
	len = MIN(len, maxlength);
	buffer = (char*) MALLOC (len);

	n = (*spos > slen) ? slen : ((*spos > 0) ? *spos - 1 : 0);
	while (l < n) buffer[l++] = s[j++];
	while (is[i] && (l < len - 1L)) buffer[l++] = is[i++];
	j = MIN(j + *dcount, slen);
	while (s[j] && (l < len - 1L)) buffer[l++] = s[j++];

	buffer[l] = '\0';
	return buffer;
}

char* EXPORT fn_strstuff(ARG(char*, s), ARG(long*, spos), ARG(long*, dcount), ARG(char*, is))
ARGLIST(char *s)
ARGLIST(long *spos)
ARGLIST(long *dcount)
ARGLIST(char *is)
{
	return strnstuff(s, spos, dcount, is, shortlen);
}

char* EXPORT fn_longstrstuff(ARG(char*, s), ARG(long*, spos), ARG(long*, dcount), ARG(char*, is))
ARGLIST(char *s)
ARGLIST(long *spos)
ARGLIST(long *dcount)
ARGLIST(char *is)
{
	return strnstuff(s, spos, dcount, is, longlen);
}

/*
	note: returns "s" itself if "froms" string is empty
*/
char* strnreplace(ARG(char*, s), ARG(char*, froms), ARG(char*, tos), ARG(long, maxlength))
ARGLIST(char *s)
ARGLIST(char *froms)
ARGLIST(char *tos)
ARGLIST(long maxlength)
{
	size_t sn = strlen(froms);
	char *buffer = (char*) MALLOC (maxlength);
	// if "froms" is an empty string
	if (sn == 0)
	{
		strcpy(buffer, s);
	}
     else
	{
		char *sptr = s, *ptr = s, *bptr = buffer;

		while ((ptr = strstr(ptr, froms)) != NULL)
		{
			while (sptr != ptr && (bptr -buffer < maxlength - 1)) 
				*bptr++ = *sptr++;
			sptr = tos;
			while (*sptr && (bptr-buffer<maxlength-1)) 					*bptr++ = *sptr++;
			ptr = ptr + sn;
			sptr = ptr;
		}
		while (*sptr && (bptr-buffer<maxlength-1))
			*bptr++ = *sptr++;
		*bptr = '\0';
	}
	return buffer;
}

char* EXPORT fn_strreplace(ARG(char*, s), ARG(char*, froms), ARG(char*, tos))
ARGLIST(char *s)
ARGLIST(char *froms)
ARGLIST(char *tos)
{
	return strnreplace(s, froms, tos, shortlen);
}

char* EXPORT fn_longstrreplace(ARG(char*, s), ARG(char*, froms), ARG(char*, tos))
ARGLIST(char *s)
ARGLIST(char *froms)
ARGLIST(char *tos)
{
	return strnreplace(s, froms, tos, longlen);
}

long EXPORT fn_strpos(ARG(char*, str1), ARG(char*, str2))
ARGLIST(char *str1)
ARGLIST(char *str2)
{
	char *ptr;
	if (!*str1) return 0;
	ptr = strstr(str2, str1);
	return (ptr) ? (ptr-str2+1) : 0;
}

long EXPORT fn_strlen(ARG(char*, s))
ARGLIST(char *s)
{
	return strlen(s);
}

long EXPORT fn_strcount(ARG(char*, str1), ARG(char*, str2))
ARGLIST(char *str1)
ARGLIST(char *str2)
{
	char *ptr;
	long  r = 0;
	size_t  len = strlen(str1);

	if (!len || !*str2) return 0;
	ptr = str2;
	while ((ptr = strstr(ptr, str1)) != NULL)
	{
		ptr += len;
		r++;
	}
	return r;
}

short EXPORT fn_strcmp(ARG(char*, str1), ARG(char*, str2))
ARGLIST(char *str1)
ARGLIST(char *str2)
{
	int r = strcmp(str1, str2);
	return (short) r;
}

long EXPORT fn_wordcount(ARG(char*, s), ARG(char*, delim), ARG(long*, flag))
ARGLIST(char *s)
ARGLIST(char *delim)
ARGLIST(long *flag)
{
	char *c = s;
	long r = 0;
	long d = 1;

	if (!*c) return r;
	while (*c)
		if (strchr(delim, *c++))
			d++; /* counting words */
		else {
			while (*c && !strchr(delim, *c)) c++;
			r++;  /* counting full words */
		}
	if (*flag)
		return d;
	else
		return r;
}

char* EXPORT fn_wordnum(ARG(char*, s), ARG(long*, n), ARG(char*, delim), ARG(long*, flag))
ARGLIST(char *s)
ARGLIST(long *n)
ARGLIST(char *delim)
ARGLIST(long *flag)
{
	char *c = s, *ptr;
	long r = 1;

	if (!*c) return c;
	while (*c && r!=*n)
		if (strchr(delim, *c++)) {
			if (*flag)
				r++;
			else
				while (*c && strchr(delim, *c)) c++;
		} else {
			while (*c && !strchr(delim, *c)) c++;
			if (!*flag) r++;
		}
	if (!*flag)
		while (*c && strchr(delim, *c)) c++;
	ptr = c;
	while (*ptr && !strchr(delim, *ptr)) ptr++;
	*ptr = '\0';

	return c;
}

char* padnright(ARG(char*, s), ARG(short*, n), ARG(char*, c), ARG(long, maxlength))
ARGLIST(char *s)
ARGLIST(short *n)
ARGLIST(char *c)
ARGLIST(long maxlength)
{
	long i = 0;
	char *buffer;
	char *ptr = s;
	long len = MIN(*n + 1L, maxlength);

	buffer = (char*) MALLOC (len);
	while (*ptr && (i < len - 1L)) buffer[i++] = *ptr++;
	while ((i < *n) && (i < len - 1L)) buffer[i++] = *c;
	buffer[i] = '\0';
	return buffer;
}

char* EXPORT fn_padright(ARG(char*, s), ARG(short*, n), ARG(char*, c))
ARGLIST(char *s)
ARGLIST(short *n)
ARGLIST(char *c)
{ return padnright(s, n, c, shortlen); }

char* EXPORT fn_longpadright(ARG(char*, s), ARG(short*, n), ARG(char*, c))
ARGLIST(char *s)
ARGLIST(short *n)
ARGLIST(char *c)
{ return padnright(s, n, c, longlen); }

char* padnleft(ARG(char*, s), ARG(short*, n), ARG(char*, c), ARG(long, maxlength))
ARGLIST(char *s)
ARGLIST(short *n)
ARGLIST(char *c)
ARGLIST(long maxlength)
{
	size_t l = strlen(s), i = 0;
	char *buffer;
	char *ptr = s;
	long len = MIN(*n + 1L, maxlength);

	buffer = (char*) MALLOC (len);
	while ((i < *n - l) && (i < len - 1L)) buffer[i++] = *c;
	while (*ptr && (i < len - 1L)) buffer[i++] = *ptr++;
	buffer[i] = '\0';
	return buffer;
}

char* EXPORT fn_padleft(ARG(char*, s), ARG(short*, n), ARG(char*, c))
ARGLIST(char *s)
ARGLIST(short *n)
ARGLIST(char *c)
{ return padnleft(s, n, c, shortlen); }

char* EXPORT fn_longpadleft(ARG(char*, s), ARG(short*, n), ARG(char*, c))
ARGLIST(char *s)
ARGLIST(short *n)
ARGLIST(char *c)
{ return padnleft(s, n, c, longlen); }

char* EXPORT fn_c(ARG(char*, s))
ARGLIST(char *s)
{ return s; }

char* EXPORT fn_floattostr(ARG(double*, d), ARG(char*, fmt))
ARGLIST(double *d)
ARGLIST(char *fmt)
{
	char *buffer = (char *) MALLOC (shortlen);
	char	*s, slong[20];
	long	i;

	buffer[0] = '\0';
	/* Parsing format string and trying to determine probable type of argument */
	/* Each conversion specificator begins with '%' symbol */

	if ((s = strstr(fmt, "%")) != NULL)
	{
		i = 1;
		while (strchr("+- #", s[i])) i++;
		while (strchr("0123456789", s[i])) i++;
		while (strchr(".", s[i])) i++;
		while (strchr("0123456789", s[i])) i++;
		if (strchr("diouxX", s[i]))
		{
			sprintf(slong, "%.0f", *d);
			i = atoi(slong);
			sprintf(buffer, fmt, i);
		}
		else
			sprintf(buffer, fmt, *d);
	}
	else
		sprintf(buffer, fmt, *d);
	return buffer;
}

char* EXPORT fn_inttostr(ARG(long*, l), ARG(char*, fmt))
ARGLIST(long *l)
ARGLIST(char *fmt)
{
	char *buffer = (char *) MALLOC (shortlen);

	sprintf(buffer, fmt, *l);
	return buffer;
}

char*	EXPORT fn_convertsymbols(ARG(char*, s), ARG(char*, source), ARG(char*, target))
ARGLIST(char *s)
ARGLIST(char *source)
ARGLIST(char *target)
{
	char	*c = s, *p;
	while (*c)
	  if ((p = strchr(source, *c)) != NULL)
			*c++ = target[p - source];
		else
			c++;
	return s;
}

char * EXPORT fn_xmlencent (ARG (char *, str))
  ARGLIST (char *str)
{
  size_t len; /* length of the input str*/
  char * result;

  if (str == NULL)
    return NULL;

  len = strlen (str) + 1;
  result = MALLOC (len);
  
  if (result == NULL)
    return "";

  result [0] = '\0';
    
  /* going through input string */
  while (*str)
    {
      switch (*str)
	{
	case '<':
	  len += 3;
	  result = realloc (result, len);
	  strcat (result, "&lt;");
	  break;

	case '>':
	  len += 3;
	  result = realloc (result, len);
	  strcat (result, "&gt;");
	  break;

	case '\'':
	  len += 5;
	  result = realloc (result, len);
	  strcat (result, "&apos;");
	  break;

	case '&': 
	  len += 4;
	  result = realloc (result, len);
	  strcat (result, "&amp;");
	  break;

	case '\"':
	  len += 5;
	  result = realloc (result, len);
	  strcat (result, "&quot;");
	  break;

	default:
	  strncat (result, str, 1);	  
	  break;
	}
      str++;
    }
  return result;
}

char * EXPORT fn_xmldecent (ARG (char *, str))
  ARGLIST (char *str)
{
  size_t len = 0;
  char * result;
  int dec; /* variable for dec value of char ref code */
  unsigned int hex; /* variable for dec value of char ref code */
  if (str == NULL)
    return NULL;

  result = MALLOC (strlen (str) + 1);
  
  if (result == NULL)   
    return "";

  result [len] = '\0';

  /* going through input string*/
  while (*str)
    {
      if (*str == '&')
	{
	  char * start = str;
	  size_t slen = 1; /* slice length from & to ; */

	  /* TODO: seems to be not very effecive */
	  while (*str != ';')
	    slen++, str++;	    
	  
	  if (strncmp (start, "&lt;", slen) == 0)
	    {
	      result [len] = '<';
	      ++len;
	    }
	  else if (strncmp (start, "&gt;", slen) == 0)
	    {
	      result [len] = '>';
	      ++len;
	    }
	  else if (strncmp (start, "&apos;", slen) == 0)
	    {
	      result [len] = '\'';
	      ++len;
	    }
	  else if (strncmp (start, "&amp;", slen) == 0)
	    {
	      result [len] = '&';
	      ++len;
	    }
	  else if (strncmp (start, "&quot;", slen) == 0)
	    {
	      result [len] = '\"';
	      ++len;
	    }
	  else if (strncmp (start, "&#38;#60;", slen+4) == 0)
	    {
	      result [len] = '<';
	      ++len;
	      str= str+4;
	    }
	  else if (strncmp (start, "&#38;#38;", slen+4) == 0)
	    {
	      result [len] = '&';
	      ++len;
	      str= str+4;
	    }

	  /* In this case we assumes that we got a character entities in */	  
	  else
	    {
	      char * tmp = malloc (slen + 1);
	      if (tmp == NULL)
		abort ();
	      tmp = (char *)memset (tmp, 0, slen + 1);
	      tmp = strncpy (tmp, start, slen);

	      /* In this if dec format :  &#num; */	      
	      if (tmp [2] != 'x')
		{
		  size_t idx = 2; /* the length of digits sequence after '#' */

		  while (isdigit (tmp [idx]))
		    ++idx;
		  
		  /* if one or more digits founded */
		  if (idx > 2)
		    {		      
		      /* copy founded digit to result */
		      if (sscanf (tmp, "&#%d", &dec) == 1)
			{		  
			  result [len] = (char)dec;
			  ++len;
			}
		    }
		  else 
		    idx = 0;
		  
		  /* skip ending ; symbol at entity's end, if entity os correct */
		  if (tmp [idx] == ';')
		    ++idx;
		  
		  /* copying rest part of the tmp string to result */
		  for (; idx < slen; ++idx)
		    {
		      result [len] = tmp [idx];		  
		      ++len;
		    }		      
		}

	      /* In this if hex format : &#xHex; */
	      else
		{
		  size_t idx = 3; /* the length of digits sequence after '#' */

		  /* checking if tmp is digit, or letters a,b,c,d,e,f */
		  while (isdigit (tmp [idx]) || 
			 ((tolower (tmp [idx]) >= 'a') && 
			  (tolower (tmp [idx]) <= 'f')))
		    ++idx;

		  /* if one or more digits founded */
		  if (idx > 3)
		    {
		      /* copy founded digit to result */
		      if (sscanf (tmp, "&#x%x;", &hex) == 1)
			{		  
			  result [len] = (char)hex;
			  ++len;
			}
		    }
		  else 
		    idx = 0;		    
		  
		  /* skip ending ; symbol at entity's end, if entity os correct */
		  if (tmp [idx] == ';')
		    ++idx;

		  /* copying rest part of the tmp string to result */
		  for (; idx < slen; ++idx)
		    {
		      result [len] = tmp [idx];		  
		      ++len;
		    }		      
		}
      
	      free ((void *)tmp);
	    }
	}
      else
	{
	  result [len] = *str;
	  ++len;
	}
      str++;
    }
  result = realloc (result, len + 1);
  result [len] = 0;
  return result;
}

int EXPORT fn_strnpos (ARG (char*, str1), 
		       ARG (char*, str2), 
		       ARG (int*, pos), 
		       ARG (int*, num))

ARGLIST (char* str1)
ARGLIST (char* str2)
ARGLIST (int* pos)
ARGLIST (int* num)
{  
  char *ptr;
  int i;
  
  if (!*str1) 
    return 0;
  
  if ((*pos < 1) || (*num < 1))
    {
      *pos = 1;	
      *num = 1;
    }

  ptr = str2 + *pos - 1;
  
  for (i = 0; i < *num; i++)
    {	       
      ptr = strstr (ptr, str1);

      if (ptr == NULL)
	return 0;

      ptr++;
    }
  
  return ptr - str2;
}

int EXPORT fn_strposr (ARG (char*, str1), ARG (char*, str2))
ARGLIST (char* str1)
ARGLIST (char* str2)
{
  size_t len;
  char * pos;

  if (str1 == NULL)
    return 0;

  len = strlen (str2);
  if (len < 1)
    return 0;
  /* Added -1 here, because string should begin from 1 */
  pos = str2 + len - 1;  

  while (*pos)
    {   
      if (strstr (pos, str1) != NULL)	
	return len + (str2 - pos);

      pos--;
    }

  return 0;
}

char * EXPORT fn_str2hex (ARG (char*, str))
ARGLIST (char* str)
{
  size_t len;  
  char  *result;
  char  *ptr;
  char  *res_ptr;

  if (str == NULL)
    return "";  

  ptr = str;

  len = strlen (ptr);    

  if (len < 1)
    return "";
  
  result = MALLOC (2 * len + 1);

  if (result == NULL)
    return "";

  result = (char *)memset (result, 0,  2 * len + 1);
  res_ptr = result;

  while (*ptr)
  {    
    sprintf (res_ptr, "%x",*ptr);      
    res_ptr += 2;
    ++ptr;    
  }   
  
  return result;
}

char * EXPORT fn_hex2str (ARG (char*, str))
ARGLIST (char* str)
{
  size_t len;
  char * result;
  int i  = 0;

  if (str == NULL)
	return "";

  len = strlen (str);

  if (len < 1)
	return "";

  result = MALLOC (len / 2 + 1);

  if (result == NULL)
	return "";

  while (*str)
    {
      sscanf (str, "%2x",(unsigned int*) &(result [i]));
      str += 2;
      i++;
    } 
  
  result [i + 1] = '\0'; 

  return result;
}

int EXPORT fn_strnposr (ARG (char*, str1), 
			ARG (char*, str2), 
			ARG (int*, pos),
			ARG (int*, num))
ARGLIST (char* str1)
ARGLIST (char* str2)
ARGLIST (int* pos)
ARGLIST (int* num)
{
  size_t len;
  char *buf;
  int i;
  int k;
  size_t orig;

  if (str1 == NULL)
    return 0;
  
  orig = strlen (str2);

  if (orig < 1)
    return 0;

  /* If starting search from the first postition, actually, 
     we should start from the 0 position*/
  if (*pos == 1)
    len = orig;
  else
    len = orig - *pos;

  buf = malloc (len + 1);
  if (buf == NULL)
    return 0;

  if (strncpy (buf, str2, len) == NULL)
    return 0;

  buf [len] = '\0';

  if (!*str1) 
    return 0;
  
  if ((*pos < 1) || (*num < 1))
    return 0;	
  
  /* Going in loop up to num occurence*/
  for (i = 0; i < *num; i++)
    {	       
      k = fn_strposr (str1, buf);
      if (k == 0)
	{
	  free (buf);
	  return 0;
	}

      len -= k;

      buf = realloc (buf, len + 1);
      strncpy (buf, str2, len);
      buf [len] = '\0';
    }

  free (buf);
  return orig - len;
}

/* Oh my god. This code works now */
char * EXPORT fn_substrr (ARG (char* ,str), ARG (int*, from), ARG (int*, len))
ARGLIST (char* str)
ARGLIST (int* from)
ARGLIST (int* len)
{
  int left;
  int right;
  int str_len = (int)strlen (str);
  char * result;
  char * ptr = str;
  int t;

  left = (*from > 0) ? str_len - *from + 1 : -*from;
  right = (*len > 0) ? left - 1 : left - 1 - *len - 1;
  left = (*len > 0) ? left - *len : left - 1;
  
  left = (left < 0) ? 0 : left;
  right = (right > str_len - 1) ? str_len - 1 : right;
 
  if (*len == 0 || (left > str_len - 1) || (right < 0))
    {
      t = left - right + 1;
      result = (char*)MALLOC (t + 1);
      result = (char *)memset ((void*)result, 0, t + 1);
      result = strncpy  (result, ptr + left, t); 
    }
  else  
    {      
      t = right - left + 1;
      result = (char*)MALLOC (t + 1);
      result = (char *)memset ((void*)result, 0, t + 1);
      result = strncpy (result, ptr + left, t);
    }
  return result; 
}

char * EXPORT fn_strmirror (ARG (char*, str))
ARGLIST (char* str)
{
  size_t i;
  size_t len;
  char *result;

  if (str==NULL)
       return "";
  len = strlen (str);
  result = (char*) MALLOC (len+1);
  for (i=0; i < len; i++)
  {
       result [i] = str [len-i-1];
  }
  result[len] = '\0';
  return result;
}

char * EXPORT fn_cr()
{
  char *result;
  result = MALLOC (2);
  memset (result, 0, 2);
  result = strcat (result, "\r");
  return result;
}
 
char * EXPORT fn_lf()
{
  char *result;
  result = MALLOC (2);
  memset (result, 0, 2);
  result = strcat (result, "\n");
  return result;}

char * EXPORT fn_crlf()
{
  char *result;
  result = MALLOC (3);
  memset (result, 0, 3);
  result = strcat (result, "\r\n");
  return result;
}

char * EXPORT fn_tab()
{
  char *result;
  result = MALLOC (2);
  memset (result, 0, 2);
  result = strcat (result, "\t");
  return result;
}

char * EXPORT fn_stresc (ARG(char*, str))
ARGLIST(char *str)
{
  char * result;
  char * ptr;
  size_t act_len;

  if (str == NULL)
    return "";
  
  act_len = strlen (str) + 1;
  
  result = MALLOC (act_len); 
  
  if (result == NULL)
    return "";

  ptr = result;  
  while (*str)
    {
      if (*str == '\\')
	{
	  char c = *(str + 1);

	  switch (c)
	    {
	    case 'a':
	      --act_len;
	      ++str;
	      *ptr = '\a';
	      break;
	      
	    case 'b':
	      --act_len;
	      ++str;
	      *ptr = '\b';
	      break;
	      
	    case 't':
	      --act_len;
	      ++str;
	      *ptr = '\t';
	      break;
	      
	    case 'n':
	      --act_len;
	      ++str;
	      *ptr = '\n';
	      break;
	      
	    case 'v':
	      --act_len;
	      ++str;
	      *ptr = '\v';
	      break;
	      
	    case 'f':
	      --act_len;
	      ++str;
	      *ptr = '\f';
	      break;
	      
	    case 'r':
	      ++str;
	      --act_len;
	      *ptr = '\r';
	      break;
	      
	    default:
	      if (isdigit (c) && 
		  isdigit (*(str + 2)) &&
		  isdigit (*(str + 3)))
		{		  
		  int d;
		  char num [4];
		  strncpy (num, str + 1, 3);
		  sscanf (num, "%d", &d);
		  *ptr = (char)d;
		  str += 3;
		  act_len -= 3;
		}
	      else	      
		*ptr = *str;
	      break;	      
	    }
	}
      else
	*ptr = *str;
      ++ptr;
      ++str;
    } 

  result = (char *)realloc ((void *)result, act_len);
  result [act_len - 1] = '\0';

  return result;
}

