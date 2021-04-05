#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�ε� �̹��� �� ���� �ʱ�ȭ
	this->loadingImage();
	this->loadingSound();

	//���� �ʱ�ȭ 
	_count = _index = _gauge = 0;

	//�ε��� �÷��̾� �̹��� �߰� 
	_run = IMAGEMANAGER->addFrameImage("�޸���", "images/scene/�޸���2.bmp", 343, 59, 6, 1);

	//�ε��� �ۼ�Ʈ �̹��� �߰� 
	IMAGEMANAGER->addImage("�ۼ�Ʈ", "images/scene/�ۼ�Ʈ.bmp", 15, 16);

	//�ε��� ���� �̹��� �߰� 
	_loadingNumber[0] = IMAGEMANAGER->addImage("num0", "����/num0.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[1] = IMAGEMANAGER->addImage("num1", "����/num1.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[2] = IMAGEMANAGER->addImage("num2", "����/num2.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[3] = IMAGEMANAGER->addImage("num3", "����/num3.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[4] = IMAGEMANAGER->addImage("num4", "����/num4.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[5] = IMAGEMANAGER->addImage("num5", "����/num5.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[6] = IMAGEMANAGER->addImage("num6", "����/num6.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[7] = IMAGEMANAGER->addImage("num7", "����/num7.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[8] = IMAGEMANAGER->addImage("num8", "����/num8.bmp", 15, 22, true, RGB(255, 0, 255));
	_loadingNumber[9] = IMAGEMANAGER->addImage("num9", "����/num9.bmp", 15, 22, true, RGB(255, 0, 255));


	////���� �߰� 
	//SOUNDMANAGER->addSound("���", "SOUND/�������- Tido Kang.mp3");
	//
	////���� ���
	//SOUNDMANAGER->play("���");
	return S_OK;
}

void loadingScene::release()
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ȭ�� ����
	if (_loading->loadingDone())
	{
		//���� ����
		SOUNDMANAGER->stop("���");
		SCENEMANAGER->loadScene("����ȭ��");
	}

	//�ε��� �÷��̾� ������ �Լ� 
	this->loadingPlayer();
}

void loadingScene::render()
{
	//�ε�Ŭ���� ����
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
	IMAGEMANAGER->render("�ۼ�Ʈ", getMemDC(), 1150, 430);

	//�ε� �ۼ�Ʈ �Լ� 
	this->percent();
}

//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	/*
	//��׶��� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addImage("��׶���", "Images/background.bmp", WINSIZEX, WINSIZEY);
	//UFO ������ �̹��� �ʱ�ȭ
	IMAGEMANAGER->addFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	//�Ѿ� �̹���
	IMAGEMANAGER->addImage("bullet", "Images/bullet.bmp", 21, 21);
	*/
	_loading->loadImage("��׶���", "Images/background.bmp", WINSIZEX, WINSIZEY);
	_loading->loadFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	_loading->loadImage("bullet", "Images/bullet.bmp", 21, 21);

	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ �����
	for (int i = 0; i < 200; i++)
	{
		_loading->loadImage("�׽�Ʈ", WINSIZEX, WINSIZEY);
	}

	_loading->loadImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("ball", "ball.bmp", 60, 60);
}

//�ε����� �Լ�(�̰��� ���带 ���� �־��)
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
			int temp1 = _gauge / 10;    //10���ڸ�
			int temp2 = _gauge % 10;    //1���ڸ�

			_loadingNumber[temp1]->render(getMemDC(),1100 , 430);
			_loadingNumber[temp2]->render(getMemDC(), 1120, 430);
		}
	}
}


