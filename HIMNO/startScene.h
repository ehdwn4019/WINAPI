#pragma once
#include "gameNode.h"

class startScene : public gameNode
{
private:

	//����ȭ�� ��ư ��Ʈ 
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

