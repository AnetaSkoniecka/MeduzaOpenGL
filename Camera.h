#include "Header.h"
class Camera
{
public:
	Camera();
	~Camera();
	void rotateMeX(float dangleX);
	void moveMeX(float i);
	void moveMeY(float i);
	void lookAt();

	// camera direction
	float lx = 0.0f, ly = 0.1f, lz = -1.0f;
	// camera position 
	float x = 0.0f, y = 1.75f, z = 5.0f;
	float angleX = 0.0f, angleY = 0.0f;

};

