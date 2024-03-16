#include "numpch.h"
#include "Application.h"

#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

#include "Platform/Platform.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Number {

    Application* Application::s_Instance = nullptr;

	Application::Application()
    {
        NUM_CORE_ASSERT(!s_Instance, "Application already exists");
        s_Instance = this;

        m_Window = Scope<Window>(Window::Create()); 
        m_Window->SetEventCallback(NUM_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
	}
    
	Application::~Application() {

	}

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(NUM_BIND_EVENT_FN(Application::OnWindowClosed));
        dispatcher.Dispatch<WindowResizeEvent>(NUM_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }
 
	void Application::Run() {
        while (m_Running)
        {
            m_CurrentTime = Platform::GetTime();
            m_Timestep = m_CurrentTime - m_LastFrameTime;
            m_LastFrameTime = m_CurrentTime;

            if (!m_Minimized)
            {
                for (Layer* layer : m_LayerStack)
                    layer->OnUpdate(m_Timestep);
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
	}

    bool Application::OnWindowClosed(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }
        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        return false;
    }
}