#ifndef MAIN_H
#define MAIN_H

enum Direction { RIGTH, DOWN, LEFT, UP };

//��ɫ�ṹ��
struct Color_f
{
	float r;
	float g;
	float b;
};

//����ṹ��
struct Coord
{
	double x;
	double y;
	bool operator<(const Coord& c)const;
};


const int WINWIDTH = 1000;		//���ڿ��
const int WINHEIGIHT = 600;		//���ڸ߶�
const int BLOCKCNT = 15;		//��ͼ��ÿ�и���
const int BLOCKWIDTH = WINHEIGIHT/BLOCKCNT;		//��ͼ����
const int WINPOSX = 200;		//������ʼλ��
const int WINPOSY = 100;
const int fpsScale = 15;		//ÿ����ú���ֵ


#endif // !MAIN_H



