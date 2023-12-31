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

#ifdef NUM_ENABLE_ASSERTS
    #define NUM_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define NUM_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define NUM_ASSERT(x, ...)
    #define NUM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)