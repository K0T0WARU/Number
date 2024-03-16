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
    m_SquareVertexArray = Number::VertexArray::Create();

    float squareVertices[5 * 4] = {
        -0.8f, -0.8f, 0.0f,
         0.8f, -0.8f, 0.0f,
         0.8f,  0.8f, 0.0f,
        -0.8f,  0.8f, 0.0f
    };

    Number::BufferLayout squareLayout = {
        { Number::ShaderDataType::Float3, "a_Position" },
    };

    Number::Ref<Number::VertexBuffer> squareVertexBuffer;
    squareVertexBuffer = Number::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

    squareVertexBuffer->SetLayout(squareLayout);
    m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

    Number::Ref<Number::IndexBuffer> squareIndexBuffer;
    squareIndexBuffer = Number::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

    m_FlatColorShader = Number::Shader::Create("assets/shaders/FlatColor.glsl");

    std::dynamic_pointer_cast<Number::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Number::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Number::Timestep& timestep)
{
    m_CameraController.OnUpdate(timestep);

    Number::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Number::RenderCommand::Clear();

    Number::Renderer::BeginScene(m_CameraController.GetCamera());

    std::dynamic_pointer_cast<Number::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Number::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

    Number::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, glm::translate(glm::mat4(1.0f), m_SquarePosition));

    Number::Renderer::EndScene();
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
