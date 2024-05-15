#include "numpch.h"
#include "Renderer2D.h"

#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer/RenderCommand.h"

#include <glm/gtc/type_ptr.hpp>

namespace Number {

    struct Renderer2DStorage
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;
    };

    static Renderer2DStorage* s_Data;

    void Renderer2D::Init()
    {
        NUM_PROFILE_FUNCTION();

        s_Data = new Renderer2DStorage();

        s_Data->QuadVertexArray = VertexArray::Create();

        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        BufferLayout squareLayout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoord" },
        };

        Ref<VertexBuffer> squareVertexBuffer;
        squareVertexBuffer = VertexBuffer::Create(squareVertices, sizeof(squareVertices));

        squareVertexBuffer->SetLayout(squareLayout);
        s_Data->QuadVertexArray->AddVertexBuffer(squareVertexBuffer);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        Ref<IndexBuffer> squareIndexBuffer;
        squareIndexBuffer = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        s_Data->QuadVertexArray->SetIndexBuffer(squareIndexBuffer);

        s_Data->WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        NUM_PROFILE_FUNCTION();
        
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        NUM_PROFILE_FUNCTION();

        s_Data->TextureShader->SetFloat4("u_Color", color);
        s_Data->WhiteTexture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f});
        s_Data->TextureShader->SetMat4("u_Transform", transform);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color)
    {
        NUM_PROFILE_FUNCTION();
        
        s_Data->TextureShader->SetFloat4("u_Color", color);
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data->TextureShader->SetMat4("u_Transform", transform);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

}