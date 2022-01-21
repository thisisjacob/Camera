#pragma once
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CameraEnums.h"
#include <iostream>

// This class is used to create a first person camera,
// with support for movement along the x, y, and z axes,
// and rotation along the pitch and yaw Euler angles
class Camera {
private:
	// Camera vectors
	glm::vec3 UpVector;
	glm::vec3 DirVector;
	glm::vec3 PosVector;
	glm::vec3 RightVector;
	// View settings
	float aspectRatio;
	float fieldOfView;
	// Rotation
	float yaw;
	float pitch;
	// Speed of camera alteration
	float rotationSensitivity;
	float movementSensitivity;
	// For determining rotation amount
	float lastXPos, lastYPos;
	bool hasMoved;
public:
	// Creates a new camera, the position, direction and world up vectors should be defined by the New functions
	// fov is the camera's field of view, and width and height are the width and height of the windows
	Camera(float fov, float width, float height);
	bool NewDirection(glm::vec3 dir);
	bool NewDirection(float x, float y, float z);
	bool NewPos(glm::vec3 pos);
	bool NewPos(float x, float y, float z);
	bool NewUp(glm::vec3 up);
	bool NewUp(float x, float y, float z);
	bool NewAspectRatio(float width, float height);
	bool UpdateFOV(float fov);
	// This is used to move the camera's position, relative to the current direction
	bool MoveCamera(CameraMovement direction);
	// This is used to change the camera's direction, it rotates the camera
	// xDist changes the yaw, and yDist changes the pitch
	// Roll cannot be changed
	bool MoveDir(float xPos, float yPos);
	glm::vec3 Pos();
	glm::vec3 Dir();
	glm::vec3 Up();
	// Creates a view matrix from the camera state
	glm::mat4 ViewMatrix();
	// Creates a perspective matrix from distance and window settings
	glm::mat4 PerspectiveMatrix();
};