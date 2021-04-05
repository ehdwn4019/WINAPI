#pragma once
#include "gameNode.h"

class startScene : public gameNode
{
private:

	//시작화면 버튼 렉트 
	RECT _start;
	RECT _exit;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	startScene() {}
	~startScene() {}
};

