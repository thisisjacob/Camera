#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera() {
	UpVector = glm::vec3(0.0, 1.0, 0.0);
	DirVector = glm::vec3(0.0, 0.0, -1.0);
	PosVector = glm::vec3(0.0, 0.0, 3.0);
	fieldOfView = 45.0f;
	aspectRatio = 800.0f / 600.0f;
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