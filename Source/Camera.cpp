#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->worldUp = cameraUp;
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, worldUp));
        this->cameraUpDirection = glm::cross(cameraRightDirection, cameraFrontDirection);
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraTarget, cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        switch (direction) 
        {
        case MOVE_FORWARD:
            cameraPosition = cameraPosition + (cameraFrontDirection * speed);
            cameraTarget = cameraPosition + cameraFrontDirection;
            break;
        case MOVE_BACKWARD:
            cameraPosition = cameraPosition - (cameraFrontDirection * speed);
            cameraTarget = cameraPosition + cameraFrontDirection;
            break;
        case MOVE_LEFT:
            cameraPosition = cameraPosition - (cameraRightDirection * speed);
            cameraTarget = cameraPosition + cameraFrontDirection;
            break;
        case MOVE_RIGHT:
            cameraPosition = cameraPosition + (cameraRightDirection * speed);
            cameraTarget = cameraPosition + cameraFrontDirection;
            break;
        }
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        cameraFrontDirection = glm::normalize(glm::vec3(cos(glm::radians(pitch)) * cos(glm::radians(yaw)), sin(glm::radians(pitch)), cos(glm::radians(pitch)) * sin(glm::radians(yaw))));
        cameraTarget = cameraPosition + cameraFrontDirection;
        cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, worldUp));
        cameraUpDirection = glm::cross(cameraRightDirection, cameraFrontDirection);
    }
}