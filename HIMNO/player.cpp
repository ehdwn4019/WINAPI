#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	//�÷��̾� �ʱ�ȭ
	_himno._x = WINSIZEX/2-50;
	_himno._y = WINSIZEY/2+320;
	_himno._speed = 0.0f;
	_himno._jumpSpeed = 0.f;
	_himno._gravity = 0.0f;
	_himno._angle = PI / 2;
	_himno._isJump = false;
	_himno._isJumpDown = false;
	_himno._jumpCount = 0;
	_himno._isDash = false;
	_himno._height = _himno._rcPlayer.bottom - _himno._rcPlayer.top;

	//�÷��̾� ���� �ʱ�ȭ
	_isLeft = false;
	
	//�÷��̾� ���� �ʱ�ȭ
	_state = HIMNO_IDLE;

	//�÷��̾� ���� �̹��� �ʱ�ȭ
	_idle=IMAGEMANAGER->addFrameImage("IDLE", "images/player/IDLE.bmp", 343, 120, 6, 2);
	_crouch = IMAGEMANAGER->addFrameImage("CROUCH", "images/player/CROUCH.bmp", 60, 94,1,2);
	_dash = IMAGEMANAGER->addFrameImage("DASH", "images/player/DASH.bmp", 60, 114, 1, 2);
	_jump = IMAGEMANAGER->addFrameImage("JUMP", "images/player/JUMP.bmp", 60, 120, 1, 2);
	_fall = IMAGEMANAGER->addFrameImage("FALL", "images/player/FALL.bmp", 60, 126, 1, 2);
	_run = IMAGEMANAGER->addFrameImage("RUN", "images/player/RUN.bmp", 343, 120, 6, 2);
	_slide = IMAGEMANAGER->addFrameImage("SLIDE", "images/player/SLIDE_����.bmp", 50, 120, 1, 2);
	_attack = IMAGEMANAGER->addFrameImage("ATTACK", "images/player/ATTACK.bmp", 265, 120, 5, 2);
	//_climb = IMAGEMANAGER->addFrameImage("CLIMB", "images/player/CLIMB.bmp",1500,300,10,2);
	_climb = IMAGEMANAGER->addFrameImage("CLIMB_����", "images/player/CLIMB_����.bmp", 620, 126, 10, 2);

	//������ �̹��� ���� �ʱ�ȭ
	_index = _count = _dashCount=0;

	//���� ���� �ʱ�ȭ
	_stopGame = false;
	_stopContinue = false;
	_stopMainMenu = false;
	_rcContionue = RectMake(520, 350, 199, 29);
	_rcMainMenu = RectMake(510, 450, 218, 29);

	//���� ���� �ʱ�ȭ
	_loopX = 0;
	_loopY = 0;
	
	//�� ��Ʈ �ʱ�ȭ
	_rcWater = RectMake(0, 1100, 1200, 4000);

	//���� ���� �̹��� �ʱ�ȭ 
	_stopBg = IMAGEMANAGER->addImage("stopBg", "images/stopGame/menuBackGround.bmp", 1200, 3000);
	_stopPause = IMAGEMANAGER->addImage("stopPause", "images/stopGame/Pause.bmp", 457, 110);
	_stopMainMenuOn = IMAGEMANAGER->addImage("stopMainMenuOn", "images/stopGame/mainmenuOff.bmp", 218, 29);
	_stopMainMenuOff = IMAGEMANAGER->addImage("stoprMainMenuOff", "images/stopGame/mainmenuOn.bmp", 218, 29);
	_stopContinueOn = IMAGEMANAGER->addImage("stopContinueOff", "images/stopGame/continueOn.bmp", 199, 29);
	_stopContinueOff = IMAGEMANAGER->addImage("stopContinueOn", "images/stopGame/continueOff.bmp", 199, 29);

	//�� ��ǥ �ʱ�ȭ 
	_mapX = 0;
	_mapY = -1900;
	//�� ��� �� ���� �̹���
	_mapBg = IMAGEMANAGER->addImage("mapBg", "images/bgMap.bmp", 1200, 4000);
	//�� �̹���
	_map = IMAGEMANAGER->addImage("map", "images/showMap.bmp", 1200, 2800, true, RGB(255, 255, 255));
	//�� �浹 �̹���
	_mapCollision = IMAGEMANAGER->addImage("mapCollision", "images/collisonMap_����.bmp", 1200, 3000);
	//�� �ٴ� �� �̹���
	_water = IMAGEMANAGER->addImage("water", "images/water.bmp", 1200, 4000);

	//Ŭ���� ����Ʈ �̹���
	_clearPoint = IMAGEMANAGER->addFrameImage("clearPoint", "images/clearPoint.bmp", 350, 72,7,1);
	//Ŭ���� ����Ʈ ������ �̹��� ���� �ʱ�ȭ
	_clearPointCount = 0;
	_clearPointIndex = 0;

	//ȭ�� �̹���
	_allow_L=IMAGEMANAGER->addImage("allow_L", "images/allow_L.bmp", 30, 52);
	_allow_R = IMAGEMANAGER->addImage("allow_R", "images/allow_R.bmp", 30, 52);
	//ȭ�� ��ħ �̹���
	_allow_B=IMAGEMANAGER->addImage("allow_B", "images/allow_B.bmp", 4, 60);
	//ȭ�� ��ǥ �ʱ�ȭ
	_allowX_L = 3;
	_allowX_R = 1166;
	_allowY = 0;
	
	//���Ǿ� �̹��� 
	_npc = IMAGEMANAGER->addImage("npc", "images/npc.bmp", 43, 60);

	//���� ���� ����Ʈ
	_deadTreeEffect = IMAGEMANAGER->addImage("deadTreeEffect", "images/deadTreeEffect.bmp", 128, 128);
	//���� ���� ����Ʈ ������ ���� 
	_alphaTree = 0;

	//���̹���
	_clearDoor = IMAGEMANAGER->addImage("clearDoor", "images/clearDoor.bmp", 70, 109);
	_deadDoor_G = IMAGEMANAGER->addImage("deadDoor_G", "images/deadDoor_G.bmp", 70, 109);
	_deadDoor_R = IMAGEMANAGER->addImage("deadDoor_R", "images/deadDoor_R.bmp", 70, 109);

	//�뽬 ������ �̹���
	_dashItem = IMAGEMANAGER->addImage("dashItem", "images/dashItem.bmp", 30, 28);
	//�뽬 ��ų �ʱ�ȭ
	_canDash = false;

	//���� �̹���
	_trap = IMAGEMANAGER->addImage("trap", "images/trap.bmp", 1177, 60);

	//RECT tempRect = RectMake(250, _rcMap.top + 1504, 50, 66);

	//Ŭ���� ����Ʈ �ʱ�ȭ 
	for (int i = 0; i < CLEARPOINT; i++)
	{
		//_rcClearPoint[i] = RectMake(250, _rcMap.top + 1504, 50, 66);
		//_vClearPoint.push_back(_rcClearPoint[i]);
		_getJewel[i] = false;
		_rotateJewelAngle[i] = float(i)*1.3f;
	}

	
	//���� �ؿ� �κ��̹��� 
	_jewel_B = IMAGEMANAGER->addImage("jewel_B", "images/jewel_B.bmp", 38, 29);
	_rotateJewel = IMAGEMANAGER->addImage("jewel", "images/rotateJewel.bmp", 130, 130);

	_scaleDash = 0.0f;

	_showDash = false;
	_showNpc = true;

	_LEFT = false;
	_RIGHT = false;

	_slideWall = false;
	_grabWall = false;

	
	//ī�޶� �浹 �����ִ� ��Ʈ
	_rcWall = RectMake(0, 0, 1200, 10);

	//���� Ŭ���� �ʱ�ȭ
	_isGameClear = false;
	_clearCount = 0;

	//���� Ŭ���� ���� �̹��� 
	_gameClear = IMAGEMANAGER->addImage("gameClear","images/gameClear.bmp",70,30);

	//���� �߰� 
	SOUNDMANAGER->addSound("���", "SOUND/Nine Sisters - Kenji Kawai.mp3");

	

	//���� ���
	SOUNDMANAGER->play("���");


	//SOUNDMANAGER->stop("���");

	return S_OK;
}

void player::release()
{

}

void player::update()
{
	


	//�Ͻ� ����
	if (INPUT->GetKey(VK_RETURN))
	{
		_stopGame = true;
	}

	//�Ͻ� ���� ���¿��� �ൿ �����ϱ� 
	if (INPUT->GetKeyUp(VK_LBUTTON))
	{
		//����ϱ�
		if (PtInRect(&_rcContionue, _ptMouse))
		{
			_stopContinue = false;
			_stopGame = false;
		}

		//���θ޴� ���� 
		if (PtInRect(&_rcMainMenu, _ptMouse))
		{
			_stopMainMenu = false;
			//���� ����
			SOUNDMANAGER->stop("���");

			SCENEMANAGER->loadScene("����ȭ��");
		}
	}

	//�Ͻ� ���� �ƴҶ� -> ���⼭ �浹 ó�� �ϱ� 
	if (_stopGame == false)
	{
		//�� ��������(�� ������)
		_rcWater.top -= 1;
		_rcWater.bottom += 50;

		//���� ��ų ���� ���� 
		_loopX+=1.5f;
		_loopX -= 1.4f;

		//���İ� ���� ��ų ���� 
		_alphaTree++;

		//�÷��̾� �ȼ� �浹 ��� ���� 
		_probeL = _himno._x + _mapX - 30;
		_probeR = _himno._x + _mapX + 30;
		_probeT = _himno._y - _mapY - 30;
		_probeB = _himno._y - _mapY + 30;

		//�÷��̾� ��Ʈ ��ġ �ʱ�ȭ
		_himno._rcPlayer = RectMakeCenter(_himno._x, _himno._y, 60, 60);

		//�÷��̾� ī�޶� ��ġ �ʱ�ȭ 
		_himno._rcCamera = RectMakeCenter(_himno._x, _himno._y - 250, 200, 550);

		//�� ��Ʈ �ʱ�ȭ 
		_rcMap = RectMake(_mapX, _mapY, 1200, 3000);

		//�÷��̾� ���� ȹ��� ��Ʈ �ʱ�ȭ 
		_rcRotateJewel = RectMakeCenter(_himno._x + 65, _himno._y + 65, 130, 130);

		_rcClearPoint[0] = RectMake(250, _rcMap.top + 1504, 50, 66);
		_rcClearPoint[1] = RectMake(898, _rcMap.top + 1250, 50, 66);
		_rcClearPoint[2] = RectMake(80, _rcMap.top + 825, 50, 66);
		_rcClearPoint[3] = RectMake(225, _rcMap.top + 248, 50, 66);
		_rcClearPoint[4] = RectMake(1150, _rcMap.top + 199, 50, 66);


		//ȭ�� ��ֹ� �ʱ�ȭ 
		_rcAllow[0] = RectMake(_allowX_L, _rcMap.top + 2586, 30, 52);
		_rcAllow[1] = RectMake(_allowX_R, _rcMap.top + 2255, 30, 52);
		_rcAllow[2] = RectMake(_allowX_L, _rcMap.top + 1795, 30, 52);
		_rcAllow[3] = RectMake(_allowX_R, _rcMap.top + 1583, 30, 52);
		_rcAllow[4] = RectMake(_allowX_L, _rcMap.top + 1455, 30, 52);
		_rcAllow[5] = RectMake(_allowX_R, _rcMap.top + 1245, 30, 52);
		_rcAllow[6] = RectMake(_allowX_L, _rcMap.top + 679, 30, 52);
		_rcAllow[7] = RectMake(_allowX_R, _rcMap.top + 335, 30, 52);

		//ȭ�� ��ֹ� ��ħ �ʱ�ȭ 
		_rcAllow[8] = RectMake(_rcMap.left, _rcMap.top + 2582,4,60 );
		_rcAllow[9] = RectMake(_rcMap.left+1196, _rcMap.top + 2251,4 ,60 );
		_rcAllow[10] = RectMake(_rcMap.left, _rcMap.top + 1791,4,60 );
		_rcAllow[11] = RectMake(_rcMap.left+1196, _rcMap.top + 1579,4 ,60 );
		_rcAllow[12] = RectMake(_rcMap.left, _rcMap.top + 1451,4 ,60 );
		_rcAllow[13] = RectMake(_rcMap.left+1196, _rcMap.top + 1241,4 ,60 );
		_rcAllow[14] = RectMake(_rcMap.left, _rcMap.top + 675,4 ,60 );
		_rcAllow[15] = RectMake(_rcMap.left+1196, _rcMap.top + 331,4 ,60 );

		//���� ���� ��Ʈ �ʱ�ȭ 
		_rcDeadTree = RectMake(38, _rcMap.top + 2267, 50, 165);

		//���Ǿ� ��Ʈ �ʱ�ȭ
		_rcNpc = RectMake(115, _rcMap.top+1911, 60, 60);

		//�뽬 ������ �ʱ�ȭ
		_rcDashItem = RectMake(140,_rcMap.top + 1945, 30, 28);

		//�� �ʱ�ȭ
		for (int i = 0; i < DOOR; i++)
		{
			_rcDoor[i] = RectMake(200 * i + 385, _rcMap.top + 73, 70, 109);
		}

		//�� ���� ���� �ʱ�ȭ 
		_rcTrap = RectMake(11.5f, _rcMap.top-35, 1177, 60);

		//�� ���� Ŭ���� ���� ��Ÿ���ִ� ��Ʈ �ʱ�ȭ
		for (int i = 0; i < GAMECLEAR; i++)
		{
			_rcGameClear[i] = RectMake(201 * i + 385, _rcMap.top + 42, 70, 30);
		}


		_scaleDash += 0.1f;

		for (int i = 0; i < CLEARPOINT; i++)
		{
			_rotateJewelAngle[i] += 0.05f;
		}
		

		_himno._gravity -= 1.0f;
		if (_himno._gravity < -6)
		{
			_himno._gravity = -6;
		}

		//Ŭ���� ����Ʈ ������ ������Ʈ
		_clearPointCount++;
		_clearPoint->setFrameY(1);
		if (_clearPointCount % 8 == 0)
		{
			_clearPointIndex++;
			if (_clearPointIndex > 7)
			{
				_clearPointIndex = 1;
			}
			_clearPoint->setFrameX(_clearPointIndex);
		}

		//�Ѿ� Ŭ����(ȭ��) ������Ʈ,���� �Լ� 
		//this->_allow->update();
		//this->_allow->move();

		_dashCount++;

		//�÷��̾� �̵� �Լ� 
		this->playerMove();

		//�÷��̾� �ִϸ��̼� �Լ�
		this->playerAnimation();

		//�÷��̾� �浹 �Լ� 
		this->playerCollision();

		//ȭ�� �߻� �Լ� 
		this->allowShoot();

		//�÷��̾� ���� �Լ� 
		this->playerDead();

		//�÷��̾� ��Ƴ��� �Լ�
		this->playerAlive();
		
	}

	
}
 
void player::render() 
{ 
	//Rectangle(getMemDC(), _rcDeadTree);

	//�Ͻ����� ȭ�� ���� 
	if (_stopGame == true)
	{
		IMAGEMANAGER->render("stopBg", getMemDC(), 0, 0);
		IMAGEMANAGER->render("stopPause", getMemDC(), 400, 100);
		if (_stopContinue == false)
		{
			IMAGEMANAGER->render("stopContinueOn", getMemDC(), 520, 350);
		}
		if (_stopMainMenu == false)
		{
			IMAGEMANAGER->render("stopMainMenuOn", getMemDC(), 510, 450);
		}
		if (_stopContinue == true)
		{
			IMAGEMANAGER->render("stopContinueoff", getMemDC(), 520, 350);
		}
		if (_stopMainMenu == true)
		{
			IMAGEMANAGER->render("stopMainMenuOff", getMemDC(), 510, 450);
		}
	}
	//�Ͻ����� �ƴҶ� 
	else
	{
		//�� ���� �̹��� ���� 
		IMAGEMANAGER->alphaRender("mapBg",getMemDC(),_rcMap.left,_rcMap.top-1000,70);
		
		//�� �̹��� ���� 
		IMAGEMANAGER->render("map", getMemDC(), _rcMap.left, _rcMap.top);

		//IMAGEMANAGER->frameRender("CLIMB_����", getMemDC(), _himno._rcPlayer.left, _himno._rcPlayer.top);

		//npc
		if (_showNpc)
		{
			//npc ���� 
			IMAGEMANAGER->render("npc", getMemDC(), _rcNpc.left, _rcNpc.top);
			//npc ����Ʈ ����
			IMAGEMANAGER->alphaRender("deadTreeEffect", getMemDC(), _rcNpc.left - 40, _rcNpc.top - 70, _alphaTree);
		}
		//�뽬 ������ ����
		if (_showDash)
		{
			IMAGEMANAGER->rotateRender("dashItem", getMemDC(), _rcDashItem.left, _rcDashItem.top, _scaleDash);
		}

		//�� ���� 
		IMAGEMANAGER->render("deadDoor_R", getMemDC(), _rcDoor[0].left, _rcDoor[0].top);
		IMAGEMANAGER->render("clearDoor", getMemDC(), _rcDoor[1].left, _rcDoor[1].top);
		IMAGEMANAGER->render("deadDoor_G", getMemDC(), _rcDoor[2].left, _rcDoor[2].top);

		

		//Ŭ���� ����Ʈ ���� 
		for (int i = 0; i < CLEARPOINT; i++)
		{
			if (!_getJewel[i])
			{
				IMAGEMANAGER->frameRender("clearPoint", getMemDC(), _rcClearPoint[i].left, _rcClearPoint[i].top);
				//Rectangle(getMemDC(), _rcClearPoint[i]);
			}
			//���� �ؿ� �κ� �̹��� ����
			else
			{
				IMAGEMANAGER->render("jewel_B", getMemDC(), _rcClearPoint[i].left + 6, _rcClearPoint[i].top + 43);
				//�÷��̾� ���� ȹ��� ����
				_rotateJewel->rotateRender(getMemDC(), _rcRotateJewel.left, _rcRotateJewel.top, _rotateJewelAngle[i]);
				
			}
		}

		//�� ���� ����Ŭ���� ���� ����
		for (int i = 0; i < GAMECLEAR; i++)
		{
			IMAGEMANAGER->render("gameClear", getMemDC(), _rcGameClear[i].left, _rcGameClear[i].top);
			//Rectangle(getMemDC(), _rcGameClear[i]);
		}

		//���� ���� ����Ʈ ���� 
		IMAGEMANAGER->alphaRender("deadTreeEffect", getMemDC(), _rcDeadTree.left-43, _rcDeadTree.top-55,_alphaTree);
		//IMAGEMANAGER->render("deadTreeEffect", getMemDC(), _rcDeadTree.left, _rcDeadTree.top);

		//ȭ�� ��ֹ� �̹��� ����
		for (int i = 0; i < ALLOW; i++)
		{
			if (i >= 0 && i <= 7)
			{
				if (i % 2 == 0)
				{
					IMAGEMANAGER->render("allow_L", getMemDC(), _rcAllow[i].left, _rcAllow[i].top);
				}
				else
				{
					IMAGEMANAGER->render("allow_R", getMemDC(), _rcAllow[i].left, _rcAllow[i].top);
				}
				
			}
			else
			{
				IMAGEMANAGER->render("allow_B", getMemDC(), _rcAllow[i].left, _rcAllow[i].top);
			}
		}

		//�� ���� ���� �̹��� ����
		IMAGEMANAGER->render("trap", getMemDC(), _rcTrap.left, _rcTrap.top);

		

		//�÷��̾� ��Ʈ ���̱� 
		//if (INPUT->GetToggleKey(VK_CONTROL))
		//{
		//	Rectangle(getMemDC(), _himno._rcPlayer);
		//}
		if (INPUT->GetToggleKey('B'))
		{
			Rectangle(getMemDC(), _himno._rcCamera);
		}

		//�÷��̾� ���º� �̹��� ���� 
		if (_state == HIMNO_IDLE)
		{
			IMAGEMANAGER->frameRender("IDLE", getMemDC(), _himno._rcPlayer.left, _himno._rcPlayer.top);
		}
		if (_state == HIMNO_CROUCH)
		{
			IMAGEMANAGER->frameRender("CROUCH", getMemDC(), _himno._rcPlayer.left, _himno._rcPlayer.top-7);
		}
		if (_state == HIMNO_DASH)
		{
			IMAGEMANAGER->frameRender("DASH", getMemDC(), _himno._rcPlayer.left, _himno._rcPlayer.top);
		}
		if (_state == HIMNO_JUMP)
		{
			IMAGEMANAGER->frameRender("JUMP", getMemDC(), _himno._rcPlayer.left, _himno._rcPlayer.top);
		}
		if (_state == HIMNO_FALL)
		{
			IMAGEMANAGER->frameRender("FALL", getMemDC(), _himno._rcPlayer.left, _himno._rcPlayer.top);
		}
		if (_state == HIMNO_RUN)
		{
			IMAGEMANAGER->frameRender("RUN", getMemDC(), _himno._rcPlayer.left, _himno._rcPlayer.top);
		}
		if (_state == HIMNO_SLIDE)
		{
		IMAGEMANAGER->frameRender("SLIDE", getMemDC(), _himno._rcPlayer.left, _himno._rcPlayer.top, 0, 1);
		}
		if (_state == HIMNO_CLIMB)
		{
			IMAGEMANAGER->frameRender("CLIMB_����", getMemDC(), _himno._rcPlayer.left, _himno._rcPlayer.top);
		}
		if (_state == HIMNO_ATTACK && _isLeft)
		{
			IMAGEMANAGER->frameRender("ATTACK", getMemDC(), _himno._rcPlayer.left - 10, _himno._rcPlayer.top - 5);
		}
		else if (_state == HIMNO_ATTACK && !_isLeft)
		{
			IMAGEMANAGER->frameRender("ATTACK", getMemDC(), _himno._rcPlayer.left + 10, _himno._rcPlayer.top - 5);
		}

		//�� �ٴ� �� �̹��� ���� 
		IMAGEMANAGER->loopRender("water", getMemDC(), &_rcWater, _loopX, _loopY);

		//CHAR str[128];
		//sprintf(str, "%d %f %f %d %d %f", _himno._y, _probeR, _probeL,_himno._jumpCount, _himno._isJump,_himno._gravity);
		//textOut(getMemDC(), 100, WINSIZEY - 50, str, strlen(str));
		
	}
}

void player::playerAnimation()
{
	switch (_state)
	{
	//idle ����
	case HIMNO_IDLE:
		//����
		if (_isLeft)
		{
			_count++;
			_idle->setFrameY(1);
			if (_count % 5 == 0)
			{
				_index++;
				if (_index > 6)
				{
					_index = 0;
				}
				_idle->setFrameX(_index);
			}
		}
		//������
		else 
		{
			_count++;
			_idle->setFrameY(0);
			if (_count % 5 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = 6;
				}
				_idle->setFrameX(_index);
			}
		}
		break;

	//crouch ����
	case HIMNO_CROUCH:
		//����
		if (_isLeft)
		{
			_count++;
			_crouch->setFrameY(1);
			if (_count % 5 == 0)
			{
				_index++;
				if (_index > 0)
				{
					_index = 0;
				}
				_crouch->setFrameX(_index);
			}
		}
		//������ 
		else 
		{
			_count++;
			_crouch->setFrameY(0);
			if (_count % 5 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = 1;
				}
				_crouch->setFrameX(_index);
			}
		}
		break;

	// run ����
	case HIMNO_RUN:
		//����
		if (_isLeft)
		{
			_count++;
			_run->setFrameY(1);
			if (_count % 5 == 0)
			{
				_index++;
				if (_index > 5)
				{
					_index = 0;
				}
				_run->setFrameX(_index);
			}
		}
		else //������ ������ �ִϸ��̼�
		{
			_count++;
			_run->setFrameY(0);
			if (_count % 5 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = 5;
				}
				_run->setFrameX(_index);
			}
		}
		break;

    //dash ����
	case HIMNO_DASH:
		//����
		if (_isLeft)
		{
			_count++;
			_dash->setFrameY(1);
			if (_count % 5 == 0)
			{
				_index++;
				if (_index > 0)
				{
					_index = 0;
				}
				_dash->setFrameX(_index);
			}
		}
		//������
		else 
		{
			_count++;
			_dash->setFrameY(0);
			if (_count % 5 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = 1;
				}
				_dash->setFrameX(_index);
			}
		}
		break;

	//climb ����
	case HIMNO_CLIMB:
		//����
		if (_isLeft)
		{
			_count++;
			_climb->setFrameY(1);
			if (_count % 5 == 0)
			{
				_index++;
				if (_index > 10)
				{
					_index = 0;
				}
				_climb->setFrameX(_index);
			}
		}
		//������
		else
		{
			_count++;
			_climb->setFrameY(0);
			if (_count % 5 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = 10;
				}
				_climb->setFrameX(_index);
			}
		}
		break;

	//slide ����
	//case HIMNO_SLIDE:
	//	//����
	//	if (_isLeft)
	//	{
	//		_count++;
	//		_slide->setFrameY(1);
	//		if (_count % 10 == 0)
	//		{
	//			_index++;
	//			if (_index > 0)
	//			{
	//				_index = 0;
	//			}
	//			_slide->setFrameX(_index);
	//		}
	//	}
	//	//������
	//	else
	//	{
	//		_count++;
	//		_slide->setFrameY(0);
	//		if (_count % 10 == 0)
	//		{
	//			_index--;
	//			if (_index < 0)
	//			{
	//				_index = 1;
	//			}
	//			_slide->setFrameX(_index);
	//		}
	//	}
	//	break;
	//

	//attack ����
	case HIMNO_ATTACK:
		//����
		if (_isLeft)
		{
			_count++;
			_attack->setFrameY(1);
			if (_count % 3 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = 5;
				}
				_attack->setFrameX(_index);
			}
		}
		else
		{
			_count++;
			_attack->setFrameY(0);
			if (_count % 3 == 0)
			{
				_index++;
				if (_index > 5)
				{
					_index = 0;
				}
				_attack->setFrameX(_index);
			}
		}

		break;

	//fall ����
	case HIMNO_FALL:
		//����
		if (_isLeft)
		{
			_count++;
			_fall->setFrameY(1);
			if (_count % 5 == 0)
			{
				_index++;
				if (_index > 0)
				{
					_index = 0;
				}
				_fall->setFrameX(_index);
			}
		}
		//������
		else
		{
			_count++;
			_fall->setFrameY(0);
			if (_count % 5 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = 1;
				}
				_fall->setFrameX(_index);
			}
		}
		break;

	//jump ����
	case HIMNO_JUMP:
		//����
		if (_isLeft)
		{
			_count++;
			_jump->setFrameY(1);
			if (_count % 5 == 0)
			{
				_index++;
				if (_index > 0)
				{
					_index = 0;
				}
				_jump->setFrameX(_index);
			}
		}
		//������
		else 
		{
			_count++;
			_jump->setFrameY(0);
			if (_count % 5 == 0)
			{
				_index--;
				if (_index < 0)
				{
					_index = 1;
				}
				_jump->setFrameX(_index);
			}
		}
		break;
	}
}

void player::playerMove()
{
	//�÷��̾� ���� �����̱�
	if (INPUT->GetKey(VK_LEFT) && _himno._rcPlayer.left>=0 && !_LEFT && !_himno._isDash)
	{
		_himno._x -= 5.2f;
		_state = HIMNO_RUN;
		_isLeft = true;
	}
	//�÷��̾� ������ �����̱� 
	else if (INPUT->GetKey(VK_RIGHT) && _himno._rcPlayer.right <= WINSIZEX && !_RIGHT && !_himno._isDash)
	{
		_himno._x += 5.2f;
		_state = HIMNO_RUN;
		_isLeft = false;
	}
	//�÷��̾� ������ ����
	if(INPUT->GetKeyUp(VK_LEFT) || INPUT->GetKeyUp(VK_RIGHT))
	{
		_state = HIMNO_IDLE;
	}

	//�÷��̾� �Ʒ��� ���̱�
	if (INPUT->GetKey(VK_DOWN) && _state==HIMNO_IDLE)
	{
		_state = HIMNO_CROUCH;

		if (_state == HIMNO_CROUCH)
		{
			_himno._rcPlayer.top += 20;
		}
	}
	
	//�÷��̾� ���� �õ�
	if (INPUT->GetKeyDown(VK_SPACE)&& _himno._jumpCount <= 1)
	{
		_himno._isJump = true;
		_himno._jumpCount++;
		_himno._gravity = 14.0f;
		if (_himno._jumpCount <= 1)
		{
			

		}
		
	}

	//�÷��̾� ���� 
	if (_himno._isJump)
	{
		_state = HIMNO_JUMP;
		_himno._y -=  _himno._gravity;
	
		//�������� ����
		if (_himno._gravity < 1.0f)
		{
			_state = HIMNO_FALL;
			
			if (_himno._gravity<-5.0f)
			{
				_state = HIMNO_IDLE;
			}
		}
		
	}
	//if (_himno._jumpCount == 1)
	//{
	//	_himno._isJump = true;
	//	
	//}
	//�÷��̾� �������� 
	if (_himno._jumpCount == 2)
	{
		//_himno._isJump = false;
		
	}

	
	if (_state != HIMNO_JUMP)
	{
		_himno._y -= _himno._gravity;
	}

	//�÷��̾� �뽬 ��ų ȹ��� 
	if (_canDash)
	{
		////�÷��̾� �뽬 �õ� 
		if (INPUT->GetKeyDown(VK_SHIFT))
		{
			_state = HIMNO_DASH;
			_himno._isDash = true;
			_dashCount = 0;

			
		}
	}

	//�÷��̾� �뽬 
	if ( _isLeft && _himno._isDash)
	{
		
		
		_state = HIMNO_DASH;
		_himno._x -= 13.5f;
		
		if (_dashCount >20)
		{
			_state = HIMNO_IDLE;
			_himno._isDash = false;
		}
		//�� ����ó��
		if (_himno._rcPlayer.left <= 0)
		{
			_himno._isDash = false;
		}
		
	}
	else if (!_isLeft&& _himno._isDash)
	{
		_state = HIMNO_DASH;
		_himno._x += 13.5f;
		if (_dashCount > 20)
		{
			_state = HIMNO_IDLE;
			_himno._isDash = false;
		}
	
		//�� ����ó��
		if (_himno._rcPlayer.right >= WINSIZEX)
		{
			_himno._isDash = false;
		}
	}
	
	//�� Ÿ�� ����
	if (_slideWall)
	{
		//_himno._gravity += 0.7f;


	}

	//�� ��� ����
	//if (_grabWall)
	//{
	//	_himno._y += _himno._y;
	//	_himno._gravity -= 10.2f;
	//}
	
	//�÷��̾� ����
	if (INPUT->GetKey('A'))
	{
		_state = HIMNO_ATTACK;
	}
}

void player::playerCollision()
{

	//�÷��̾� Ŭ���� ����Ʈ �浹
	RECT _temp5;
	for (int i = 0; i < CLEARPOINT; i++)
	{
		if (IntersectRect(&_temp5, &_rcClearPoint[i], &_himno._rcPlayer))
		{
			_getJewel[i] = true;
			//_isGameClear = true;


		}
	}

	//���� Ŭ���� ����
	if (_getJewel[0] && _getJewel[1] && _getJewel[2] && _getJewel[3] && _getJewel[4])
	{
		_isGameClear = true;
	}

	//�÷��̾� ī�޶� �浹 
	RECT _temp3;
	if (IntersectRect(&_temp3, &_himno._rcCamera, &_rcWall))
	{
		_mapY += 12;
		_rcWater.top += 6;
		_rcWater.bottom += 12;
		_himno._y += 12;
	}

	//�÷��̾� npc �浹
	if (INPUT->GetKey(VK_UP))
	{
		RECT _temp8;
		if (IntersectRect(&_temp8, &_himno._rcPlayer, &_rcNpc))
		{
			_showNpc = false;
			_showDash = true;

		}

	}

	//�뽬 ������ 
	if (_showDash)
	{
		if (INPUT->GetKey('Z'))
		{
			_showDash = false;
			_canDash = true;
		}
	}

	//�ȼ� �浹 ����
	for (int i = _probeT - 10; i < _probeT + 10; i++)
	{
		COLORREF color = GetPixel(_mapCollision->getMemDC(), _himno._x, i);
		//COLORREF color = GetPixel(_mapCollision->getMemDC(), _himno._x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		//COLORREF color1 = GetPixel(_mapCollision->getMemDC(), _himno._x-5, i);
		//int r1 = GetRValue(color1);
		//int g1= GetGValue(color1);
		//int b1 = GetBValue(color1);

		//if ((!(r == 255 && g == 0 && b == 255) || !(r1 == 255 && g1 == 0 && b1 == 255)) && _himno._gravity > 0)
		if (!(r == 255 && g == 0 && b == 255) && _himno._gravity > 0)
		{
			_himno._y = i + _mapY + 30;
			_himno._gravity -= _himno._gravity;

			//if(_himno._jumpCount==2) _himno._isJump = false;
			break;
		}
	}

	//�ȼ� �浹 �Ʒ���
	for (int i = _probeB - 10; i < _probeB + 10; i++)
	{
		//COLORREF color = GetPixel(_mapCollision->getMemDC(), _himno._x+5, i);
		COLORREF color = GetPixel(_mapCollision->getMemDC(), _himno._x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		//COLORREF color1 = GetPixel(_mapCollision->getMemDC(), _himno._x-5, i);
		//int r1 = GetRValue(color);
		//int g1 = GetGValue(color);
		//int b1 = GetBValue(color);

		//if ((!(r == 255 && g == 0 && b == 255) || !(r1 == 255 && g1 == 0 && b1 == 255)) && _himno._gravity < 0)
		if (!(r == 255 && g == 0 && b == 255) && _himno._gravity < 0)
		{
			_himno._y = i + _mapY - 30;
			_himno._gravity = 0.0f;
			_himno._jumpCount = 0;
			_himno._isJump = false;
			break;
		}
	}

	//�ȼ� �浹 ����
	for (int i = _probeL - 10; i < _probeL + 10; i++)
	{
		COLORREF color = GetPixel(_mapCollision->getMemDC(), i, _probeB - 10);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255) && !_himno._isJump)
		{
			//_himno._x = i + _mapX - 30;
			_LEFT = true;
			break;
		}
		//�ȼ� �浹 ���� ��Ÿ��(�����)
		else if (r == 255 && g == 255 && b == 0)
		{
			_state = HIMNO_SLIDE;
			//_LEFT = true;
			//_himno._isJump = true;
			_LEFT = true;
			if (_state == HIMNO_SLIDE && _LEFT)
			{
				_slideWall = true;
			}
		}
		//�ȼ� �浹 ���� �����(�ʷϻ�)
		else if (r == 0 && g == 255 && b == 30)
		{
			_state = HIMNO_CLIMB;
			if (_state == HIMNO_CLIMB && _LEFT)
			{
				_grabWall = true;
			}
		}
		else
		{
			_LEFT = false;
		}

		//�ȼ� �浹 ���� ��Ÿ��(�����)
		//if((r == 255 && g == 255 && b == 0))
		//{
		//	_state = HIMNO_SLIDE;
		//	//_LEFT = true;
		//	_himno._isJump = true;
		//
		//	if (_state == HIMNO_SLIDE)
		//	{
		//		_slideWall = true;
		//	}
		//
		//	//if (_state == HIMNO_SLIDE)
		//	//{
		//	//	_slideWall = true;
		//	//}
		//}
		//else
		//{
		//	_himno._isJump = false;
		//}

		//�ȼ� �浹 ���� �����(�ʷϻ�)
		//else if (!(r == 0 && g == 255 && b == 30))
		//{
		//	_state = HIMNO_CLIMB;
		//	//if (_state == HIMNO_CLIMB)
		//	//{
		//	//	_grabWall = true;
		//	//}
		//}
	}

	//�ȼ� �浹 ������
	for (int i = _probeR - 10; i < _probeR + 10; i++)
	{
		COLORREF color = GetPixel(_mapCollision->getMemDC(), i, _probeB - 10);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255) && !_himno._isJump)
		{
			//_himno._x = i - _mapX - 30;
			_RIGHT = true;
			break;
		}
		//�ȼ� �浹 ���� ��Ÿ��(�����)
		else if (r == 255 && g == 255 && b == 0)
		{
			_state = HIMNO_SLIDE;
			//_LEFT = true;
			//_himno._isJump = true;
			_LEFT = false;
			if (_state == HIMNO_SLIDE && !_LEFT)
			{
				_slideWall = false;
			}
		}
		//�ȼ� �浹 ������ �����(�ʷϻ�)
		else if ((r == 0 && g == 255 && b == 30)&&(r=255 &&g==0 && b==255))
		{
			_state = HIMNO_CLIMB;
			if (_state == HIMNO_CLIMB && !_LEFT)
			{
				_grabWall = false;
			}
		}
		else
		{
			_RIGHT = false;
		}

		//if (_himno._isJump)
		//{
		//	//�ȼ� �浹 ������ ��Ÿ��(�����)
		//	if (!(r == 255 && g == 255 && b == 0))
		//	{
		//		_state = HIMNO_SLIDE;
		//		//if (_state == HIMNO_SLIDE)
		//		//{
		//		//	_slideWall = false;
		//		//}
		//	}
		//
		//	////�ȼ� �浹 ������ �����(�ʷϻ�)
		//	//if (r == 0 && g == 255 && b == 30)
		//	//{
		//	//	_state = HIMNO_CLIMB;
		//	//}
		//}

	}
}

void player::allowShoot()
{
	for (int i = 0; i < ALLOW - 8; i++)
	{
		_allowX_L += 1;
		_allowX_R -= 1;
		if (i % 2 == 0)
		{
			if (_rcAllow[i].left >= WINSIZEX)
			{
				_allowX_L = 3;
				_rcAllow[0] = RectMake(_allowX_L, _rcMap.top + 2255, 30, 52);
				_rcAllow[2] = RectMake(_allowX_L, _rcMap.top + 1795, 30, 52);
				_rcAllow[4] = RectMake(_allowX_L, _rcMap.top + 1455, 30, 52);
				_rcAllow[6] = RectMake(_allowX_L, _rcMap.top + 679, 30, 52);
			}
		}
		else
		{
			if (_rcAllow[i].right <= 0)
			{
				_allowX_R = 1166;
				_rcAllow[1] = RectMake(_allowX_R, _rcMap.top + 2255, 30, 52);
				_rcAllow[3] = RectMake(_allowX_R, _rcMap.top + 1583, 30, 52);
				_rcAllow[5] = RectMake(_allowX_R, _rcMap.top + 1245, 30, 52);
				_rcAllow[7] = RectMake(_allowX_R, _rcMap.top + 335, 30, 52);
			}
		}
	}
}

void player::playerDead()
{
	//�÷��̾� ���̶� �浹
	RECT _temp;
	if (IntersectRect(&_temp, &_himno._rcPlayer, &_rcWater))
	{
		//���� ����
		SOUNDMANAGER->stop("���");
	
		SCENEMANAGER->loadScene("����");
	}
	
	RECT _temp4;
	//�÷��̾� ������ ������ �浹 
	if (IntersectRect(&_temp4, &_himno._rcPlayer, &_rcDeadTree))
	{
		//���� ����
		SOUNDMANAGER->stop("���");
	
		SCENEMANAGER->loadScene("����");
	}
	
	if (_isGameClear)
	{
		//�߸��� ���� ������ 
		RECT _temp6;
		if (INPUT->GetKey(VK_UP))
		{
			if ((IntersectRect(&_temp6, &_rcDoor[0], &_himno._rcPlayer)) || IntersectRect(&_temp6, &_rcDoor[2], &_himno._rcPlayer))
			{
				//���� ����
				SOUNDMANAGER->stop("���");
	
				SCENEMANAGER->loadScene("����");
			}
		}
	}
	
	//ȭ�쿡 �¾�����
	RECT _temp9;
	for (int i = 0; i < ALLOW; i++)
	{
		if (IntersectRect(&_temp9, &_rcAllow[i], &_himno._rcPlayer))
		{
			//���� ����
			SOUNDMANAGER->stop("���");
	
			SCENEMANAGER->loadScene("����");
		}
	}
	
	//�� ���� ������ �������
	RECT _temp10;
	if (IntersectRect(&_temp10, &_rcTrap, &_himno._rcPlayer))
	{
		//���� ����
		SOUNDMANAGER->stop("���");
	
		SCENEMANAGER->loadScene("����");
	}
}

void player::playerAlive()
{
	if (_isGameClear)
	{
		//Ŭ����� 
		if (INPUT->GetKey(VK_UP))
		{
			RECT _temp7;
			if (IntersectRect(&_temp7, &_rcDoor[1], &_himno._rcPlayer))
			{
				SCENEMANAGER->loadScene("����");
			}
		}
	}
	
}
