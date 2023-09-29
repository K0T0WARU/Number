#include "Application.h"

#include "Number/Event/ApplicationEvent.h"
#include "Log.h"

namespace Number {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
        WindowResizeEvent e(1280, 720);
        //NUM_TRACE(e);

		while (true);
	}
}