/*
 *   Simple graphics library - ���������� �����������  ��� �������� 
 *	 2011.
 */
#ifdef DLLCOMPILE
#define TYPEDLL __declspec(dllexport)
#else
#define TYPEDLL __declspec(dllimport)
#pragma comment (lib, "GraphicsLibrary.lib")
#endif



#define sgRGB(r,g,b) ((unsigned long)(((unsigned char)(r)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned long)(unsigned char)(b))<<16)))
#define SgRGB	sgRGB


 //������ ����
enum{
	//������������ �����
	SG_FULLSCREEN =1, 
	//����������� �����
	SG_NORMAL = 0
};
// ���� ����
enum {
	//��������
	BRUSH_SOLID=-1,
	//����� �� �������������� � ������������ �����
	BRUSH_CROSS=HS_CROSS,
	//����� �� ������������ ����� 
	BRUSH_DIAGCROSS=HS_DIAGCROSS,
	//�������������� �����
	BRUSH_HORIZONTAL = HS_HORIZONTAL,
	//������������ �����
	BRUSH_VERTICAL=HS_VERTICAL,
	//������������ ����� � ������� �������� ���� � ����� ������ 
	BRUSH_BDIAGONAL = HS_BDIAGONAL,
	//������������ ����� � ������ �������� ���� � ������ ������ 
	BRUSH_FDIAGONAL = HS_FDIAGONAL
};
//���� �����
enum {
	//��������
	PEN_SOLID = PS_SOLID,
	//����� �� �����
	PEN_DOT = PS_DOT,
	//����� �� ����
	PEN_DASH = PS_DASH,
	//���� �����
	PEN_DASHDOT = PS_DASHDOT,
	//���� ��� �����
	PEN_DASHDOTDOT = PS_DASHDOTDOT
};



//������� ����������� ��������
TYPEDLL bool SgCreate( unsigned int width, unsigned int height, const char *title=0 );
//�������� ������� ����������
TYPEDLL void SgDestroy();
//��������, ���������� �� ����
TYPEDLL bool SgIsActive();
//�������� ��������� �� ��������� �����
TYPEDLL void SgPause( int msec );
//�������� ����� ��������� ������
TYPEDLL void SgClearScreen( unsigned long color );
//������ ��� �����
TYPEDLL void SgSelectPen( int width, unsigned long color );
//������ ��� ���� (�������)
TYPEDLL void SgSelectBrush( int style, unsigned long color );
//������ ������ �����
TYPEDLL void SgMoveTo( int x, int y );
//����������� �����
TYPEDLL void SgLineTo( int x, int y );
//���������� �����
TYPEDLL void SgLine( int x1, int y1, int x2, int y2 );
//���������� �������������
TYPEDLL void SgRectangle( int x1, int y1, int x2, int y2 );
//���������� ����
TYPEDLL void SgCircle( int x, int y, int radius );
//���������� �����
TYPEDLL void SgEllipse( int x, int y, int radius1, int radius2 );
//��������� ������ �� �������? 
TYPEDLL bool SgIsKeyDown(int key);
//�������� ������� ������� 
TYPEDLL bool SgGetCursorPos( int& rx, int& ry );
//��������� �����������
TYPEDLL int SgLoadImage( const char *name );
//������ ���������� ���� �� �����������
TYPEDLL void SgSetImageColorKey( int handle, unsigned long color );
//�������� ���������� ���� �� ����������� 
TYPEDLL void SgResetImageColorKey( int handle );
//���������� �����������
TYPEDLL void SgDrawImage( int handle, int x, int y );
//���������� �������� �����������
TYPEDLL void SgDrawImageArea( int handle, int xDest, int yDest, int xSrc, int ySrc, int widthSrc, int heightSrc );
//���������� ����������� � ����������� ������������ 
TYPEDLL void SgDrawAlphaImage( int handle, int x, int y, int alpha );
//���������� �������� ����������� � ����������� ������������ 
TYPEDLL void SgDrawAlphaImage( int handle, int xDest, int yDest, int xSrc, int ySrc, int widthSrc, int heightSrc , int alpha);
//��������� � ���������� �����������
TYPEDLL void SgDrawImageFile( const char *name, int x, int y );
//�������� ������ �����������
TYPEDLL bool SgGetImageSizes( int handle, int& width, int& height );
//������ ��������� ������
TYPEDLL void SgSelectFont(int Height,int Width,int clr,char*face="Tahoma",bool IsItalic=false,bool IsUnderLine=false,bool IsStrike=false,int Orientation=0);
//������� �����
TYPEDLL void SgDrawText(int x,int y,const char*pstr,...);
//��������� �������(������� mp3|wav|ogg)
TYPEDLL long SgLoadSound(char*name);
//������������� ������� 
TYPEDLL void SgPlaySound(long handle);
//���������� �������
TYPEDLL void SgStopSound(long handle);
//������� �������
TYPEDLL void SgDestroySound(long handle);
//������������� �������
TYPEDLL void SgPauseSound(long handle);
//������ ��������� (�� 0 �� 100)
TYPEDLL void SgSetVolume(long volume);
//�������� ��������� (�� 0 �� 100)
TYPEDLL long SgGetVolume();
//�������� ������������ ������� � ��������
TYPEDLL double SgGetSoundDuration(long handle);
//������ ������ ��������������� � ��������
TYPEDLL void SgSetSoundPosition(long handle, double seconds);
//�������� ���������� ����������� ������ 
TYPEDLL double SgGetSoundPosition(long handle);
//�������� ������� �������
TYPEDLL void SgGetSoundData(long handle, float data[],int count);
//���������� ��������
TYPEDLL void SgGradient(int left,int top,int right,int bottom,int clr1,int clr2,bool IsHorz = true);
//��������� ����� ��� ���������
TYPEDLL void SgBeginDraw();
//��������� ����� ��� ���������
TYPEDLL void SgEndDraw();
//������ �������
TYPEDLL void SgHideConsole();
//���������� �������
TYPEDLL void SgShowConsole();
//���������� ����� ����
TYPEDLL void SgScreenMode(int iMode);
//�������� ������ ����
TYPEDLL int SgGetWidth();
//�������� ������ ����
TYPEDLL int SgGetHeight();
//�������� ���� � ����� ��� ��������
TYPEDLL BOOL SgGetOpenFile(char*path,int length,char*filter="All Files\0*.*\0\0");
//�������� ���� � ����� ��� ����������
TYPEDLL BOOL SgGetSaveFile(char*path,int length,char*filter="All Files\0*.*\0\0");