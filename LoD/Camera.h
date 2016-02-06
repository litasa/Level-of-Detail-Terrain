#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS
#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"
#include "glm\gtx\rotate_vector.hpp"


class Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float znear, float zfar);

	glm::mat4 GetViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	glm::mat4 GetProjectionMatrix() const { return m_perspective; }
	glm::mat4 GetViewMatrix() const { return glm::lookAt(m_position, m_position + m_forward, m_up); }

	void SetPosition(const glm::vec3& pos) { m_position = pos; }
	glm::vec3 GetPosition() const { return m_position; }
	const glm::vec3 GetPosition() { return m_position; }

	void SetForward(const glm::vec3& view) { m_forward = view; }
	glm::vec3 GetForward() { return m_forward; }
	glm::vec3 GetBackwards() { return -m_forward; }

	void RotateX(float amount);
	void RotateY(float amount);

	void Move(glm::vec3& dir, float amount);

	glm::vec3 GetUp() { return m_up; }
	glm::vec3 GetDown() { return -m_up; }
	glm::vec3 GetLeft() { return glm::normalize(glm::cross(m_up, m_forward)); }
	glm::vec3 GetRight() { return -GetLeft(); }

	~Camera() {};

private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;

	glm::vec3 m_forward;
	glm::vec3 m_up;
};

#endif //CAMERA_H