#pragma once
#include "gameNode.h"
#define PI 3.141592

class mainGame : public gameNode
{
private:
	//�̰��� ���� ����

	image* _bgNoon;
	image* _bgNight;
	image* _ground;

	image* _bird1;
	image* _bird2;
	image* _bird3;

	image* topPillar;
	image* bottomPillar;

	image* num0;
	image* num1;
	image* num2;
	image* num3;
	image* num4;
	image* num5;
	image* num6;
	image* num7;
	image* num8;
	image* num9;
	//image* _ball;

	int _alpha;			//���� �����ų ���İ�
	int _count;			//���̵���,�ƿ��� �ӵ� ������
	float gravity;
	int temp;
	int score;
	int scoreCount;
	
	RECT collision;
	RECT _rcGround;
	RECT _rcBird;

	RECT _rcPillar1;
	RECT _rcPillar2;
	RECT _rcPillar3;
	RECT _rcPillar4;
	RECT _rcPillar5;
	RECT _rcPillar6;


	

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	//�̰��� �Լ� ����


	mainGame() {}
	~mainGame() {}
};

