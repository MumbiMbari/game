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

	if (mouseX >= -100 && mouseX <= 100 && mouseY >= 150 && mouseY <= 200) {
		glColor3f(0, 0, 1);
		if (mButtonPressed) {
			alienLife1 = alienLife2 = 100;
			viewPage = GAME;
			mButtonPressed = false;
		}
	}
	else
		glColor3f(0, 0, 0);

	displayRasterText(-100, 340, 0.4, "Start Game");

	if (mouseX >= -100 && mouseX <= 100 && mouseY >= 30 && mouseY <= 80) {
		glColor3f(0, 0, 1);
		if (mButtonPressed) {
			viewPage = INSTRUCTIONS;
			printf("button pressed bitch\n");
			mButtonPressed = false;
		}
	}
	else
		glColor3f(0, 0, 0);
	displayRasterText(-120, 80, 0.4, "Instructions");

	if (mouseX >= -100 && mouseX <= 100 && mouseY >= -90 && mouseY <= -40) {
		glColor3f(0, 0, 1);
		if (mButtonPressed) {
			mButtonPressed = false;
			exit(0);
		}
	}
	else
		glColor3f(0, 0, 0);
	displayRasterText(-100, -170, 0.4, "    Quit");
	glutPostRedisplay();
}

void backButton() {
	if (mouseX <= -450 && mouseX >= -500 && mouseY >= -275 && mouseY <= -250) {
		glColor3f(0, 0, 1);
		if (mButtonPressed) {
			viewPage = MENU;
			mButtonPressed = false;
			//instructionsGame = false;
			glutPostRedisplay();
		}
	}
	else glColor3f(1, 0, 0);
	displayRasterText(-1000, -550, 0, "Back");
}

void instructionsScreenDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//SetDisplayMode(MENU_SCREEN);
	//colorBackground();
	glColor3f(1, 0, 0);
	displayRasterText(-900, 550, 0.4, "INSTRUCTIONS");
	glColor3f(1, 0, 0);
	displayRasterText(-1000, 400, 0.4, "PLAYER 1");
	displayRasterText(200, 400, 0.4, "PLAYER 2");
	glColor3f(1, 1, 1);
	displayRasterText(-1100, 300, 0.4, "Key 'w' to move up.");
	displayRasterText(-1100, 200, 0.4, "Key 's' to move down.");
	displayRasterText(-1100, 100, 0.4, "Key 'd' to move right.");
	displayRasterText(-1100, 0, 0.4, "Key 'a' to move left.");
	displayRasterText(100, 300, 0.4, "Key 'i' to move up.");
	displayRasterText(100, 200, 0.4, "Key 'k' to move down.");
	displayRasterText(100, 100, 0.4, "Key 'j' to move right.");
	displayRasterText(100, 0, 0.4, "Key 'l' to move left.");
	displayRasterText(-1100, -100, 0.4, "Key 'c' to shoot, Use 'w' and 's' to change direction.");
	displayRasterText(100, -100, 0.4, "Key 'm' to shoot, Use 'i' and 'k' to change direction.");
	//displayRasterText(-1100 ,-100 ,0.4 ,"The packet can be placed only when 's' is pressed before.");
	displayRasterText(-1100, -300, 0.4, "The Objective is to kill your opponent.");
	displayRasterText(-1100, -370, 0.4, "Each time a player gets shot, LIFE decreases by 5 points.");
	backButton();
	//if(previousScreen)
	//	nextScreen = false ,previousScreen = false; //as set by backButton()
}

void DrawAlienBody(bool isPlayer1)
{
	if (isPlayer1)
		glColor3f(0, 1, 0);
	else
		glColor3f(1, 5, 0);		//BODY color
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 8; i++)
		glVertex2fv(AlienBody[i]);
	glEnd();

	glColor3f(0, 0, 0);			//BODY Outline
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 8; i++)
		glVertex2fv(AlienBody[i]);
	glEnd();

	glBegin(GL_LINES);                //BODY effect
	glVertex2f(-13, 11);
	glVertex2f(-15, 9);
	glEnd();
}
void DrawAlienCollar()
{
	glColor3f(1, 0, 0);				//COLLAR
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 20; i++)
		glVertex2fv(AlienCollar[i]);
	glEnd();

	glColor3f(0, 0, 0);				//COLLAR outline
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 20; i++)
		glVertex2fv(AlienCollar[i]);
	glEnd();
}
void DrawAlienFace(bool isPlayer1)
{
	//glColor3f(0.6,0.0,0.286);				//FACE
	//glColor3f(0.8,0.2,0.1);
	//glColor3f(0,0.5,1);
	//if(isPlayer1)
	glColor3f(0, 0, 1);
	// else
	// 	glColor3f(0,1,0);

	glBegin(GL_POLYGON);
	for (int i = 0; i <= 42; i++)
		glVertex2fv(ALienFace[i]);
	glEnd();

	glColor3f(0, 0, 0);				//FACE outline
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 42; i++)
		glVertex2fv(ALienFace[i]);
	glEnd();

	glBegin(GL_LINE_STRIP);      //EAR effect
	glVertex2f(3.3, 22);
	glVertex2f(4.4, 23.5);
	glVertex2f(6.3, 26);
	glEnd();
}
void DrawAlienBeak()
{
	glColor3f(1, 1, 0);				//BEAK color
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 14; i++)
		glVertex2fv(ALienBeak[i]);
	glEnd();

	glColor3f(0, 0, 0);				//BEAK outline
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 14; i++)
		glVertex2fv(ALienBeak[i]);
	glEnd();
}
void DrawAlienEyes(bool isPlayer1)
{
	// if(isPlayer1)
	glColor3f(0, 1, 1);
	// else
	// 	glColor3f(0,0,0);

	glPushMatrix();
	glRotated(-10, 0, 0, 1);
	glTranslated(-6, 32.5, 0);      //Left eye
	glScalef(2.5, 4, 0);
	glutSolidSphere(1.5, 20, 30);
	glPopMatrix();

	glPushMatrix();
	glRotated(-1, 0, 0, 1);
	glTranslated(-8, 36, 0);							//Right eye
	glScalef(2.5, 4, 0);
	glutSolidSphere(1.5, 100, 100);
	glPopMatrix();
}
void DrawAlien(bool isPlayer1)
{
	DrawAlienBody(isPlayer1);
	DrawAlienCollar();
	DrawAlienFace(isPlayer1);
	DrawAlienBeak();
	DrawAlienEyes(isPlayer1);
}
void DrawSpaceshipBody(bool isPlayer1)
{
	if (isPlayer1)
		glColor3f(1, 0, 0);			//BASE
	else
		glColor3f(0.5, 0, 0.5);

	glPushMatrix();
	glScalef(70, 20, 1);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();

	glPushMatrix();							//LIGHTS
	glScalef(3, 3, 1);
	glTranslated(-20, 0, 0);			//1
	glColor3fv(LightColor[(CI + 0) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//2
	glColor3fv(LightColor[(CI + 1) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//3
	glColor3fv(LightColor[(CI + 2) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//4
	glColor3fv(LightColor[(CI + 0) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//5
	glColor3fv(LightColor[(CI + 1) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//6
	glColor3fv(LightColor[(CI + 2) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//7
	glColor3fv(LightColor[(CI + 0) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//8
	glColor3fv(LightColor[(CI + 1) % 3]);
	glutSolidSphere(1, 1000, 1000);
	glTranslated(5, 0, 0);					//9
	glColor3fv(LightColor[(CI + 2) % 3]);
	glutSolidSphere(1, 1000, 1000);

	glPopMatrix();
}
void DrawSteeringWheel()
{
	glPushMatrix();
	glLineWidth(3);
	glColor3f(0.20, 0., 0.20);
	glScalef(7, 4, 1);
	glTranslated(-1.9, 5.5, 0);
	glutWireSphere(1, 8, 8);
	glPopMatrix();

}
void DrawSpaceshipDoom()
{
	glColor4f(0.7, 1, 1, 0.0011);
	glPushMatrix();
	glTranslated(0, 30, 0);
	glScalef(35, 50, 1);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();
}

void DrawLaser(int x, int y, bool dir[]) {
	//glPushMatrix();
	int xend = -XMAX, yend = y;
	if (dir[0])
		yend = YMAX;
	else if (dir[1])
		yend = -YMAX;
	glLineWidth(5);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(xend, yend);
	glEnd();
	//glPopMatrix();
}

void SpaceshipCreate(int x, int y, bool isPlayer1) {
	glPushMatrix();
	glTranslated(x, y, 0);
	// if(!checkIfSpaceShipIsSafe() && alienLife1 ){
	// 	alienLife1-=10;
	// 	xStart -= 23;
	// }
	DrawSpaceshipDoom();
	glPushMatrix();
	glTranslated(4, 19, 0);
	DrawAlien(isPlayer1);
	glPopMatrix();
	DrawSteeringWheel();
	DrawSpaceshipBody(isPlayer1);
	// DrawSpaceShipLazer();
	// if(mButtonPressed) {
	// 	DrawLazerBeam();
	// }
	glEnd();
	glPopMatrix();
}
