#ifndef _TC_CAMERA_HPP_
#define _TC_CAMERA_HPP_
#include "pch.hpp"

class Camera {
  private:
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;

  public:
    glm::mat4 MVP;

    Camera(glm::vec3 pos, glm::vec4 viewport);
    ~Camera();

    auto Move(glm::vec3 deltas) -> void;
};

#endif