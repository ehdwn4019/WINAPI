#include "stdafx.h"
#include "image.h"
image::image() : _imageInfo(NULL), _fileName(NULL), _blendImage(NULL)
{
}
image::~image()
{
}

//빈 비트맵 초기화
HRESULT image::init(int width, int height)
{
	//재초기화 방지용, 이미지 정보의 값이 들어 있다면 릴리즈해서 깨끗하게 초기화 해주자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//투명키 컬러 세팅
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//리소스 얻는데 실패하면 바로 종료
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//이미지 파일로 초기화
HRESULT image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보의 값이 들어 있다면 릴리즈해서 깨끗하게 초기화 해주자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//투명키 컬러 세팅
	_isTrans = isTrans;
	_transColor = transColor;

	//리소스 얻는데 실패하면 바로 종료
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForAlphaBlend()
{
	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//알파블렌드 옵션초기화
	//BlendOp => 현재는 AC_SRC_OVER만 사용가능
	//BlendFlags => 걍 0대입, 나도 잘모름, 예전 OS에서 사용했다는 썰이 있음
	//AlphaFormat => 24bit사용시 0, 32bit사용시 AC_SRC_ALPHA 사용하면 되지만 별차이가 없으니 우린 걍 0
	//SourceConstantAlpha => 비트맵 투명도 세팅
	_blendFunc.BlendOp = AC_SRC_OVER;
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	//_blendFunc.SourceConstantAlpha = 255; // 0 ~ 255, 255일때 원본색상

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

void image::release()
{
	//이미지 정보가 남아 있다면 해제 시켜라
	if (_imageInfo)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);
		
		//포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);
		
		//투명 컬러키 초기화
		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}
}

//렌더(내가 원하는 좌표에 출력해라, 일반적으로 RECT의 LT좌표에 이미지를 붙인다)
void image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)//배경색 없애고 출력
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,				//복사할 장소의 DC
			destX,				//복사할 좌표 시작X
			destY,				//복사할 좌표 시작Y
			_imageInfo->width,	//복사할 이미지 가로크기
			_imageInfo->height,	//복사할 이미지 세로크기
			_imageInfo->hMemDC,	//복사될 대상 DC
			0, 0,				//복사될 대상의 시작지점
			_imageInfo->width,	//복사 영역 가로크기
			_imageInfo->height,	//복사 영역 세로크기
			_transColor);		//복사할때 제외할 색상(일반적으로 마젠타)
	}
	else//원본 이미지 그대로 출력
	{
		//BitBlt : DC간의 영역끼리 고속복사 해주는 함수
		//메모리DC -> 화면DC로 복사한다
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//렌더(원하는 좌표에 이미지를 잘라서 붙이기)
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)//배경색 없애고 출력
	{
		//GdiTransparentBlt : 비트맵의 특정색상을 제외하고 고속복사 해주는 함수
		GdiTransparentBlt(
			hdc,				//복사할 장소의 DC
			destX,				//복사할 좌표 시작X
			destY,				//복사할 좌표 시작Y
			sourWidth,			//복사할 이미지 가로크기
			sourHeight,			//복사할 이미지 세로크기
			_imageInfo->hMemDC,	//복사될 대상 DC
			sourX, sourY,		//복사될 대상의 시작지점
			sourWidth,			//복사 영역 가로크기
			sourHeight,			//복사 영역 세로크기
			_transColor);		//복사할때 제외할 색상(일반적으로 마젠타)
	}
	else//원본 이미지 그대로 출력
	{
		//BitBlt : DC간의 영역끼리 고속복사 해주는 함수
		//메모리DC -> 화면DC로 복사한다
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

//1번
void image::alphaRender(HDC hdc, BYTE alpha)
{
	//알파블렌드를 처음 사용하냐?
	//알파블렌드를 사용할 수 있도록 초기화 해라
	if (!_blendImage) this->initForAlphaBlend();
	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;


	if (_isTrans)//배경색 없애고 출력
	{
		//1. 현재화면 DC의 내용을 => 블렌드이미지에 복사
		//2. 이미지메모리DC의 배경색을 없앤후 => 블렌드이미지에 복사
		//3. 블렌드이미지를 화면DC에 복사(알파블렌드)

		//1
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, 0, 0, SRCCOPY);
		
		//2
		GdiTransparentBlt(
			_blendImage->hMemDC,	//복사할 장소의 DC
			0,					//복사할 좌표 시작X
			0,					//복사할 좌표 시작Y
			_imageInfo->width,		//복사할 이미지 가로크기
			_imageInfo->height,		//복사할 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사될 대상의 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상(일반적으로 마젠타)
		//3
		GdiAlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else//원본 이미지 그대로 출력
	{
		GdiAlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

//2번
void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//알파블렌드를 처음 사용하냐?
//알파블렌드를 사용할 수 있도록 초기화 해라
	if (!_blendImage) this->initForAlphaBlend();
	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;


	if (_isTrans)//배경색 없애고 출력
	{
		//1. 현재화면 DC의 내용을 => 블렌드이미지에 복사
		//2. 이미지메모리DC의 배경색을 없앤후 => 블렌드이미지에 복사
		//3. 블렌드이미지를 화면DC에 복사(알파블렌드)

		//1
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, destX, destY, SRCCOPY);

		//2
		GdiTransparentBlt(
			_blendImage->hMemDC,	//복사할 장소의 DC
			0,					//복사할 좌표 시작X
			0,					//복사할 좌표 시작Y
			_imageInfo->width,		//복사할 이미지 가로크기
			_imageInfo->height,		//복사할 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			0, 0,					//복사될 대상의 시작지점
			_imageInfo->width,		//복사 영역 가로크기
			_imageInfo->height,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상(일반적으로 마젠타)
		//3
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else//원본 이미지 그대로 출력
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

//3번
void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//알파블렌드를 처음 사용하냐?
	//알파블렌드를 사용할 수 있도록 초기화 해라
	if (!_blendImage) this->initForAlphaBlend();
	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;


	if (_isTrans)//배경색 없애고 출력
	{
		//1. 현재화면 DC의 내용을 => 블렌드이미지에 복사
		//2. 이미지메모리DC의 배경색을 없앤후 => 블렌드이미지에 복사
		//3. 블렌드이미지를 화면DC에 복사(알파블렌드)

		//1
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, destX, destY, SRCCOPY);

		//2
		GdiTransparentBlt(
			_blendImage->hMemDC,	//복사할 장소의 DC
			0,					//복사할 좌표 시작X
			0,					//복사할 좌표 시작Y
			sourWidth,		//복사할 이미지 가로크기
			sourHeight,		//복사할 이미지 세로크기
			_imageInfo->hMemDC,		//복사될 대상 DC
			sourX,
			sourY,					//복사될 대상의 시작지점
			sourWidth,		//복사 영역 가로크기
			sourHeight,		//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상(일반적으로 마젠타)
		//3
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else//원본 이미지 그대로 출력
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
}
