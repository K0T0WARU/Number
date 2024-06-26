#include "numpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Number {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case Number::ShaderDataType::Float:    return GL_FLOAT;
            case Number::ShaderDataType::Float2:   return GL_FLOAT;
            case Number::ShaderDataType::Float3:   return GL_FLOAT;
            case Number::ShaderDataType::Float4:   return GL_FLOAT;
            case Number::ShaderDataType::Mat3:     return GL_FLOAT;
            case Number::ShaderDataType::Mat4:     return GL_FLOAT;
            case Number::ShaderDataType::Int:      return GL_INT;
            case Number::ShaderDataType::Int2:     return GL_INT;
            case Number::ShaderDataType::Int3:     return GL_INT;
            case Number::ShaderDataType::Int4:     return GL_INT;
            case Number::ShaderDataType::Bool:     return GL_BOOL;
        }

        NUM_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        NUM_PROFILE_FUNCTION();

        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        NUM_PROFILE_FUNCTION();

        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        NUM_PROFILE_FUNCTION();

        NUM_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.Offset
            );
            index++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        NUM_PROFILE_FUNCTION();

        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }

}