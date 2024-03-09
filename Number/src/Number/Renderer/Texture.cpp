#include "numpch.h"
#include "Texture.h"

#include "Number/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Number {

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None:     NUM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:   return std::make_shared<OpenGLTexture2D>(path);
        }

        NUM_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }


}