#include "stdafx.h"
#include "aliveScene.h"


HRESULT aliveScene::init()
{
	_rcMainMenu_a = RectMake(520, 895, 200, 28);
	_alive = IMAGEMANAGER->addImage("alive", "images/alive.bmp", 600, 1000);
	return S_OK;
}

void aliveScene::release()
{


}

void aliveScene::update()
{
	if (INPUT->GetKey(VK_LBUTTON))
	{
		if (PtInRect(&_rcMainMenu_a, _ptMouse))
		{
			SCENEMANAGER->loadScene("시작화면");
		}
	}
}

void aliveScene::render()
{
	IMAGEMANAGER->render("alive", getMemDC(), 320, 0);
	//Rectangle(getMemDC(), _rcMainMenu_a);
}

aliveScene::aliveScene()
{
}


aliveScene::~aliveScene()
{
}
