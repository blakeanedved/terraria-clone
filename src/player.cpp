#include "headers/player.hpp"
#include "headers/window.hpp"

extern std::unique_ptr<Window> window;
float playerWidth = 100.0f;
float playerHeight = 100.0f;

Player::Player(glm::vec2 pos) {
    this->pos = pos;
    this->vel = glm::vec2(0.0, 0.0);

    this->texture =
        std::unique_ptr<Texture>(new Texture("resources/images/player.png"));

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

    this->UpdatePos(); // This could probably be changed to this->Update();
                       // since that calls this->UpdatePos();
}

Player::~Player() {}

auto Player::Update(double dt) -> void {
    if (window->IsKeyDown(GLFW_KEY_A)) {
        this->vel.x = -200.0;
    } else if (window->IsKeyDown(GLFW_KEY_D)) {
        this->vel.x = 200.0;
    } else {
        this->vel.x = 0.0;
    }
    if (window->IsKeyDown(GLFW_KEY_S)) {
        this->vel.y = -200.0;
    } else if (window->IsKeyDown(GLFW_KEY_W)) {
        this->vel.y = 200.0;
    } else {
        this->vel.y = 0.0;
    }

    // this->vel.y -= (9.81 * dt);

    this->pos.x += (this->vel.x * dt);
    this->pos.y += (this->vel.y * dt);

    this->UpdatePos();

    std::cout << "Player pos: (" << this->pos.x << "," << this->pos.y << ")"
              << std::endl;
}

auto Player::Render() -> void {
    this->texture->Bind();

    glBindVertexArray(this->vaoID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iboID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

auto Player::UpdatePos() -> void {
    this->VBO[0] = this->pos.x;
    this->VBO[1] = this->pos.y;
    this->VBO[4] = this->pos.x + playerWidth;
    this->VBO[5] = this->pos.y;
    this->VBO[8] = this->pos.x;
    this->VBO[9] = this->pos.y + playerHeight;
    this->VBO[12] = this->pos.x + playerWidth;
    this->VBO[13] = this->pos.y + playerHeight;

    glBindVertexArray(this->vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLfloat), this->VBO,
                 GL_DYNAMIC_DRAW);
}