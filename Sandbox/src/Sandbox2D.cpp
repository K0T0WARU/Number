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
    m_Texture = Number::Texture2D::Create("assets/textures/Goblin.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Number::Timestep& timestep)
{
    NUM_PROFILE_FUNCTION();

    {
        NUM_PROFILE_SCOPE("CameraController::OnUpdate");
        m_CameraController.OnUpdate(timestep);
    }

    {
        NUM_PROFILE_SCOPE("Renderer Prep");
        Number::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Number::RenderCommand::Clear();
    }

    {
        NUM_PROFILE_SCOPE("Renderer Draw");
        Number::Renderer2D::BeginScene(m_CameraController.GetCamera());
        Number::Renderer2D::DrawQuad({ -1.0f, -1.0f }, { 1.0f, 1.0f }, m_SquareColor);
        Number::Renderer2D::DrawQuad({ 1.0f, 1.0f }, { 2.0f, 2.0f }, { 0.8f, 0.2f, 0.2f, 1.0f });
        Number::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 2.0f, 2.0f }, m_Texture);
        Number::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender()
{
    NUM_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Number::Event& e)
{
    m_CameraController.OnEvent(e);
}
