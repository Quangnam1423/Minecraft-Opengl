#include "Camera.h"

Camera::Camera(glm::vec3 _position, glm::vec3 _worldUp, glm::vec3 _cameraTarget) : Yaw(YAW), Pitch(PITCH),
MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    cameraPosition = _position;
    worldUp = _worldUp;
    cameraTarget = _cameraTarget;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}


void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
    {
        cameraPosition[0] += cameraDirection[0] * velocity;
        cameraPosition[2] += cameraDirection[2] * velocity;
    }

    if (direction == BACKWARD)
    {
        cameraPosition[0] -= cameraDirection[0] * velocity;
        cameraPosition[2] -= cameraDirection[2] * velocity;
    }
    if (direction == LEFT)
    {
        cameraPosition[0] -= cameraRight[0] * velocity;
        cameraPosition[2] -= cameraRight[2] * velocity;
    }

    if (direction == RIGHT)
    {
        cameraPosition[0] += cameraRight[0] * velocity;
        cameraPosition[2] += cameraRight[2] * velocity;
    }
    if (direction == JUMP)
    {
        cameraPosition[1] += worldUp[1] * velocity;
    }
    cameraTarget = cameraPosition + cameraDirection;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw -= xoffset;
    Pitch -= yoffset;
    if (Pitch < -89.0f)
        Pitch = -89.0f;
    if (Pitch > 89.0f)
        Pitch = 89.0f;

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
    glm::vec3 front(1.0f);
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    cameraDirection = glm::normalize(front);
    cameraTarget = cameraPosition + cameraDirection;
    cameraRight = glm::normalize(glm::cross(cameraDirection, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraDirection));
}