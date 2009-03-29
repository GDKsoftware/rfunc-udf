/** \file  rblob.c
    
    \brief Blob functions.

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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rfunc.h"
#include "rblob.h"
#include "rstring.h"
#include "win1251.h"
#include <stdio.h>

long EXPORT fn_b_number_segments (ARG(BLOB, b))
ARGLIST(BLOB b)
{
  if (!b->blob_handle)
    return 0L;

  return b->blob_number_segments;
}

long EXPORT fn_b_max_segment (ARG(BLOB, b))
ARGLIST(BLOB b)
{
  if (!b->blob_handle)
    return 0L;

  return b->blob_max_segment;
}

long EXPORT fn_b_total_length (ARG(BLOB, b))
ARGLIST(BLOB b)
{
  if (!b->blob_handle)
    return 0L;

  return b->blob_total_length;
}

long EXPORT fn_b_line_count (ARG(BLOB, b))
ARGLIST(BLOB b)
{
  unsigned char *buf, *p;
  unsigned short length, actual_length;
  long curr_segment = 0L, linecount = 0L;

  if (!b->blob_handle)
    return 0L;

  length = (unsigned short) (b->blob_max_segment);
  buf = (unsigned char *) malloc (b->blob_max_segment + 1L);

  while ((*b->blob_get_segment) (b->blob_handle, buf, length, &actual_length))
    {
      buf [actual_length] = 0;
      p = buf;
      while (*p)
	if (*p++ == '\n')
	  linecount++;
      if ((++curr_segment == b->blob_number_segments) && actual_length && (*--p != '\n'))
	linecount++;
    }

  free (buf);
  return linecount;
}

char* b_nsubstr(ARG(BLOB, b), ARG(long*, m), ARG(long*, n), ARG(long, maxlength))
ARGLIST(BLOB b)
ARGLIST(long *m)
ARGLIST(long *n)
ARGLIST(long maxlength)
{
  unsigned char *buf, *p, *q;
  long curr_bytecount = 0;
  unsigned short length, actual_length;

  char *buffer = (char *) MALLOC (maxlength);

  long left, right;

  buffer[0] = '\0';
  if (!b->blob_handle)
    return buffer;

  left = (*m < 0) ? b->blob_total_length + *m + 1 : *m;
  right = (*n < 0) ? left - 1 : left - 1 + *n - 1;
  left = (*n < 0) ? left + *n : left - 1;

  left = (left < 0) ? 0 : left;
  right = (right > b->blob_total_length - 1) ? b->blob_total_length - 1 : right;

  if (!*n || (left > b->blob_total_length - 1) || (right < 0))
    return buffer;

  length = (unsigned short) (b->blob_max_segment);
  buf = malloc (length + 1L);

  /* Limit the return string to "maxlength" bytes */
  if (right - left + 1L > maxlength - 1L)
    right = left + maxlength - 2L;
  q = (unsigned char *) buffer;
  while ((*b->blob_get_segment) (b->blob_handle, buf, length,
				 &actual_length))
    {
      buf [actual_length] = 0;

      p = buf;
      while (*p && (curr_bytecount <= right))
	{
	  if (curr_bytecount >= left)
	    *q++ = *p;
	  p++;
	  curr_bytecount++;
	}
      if (curr_bytecount >= right)
	break;
    }

  free (buf);
  *q = 0;
  return buffer;
}

char* EXPORT fn_b_substr(ARG(BLOB, b), ARG(long*, m), ARG(long*, n))
ARGLIST(BLOB b)
ARGLIST(long *m)
ARGLIST(long *n)
{
  return b_nsubstr(b, m, n, shortlen);
}

char* EXPORT fn_b_longsubstr(ARG(BLOB, b), ARG(long*, m), ARG(long*, n))
ARGLIST(BLOB b)
ARGLIST(long *m)
ARGLIST(long *n)
{
  return b_nsubstr(b, m, n, longlen);
}

char* b_nline(ARG(BLOB, b), ARG(long*, l), ARG(long, maxlength))
ARGLIST(BLOB b)
ARGLIST(long *l)
ARGLIST(long maxlength)
{
  unsigned char *buf, *p;
  long curr_bytecount = 0, curr_linecount = 1;
  unsigned short length, actual_length;
  char *buffer = (char *) MALLOC (maxlength);

  buffer[0] = '\0';
  if (!b->blob_handle)
    return buffer;

  length = (unsigned short) (b->blob_max_segment);
  buf = (unsigned char *) malloc (length + 1L);
  while ((*b->blob_get_segment) (b->blob_handle, buf, length,
				 &actual_length))
    {
      buf [actual_length] = 0;
	  
      p = buf;
      while (*p)
	{
	  if (*p == '\n')
	    {
	      curr_linecount++;
	      if (curr_linecount > *l)
		{
		  /* if (((*p == 0x0D) && (*(p+1) == 0x0A)) || ((*(p+1) == 0x0D) && (*p == 0x0A))) 
		     p++; */
		  break;
		}
	    }
	  else
	    if (curr_linecount == *l)
	      {
		if ((*p != 0x0D) && (*p != 0x0A))
		  buffer[curr_bytecount++] = *p;
		if (curr_bytecount >= maxlength - 1L)
		  break;
	      }
	  p++;
	}
      if ((curr_linecount > *l) || (curr_bytecount >= maxlength - 1L))
	break;
    }

  buffer[curr_bytecount] = 0;
  free (buf);
  return buffer;
}

char* EXPORT fn_b_line(ARG(BLOB, b), ARG(long*, l))
ARGLIST(BLOB b)
ARGLIST(long *l)
{
  return b_nline(b, l, shortlen);
}

char* EXPORT fn_b_longline(ARG(BLOB, b), ARG(long*, l))
ARGLIST(BLOB b)
ARGLIST(long *l)
{
  return b_nline(b, l, longlen);
}

void EXPORT fn_b_put_segment(ARG(char*, s), ARG(BLOB, b))
ARGLIST(char *s)
ARGLIST(BLOB b)
{
  if (b->blob_handle)
    (*b->blob_put_segment) (b->blob_handle, (unsigned char *) s, (unsigned short) strlen(s));
}

long get_next_segment(ARG(BLOB, b), ARG(unsigned char**, buffer), ARG(unsigned char**, ptr),
		      ARG(unsigned short, length), ARG(unsigned short*, actual_length))
ARGLIST(BLOB b)
ARGLIST(unsigned char **buffer)
ARGLIST(unsigned char **ptr)
ARGLIST(unsigned short length)
ARGLIST(unsigned short *actual_length)
{
  long result = 0;

  if (**ptr) return 0;

  if (!(*b->blob_get_segment) (b->blob_handle, *buffer, length, actual_length))
    {
      *actual_length = 0;
      result = 1;
    }
  (*buffer) [*actual_length] = '\0';
  *ptr = *buffer;
  return result;
}

short EXPORT fn_b_strcmp(ARG(BLOB, b1), ARG(BLOB, b2))
ARGLIST(BLOB b1)
ARGLIST(BLOB b2)
{
  long result = 0, r1, r2;
  unsigned char *s1, *s2, *p1, *p2;
  unsigned short l1, al1, l2, al2, minlen;

  /* Checking for bad BLOb handle. */
  if (!b1->blob_handle && !b2->blob_handle) return 0;
  if (!b1->blob_handle) return -1;
  if (!b2->blob_handle) return 1;

  l1 = (unsigned short) (b1->blob_max_segment);
  l2 = (unsigned short) (b2->blob_max_segment);

  s1 = (unsigned char *) malloc (l1 + 1L);
  s1[0] = '\0';
  p1 = s1;
  s2 = (unsigned char *) malloc (l2 + 1L);
  s2[0] = '\0';
  p2 = s2;

  while (!result)
    {
      r1 = get_next_segment(b1, &s1, &p1, l1, &al1);
      r2 = get_next_segment(b2, &s2, &p2, l2, &al2);

      if (r1 && r2)
	/* Nothing to do. BLOb is equal. */
	break;

      if (r1 || r2)
	minlen = 1;
      else
	minlen = MIN(al1, al2);
      result = strncmp((char *) p1, (char *) p2, minlen);
      if (!result)
	{
	  al1 -= minlen; al2 -= minlen;
	  p1 += minlen; p2 += minlen;
	}
    }

  free(s1);
  free(s2);
  return (short) result;
}

int b_textpos(ARG(char*, s), ARG(BLOB, b), ARG(short, ignore_case))
ARGLIST(char *s)
ARGLIST(BLOB b)
ARGLIST(short ignorecase)
{
  int result = 0;
  unsigned char *buf;
  char *found;
  unsigned short max_len, al = 0;
  size_t s_len=0, found_len = 0;

  s_len = strlen(s);
  if (!b->blob_handle || !b->blob_total_length || !s_len || (b->blob_total_length < s_len))
    return 0;
  max_len = (unsigned short) (b->blob_max_segment);
  buf =  malloc (max_len+1);
  memset (buf, 0, max_len+1);
  if (ignore_case) 
    fn_rupper((unsigned char *)s);
	
  while (result == 0 && buf != 0)
    {
      if (!(*b->blob_get_segment) (b->blob_handle, &buf[0], max_len, &al))
	{
	  result = 0;
	  break;
	}
      if (ignore_case) 
	fn_rupper((unsigned char *)buf);
	
      found = strstr ((char*)(buf),s);
      if (found!=0)
	{
	  found_len = strlen (found)-1;
	  result = al - found_len ;
	}
    }
  free(buf);
  return result;
}

	

int EXPORT fn_b_strpos(ARG(char*, s), ARG(BLOB, b))
ARGLIST(char *s)
ARGLIST(BLOB b)
{
  return b_textpos(s, b, 0);
}

int EXPORT fn_b_textpos(ARG(char*, s), ARG(BLOB, b))
ARGLIST(char *s)
ARGLIST(BLOB b)
{
  return b_textpos(s, b, 1);
}

void EXPORT fn_b_strupper(ARG(BLOB, b), ARG(BLOB, out))
ARGLIST(BLOB b)
ARGLIST(BLOB out)
{
  unsigned char *buf = NULL;
  unsigned short length = 0;
  unsigned short actual_length = 0;
  unsigned char *tmp = NULL;

  if (!b->blob_handle)
    return;

  length = (unsigned short) (b->blob_max_segment);
  buf = malloc (length + 1L);
  
  while ((*b->blob_get_segment) (b->blob_handle, buf, length, &actual_length))
    {
      buf [actual_length] = 0;
      tmp = (unsigned char *)malloc (actual_length + 1);
      tmp = (unsigned char *)strcpy ((char*)tmp, (char *)buf);

      fn_rupper (tmp);

      if (out->blob_handle)
	(*out->blob_put_segment) (out->blob_handle, tmp, actual_length);
     
      if (tmp)
	free (tmp);
    }
  if (buf)
    free (buf);
}

void EXPORT fn_b_strlower(ARG(BLOB, b), ARG(BLOB, out))
ARGLIST(BLOB b)
ARGLIST(BLOB out)
{
  unsigned char *buf = NULL;
  unsigned short length = 0;
  unsigned short actual_length = 0;
  unsigned char *tmp = NULL;

  if (!b->blob_handle)
    return;

  length = (unsigned short) (b->blob_max_segment);
  buf = malloc (length + 1L);
  
  while ((*b->blob_get_segment) (b->blob_handle, buf, length, &actual_length))
    {
      buf [actual_length] = 0;
      tmp = (unsigned char *)malloc (actual_length + 1);
      tmp = (unsigned char *)strcpy ((char*)tmp, (char *)buf);
      
      fn_rlower (tmp);

      if (out->blob_handle)
	(*out->blob_put_segment) (out->blob_handle, tmp, actual_length);
     
      if (tmp)
	free (tmp);
    }
  if (buf)
    free (buf);
}
