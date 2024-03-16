#include "numpch.h"
#include "RenderCommand.h"

#include "Renderer/VertexArray.h"
#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Number {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}