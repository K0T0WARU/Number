#pragma once

#include "Number/Renderer/OrthographicCamera.h"
#include "Number/Renderer/Shader.h"

#include "Number/Renderer/VertexArray.h"

namespace Number {

    class Renderer
    {
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;
    };

}