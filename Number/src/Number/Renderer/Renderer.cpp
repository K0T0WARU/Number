#include "numpch.h"
#include "Renderer.h"

#include "Number/Renderer/VertexArray.h"
#include "Number/Renderer/RenderCommand.h"
#include "Number/Renderer/RendererAPI.h"

#include "RenderCommand.h"

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Number {

    void Renderer::BeginScene()
    {
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

}