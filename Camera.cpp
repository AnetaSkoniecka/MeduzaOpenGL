#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::lookAt()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 0.1f, 0.0f);
}

void Camera::rotateMeX(float dangleX)
{
	angleX += dangleX;
	lx = sin(angleX);
	lz = -cos(angleX);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 0.1f, 0.0f);
}

void Camera::moveMeX(float i)
{
	x = x + i*(lx)*0.1;
	//y = y + (ly)*0.1;
	z = z + i*(lz)*0.1;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.0f, 0.0f);
}
void Camera::moveMeY(float i)
{
	y += i;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.0f, 0.0f);
}