#include "numpch.h"
#include "RenderCommand.h"

#include "Number/Renderer/VertexArray.h"
#include "Number/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Number {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}