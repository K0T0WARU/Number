#pragma once

#include <memory>

#ifdef NUM_PLATFORM_WINDOWS
	#ifdef NUM_BUILD_DLL
		#define NUMBER_API __declspec(dllexport)
	#else
		#define NUMBER_API __declspec(dllimport)
	#endif
#else
	#error Number only support Windows!
#endif

#ifdef NUM_DEBUG
    #define NUM_ENABLE_ASSERTS
#endif

#ifdef NUM_ENABLE_ASSERTS
    #define NUM_ASSERT(x, ...) { if(!(x)) { NUM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define NUM_CORE_ASSERT(x, ...) { if(!(x)) { NUM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define NUM_ASSERT(x, ...)
    #define NUM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

namespace Number {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;

}