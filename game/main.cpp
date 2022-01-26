#include<windows.h>

#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#define GL_SILENCE_DEPRECATION

#define XMAX 1200
#define YMAX 700
#define SPACESHIP_SPEED 20
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3


GLint m_viewport[4];
bool mButtonPressed = false;
float mouseX, mouseY;
enum view { INTRO, MENU, INSTRUCTIONS, GAME, GAMEOVER };
view viewPage = INTRO; // initial value
bool keyStates[256] = { false };
bool direction[4] = { false };
bool laser1Dir[2] = { false };
bool laser2Dir[2] = { false };

int alienLife1 = 200;
int alienLife2 = 200;
bool gameOver = false;
float xOne = 500, yOne = 0;
float xTwo = 500, yTwo = 0;
bool laser1 = false, laser2 = false;
GLint CI = 0;
GLfloat a[][2] = { 0,-50, 70,-50, 70,70, -70,70 };
GLfloat LightColor[][3] = { 1,1,0,   0,1,1,   0,1,0 };
GLfloat AlienBody[][2] = { {-4,9}, {-6,0}, {0,0}, {0.5,9}, {0.15,12}, {-14,18}, {-19,10}, {-20,0},{-6,0} };
GLfloat AlienCollar[][2] = { {-9,10.5}, {-6,11}, {-5,12}, {6,18}, {10,20}, {13,23}, {16,30}, {19,39}, {16,38},
						  {10,37}, {-13,39}, {-18,41}, {-20,43}, {-20.5,42}, {-21,30}, {-19.5,23}, {-19,20},
						  {-14,16}, {-15,17},{-13,13},  {-9,10.5} };
GLfloat ALienFace[][2] = { {-6,11}, {-4.5,18}, {0.5,20}, {0.,20.5}, {0.1,19.5}, {1.8,19}, {5,20}, {7,23}, {9,29},
						{6,29.5}, {5,28}, {7,30}, {10,38},{11,38}, {11,40}, {11.5,48}, {10,50.5},{8.5,51}, {6,52},
						{1,51}, {-3,50},{-1,51}, {-3,52}, {-5,52.5}, {-6,52}, {-9,51}, {-10.5,50}, {-12,49}, {-12.5,47},
						{-12,43}, {-13,40}, {-12,38.5}, {-13.5,33},{-15,38},{-14.5,32},  {-14,28}, {-13.5,33}, {-14,28},
						{-13.8,24}, {-13,20}, {-11,19}, {-10.5,12}, {-6,11} };
GLfloat ALienBeak[][2] = { {-6,21.5}, {-6.5,22}, {-9,21}, {-11,20.5}, {-20,20}, {-14,23}, {-9.5,28}, {-7,27}, {-6,26.5},
						{-4.5,23}, {-4,21}, {-6,19.5}, {-8.5,19}, {-10,19.5}, {-11,20.5} };


void displayRasterText(float x, float y, float z, const char* stringToDisplay) {
	glRasterPos3f(x, y, z);
	for (const char* c = stringToDisplay; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

void init()
{

	glClearColor(0.0, 0.0, 0.0, 0);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-1200, 1200, -700, 700);                   //<-----CHANGE THIS TO GET EXTRA SPACE
//  gluOrtho2D(-200,200,-200,200);
	glMatrixMode(GL_MODELVIEW);

}

void introScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);


	displayRasterText(-125, 225, 0.0, "Space Shooter");
	glColor3f(1.0, 0.7, 0.8);

	displayRasterText(-130, 80, 0.0, "SHOOTERS");
	glColor3f(1.0, 0.0, 0.0);
	displayRasterText(-800, -100, 0.0, " STUDENT NAMES");
	glColor3f(1.0, 1.0, 1.0);
	displayRasterText(-800, -200, 0.0, " Frankline Mutwa");
	displayRasterText(-800, -285, 0.0, " Regina Mbari");
	glColor3f(1.0, 0.0, 0.0);

	displayRasterText(-300, -550, 0.0, "Press ENTER to start the game");
	glFlush();
	glutSwapBuffers();
}
void startScreenDisplay()
{
	glLineWidth(10);
	//SetDisplayMode(MENU_SCREEN);

	glVertex3f(0.05f, 0.05f, 0.0f);
	glVertex3f(0.35f, 0.05f, 0.0f);
	glVertex3f(0.40f, 0.35f, 0.0f);
	glVertex3f(0.00f, 0.35f, 0.0f);

	glEnd();

	glColor3f(7, 5, 0);
	glBegin(GL_LINE_LOOP);               //Border
	glVertex2f(-750, -500);
	glVertex2f(-750, 550);
	glVertex2f(750, 550);
	glVertex2f(750, -500);
	glEnd();

	glLineWidth(1);

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);				//START GAME PLOYGON
	glVertex2f(-200, 300);
	glVertex2f(-200, 400);
	glVertex2f(200, 400);
	glVertex2f(200, 300);
	glEnd();

glBegin(GL_POLYGON);				//INSTRUCTIONS POLYGON
	glVertex2f(-200, 50);
	glVertex2f(-200, 150);
	glVertex2f(200, 150);
	glVertex2f(200, 50);
	glEnd();

	glBegin(GL_POLYGON);				//QUIT POLYGON
	glVertex2f(-200, -200);
	glVertex2f(-200, -100);
	glVertex2f(200, -100);
	glVertex2f(200, -200);
	glEnd();



