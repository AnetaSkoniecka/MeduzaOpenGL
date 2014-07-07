#include "Lights.h"


Lights::Lights()
{
	ambient_light0[0] = 0.2;
	ambient_light0[1] = 0.8;
	ambient_light0[2] = 0.8;
	ambient_light0[3] = 1.0;
	diffuse_light0[0] = 0.8f;
	diffuse_light0[1] = 0.8f;
	diffuse_light0[2] = 0.8f;
	diffuse_light0[3] = 1.0f;
	light_pos0[0] = 0.0f;
	light_pos0[1] = 10.5;
	light_pos0[2] = 5.5f;
	light_pos0[3] = 1.0f;
}


Lights::~Lights()
{
}

void Lights::switchOn()
{
	glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT, GL_DIFFUSE);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //Color (0.5, 0.5, 0.5)
	//GLfloat lightPos0[] = { 10.0f, 10.0f, 5.0f, 1.0f }; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);



	putControlWall();
}

void Lights::switchOff()
{
	glDisable(GL_NORMALIZE);
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
}

void Lights::putControlWall()
{
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
	glVertex3f(11.0f, 10.0f, 5.0f);
	glVertex3f(11.0f, 10.0f, 6.0f);
	glVertex3f(11.0f, 11.0f, 6.0f);
	glVertex3f(11.0f, 11.0f, 5.0f);
	glEnd();

	glPushMatrix();
		glutSolidSphere(1, 5, 5);// dokladnie pod parasolem
		glTranslatef(-5.0f, 5.0f, 8.0f);
		glutSolidSphere(1, 5, 5);
		glTranslatef(10.0f, 0.0f, 0.0f);
		glutSolidSphere(1, 5, 5);
		glTranslatef(-5.0f, 0.0f, 8.0f);
		glutSolidSphere(1, 5, 5);
		glTranslatef(0.0f, 0.0f, -24.0f);
		glutSolidSphere(1, 5, 5);
		glTranslatef(10.0f, 0.0f, 0.0f);
		glutSolidSphere(1, 5, 5);
		glTranslatef(0.0f, -4.0f, 0.0f);
		glutSolidSphere(1, 5, 5);
		glTranslatef(-15.0f, 0.0f, 0.0f);
		glutSolidSphere(1, 5, 5);
		glTranslatef(0.0f, 0.0f, 15.0f);
		glutSolidSphere(1, 5, 5);
		glTranslatef(0.0f, 15.0f, 0.0f);
		glutSolidSphere(1, 5, 5);
		glTranslatef(10.0f, 0.0f, 0.0f);
		glutSolidSphere(1, 5, 5);
		glTranslatef(0.0f, 0.0f, -5.0f);
		glutSolidSphere(1, 5, 5);
		glTranslatef(-10.0f, 0.0f, 0.0f);
		glutSolidSphere(1, 5, 5);
		glTranslatef(0.0f, 0.0f, 5.0f);
		glutSolidSphere(1, 5, 5);
		glTranslatef(5.0f, -16.0f, -7.0f);//teraz maciez jest pod parasolem
		//glutSolidSphere(1, 5, 5);
		glFlush();
	glPopMatrix();
}
