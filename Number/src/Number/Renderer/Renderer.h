#pragma once

#include "Number/Renderer/VertexArray.h"

namespace Number {

    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
    };

}