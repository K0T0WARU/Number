#include "numpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Number {
     
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        :m_windowHandle(windowHandle)
    {
        NUM_CORE_ASSERT(windowHandle, "Window handle is null")
    }

    void OpenGLContext::Init()
    {
        NUM_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_windowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        NUM_CORE_ASSERT(status, "Failed to initailize Glad!");
        NUM_CORE_INFO("OpenGL Render info:");
        NUM_CORE_INFO("   Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        NUM_CORE_INFO("   Version: {0}", (const char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_windowHandle);
    }

}