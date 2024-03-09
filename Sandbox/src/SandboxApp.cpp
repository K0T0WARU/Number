#include "numpch.h"
#include <Number.h>

#include "imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Number::Layer 
{
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_CameraRotation(0.0f), m_SquarePosition(0.0f)
    {
        m_VertexArray.reset(Number::VertexArray::Create());

        float vertices[7 * 3] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f
        };

        Number::Ref<Number::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Number::VertexBuffer::Create(vertices, sizeof(vertices)));

        Number::BufferLayout layout = {
            { Number::ShaderDataType::Float3, "a_Position" },
            { Number::ShaderDataType::Float4, "a_Color" }
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };

        Number::Ref<Number::IndexBuffer> indexBuffer;
        indexBuffer.reset(Number::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVertexArray.reset(Number::VertexArray::Create());

        float squareVertices[5 * 4] = {
            -0.8f, -0.8f, 0.0f, 0.0f, 0.0f,
             0.8f, -0.8f, 0.0f, 1.0f, 0.0f,
             0.8f,  0.8f, 0.0f, 1.0f, 1.0f,
            -0.8f,  0.8f, 0.0f, 0.0f, 1.0f
        };

        Number::BufferLayout squareLayout = {
            { Number::ShaderDataType::Float3, "a_Position" },
            { Number::ShaderDataType::Float2, "a_TexCoord" }
        };

        Number::Ref<Number::VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(Number::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVertexBuffer->SetLayout(squareLayout);
        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        Number::Ref<Number::IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(Number::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

        std::string vertexSrc = R"(
            #version 430 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            
            uniform mat4 u_ViewProjectionMatrix;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;
            
            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0); 
            }  
        )";

        std::string fragmentSrc = R"(
            #version 430 core
            
            layout(location = 0) out vec4 Color;
            
            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                Color = v_Color;
            }  
        )";

        m_Shader.reset(Number::Shader::Create(vertexSrc, fragmentSrc));

        std::string textureVertexSrc = R"(
            #version 430 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;
            
            uniform mat4 u_ViewProjectionMatrix;
            uniform mat4 u_Transform;

            out vec2 v_TexCoord;
            
            void main()
            {
                v_TexCoord = a_TexCoord;
                gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0); 
            }  
        )";

        std::string textureFragmentSrc = R"(
            #version 430 core
            
            layout(location = 0) out vec4 color;

            in vec2 v_TexCoord;

            uniform sampler2D u_Texture;

            void main()
            {
                color = texture(u_Texture, v_TexCoord);
            }  
        )";

        m_TextureShader.reset(Number::Shader::Create(textureVertexSrc, textureFragmentSrc));

        m_Texture = Number::Texture2D::Create("assets/textures/Goblin.png");

        std::dynamic_pointer_cast<Number::OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<Number::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(Number::Timestep& timestep) override
    {
        if (Number::Input::IsKeyPresed(NUM_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMoveSpeed * timestep;
        else if (Number::Input::IsKeyPresed(NUM_KEY_LEFT))
            m_CameraPosition.x -= m_CameraMoveSpeed * timestep;

        if (Number::Input::IsKeyPresed(NUM_KEY_UP))
            m_CameraPosition.y += m_CameraMoveSpeed * timestep;
        else if (Number::Input::IsKeyPresed(NUM_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMoveSpeed * timestep;

        if (Number::Input::IsKeyPresed(NUM_KEY_E))
            m_CameraRotation += m_CameraRotationSpeed * timestep;
        else if (Number::Input::IsKeyPresed(NUM_KEY_Q))
            m_CameraRotation -= m_CameraRotationSpeed * timestep;

        if (Number::Input::IsKeyPresed(NUM_KEY_D))
            m_SquarePosition.x += m_SquareMoveSpeed * timestep;
        else if (Number::Input::IsKeyPresed(NUM_KEY_A))
            m_SquarePosition.x -= m_SquareMoveSpeed * timestep;

        if (Number::Input::IsKeyPresed(NUM_KEY_W))
            m_SquarePosition.y += m_SquareMoveSpeed * timestep;
        else if (Number::Input::IsKeyPresed(NUM_KEY_S))
            m_SquarePosition.y -= m_SquareMoveSpeed * timestep;

        Number::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Number::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Number::Renderer::BeginScene(m_Camera);

        std::dynamic_pointer_cast<Number::OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<Number::OpenGLShader>(m_TextureShader)->UploadUniformFloat3("u_Color", m_SquareColor);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);

        m_Texture->Bind();

        Number::Renderer::Submit(m_TextureShader, m_SquareVertexArray, transform);
        //Number::Renderer::Submit(m_Shader, m_VertexArray);

        Number::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(Number::Event& event) override
    {
        
    }
private:
    Number::Ref<Number::Shader> m_Shader;
    Number::Ref<Number::VertexArray> m_VertexArray;

    Number::Ref<Number::Shader> m_TextureShader;
    Number::Ref<Number::VertexArray> m_SquareVertexArray;

    Number::Ref<Number::Texture2D> m_Texture;

    Number::OrthographicCamera m_Camera;

    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 1.5f;

    float m_CameraRotation;
    float m_CameraRotationSpeed = 10.0f;

    glm::vec3 m_SquarePosition = { 0.0f, 0.0f, 0.0f };
    float m_SquareMoveSpeed = 0.5f;

    glm::vec3 m_SquareColor = { 0.2f, 0.2f, 0.8f };
};

class Sandbox : public Number::Application 
{
public:
	Sandbox() 
    {
        PushLayer(new ExampleLayer());
	}

	~Sandbox() 
    {

	}
};

Number::Application* Number::CreateApplication() 
{
	return new Sandbox();
}