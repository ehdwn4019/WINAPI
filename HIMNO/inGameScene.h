#pragma once
#include "gameNode.h"
#include "player.h"
#include "vector"


class inGameScene : public gameNode
{

private:
	//�÷��̾� Ŭ����
	player* _player; 




public:

	HRESULT init();
	void release();
	void update();
	void render();

	inGameScene() {}
	~inGameScene() {}
};

