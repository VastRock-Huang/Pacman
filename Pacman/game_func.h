#ifndef GAME_FUNC_H
#define GAME_FUNC_H

void displayFunc();		//��ʾ����
void timerFunc(int value);		//���ڵ��ú���
void reshapeFunc(int width, int height);		//���ڵ�������
void keyboardFunc(unsigned char key, int x, int y);		//�������º���
void keyboardUpFunc(unsigned char key, int x, int y);	//����̧����	
void specialKeyFunc(int key, int x, int y);		//���ⰴ�����º���
void specialKeyUpFunc(int key, int x, int y);	//���ⰴ��̧����
void mouseFunc(int button, int state, int x, int y);
void elementsReset(bool re);		//Ԫ������


#endif // !GAME_FUNC_H


