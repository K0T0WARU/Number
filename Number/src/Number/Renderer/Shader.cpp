#include "numpch.h"
#include "Shader.h"

#include "Number/Renderer/Renderer.h"
#include "Number/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/glm.hpp>

namespace Number {
    Shader* Shader::Create(const std::string& filepath)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None:     NUM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:   return new OpenGLShader(filepath);
        }

        NUM_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None:     NUM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:   return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        NUM_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}