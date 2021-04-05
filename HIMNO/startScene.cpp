#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init()
{
	//시작화면 이미지 추가 
	IMAGEMANAGER->addImage("시작화면","images/scene/시작화면.bmp",WINSIZEX,WINSIZEY);

	//렉트 위치 초기화
	//_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 200, 200, 100);
	_start = RectMake(780, 480, 85, 40);
	_exit = RectMake(780, 550, 85, 40);

	//사운드 추가 
	SOUNDMANAGER->addSound("산뜻", "SOUND/술래잡기- Tido Kang.mp3");
	
	//사운드 재생
	SOUNDMANAGER->play("산뜻");

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
			SCENEMANAGER->loadScene("로딩화면");
		}
		if (PtInRect(&_exit, _ptMouse))
		{
			PostQuitMessage(0);
		}
	}
}

void startScene::render()
{

	IMAGEMANAGER->render("시작화면", getMemDC(), 0, 0);
	if (INPUT->GetToggleKey('B'))
	{
		Rectangle(getMemDC(), _start);
		Rectangle(getMemDC(), _exit);
	}

	//Rectangle(getMemDC(), _rc);
	//TextOut(getMemDC(), _rc.left + 50, _rc.top + 50, "START", strlen("START"));


}
