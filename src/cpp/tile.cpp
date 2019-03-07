#include "../headers/tile.hpp"

Tile::Tile(float x, float y, int type, glm::vec4 color){
	this->color = color;
	this->position.x = x;
	this->position.y = y;
	this->type = type;
	this->verts[0] = x;
	this->verts[1] = y;
	this->verts[2] = 0.0f;
	this->verts[3] = 0.0f;
	this->verts[4] = x + 1.0f;
	this->verts[5] = y;
	this->verts[6] = 1.0f;
	this->verts[7] = 0.0f;
	this->verts[8] = x;
	this->verts[9] = y + 1.0f;
	this->verts[10] = 0.0f;
	this->verts[11] = 1.0f;
	this->verts[12] = x + 1.0f;
	this->verts[13] = y + 1.0f;
	this->verts[14] = 1.0f;
	this->verts[15] = 1.0f;

	GLuint indices[] = {
		0, 1, 2,
		1, 2, 3
	};

	glGenVertexArrays(1, &this->vaoID);
	glBindVertexArray(this->vaoID);

	glGenBuffers(1, &this->vboID);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->verts), this->verts, GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (const void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (const void*)(2*sizeof(GLfloat)));

	glGenBuffers(1, &this->iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

Tile::~Tile(){
}

auto Tile::SetColor(GLuint uniform) -> void {
	glUniform4f(uniform, this->color[0], this->color[1], this->color[2], this->color[3]);
}

auto Tile::Render() -> void {
	glBindVertexArray(this->vaoID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iboID);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}