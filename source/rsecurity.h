/** \file  rsecurity.h
    
    \brief User manipulations.

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
#ifndef _RSECURITY_H
#define _RSECURITY_H

#include "rfunc.h"

#if defined IB_5X

long EXPORT fn_add_user(ARG(long*, protocol), ARG(char*, server),
	ARG(char*, user_name), ARG(char*, password),
	ARG(char*, group_name), ARG(char*, first_name), ARG(char*, middle_name), ARG(char*, last_name),
	ARG(char*, dba_user_name), ARG(char*, dba_password));

long EXPORT fn_modify_user(ARG(long*, protocol), ARG(char*, server),
	ARG(char*, user_name), ARG(char*, password),
	ARG(char*, group_name), ARG(char*, first_name), ARG(char*, middle_name), ARG(char*, last_name),
	ARG(char*, dba_user_name), ARG(char*, dba_password));

long EXPORT fn_delete_user(ARG(long*, protocol), ARG(char*, server),
	ARG(char*, user_name),
	ARG(char*, dba_user_name), ARG(char*, dba_password));

#endif /* IB_5X */

#endif /* _RSECURITY_H */
