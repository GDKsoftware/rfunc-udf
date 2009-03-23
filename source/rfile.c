/*====================================================================
		rfile.c

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

#if defined RUSE_FILE

#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include "rfunc.h"
#include "rfile.h"

long	EXPORT fn_fcreate(ARG(char*, path), ARG(long*, mode))
ARGLIST(char *path)
ARGLIST(long *mode)
{
	return creat(path, *mode);
}

long	EXPORT fn_fopen(ARG(char*, path), ARG(long*, oflag), ARG(long*, mode))
ARGLIST(char *path)
ARGLIST(long *oflag)
ARGLIST(long *mode)
{
	return open(path, *oflag, *mode);
}

char*	EXPORT fn_fread(ARG(long*, fd), ARG(long*, count))
ARGLIST(long *fd)
ARGLIST(long *count)
{
	long number = 0;
	char *buffer = (char*) MALLOC (*count+1);
//MALLOC(???)

	if (*fd)
		number = read(*fd, buffer, *count);
	buffer[number] = '\0';

	return buffer;
}

long	EXPORT fn_fwrite(ARG(long*, fd), ARG(char*, buffer))
ARGLIST(long *fd)
ARGLIST(char *buffer)
{
	long number = strlen(buffer);

	if (!*fd || !number) return 0;
	write(*fd, buffer, number);

	return number;
}

long	EXPORT fn_fseek(ARG(long*, fd), ARG(long*, offset), ARG(long*, reference))
ARGLIST(long *fd)
ARGLIST(long *offset)
ARGLIST(long *reference)
{
	if (!*fd) return 0;

	return lseek(*fd, *offset, *reference);
}

long	EXPORT fn_fclose(ARG(long*, fd))
ARGLIST(long *fd)
{
	if (*fd) close(*fd);
	return 0;
}

long	EXPORT fn_fremove(ARG(char*, path))
ARGLIST(char *path)
{
	return remove(path);
}

long	EXPORT fn_fseek_cur(){ return SEEK_CUR; }
long	EXPORT fn_fseek_end(){ return SEEK_END; }
long	EXPORT fn_fseek_set(){ return SEEK_SET; }
/* The first three can only be set by open */
long	EXPORT fn_fo_rdonly(){ return O_RDONLY; }
long	EXPORT fn_fo_wronly(){ return O_WRONLY; }
long	EXPORT fn_fo_rdwr  (){ return O_RDWR;   }
/* Flag values for open only */
long	EXPORT fn_fo_creat (){ return O_CREAT;  }
long	EXPORT fn_fo_trunc (){ return O_TRUNC;  }
long	EXPORT fn_fo_excl  (){ return O_EXCL;   }
/* a file in append mode may be written to only at its end.*/
long	EXPORT fn_fo_append(){ return O_APPEND; } /* to end of file */

/* Traditional names for bits in st_mode. */
long	EXPORT fn_fs_iread  (){ return S_IREAD;  } /* owner may read */
long	EXPORT fn_fs_iwrite (){ return S_IWRITE; } /* owner may write */
long	EXPORT fn_fs_iexec  (){ return S_IEXEC;  } /* owner may execute <directory search> */

long	EXPORT fn_fsize(ARG(char*, path))
ARGLIST(char *path)
{
	struct stat buffer;

	stat(path, &buffer);
	return buffer.st_size;
}

#endif /* RUSE_FILE */
