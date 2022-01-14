#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PerspectiveCamera {
private:
	glm::vec3 UpVector;
	glm::vec3 DirVector;
	glm::vec3 PosVector;
	float aspectRatio;
	float fieldOfView;
public:
	PerspectiveCamera();
	bool NewDirection(glm::vec3);
	bool NewDirection(float x, float y, float z);
	bool NewPos(glm::vec3);
	bool NewPos(float x, float y, float z);
	bool NewUp(glm::vec3);
	bool NewUp(float x, float y, float z);
	glm::vec3 Pos();
	glm::vec3 Dir();
	glm::vec3 Up();
	glm::mat4 ViewMatrix();
	glm::mat4 ProjectionMatrix();
};