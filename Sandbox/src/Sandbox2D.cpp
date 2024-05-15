#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

template<typename Fn>
class Timer
{
public:
    Timer(const char* name, Fn&& func)
        : m_Name(name), m_Func(func), m_Stopped(false)
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        if (!m_Stopped)
            Stop();
    }

    void Stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimepoint).time_since_epoch().count();

        m_Stopped = true;
        float duration = (end - start) * 0.001f;
        m_Func({ m_Name, duration });
    }
private:
    const char* m_Name;
    std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
    bool m_Stopped;
    Fn m_Func;
};

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
    Timer timer("Sandbox", [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); });

    NUM_PROFILE_FUNCTION();

    m_CameraController.OnUpdate(timestep);

    {
        NUM_PROFILE_SCOPE("Renderer Prep");
        Number::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Number::RenderCommand::Clear();
    }

    {
        NUM_PROFILE_SCOPE("Renderer Draw");
        Number::Renderer2D::BeginScene(m_CameraController.GetCamera());
        Number::Renderer2D::DrawQuad({ -1.0f, -1.0f }, { 1.0f, 1.0f }, m_SquareColor);
        Number::Renderer2D::DrawQuad(m_SquarePosition, { 2.0f, 2.0f }, { 0.8f, 0.2f, 0.2f, 1.0f });
        Number::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 2.0f, 2.0f }, m_Texture);
        Number::Renderer2D::EndScene();
    }

    if (Number::Input::IsKeyPresed(NUM_KEY_RIGHT))
        m_SquarePosition.x += m_SquareMoveSpeed * timestep;
    else if (Number::Input::IsKeyPresed(NUM_KEY_LEFT))
        m_SquarePosition.x -= m_SquareMoveSpeed * timestep;

    if (Number::Input::IsKeyPresed(NUM_KEY_UP))
        m_SquarePosition.y += m_SquareMoveSpeed * timestep;
    else if (Number::Input::IsKeyPresed(NUM_KEY_DOWN))
        m_SquarePosition.y -= m_SquareMoveSpeed * timestep;
}

void Sandbox2D::OnImGuiRender()
{
    NUM_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::InputFloat("Square Speed", &m_SquareMoveSpeed);
    ImGui::End();

    ImGui::Begin("Tests");
    for (auto& result : m_ProfileResults)
    {
        char label[50];
        strcpy(label, result.Name);
        strcat(label, " %.3fms");
        ImGui::Text(label, result.Time);
    }
    m_ProfileResults.clear();
    ImGui::End();
}

void Sandbox2D::OnEvent(Number::Event& e)
{
    m_CameraController.OnEvent(e);
}