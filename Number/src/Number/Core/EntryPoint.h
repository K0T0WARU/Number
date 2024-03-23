#pragma once

#ifdef NUM_PLATFORM_WINDOWS

extern Number::Application* Number::CreateApplication();

int main(int argc, char** argv) 
{
	Number::Log::Init();

    NUM_PROFILE_BEGIN_SESSION("Startup", "NumberProfile-Startup.json");
	auto app = Number::CreateApplication();
    NUM_PROFILE_END_SESSION();

    NUM_PROFILE_BEGIN_SESSION("Runtime", "NumberProfile-Runtime.json");
    app->Run();
    NUM_PROFILE_END_SESSION();
    
    NUM_PROFILE_BEGIN_SESSION("Shutdown", "NumberProfile-Shutdown.json");
    delete app;
    NUM_PROFILE_END_SESSION();
}

#endif