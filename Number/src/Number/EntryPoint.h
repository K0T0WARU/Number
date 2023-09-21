#pragma once

#ifdef NUM_PLATFORM_WINDOWS

extern Number::Application* Number::CreateApplication();

int main(int argc, char** argv) {
	auto app = Number::CreateApplication();
	app->Run();
	delete app;
}

#endif