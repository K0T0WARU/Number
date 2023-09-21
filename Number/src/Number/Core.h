#pragma once

#ifdef NUM_PLATFORM_WINDOWS
	#ifdef NUM_BUILD_DLL
		#define NUMBER_API __declspec(dllexport)
	#else
		#define NUMBER_API __declspec(dllimport)
	#endif
#else
	#error Number only support Windows!
#endif