#pragma once

#include "Core.h"

#include "Window.h"
#include "Number/LayerStack.h"
#include "Number/Events/Event.h"
#include "Number/Events/ApplicationEvent.h"

#include "Number/ImGui/ImGuiLayer.h"

#include "Number/Renderer/Shader.h"

namespace Number {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() { return *m_Window; }

    private:
        bool OnWindowClosed(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
    private:
        static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
