#pragma once
#include "gameNode.h"

//?Ѿ? ????ü
struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	int count;
};

//=============================================================
//	## bullet ## (?????Ѿ? - ???????? ???????? ??)
//=============================================================
class bullet : public gameNode
{
private:
	//?Ѿ? ????ü?? ???? ????, ?ݺ???
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	const char* _imageName;	//?Ѿ? ?̹??? ?̸?
	float _range;			//?Ѿ? ???Ÿ?
	int _bulletMax;			//?Ѿ? ?ִ밹??
	bool _isFrameImg;		//?????? ?̹??????

public:
	HRESULT init(const char* imageName, int bulletMax, float range, bool isFrameImg = false);
	void release();
	void update();
	void render();

	//?Ѿ˹߻?
	void fire(float x, float y, float angle, float speed);
	//?Ѿ˹???
	void move();

	//?Ѿ˺??? ????????
	vector<tagBullet> getBullet() { return _vBullet; }
	//??ź ????
	void removeBullet(int index);

	bullet() {}
	~bullet() {}
};


//=============================================================
//	## missile ## (missile[0] -> ?迭ó?? ?̸? ?????صΰ? ?Ѿ˹߻?)
//=============================================================
class missile : public gameNode
{
private:
	//?Ѿ? ????ü?? ???? ????, ?ݺ???
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	float _range;		//?Ѿ? ???Ÿ?
	int _bulletMax;		//?Ѿ? ?ִ밹??

public:
	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	//?Ѿ˹߻?
	void fire(float x, float y);
	//?Ѿ˹???
	void move();

	missile() {}
	~missile() {}
};


//=============================================================
//	## bomb ## (??źó?? ?ѹ߾? ?߻??ϰ? ?????ϰ? ?ڵ?????)
//=============================================================
class bomb : public gameNode
{
private:
	//?Ѿ? ????ü?? ???? ????, ?ݺ???
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	float _range;		//?Ѿ? ???Ÿ?
	int _bulletMax;		//?Ѿ? ?ִ밹??

public:
	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	//?Ѿ˹߻?
	void fire(float x, float y);
	//?Ѿ˹???
	void move();

	//?Ѿ˺??? ????????
	vector<tagBullet> getBullet() { return _vBullet; }
	//??ź ????
	void removeBomb(int index);

	bomb() {}
	~bomb() {}
};



