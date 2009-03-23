##########################################################################
#
#                rfunc UDF library
#
##########################################################################
#
#  <Copyright>
#      Copyright 2009 PoleSoft Technologies Group
#      http://www.polesoft.ru/project/rfunc
#      mailto:support@polesoft.ru
#
#      This library is free software; you can redistribute it and/or
#      modify it under the terms of the GNU Lesser General Public
#      License as published by the Free Software Foundation; either
#      version 2.1 of the License, or (at your option) any later version.
#      See license.txt for more details.
#
#  <Unit> get_fb.m4
#    <Purpose>
#    <Effects>
#    <Perfomance>
##########################################################################
#  $Revision: 114 $ $Author: coopht $
#  $Date: 2009-03-15 17:49:11 +0300 (Вск, 15 Мар 2009) $
##########################################################################
AC_DEFUN([AC_FBA_CHECK],
[
AC_ARG_WITH([fb-includes],
             AC_HELP_STRING([--with-fb-includes=prefix],
	     [specify prefix to the firebird includes library, /usr/include by default]),
             [if test "$withval" = ""; then
	        ac_fb_inc_path="/usr/include"
	      else
                ac_fb_inc_path="$withval"
              fi
	      ],
	      [ac_fb_inc_path="/usr/include"])

AC_ARG_WITH([fb-libs],
             AC_HELP_STRING([--with-fb-libs=prefix],
	     [specify prefix to the firebird libs library, /usr/lib by default]),
             [if test "$withval" = ""; then
	        ac_fb_lib_path="/usr/lib"
	      else
                ac_fb_lib_path="$withval"
              fi
	      ],
	      [ac_fb_lib_path="/usr/lib"])


   FB_CFLAGS=""
   FB_LDFLAGS=""
   FB_VERSION=""

   ac_fb_header="ibase.h"

   AC_MSG_CHECKING([for Firebird client library includes])

   if test ! -f "$ac_fb_inc_path/$ac_fb_header"; then
     AC_MSG_ERROR([Cannot find $ac_fb_inc_path/$ac_fb_header])

   else		   
     ac_fb_cppflags="-I$ac_fb_inc_path/"
     old_CPPFLAGS="$CPPFLAGS"
     CPPFLAGS="$CPPFLAGS $ac_fb_cppflags"

     ac_fb_ldflags="-L$ac_fb_lib_path -lfbclient -lpthread"
     old_LDFLAGS="$LDFLAGS"
     LDFLAGS="$LDFLAGS $ac_fb_ldflags"

     AC_LANG_PUSH(C++)

# compiling test program with gcc -c to check if specified heder is present and it is correct
     AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <ibase.h>]],
                   [[
#if (FB_API_VER >= 0)
/* Everything is okay*/
#else
#  error Firebird version is too old
#endif
                   ]]
               )
               ],
               [AC_MSG_RESULT([found in $ac_fb_inc_path])],
               [AC_MSG_ERROR([Cannot compile test program, see config.log for details])]
           )

   AC_MSG_CHECKING([for Firebird client library libs])
# compiling test program with gcc -c to check if specified heder is present and it is correct
   AC_LINK_IFELSE([AC_LANG_PROGRAM([[@%:@include <ibase.h>]],
                   [[
isc_db_handle   newdb = 0;         /* database handle */
isc_tr_handle   trans = 0;         /* transaction handle */
ISC_STATUS_ARRAY status;           /* status vector */
                   ]]
               )
               ],
               [AC_MSG_RESULT([found in $ac_fb_lib_path])],
               [AC_MSG_ERROR([Cannot run test program, see config.log for details])]
           )
            AC_LANG_POP([C++])

            CPPFLAGS="$saved_CPPFLAGS"  
            FB_CFLAGS="$ac_fb_cppflags"

	    LDFLAGS="#saved_LDFLAGS"
            FB_LDFLAGS="$ac_fb_ldflags"

	    AC_MSG_CHECKING([firebird version])

            # Extracting Firebird version from ibase.h

            ac_fb_version=`cat "$ac_fb_inc_path/$ac_fb_header" | \
                           grep '#define.*FB_API_VER.*' | \
                           sed -e 's/.* //'`

            if test -n "$ac_fb_version"; then
               ac_fb_version_major=`expr $ac_fb_version \/ 10`
               ac_fb_version_minor=`expr $ac_fb_version \% 10`

               FB_VERSION="$ac_fb_version_major.$ac_fb_version_minor.x"
	       
	       AC_MSG_RESULT([found $FB_VERSION])   
             else
               AC_MSG_WARN([Could not find FB_API_VER macro in $ac_fb_header to get Firebird version.])
             fi

             AC_SUBST(FB_CFLAGS)
             AC_SUBST(FB_LDFLAGS)
             AC_SUBST(FB_VERSION)
        fi
])

AC_DEFUN([USE_RFUNC_ARGS],
[
	AC_ARG_ENABLE(rfile,
	              [  --enable-rfile  Enable an rfunc file module],
	              [rfile=true],
		      [rfile=false])
        AM_CONDITIONAL(R_USE_FILE, test x$rfile = xtrue)	

	AC_ARG_ENABLE(rdatetime,
	              [  --enable-rdatetime  Enable an rfunc date and time module],
	              [rdatetime=true],
		      [rdatetime=false])
        AM_CONDITIONAL(R_USE_DATETIME, test x$rdatetime = xtrue)	
	
	AC_ARG_ENABLE(rguid_win_style,
	              [  --enable-rguid_win_style  Enable an rfunc guid win style  module],
	              [rguid_win_style=true],
		      [rguid_win_style=false])
        AM_CONDITIONAL(R_GUID_WIN_STYLE, test x$r_guid_win_style = xtrue)	

	AC_ARG_ENABLE(rguid,
	              [  --enable-rguid  Enable an rfunc guid module],
	              [rguid=true],
		      [rguid=false])
        AM_CONDITIONAL(R_USE_GUID, test x$rguid = xtrue)	

	AC_SUBST(R_USE_FILE)
	AC_SUBST(R_USE_DATETIME)
	AC_SUBST(R_GUID_WIN_STYLE)
	AC_SUBST(R_USE_GUID)
])
