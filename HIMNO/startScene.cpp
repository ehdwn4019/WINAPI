#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init()
{
	//����ȭ�� �̹��� �߰� 
	IMAGEMANAGER->addImage("����ȭ��","images/scene/����ȭ��.bmp",WINSIZEX,WINSIZEY);

	//��Ʈ ��ġ �ʱ�ȭ
	//_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 200, 200, 100);
	_start = RectMake(780, 480, 85, 40);
	_exit = RectMake(780, 550, 85, 40);

	//���� �߰� 
	SOUNDMANAGER->addSound("���", "SOUND/�������- Tido Kang.mp3");
	
	//���� ���
	SOUNDMANAGER->play("���");

	return S_OK;
}

void startScene::release()
{

}

void startScene::update()
{
	if (INPUT->GetKey(VK_LBUTTON))
	{       
		if (PtInRect(&_start, _ptMouse))
		{
			SCENEMANAGER->loadScene("�ε�ȭ��");
		}
		if (PtInRect(&_exit, _ptMouse))
		{
			PostQuitMessage(0);
		}
	}
}

void startScene::render()
{

	IMAGEMANAGER->render("����ȭ��", getMemDC(), 0, 0);
	if (INPUT->GetToggleKey('B'))
	{
		Rectangle(getMemDC(), _start);
		Rectangle(getMemDC(), _exit);
	}

	//Rectangle(getMemDC(), _rc);
	//TextOut(getMemDC(), _rc.left + 50, _rc.top + 50, "START", strlen("START"));


}
