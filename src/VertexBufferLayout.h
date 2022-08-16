#pragma once
#include <vector>
#include <GLEW/glew.h>
#include "Common.h"

struct VertexBufferElement 
{
	uint32_t type;
	uint32_t count;
	uint8_t normalized;

	static uint32_t GetSizeOfType(uint32_t type) {
		switch (type) {
		case GL_FLOAT:		   return 4; break;
		case GL_UNSIGNED_INT:  return 4; break;
		case GL_UNSIGNED_BYTE: return 1; break;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_elements;
	uint32_t m_stride;
public:
	VertexBufferLayout()
		: m_stride(0) {}

	template<typename T>
	void Push(uint32_t count) {
		static_assert(false);
	}

	template<>
	void Push<float>(uint32_t count) {
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<uint32_t>(uint32_t count) {
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<uint8_t>(uint32_t count) {
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_elements; } // Might be wrong (ep 14 - 15:10)
	inline uint32_t GetStride() const { return m_stride; }
};

