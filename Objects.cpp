#include "Objects.h"


Objects::Objects()
{
	CalculateUmbrellaVertices(16, 16);
	CalculateUmbrellaIndices(16,16);
	CalculateRopeVertices(16, 16);
	CalculateRopeIndices(16, 16);
}

Objects::~Objects()
{
}

void Objects::CalculateUmbrellaVertices(int PointRows, int PointsPerRow)
{
	NumVertices = (PointRows - 2)*PointsPerRow + 2;
	Vertices = new SVertex[NumVertices];
	IndexVect.clear();  //to be sure it is empty
	float x, y, z;
	int i, j;
	double r;
	//narysowanie kopuly
	for (i = 1; i < (PointRows - 1) / 2; i++)
	{
		for (j = 0; j < PointsPerRow; j++)
		{
			y = 1.0 - float(i) / float(PointRows - 1)*2.0;
			r = sin(acos(y));  //radius of the row
			x = r * sin(float(j) / float(PointsPerRow)*PI*2.0);
	
			z = r * cos(float(j) / float(PointsPerRow)*PI*2.0);
			Vertices[(i - 1)*PointsPerRow + j].x = x; 
			Vertices[(i - 1)*PointsPerRow + j].y = y;
			Vertices[(i - 1)*PointsPerRow + j].z = z;
			Vertices[(i - 1)*PointsPerRow + j].r = (float)(i) / float(PointRows);
			Vertices[(i - 1)*PointsPerRow + j].g = 0.7;
			Vertices[(i - 1)*PointsPerRow + j].b = (float)(j) / float(PointsPerRow);
		}
	}
	//narysowanie czesci cylindrycznej
	for (; i < (PointRows - 1) * 3 / 5; i++)
	{
		for (j = 0; j < PointsPerRow; j++)
		{
			y = 1.0 - float(i) / float(PointRows - 1)*2.0;
			x = r * sin(float(j) / float(PointsPerRow)*PI*2.0);
			z = r * cos(float(j) / float(PointsPerRow)*PI*2.0);
			Vertices[(i - 1)*PointsPerRow + j].x = x; 
			Vertices[(i - 1)*PointsPerRow + j].y = y;
			Vertices[(i - 1)*PointsPerRow + j].z = z;
			Vertices[(i - 1)*PointsPerRow + j].r = (float)(i) / float(PointRows);
			Vertices[(i - 1)*PointsPerRow + j].g = 0.7;
			Vertices[(i - 1)*PointsPerRow + j].b = (float)(j) / float(PointsPerRow);
		}
	}
	//narysiwanie czesci ruszajacej sie
	for (; i < (PointRows - 1) ; i++)
	{
		for (j = 0; j < PointsPerRow; j++)
		{
			y = 1.0 - float(i) / float(PointRows - 1)*2.0;
			r = r + 0.01*(AnimationUmbrella);
			x = r * sin(float(j) / float(PointsPerRow)*PI*2.0);
			z = r * cos(float(j) / float(PointsPerRow)*PI*2.0);
			Vertices[(i - 1)*PointsPerRow + j].x = x; 
			Vertices[(i - 1)*PointsPerRow + j].y = y;
			Vertices[(i - 1)*PointsPerRow + j].z = z;
			Vertices[(i - 1)*PointsPerRow + j].r = (float)(i) / float(PointRows);
			Vertices[(i - 1)*PointsPerRow + j].g = 0.7;
			Vertices[(i - 1)*PointsPerRow + j].b = (float)(j) / float(PointsPerRow);
		}
	}
	//The highest and deepest vertices:
	Vertices[(PointRows - 2)*PointsPerRow].x = 0.0;
	Vertices[(PointRows - 2)*PointsPerRow].y = 1.0;
	Vertices[(PointRows - 2)*PointsPerRow].z = 0.0;
	Vertices[(PointRows - 2)*PointsPerRow].r = 1.0;
	Vertices[(PointRows - 2)*PointsPerRow].g = 0.7;
	Vertices[(PointRows - 2)*PointsPerRow].b = 1.0;
	Vertices[(PointRows - 2)*PointsPerRow + 1].x = 0.0;
	Vertices[(PointRows - 2)*PointsPerRow + 1].y = -1.0;
	Vertices[(PointRows - 2)*PointsPerRow + 1].z = 0.0;
	Vertices[(PointRows - 2)*PointsPerRow + 1].r = 1.0;
	Vertices[(PointRows - 2)*PointsPerRow + 1].g = 0.7;
	Vertices[(PointRows - 2)*PointsPerRow + 1].b = 1.0;
}
void Objects::CalculateUmbrellaIndices(int PointRows, int PointsPerRow)
{
	int i, j;
	for (i = 1; i < (PointRows - 2); i++)
	{
		for (j = 0; j < (PointsPerRow - 1); j++)
		{
			IndexVect.push_back((i - 1)*PointsPerRow + j);
			IndexVect.push_back((i - 1)*PointsPerRow + j + 1);
			IndexVect.push_back((i)*PointsPerRow + j);

			IndexVect.push_back((i - 1)*PointsPerRow + j + 1);
			IndexVect.push_back((i)*PointsPerRow + j + 1);
			IndexVect.push_back((i)*PointsPerRow + j);
		}

		IndexVect.push_back((i - 1)*PointsPerRow + PointsPerRow - 1);
		IndexVect.push_back((i - 1)*PointsPerRow);
		IndexVect.push_back((i)*PointsPerRow + j);

		IndexVect.push_back((i)*PointsPerRow);
		IndexVect.push_back((i - 1)*PointsPerRow);
		IndexVect.push_back((i)*PointsPerRow + j);
	}

	//The triangles to the highest and deepest vertices:
	for (j = 0; j< (PointsPerRow - 1); j++)
	{
		IndexVect.push_back(j);
		IndexVect.push_back(j + 1);
		IndexVect.push_back((PointRows - 2)*PointsPerRow);
	}
	IndexVect.push_back(j);
	IndexVect.push_back(0);
	IndexVect.push_back((PointRows - 2)*PointsPerRow);

	for (j = 0; j< (PointsPerRow - 1); j++)
	{
		IndexVect.push_back((PointRows - 3)*PointsPerRow + j);
		IndexVect.push_back((PointRows - 3)*PointsPerRow + j + 1);
		IndexVect.push_back((PointRows - 2)*PointsPerRow + 1);
	}
	IndexVect.push_back((PointRows - 3)*PointsPerRow + j);
	IndexVect.push_back((PointRows - 3)*PointsPerRow);
	IndexVect.push_back((PointRows - 2)*PointsPerRow + 1);

	Indices = new GLuint[IndexVect.size()];  //allocate the required memory
	for (i = 0; i < IndexVect.size(); i++)
	{
		Indices[i] = IndexVect[i];
	}
	NumIndices = IndexVect.size();
}

void Objects::CalculateUmbrellaNormals()
{

}

void Objects::DrawUmbrella()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, umbrellaTexture);

	//glNormalPointer(GL_FLOAT, 0, umbrellaNormals);

	glPushMatrix();
		glVertexPointer(3, GL_FLOAT, sizeof(SVertex), Vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, umbrellaTex);
		glTranslatef(0.0f, umbrellaY+ sin(umbrellaX*2)*0.2 + sin(umbrellaZ*2)*0.2, 0.0f); // ruch do gory i w przypadku ruchu poziomego ruch falowy
		glTranslatef(0.0f, 0.0f, umbrellaZ); // rucho do przodu
		glTranslatef(umbrellaX, 0.0f, 0.0f); // ruch na boki
		if (dX) { glRotatef(-30, 0.0f, 0.0f, 1.0f); } // pochylenie na bok w przypadku ruchu
		glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_INT, Indices);
		glFlush();
		if (dX) { glRotatef(30, 0.0f, 0.0f, 1.0f); }
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
	//glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void Objects::DrawTwist()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, twistTexture);

	glPushMatrix();
	glPushMatrix();
		glVertexPointer(3, GL_FLOAT, sizeof(SVertex), VerticesTwist);
		glTexCoordPointer(2, GL_FLOAT, 0, twistTex);

		glTranslatef(0.0f, -1.2, 0.0f); // dopasowanie wysokosci do parasola
		glTranslatef(0.0f, umbrellaY + sin(umbrellaX * 2)*0.2 + sin(umbrellaZ * 2)*0.2, 0.0f); // ruch do gory i w przypadku ruchu poziomego ruch falowy
		glTranslatef(0.0f, 0.0f, umbrellaZ);
		glTranslatef(umbrellaX, 0.0f, 0.0f);
		glScalef(1, (AnimationUmbrella + 0.7), 1);//skurcz i rozkurcz konczyn
		glRotatef(25.0f, 0.0f, 1.0f, 0.0f);//obrot konczyn

		//jesli meduza sie przemieszcza to parzydelka sie pochylaja
		if (dX) { glRotatef(-30, 0.0f, 0.0f, 1.0f); } // pochylenie na bok w przypadku ruchu

		//ustawienie i narysowanie konczyn
		glTranslatef(-0.4f, 0.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, NumIndicesTwist, GL_UNSIGNED_INT, IndicesTwist);
		glTranslatef(0.8f, 0.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, NumIndicesTwist, GL_UNSIGNED_INT, IndicesTwist);
		glTranslatef(-0.4f, 0.0f, 0.4f);
		glDrawElements(GL_TRIANGLES, NumIndicesTwist, GL_UNSIGNED_INT, IndicesTwist);
		glTranslatef(0.0f, 0.0f, -0.8f);
		glDrawElements(GL_TRIANGLES, NumIndicesTwist, GL_UNSIGNED_INT, IndicesTwist);
		glTranslatef(0.0f, 0.0f, 0.4f);
		glDrawElements(GL_TRIANGLES, NumIndicesTwist, GL_UNSIGNED_INT, IndicesTwist);
		if (dX) { glRotatef(30, 0.0f, 0.0f, 1.0f); } // pochylenie na bok w przypadku ruchu
		glFlush();
	glPopMatrix();
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Objects::DrawGround() {
	 //ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, groundTexture);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-20.0f, 0.0f, -20.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-20.0f, 0.0f, 20.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(20.0f, 0.0f, 20.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(20.0f, 0.0f, -20.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Objects::DrawWalls() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wallTexture);

	// backwall
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-20.0f, 0.0f, -20.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-20.0f, 20.0f, -20.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-20.0f, 20.0f, 20.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-20.0f, 0.0f, 20.0f);
	glEnd();

	// leftwall
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-20.0f, 0.0f, -20.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-20.0f, 20.0f, -20.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(20.0f, 20.0f, -20.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(20.0f, 0.0f, -20.0f);
	glEnd();

	// rightwall
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(20.0f, 0.0f, -20.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(20.0f, 20.0f, -20.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(20.0f, 20.0f, 20.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(20.0f, 0.0f, 20.0f);
	glEnd();

	// frontwall
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-20.0f, 0.0f, 20.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-20.0f, 20.0f, 20.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(20.0f, 20.0f, 20.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(20.0f, 0.0f, 20.0f);
	glEnd();

	// ceiling
	glBindTexture(GL_TEXTURE_2D, ceilingTexture);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-20.0f, 20.0f, -20.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-20.0f, 20.0f, 20.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(20.0f, 20.0f, 20.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(20.0f, 20.0f, -20.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
void Objects::initTextures() {
	umbrellaTexture = loadImage("jftext1.bmp", 100, 100);
	vector <GLuint> umbrelaTexVect;
	float k = 0.0f;
	for (int i = 0; i < NumVertices; i++){
		umbrelaTexVect.push_back(k); if ((i % 3) == 0) { if (k == 0.0f) k = 1.0f; else k = 0.0f; };
		umbrelaTexVect.push_back(k);
	}
	umbrellaTex = new GLfloat[umbrelaTexVect.size()];  //allocate the required memory
	for (int j = 0; j < umbrelaTexVect.size(); j++)
		umbrellaTex[j] = umbrelaTexVect[j];

	twistTexture = loadImage("jftext2.bmp", 100, 100);
	vector <GLuint> twistTexVect;
	k = 0.0f;
	for (int i = 0; i < NumVerticesTwist; i++){
		twistTexVect.push_back(k); if ((i % 3) == 0) { if (k == 0.0f) k = 1.0f; else k = 0.0f; };
		twistTexVect.push_back(k);
	}
	twistTex = new GLfloat[twistTexVect.size()];  //allocate the required memory
	for (int j = 0; j < twistTexVect.size(); j++)
		twistTex[j] = twistTexVect[j];

	groundTexture = loadImage("dno1.bmp", 636, 274);
	wallTexture = loadImage("sciana2.bmp", 636, 302);
	ceilingTexture = loadImage("tafla.bmp", 484, 340);
	cout << "tu\n";
}

GLuint Objects::loadImage(const char* theFileName, int h, int w)
{
	GLuint texture;
	int width, height;
	unsigned char * data;
	FILE * file;
	file = fopen(theFileName, "rb");

	if (file == NULL) return 0;
	width = h;
	height = w;
	data = (unsigned char *)malloc(width * height * 3);
	//int size = fseek(file,);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}
void Objects::AnimateUmbrella()
{
	if (AnimationUmbrella >= 0.3 && AnimationUmbrellaFlag1 == 1)
		AnimationUmbrellaFlag1 = 0;
	if (AnimationUmbrella <= -0.3 && AnimationUmbrellaFlag1 == 0)
		AnimationUmbrellaFlag1 = 1;
	if (AnimationUmbrellaFlag1 == 1)
		AnimationUmbrella += 0.03;
	else
		AnimationUmbrella -= 0.04;
	CalculateUmbrellaVertices(16, 16);
}
void Objects::CalculateRopeVertices(int PointRows, int PointsPerRow)
{
	NumVerticesTwist = (PointRows - 2)*PointsPerRow + 2;
	VerticesTwist = new SVertex[NumVerticesTwist];
	IndexVectTwist.clear();  //to be sure it is empty
	float x, y, z;
	int i, j;
	double r = 0.08;
	for (i = 1; i < (PointRows - 1); i++)
	{
		if (r == 0.08)
			r -= 0.02;
		else
			r += 0.02;
		for (j = 0; j < PointsPerRow; j++)
		{
			y = 1.0 - float(i) / float(PointRows - 1)*2.0;
			x = r * sin(float(j) / float(PointsPerRow)*PI*2.0);
			z = r * cos(float(j) / float(PointsPerRow)*PI*2.0);
			VerticesTwist[(i - 1)*PointsPerRow + j].x = x;
			VerticesTwist[(i - 1)*PointsPerRow + j].y = y;
			VerticesTwist[(i - 1)*PointsPerRow + j].z = z;
			VerticesTwist[(i - 1)*PointsPerRow + j].r = (float)(i) / float(PointRows);
			VerticesTwist[(i - 1)*PointsPerRow + j].g = 0.7;
			VerticesTwist[(i - 1)*PointsPerRow + j].b = (float)(j) / float(PointsPerRow);
		}
	}

	//The highest and deepest vertices:
	VerticesTwist[(PointRows - 2)*PointsPerRow].x = 0.0;
	VerticesTwist[(PointRows - 2)*PointsPerRow].y = 1.0;
	VerticesTwist[(PointRows - 2)*PointsPerRow].z = 0.0;
	VerticesTwist[(PointRows - 2)*PointsPerRow].r = 1.0;
	VerticesTwist[(PointRows - 2)*PointsPerRow].g = 0.7;
	VerticesTwist[(PointRows - 2)*PointsPerRow].b = 1.0;
	VerticesTwist[(PointRows - 2)*PointsPerRow + 1].x = 0.0;
	VerticesTwist[(PointRows - 2)*PointsPerRow + 1].y = -1.0;
	VerticesTwist[(PointRows - 2)*PointsPerRow + 1].z = 0.0;
	VerticesTwist[(PointRows - 2)*PointsPerRow + 1].r = 1.0;
	VerticesTwist[(PointRows - 2)*PointsPerRow + 1].g = 0.7;
	VerticesTwist[(PointRows - 2)*PointsPerRow + 1].b = 1.0;
}
void Objects::CalculateRopeIndices(int PointRows, int PointsPerRow)
{
	int i, j;
	for (i = 1; i < (PointRows - 2); i++)
	{
		for (j = 0; j < (PointsPerRow - 1); j++)
		{
			IndexVectTwist.push_back((i - 1)*PointsPerRow + j);
			IndexVectTwist.push_back((i - 1)*PointsPerRow + j + 1);
			IndexVectTwist.push_back((i)*PointsPerRow + j);

			IndexVectTwist.push_back((i - 1)*PointsPerRow + j + 1);
			IndexVectTwist.push_back((i)*PointsPerRow + j + 1);
			IndexVectTwist.push_back((i)*PointsPerRow + j);
		}

		IndexVectTwist.push_back((i - 1)*PointsPerRow + PointsPerRow - 1);
		IndexVectTwist.push_back((i - 1)*PointsPerRow);
		IndexVectTwist.push_back((i)*PointsPerRow + j);

		IndexVectTwist.push_back((i)*PointsPerRow);
		IndexVectTwist.push_back((i - 1)*PointsPerRow);
		IndexVectTwist.push_back((i)*PointsPerRow + j);
	}

	//The triangles to the highest and deepest vertices:
	for (j = 0; j< (PointsPerRow - 1); j++)
	{
		IndexVectTwist.push_back(j);
		IndexVectTwist.push_back(j + 1);
		IndexVectTwist.push_back((PointRows - 2)*PointsPerRow);
	}
	IndexVectTwist.push_back(j);
	IndexVectTwist.push_back(0);
	IndexVectTwist.push_back((PointRows - 2)*PointsPerRow);

	for (j = 0; j< (PointsPerRow - 1); j++)
	{
		IndexVectTwist.push_back((PointRows - 3)*PointsPerRow + j);
		IndexVectTwist.push_back((PointRows - 3)*PointsPerRow + j + 1);
		IndexVectTwist.push_back((PointRows - 2)*PointsPerRow + 1);
	}
	IndexVectTwist.push_back((PointRows - 3)*PointsPerRow + j);
	IndexVectTwist.push_back((PointRows - 3)*PointsPerRow);
	IndexVectTwist.push_back((PointRows - 2)*PointsPerRow + 1);

	IndicesTwist = new GLuint[IndexVectTwist.size()];  //allocate the required memory
	for (i = 0; i < IndexVectTwist.size(); i++)
	{
		IndicesTwist[i] = IndexVectTwist[i];
	}
	NumIndicesTwist = IndexVectTwist.size();
}
void Objects::CalculateRopeNormals()
{

}
void Objects::fallTwist()
{
	if (startFishHigh < umbrellaY) {
		umbrellaY -= 0.01;
	}
}
void Objects::MoveUmbrellaY(float move)
{
	if (move >= 0.0f) {
		if (umbrellaY < 18.0f)
			umbrellaY += move*0.01;
	}
	else if (move < 0.0f) {
		if (umbrellaY > startFishHigh)
			umbrellaY += move*0.01;
	}
}
void Objects::MoveUmbrellaX(float move)
{
	if (move >= 0.0f) {
		if (umbrellaX < 18.0f)
			umbrellaX += move*0.01;
	}
	else if (move < 0.0f) {
		if (umbrellaX > -18.0f)
			umbrellaX += move*0.01;
	}
	dX = move;

}
void Objects::MoveUmbrellaZ(float move)
{
	if (move >= 0.0f) {
		if (umbrellaZ < 18.0f){
			umbrellaZ += move*0.01;
		}
			
	}
	else if (move < 0.0f) {
		if (umbrellaZ > -18.0f)
			umbrellaZ += move*0.01;
	}
}
