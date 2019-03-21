#include "headers/camera.hpp"

Camera::Camera(glm::vec3 pos, glm::vec4 viewport) {
    this->projection = glm::ortho(viewport[0], viewport[1], viewport[2],
                                  viewport[3], -1.0f, 1.0f);

    this->view = glm::translate(glm::mat4(1.0f), -pos);

    this->model = glm::mat4(1.0f);

    this->MVP = this->projection * this->view * this->model;
}

Camera::~Camera() {}

auto Camera::Move(glm::vec3 deltas) -> void {
    this->view = glm::translate(this->view, -deltas);
    this->MVP = this->projection * this->view * this->model;
}