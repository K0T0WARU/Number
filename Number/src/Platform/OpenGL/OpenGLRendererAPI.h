#pragma once

#include "Number/Renderer/RendererAPI.h"

#include <glm/glm.hpp>

namespace Number {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    };

}