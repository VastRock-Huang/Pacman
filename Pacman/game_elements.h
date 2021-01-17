#ifndef MAIN_H
#include "main.h"
#endif // !MAIN_H

#ifndef GAME_ELEMENTS_H
#define GAME_ELEMENTS_H
#include <list>
#include <string>
#include <ctime>


//��ͼ
class GameMap
{
private:
	//��ɫ
	const Color_f CLR[3] = {
		{ 0.f, 0.2f, 0.6f },
		{ 0.2f, 0.6f, 0.1f },
		{ 0.5f, 0.f, 0.7f }
	};
	int clrIdx = 0;		//��ǰ��ͼ��ɫ���

public:	
	const bool BLOCKS[BLOCKCNT][BLOCKCNT] = {	//��ͼ��: 0Ϊǽ, 1Ϊ��·
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0 },
		{ 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0 },
		{ 0, 1, 1, 0, 0, 1, 0, 0, 0, 0,	1, 1, 0, 1, 0 },
		{ 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0 },
		{ 0, 1, 1, 0, 0, 1, 0, 0, 0, 0,	1, 1, 0, 1, 0 },
		{ 0, 1, 0, 0, 1, 1, 1, 1, 1, 0,	0, 1, 1, 1, 0 },
		{ 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0 },
		{ 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,	1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	void draw() const;		//���Ƶ�ͼ
	void setColor(bool re);
};

//ǰ������
class Food;
class Ghost;
class GameConsole;
class TcpCli;

//�Զ���
class Pacman
{
private:
	const double SPEED = 0.15 * fpsScale;	//�ٶ�
	const double R = 0.4 * BLOCKWIDTH;		//ͼ�ΰ뾶
	const Color_f CLR[2] = { { 1.f, 1.f, 0.f }, {1.f, 0.3f, 0.f} };
	Direction dir;	//����
	Coord pos;	//ͼ�����ĵ�
	const double MOUTHSPEED = 0.3 * fpsScale;	//�����ٶ�
	const double mouthAngleMax = 75;	//��������
	const double mouthAngleMin = 0;		//������С��
	bool mouthFlag = true;		//�����ʶ:����Ϊtrue, ����Ϊfalse
	double mouthAngle = 30;		//��ʼ����Ƕ�
	int lifeCnt;
	bool ghostFlag;		//�����ʶ: ����ghost������ֵʱΪtrue, false��Ϊ�޵�ʱ
	time_t ghostTime;	//�ϴ����������ʱ��
	//��ǽ����ײ���
	bool checkLeftCollision(const GameMap& gm) const;
	bool checkRightCollision(const GameMap& gm) const;
	bool checkUpCollision(const GameMap& gm) const;
	bool checkDownCollision(const GameMap& gm) const;

public:
	//������ʶ
	bool upFlag = false;
	bool downFlag = false;
	bool leftFlag = false;
	bool rightFlag = false;
	Pacman(const Coord& c);
	void draw();	//����
	void move(const GameMap& gm);	//�ƶ�
	void eatFood(Food& f, GameConsole & gc);	//��ʳ
	void meetGhost(const Ghost * ghp);		//��������ײ���
	int getLifeCnt() const { return lifeCnt; }	//��ȡ����ֵ
	void reset(const Coord& c, bool lifeRe);		//���ò���
};


//ʳ��
class Food
{
private:
	const Color_f CLR = { 1.,0.5,0. };	//��ɫ
	double pointSize = 5.0;		//ʳ���С
	std::list<Coord> cor;	//λ��
	
public:
	Food();
	void draw() const;	//����
	unsigned foodCnt() const { return cor.size(); }		//ʣ��ʳ������

	friend class Pacman;
};


//��Ϸ����̨
class GameConsole
{
private:
	const double playPos = 370;		//play��ťλ��
	double playLneLen;		//play���߳���
	int hiScore = 0;	//��߷�
	int level;		//��Ϸ�ȼ�

	int FPS = 0, frame = 0, timeBase = 0;	//FPS����

	void updateHiScore();	//������߷�
	void playAn();		//����play���߶���
	void printStr(const std::string msg, void* font) const;		//��������
	void drawPacmanLife(const Pacman& pac);		//���ƳԶ�������ֵ

public:
	bool gameActive;	//��Ϸ���ʶ
	bool gameOver;		//��Ϸ������ʶ
	bool playFlag;		//play��ť��ʶ: true��ʾ
	int scores;			//����
	int scoreInc;		//��������	
	GameConsole();
	void drawWelcomeScreen();		//���ƻ�ӭ����
	void resetPlayLine() { playFlag = false; playLneLen = 0; }	//����play����
	void drawScoreBoard(const Pacman& pac);		//���ƼƷְ�
	void drawGameOver()const;		//��Ϸ����
	bool checkGameOver(const Pacman& pac);		//�����Ϸ�Ƿ����
	void reset();		//���ò���
	void readHiScore();		//��ȡ��߷�
	void saveHiScore()const;		//������߷�
	void GameExit();	//�˳���Ϸ
	void upgrade(Ghost * ghp);		//����
	void drawFPS();		//����FPS
};


//����
class Ghost
{
private:
	static const double initSpeed;		//��ʼ�ٶ�
	static const double speedInc;		//�ٶ�����
	const double R = 0.46 * BLOCKWIDTH;		//ͼ�ΰ뾶
	Color_f clr;	//��ɫ
	Coord corMulWid;	//����λ�� = ����λ��*BLOCKWIDTH
	Direction dir;	//�ƶ�����
	double speed;	//�ٶ�
	bool checkCollision(Direction d, const GameMap& gm) const;	//�����ǽ����ײ

public:
	static int cnt;		//������Ŀ
	Ghost(const Coord& c, const Color_f& rgb);
	void draw() const;		//����
	void autoMove(const GameMap& gm);	//�Զ��ƶ�

	friend class Pacman;
	friend void GameConsole::upgrade(Ghost * ghp);		//����
	friend void ghostReset(Ghost* ghp, const Coord * cp, const Color_f * clrp, bool speedRe);		//�����������
};


#endif // !GAME_ELEMENTS_H