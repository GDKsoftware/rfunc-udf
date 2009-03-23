/*====================================================================
		rsecurity.c

		rFunc InterBase UDF library.
		User manipulations.

		Copyright 1998-2003 Polaris Software
		http://rfunc.sourceforge.net
		mailto: rFunc@mail.ru

	 This library is free software; you can redistribute it and/or
	 modify it under the terms of the GNU Lesser General Public
	 License as published by the Free Software Foundation; either
	 version 2.1 of the License, or (at your option) any later version.
	 See license.txt for more details.

====================================================================== */

#include "rfunc.h"

#if defined IB_5X

#include "rsecurity.h"

long EXPORT fn_add_user(ARG(long*, protocol), ARG(char*, server),
	ARG(char*, user_name), ARG(char*, password),
	ARG(char*, group_name), ARG(char*, first_name), ARG(char*, middle_name), ARG(char*, last_name),
	ARG(char*, dba_user_name), ARG(char*, dba_password))
ARGLIST(long *protocol)
ARGLIST(char *server)
ARGLIST(char *user_name)
ARGLIST(char *password)
ARGLIST(char *group_name)
ARGLIST(char *first_name)
ARGLIST(char *middle_name)
ARGLIST(char *last_name)
ARGLIST(char *dba_user_name)
ARGLIST(char *dba_password)
{
	ISC_STATUS status[20];
	USER_SEC_DATA sec;

	switch (*protocol)
	{
		case 1: sec.protocol = sec_protocol_tcpip; break;
		case 2: sec.protocol = sec_protocol_netbeui; break;
#ifndef IB_6X
		case 3: sec.protocol = sec_protocol_spx; break;
#endif
		case 4: sec.protocol = sec_protocol_local; break;
//    else return -1;
	}
//  if (!*password) return -2;
	sec.server = server;
	sec.user_name = user_name;
	sec.password = password;
	sec.group_name = group_name;
	sec.first_name = first_name;
	sec.middle_name = middle_name;
	sec.last_name = last_name;
	sec.dba_user_name = dba_user_name;
	sec.dba_password = dba_password;
	if (*server)
		sec.sec_flags = sec.sec_flags | (short) sec_server_spec;
	if (*password)
		sec.sec_flags = sec.sec_flags | (short) sec_password_spec;
	if (*group_name)
		sec.sec_flags = sec.sec_flags | (short) sec_group_name_spec;
	if (*first_name)
		sec.sec_flags = sec.sec_flags | (short) sec_first_name_spec;
	if (*middle_name)
		sec.sec_flags = sec.sec_flags | (short) sec_middle_name_spec;
	if (*last_name)
		sec.sec_flags = sec.sec_flags | (short) sec_last_name_spec;

	if (*dba_user_name)
		sec.sec_flags = sec.sec_flags | (short) sec_dba_user_name_spec;
	if (*dba_password)
		sec.sec_flags = sec.sec_flags | (short) sec_dba_password_spec;

	isc_add_user(status, &sec);

	/* check status for errors */
	if (status[0] == 1 && status[1])
		return status[1];
	else
		return 0;
}

long EXPORT fn_modify_user(ARG(long*, protocol), ARG(char*, server),
	ARG(char*, user_name), ARG(char*, password),
	ARG(char*, group_name), ARG(char*, first_name), ARG(char*, middle_name), ARG(char*, last_name),
	ARG(char*, dba_user_name), ARG(char*, dba_password))
ARGLIST(long *protocol)
ARGLIST(char *server)
ARGLIST(char *user_name)
ARGLIST(char *password)
ARGLIST(char *group_name)
ARGLIST(char *first_name)
ARGLIST(char *middle_name)
ARGLIST(char *last_name)
ARGLIST(char *dba_user_name)
ARGLIST(char *dba_password)
{
	ISC_STATUS status[20];
	USER_SEC_DATA sec;

	switch (*protocol)
	{
		case 1: sec.protocol = sec_protocol_tcpip; break;
		case 2: sec.protocol = sec_protocol_netbeui; break;
#ifndef IB_6X
		case 3: sec.protocol = sec_protocol_spx; break;
#endif
		case 4: sec.protocol = sec_protocol_local; break;
	}
	sec.server = server;
	sec.user_name = user_name;
	sec.password = password;
	sec.group_name = group_name;
	sec.first_name = first_name;
	sec.middle_name = middle_name;
	sec.last_name = last_name;
	sec.dba_user_name = dba_user_name;
	sec.dba_password = dba_password;
	if (*server)
		sec.sec_flags = sec.sec_flags | (short) sec_server_spec;
	if (*password)
		sec.sec_flags = sec.sec_flags | (short) sec_password_spec;
	if (*group_name)
		sec.sec_flags = sec.sec_flags | (short) sec_group_name_spec;
	if (*first_name)
		sec.sec_flags = sec.sec_flags | (short) sec_first_name_spec;
	if (*middle_name)
		sec.sec_flags = sec.sec_flags | (short) sec_middle_name_spec;
	if (*last_name)
		sec.sec_flags = sec.sec_flags | (short) sec_last_name_spec;

	if (*dba_user_name)
		sec.sec_flags = sec.sec_flags | (short) sec_dba_user_name_spec;
	if (*dba_password)
		sec.sec_flags = sec.sec_flags | (short) sec_dba_password_spec;

	isc_modify_user(status, &sec);

	/* check status for errors */
	if (status[0] == 1 && status[1])
		return status[1];
	else
		return 0;
}

long EXPORT fn_delete_user(ARG(long*, protocol), ARG(char*, server),
	ARG(char*, user_name),
	ARG(char*, dba_user_name), ARG(char*, dba_password))
ARGLIST(long *protocol)
ARGLIST(char *server)
ARGLIST(char *user_name)
ARGLIST(char *dba_user_name)
ARGLIST(char *dba_password)
{
	ISC_STATUS status[20];
	USER_SEC_DATA sec;

	switch (*protocol)
	{
		case 1: sec.protocol = sec_protocol_tcpip; break;
		case 2: sec.protocol = sec_protocol_netbeui; break;
#ifndef IB_6X
		case 3: sec.protocol = sec_protocol_spx; break;
#endif
		case 4: sec.protocol = sec_protocol_local; break;
	}
	sec.server = server;
	sec.user_name = user_name;
	sec.dba_user_name = dba_user_name;
	sec.dba_password = dba_password;
	if (*server)
		sec.sec_flags = sec.sec_flags | (short) sec_server_spec;

	if (*dba_user_name)
		sec.sec_flags = sec.sec_flags | (short) sec_dba_user_name_spec;
	if (*dba_password)
		sec.sec_flags = sec.sec_flags | (short) sec_dba_password_spec;

	isc_delete_user(status, &sec);

	/* check status for errors */
	if (status[0] == 1 && status[1])
		return status[1];
	else
		return 0;
}

#endif
