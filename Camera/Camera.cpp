#include "Camera.h"

Camera::Camera(float fov, float width, float height) {
	UpVector = glm::vec3(0.0, 1.0, 0.0);
	DirVector = glm::vec3(0.0, 0.0, -1.0);
	PosVector = glm::vec3(0.0, 0.0, 3.0);
	RightVector = glm::vec3(1.0, 0.0, 0.0);
	fieldOfView = fov;
	aspectRatio = width / height;
	yaw = -90.0f;
	pitch = 0.0f;
	rotationSensitivity = 0.2f;
	movementSensitivity = 0.1f;
	lastXPos = 0;
	lastYPos = 0;
	hasMoved = false;
}

bool Camera::NewDirection(glm::vec3 dir) {
	DirVector = glm::normalize(dir);
	RightVector = glm::cross(DirVector, UpVector);
	RightVector = glm::normalize(RightVector);
	return true;
}

bool Camera::NewDirection(float x, float y, float z) {
	DirVector = glm::normalize(glm::vec3(x, y, z));
	RightVector = glm::cross(DirVector, UpVector);
	RightVector = glm::normalize(RightVector);
	return true;
}

bool Camera::NewPos(glm::vec3 pos) {
	PosVector = pos;
	return true;
}

bool Camera::NewPos(float x, float y, float z) {
	PosVector = glm::vec3(x, y, z);
	return true;
}

bool Camera::NewAspectRatio(float width, float height) {
	aspectRatio = width / height;
	return true;
}

bool Camera::NewSensitivity(float rotationSens, float movementSens) {
	rotationSensitivity = rotationSens;
	movementSensitivity = movementSens;
	return true;
}

bool Camera::NewRotationSensitivity(float rotationSens) { 
	rotationSensitivity = rotationSens;
	return true;
}

bool Camera::NewMovementSensitivity(float movementSens) {
	movementSensitivity = movementSens;
	return true;
}

float Camera::GetMovementSensitivity() { return movementSensitivity; }

float Camera::GetRotationSensitivity() { return rotationSensitivity; }

bool Camera::UpdateFOV(float fov) {
	fieldOfView = fov;
	return true;
}

bool Camera::MoveCamera(CameraMovement direction) {
	if (direction == CameraMovement::FORWARD)
		PosVector += movementSensitivity * DirVector;
	else if (direction == CameraMovement::BACKWARD)
		PosVector -= movementSensitivity * DirVector;
	else if (direction == CameraMovement::LEFT)
		PosVector -= movementSensitivity * RightVector;
	else if (direction == CameraMovement::RIGHT)
		PosVector += movementSensitivity * RightVector;

	return true;
}

bool Camera::MoveDir(float xPos, float yPos) {
	// on first move, do not move camera to prevent direction from moving around wildly
	if (!hasMoved) {
		hasMoved = true;
		lastXPos = xPos;
		lastYPos = yPos;
	}
	float xDist = xPos - lastXPos;
	float yDist = lastYPos - yPos;
	yaw += rotationSensitivity * xDist;
	pitch += rotationSensitivity * yDist;
	if (pitch >= 89.0f)
		pitch = 89.0f;
	else if (pitch <= -89.0f)
		pitch = -89.0f;
	std::cout << "Yaw: " << yaw << " Pitch: " << pitch << "\n";

	// Create new direction vectors
	DirVector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	DirVector.y = sin(glm::radians(pitch));
	DirVector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	DirVector = glm::normalize(DirVector);

	// UpVector is the the world up vector, so we do not need to recalculate it
	// RightVecotr depends on DirVector, so we find it
	RightVector = glm::cross(DirVector, UpVector);
	RightVector = glm::normalize(RightVector);

	// Change for next movement
	lastXPos = xPos;
	lastYPos = yPos;

	return true;
}

glm::vec3 Camera::Pos() {
	return PosVector;
}

glm::vec3 Camera::Dir() {
	return DirVector;
}

glm::vec3 Camera::Up() {
	return UpVector;
}

glm::mat4 Camera::ViewMatrix() {
	return glm::lookAt(PosVector, PosVector + DirVector, UpVector);
}

glm::mat4 Camera::PerspectiveMatrix() {
	// TODO: add options for defining near and far planes
	return glm::perspective(glm::radians(fieldOfView), aspectRatio, 0.1f, 100.0f);
}