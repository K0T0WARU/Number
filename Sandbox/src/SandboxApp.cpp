#include "numpch.h"
#include <Number.h>

#include "imgui.h"

class ExampleLayer : public Number::Layer 
{
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_CameraRotation(0.0f)
    {
        m_VertexArray.reset(Number::VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f
        };

        std::shared_ptr<Number::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Number::VertexBuffer::Create(vertices, sizeof(vertices)));

        Number::BufferLayout layout = {
            { Number::ShaderDataType::Float3, "a_Position" },
            { Number::ShaderDataType::Float4, "a_Color" }
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };

        std::shared_ptr<Number::IndexBuffer> indexBuffer;
        indexBuffer.reset(Number::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);



        m_SquareVertexArray.reset(Number::VertexArray::Create());

        float squareVertices[4 * 3] = {
            -0.8f, -0.8f, 0.0f,
             0.8f, -0.8f, 0.0f,
             0.8f,  0.8f, 0.0f,
            -0.8f,  0.8f, 0.0f
        };

        Number::BufferLayout squareLayout = {
            { Number::ShaderDataType::Float3, "a_Position" }
        };

        std::shared_ptr<Number::VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(Number::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVertexBuffer->SetLayout(squareLayout);
        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        std::shared_ptr<Number::IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(Number::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

        std::string vertexSrc = R"(
            #version 430 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            
            uniform mat4 u_ViewProjectionMatrix;

            out vec3 v_Position;
            out vec4 v_Color;
            
            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0); 
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

        m_Shader.reset(new Number::Shader(vertexSrc, fragmentSrc));

        std::string squareVertexSrc = R"(
            #version 430 core
            
            layout(location = 0) in vec3 a_Position;
            
            uniform mat4 u_ViewProjectionMatrix;

            out vec3 v_Position;
            
            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0); 
            }  
        )";

        std::string squareFragmentSrc = R"(
            #version 430 core
            
            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main()
            {
                color = vec4(0.2f, 0.2f, 0.5f, 1.0f);
            }  
        )";

        m_SquareShader.reset(new Number::Shader(squareVertexSrc, squareFragmentSrc));
    }

    void OnUpdate() override
    {
        if (Number::Input::IsKeyPresed(NUM_KEY_LEFT))
            m_CameraPosition.x -= m_CameraMoveSpeed;
        else if (Number::Input::IsKeyPresed(NUM_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMoveSpeed;

        if (Number::Input::IsKeyPresed(NUM_KEY_UP))
            m_CameraPosition.y += m_CameraMoveSpeed;
        else if (Number::Input::IsKeyPresed(NUM_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMoveSpeed;

        if (Number::Input::IsKeyPresed(NUM_KEY_Q))
            m_CameraRotation -= m_CameraRotationSpeed;
        else if (Number::Input::IsKeyPresed(NUM_KEY_E))
            m_CameraRotation += m_CameraRotationSpeed;

        Number::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Number::RenderCommand::Clear();

        Number::Renderer::BeginScene(m_Camera);

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Number::Renderer::Submit(m_SquareShader, m_SquareVertexArray);
        Number::Renderer::Submit(m_Shader, m_VertexArray);

        Number::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        
    }

    void OnEvent(Number::Event& event) override
    {
        
    }
private:
    std::shared_ptr<Number::Shader> m_Shader;
    std::shared_ptr<Number::VertexArray> m_VertexArray;

    std::shared_ptr<Number::Shader> m_SquareShader;
    std::shared_ptr<Number::VertexArray> m_SquareVertexArray;

    Number::OrthographicCamera m_Camera;

    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 0.025f;

    float m_CameraRotation;
    float m_CameraRotationSpeed = 0.1f;
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