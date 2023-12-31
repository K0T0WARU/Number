#include "numpch.h"
#include <Number.h>

class ExampleLayer : public Number::Layer 
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        NUM_INFO("ExampleLayer::Update");
    }

    void OnEvent(Number::Event& event) override
    {
        NUM_TRACE("{0}", event);
    }
};

class Sandbox : public Number::Application 
{
public:
	Sandbox() 
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new Number::ImGuiLayer());
	}

	~Sandbox() 
    {

	}
};

Number::Application* Number::CreateApplication() 
{
	return new Sandbox();
}