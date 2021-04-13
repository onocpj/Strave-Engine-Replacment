#pragma once

#include <StraveEngine/System/DataTypes.hpp>

#include <string>


#define EXC_MSG		0
#define EXC_CODE	1

#define EXC_CODE_0	0
#define EXC_CODE_1	1
#define EXC_CODE_2	2
#define EXC_CODE_3	3
#define EXC_CODE_4	4
#define EXC_CODE_5	5
#define EXC_CODE_6	6
#define EXC_CODE_7	7
#define EXC_CODE_8	8
#define EXC_CODE_9	9

#define NO_EXCEPTION				{ "No Errors", EXC_CODE_0 }
// Log exceptions
#define THROW__EXC_LOG_DEL			{ "function Delete from Log: Unable to delete Log instance", EXC_CODE_1 }
// Window exceptions
#define THROW__EXC_WIN_RUN			{ "function Execute from Window: Window instance is already running", EXC_CODE_2 }
#define THROW__EXC_WIN_DEL			{ "function Delete from Window: Unable to delete Window instance", EXC_CODE_3 }
// Garbage collector exceptions
#define THROW__EXC_GBC_SWEEP_MEM	{ "function SweepMemory from GarbageCollector: Unable to sweep memory", EXC_CODE_4 }
#define THROW__EXC_GBC_DEL			{ "function Delete from GarbageCollector: Unable to delete garbage collector instance", EXC_CODE_5 }
// Map container exceptions
#define THROW__EXC_MAPC_RMV			{ "function EraseElement from MapContainer: Unable to erase element from container",  EXC_CODE_6 }
// Renderer exceptions
#define THROW__EXC_RNDR_DEL			{ "function Delete from Renderer: Unable to delete renderer instance",  EXC_CODE_7 }
// Scene sxceptions
#define THROW__EXC_SCENE_DEL		{ "function Delete from Scene: Unable to delete scene instance",  EXC_CODE_8 }


namespace Strave
{
	typedef Int16 ExceptionCode;

	struct Exception
	{
		const char*		title;
		ExceptionCode	code;
	};
}
