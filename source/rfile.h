/*====================================================================
		rfile.h

		rFunc InterBase UDF library.
		Version functions.

		Copyright 1998-2003 Polaris Software
		http://rfunc.sourceforge.net
		mailto:rFunc@mail.ru

	 This library is free software; you can redistribute it and/or
	 modify it under the terms of the GNU Lesser General Public
	 License as published by the Free Software Foundation; either
	 version 2.1 of the License, or (at your option) any later version.
	 See license.txt for more details.

====================================================================== */

#ifndef _RFILE_H
#define _RFILE_H

#if defined RUSE_FILE

long	EXPORT fn_fseek_cur();
long	EXPORT fn_fseek_end();
long	EXPORT fn_fseek_set();
/* The first three can only be set by open */
long	EXPORT fn_fo_rdonly();
long	EXPORT fn_fo_wronly();
long	EXPORT fn_fo_rdwr  ();
/* Flag values for open only */
long	EXPORT fn_fo_creat ();
long	EXPORT fn_fo_trunc ();
long	EXPORT fn_fo_excl  ();
/* a file in append mode may be written to only at its end.*/
long	EXPORT fn_fo_append(); /* to end of file */
/* Traditional names for bits in st_mode. */
long	EXPORT fn_fs_iread  (); /* owner may read */
long	EXPORT fn_fs_iwrite (); /* owner may write */
long	EXPORT fn_fs_iexec  (); /* owner may execute <directory search> */

long	EXPORT fn_fcreate(ARG(char*, path), ARG(long*, mode));
long	EXPORT fn_fopen(ARG(char*, path), ARG(long*, oflag), ARG(long*, mode));
char*	EXPORT fn_fread(ARG(long*, fd), ARG(long*, count));
long	EXPORT fn_fwrite(ARG(long*, fd), ARG(char*, buffer));
long	EXPORT fn_fseek(ARG(long*, fd), ARG(long*, offset), ARG(long*, reference));
long	EXPORT fn_fclose(ARG(long*, fd));
long	EXPORT fn_fremove(ARG(char*, path));

long	EXPORT fn_fsize(ARG(char*, path));

#endif /* RUSE_FILE */

#endif /* _RFILE_H */
