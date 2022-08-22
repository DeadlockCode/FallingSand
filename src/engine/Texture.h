#pragma once

#include <GLEW/glew.h>
#include <stdint.h>
#include <string>

class Texture
{
private:
	uint32_t m_rendererID;
	std::string m_filepath;
	uint8_t* m_localBuffer;
	int m_width, m_height, m_bpp;
public:
	Texture(const std::string& filepath);
	Texture(uint32_t width, uint32_t height);
	~Texture();

	void Bind(uint32_t slot = 0) const;
	void Unbind() const;

	void SetPixel(uint32_t index, uint32_t color);
	void SetPixel(uint32_t x, uint32_t y, uint32_t color);
	void SetPixel(uint32_t index, int offset, uint8_t color);
	void SetPixel(uint32_t x, uint32_t y, int offset, uint8_t color);
	void ApplyTextureChanges(uint32_t slot = 0);

	inline uint32_t GetIndex(uint32_t x, uint32_t y) const { return x + y * m_width; }
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
};

