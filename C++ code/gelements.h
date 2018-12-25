#pragma once

///////////////////////////object2D/////////////////////////////////класс 2D объект

class object2D
{
	protected:

		int left,top; //координаты вверхнего левого угла
		int w,h;//ширина и высота
		char*text;//текс
		bool visible;//видимый на экране объект
		bool mouseuse;//взаимодействует объекта с мышкой
		bool mousein;//нахождение мыши в пределах объекта
		bool mousedown;	//нажатие мыши на объект
		bool keydown;//нажатие кнопки клавиши
		bool gunfire;//выстрел
		int id;//идентификатор объекта

	public:

		object2D()
		{
			left=top=w=h=0; text=NULL;
			gunfire=visible=mouseuse=mousein=mousedown=keydown=false;
		}
		object2D(int left, int top, int w, int h,char*title=NULL)
		{
			this->left=left;
			this->top=top;
			this->h=h;
			this->w=w;
			
			if(title)
			{
				text=new char[strlen(title)+1];
				strcpy(text,title);
			}
			else text=NULL;

			visible=true;
			gunfire=mouseuse=mousein=mousedown=keydown=false;
			id=-1;
		}

		virtual ~object2D()=0
		{
			delete [] text;
			
		}

		virtual void Draw()=0;//метод отрисовки

		virtual bool PointInside(int x,int y)//попадания точки в обект
		{
			return x>=left && x<=left+w && y>=top && y<=top+h;
		}

		virtual bool MouseCheck(int x,int y, bool leftdown)//x,y, координаты мыши лефт нажати левой кнопки
		{
			if(!visible || !mouseuse) return false;

			mousein=PointInside(x,y);
			mousedown=mousein&&leftdown;//при нажатии и нахождении мыши
			
			return mousein; 
		}
	
		void SetText(char*title)
		{
			delete [] text;

			if(title)
			{
				text=new char[strlen(title)+1];
				strcpy(text,title);
			}
			else text=NULL;
		}

		void SetPozition(int left,int top)
		{
			this->left=left;
			this->top=top;
		}

		char* GetText() const
		{
			return text;
		}

		int GetId(){return id;}

		friend class gapp2;
};


///////////////////////////gwindow/////////////////////////////////класс окно
class gwindow:public object2D
{
	protected:

		int colorin, colorout;// 1 цвет заливки 2 цвет рамки
		int textw,texth;//ширина и высота символа
		int textcolor;//цвет текста

	public:

		gwindow(int left=0,int top=0, int w=100, int h=100,char*title="", int id=-1):
		object2D(left,top,w,h,title)
		{
			colorin=sgRGB(255,255,255);
			colorout=sgRGB(0,0,0);
			textw=10;
			texth=20;
			textcolor=sgRGB(0,0,0);
			this->id=id;
		}

		void Draw()
		{
			SgSelectPen(1,colorout);
			SgSelectBrush(BRUSH_SOLID,colorin);
			SgRectangle(left,top,left+w,top+h);

			if(text)
			{
				SgSelectFont(texth,textw,textcolor);
				SgDrawText(left+2,top+2,text);
			}

		}
};

