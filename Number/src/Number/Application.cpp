#include "numpch.h"
#include "Application.h"

#include "Number/Events/ApplicationEvent.h"

#include "Number/Renderer/Renderer.h"
#include "Number/Renderer/RenderCommand.h"

#include <glad/glad.h>

namespace Number {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

	Application::Application() 
        : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        NUM_CORE_ASSERT(!s_Instance, "Application already exists");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create()); 
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        m_VertexArray.reset(VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.2f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.8f, 0.2f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f
        };

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };

        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);



        m_SquareVertexArray.reset(VertexArray::Create());

        float squareVertices[4 * 3] = {
            -0.8f, -0.8f, 0.0f,
             0.8f, -0.8f, 0.0f,
             0.8f,  0.8f, 0.0f,
            -0.8f,  0.8f, 0.0f
        };

        BufferLayout squareLayout = {
            { ShaderDataType::Float3, "a_Position" }
        };

        std::shared_ptr<VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVertexBuffer->SetLayout(squareLayout);
        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        std::shared_ptr<IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

        std::string vertexSrc =  R"(
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

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

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

        m_SquareShader.reset(new Shader(squareVertexSrc, squareFragmentSrc));
	}
    
	Application::~Application() {

	}

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }
 
	void Application::Run() {
        while (m_Running)
        {
            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            RenderCommand::Clear(); 

            Renderer::BeginScene(m_Camera);

            m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
            m_Camera.SetRotation(45.0f);

            Renderer::Submit(m_SquareShader, m_SquareVertexArray);
            Renderer::Submit(m_Shader, m_VertexArray);

            Renderer::EndScene();

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();
            m_Window->OnUpdate();
        }
	}

    bool Application::OnWindowClosed(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}