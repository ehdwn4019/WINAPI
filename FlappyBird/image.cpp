#include "stdafx.h"
#include "image.h"
image::image() : _imageInfo(NULL), _fileName(NULL), _blendImage(NULL)
{
}
image::~image()
{
}

//�� ��Ʈ�� �ʱ�ȭ
HRESULT image::init(int width, int height)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ������
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	_fileName = NULL;

	//����Ű �÷� ����
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//���ҽ� ��µ� �����ϸ� �ٷ� ����
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//�̹��� ���Ϸ� �ʱ�ȭ
HRESULT image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ������
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��µ� �����ϸ� �ٷ� ����
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForAlphaBlend()
{
	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//���ĺ��� �ɼ��ʱ�ȭ
	//BlendOp => ����� AC_SRC_OVER�� ��밡��
	//BlendFlags => �� 0����, ���� �߸�, ���� OS���� ����ߴٴ� ���� ����
	//AlphaFormat => 24bit���� 0, 32bit���� AC_SRC_ALPHA ����ϸ� ������ �����̰� ������ �츰 �� 0
	//SourceConstantAlpha => ��Ʈ�� ���� ����
	_blendFunc.BlendOp = AC_SRC_OVER;
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	//_blendFunc.SourceConstantAlpha = 255; // 0 ~ 255, 255�϶� ��������

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

void image::release()
{
	//�̹��� ������ ���� �ִٸ� ���� ���Ѷ�
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);
		
		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);
		
		//���� �÷�Ű �ʱ�ȭ
		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}
}

//����(���� ���ϴ� ��ǥ�� ����ض�, �Ϲ������� RECT�� LT��ǥ�� �̹����� ���δ�)
void image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)//���� ���ְ� ���
	{
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,				//������ ����� DC
			destX,				//������ ��ǥ ����X
			destY,				//������ ��ǥ ����Y
			_imageInfo->width,	//������ �̹��� ����ũ��
			_imageInfo->height,	//������ �̹��� ����ũ��
			_imageInfo->hMemDC,	//����� ��� DC
			0, 0,				//����� ����� ��������
			_imageInfo->width,	//���� ���� ����ũ��
			_imageInfo->height,	//���� ���� ����ũ��
			_transColor);		//�����Ҷ� ������ ����(�Ϲ������� ����Ÿ)
	}
	else//���� �̹��� �״�� ���
	{
		//BitBlt : DC���� �������� ��Ӻ��� ���ִ� �Լ�
		//�޸�DC -> ȭ��DC�� �����Ѵ�
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//����(���ϴ� ��ǥ�� �̹����� �߶� ���̱�)
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)//���� ���ְ� ���
	{
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,				//������ ����� DC
			destX,				//������ ��ǥ ����X
			destY,				//������ ��ǥ ����Y
			sourWidth,			//������ �̹��� ����ũ��
			sourHeight,			//������ �̹��� ����ũ��
			_imageInfo->hMemDC,	//����� ��� DC
			sourX, sourY,		//����� ����� ��������
			sourWidth,			//���� ���� ����ũ��
			sourHeight,			//���� ���� ����ũ��
			_transColor);		//�����Ҷ� ������ ����(�Ϲ������� ����Ÿ)
	}
	else//���� �̹��� �״�� ���
	{
		//BitBlt : DC���� �������� ��Ӻ��� ���ִ� �Լ�
		//�޸�DC -> ȭ��DC�� �����Ѵ�
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

//1��
void image::alphaRender(HDC hdc, BYTE alpha)
{
	//���ĺ��带 ó�� ����ϳ�?
	//���ĺ��带 ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_blendImage) this->initForAlphaBlend();
	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;


	if (_isTrans)//���� ���ְ� ���
	{
		//1. ����ȭ�� DC�� ������ => �����̹����� ����
		//2. �̹����޸�DC�� ������ ������ => �����̹����� ����
		//3. �����̹����� ȭ��DC�� ����(���ĺ���)

		//1
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, 0, 0, SRCCOPY);
		
		//2
		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC
			0,					//������ ��ǥ ����X
			0,					//������ ��ǥ ����Y
			_imageInfo->width,		//������ �̹��� ����ũ��
			_imageInfo->height,		//������ �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			0, 0,					//����� ����� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ����(�Ϲ������� ����Ÿ)
		//3
		GdiAlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else//���� �̹��� �״�� ���
	{
		GdiAlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

//2��
void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//���ĺ��带 ó�� ����ϳ�?
//���ĺ��带 ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_blendImage) this->initForAlphaBlend();
	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;


	if (_isTrans)//���� ���ְ� ���
	{
		//1. ����ȭ�� DC�� ������ => �����̹����� ����
		//2. �̹����޸�DC�� ������ ������ => �����̹����� ����
		//3. �����̹����� ȭ��DC�� ����(���ĺ���)

		//1
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, destX, destY, SRCCOPY);

		//2
		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC
			0,					//������ ��ǥ ����X
			0,					//������ ��ǥ ����Y
			_imageInfo->width,		//������ �̹��� ����ũ��
			_imageInfo->height,		//������ �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			0, 0,					//����� ����� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ����(�Ϲ������� ����Ÿ)
		//3
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else//���� �̹��� �״�� ���
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

//3��
void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//���ĺ��带 ó�� ����ϳ�?
	//���ĺ��带 ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_blendImage) this->initForAlphaBlend();
	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;


	if (_isTrans)//���� ���ְ� ���
	{
		//1. ����ȭ�� DC�� ������ => �����̹����� ����
		//2. �̹����޸�DC�� ������ ������ => �����̹����� ����
		//3. �����̹����� ȭ��DC�� ����(���ĺ���)

		//1
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, destX, destY, SRCCOPY);

		//2
		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC
			0,					//������ ��ǥ ����X
			0,					//������ ��ǥ ����Y
			sourWidth,		//������ �̹��� ����ũ��
			sourHeight,		//������ �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			sourX,
			sourY,					//����� ����� ��������
			sourWidth,		//���� ���� ����ũ��
			sourHeight,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ����(�Ϲ������� ����Ÿ)
		//3
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else//���� �̹��� �״�� ���
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
}
