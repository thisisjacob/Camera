#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CameraEnums.h"

class PerspectiveCamera {
private:
	glm::vec3 UpVector;
	glm::vec3 DirVector;
	glm::vec3 PosVector;
	glm::vec3 RightVector;
	float aspectRatio;
	float fieldOfView;
public:
	PerspectiveCamera(float fov, float width, float height);
	bool NewDirection(glm::vec3 dir);
	bool NewDirection(float x, float y, float z);
	bool NewPos(glm::vec3 pos);
	bool NewPos(float x, float y, float z);
	bool NewUp(glm::vec3 up);
	bool NewUp(float x, float y, float z);
	bool NewAspectRatio(float width, float height);
	bool UpdateFOV(float fov);
	bool MoveCamera(CameraMovement direction);
	glm::vec3 Pos();
	glm::vec3 Dir();
	glm::vec3 Up();
	glm::mat4 ViewMatrix();
	glm::mat4 ProjectionMatrix();
};