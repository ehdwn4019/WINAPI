#include "stdafx.h" 
#include "mainGame.h" 
  
//============================================================= 
//	## 초기화 ## init() 
//============================================================= 
HRESULT mainGame::init() 
{ 
	gameNode::init(); 
	//이곳에서 초기화를 한다 
	 
	_count = 0; 
	temp = 0; 
	gravity = 0; 
	score = 0; 
	scoreCount = 0; 
	  
	_bgNoon = new image;  
	_bgNoon->init("bg_noon.bmp", 800, 800);  
	  
	_bgNight = new image;  
	_bgNight->init("bg_night.bmp", 800, 800);  
	 
	_ground = new image; 
	_ground->init("bg_tile.bmp", 800, 100); 
	 
	_bird1 = new image; 
	_bird1->init("bird1.bmp", 50, 50, true , RGB(255,0,255)); 
	 
	_bird2 = new image; 
	_bird2->init("bird2.bmp", 50, 50, true, RGB(255, 0, 255)); 
	  
	_bird3 = new image; 
	_bird3->init("bird3.bmp", 50, 50, true, RGB(255, 0, 255)); 
	 
	topPillar = new image; 
	topPillar->init("top.bmp", 80, 400, true, RGB(255, 0, 255)); 
	 
	bottomPillar = new image; 
	bottomPillar->init("bottom.bmp", 80, 600, true, RGB(255, 0, 255)); 
	 
	 
	num0 = new image; 
	num0->init("num0.bmp", 60, 90, true, RGB(255, 0, 255)); 
	 
	num1 = new image; 
	num1->init("num1.bmp", 60, 90, true, RGB(255, 0, 255)); 
	 
	num2 = new image; 
	num2->init("num2.bmp", 60, 90, true, RGB(255, 0, 255)); 
	 
	num3 = new image; 
	num3->init("num3.bmp", 60, 90, true, RGB(255, 0, 255)); 
	 
	num4 = new image; 
	num4->init("num4.bmp", 60, 90, true, RGB(255, 0, 255)); 
	 
	num5 = new image; 
	num5->init("num5.bmp", 60, 90, true, RGB(255, 0, 255)); 
	  
	num6 = new image; 
	num6->init("num6.bmp", 60, 90, true, RGB(255, 0, 255)); 
	 
	num7 = new image; 
	num7->init("num7.bmp", 60, 90, true, RGB(255, 0, 255)); 
	 
	num8 = new image; 
	num8->init("num8.bmp", 60, 90, true, RGB(255, 0, 255)); 
	 
	num9 = new image; 
	num9->init("num9.bmp", 60, 90, true, RGB(255, 0, 255)); 
	 
	_rcGround = RectMake(0,700, 800, 100);        
	_rcBird = RectMake(50, 400, 50, 50);       
	 
	_rcPillar1 = RectMake(300,0,80, RANDOM->Range(300, 400));//왼쪽위 
	_rcPillar2 = RectMake(300,_rcPillar1.bottom+125, 80, 1000);//왼쪽 아래 
	_rcPillar3 = RectMake(600,0,80, RANDOM->Range(100, 200));//오른쪽 위 
	_rcPillar4 = RectMake(600,_rcPillar3.bottom+125,80, 1000);//오른쪽 아래 
	//_alpha = _count = 0; 
	 
	return S_OK; 
} 
 
//============================================================= 
//	## 해제 ## release() 
//============================================================= 
void mainGame::release() 
{ 
	gameNode::release(); 
	//이미지 클래스를 나갈때까진 사용할 일 없다 
	//동적할당 new를 사용했다면 이곳에서 SAFE_DELETE() 사용한다 

	SAFE_DELETE(_bgNoon);
	SAFE_DELETE(_bgNight);
	SAFE_DELETE(_ground);
	SAFE_DELETE(_bird1);
	SAFE_DELETE(_bird2);
	SAFE_DELETE(_bird3);
	SAFE_DELETE(topPillar);
	SAFE_DELETE(bottomPillar);
	SAFE_DELETE(num0);
	SAFE_DELETE(num1);
	SAFE_DELETE(num2);
	SAFE_DELETE(num3);
	SAFE_DELETE(num4);
	SAFE_DELETE(num5);
	SAFE_DELETE(num6);
	SAFE_DELETE(num7);
	SAFE_DELETE(num8);
	SAFE_DELETE(num9);
	
	//delete _bgImg;
	//_bgImg = NULL;
}



//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	//간단하게 이곳에서 코딩한다고 생각하면 된다
	//충돌처리

	if (_rcBird.top<=0)
	{
		this->init();
	}
	if (_rcBird.top >= 800)
	{
		this->init();
	}

	//충돌
	if (IntersectRect(&collision, &_rcBird, &_rcPillar1))
	{
		this->init();
	}
	if (IntersectRect(&collision, &_rcBird, &_rcPillar2))
	{
		this->init();
	}
	if (IntersectRect(&collision, &_rcBird, &_rcPillar3))
	{
		this->init();
	}
	if (IntersectRect(&collision, &_rcBird, &_rcPillar4))
	{
		this->init();
	}
		
	

	

	_count++;

	if (_count % 5==0)
	{
		temp++;
	}

	gravity+=0.1f;

	_rcBird.top += gravity;
	_rcBird.bottom += gravity;

	_rcPillar1.left-=2;
	_rcPillar1.right-=2;
	_rcPillar2.left=_rcPillar1.left;
	_rcPillar2.right=_rcPillar1.right;

	if (_rcPillar1.right < 0)
	{
		_rcPillar1 = RectMake(550, 0, 80, RANDOM->Range(200, 400));
		_rcPillar2.top = _rcPillar1.bottom + 100;
	}

	_rcPillar3.left-=2;
	_rcPillar3.right-=2;
	_rcPillar4.left=_rcPillar3.left;
	_rcPillar4.right=_rcPillar3.right;
	if (_rcPillar3.right <0)
	{
		_rcPillar3 = RectMake(550, 0, 80, RANDOM->Range(150, 350));
		_rcPillar4.top = _rcPillar3.bottom + 100;
	}

	if (INPUT->GetKeyDown(VK_SPACE))
	{
		gravity=-3.0f;
	}
	
	if (_rcBird.left > _rcPillar1.right)
	{
		scoreCount++;

		if(scoreCount % 50 == 1)
		{
			score++;
		}
	}
	if (_rcBird.left > _rcPillar3.right)
	{
		scoreCount++;

		if (scoreCount % 50 == 1)
		{
			score++;
		
		}
	}
	
	//_rcGround.right -= 5;
	//if (_rcGround.right <0)
	//{
	//	_rcGround.right++;
	//}
	
	

	//_count++;
	//if (_count % 2 == 0)
	//{
	//	_alpha++;
	//	if (_alpha > 255) _alpha = 255;
	//}
}

//=============================================================
//	## 렌더 ## render()
//=============================================================
void mainGame::render(HDC hdc)
{
	//백버퍼 가져오기(이건 렌더에 두기)
	HDC memDC = this->getBackBuffer()->getMemDC();
	//흰색 빈 비트맵 (이것도 렌더에 그냥 두기)
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
//=============================================================	
	//이곳에서 WM_PAINT에서 했던것을 처리하면 된다
	
	

	_bgNoon->render(memDC);
	//if (_count == 3)
	//{
	//	_bgNight->render(memDC);
	//	if (_count == 6)
	//	{
	//		_bgNoon->render(memDC);
	//		_count = 0;
	//	}
	//}

	_ground->render(memDC, _rcGround.left, _rcGround.top);
	_bird1->render(memDC, _rcBird.left, _rcBird.top);


	topPillar->render(memDC, _rcPillar1.left, _rcPillar1.bottom-400);//왼쪽위 
	bottomPillar->render(memDC, _rcPillar2.left, _rcPillar2.top);//왼쪽 아래 
	topPillar->render(memDC, _rcPillar3.left, _rcPillar3.bottom-400);//오른쪽 위 
	bottomPillar->render(memDC, _rcPillar4.left, _rcPillar4.top);// 오른쪽 아래	


	if (temp % 3 == 0)
	{
		_bird1->render(memDC, _rcBird.left, _rcBird.top);
	}
	if (temp % 3 == 1)
	{
		_bird2->render(memDC, _rcBird.left, _rcBird.top);
	}
	if (temp % 3 == 2)
	{
		_bird3->render(memDC, _rcBird.left, _rcBird.top);
	}





	//일의 자리 점수표시
	if (score < 10)
	{
		if (score % 10 == 0)
		{
			num0->render(memDC, 240, 100);
		}
		if (score % 10 == 1)
		{
			num1->render(memDC, 240, 100);
		}
		if (score % 10 == 2)
		{
			num2->render(memDC, 240, 100);
		}
		if (score % 10 == 3)
		{
			num3->render(memDC, 240, 100);
		}
		if (score % 10 == 4)
		{
			num4->render(memDC, 240, 100);
		}
		if (score % 10 == 5)
		{
			num5->render(memDC, 240, 100);
		}
		if (score % 10 == 6)
		{
			num6->render(memDC, 240, 100);
		}
		if (score % 10 == 7)
		{
			num7->render(memDC, 240, 100);
		}
		if (score % 10 == 8)
		{
			num8->render(memDC, 240, 100);
		}
		if (score % 10 == 9)
		{
			num9->render(memDC, 240, 100);
		}
	}
	//십의자리 점수 표시 
    if (score >= 10)
	{
		if (score / 10 == 0)
		{
			num0->render(memDC, 210, 100);
		}
		if (score / 10 == 1)
		{
			num1->render(memDC, 210, 100);
		}
		if (score / 10 == 2)
		{
			num2->render(memDC, 210, 100);
		}
		if (score / 10 == 3)
		{
			num3->render(memDC, 210, 100);
		}
		if (score / 10 == 4)
		{
			num4->render(memDC, 210, 100);
		}
		if (score / 10 == 5)
		{
			num5->render(memDC, 210, 100);
		}
		if (score / 10 == 6)
		{
			num6->render(memDC, 210, 100);
		}
		if (score / 10 == 7)
		{
			num7->render(memDC, 210, 100);
		}
		if (score / 10 == 8)
		{
			num8->render(memDC, 210, 100);
		}
		if (score / 10 == 9)
		{
			num9->render(memDC, 210, 100);
		}

		//일의자리
		if (score % 10 == 0)
		{
			num0->render(memDC, 240, 100);
		}
		if (score % 10 == 1)
		{
			num1->render(memDC, 240, 100);
		}
		if (score % 10 == 2)
		{
			num2->render(memDC, 240, 100);
		}
		if (score % 10 == 3)
		{
			num3->render(memDC, 240, 100);
		}
		if (score % 10 == 4)
		{
			num4->render(memDC, 240, 100);
		}
		if (score % 10 == 5)
		{
			num5->render(memDC, 240, 100);
		}
		if (score % 10 == 6)
		{
			num6->render(memDC, 240, 100);
		}
		if (score % 10 == 7)
		{
			num7->render(memDC, 240, 100);
		}
		if (score % 10 == 8)
		{
			num8->render(memDC, 240, 100);
		}
		if (score % 10 == 9)
		{
			num9->render(memDC, 240, 100);
		}
	}


	

	//_bgImg->render(memDC, 500, 500, 150, 100, 150, 150);
	//_bgImg->alphaRender(memDC, _alpha);

	//Rectangle(memDC, _rcGround);
	//Rectangle(memDC, _rcPillar1);
	//Rectangle(memDC, _rcPillar2);
	//Rectangle(memDC, _rcPillar3);
	//Rectangle(memDC, _rcPillar4);
	//Rectangle(memDC, _rcBird);

	//_ball->render(memDC, _rc.left, _rc.top);
	//if (INPUT->GetToggleKey(VK_SPACE))
	//{
	//	Rectangle(memDC, _rc);
	//}
	//_ball->render(memDC, _rc.left, _rc.top);
	//_ball->alphaRender(memDC, _alpha);

//=============================================================
	//백버퍼의 내용을 화면DC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(hdc);
}
