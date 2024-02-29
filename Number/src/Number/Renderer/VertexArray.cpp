#include "numpch.h"
#include "VertexArray.h"

#include "Number/Renderer/Renderer.h"
#include "Number/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Number {

    VertexArray* VertexArray::Create()
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None:     NUM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:   return new OpenGLVertexArray();
        }

        NUM_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}