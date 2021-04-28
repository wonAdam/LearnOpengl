#include "Camera.h"

#include "Game.h"


Camera::Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up, float yaw, float pitch)
    : _movementSpeed(SPEED), _mouseSensitivity(SENSITIVITY), _zoom(ZOOM), GameObject("Camera", position, forward, up)
{
    _yaw = yaw;
    _pitch = pitch;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(_position, _position + _forward, _up);
}

void Camera::ProcessKeyboard(Camera::Camera_Movement direction, float deltaTime)
{
    float velocity = _movementSpeed * deltaTime;
    if (direction == FORWARD)
        _position += _forward * velocity;
    if (direction == BACKWARD)
        _position -= _forward * velocity;
    if (direction == LEFT)
        _position -= glm::cross(_forward, _up) * velocity;
    if (direction == RIGHT)
        _position += glm::cross(_forward, _up) * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;

    _yaw += xoffset;
    _pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (_pitch > 89.0f)
            _pitch = 89.0f;
        if (_pitch < -89.0f)
            _pitch = -89.0f;
    }
}

void Camera::ProcessMouseScroll(float yoffset)
{
    /*_zoom -= (float)yoffset;
    if (_zoom < 1.0f)
        _zoom = 1.0f;
    if (_zoom > 45.0f)
        _zoom = 45.0f;*/

    _movementSpeed += (float)yoffset;
    if (_movementSpeed < 10.0f)
        _movementSpeed = 10.0f;
    if (_movementSpeed > 300.0f)
        _movementSpeed = 300.0f;
}

void Camera::Update(float deltaTime)
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _forward = glm::normalize(front);
    // also re-calculate the Right and Up vector
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(_forward, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    _up = glm::normalize(glm::cross(right, _forward));
}