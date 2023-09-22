#pragma once

#ifdef NUM_PLATFORM_WINDOWS

extern Number::Application* Number::CreateApplication();

int main(int argc, char** argv) 
{
	Number::Log::Init();
	NUM_CORE_WARN("Initialized Log!");
	bool a = 0;
	NUM_INFO("Bool a = {0}", a);

	auto app = Number::CreateApplication();
	app->Run();
	delete app;
}

#endif