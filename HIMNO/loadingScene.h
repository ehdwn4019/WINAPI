#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingScene : public gameNode
{
private:
	//로딩 클래스 선언
	loading* _loading;

	//로딩바 플레이어 달리는 이미지 추가 변수
	image* _run;

	//로딩 퍼센트 숫자 이미지 추가 변수
	image* _loadingNumber[10];

	//플레이어 렉트 추가 변수
	RECT _rcPlayer;

	//로딩바 플레이어 프레임이미지 움직임에 사용하는 변수 
	int _count;
	int _index;

	//텍스트 퍼센트 게이지 변수 
	int _gauge;

	//텍스트 표시 해주는 문자열 변수 
	char str[100];
	char str1[100];



	

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
	void loadingImage();
	//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
	void loadingSound();


	//로딩바 게이지 수치 표시 함수 
	int setLoadingGauge(float maxGauge, float currentGauge);
	//로딩바 플레이어 프레임 이미지 함수 
	void loadingPlayer();
	//퍼센트 함수
	void percent();

	loadingScene() {}
	~loadingScene() {}
};

