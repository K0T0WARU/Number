#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <chrono>

#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>

#ifdef NUM_PLATFORM_WINDOWS
    #include <Windows.h>
#endif

#include "Core/Log.h"
#include "Core/Core.h"
#include "Debug/Instrumentor.h"