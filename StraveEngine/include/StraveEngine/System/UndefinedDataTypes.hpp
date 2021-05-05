#pragma once

#include <StraveEngine/Config.hpp>


#if defined(STRAVE_SYSTEM_WINDOWS)

	#define NULL_PTR		nullptr
	#define EMPTY_STR		"\0"

	#define UNDEF_PTR		NULL_PTR
	#define UNDEF_STR		EMPTY_STR

#endif

#define UNDEF_INT16			NULL
#define UNDEF_INT32			NULL
#define UNDEF_INT64			NULL

#define UNDEF_SMARTPTR		NULL
#define UNDEF_STD_VECTOR	NULL

#define UNDEF_INT			NULL
#define UNDEF_INT32			NULL
#define UNDEF_INT64			NULL
#define UNDEF_UINT			NULL
#define UNDEF_UINT16		NULL
#define UNDEF_UINT32		NULL
#define UNDEF_UINT64		NULL

#define UNDEF_BOOL			0

#define UNDEF_FLOAT			0.0f
#define UNDEF_DOUBLE		0.0
#define UNDEF_LFLOAT		UNDEF_FLOAT
#define UNDEF_LLFLOAT		UNDEF_FLOAT

#define UNDEF_VECTOR2F		{ UNDEF_FLOAT, UNDEF_FLOAT }
#define UNDEF_VECTOR2U		{ UNDEF_UINT, UNDEF_INT }
#define UNDEF_VECTOR2I		{ UNDEF_INT, UNDEF_INT }
#define UNDEF_VECTOR4F		{ UNDEF_VECTOR2F, UNDEF_VECTOR2F }
#define UNDEF_VECTOR4U		{ UNDEF_VECTOR2U, UNDEF_VECTOR2U }		
#define UNDEF_VECTOR4I		{ UNDEF_VECTOR2I, UNDEF_VECTOR2I }		

#define ERROR_TYPE			-1
#define UINT64_ERROR_TYPE	0xfffffff
#define UINT16_ERROR_TYPE	0xfffe
