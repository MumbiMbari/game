
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


