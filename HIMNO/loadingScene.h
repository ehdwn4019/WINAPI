#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingScene : public gameNode
{
private:
	//�ε� Ŭ���� ����
	loading* _loading;

	//�ε��� �÷��̾� �޸��� �̹��� �߰� ����
	image* _run;

	//�ε� �ۼ�Ʈ ���� �̹��� �߰� ����
	image* _loadingNumber[10];

	//�÷��̾� ��Ʈ �߰� ����
	RECT _rcPlayer;

	//�ε��� �÷��̾� �������̹��� �����ӿ� ����ϴ� ���� 
	int _count;
	int _index;

	//�ؽ�Ʈ �ۼ�Ʈ ������ ���� 
	int _gauge;

	//�ؽ�Ʈ ǥ�� ���ִ� ���ڿ� ���� 
	char str[100];
	char str1[100];



	

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
	void loadingImage();
	//�ε����� �Լ�(�̰��� ���带 ���� �־��)
	void loadingSound();


	//�ε��� ������ ��ġ ǥ�� �Լ� 
	int setLoadingGauge(float maxGauge, float currentGauge);
	//�ε��� �÷��̾� ������ �̹��� �Լ� 
	void loadingPlayer();
	//�ۼ�Ʈ �Լ�
	void percent();

	loadingScene() {}
	~loadingScene() {}
};

