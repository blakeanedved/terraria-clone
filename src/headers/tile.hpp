#ifndef _TC_TILE_HPP_
#define _TC_TILE_HPP_
#include "pch.hpp"

// float TileWidth = 0.5f;
// float TileHeight = 0.5f;

class Tile {
private:
	GLuint vaoID;
	GLuint iboID;
	GLuint vboID;
	GLfloat verts[8];
	glm::vec4 color;
	glm::vec2 position;
	int type;

public:
	Tile(float x, float y, int type, glm::vec4 color);
	~Tile();
	auto SetColor(GLuint uniform) -> void;
	auto Render() -> void;
};

#endif