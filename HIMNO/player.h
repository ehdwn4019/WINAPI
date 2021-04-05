#pragma once
#include "gameNode.h"
//#include "bullet.h"
#include <vector>
#define ALLOW 16
#define CLEARPOINT 5
#define DOOR 3
#define GAMECLEAR 3

//플레이어 구조체 
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

//플레이어 상태 
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

	//플레이어 구조체 선언
	Himno _himno;
	HIMNOSTATE _state;

	//플레이어 프레임 이미지 변수 
	int _count;
	int _index;

	//플레이어 방향 불 변수 
	int _isLeft;

	//플레이어 이미지 추가 변수 
	image* _idle;
	image* _crouch;
	image* _dash;
	image* _jump;
	image* _fall;
	image* _run;
	image* _slide;
	image* _attack;
	image* _climb;

	//루프렌더 시킬 변수 
	float _loopX;
	float _loopY;
	//루프렌더 사용 렉트 
	RECT _rcWater;

	//게임 일시중지 불변수  
	bool _stopGame;
	//게임 일시중지 메뉴 선택 불변수
	bool _stopContinue;
	bool _stopMainMenu;
	//일시중지 렉트 
	RECT _rcContionue;
	RECT _rcMainMenu;
	//일시중지 이미지 
	image* _stopBg;
	image* _stopPause;
	image* _stopMainMenuOn;
	image* _stopMainMenuOff;
	image* _stopContinueOn;
	image* _stopContinueOff;



	//맵 좌표 
	int _mapX;
	int _mapY;
	//맵 카메라 렉트
	RECT _rcMap;

	//맵 배경 반 투명 이미지
	image* _mapBg;
	//맵 이미지 
	image* _map;
	//맵 충돌 이미지
	image* _mapCollision;
	//맵 바닥 물 이미지
	image* _water;
	//물 스피드용 y좌표 
	float _waterY;



	//장애물 렉트 
	RECT _rcAllow[ALLOW];

	

	//화살 이미지
	image* _allow_L;
	image* _allow_R;
	//화살 받침 이미지
	image* _allow_B;
	//화살 좌표
	int _allowX_L;
	int _allowX_R;
	int _allowY;

	//npc 렉트
	RECT _rcNpc;
	//npc 이미지
	image* _npc;

	//죽음 나무 렉트
	RECT _rcDeadTree;
	//죽음 나무 이펙트
	image* _deadTreeEffect;
	//죽음 나무 알파 렌더 변수 
	int _alphaTree;

	//클리어 문 
	RECT _rcDoor[DOOR];
	//클리어 문 이미지
	image* _clearDoor;
	image* _deadDoor_R;
	image* _deadDoor_G;

	//픽셀 충돌 변수
	float _probeL;
	float _probeR;
	float _probeT;
	float _probeB;
	bool _LEFT;
	bool _RIGHT;

	//대쉬 아이템 렉트
	RECT _rcDashItem;
	//대쉬 아이템 이미지
	image* _dashItem;
	//대쉬 스케일 렌더 변수 
	float _scaleDash;
	//대쉬 스킬 변수
	bool _canDash;

	//클리어 포인트
	RECT _rcClearPoint[CLEARPOINT];
	//클리어 포인트 이미지
	image* _clearPoint;
	//클리어 포인트 프레임 이미지 변수
	int _clearPointCount;
	int _clearPointIndex;
	//보석 밑에 부분 이미지
	image* _jewel_B;
	//보석 획득 변수
	bool _getJewel[CLEARPOINT];
	//보석 획득시 이미지(플레이어 주변) 
	//image* _Jewel;
	image* _rotateJewel;
	//보석 이미지 렉트
	RECT _rcRotateJewel;
	//보석 로테이트 렌더용 앵글값
	float _rotateJewelAngle[CLEARPOINT];

	//카메라 충돌 렉트 
	RECT _rcWall;

	//문 위에 함정
	RECT _rcTrap;
	//문 위에 함정 이미지
	image* _trap;
	//문 위에 클리어 조건 렉트
	RECT _rcGameClear[GAMECLEAR];
	//문 위에 클리어 조건 이미지 
	image* _gameClear;

	//대쉬 아이템 변수 
	bool _showDash;
	bool _showNpc;
	int _dashCount;

	//게임 클리어 변수
	int _clearCount;
	bool _isGameClear;

	//벽타기 변수
	bool _slideWall;
	//벽잡기 변수
	bool _grabWall;


	image* _a;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	//플레이어 애니메이션
	void playerAnimation();

	//플레이어 이동 
	void playerMove();

	//플레이어 충돌
	void playerCollision();

	//화살 발사 
	void allowShoot();

	//플레이어 죽음 
	void playerDead();
	//플레이어 살아남음
	void playerAlive();

	////플레이어 겟 함수 
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
	
	////플레이어 셋 함수 
	//void setPlayerY(int y) { _himno._y=y; }
	//void setPlayerHeight(int height) { _himno._height = height; }
	//void setPlayerGravity(float gravity) { _himno._gravity = gravity; }
	//void setPlayerJumpSpeed(float jump) { _himno._jumpSpeed = jump; }
	//void setPlayerIsjump(bool isJump) { _himno._isJump = isJump; }
	//void setPlayerSpeed(float speed) { _himno._speed = speed; }

	//카메라
	//float getColY() { return _colY; }
};

