#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fov, float width, float height) {
	UpVector = glm::vec3(0.0, 1.0, 0.0);
	DirVector = glm::vec3(0.0, 0.0, -1.0);
	PosVector = glm::vec3(0.0, 0.0, 3.0);
	RightVector = glm::vec3(1.0, 0.0, 0.0);
	fieldOfView = fov;
	aspectRatio = width / height;
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
		PosVector += 0.05f * DirVector;
	else if (direction == CameraMovement::BACKWARD)
		PosVector -= 0.05f * DirVector;
	else if (direction == CameraMovement::LEFT)
		PosVector -= 0.05f * RightVector;
	else if (direction == CameraMovement::RIGHT)
		PosVector += 0.05f * RightVector;

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