#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera() {
	UpVector = glm::vec3(0.0, 1.0, 0.0);
	DirVector = glm::vec3(0.0, 0.0, 1.0);
	PosVector = glm::vec3(0.0, 0.0, -1.0);
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