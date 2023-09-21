#pragma once

#include "Core.h"

namespace Number {

	class NUMBER_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
