#include <Number.h>

class Sandbox : public Number::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Number::Application* Number::CreateApplication() {
	return new Sandbox();
}