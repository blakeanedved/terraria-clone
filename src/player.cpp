#include "headers/player.hpp"
#include "headers/tilemap.hpp"
#include "headers/window.hpp"

extern std::unique_ptr<Window> window;
extern std::unique_ptr<TileMap> tm;
float playerWidth = 100.0f;
float playerHeight = 100.0f;

Player::Player(glm::vec2 pos) {
    this->tilePos = pos;
    this->worldPos = glm::vec2(0, 0);
    this->vel = glm::vec2(0.0, 0.0);

    this->texture =
        std::unique_ptr<Texture>(new Texture("resources/images/player.png"));

    float ww = window->Width() / 2.0f, wh = window->Height() / 2.0f;
    float pw = playerWidth / 2.0f, ph = playerHeight / 2.0f;
    this->VBO[0] = ww - pw;
    this->VBO[1] = wh - ph;
    this->VBO[2] = 0.0f;
    this->VBO[3] = 0.0f;
    this->VBO[4] = ww + pw;
    this->VBO[5] = wh - ph;
    this->VBO[6] = 1.0f;
    this->VBO[7] = 0.0f;
    this->VBO[8] = ww - pw;
    this->VBO[9] = wh + ph;
    this->VBO[10] = 0.0f;
    this->VBO[11] = 1.0f;
    this->VBO[12] = ww + pw;
    this->VBO[13] = wh + ph;
    this->VBO[14] = 1.0f;
    this->VBO[15] = 1.0f;

    glGenVertexArrays(1, &this->vaoID);
    glBindVertexArray(this->vaoID);
    glGenBuffers(1, &this->vboID);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLfloat), this->VBO,
                 GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4,
                          (const void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4,
                          (const void *)(2 * sizeof(GLfloat)));

    glGenBuffers(1, &this->iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), this->IBO,
                 GL_STATIC_DRAW);

    // this->UpdatePos(); // This could probably be changed to this->Update();
    // since that calls this->UpdatePos();
}

Player::~Player() {}

auto Player::Update(double dt) -> void {
    if (window->IsKeyDown(GLFW_KEY_A)) {
        this->vel.x = -this->movementSpeed;
    } else if (window->IsKeyDown(GLFW_KEY_D)) {
        this->vel.x = this->movementSpeed;
    } else {
        this->vel.x = 0.0;
    }
    if (window->IsKeyDown(GLFW_KEY_S)) {
        this->vel.y = -this->movementSpeed;
    } else if (window->IsKeyDown(GLFW_KEY_W)) {
        this->vel.y = this->movementSpeed;
    } else {
        this->vel.y = 0.0;
    }

    // this->vel.y -= (9.81 * dt);

    this->worldPos.x += (this->vel.x * dt);
    this->worldPos.y += (this->vel.y * dt);

    if (this->worldPos.x > tm->GetTileSize()) {
        this->worldPos.x -= tm->GetTileSize();
        this->tilePos.x++;
        tm->IncrementColumn();
    } else if (this->worldPos.x < 0) {
        this->worldPos.x += tm->GetTileSize();
        this->tilePos.x--;
        tm->DecrementColumn();
    }
    if (this->worldPos.y > tm->GetTileSize()) {
        this->worldPos.y -= tm->GetTileSize();
        this->tilePos.y++;
        tm->IncrementRow();
    } else if (this->worldPos.y < 0) {
        this->worldPos.y += tm->GetTileSize();
        this->tilePos.y--;
        tm->DecrementRow();
    }
}

auto Player::GetWorldX() -> float { return this->worldPos.x; }
auto Player::GetWorldY() -> float { return this->worldPos.y; }
auto Player::GetTileX() -> int { return this->tilePos.x; }
auto Player::GetTileY() -> int { return this->tilePos.y; }

auto Player::Render() -> void {
    this->texture->Bind();

    glBindVertexArray(this->vaoID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iboID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

// auto Player::UpdatePos() -> void {
//     this->VBO[0] = this->pos.x;
//     this->VBO[1] = this->pos.y;
//     this->VBO[4] = this->pos.x + playerWidth;
//     this->VBO[5] = this->pos.y;
//     this->VBO[8] = this->pos.x;
//     this->VBO[9] = this->pos.y + playerHeight;
//     this->VBO[12] = this->pos.x + playerWidth;
//     this->VBO[13] = this->pos.y + playerHeight;

//     glBindVertexArray(this->vaoID);
//     glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
//     glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLfloat), this->VBO,
//                  GL_DYNAMIC_DRAW);
// }