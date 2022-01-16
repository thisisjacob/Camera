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
	rotationSensitivity = 0.4f;
	movementSensitivity = 0.3f;
}

bool Camera::NewDirection(glm::vec3 dir) {
	DirVector = glm::normalize(dir);
	return true;
}

bool Camera::NewDirection(float x, float y, float z) {
	DirVector = glm::normalize(glm::vec3(x, y, z));
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

bool Camera::NewUp(glm::vec3 up) {
	UpVector = glm::normalize(up);
	return true;
}

bool Camera::NewUp(float x, float y, float z) {
	UpVector = glm::normalize(glm::vec3(x, y, z));
	return true;
}

bool Camera::NewAspectRatio(float width, float height) {
	aspectRatio = width / height;
	return true;
}

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

bool Camera::MoveDir(float xDist, float yDist) {
	yaw += rotationSensitivity * xDist;
	pitch += rotationSensitivity * yDist;
	if (pitch >= 90.0f)
		pitch = 90.0f;
	else if (pitch <= -90.0f)
		pitch = -90.0f;
	std::cout << "Yaw: " << yaw << " Pitch: " << pitch << "\n";

	DirVector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	DirVector.y = sin(glm::radians(pitch));
	DirVector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	DirVector = glm::normalize(DirVector);

	//TODO: Update Up and Right vectors
	if (xDist != 0 || yDist != 0)
		auto i = 0;
	// UpVector is the the world up vector, so we do not need to recalculate it
	// RightVecotr depends on DirVector, so we find it
	RightVector = glm::cross(DirVector, UpVector);
	RightVector = glm::normalize(RightVector);
	
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