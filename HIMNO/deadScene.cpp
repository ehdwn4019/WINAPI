#include "stdafx.h"
#include "deadScene.h"


HRESULT deadScene::init()
{
	//_rcDead = RectMake(0, 0, WINSIZEX, WINSIZEY);
	_rcMainMenu_d = RectMake(520, 870, 200, 28);
	_dead = IMAGEMANAGER->addImage("dead","images/dead.bmp", 600, 1000);
	return S_OK;
}

void deadScene::release()
{

}

void deadScene::update()
{
	if (INPUT->GetKey(VK_LBUTTON))
	{
		if (PtInRect(&_rcMainMenu_d, _ptMouse))
		{
			SCENEMANAGER->loadScene("시작화면");
		}
	}
	
}

void deadScene::render()
{
	IMAGEMANAGER->render("dead", getMemDC(), 320, 0);
	//Rectangle(getMemDC(), _rcMainMenu_d);
}

deadScene::deadScene()
{

}


deadScene::~deadScene()
{
}
