#pragma once
//=============================================================
//	## image ## (앞으로 계속 업데이트 된다)
//=============================================================

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,  //리소스로 로딩(사용안함)
		LOAD_FILE,			//파일로 로딩
		LOAD_EMPTY,			//빈비트맵 로딩
		LOAD_END
	};

	typedef struct tagImage
	{
		HDC hMemDC;			//메모리 DC
		HBITMAP hBit;		//비트맵
		HBITMAP hOBit;		//올드비트맵
		int width;			//이미지 가로길이
		int height;			//이미지 세로길이
		BYTE loadType;		//이미지 로드타입
		tagImage()			//생성자 = 초기화
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
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	char*			_fileName;		//이미지 이름
	bool			_isTrans;		//배경색 없앨거냐?
	COLORREF		_transColor;	//배경색 없앨 RGB색상 (마젠타 = RGB(255, 0, 255))	
	
	LPIMAGE_INFO	_blendImage;	//알파블렌드 이미지
	BLENDFUNCTION	_blendFunc;		//알파블렌드 기능

public:
	image();
	~image();

	//빈 비트맵 초기화
	HRESULT init(int width, int height);
	//이미지 리소스 초기화 => 사용안해서 안만듬
	//이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//알파블렌드 초기화
	HRESULT initForAlphaBlend();

	//해제
	void release();

	//렌더(내가 원하는 좌표에 출력해라, 일반적으로 RECT의 LT좌표에 이미지를 붙인다)
	void render(HDC hdc, int destX = 0, int destY = 0);
	//렌더(원하는 좌표에 이미지를 잘라서 붙이기)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	
	//알파렌더(이미지를 알파값만큼 투명화 시켜준다)
	//0(min) ~ 255(max)
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int dextX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//DC 얻기
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
};

