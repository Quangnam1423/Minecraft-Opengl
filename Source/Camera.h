#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    // camera Attributes
    glm::vec3 cameraPosition;
    glm::vec3 cameraTarget;
    glm::vec3 cameraDirection;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;
    glm::vec3 worldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(glm::vec3 _position , glm::vec3 _worldUp , glm::vec3 _cameraTarget);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();

    // processes input received from any keyboard-like input system. 
    // Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // processes input received from a mouse input system. 
    // Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);

    // processes input received from a mouse scroll-wheel event. 
    //  requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);
    float getZoom() { return this->Zoom; };

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};

