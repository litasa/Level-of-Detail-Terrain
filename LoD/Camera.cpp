#include "Camera.h"
#include "glm\gtx\rotate_vector.hpp"

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float znear, float zfar)
{
	m_perspective = glm::perspective(fov, aspect, znear, zfar);
	m_position = pos;

	m_forward = glm::vec3(0, 0, 1);
	m_up = glm::vec3(0, 1, 0);
}

void Camera::RotateX(float amount)
{
	glm::vec3 hAxis = glm::cross(glm::vec3(0, 1, 0), m_forward);
	hAxis = glm::normalize(hAxis);

	m_forward = glm::rotate(m_forward, amount, hAxis);
	m_forward = glm::normalize(m_forward);

	m_up = glm::cross(m_forward, hAxis);
	m_up = glm::normalize(m_up);
}

void Camera::RotateY(float amount)
{
	glm::vec3 hAxis = glm::cross(glm::vec3(0, 1, 0), m_forward);
	hAxis = glm::normalize(hAxis);

	m_forward = glm::rotate(m_forward, amount, glm::vec3(0, 1, 0));

	m_up = glm::cross(m_forward, hAxis);
	m_up = glm::normalize(m_up);

}

void Camera::Move(glm::vec3& vec, float amount)
{
	m_position += amount * vec;
}