/*
*
* Copyright (C) <2014> <w-hs - cglab projects>
* All rights reserved.
*
* This software may be modified and distributed under the terms
* of the BSD license.  See the LICENSE file for details.
*/

#ifndef _Types_H__
#define _Types_H__

///////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////

#include "CompilerPre.h"

///////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////

#ifndef	NULL
	#define NULL		0			//!< Definition of NULL keyword
#endif

#define FORCE_DWORD	0x7fffffff	//!< Force dword to 4 bytes in enum

typedef signed short    ss16;
typedef unsigned short  us16;
typedef unsigned long   ul32;
typedef float           fl32;
typedef double          db64;
typedef unsigned char   ub8;
typedef signed char		sb8;
typedef unsigned int	ui32;
typedef signed int		si32;

#ifdef _WIN32
	typedef signed __int64		si64;	//!< Signed ultra long (qword, 64 bit) definition
	typedef unsigned __int64	ui64;	//!< Unsigned ultra long (qword, 64 bit) definition
#endif
//typedef LARGE_INTEGER   li64;
//typedef LONGLONG        ll64;

#ifdef __APPLE__

	#include <MacTypes.h>

	typedef UInt64 ui64;
	typedef SInt64 si64;
#endif

#if defined __linux__
typedef unsigned char byte;
typedef long long si64;
typedef long long ul64;
typedef int64_t ui64;
#endif

//#ifndef __STDC__
//
//	#if defined _WIN64
//		typedef signed __int64 si64;
//		typedef unsigned __int64 ul64;
//	#else
//		if defined _WIN32
//			typedef LARGE_INTEGER   si64;
//			typedef LONGLONG        ul64;
//		#endif
//	#endif
//
//	#if defined _XBOX
//		typedef LARGE_INTEGER   si64;
//		typedef LONGLONG        ul64;
//	#endif
//
//	#if defined __GNUC__
//		typedef long long       si64;
//		typedef long long       ul64;
//	#endif
//
//#else // #ifndef __STDC__
//
//	// Standard ISO C does not allow 64 bit integer
//	// -> replace by a structure
//	typedef struct
//	{
//		long l1;
//		long l2;
//	} si64;
//
//	typedef struct
//	{
//		long l1;
//		long l2;
//	} sl64;
//
//#endif

#endif // _Types_H__
