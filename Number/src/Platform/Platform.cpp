#include "numpch.h"
#include "Platform.h"

#include "Number/Renderer/RendererAPI.h"

#include <glfw/glfw3.h>

namespace Number {

    float Platform::GetTime()
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None:     NUM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return 0.0f;
            case RendererAPI::API::OpenGL:   return (float)glfwGetTime();
        }

        NUM_CORE_ASSERT(false, "Unknown RendererAPI!");
        return 0.0f;
    }

}