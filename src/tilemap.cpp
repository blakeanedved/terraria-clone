#include "headers/tilemap.hpp"
#include "headers/noisegenerator.hpp"

extern std::unique_ptr<NoiseGenerator> noisegen;

const auto AMOUNT_OF_TILES = 2;
const auto TILE_SIZE = 25.0f;

TileMap::TileMap(int width, int height) {
    this->hTiles = static_cast<int>(static_cast<float>(width) / TILE_SIZE);
    this->vTiles = static_cast<int>(static_cast<float>(height) / TILE_SIZE);

    for (int i = 0; i < this->vTiles; i++) {
        this->tiles.push_back(std::vector<int>());
        for (int j = 0; j < this->hTiles; j++)
            this->tiles[i].push_back(-1);
    }

    int tempArbitraryNumber = 2134;
    for (int i = 0; i < this->hTiles; i++) {
        this->GenerateColumn(tempArbitraryNumber + (i * 20), i);
    }

    for (int t = 0; t < AMOUNT_OF_TILES; t++) {
        this->textures.push_back(std::unique_ptr<Texture>(
            new Texture("resources/images/" + std::to_string(t) + ".png")));
    }
}

TileMap::~TileMap() {}

auto TileMap::Render() -> void {
#warning TODO: make generate all of the VBOs, IBOs, and VAOs at the same time rather than using a useless loop
    GLuint currentIBOTile;
    for (int t = 0; t < AMOUNT_OF_TILES; t++) {
        currentIBOTile = 0;
        std::vector<GLfloat> tileVBO;
        std::vector<GLuint> tileIBO;
        for (int i = 0; i < this->vTiles; i++) {
            for (int j = 0; j < this->hTiles; j++) {
                if (this->tiles[i][j] == t) {
                    tileVBO.push_back(j * TILE_SIZE);
                    tileVBO.push_back(i * TILE_SIZE);
                    tileVBO.push_back(0.0f);
                    tileVBO.push_back(0.0f);
                    tileVBO.push_back((j + 1) * TILE_SIZE);
                    tileVBO.push_back(i * TILE_SIZE);
                    tileVBO.push_back(1.0f);
                    tileVBO.push_back(0.0f);
                    tileVBO.push_back(j * TILE_SIZE);
                    tileVBO.push_back((i + 1) * TILE_SIZE);
                    tileVBO.push_back(0.0f);
                    tileVBO.push_back(1.0f);
                    tileVBO.push_back((j + 1) * TILE_SIZE);
                    tileVBO.push_back((i + 1) * TILE_SIZE);
                    tileVBO.push_back(1.0f);
                    tileVBO.push_back(1.0f);

                    tileIBO.push_back(currentIBOTile);
                    tileIBO.push_back(currentIBOTile + 1);
                    tileIBO.push_back(currentIBOTile + 2);
                    tileIBO.push_back(currentIBOTile + 1);
                    tileIBO.push_back(currentIBOTile + 2);
                    tileIBO.push_back(currentIBOTile + 3);

                    currentIBOTile += 4;
                }
            }
        }

        if (tileVBO.size() > 0) {

            GLuint vao;
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            GLuint vbo;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, tileVBO.size() * sizeof(GLfloat),
                         &tileVBO[0], GL_DYNAMIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4,
                                  (const void *)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4,
                                  (const void *)(2 * sizeof(GLfloat)));

            GLuint ibo;
            glGenBuffers(1, &ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         tileIBO.size() * sizeof(GLuint), &tileIBO[0],
                         GL_STATIC_DRAW);

            this->textures[t]->Bind();

            glBindVertexArray(vao); // NOT SURE IF THESE TWO LINES ARE NEEDED
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // ^
            glDrawElements(GL_TRIANGLES, tileIBO.size(), GL_UNSIGNED_INT,
                           nullptr);
        }
    }
}

auto TileMap::GenerateColumn(int noiseColumn, int tileColumn) -> void {
#warning TODO: actual world design
    int value = noisegen->Get(0, noiseColumn, 0, 10, 50);

    this->tiles[value][tileColumn] = 1;

    for (int i = value - 1; i >= 0; i--) {
        this->tiles[i][tileColumn] = 0;
    }

    for (int i = value + 1; i < this->vTiles; i++) {
        this->tiles[i][tileColumn] = -1;
    }
}