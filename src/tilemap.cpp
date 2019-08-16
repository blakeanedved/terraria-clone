#include "headers/tilemap.hpp"
#include "headers/camera.hpp"
#include "headers/noisegenerator.hpp"
#include "headers/player.hpp"

extern std::unique_ptr<NoiseGenerator> noisegen;
extern std::unique_ptr<Player> player;
extern std::unique_ptr<Camera> camera;

const auto AMOUNT_OF_TILES = 2;
const auto TERRAIN_MAX_HEIGHT = 130;
const auto TERRAIN_MIN_HEIGHT = 110;
const auto SKY_LEVEL = 40;

TileMap::TileMap(int width, int height) {
    this->hTiles =
        static_cast<int>(static_cast<float>(width) / this->TILE_SIZE) + 2;
    this->vTiles =
        static_cast<int>(static_cast<float>(height) / this->TILE_SIZE) + 2;

    std::cout << this->hTiles << "," << this->vTiles << std::endl;

    for (int i = 0; i < this->vTiles; i++) {
        this->tiles.push_back(std::vector<int>());
        for (int j = 0; j < this->hTiles; j++)
            this->tiles[i].push_back(-1);
    }

    this->noiseX = rand() % 100000;
    this->noiseY = rand() % 100000;
    for (int i = 0; i < this->hTiles; i++) {
        this->noiseX += this->TILE_SIZE;
        this->GenerateColumn(this->noiseX, i);
    }

    this->shader = std::make_unique<Shader>("src/shaders/tile/vert.glsl",
                                            "src/shaders/tile/frag.glsl");
    this->shader->Bind();
    this->shader->AddUniform("MVP");
    this->shader->AddUniform("u_Texture");
    this->shader->SetUniform("MVP", camera->MVP);
    this->shader->SetUniform("u_Texture", 0);

    for (int t = 0; t < AMOUNT_OF_TILES; t++) {
        this->textures.push_back(std::make_unique<Texture>(
            "resources/images/" + std::to_string(t) + ".png"));
    }
}

TileMap::~TileMap() {}

auto TileMap::Render() -> void {
    std::vector<std::vector<GLfloat>> tileVBOs(AMOUNT_OF_TILES,
                                               std::vector<GLfloat>());
    std::vector<std::vector<GLuint>> tileIBOs(AMOUNT_OF_TILES,
                                              std::vector<GLuint>());
    std::vector<int> currentIBOTiles(AMOUNT_OF_TILES, 0);
    int t;

    this->offset = glm::vec2(-player->GetWorldX(), -player->GetWorldY());

    for (int i = 0; i < this->vTiles; i++) {
        for (int j = 0; j < this->hTiles; j++) {
            if (this->tiles[i][j] != -1) {
                t = this->tiles[i][j];
                tileVBOs[t].push_back(j * this->TILE_SIZE + this->offset.x);
                tileVBOs[t].push_back(i * this->TILE_SIZE + this->offset.y);
                tileVBOs[t].push_back(0.0f);
                tileVBOs[t].push_back(0.0f);
                tileVBOs[t].push_back((j + 1) * this->TILE_SIZE +
                                      this->offset.x);
                tileVBOs[t].push_back(i * this->TILE_SIZE + this->offset.y);
                tileVBOs[t].push_back(1.0f);
                tileVBOs[t].push_back(0.0f);
                tileVBOs[t].push_back(j * this->TILE_SIZE + this->offset.x);
                tileVBOs[t].push_back((i + 1) * this->TILE_SIZE +
                                      this->offset.y);
                tileVBOs[t].push_back(0.0f);
                tileVBOs[t].push_back(1.0f);
                tileVBOs[t].push_back((j + 1) * this->TILE_SIZE +
                                      this->offset.x);
                tileVBOs[t].push_back((i + 1) * this->TILE_SIZE +
                                      this->offset.y);
                tileVBOs[t].push_back(1.0f);
                tileVBOs[t].push_back(1.0f);

                tileIBOs[t].push_back(currentIBOTiles[t]);
                tileIBOs[t].push_back(currentIBOTiles[t] + 1);
                tileIBOs[t].push_back(currentIBOTiles[t] + 2);
                tileIBOs[t].push_back(currentIBOTiles[t] + 1);
                tileIBOs[t].push_back(currentIBOTiles[t] + 2);
                tileIBOs[t].push_back(currentIBOTiles[t] + 3);

                currentIBOTiles[t] += 4;
            }
        }
    }

    this->shader->Bind();

    for (int t = 0; t < AMOUNT_OF_TILES; t++) {
        if (tileVBOs[t].size() > 0) {
            GLuint vao;
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            GLuint vbo;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, tileVBOs[t].size() * sizeof(GLfloat),
                         &tileVBOs[t][0], GL_DYNAMIC_DRAW);

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
                         tileIBOs[t].size() * sizeof(GLuint), &tileIBOs[t][0],
                         GL_STATIC_DRAW);

            this->textures[t]->Bind();

            glBindVertexArray(vao); // NOT SURE IF THESE TWO LINES ARE NEEDED
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // ^
            glDrawElements(GL_TRIANGLES, tileIBOs[t].size(), GL_UNSIGNED_INT,
                           nullptr);
        }
    }
}

auto TileMap::GenerateColumn(float noiseColumn, int tileColumn) -> void {
#warning TODO: actual world design
    int value = noisegen->Get(0, noiseColumn, 0, TERRAIN_MIN_HEIGHT,
                              TERRAIN_MAX_HEIGHT);

    if (value >= player->GetTileY() &&
        value < player->GetTileY() + this->vTiles)
        this->tiles[value - player->GetTileY()][tileColumn] = 1;

    for (int i = value - player->GetTileY() - 1; i >= 0; i--) {
        this->tiles[i][tileColumn] = 0;
    }

    // This would be for setting sky tiles
    // for (int i = value + 1; i < this->vTiles; i++) {
    //     this->tiles[i][tileColumn] = -1;
    // }
}

auto TileMap::GetTileSize() -> float { return this->TILE_SIZE; }

auto TileMap::IncrementColumn() -> void {
    for (auto &row : this->tiles) {
        row.erase(row.begin());
        row.push_back(-1);
    }

    this->noiseX += this->TILE_SIZE;
    this->GenerateColumn(this->noiseX, this->hTiles - 1);
}

auto TileMap::DecrementColumn() -> void {
    for (auto &row : this->tiles) {
        row.pop_back();
        row.insert(row.begin(), -1);
    }

    this->noiseX -= this->TILE_SIZE;
    this->GenerateColumn(this->noiseX - (this->TILE_SIZE * this->hTiles), 0);
}

auto TileMap::IncrementRow() -> void {
    std::vector<int> temp;
    this->noiseX -= (this->TILE_SIZE * (this->hTiles + 1.0f));
    for (int i = 0; i < this->hTiles; i++) {
        this->noiseX += this->TILE_SIZE;
        int value = noisegen->Get(0, this->noiseX, 0, TERRAIN_MIN_HEIGHT,
                                  TERRAIN_MAX_HEIGHT);

        if (value == player->GetTileY())
            temp.push_back(1);
        else if (value > player->GetTileY())
            temp.push_back(-1);
        else
            temp.push_back(0);
    }
    this->tiles.push_back(temp);
    this->tiles.erase(this->tiles.begin());
}
auto TileMap::DecrementRow() -> void {
    std::vector<int> temp;
    this->noiseX -= (this->TILE_SIZE * (this->hTiles + 1.0f));
    for (int i = 0; i < this->hTiles; i++) {
        this->noiseX += this->TILE_SIZE;
        int value = noisegen->Get(0, this->noiseX, 0, TERRAIN_MIN_HEIGHT,
                                  TERRAIN_MAX_HEIGHT);

        if (value == (player->GetTileY() + this->hTiles - 1))
            temp.push_back(1);
        else if (value > (player->GetTileY() + this->hTiles - 1))
            temp.push_back(-1);
        else
            temp.push_back(0);
    }
    this->tiles.insert(this->tiles.begin(), temp);
    this->tiles.pop_back();
}

auto TileMap::GetWorldTile(int tileColumn, int tileRow) -> int {
    int grassValue =
        noisegen->Get(tileColumn * this->TILE_SIZE, tileRow * this->TILE_SIZE,
                      0.f, TERRAIN_MIN_HEIGHT, TERRAIN_MAX_HEIGHT);
    return grassValue;
}