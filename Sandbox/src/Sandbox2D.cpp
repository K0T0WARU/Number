#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1920.0f / 1080.0f, true), m_SquarePosition(0.0f)
{
}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Number::Timestep& timestep)
{
    m_CameraController.OnUpdate(timestep);

    Number::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Number::RenderCommand::Clear();

    Number::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Number::Renderer2D::DrawQuad(m_SquarePosition, {1.0f, 1.0f}, m_SquareColor);
    Number::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Number::Event& e)
{
    m_CameraController.OnEvent(e);
}
