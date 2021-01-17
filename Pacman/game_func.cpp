#include <string>
#include <windows.h>
#include "game_func.h"
#include "main.h"
#include "game_elements.h"
#include "GL/glut.h"



GameMap gMap;	//��ͼ
Food food;		//ʳ��
Pacman pacman({ 7,10 });
Ghost ghosts[4] = {		//����
	Ghost({ 13,1 }, { 1,0,0 }),		//red
	Ghost({4,6},{0,1,1}),			//blue
	Ghost({10,8},{1.0,0.6,0}),		//orange
	Ghost({2,13},{1.,0,0.6})		//pink
};
GameConsole gameC;		//��Ϸ����̨
time_t timer;		//��ʱ��


//��ʾ����
void displayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT);	//�������
	gameC.drawFPS();	//����FPS
	//��Ϸ������
	if (gameC.gameActive)
	{
		glEnable(GL_POINT_SMOOTH);		//ͼ�񿹳ݾ�
		gMap.draw();		//���Ƶ�ͼ
		food.draw();		//����ʳ��
		pacman.draw();		//���ƳԶ���
		for (int i = 0; i < Ghost::cnt; i++)		//��������
			ghosts[i].draw();

		gameC.drawScoreBoard(pacman);	//���ƼƷְ�

		//��Ϸδ����
		if(gameC.gameOver)	//��Ϸ����
			gameC.drawGameOver();	//������Ϸ����
	}
	else	//��Ϸδ����
		gameC.drawWelcomeScreen();		//���ƿ�ʼ����
	glutSwapBuffers();
}


//���ڵ��ú���
void timerFunc(int value)
{
	if (gameC.gameActive)
	{
		if (!gameC.gameOver)
		{
			if (food.foodCnt() == 0)	//ʳ��Թ�
			{
				Sleep(1500);
				elementsReset(false);	//���ò���
				gameC.upgrade(ghosts);	//����
			}
			pacman.eatFood(food, gameC);	//�Զ��˳�ʳ��
			pacman.move(gMap);		//�Զ����ƶ�
			pacman.meetGhost(ghosts);		//�Զ�����������ײ
			for (int i = 0; i < Ghost::cnt; i++)		//�����ƶ�
				ghosts[i].autoMove(gMap);

			//��Ϸ��������
			if (gameC.checkGameOver(pacman))
			{
				gameC.gameOver = true;
				timer = time(nullptr);	//���¼�ʱ��
			}
		}
		else if (time(nullptr) - timer >= 2)		//2s��������Ϸ��Ϣ
		{
			gameC.saveHiScore();	//�洢��߷�
			//���ò���
			gameC.reset();
			elementsReset(true);
		}
	}
	glutTimerFunc(fpsScale, timerFunc, 1);
	glutPostRedisplay();
}


//����Ԫ�ز���
void elementsReset(bool re)
{	//ghSpeed��ʾ�Ƿ�����������ٶ�
	food.Food::Food();
	pacman.reset({ 7,10 }, re);
	const Coord tmpC[] = { {13, 1}, { 4,6 }, { 10,8 }, { 2,13 } };
	const Color_f tmpclr[] = { { 1,0,0 } ,{ 0,1,1 } ,{ 1.0,0.6,0 },{ 1.,0,0.6 } };
	ghostReset(ghosts, tmpC, tmpclr, re);
	gMap.setColor(re);	//���ĵ�ͼǽ����ɫ
}


//���ڵ�������
void reshapeFunc(int width, int height)
{
	glMatrixMode(GL_PROJECTION);	//����ͶӰ��ʽ
	glLoadIdentity();	//�ָ���ʼ����ϵ
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);		//������ͼ����: x����, y����, ���, �߶�
	glOrtho(0, WINWIDTH, WINHEIGIHT, 0, -1, 1.);	//�����Ӿ���(��,��,��,��,��,Զ)
	glMatrixMode(GL_MODELVIEW);		//����ͶӰ��ʽ: ģ����ͼ
	glLoadIdentity();
}

//��������
void keyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':	//�ո�
		gameC.playFlag = true;
		break;
	case 27:	//Esc
		gameC.GameExit();	//�˳���Ϸ
		break;
	}
}

//̧�𰴼�
void keyboardUpFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		gameC.resetPlayLine();	//�ػ�play����
	}
}

//���ⰴ������
void specialKeyFunc(int key, int x, int y)
{
	switch (key)
	{
	//��������
	case GLUT_KEY_DOWN:
		pacman.downFlag = true;
		break;
	case GLUT_KEY_UP:
		pacman.upFlag = true;
		break;
	case GLUT_KEY_LEFT:
		pacman.leftFlag = true;
		break;
	case GLUT_KEY_RIGHT:
		pacman.rightFlag = true;
	}
}

//���ⰴ��̧��
void specialKeyUpFunc(int key, int x, int y)
{
	switch (key)
	{
	//��������
	case GLUT_KEY_DOWN:
		pacman.downFlag = false;
		break;
	case GLUT_KEY_UP:
		pacman.upFlag = false;
		break;
	case GLUT_KEY_LEFT:
		pacman.leftFlag = false;
		break;
	case GLUT_KEY_RIGHT:
		pacman.rightFlag = false;
	}
}


void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON &&
		x >= WINWIDTH / 2 - 40. && x <= WINWIDTH / 2 + 40 &&
		y >= 365 && y <= 400)
	{
		if (state == GLUT_DOWN)
			gameC.playFlag = true;
		else
			gameC.resetPlayLine();
	}
}


