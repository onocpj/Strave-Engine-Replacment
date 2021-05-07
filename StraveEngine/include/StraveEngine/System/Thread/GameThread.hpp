#pragma once

#include <StraveEngine/System/DataTypes.hpp>


#define THREAD_TASK			Strave::Uint16
#define TASK_RENDER			_render
#define TASK_LOGIC			_update
#define TASK_AUDIO			_audio
#define TASK_NETWORK		_network

#define DEFINE_TASK_RENDER		THREAD_TASK TASK_RENDER
#define DEFINE_TASK_LOGIC		THREAD_TASK TASK_LOGIC	
#define DEFINE_TASK_AUDIO		THREAD_TASK TASK_AUDIO	
#define DEFINE_TASK_NETWORK		THREAD_TASK TASK_NETWORK
