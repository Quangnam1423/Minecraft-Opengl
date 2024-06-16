#include "Camera.h"

Camera::Camera(glm::vec3 _position, glm::vec3 _worldUp, glm::vec3 _cameraTarget) : Yaw(YAW) , Pitch(PITCH) ,
                                                MovementSpeed(SPEED) , MouseSensitivity(SENSITIVITY) , Zoom(ZOOM)
{
    cameraPosition = _position;
    worldUp = _worldUp;
    cameraTarget = _cameraTarget;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraUp);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        cameraPosition += cameraDirection * velocity;
    if (direction == BACKWARD)
        cameraPosition -= cameraDirection * velocity;
    if (direction == LEFT)
        cameraPosition -= cameraRight * velocity;
    if (direction == RIGHT)
        cameraPosition += cameraRight * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 145.0f)
        Zoom = 145.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    cameraDirection = glm::normalize(front);

    cameraRight = glm::normalize(glm::cross(cameraDirection, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraDirection));
}