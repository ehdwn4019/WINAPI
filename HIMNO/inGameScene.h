#pragma once
#include "gameNode.h"
#include "player.h"
#include "vector"


class inGameScene : public gameNode
{

private:
	//플레이어 클래스
	player* _player; 




public:

	HRESULT init();
	void release();
	void update();
	void render();

	inGameScene() {}
	~inGameScene() {}
};

