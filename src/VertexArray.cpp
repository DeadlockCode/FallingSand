#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_rendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_rendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
	vb.Bind();

    const auto& elements = layout.GetElements();
    uint32_t offset = 0;
    for (uint32_t i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}

void VertexArray::Bind() const
{
    glBindVertexArray(m_rendererID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
