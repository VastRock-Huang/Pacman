#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")		//ȡ����������̨
#include "GL/glut.h"
#include "main.h"
#include "game_elements.h"
#include "game_func.h"


extern GameConsole gameC;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//glut��ʼ��
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINWIDTH, WINHEIGIHT);	//���ڴ�С
	glutInitWindowPosition(WINPOSX, WINPOSY);	//����λ��
	glutCreateWindow("Pacman V1.0");	//���ڱ���
	glutDisplayFunc(displayFunc);		//��ʾ����
	glutTimerFunc(fpsScale, timerFunc, 1);		//��ʱ������ʾ����
	glutReshapeFunc(reshapeFunc);		//���ڴ�С�仯���ú���

	glutKeyboardFunc(keyboardFunc);		//����������Ӧ
	glutKeyboardUpFunc(keyboardUpFunc);		//����̧��
	glutSpecialFunc(specialKeyFunc);	//���ⰴ��������Ӧ
	glutSpecialUpFunc(specialKeyUpFunc);	//���ⰴ��̧��
	glutMouseFunc(mouseFunc);
	glutMainLoop();		//��ѭ��

	return 0;
}



bool Coord::operator<(const Coord& c) const
{
	if (x == c.x)
		return y < c.y;
	return x < c.x;
}
