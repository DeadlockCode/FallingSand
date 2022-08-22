#include "Texture.h"

#include "../vendor/stb/stb_image.h"

Texture::Texture(const std::string& filepath)
	: m_rendererID(0), m_filepath(filepath), m_localBuffer(nullptr), m_width(0), m_height(0), m_bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_bpp, 4);

	glGenTextures(1, &m_rendererID);
	glBindTexture(GL_TEXTURE_2D, m_rendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(uint32_t width, uint32_t height)
	: m_rendererID(0), m_filepath(""), m_localBuffer(nullptr), m_width(width), m_height(height), m_bpp(0)
{
	m_localBuffer = new uint8_t[width * height * 4];

	glGenTextures(1, &m_rendererID);
	glBindTexture(GL_TEXTURE_2D, m_rendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_rendererID);
}

void Texture::Bind(uint32_t slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_rendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetPixel(uint32_t index, uint32_t color)
{
	((uint32_t*)m_localBuffer)[index] = color;
}

void Texture::SetPixel(uint32_t x, uint32_t y, uint32_t color)
{
	((uint32_t*)m_localBuffer)[GetIndex(x, y)] = color;
}

void Texture::SetPixel(uint32_t index, int offset, uint8_t color)
{
	m_localBuffer[index * 4 + offset] = color;
}

void Texture::SetPixel(uint32_t x, uint32_t y, int offset, uint8_t color)
{
	m_localBuffer[GetIndex(x, y) * 4 + offset] = color;
}

void Texture::ApplyTextureChanges(uint32_t slot) {
	//Bind(slot);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
}
