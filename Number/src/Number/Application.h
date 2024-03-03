#pragma once

#include "Window.h"
#include "Number/LayerStack.h"
#include "Number/Events/Event.h"
#include "Number/Events/ApplicationEvent.h"

#include "Number/ImGui/ImGuiLayer.h"

#include "Number/Renderer/Shader.h"
#include "Number/Renderer/Buffer.h"
#include "Number/Renderer/VertexArray.h"

#include "Number/Renderer/OrthographicCamera.h"

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
    private:
        static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
