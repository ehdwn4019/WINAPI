#pragma once
#include "gameNode.h"
//#include "bullet.h"
#include <vector>
#define ALLOW 16
#define CLEARPOINT 5
#define DOOR 3
#define GAMECLEAR 3

//�÷��̾� ����ü 
struct Himno
{
	RECT _rcPlayer;
	RECT _rcCamera;
	int _x, _y; 
	float _speed;
	float _jumpSpeed;
	bool _isJumpDown;
	int _jumpCount;
	bool _isDash;
	float _gravity;
	float _angle;
	bool _isJump;
	int _foot;
	int _height;
};

//�÷��̾� ���� 
enum HIMNOSTATE
{
	HIMNO_IDLE,HIMNO_RUN,HIMNO_JUMP,
	HIMNO_DASH,HIMNO_CLIMB,HIMNO_SLIDE,
	HIMNO_CROUCH,HIMNO_ATTACK,HIMNO_FALL
};

class player : public gameNode
{
private:

	//bullet* _allow;

	//�÷��̾� ����ü ����
	Himno _himno;
	HIMNOSTATE _state;

	//�÷��̾� ������ �̹��� ���� 
	int _count;
	int _index;

	//�÷��̾� ���� �� ���� 
	int _isLeft;

	//�÷��̾� �̹��� �߰� ���� 
	image* _idle;
	image* _crouch;
	image* _dash;
	image* _jump;
	image* _fall;
	image* _run;
	image* _slide;
	image* _attack;
	image* _climb;

	//�������� ��ų ���� 
	float _loopX;
	float _loopY;
	//�������� ��� ��Ʈ 
	RECT _rcWater;

	//���� �Ͻ����� �Һ���  
	bool _stopGame;
	//���� �Ͻ����� �޴� ���� �Һ���
	bool _stopContinue;
	bool _stopMainMenu;
	//�Ͻ����� ��Ʈ 
	RECT _rcContionue;
	RECT _rcMainMenu;
	//�Ͻ����� �̹��� 
	image* _stopBg;
	image* _stopPause;
	image* _stopMainMenuOn;
	image* _stopMainMenuOff;
	image* _stopContinueOn;
	image* _stopContinueOff;



	//�� ��ǥ 
	int _mapX;
	int _mapY;
	//�� ī�޶� ��Ʈ
	RECT _rcMap;

	//�� ��� �� ���� �̹���
	image* _mapBg;
	//�� �̹��� 
	image* _map;
	//�� �浹 �̹���
	image* _mapCollision;
	//�� �ٴ� �� �̹���
	image* _water;
	//�� ���ǵ�� y��ǥ 
	float _waterY;



	//��ֹ� ��Ʈ 
	RECT _rcAllow[ALLOW];

	

	//ȭ�� �̹���
	image* _allow_L;
	image* _allow_R;
	//ȭ�� ��ħ �̹���
	image* _allow_B;
	//ȭ�� ��ǥ
	int _allowX_L;
	int _allowX_R;
	int _allowY;

	//npc ��Ʈ
	RECT _rcNpc;
	//npc �̹���
	image* _npc;

	//���� ���� ��Ʈ
	RECT _rcDeadTree;
	//���� ���� ����Ʈ
	image* _deadTreeEffect;
	//���� ���� ���� ���� ���� 
	int _alphaTree;

	//Ŭ���� �� 
	RECT _rcDoor[DOOR];
	//Ŭ���� �� �̹���
	image* _clearDoor;
	image* _deadDoor_R;
	image* _deadDoor_G;

	//�ȼ� �浹 ����
	float _probeL;
	float _probeR;
	float _probeT;
	float _probeB;
	bool _LEFT;
	bool _RIGHT;

	//�뽬 ������ ��Ʈ
	RECT _rcDashItem;
	//�뽬 ������ �̹���
	image* _dashItem;
	//�뽬 ������ ���� ���� 
	float _scaleDash;
	//�뽬 ��ų ����
	bool _canDash;

	//Ŭ���� ����Ʈ
	RECT _rcClearPoint[CLEARPOINT];
	//Ŭ���� ����Ʈ �̹���
	image* _clearPoint;
	//Ŭ���� ����Ʈ ������ �̹��� ����
	int _clearPointCount;
	int _clearPointIndex;
	//���� �ؿ� �κ� �̹���
	image* _jewel_B;
	//���� ȹ�� ����
	bool _getJewel[CLEARPOINT];
	//���� ȹ��� �̹���(�÷��̾� �ֺ�) 
	//image* _Jewel;
	image* _rotateJewel;
	//���� �̹��� ��Ʈ
	RECT _rcRotateJewel;
	//���� ������Ʈ ������ �ޱ۰�
	float _rotateJewelAngle[CLEARPOINT];

	//ī�޶� �浹 ��Ʈ 
	RECT _rcWall;

	//�� ���� ����
	RECT _rcTrap;
	//�� ���� ���� �̹���
	image* _trap;
	//�� ���� Ŭ���� ���� ��Ʈ
	RECT _rcGameClear[GAMECLEAR];
	//�� ���� Ŭ���� ���� �̹��� 
	image* _gameClear;

	//�뽬 ������ ���� 
	bool _showDash;
	bool _showNpc;
	int _dashCount;

	//���� Ŭ���� ����
	int _clearCount;
	bool _isGameClear;

	//��Ÿ�� ����
	bool _slideWall;
	//����� ����
	bool _grabWall;


	image* _a;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	//�÷��̾� �ִϸ��̼�
	void playerAnimation();

	//�÷��̾� �̵� 
	void playerMove();

	//�÷��̾� �浹
	void playerCollision();

	//ȭ�� �߻� 
	void allowShoot();

	//�÷��̾� ���� 
	void playerDead();
	//�÷��̾� ��Ƴ���
	void playerAlive();

	////�÷��̾� �� �Լ� 
	//RECT getPlayerRect() { return _himno._rcPlayer; }
	//RECT getPlayerCamera() { return _himno._rcCamera; }
	//Himno getHimno() { return _himno; }
	//int getPlayerY() { return _himno._y; }
	//int getPlayerX() { return _himno._x; }
	//int getPlayerHeight() { return _himno._height; } 
	//float getPlayerGravity() { return _himno._gravity; }
	//bool getPlayerIsJump() { return _himno._isJump; }
	//float getPlayerSpeed() { return _himno._speed; }
	//float getPlayerJump() { return _saveJump; }
	//HIMNOSTATE getPlayerState() { return _state; }
	
	////�÷��̾� �� �Լ� 
	//void setPlayerY(int y) { _himno._y=y; }
	//void setPlayerHeight(int height) { _himno._height = height; }
	//void setPlayerGravity(float gravity) { _himno._gravity = gravity; }
	//void setPlayerJumpSpeed(float jump) { _himno._jumpSpeed = jump; }
	//void setPlayerIsjump(bool isJump) { _himno._isJump = isJump; }
	//void setPlayerSpeed(float speed) { _himno._speed = speed; }

	//ī�޶�
	//float getColY() { return _colY; }
};

