/** \file  md5c.c
    
    \brief MD5 message-digest algorithm.

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

      *******************************************************************

      MD5C.C - RSA Data Security, Inc., MD5 message-digest algorithm

      Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
      rights reserved.

      License to copy and use this software is granted provided that it
      is identified as the "RSA Data Security, Inc. MD5 Message-Digest
      Algorithm" in all material mentioning or referencing this software
      or this function.
      
      License is also granted to make and use derivative works provided
      that such works are identified as "derived from the RSA Data
      Security, Inc. MD5 Message-Digest Algorithm" in all material
      mentioning or referencing the derived work.
      
      RSA Data Security, Inc. makes no representations concerning either
      the merchantability of this software or the suitability of this
      software for any particular purpose. It is provided "as is"
      without express or implied warranty of any kind.

      These notices must be retained in any copies of any part of this
      documentation and/or software.
      
 **************************************************************************
 Last Changes:
   $Revision: 112 $ $Author: coopht $
   $Date: 2009-03-15 17:36:36 +0300 (Вск, 15 Мар 2009) $
 **************************************************************************/
/* GLOBAL.H - RSAREF types and constants
 */
/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;

/* UINT2 defines a two byte word */
typedef unsigned short int UINT2;

/* UINT4 defines a four byte word */
typedef unsigned long int UINT4;

/* End of GLOBAL.H - RSAREF types and constants
 */

/* MD5 context. */
typedef struct {
	UINT4 state[4];                                   /* state (ABCD) */
	UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;

#define MD5_SIGNATURE_LEN	16
#define MD5_CTX_LEN	177
#define MD5_CTX_BUFFER_LEN	64

#define hexfmt "%02X"

void	MD5Init (ARG(MD5_CTX, *context));
void	MD5Update (ARG(MD5_CTX *, context), ARG(unsigned char *, input), ARG(unsigned int, inputLen));
void	MD5Final (ARG(unsigned char *, digest), ARG(MD5_CTX *, context));

char*	EXPORT fn_md5sum(ARG(char*, s));

char*	EXPORT fn_md5init();
char*	EXPORT fn_md5update(ARG(char *, context), ARG(char *, input), ARG(long *, inputLen));
char*	EXPORT fn_md5final(ARG(char *, context));
