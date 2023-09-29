#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Number {

	class NUMBER_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define NUM_CORE_TRACE(...)		::Number::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NUM_CORE_INFO(...)		::Number::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NUM_CORE_WARN(...)		::Number::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NUM_CORE_ERROR(...)		::Number::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NUM_CORE_FATAL(...)		::Number::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define NUM_TRACE(...)		::Number::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NUM_INFO(...)		::Number::Log::GetClientLogger()->info(__VA_ARGS__)
#define NUM_WARN(...)		::Number::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NUM_ERROR(...)		::Number::Log::GetClientLogger()->error(__VA_ARGS__)
#define NUM_FATAL(...)		::Number::Log::GetClientLogger()->fatal(__VA_ARGS__)