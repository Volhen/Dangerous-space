/*
 *   Simple graphics library - Библиотека разработана  для обучения 
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


 //Тежимы окна
enum{
	//Полноэкраный режим
	SG_FULLSCREEN =1, 
	//Стандартный режим
	SG_NORMAL = 0
};
// Типы фона
enum {
	//Сплошная
	BRUSH_SOLID=-1,
	//Сетка из горизонтальных и вертикальных линий
	BRUSH_CROSS=HS_CROSS,
	//Сетка из диагональных линий 
	BRUSH_DIAGCROSS=HS_DIAGCROSS,
	//горизонтальные линии
	BRUSH_HORIZONTAL = HS_HORIZONTAL,
	//вертикальные линии
	BRUSH_VERTICAL=HS_VERTICAL,
	//Диагональные линии с правого верхнего угла в левый нижний 
	BRUSH_BDIAGONAL = HS_BDIAGONAL,
	//Диагональные линии с левого верхнего угла в правый нижний 
	BRUSH_FDIAGONAL = HS_FDIAGONAL
};
//Типы линий
enum {
	//Сплошная
	PEN_SOLID = PS_SOLID,
	//Линия из точек
	PEN_DOT = PS_DOT,
	//Линия из тире
	PEN_DASH = PS_DASH,
	//Тире точка
	PEN_DASHDOT = PS_DASHDOT,
	//Тире две точки
	PEN_DASHDOTDOT = PS_DASHDOTDOT
};



//Создать графическую оболочку
TYPEDLL bool SgCreate( unsigned int width, unsigned int height, const char *title=0 );
//Очистить ресурсы библиотеки
TYPEDLL void SgDestroy();
//Проверка, существует ли окно
TYPEDLL bool SgIsActive();
//Задержка программы на указанное время
TYPEDLL void SgPause( int msec );
//Очистить экран указанным цветом
TYPEDLL void SgClearScreen( unsigned long color );
//Задать тип линии
TYPEDLL void SgSelectPen( int width, unsigned long color );
//Задать тип фона (заливки)
TYPEDLL void SgSelectBrush( int style, unsigned long color );
//Задать начало линии
TYPEDLL void SgMoveTo( int x, int y );
//Прорисовать линию
TYPEDLL void SgLineTo( int x, int y );
//нарисовать линию
TYPEDLL void SgLine( int x1, int y1, int x2, int y2 );
//нарисовать прямоугольник
TYPEDLL void SgRectangle( int x1, int y1, int x2, int y2 );
//нарисовать круг
TYPEDLL void SgCircle( int x, int y, int radius );
//нарисовать Елипс
TYPEDLL void SgEllipse( int x, int y, int radius1, int radius2 );
//Проверить нажата ли клавиша? 
TYPEDLL bool SgIsKeyDown(int key);
//Получить позицию курсора 
TYPEDLL bool SgGetCursorPos( int& rx, int& ry );
//Загрузить изображение
TYPEDLL int SgLoadImage( const char *name );
//Задать прозрачный цвет на изображении
TYPEDLL void SgSetImageColorKey( int handle, unsigned long color );
//Сбросить прозрачный цвет на изображении 
TYPEDLL void SgResetImageColorKey( int handle );
//Нарисовать изображение
TYPEDLL void SgDrawImage( int handle, int x, int y );
//Нарисовать фрагмент изображения
TYPEDLL void SgDrawImageArea( int handle, int xDest, int yDest, int xSrc, int ySrc, int widthSrc, int heightSrc );
//Нарисовать изображение с применением прозрачности 
TYPEDLL void SgDrawAlphaImage( int handle, int x, int y, int alpha );
//Нарисовать фрагмент изображения с применением прозрачности 
TYPEDLL void SgDrawAlphaImage( int handle, int xDest, int yDest, int xSrc, int ySrc, int widthSrc, int heightSrc , int alpha);
//Загрузить и нарисовать изображение
TYPEDLL void SgDrawImageFile( const char *name, int x, int y );
//Получить размер изображения
TYPEDLL bool SgGetImageSizes( int handle, int& width, int& height );
//Задать настройки шрифта
TYPEDLL void SgSelectFont(int Height,int Width,int clr,char*face="Tahoma",bool IsItalic=false,bool IsUnderLine=false,bool IsStrike=false,int Orientation=0);
//Вывести текст
TYPEDLL void SgDrawText(int x,int y,const char*pstr,...);
//Загрузить мелодию(форматы mp3|wav|ogg)
TYPEDLL long SgLoadSound(char*name);
//Воспроизвести мелодию 
TYPEDLL void SgPlaySound(long handle);
//Остановить мелодию
TYPEDLL void SgStopSound(long handle);
//Удалить мелодию
TYPEDLL void SgDestroySound(long handle);
//Приостановить мелодию
TYPEDLL void SgPauseSound(long handle);
//Задать громкость (от 0 до 100)
TYPEDLL void SgSetVolume(long volume);
//Получить громкость (от 0 до 100)
TYPEDLL long SgGetVolume();
//Получить длительность мелодии в секундах
TYPEDLL double SgGetSoundDuration(long handle);
//Задать начало воспроизведения в секундах
TYPEDLL void SgSetSoundPosition(long handle, double seconds);
//Получить количество проигранных секунд 
TYPEDLL double SgGetSoundPosition(long handle);
//получить частоты мелодии
TYPEDLL void SgGetSoundData(long handle, float data[],int count);
//Нарисовать градиент
TYPEDLL void SgGradient(int left,int top,int right,int bottom,int clr1,int clr2,bool IsHorz = true);
//Открывает поток для рисования
TYPEDLL void SgBeginDraw();
//Закрывает поток для рисования
TYPEDLL void SgEndDraw();
//Скрыть консоль
TYPEDLL void SgHideConsole();
//Отобразить консоль
TYPEDLL void SgShowConsole();
//Установить режим окна
TYPEDLL void SgScreenMode(int iMode);
//Получить ширину окна
TYPEDLL int SgGetWidth();
//Получить высоту окна
TYPEDLL int SgGetHeight();
//Получить путь к файлу для открытия
TYPEDLL BOOL SgGetOpenFile(char*path,int length,char*filter="All Files\0*.*\0\0");
//Получить путь к файлу для сохранения
TYPEDLL BOOL SgGetSaveFile(char*path,int length,char*filter="All Files\0*.*\0\0");