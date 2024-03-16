#pragma once

#include <Number.h>

class Sandbox2D : public Number::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    void OnUpdate(Number::Timestep& timestep) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Number::Event& e) override;
private:

    Number::OrthographicCameraController m_CameraController;
    Number::ShaderLibrary m_ShaderLibrary;

    Number::Ref<Number::Shader> m_FlatColorShader;

    Number::Ref<Number::VertexArray> m_SquareVertexArray;

    Number::Ref<Number::Texture2D> m_Texture;

    glm::vec4 m_SquareColor = { 0.2f, 0.2f, 0.8f, 1.0f };
    glm::vec3 m_SquarePosition = { 0.0f, 0.0f, 0.0f };
};

