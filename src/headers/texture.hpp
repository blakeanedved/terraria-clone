#ifndef _TC_TEXTURE_HPP_
#define _TC_TEXTURE_HPP_

#include "pch.hpp"

class Texture {
private:
	unsigned char* localBuffer;
	int width, height, channels;
	GLuint textureID;
public:
	Texture(const std::string& filepath);
	~Texture();

	auto Bind(GLuint slot = 0) -> void;
	auto Unbind() -> void;
};

#endif