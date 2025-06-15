#pragma once
#include "../Common/Glm.h"

struct Camera {
	void Update();

private:
	glm::vec3 m_position = glm::vec3(0.0f);
	glm::vec3 m_rotation = glm::vec3(0.0f);
	glm::mat4 m_viewMatrix = glm::mat4(1.0f);
};