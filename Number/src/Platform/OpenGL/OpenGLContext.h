#pragma once
#include "Number/Log.h"

#include "Number/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Number {

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_windowHandle;
    };

}