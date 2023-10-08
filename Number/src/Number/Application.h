#pragma once

#include "Core.h"

#include "Window.h"
#include "Number/LayerStack.h"
#include "Number/Events/Event.h"
#include "Number/Events/ApplicationEvent.h"

namespace Number {

	class NUMBER_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
    private:
        bool OnWindowClosed(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
