#pragma once
#include "gameNode.h"
class aliveScene : public gameNode
{
	image* _alive;
	RECT _rcMainMenu_a;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	aliveScene();
	~aliveScene();
};

