#pragma once

#include <StraveEngine/System/DataTypes.hpp>


#define THREAD_TASK			Strave::Uint16
#define THREAD_RENDER		_render
#define THREAD_LOGIC		_update
#define THREAD_AUDIO		_audio
#define THREAD_NETWORK		_network

#define THREAD_RENDER		THREAD_TASK THREAD_RENDER
#define THREAD_LOGIC		THREAD_TASK THREAD_LOGIC	
#define THREAD_AUDIO		THREAD_TASK THREAD_AUDIO	
#define THREAD_NETWORK		THREAD_TASK THREAD_NETWORK
