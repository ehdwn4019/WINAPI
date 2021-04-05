#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//로딩 이미지 및 사운드 초기화
	this->loadingImage();
	this->loadingSound();

	//변수 초기화 
	_count = _index = _gauge = 0;

	//로딩바 플레이어 이미지 추가 
	_run = IMAGEMANAGER->addFrameImage("달리기", "images/scene/달리기2.bmp", 343, 59, 6, 1);

	//로딩바 퍼센트 이미지 추가 
	IMAGEMANAGER->addImage("퍼센트", "images/scene/퍼센트.bmp", 15, 16);

	//로딩바 숫자 이미지 추가 
	_loadingNumber[0] = IMAGEMANAGER->addImage("num0", "숫자/num0.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[1] = IMAGEMANAGER->addImage("num1", "숫자/num1.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[2] = IMAGEMANAGER->addImage("num2", "숫자/num2.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[3] = IMAGEMANAGER->addImage("num3", "숫자/num3.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[4] = IMAGEMANAGER->addImage("num4", "숫자/num4.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[5] = IMAGEMANAGER->addImage("num5", "숫자/num5.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[6] = IMAGEMANAGER->addImage("num6", "숫자/num6.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[7] = IMAGEMANAGER->addImage("num7", "숫자/num7.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[8] = IMAGEMANAGER->addImage("num8", "숫자/num8.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[9] = IMAGEMANAGER->addImage("num9", "숫자/num9.bmp", 15, 22, true, RGB(255, 0, 255));


	////사운드 추가 
	//SOUNDMANAGER->addSound("산뜻", "SOUND/술래잡기- Tido Kang.mp3");
	//
	////사운드 재생
	//SOUNDMANAGER->play("산뜻");
	return S_OK;
}

void loadingScene::release()
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 화면 변경
	if (_loading->loadingDone())
	{
		//사운드 중지
		SOUNDMANAGER->stop("산뜻");
		SCENEMANAGER->loadScene("게임화면");
	}

	//로딩바 플레이어 움직임 함수 
	this->loadingPlayer();
}

void loadingScene::render()
{
	//로딩클래스 렌더
	_loading->render();

	sprintf(str, "%d", setLoadingGauge(_loading->getLoadItem().size(), _loading->getCurrentGauge()));
	TextOut(getMemDC(), 720, 500, str, strlen(str));


	for (int i = 0; i < _loading->getLoadItem().size(); i++)
	{
		if (_loading->getLoadItem()[i]->getLoadKind() == LOAD_KIND_IMAGE_0) continue;

		sprintf(str1, _loading->getLoadItem()[i]->getImageResource().fileName);

	}

	//TextOut(getMemDC(), 120, 500, str1, strlen(str1));
	//SetBkMode(getMemDC(), TRANSPARENT);

	//Rectangle(getMemDC(), _rcPlayer);

	_run->frameRender(getMemDC(), _loading->getBar()->getWidth(), 370);
	IMAGEMANAGER->render("퍼센트", getMemDC(), 1150, 430);

	//로딩 퍼센트 함수 
	this->percent();
}

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	/*
	//백그라운드 이미지 초기화
	IMAGEMANAGER->addImage("백그라운드", "Images/background.bmp", WINSIZEX, WINSIZEY);
	//UFO 프레임 이미지 초기화
	IMAGEMANAGER->addFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	//총알 이미지
	IMAGEMANAGER->addImage("bullet", "Images/bullet.bmp", 21, 21);
	*/
	_loading->loadImage("백그라운드", "Images/background.bmp", WINSIZEX, WINSIZEY);
	_loading->loadFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	_loading->loadImage("bullet", "Images/bullet.bmp", 21, 21);

	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들기
	for (int i = 0; i < 200; i++)
	{
		_loading->loadImage("테스트", WINSIZEX, WINSIZEY);
	}

	_loading->loadImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("ball", "ball.bmp", 60, 60);
}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound()
{

}



int loadingScene::setLoadingGauge(float maxGauge, float currentGauge)
{
	_gauge = (currentGauge / maxGauge) * 100;

	return _gauge;
}

void loadingScene::loadingPlayer()
{
	_count++;
	_run->setFrameY(0);
	if (_count % 10 == 0)
	{
		_index++;
		if (_index > 6)
		{
			_index = 0;
		}
		_run->setFrameX(_index);
	}
}

void loadingScene::percent()
{
	for (int i = 0; i < 10; i++)
	{ 
		if (_gauge == i && _gauge < 10)
		{
			_loadingNumber[i]->render(getMemDC(), 1120, 430);
		}
		if (_gauge >= 10 && _gauge < 100)
		{
			int temp1 = _gauge / 10;    //10의자리
			int temp2 = _gauge % 10;    //1의자리

			_loadingNumber[temp1]->render(getMemDC(),1100 , 430);
			_loadingNumber[temp2]->render(getMemDC(), 1120, 430);
		}
	}
}


