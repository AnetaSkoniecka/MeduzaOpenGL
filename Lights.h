#include "Header.h"
class Lights
{
public:
	Lights();
	~Lights();
	void switchOn();
	void switchOff();
	void putControlWall();


	GLfloat ambient_light0[4];
	GLfloat diffuse_light0[4];
	GLfloat light_pos0[4];
};

