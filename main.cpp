#include "Header.h"
#include "Lights.h"
#include "Objects.h"
#include "Camera.h"
using namespace std;
/*
Projekt z przedmiotu GKOM
autor: Aneta Skoniecka
Program ma na celu zaprezentowanie wizualizacji meduzy znajduj¹cej siê w zamkniêtym pomieszczeniu.
Meduza sk³ada siê z parasola i nitek zbudowanych na vertexarrays, a œciany s¹ budowane z prostok¹tów.
Ka¿dy element sceny jest oteksturowany - pliki tekstur znajduj¹ siê w folderze z projektem.
Scena oœwietlona jest za pomoc¹ œwiat³a ambient oraz znajduj¹cego siê poœrodku pomieszczenia œwiat³a diffuse.
Mo¿na sterowaæ kamer¹ w celu obejrzenia sceny z ka¿dej strony.
Meduza mozna serowac za pomoc¹ przyciskow F1-F6 (w góre, w dó³ i na boki). Meduza nie mo¿e wyjsc poza pomieszczenie.
Meduza przy poruszaniu siê na boki porusza siê ruchem op³ywowym po torze sinusoidy. Przy pop³yniêciu meduzy do góry, gdy
 przestanie p³yn¹æ to zaczyna swobodnie opadaæ na dó³.

 Sterowanie:
Camera:
KEY_UP - move front
KEY_DOWN - move back
KEY_LEFT - rotate left
KEY_RIGHT - rotate right
O - move up
P - move down
JellyFish:
F1 - up
F2 - down
F3 - move front
F4 - move back
F5 - move left
F6 - move right

Projekt sk³ada siê z plików: main.cpp, camera.cpp, camera.h, objects.cpp, objects.h, lights.cpp, lights.h, header.h, z plików tekstur i folderu z nag³ówkami do bibliotek glut.
*/

Camera camera;
Objects objects;
Lights lights;

// umbrella movement
float moveX = 0.0f, moveY = 0.0f, moveZ = 0.0f, rotateX = 0.0f, rotateY = 0.0f;
// camera movement
float moveCamX = 0.0f, moveCamY = 0.0f, moveCamZ = 0.0f, rotateCamX = 0.0f, rotateCamY = 0.0f;

// window
float h, w;

////
//GLfloat * calculateNormals(GLuint * indices, int num)
//{
//	cout << "num:" << num << "\n";
//	GLfloat * Normals = new GLfloat[num];
//	vector<GLfloat> NormalsVec;
//	SVertex p1, p2, p3; //punkty trojkata
//	SVertex U, V; // wektory posredniczace
//	GLfloat nx, ny, nz; // wspolrzedne normalnej
//	GLuint i1, i2, i3; // wspolrzedne punktow trojkata w tablicy vertices
//	int j = 0;
//	for (int i = 0; i < num;)
//	{
//		i1 = indices[i++];
//		i2 = indices[i++];
//		i3 = indices[i++];
//		p1 = Vertices[i1];
//		p2 = Vertices[i2];
//		p3 = Vertices[i3];
//		U.x = p2.x - p1.x;
//		U.y = p2.y - p1.y;
//		U.z = p2.z - p1.z;
//		V.x = p3.x - p1.x;
//		V.y = p3.y - p1.y;
//		V.z = p3.z - p1.z;
//		nx = U.y * V.z - U.z * V.y;
//		ny = U.z * V.x - U.x * V.z;
//		nz = U.x * V.y - U.y * V.x;
//
//		NormalsVec.push_back(nx);
//		NormalsVec.push_back(ny);
//		NormalsVec.push_back(nz);
//
//		
//		cout << "i1 " << i1 << " i2 " << i2 << " i3 " << i3 ; cout << " nx: " << nx << " ny " << ny << " nz " << nz << "\n";
//	}
//	for (int j = 0; j < num; j++)
//	{
//		Normals[j] = NormalsVec[j];
//	}
//	return Normals;
//}



void changeSize(int w1, int h1)
{
	if (h1 == 0)
		h1 = 1;
	w = w1;
	h = h1;
	float ratio = 1.0f * w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.lookAt();
}
void AnimateFalling(int time) {
	objects.fallTwist();
	glutTimerFunc(120, AnimateFalling, 0);
}
void AnimateUmbrella(int time) {
	objects.AnimateUmbrella();
	glutTimerFunc(30, AnimateUmbrella, 0);
}
void renderScene(void) {
	if (moveCamZ != 0.0f)
		camera.moveMeX(moveCamZ);
	if (rotateCamX != 0.0f) {
		camera.rotateMeX(rotateCamX);
	}
	if (moveY) {
		objects.MoveUmbrellaY(moveY);
	}
	objects.MoveUmbrellaZ(moveZ);
	objects.MoveUmbrellaX(moveX);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//lights.switchOn();
	objects.DrawGround();
	objects.DrawWalls();
	objects.DrawUmbrella();
	objects.DrawTwist();
	//lights.switchOff();
	glutSwapBuffers();
}
void initObjects(void) {
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	objects.initTextures();
}
void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
	if (key == 'p')
		camera.moveMeY(-0.5);
	if (key == 'o')
		camera.moveMeY(0.5);
}
void pressKey(int key, int c, int y) {
	switch (key) {
	case GLUT_KEY_LEFT: rotateCamX = -0.005f; break;
	case GLUT_KEY_RIGHT: rotateCamX = 0.005f; break;
	case GLUT_KEY_UP: moveCamZ = 0.5; break;
	case GLUT_KEY_DOWN: moveCamZ = -0.5; break;
	case GLUT_KEY_F1: moveY += 0.1; break;
	case GLUT_KEY_F2: moveY -= 0.05; break;
	case GLUT_KEY_F3: moveZ += 0.3; break;
	case GLUT_KEY_F4: moveZ -= 0.3; break;
	case GLUT_KEY_F5: moveX += 0.3; break;
	case GLUT_KEY_F6: moveX -= 0.3; break;
	}
}
void releaseKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT: if (rotateCamX < 0.0f)
		rotateCamX = 0.0f;
		break;
	case GLUT_KEY_RIGHT: if (rotateCamX > 0.0f)
		rotateCamX = 0.0f;
		break;
	case GLUT_KEY_UP:     if (moveCamZ > 0.0f)
		moveCamZ = 0.0f;
		break;
	case GLUT_KEY_DOWN: if (moveCamZ < 0.0f)
		moveCamZ = 0.0f;
		break;
	case GLUT_KEY_F1: if (moveY < 0.0f)
		moveY = 0.0f;
		break;
	case GLUT_KEY_F2: if (moveY > 0.0f)
		moveY = 0.0f;
		break;
	case GLUT_KEY_F3: if (moveZ != 0.0f)
		moveZ = 0.0f;
		break;
	}
	moveY = 0.0f;
	moveZ = 0.0f;
	moveX = 0.0f;
}
void initWindow() {
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutCreateWindow("GKOM - meduza");

	initObjects();
	initWindow();

	AnimateUmbrella(0);
	AnimateFalling(0);

	glutMainLoop();

	return(0);
}
