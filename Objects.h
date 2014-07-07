#include "Header.h"
using namespace std;



class Objects
{
	struct SVertex
	{
		GLfloat x, y, z;
		GLfloat r, g, b;
	};
public:
	Objects();
	~Objects();
	void CalculateUmbrellaVertices(int PointRows, int PointsPerRow);
	void CalculateUmbrellaIndices(int PointRows, int PointsPerRow);
	void CalculateUmbrellaNormals();
	void AnimateUmbrella();
	void DrawUmbrella();
	void CalculateRopeVertices(int PointRows, int PointsPerRow);
	void CalculateRopeIndices(int PointRows, int PointsPerRow);
	void CalculateRopeNormals();
	void MoveUmbrellaY(float move);
	void MoveUmbrellaZ(float move);
	void MoveUmbrellaX(float move);
	void DrawTwist();
	void fallTwist();
	void DrawGround();
	void DrawWalls();
	void initTextures();
	GLuint loadImage(const char* theFileName, int h, int w);

	// parasol //////////////////
	float ubrellahigh = 2.5f;
	float umbrellaX = 0.0f, umbrellaY = 2.5f, umbrellaZ = 0.0f;
	float dX = 0.0f, dY = 0.0f, dZ = 0.0f;
	SVertex * Vertices;
	int NumVertices;
	vector<GLuint>  IndexVect;
	GLuint * Indices;
	int NumIndices;
		//tekstury
	GLuint umbrellaTexture;
	GLfloat * umbrellaTex;
	vector <GLfloat> umbrelaTexVect;
		// normalne
	GLfloat * umbrellaNormals;
		//animacja
	double AnimationUmbrella = -0.3;
	int AnimationUmbrellaFlag1 = 1;
	float startFishHigh = 2.5f;

	// nitki //////////////////
	SVertex * VerticesTwist;
	int NumVerticesTwist;
	vector <GLuint> IndexVectTwist;
	GLuint * IndicesTwist;
	int NumIndicesTwist;
	GLuint twistTexture;
	GLfloat * twistTex;
	vector <GLfloat> twistTexVect;
	// sciany //////////////////

	// podloga //////////////////

	// pozostale tekstury
	GLuint groundTexture;
	GLuint wallTexture;
	GLuint ceilingTexture;
};

