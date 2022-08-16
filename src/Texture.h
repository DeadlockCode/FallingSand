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
	~Texture();

	void Bind(uint32_t slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
};

