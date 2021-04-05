#pragma once
#include "gameNode.h"
class deadScene : public gameNode
{
	RECT _rcDead;
	image* _dead;
	RECT _rcMainMenu_d;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	deadScene();
	~deadScene();
};

