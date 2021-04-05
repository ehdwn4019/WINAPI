#pragma once
#include "gameNode.h"
#include "camera.h"

#define ENEMY 5
#define BULLET 10 
#define PI 3.1415926f
#define BOSSBULLET 200
enum StateET
{
	IDLE_Et,
	DEAD_Et
};

enum StatePlayer
{
	IDLE_Player,
	LEFT_Player,
	RIGHT_Player,
	DEAD_Player
};

struct tagPlayer
{
	RECT _rc;
	float _speed;
	bool _isFire;
	RECT _HP;
	int _showHp;
	bool _destroy;
	bool _dead;
	
};

struct tagPlayerbullet
{
	RECT _rc;
	float _speed;
	bool _isFire;
    int _playerBulletCount;
	bool _shoot;
};

struct tagEnemy
{
	RECT _rc_B_green;
	RECT _rc_B_green_side;
	RECT _rc_B_gray;
	RECT _rc_B_gray_side;
	float _speed;
	bool _isFire;
	
};

struct  tagEnemybullet
{
	RECT _rc_B_green;
	RECT _rc_B_green_side;
	RECT _rc_B_gray;
	RECT _rc_B_gray_side;
	float _speed;
	bool _isFire;
	int _enemyBulletCount;
};

class mainGame : public gameNode
{
private:
	//camera* _camera;	//카메라 클래스

	HBRUSH _brush;

	//이미지 씌울 렉트
	RECT _rcBg;
	RECT _rcBasicgreen;

	//이넘문 선언
	StatePlayer _statePlayer;
	StateET _stateEt;

	//초기화면 게임스타트
	image* _gameStart;
	//게임오버 화면 
	image* _gameOver;
	//게임클리어 화면
	image* _gameClear;

	//플레이어 모션 이미지 선언
	image* _idle;
	image* _left;
	image* _right;
	image* _dead;
	//플레이어 총알 이미지
	image* _playerbullet;

	//기본 적 이미지 
	image* _basicGreen;
	image* _basicGreenSide;
	image* _basicGray;
	image* _basicGraySide;
	//기본 사이드 적 총알 이미지
	image* _sidebullet;


	//중간 보스 이미지 
	image* _middleGreen;
	image* _middleGray;
	//중간 보스 자폭기 이미지
	image* _middlePung;

	//마지막 보스 이미지
	image* _lastBoss;
	//마지막 보스 총알 이미지
	image* _lastBossBullet;


	//ET 이미지
	image* _ET;
	image* _ET_Dead;
	//ET 총알 이미지
	image* _etbullet;


	//구조체 선언
	tagPlayer _player;
	tagEnemy _enemy[5];
	tagPlayerbullet _playerBullet[10];
	tagEnemybullet _enemyBullet[10];



	//기본 적 죽은 상태 파악
	bool _basicGreenDead[BULLET];
	bool _basicGrayDead[BULLET];
	bool _basicGreenSideDead[BULLET];
	bool _basicGraySideDead[BULLET];



	//기본적 hp카운트 
	int _basicGreenHpCount;
	int _basicGrayHpCount;
	int _basicGreenSideHpCount;
	int _basicGraySideHpCount;
	

	//중간 보스 
	RECT _rc_middle_Green;
	RECT _rc_middle_Gray;
	float _middleBossSpeed;
	//중간 보스 총알
	RECT _rc_middle_Green_Bullet[BOSSBULLET];
	RECT _rc_middle_Gray_Bullet[BOSSBULLET];
	float _middleBossBulletSpeed[BOSSBULLET];
	int _middleBossBulletCount;
	float _middleBossBulletGreenX[BOSSBULLET];
	float _middleBossBulletGreenY[BOSSBULLET];
	float _middleBossBulletGrayX[BOSSBULLET];
	float _middleBossBulletGrayY[BOSSBULLET];
	float _middleBossBulletAngle;

	//마지막 보스 
	RECT _rc_lastBoss;
	float _lastBossSpeed;
	float _lastBossX;
	float _lastBossY;
	int bulletCount;
	RECT _rc_lastBoss_Bullet[BOSSBULLET];
	float _lastBossBulletSpeed[BOSSBULLET];
	float _lastBossBulletX[BOSSBULLET];
	float _lastBossBulletY[BOSSBULLET];
	float _lastBossBulletMoveAngle[BOSSBULLET];
	float _lastBossBulletMoveX[BOSSBULLET];
	float _lastBossBulletMoveY[BOSSBULLET];
	float _lastBossBulletAngle;
	bool _lastBulletFire[BOSSBULLET];
	bool _showBossBullet;
	
	int _lastBossBulletCount;

	//ET
	RECT _rc_ET;
	RECT _rc_ET_Bullet;
	int _etBulletcount;
	int _moveCountEt;
	bool _etAttack;

	


	//기타 변수 
	int _loopX;
	int _loopY;
	int _count;
	int _countEt;
	int _index;
	int _index_Et;
	bool _isGame;
	int _showEnemycount;
	char str[100];
	char str1[100];
	RECT wall;
	bool _bgMove;
	int _deadCount;
	int _endGameCount;


	//게임 이미지 띄우는 불변수
	bool _GameStart;
	bool _GameClear;
	bool _GameOver;

	//총알 카운트
	int _playerBulletCount;
	int _enemyBulletCount;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//함수

	//플레이어 함수
	void movePlayer();
	void moveBulletPlayer();
	void shootPlayer();
	void animationPlayer();
	void deadPlayer();
	void destoryEnemy();

	//기본 적 함수
	void moveEnemy();
	void moveBulletEnemy();

	//중간 보스 함수 
	void moveMiddleboss();
	void moveBulletMiddleboss();

	//마지막 보스 함수 
	void moveLastboss();
	void moveBulletLastboss();
	void shootLastBoss();


	//ET 함수 
	void moveET();
	void moveBulletEt();
	void animationET();

	//기타 함수
	void collision();
	void wallCollision();



	mainGame() {}
	~mainGame() {}
};

