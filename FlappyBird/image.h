#pragma once
//=============================================================
//	## image ## (������ ��� ������Ʈ �ȴ�)
//=============================================================

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,  //���ҽ��� �ε�(������)
		LOAD_FILE,			//���Ϸ� �ε�
		LOAD_EMPTY,			//���Ʈ�� �ε�
		LOAD_END
	};

	typedef struct tagImage
	{
		HDC hMemDC;			//�޸� DC
		HBITMAP hBit;		//��Ʈ��
		HBITMAP hOBit;		//�õ��Ʈ��
		int width;			//�̹��� ���α���
		int height;			//�̹��� ���α���
		BYTE loadType;		//�̹��� �ε�Ÿ��
		tagImage()			//������ = �ʱ�ȭ
		{
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_EMPTY;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	char*			_fileName;		//�̹��� �̸�
	bool			_isTrans;		//���� ���ٰų�?
	COLORREF		_transColor;	//���� ���� RGB���� (����Ÿ = RGB(255, 0, 255))	
	
	LPIMAGE_INFO	_blendImage;	//���ĺ��� �̹���
	BLENDFUNCTION	_blendFunc;		//���ĺ��� ���

public:
	image();
	~image();

	//�� ��Ʈ�� �ʱ�ȭ
	HRESULT init(int width, int height);
	//�̹��� ���ҽ� �ʱ�ȭ => �����ؼ� �ȸ���
	//�̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//���ĺ��� �ʱ�ȭ
	HRESULT initForAlphaBlend();

	//����
	void release();

	//����(���� ���ϴ� ��ǥ�� ����ض�, �Ϲ������� RECT�� LT��ǥ�� �̹����� ���δ�)
	void render(HDC hdc, int destX = 0, int destY = 0);
	//����(���ϴ� ��ǥ�� �̹����� �߶� ���̱�)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	
	//���ķ���(�̹����� ���İ���ŭ ����ȭ �����ش�)
	//0(min) ~ 255(max)
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int dextX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//DC ���
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
};

