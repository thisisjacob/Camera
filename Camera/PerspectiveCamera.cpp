#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float width, float height) {
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

bool PerspectiveCamera::NewDirection(glm::vec3 dir) {
	DirVector = glm::normalize(dir);
	return true;
}

bool PerspectiveCamera::NewDirection(float x, float y, float z) {
	DirVector = glm::normalize(glm::vec3(x, y, z));
	return true;
}

bool PerspectiveCamera::NewPos(glm::vec3 pos) {
	PosVector = pos;
	return true;
}

bool PerspectiveCamera::NewPos(float x, float y, float z) {
	PosVector = glm::vec3(x, y, z);
	return true;
}

bool PerspectiveCamera::NewUp(glm::vec3 up) {
	UpVector = glm::normalize(up);
	return true;
}

bool PerspectiveCamera::NewUp(float x, float y, float z) {
	UpVector = glm::normalize(glm::vec3(x, y, z));
	return true;
}

bool PerspectiveCamera::NewAspectRatio(float width, float height) {
	aspectRatio = width / height;
	return true;
}

bool PerspectiveCamera::UpdateFOV(float fov) {
	fieldOfView = fov;
	return true;
}

bool PerspectiveCamera::MoveCamera(CameraMovement direction) {
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

bool PerspectiveCamera::MoveDir(float xDist, float yDist) {
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
	// Right vector will always have a y of 0
	// How do the Euler angles affect the right vector?
	RightVector.x = cos(glm::radians(yaw + 90)) * cos(glm::radians(pitch - 90));
	RightVector.z = sin(glm::radians(yaw + 90)) * cos(glm::radians(pitch - 90));
	RightVector = glm::normalize(RightVector);
	UpVector = glm::cross(DirVector, RightVector);
	UpVector = glm::normalize(UpVector);
	
	return true;
}

glm::vec3 PerspectiveCamera::Pos() {
	return PosVector;
}

glm::vec3 PerspectiveCamera::Dir() {
	return DirVector;
}

glm::vec3 PerspectiveCamera::Up() {
	return UpVector;
}

glm::mat4 PerspectiveCamera::ViewMatrix() {
	return glm::lookAt(PosVector, PosVector + DirVector, UpVector);
}

glm::mat4 PerspectiveCamera::ProjectionMatrix() {
	// TODO: add options for defining near and far planes
	return glm::perspective(glm::radians(fieldOfView), aspectRatio, 0.1f, 100.0f);
}