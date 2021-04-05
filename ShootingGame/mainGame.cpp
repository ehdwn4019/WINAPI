#include "stdafx.h" 
#include "mainGame.h" 
 
//============================================================= 
//	## 초기화 ## init() 
//============================================================= 
HRESULT mainGame::init() 
{ 
	gameNode::init(); 
	//클래스 초기화를 이곳에서 한다   
	  
	//카메라 클래스  
	//_camera = new camera;   
	//_camera->init();  47  
//===============================================<이미지>================================================================== 
	 
	//백그라운드 이미지       
	IMAGEMANAGER->addImage("배경", "배경.bmp", 1731, 1000);  

	//게임 스타트 이미지
	IMAGEMANAGER->addImage("게임시작", "게임시작.bmp", 571, 300, true, RGB(255, 0, 255));
	//게임 오버 이미지
	IMAGEMANAGER->addImage("게임오버", "게임오버.bmp", 587, 600, true, RGB(255, 0, 255));
	//게임 클리어 이미지
	IMAGEMANAGER->addImage("게임클리어", "게임클리어.bmp", 794, 250, true, RGB(255, 0, 255));
	             
	//플레이어 이미지                                          
	_idle = IMAGEMANAGER->addFrameImage("기본이미지", "기본이미지.bmp", 145, 50,2,1,true,RGB(255,0,255)); 
	_left = IMAGEMANAGER->addFrameImage("왼쪽모션", "왼쪽모션.bmp", 218, 50, 3, 1, true, RGB(255, 0, 255)); 
	_right = IMAGEMANAGER->addFrameImage("오른쪽모션", "오른쪽모션.bmp", 218, 50, 3, 1, true, RGB(255, 0, 255)); 
	_dead = IMAGEMANAGER->addFrameImage("죽음", "죽음.bmp", 235, 50, 5, 1, true, RGB(255, 0, 255)); 
	 
	//플레이어 총알 이미지 
	_playerbullet = IMAGEMANAGER->addImage("플레이어총알", "플레이어총알.bmp", 18, 18, true, RGB(255, 0, 255)); 
	 

	//기본 적 이미지 
	_basicGreen = IMAGEMANAGER->addImage("기본적초록색아래", "기본적초록색아래.bmp", 68, 50, true, RGB(255, 0, 255));  
	_basicGreenSide = IMAGEMANAGER->addImage("기본적초록색사이드", "기본적초록색사이드.bmp", 37, 50, true, RGB(255, 0, 255));   
	_basicGray = IMAGEMANAGER->addImage("기본적회색아래", "기본적회색아래.bmp", 63, 50, true, RGB(255, 0, 255));   
	_basicGraySide = IMAGEMANAGER->addImage("기본적회색사이드", "기본적회색사이드.bmp", 33, 50, true, RGB(255, 0, 255));  
	//기본 적 총알 이미지   
	_sidebullet = IMAGEMANAGER->addImage("사이드적총알", "사이드적총알.bmp", 23, 36, true, RGB(255, 0, 255));      


	//중간 보스 이미지
	_middleGray = IMAGEMANAGER->addImage("중간회색자폭기", "중간회색자폭기.bmp", 264, 200, true, RGB(255, 0, 255));
	_middleGreen = IMAGEMANAGER->addImage("중간초록자폭기", "중간초록자폭기.bmp", 239, 200, true, RGB(255, 0, 255));
	//중간 보스 자폭기
	_middlePung = IMAGEMANAGER->addImage("자폭기", "자폭기.bmp", 36, 30, true, RGB(255, 0, 255));


	//마지막 보스 이미지
	_lastBoss = IMAGEMANAGER->addImage("마지막보스", "마지막보스.bmp", 825, 450, true, RGB(255, 0, 255));
	//마지막 보스 총알
	_lastBossBullet = IMAGEMANAGER->addImage("보스총알", "보스총알.bmp", 40, 40, true, RGB(255, 0, 255));


	//ET
	_ET = IMAGEMANAGER->addFrameImage("이티", "이티.bmp", 1320, 78,15,1 , true, RGB(255, 0, 255));
	_ET_Dead = IMAGEMANAGER->addFrameImage("이티죽음", "이티죽음.bmp", 2501, 120, 22, 1, true, RGB(255, 0, 255));
	//ET 총알 이미지
	_etbullet = IMAGEMANAGER->addImage("이티총알", "이티총알.bmp", 133, 400, true, RGB(255, 0, 255));

//=========================================<플레이어>========================================================================
	//플레이어 초기화 
	_player._speed = 4.5f; 
	_player._rc = RectMake(425, 800, 73, 50); 
	_player._isFire = false; 
	_player._HP = RectMake(0, 960, 900, 40);
	_player._showHp = 900;
	_player._destroy = false;
	_player._dead = false;
	_deadCount = 0;

	//플레이어 총알 초기화 
	for (int i = 0; i < BULLET; i++)
	{
		_playerBullet[i]._isFire = false;
		_playerBullet[i]._speed = 10.5f;
		_playerBullet[i]._playerBulletCount = 0;
		_playerBullet[i]._shoot = false;
	   //_playerBullet[i]._rc = RectMake(_player._rc.left + 20, _player._rc.top - 25, 10, 25);
	}

//=========================================<기본 적>========================================================================

	//기본 초록적 초기화 
	
	for (int i = 0; i < ENEMY; i++)
	{
		_enemy[i]._speed = 2.5f;
		_enemy[i]._rc_B_green = RectMake(125 + (150 * i), -100 - (150 * i), 73, 50);
		if (i > 2)
		{
			_enemy[i]._rc_B_green = RectMake(125 + (150 * i), -100 + (150 * i - 595), 73, 50);
		}
	}
	

	//기본 사이드 초록적 초기화 
	for (int i = 0; i < ENEMY; i++)
	{
		_enemy[i]._speed = 2.5f;
		_enemy[i]._rc_B_green_side = RectMake(900 + (150 * i), 400, 73, 50);
	}

	//기본 회색적 초기화
	for (int i = 0; i < ENEMY; i++)
	{
		_enemy[i]._speed = 2.5f;
		_enemy[i]._rc_B_gray = RectMake(125 + (150 * i), -100 - (150 * i), 73, 50);
		if (i > 2)
		{
			_enemy[i]._rc_B_gray = RectMake(125 + (150 * i), -100 + (150 * i - 595), 73, 50);
		}

	}

	//기본 사이드 회색적 초기화
	for (int i = 0; i < ENEMY; i++)
	{
		_enemy[i]._speed = 2.5f;
		_enemy[i]._rc_B_gray_side = RectMake(-900 + (150 * i), 400, 73, 50);
	}

	//기본 적 총알 초기화
	for (int i = 0; i < ENEMY; i++)
	{
		//_enemyBullet[i]._isFire = false;
		_enemyBullet[i]._speed = 10.5f;
		_enemyBullet[i]._rc_B_green = RectMake(_enemy[i]._rc_B_green.left+23, _enemy[i]._rc_B_green.bottom+23, 18, 18);
		_enemyBullet[i]._rc_B_green_side = RectMake(_enemy[i]._rc_B_green_side.left,_enemy[i]._rc_B_green_side.bottom, 36, 36);
		_enemyBullet[i]._rc_B_gray = RectMake(_enemy[i]._rc_B_gray.left+23, _enemy[i]._rc_B_gray.bottom+23, 18, 18);
		//_enemyBullet[i]._rc_B_gray = RectMake(100,100, 18, 18);
		_enemyBullet[i]._rc_B_gray_side = RectMake(_enemy[i]._rc_B_gray_side.left, _enemy[i]._rc_B_gray_side.bottom, 36, 36);
		_enemyBullet[i]._enemyBulletCount = 0;
	}

	//기본 적 입은 데미지 카운트
	_basicGreenHpCount = 0;
	_basicGrayHpCount = 0;
	_basicGreenSideHpCount = 0;
	_basicGraySideHpCount = 0;


	//기본 적 죽은 상태 판별
	for (int i = 0; i < BULLET; i++)
	{
		_basicGreenDead[i] = false;
		_basicGrayDead[i] = false;
		_basicGreenSideDead[i] = false;
		_basicGraySideDead[i] = false;
	}
	

//=============================================<중간 보스>====================================================================
	//중간 보스 초기화   
	_rc_middle_Green = RectMake(600, -200, 264, 200);   
	_rc_middle_Gray = RectMake(50, -200, 264, 200);  
	_middleBossSpeed = 5.0f;  
	  
	_middleBossBulletCount = 0;  
	_middleBossBulletAngle = PI / 2; 
	 
	//중간 보스 총알 초기화 
	//_middle_Green_Bullet=RectangleMake() 
	for (int i = 0; i < BOSSBULLET; i++) 
	{ 
		_middleBossBulletSpeed[i] = 5.5f; 
		_middleBossBulletGreenX[i] = 600; 
		_middleBossBulletGreenY[i] = -400; 
		_middleBossBulletGrayX[i] = 200; 
		_middleBossBulletGrayY[i] = -400; 
	} 
//===============================================<마지막 보스,ET>================================================================	 

	//마지막 보스 초기화 
	_lastBossX = 450;
	_lastBossY = 1300;
	_lastBossSpeed = 0.1f; 
	_lastBossBulletCount = 0; 
	_showBossBullet = false;

	//마지막 보스 총알 초기화
	for (int i = 0; i < BOSSBULLET; i++)
	{
		_lastBulletFire[i] = false;
		_lastBossBulletMoveX[i] = 300;
		_lastBossBulletMoveY[i] = 300;
		_lastBossBulletSpeed[i] = 5.0f;
	}

	_lastBossBulletAngle = PI / 2; //앵글값

	//ET 초기화 
	_etAttack = true;
	if (_etAttack == true)
	{
		_rc_ET = RectMake(400, 0, 100, 78);
		_rc_ET_Bullet = RectMake(_rc_ET.left, _rc_ET.bottom, 70, 335);
		_etBulletcount = 0;
		_moveCountEt = 0;
	}
	 
//=================================================<기타 초기화>================================================================
	//기타 초기화
	_rcBg = RectMake(0, 0, 1800,1000);
	_count = 0;
	_countEt = 0;
	_index = 0;
	_index_Et = 0;
	_statePlayer = IDLE_Player;
	_stateEt = IDLE_Et;
	_isGame = false;
	_showEnemycount = 0;
	wall = RectMake(0, 200, 1000, 50);
	_bgMove = true;
	_endGameCount = 0;

	_GameStart = false;
	_GameOver = false;
	_GameClear = false;

	//총알 카운트 초기화
	_playerBulletCount = 0;
	_enemyBulletCount = 0;

	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//클래스 해제를 이곳에서 한다

	//카메라 클래스
	//_camera->release();
	//SAFE_DELETE(_camera);
}

//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//클래스 업데이트를 이곳에서 한다

	//카메라 클래스
	//_camera->update();
	//_lastBossX = WINSIZEX / 2;

	
	//기타 업데이트
	if (_bgMove)
	{
		_loopX -= 0;
		_loopY -= 3;
	}

	//게임시작
	if (INPUT->GetKeyDown(VK_SPACE))
	{
		_GameStart = true;
	}

	if (_GameStart == true)
	{
		//각종 카운트 플러스 
		_count++;
		_countEt++;
		_showEnemycount++;
		_moveCountEt++;

		//플레이어 
		this->movePlayer();
		this->animationPlayer();
		this->moveBulletPlayer();
		this->deadPlayer();

		//기본 적
		this->moveEnemy();
		this->moveBulletEnemy();

		//중간 보스 
		this->moveMiddleboss();
		this->moveBulletMiddleboss();

		//마지막 보스
		this->moveLastboss();
		this->moveBulletLastboss();

		//마지막 보스 생성
		_rc_lastBoss = RectMakeCenter(_lastBossX, _lastBossY, 825, 450);

		//마지막 보스 총알 각도
		_lastBossBulletAngle += 0.5f;

		//마지막 보스 총알 생성
		for (int i = 0; i < BOSSBULLET; i++)
		{
			_rc_lastBoss_Bullet[i] = RectMakeCenter(_lastBossBulletMoveX[i] + 150, _lastBossBulletMoveY[i] + 100, 40, 40);
			//_lastBossX = cosf(_lastBossBulletAngle) * 200 + _lastBossX;
			//_lastBossY = sinf(_lastBossBulletAngle) * 200 + _lastBossY;
		}


		//ET
		this->moveET();
		this->moveBulletEt();
		this->animationET();

		//충돌
		this->collision();
		this->wallCollision();

		//체력 수치 
		sprintf(str, "HP : %d", _player._showHp); 
		if (_player._showHp < 0)
		{
			_player._showHp = 0;
		}

		//적파괴 
		this->destoryEnemy();
		//sprintf(str1, "점수 : %d", _showEnemycount);

		//for (int i = 0; i < BULLET; i++)
		//{
		//	if (_playerBullet[i]._isFire == false)
		//	{
		//		_playerBullet[i]._rc = RectMake(2000, 2000, 18, 18);
		//	}
		//}

		//게임클리어 상태
		if (_showEnemycount == 0)
		{
			_endGameCount++;
			if (_endGameCount == 400)
			{
				_GameClear = true;

				if (_endGameCount == 550)
				{
					this->init();
				}
			}
		}
			




		//_count++;
		//if (_count % 20 == 0)
		//{
		//	this->shoot();
		//}

		//if (_showEnemycount>=50)
		//{
		//	_GameClear = true;
		//}

	}
}

//=============================================================
//	## 렌더 ## render()
//=============================================================
void mainGame::render()
{
	//흰색 빈 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================	
	//클래스 렌더를 이곳에서 한다
	
	//카메라 클래스
	//_camera->render();
	
	IMAGEMANAGER->loopRender("배경", getMemDC(), &_rcBg, _loopX, _loopY);
	if (_GameStart == false)
	{
		IMAGEMANAGER->render("게임시작", getMemDC(), 170, 300);
	}

	if (_GameOver == true)
	{
		IMAGEMANAGER->render("게임오버", getMemDC(), 155, 200);
	}
	
	if (_GameClear == true)
	{
		IMAGEMANAGER->render("게임클리어", getMemDC(), 60, 25);
	}
	

	if (_GameStart == true)
	{

		//HP 색깔 
		Rectangle(getMemDC(), _player._HP);
		_brush = CreateSolidBrush(RGB(255, 0, 42));
		FillRect(getMemDC(), &_player._HP, _brush);


		//플레이어
		if (_statePlayer == IDLE_Player) IMAGEMANAGER->frameRender("기본이미지", getMemDC(), _player._rc.left, _player._rc.top);
		if (_statePlayer == LEFT_Player) IMAGEMANAGER->frameRender("왼쪽모션", getMemDC(), _player._rc.left, _player._rc.top);
		if (_statePlayer == RIGHT_Player) IMAGEMANAGER->frameRender("오른쪽모션", getMemDC(), _player._rc.left, _player._rc.top);
		if (_statePlayer == DEAD_Player) IMAGEMANAGER->frameRender("죽음", getMemDC(), _player._rc.left, _player._rc.top);
		//플레이어총알
		for (int i = 0; i < BULLET; i++)
		{
			//Rectangle(getMemDC(), _playerBullet[i]._rc);
			IMAGEMANAGER->render("플레이어총알", getMemDC(), _playerBullet[i]._rc.left, _playerBullet[i]._rc.top);
		}

		//적 
		for (int i = 0; i < ENEMY; i++)
		{
			if (_basicGreenDead[i] == false) IMAGEMANAGER->render("기본적초록색아래", getMemDC(), _enemy[i]._rc_B_green.left, _enemy[i]._rc_B_green.top);
			if (_basicGrayDead[i] == false) IMAGEMANAGER->render("기본적회색아래", getMemDC(), _enemy[i]._rc_B_gray.left, _enemy[i]._rc_B_gray.top);
			if (_basicGreenSideDead[i] == false) IMAGEMANAGER->render("기본적초록색사이드", getMemDC(), _enemy[i]._rc_B_green_side.left, _enemy[i]._rc_B_green_side.top);
			if (_basicGraySideDead[i] == false) IMAGEMANAGER->render("기본적회색사이드", getMemDC(), _enemy[i]._rc_B_gray_side.left, _enemy[i]._rc_B_gray_side.top);



			//IMAGEMANAGER->render("기본적초록색아래", getMemDC(), _enemy[i]._rc_B_green.left, _enemy[i]._rc_B_green.top);
			//IMAGEMANAGER->render("기본적회색아래", getMemDC(), _enemy[i]._rc_B_gray.left, _enemy[i]._rc_B_gray.top);
			//IMAGEMANAGER->render("기본적초록색사이드", getMemDC(), _enemy[i]._rc_B_green_side.left, _enemy[i]._rc_B_green_side.top);
			//IMAGEMANAGER->render("기본적회색사이드", getMemDC(), _enemy[i]._rc_B_gray_side.left, _enemy[i]._rc_B_gray_side.top);

		}

		////기본 적 총알 .사이드 적 총알 
		for (int i = 0; i < BULLET; i++)
		{
			if(_basicGreenDead[i]==false) IMAGEMANAGER->render("플레이어총알", getMemDC(), _enemyBullet[i]._rc_B_green.left, _enemyBullet[i]._rc_B_green.top);
			if (_basicGreenSideDead[i] == false) IMAGEMANAGER->render("사이드적총알", getMemDC(), _enemyBullet[i]._rc_B_green_side.left, _enemyBullet[i]._rc_B_green_side.top);
			if (_basicGrayDead[i] == false) IMAGEMANAGER->render("플레이어총알", getMemDC(), _enemyBullet[i]._rc_B_gray.left, _enemyBullet[i]._rc_B_gray.top);
			if (_basicGraySideDead[i] == false) IMAGEMANAGER->render("사이드적총알", getMemDC(), _enemyBullet[i]._rc_B_gray_side.left, _enemyBullet[i]._rc_B_gray_side.top);
		}



		//총알 렌더

		//for (int i = 0; i < BULLET; i++)
		//{
		//	Rectangle(getMemDC(), _enemyBullet[i]._rc_B_green);
		//	//Rectangle(getMemDC(), _enemyBullet[i]._rc_B_green_side);
		//	Rectangle(getMemDC(), _enemyBullet[i]._rc_B_gray);
		//	//Rectangle(getMemDC(), _enemyBullet[i]._rc_B_gray_side);
		//}

		//중간 보스 

		//Rectangle(getMemDC(), _rc_middle_Green);
		//Rectangle(getMemDC(), _rc_middle_Gray);
		IMAGEMANAGER->render("중간회색자폭기", getMemDC(), _rc_middle_Gray.left, _rc_middle_Gray.top);
		IMAGEMANAGER->render("중간초록자폭기", getMemDC(), _rc_middle_Green.left, _rc_middle_Green.top);

		//중간 보스 총알
		//EllipseMake(getMemDC(),)
		for (int i = 0; i < BOSSBULLET; i++)
		{
			//Rectangle(getMemDC(), _rc_middle_Green_Bullet[i]);
			//Rectangle(getMemDC(), _rc_middle_Gray_Bullet[i]);
			IMAGEMANAGER->render("자폭기", getMemDC(), _rc_middle_Green_Bullet[i].left, _rc_middle_Green_Bullet[i].top);
			IMAGEMANAGER->render("자폭기", getMemDC(), _rc_middle_Gray_Bullet[i].left, _rc_middle_Gray_Bullet[i].top);
		}

		//마지막 보스
		IMAGEMANAGER->render("마지막보스", getMemDC(), _rc_lastBoss.left, _rc_lastBoss.top);
		//마지막 보스 총알
		for (int i = 0; i < BOSSBULLET; i++)
		{
			if (_showBossBullet == true)
			{
				IMAGEMANAGER->render("보스총알", getMemDC(), _lastBossBulletMoveX[i] + 131, _lastBossBulletMoveY[i] + 100);
			}

			if (!_lastBulletFire)continue;
			//Rectangle(getMemDC(), _rc_lastBoss_Bullet[i]);
		}

		//ET
		//Rectangle(getMemDC(), _rc_ET);
		if (_stateEt == IDLE_Et) IMAGEMANAGER->frameRender("이티", getMemDC(), _rc_ET.left, _rc_ET.top);
		if (_stateEt == DEAD_Et) IMAGEMANAGER->frameRender("이티죽음", getMemDC(), _rc_ET.left, _rc_ET.top - 30);

		//ET 총알
		//Rectangle(getMemDC(), _rc_ET_Bullet);
		if (_etAttack)
		{
			IMAGEMANAGER->render("이티총알", getMemDC(), _rc_ET_Bullet.left - 30.5, _rc_ET_Bullet.top - 30);
		}


		//임시 카운트 
		TextOut(getMemDC(), 0, 940, str, strlen(str));
		//TextOut(getMemDC(), 0, 0, str1, strlen(str));

		//임시 벽 
		//Rectangle(getMemDC(), wall); 

		//보스 총알 생성
		for (int i = 0; i < BOSSBULLET; i++)
		{
			_rc_lastBoss_Bullet[i] = RectMakeCenter(_lastBossBulletX[i], _lastBossBulletY[i], 40, 40);
		}
	}
//=============================================================
	//백버퍼의 내용을 화면DC에 그린다
	this->getBackBuffer()->render(getHDC());
}



//플레이어 움직임
void mainGame::movePlayer()
{
	if (_player._dead == false)
	{
		//왼쪽이동
		if (INPUT->GetKey(VK_LEFT) && _player._rc.left > 0)
		{
			_statePlayer = LEFT_Player;
			_player._rc.left -= _player._speed;
			_player._rc.right -= _player._speed;
			//이동 예외
			if (_player._rc.left < 0)
			{
				_player._rc.left += _player._speed;
				_player._rc.right = _player._rc.left + 71;
			}
		}
		if (INPUT->GetKeyUp(VK_LEFT))
		{
			_statePlayer = IDLE_Player;
		}

		//오른쪽이동
		if (INPUT->GetKey(VK_RIGHT) && _player._rc.right < 900)
		{
			_statePlayer = RIGHT_Player;
			_player._rc.left += _player._speed;
			_player._rc.right += _player._speed;
		}
		if (INPUT->GetKeyUp(VK_RIGHT))
		{
			_statePlayer = IDLE_Player;
		}

		//위쪽이동
		if (INPUT->GetKey(VK_UP) && _player._rc.top > 0)
		{
			_player._rc.top -= _player._speed;
			_player._rc.bottom -= _player._speed;
		}
		//아래쪽이동
		if (INPUT->GetKey(VK_DOWN) && _player._rc.bottom < 1000)
		{
			_player._rc.top += _player._speed;
			_player._rc.bottom += _player._speed;
		}
		//공격
		if (INPUT->GetKeyDown('A'))
		{
			this->shootPlayer();
			_player._isFire = true;
			for (int i = 0; i < BULLET; i++)
			{
				_playerBullet[i]._isFire = true;
			}
		}
	}
	
}

//플레이어 총알 발사
void mainGame::shootPlayer()
{
	if (_player._dead == false)
	{
		_playerBulletCount++;

		for (int i = 0; i < BULLET; i++)
		{
			if (_playerBullet[i]._isFire == true) continue;
			_playerBullet[i]._isFire = true;
			_playerBullet[i]._rc = RectMake(_player._rc.left + 28, _player._rc.top - 8, 18, 18);
			break;
		}

		if (_playerBulletCount % 10 == 0)
		{
			this->shootPlayer();
		}
	}
}

//플레이어 총알 움직임
void mainGame::moveBulletPlayer()
{
	for (int i = 0; i < BULLET; i++)
	{

		if (!_playerBullet[i]._isFire)continue;
		//총알 이동
		_playerBullet[i]._rc.top -= _playerBullet[i]._speed;
		_playerBullet[i]._rc.bottom -= _playerBullet[i]._speed;
		
		//총알 재생성
		if (_playerBullet[i]._rc.bottom < 0)
		{
			_playerBullet[i]._isFire = false;
		}
	}
	
}

//기본 비행기 움직임
void mainGame::moveEnemy()
{
	for (int i = 0; i < ENEMY; i++)
	{

		_enemy[i]._rc_B_green.top += _enemy[i]._speed;
		_enemy[i]._rc_B_green.bottom += _enemy[i]._speed;

		if (_showEnemycount >= 700) 
		{ 
			_enemy[i]._rc_B_green_side.left -= _enemy[i]._speed; 
			_enemy[i]._rc_B_green_side.right -= _enemy[i]._speed; 
		} 
		 
		if (_showEnemycount >= 1250 )
		{ 
			_enemy[i]._rc_B_gray.top += _enemy[i]._speed;
			_enemy[i]._rc_B_gray.bottom += _enemy[i]._speed;
		}

		if (_showEnemycount >= 1850 )
		{ 
			_enemy[i]._rc_B_gray_side.left += _enemy[i]._speed;
			_enemy[i]._rc_B_gray_side.right += _enemy[i]._speed;
		}
	}
}

//기본 적 총알 발사 (움직임,생성)
void mainGame::moveBulletEnemy()
{
	for (int i = 0; i < BULLET; i++)
	{

		//기본 적 초록 총알 이동
		
		
		_enemyBullet[i]._rc_B_green.top += _enemyBullet[i]._speed;
		_enemyBullet[i]._rc_B_green.bottom += _enemyBullet[i]._speed;

		//기본 적 초록 사이드 총알 이동
		if (_showEnemycount >= 650 )
		{
			_enemyBullet[i]._rc_B_green_side.top += _enemyBullet[i]._speed-1.5f;
			_enemyBullet[i]._rc_B_green_side.bottom += _enemyBullet[i]._speed-1.5f;
		}

		//기본 적 회색 총알 이동
		if (_showEnemycount >= 1250 )
		{
			_enemyBullet[i]._rc_B_gray.top += _enemyBullet[i]._speed;
			_enemyBullet[i]._rc_B_gray.bottom += _enemyBullet[i]._speed;
		}
		
		//기본 적 회색 사이드 총알 이동
		if (_showEnemycount >= 1850 )
		{
			_enemyBullet[i]._rc_B_gray_side.top += _enemyBullet[i]._speed-1.5f;
			_enemyBullet[i]._rc_B_gray_side.bottom += _enemyBullet[i]._speed-1.5f;
		}

		//기본 적 초록 총알 재생성
		if (_enemyBullet[i]._rc_B_green.bottom > 1500 )
		{
			if(_basicGreenDead[i]==false)_enemyBullet[i]._rc_B_green = RectMake(_enemy[i]._rc_B_green.left+23, _enemy[i]._rc_B_green.bottom+23, 18, 18);
		}

		//기본 적 초록 사이드 총알 재생성
		if (_enemyBullet[i]._rc_B_green_side.bottom > 1500 )
		{
			_enemyBullet[i]._rc_B_green_side = RectMake(_enemy[i]._rc_B_green_side.left + 23, _enemy[i]._rc_B_green_side.bottom + 23, 36, 36);
		}

		//기본 적 회색 총알 재생성
		if (_enemyBullet[i]._rc_B_gray.bottom > 1500 )
		{
			_enemyBullet[i]._rc_B_gray = RectMake(_enemy[i]._rc_B_gray.left + 23, _enemy[i]._rc_B_gray.bottom + 23, 18, 18);
		}

		//기본 적 회색 사이드 총알 재생성
		if (_enemyBullet[i]._rc_B_gray_side.bottom > 1500 )
		{
			_enemyBullet[i]._rc_B_gray_side = RectMake(_enemy[i]._rc_B_gray_side.left + 23, _enemy[i]._rc_B_gray_side.bottom + 23, 36, 36);
		}
	}
}

//중간 보스 움직임
void mainGame::moveMiddleboss()
{
	if (_showEnemycount >= 2650 ) //2650
	{
		_rc_middle_Gray.top += _middleBossSpeed;
		_rc_middle_Gray.bottom += _middleBossSpeed;
		_rc_middle_Green.top += _middleBossSpeed;
		_rc_middle_Green.bottom += _middleBossSpeed;
	}

	//if (_showEnemycount >= 3050) //2650
	//{
	//	_rc_middle_Gray.top += _middleBossSpeed;
	//	_rc_middle_Gray.bottom += _middleBossSpeed;
	//	_rc_middle_Green.top += _middleBossSpeed;
	//	_rc_middle_Green.bottom += _middleBossSpeed;
	//}
}

//중간보스 총알 움직임
void mainGame::moveBulletMiddleboss()
{
	if(_showEnemycount >=2650)
	{ 
	for (int i = 0; i < BOSSBULLET; i++)
	{
		//_rc_middle_Green_Bullet[i] = RectMake(_middleBossBulletGreenX[i], _middleBossBulletGreenY[i], 25, 25);
		//_rc_middle_Gray_Bullet[i] = RectMake(_middleBossBulletGrayX[i], _middleBossBulletGrayY[i], 25, 25);
		//_middleBossBulletAngle+=5.5f;

		_rc_middle_Green_Bullet[i] = RectMake(_middleBossBulletGreenX[i], _middleBossBulletGreenY[i], 30, 30);
		_rc_middle_Gray_Bullet[i] = RectMake(_middleBossBulletGrayX[i], _middleBossBulletGrayY[i], 30, 30);

		_middleBossBulletGreenX[i] += cosf(-_middleBossBulletAngle) *_middleBossBulletSpeed[i];
		_middleBossBulletGreenY[i] += -sinf(-_middleBossBulletAngle) *_middleBossBulletSpeed[i];
		_middleBossBulletGrayX[i] += cosf(-_middleBossBulletAngle) * _middleBossBulletSpeed[i];
		_middleBossBulletGrayY[i] += -sinf(-_middleBossBulletAngle) * _middleBossBulletSpeed[i];

		_middleBossBulletGreenX[i] += cosf(RANDOM->Range(-_middleBossBulletAngle *4, _middleBossBulletAngle / 2)) *_middleBossBulletSpeed[i];
		_middleBossBulletGreenY[i] += -sinf(RANDOM->Range(-_middleBossBulletAngle*4, _middleBossBulletAngle / 2)) *_middleBossBulletSpeed[i];
		_middleBossBulletGrayX[i] += cosf(RANDOM->Range(-_middleBossBulletAngle*4, _middleBossBulletAngle /2)) * _middleBossBulletSpeed[i];
		_middleBossBulletGrayY[i] += -sinf(RANDOM->Range(-_middleBossBulletAngle *4, _middleBossBulletAngle /2)) * _middleBossBulletSpeed[i];
	}
	}

	//if (_showEnemycount >= 3050)
	//{
	//	for (int i = 0; i < BOSSBULLET; i++)
	//	{
	//		//_rc_middle_Green_Bullet[i] = RectMake(_middleBossBulletGreenX[i], _middleBossBulletGreenY[i], 25, 25);
	//		//_rc_middle_Gray_Bullet[i] = RectMake(_middleBossBulletGrayX[i], _middleBossBulletGrayY[i], 25, 25);
	//		//_middleBossBulletAngle+=5.5f;
	//
	//		_rc_middle_Green_Bullet[i] = RectMake(_middleBossBulletGreenX[i], _middleBossBulletGreenY[i], 30, 30);
	//		_rc_middle_Gray_Bullet[i] = RectMake(_middleBossBulletGrayX[i], _middleBossBulletGrayY[i], 30, 30);
	//
	//		_middleBossBulletGreenX[i] += cosf(-_middleBossBulletAngle) *_middleBossBulletSpeed[i];
	//		_middleBossBulletGreenY[i] += -sinf(-_middleBossBulletAngle) *_middleBossBulletSpeed[i];
	//		_middleBossBulletGrayX[i] += cosf(-_middleBossBulletAngle) * _middleBossBulletSpeed[i];
	//		_middleBossBulletGrayY[i] += -sinf(-_middleBossBulletAngle) * _middleBossBulletSpeed[i];
	//
	//		_middleBossBulletGreenX[i] += cosf(RANDOM->Range(-_middleBossBulletAngle * 4, _middleBossBulletAngle / 2)) *_middleBossBulletSpeed[i];
	//		_middleBossBulletGreenY[i] += -sinf(RANDOM->Range(-_middleBossBulletAngle * 4, _middleBossBulletAngle / 2)) *_middleBossBulletSpeed[i];
	//		_middleBossBulletGrayX[i] += cosf(RANDOM->Range(-_middleBossBulletAngle * 4, _middleBossBulletAngle / 2)) * _middleBossBulletSpeed[i];
	//		_middleBossBulletGrayY[i] += -sinf(RANDOM->Range(-_middleBossBulletAngle * 4, _middleBossBulletAngle / 2)) * _middleBossBulletSpeed[i];
	//	}
	//}
}

//플레이어 애니매이션
void mainGame::animationPlayer()
{
	switch (_statePlayer)
	{
	case IDLE_Player:
		_count++;
		_idle->setFrameY(0);
		if (_count % 5 == 0)
		{
			_index++;
			if (_index > 2)
			{
				_index = 0;
			}
			_idle->setFrameX(_index);
		}
		break;
	case LEFT_Player:
		_count++;
		_left->setFrameY(0);
		if (_count % 5 == 0)
		{
			_index++;
			if (_index > 3)
			{
				_index = 3;
			}
			_left->setFrameX(_index);
		}
		break;
	case RIGHT_Player:
		_count++;
		_right->setFrameY(0);
		if (_count % 5 == 0)
		{
			_index++;
			if (_index > 3)
			{
				_index = 3;
			}
			_right->setFrameX(_index);
		}
		break;
	case DEAD_Player:
		_count++;
		_dead->setFrameY(0);
		if (_count % 5 == 0)
		{
			_index++;
			if (_index > 5)
			{
				_index = 5;
			}
			_dead->setFrameX(_index);
		}
		break;
	}
}

//플레이어 죽음
void mainGame::deadPlayer()
{
	if (_player._HP.right <= 0)
	{
		_statePlayer = DEAD_Player;
		if (_statePlayer == DEAD_Player)
		{
			_GameOver = true;
			_player._dead = true;
			_deadCount++;
			if (_deadCount == 150)
			{
				this->init();
			}
		}
	}
}

//적 파괴 --> 여기 해결하기 
void mainGame::destoryEnemy()
{
	RECT temp4;
	for (int i = 0; i < ENEMY; i++)
	{
		for (int j = 0; j < BULLET; j++)
		{
			//기본 초록 적 격추
			if (IntersectRect(&temp4, &_enemy[i]._rc_B_green, &_playerBullet[j]._rc))
			{
				_basicGreenHpCount++;
				if (_basicGreenHpCount = 3)
				{
					_basicGreenDead[i] = true;
					_basicGreenHpCount = 0;
				}

			}

			//기본 초록 사이드 적 격추
			if (IntersectRect(&temp4, &_enemy[i]._rc_B_green_side, &_playerBullet[j]._rc))
			{
				_basicGreenSideHpCount++;
				if (_basicGreenSideHpCount = 3)
				{
					_basicGreenSideDead[i] = true;
					_basicGreenSideHpCount = 0;
				}

			}

			//기본 적 회색 격추
			if (IntersectRect(&temp4, &_enemy[i]._rc_B_gray, &_playerBullet[i]._rc))
			{
				_basicGrayHpCount++;
				if (_basicGrayHpCount == 3)
				{
					_basicGrayDead[i] = true;
					_basicGrayHpCount = 0;
				}
			}

			//기본 회색 사이드 적 격추
			if (IntersectRect(&temp4, &_enemy[i]._rc_B_gray_side, &_playerBullet[j]._rc))
			{
				_basicGraySideHpCount++;
				if (_basicGraySideHpCount = 3)
				{
					_basicGraySideDead[i] = true;
					_basicGraySideHpCount = 0;
				}

			}
		}
	}
	

	//if (IntersectRect(&temp4, &_rc_middle_Gray, &_rc_middle_Green))
	//{
	//	_basicSideDead = true;
	//}
	
}

//마지막 보스 움직임
void mainGame::moveLastboss()
{

	if (_showEnemycount >= 3000)//3000
	{
		//_rc_lastBoss = RectMake(_lastBossX, _lastBossY, 825, 450);
		//40,1000
		//_rc_lastBoss.top -= _lastBossSpeed;
		//_rc_lastBoss.bottom -= _lastBossSpeed;
		_lastBossY -= 1.0f;
	}
}

//마지막 보스 총알 발사
void mainGame::shootLastBoss()
{
	for (int i = 0; i < BOSSBULLET; i++)
	{
		if (_lastBulletFire[i])continue;
		_lastBulletFire[i] = true;
		_lastBossBulletMoveAngle[i] = _lastBossBulletAngle;
		_lastBossBulletMoveX[i] = 300;
		_lastBossBulletMoveY[i] = 300;
		break;
	}
}

//마지막 보스 총알 움직임
void mainGame::moveBulletLastboss()
{
	for (int i = 0; i < BOSSBULLET; i++) 
	{ 
		
		if (!_lastBulletFire[i])continue;

		_lastBossBulletMoveX[i] += cosf(_lastBossBulletMoveAngle[i]) * _lastBossBulletSpeed[i];
		_lastBossBulletMoveY[i] += -sinf(_lastBossBulletMoveAngle[i]) * _lastBossBulletSpeed[i];
		//_rc_lastBoss_Bullet[i] = RectMakeCenter(_lastBossBulletX[i], _lastBossBulletY[i], 40, 40);
	//_lastBossBulletAngle[i] = _lastBossBulletMoveAngle;
	//_lastBossBulletX[i] = cosf(_lastBossBulletAngle[i])*_lastBossBulletSpeed[i]; 
	//_lastBossBulletY[i] = -sinf(_lastBossBulletAngle[i])*_lastBossBulletSpeed[i];
	//_lastBossBulletMoveAngle += 0.1f;
	//_lastBossBulletMoveX[i] = RANDOM->Range(_lastBossBulletX[i]*2, _lastBossBulletX[i]/2);
	//_lastBossBulletMoveY[i] = RANDOM->Range(_lastBossBulletY[i] * 2, _lastBossBulletY[i] / 2);
	//_rc_lastBoss_Bullet[i] = RectMakeCenter(_lastBossBulletMoveX[i], _lastBossBulletMoveY[i], 40, 40);
		
		
	}
}

//UFO 움직임
void mainGame::moveET()
{
	if (_etAttack) 
	{
		if (_moveCountEt % 30 == 0)
		{
			
				_rc_ET = RectMake(RANDOM->Range(0, 800), 0, 100, 78);
			
		}
	}
}

//UFO 총알 움직임
void mainGame::moveBulletEt()
{
	if (_etAttack) 
	{
		_rc_ET_Bullet.top += 10.0f;
		_rc_ET_Bullet.bottom += 10.0f;
		if (_rc_ET_Bullet.top >= 1000)
		{
				_rc_ET_Bullet = RectMake(_rc_ET.left, _rc_ET.bottom, 70, 335);
		}
	}
}



//ET 애니메이션
void mainGame::animationET()
{
	switch (_stateEt)
	{
	case IDLE_Et:
		_countEt++;
		_ET->setFrameY(0);
		if (_countEt % 10 == 0)
		{
			_index_Et++;
			if (_index_Et > 15)
			{
				_index_Et = 0;
			}
			_ET->setFrameX(_index_Et);
		}
		break;
	case DEAD_Et:
		_countEt++;
		_ET_Dead->setFrameY(0);
		if (_countEt % 10 == 0)
		{
			_index_Et++;
			if (_index_Et > 22)
			{
				_index_Et = 22;
			}
			_ET_Dead->setFrameX(_index_Et);
		}
		break;
	}
}

//충돌
void mainGame::collision()
{
	//총알 충돌
	RECT _temp1;
	for (int i = 0; i < ENEMY; i++)
	{
		//기본 적 데미지
		if (IntersectRect(&_temp1, &_enemyBullet[i]._rc_B_green, &_player._rc) || IntersectRect(&_temp1, &_enemyBullet[i]._rc_B_gray, &_player._rc))
		{
		//	_player._HP.right -= 10;
		//	_player._showHp -= 10;
		}
	
		//중간보스 닿았을떄 데미지
		if (IntersectRect(&_temp1, &_rc_middle_Green_Bullet[i], &_player._rc) || IntersectRect(&_temp1, &_rc_middle_Gray_Bullet[i], &_player._rc))
		{
		//	_player._HP.right -=1;
		//	_player._showHp -= 1;
		}
		
		//ET총알 데미지
		if(IntersectRect(&_temp1, &_rc_ET_Bullet, &_player._rc))
		{
		//	_player._HP.right -= 1;
		//	_player._showHp -= 1;
		}
	
		//사이드 적 데미지
		if (IntersectRect(&_temp1, &_enemyBullet[i]._rc_B_green_side, &_player._rc) || IntersectRect(&_temp1, &_enemyBullet[i]._rc_B_gray_side, &_player._rc))
		{
		//	_player._HP.right -= 10;
		//	_player._showHp -= 10;
		}
	}
	
	//중간 보스 직접 충돌
	if (IntersectRect(&_temp1, &_rc_middle_Gray, &_player._rc) || IntersectRect(&_temp1, &_rc_middle_Green, &_player._rc))
	{
		
		//_player._HP.right -= 25;
		//_player._showHp -= 25;
	}
	
	//보스 총알 충돌
	for (int i = 0; i < BOSSBULLET; i++)
	{
		if (IntersectRect(&_temp1, &_rc_lastBoss_Bullet[i], &_player._rc))
		{
			//_player._HP.right -= 5;
			//_player._showHp -= 5;
			
		}
	}
}

//벽 충돌
void mainGame::wallCollision()
{
	RECT _temp2;
	if (IntersectRect(&_temp2, &_rc_lastBoss, &wall))
	{
		_etAttack = false;
		_bgMove = false;
		_showBossBullet = true;
		_stateEt = DEAD_Et;
		_showEnemycount = 0;
		this->shootLastBoss();
	}

}

