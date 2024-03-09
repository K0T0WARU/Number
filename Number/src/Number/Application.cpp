#include "numpch.h"
#include "Application.h"

#include "Number/Events/ApplicationEvent.h"

#include "Number/Renderer/Renderer.h"
#include "Number/Renderer/RenderCommand.h"

#include "Platform/Platform.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Number {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

	Application::Application()
    {
        NUM_CORE_ASSERT(!s_Instance, "Application already exists");
        s_Instance = this;

        m_Window = Scope<Window>(Window::Create()); 
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

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
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

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

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate(m_Timestep);

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
	}

    bool Application::OnWindowClosed(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}