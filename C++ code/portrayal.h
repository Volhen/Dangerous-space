#pragma once
//////////////////////////picture/////////////////////////////////////////класс картинка
class picture:public object2D
{
	protected:

		int handle; //Идентификатор изображения

	public:

		picture(char*filename=0,int left=0, int top=0,int w=100, int h=100,char*title="",int id=-1):
		object2D(left,top,w,h,title)
		{
			this->left=left;
			this->top=top;
			this->id=id;
			
			if(filename)
			{
				handle=SgLoadImage(filename);
			}
			else handle=0;
		}

		picture(int handle,int left,int top, int w=100, int h=100,char*title="",int id=-1):
		object2D(left,top,w,h,title)
		{
			this->handle=handle;
			this->left=left;
			this->top=top;
			this->id=id;
			SgGetImageSizes( handle, w, h ); 
		}
		void Draw()
		{
			SgDrawImage( handle, left, top );
		}
		
};

//////////////////////////////////animation/////////////////////////////////////////класс анимация 

class animation:public picture
{
	protected:

		int xSrc,ySrc,//координаты верхнего левого угла при анимации
			step,//шаг кадра
			count,//количество кадров в спрайте
			speed,//скорость кадра
			heath,//количество здоровья
			speed_max;//максимальная корость кадра
			
	
	public:

		animation(int handle,int left,int top,int id=-1):
		picture(handle,left,top)
		{
			this->handle=handle;
			this->left=left;
			this->top=top;
			this->id=id;
			SgGetImageSizes( handle, w, h );
			xSrc=ySrc=0;
			count=w/h;
			step=w/count;
			speed=0;
			speed_max=5;
			heath=2;
			
		}
		virtual void Draw();//метод отрисовки
		virtual void Animated();//метод анимации спрайта
		virtual void Move(int left,int top);//метод движения объекта 
		bool RectCrossed(int l1,int t1,int r1,int b1,int l2,int t2,int r2,int b2);//метод проверки столкновения объекта с объектом
		bool Cross(animation*obj);//метод проверки столкновения объекта с объектом
		int GetC();//возвращает шаг кадра
		int GetStep();//возвращает шаг кадра
		int GetHeath();//возвращает количество жизни
		int GetLeft();//возвращает левую точку
		int GetTop();//возвращает верх точку
		//int GetCenterLeft();//возвращает центральную левую точку
		//int GetCenterTop();//возвращает центральную верхнюю точку
		int GetRight();//возвращает правую сторону
		int GetBattom();//возвращает низ
		//////////////////для маски/////////////////////////////
		virtual int GetLeft_M();//возвращает левую точку
		virtual int GetTop_M();//возвращает верх точку
		virtual int GetRight_M();//возвращает правую сторону
		virtual int GetBattom_M();//возвращает низ
		///////////////////////////////////////////////////////
		bool StopDraw();//метод фиксации остановки анимации
		void ReduceHeath();//метод отнимает очки здоровья 
		void AddHeath();//метод добавления здоровья 
		bool LifeObject();//метод жизнь объекта
		void SetHeath(int heath);//метод для установки уровня здоровья объекта
		void DrwRec();//проверка на маску
		
};
		void animation::Draw()
		{
			Animated();
			//DrwRec();// для проверки маски
		}

		void animation::Animated()
		{
			Move(0,0);

			SgDrawImageArea( handle, left,  top, xSrc, ySrc, step, h );
				
			speed++;
			
			if(speed>=speed_max)
			{
				xSrc+=step;speed=0;
				if(xSrc==w)
				xSrc=0;
			}
		}
	
		int animation::GetStep(){return step;}

		int animation::GetHeath(){return heath;}

		int animation::GetLeft(){return left;}

		int animation::GetTop(){return top;}

		//int animation::GetCenterLeft(){return left+(step/2);}

		//int animation::GetCenterTop(){return top+(h/2);}

		int animation::GetRight(){return left+step;}

		int animation::GetBattom(){return top+h;}

		//////////////////для маски/////////////////////////////
		int animation::GetLeft_M(){return GetLeft()+1;}//возвращает левую точку маски
		int animation::GetTop_M(){return GetTop()+1;}//возвращает верх точку маски
		int animation::GetRight_M(){return GetRight()-1;}//возвращает правую сторону маски
		int animation::GetBattom_M(){return GetBattom()-1;}//возвращает низ маски
		///////////////////////////////////////////////////////

		bool animation::RectCrossed(int left1,int top1,int right1,int bottom1,int left2,int top2,int right2,int bottom2)
		{
		 int left=left1>left2?left1:left2,
			 right=right1<right2?right1:right2,
			 top=top1>top2?top1:top2,
			 bottom=bottom1<bottom2?bottom1:bottom2;
		 return (left<=right&&top<=bottom);
		}

		bool animation::Cross(animation*obj)
		{
			return RectCrossed(GetLeft_M(),GetTop_M(),GetRight_M(),GetBattom_M(),obj->GetLeft_M(),obj->GetTop_M(),obj->GetRight_M(),obj->GetBattom_M());
		}

		void animation::Move(int left=0,int top=0)
		{
			this->left+=left;
			this->top+=top;
		}

		bool animation::StopDraw()
		{
			if(xSrc==w)
			return true;
			
			else return false;
		}

		void animation::ReduceHeath()
		{
			heath-=1;
		}

		void animation::AddHeath()
		{
			heath+=1;
		}

		bool animation::LifeObject()
		{
			if(GetHeath()>0 && GetHeath()!=0)
			return true;

			else false;
		}

		void animation::SetHeath(int heath)
		{
			this->heath=heath;
		}

		//void animation::DrwRec()//проверка на маску
		//{
		//	SgSelectBrush(0,sgRGB(255,255,255));
		//	SgRectangle(GetLeft_M(),GetTop_M(),GetRight_M(),GetBattom_M());
		//}

//////////////////////////////////asteroid/////////////////////////////////////////класс астероид

class asteroid: public animation
{
	public:

		asteroid(int handle,int left,int top,int id=-1):
		animation(handle,left,top)
		{
			this->handle=handle;
			this->left=left;
			this->top=top;
			this->id=id;
			heath=2;
		}
		//////////////////для маски/////////////////////////////
		int GetLeft_M(){return GetLeft()+10;}//возвращает левую точку маски
		int GetTop_M(){return GetTop()+10;}//возвращает верх точку маски
		int GetRight_M(){return GetRight()-10;}//возвращает правую сторону маски
		int GetBattom_M(){return GetBattom()-10;}//возвращает низ маски
		///////////////////////////////////////////////////////
};
//////////////////////////////////spaceobjects/////////////////////////////////////////класс космические объекты

class spaceobjects: public animation
{
	public:

		spaceobjects(int handle,int left,int top,int id=-1):
		animation(handle,left,top)
		{
			this->handle=handle;
			this->left=left;
			this->top=top;
			this->id=id;
			heath=3;
		}
		//////////////////для маски/////////////////////////////
		int GetLeft_M(){return GetLeft()+20;}//возвращает левую точку маски
		int GetTop_M(){return GetTop()+20;}//возвращает верх точку маски
		int GetRight_M(){return GetRight()-20;}//возвращает правую сторону маски
		int GetBattom_M(){return GetBattom()-20;}//возвращает низ маски
		///////////////////////////////////////////////////////
};
////////////////////////////////////bullet/////////////////////////////////////////класс снаряд

class bullet: public animation
{
	public:

		bullet(int handle,int left=0,int top=0,int id=10):
		animation(handle,left,top)
		{
			this->handle=handle;
			this->left=left;
			this->top=top;
			this->id=id;
			count=w/h*2;
			step=w/count;	
			speed=0;
			speed_max=5;
		}
			
};

////////////////////////////////////life/////////////////////////////////////////класс life

class life: public animation
{
	public:

		life(int handle,int left=0,int top=0,int id=10):
		animation(handle,left,top)
		{
			this->handle=handle;
			this->left=left;
			this->top=top;
			this->id=id;
			
		}
			
};
////////////////////////////////////Stars/////////////////////////////////////////класс stars
class stars: public animation
{
	public:

		stars(int handle,int left=0,int top=0,int id=10):
		animation(handle,left,top)
		{
			this->handle=handle;
			this->left=left;
			this->top=top;
			this->id=id;
		}
		
};

////////////////////////////////////bang/////////////////////////////////////////класс взрыв

class bang: public animation
{
	public:

		bang(int handle,int left,int top,int id=-1):
		animation(handle,left,top)
		{
			this->handle=handle;
			this->left=left;
			this->top=top;
			this->id=id;
			speed=0;
			speed_max=3;
		}
		void Draw()//переопределен для отмены бесконечной анимации
		{
			SgDrawImageArea( handle, left,  top, xSrc, ySrc, step, h );
				
			speed++;
			
			if(speed>=speed_max)
			{
				xSrc+=step;speed=0;
			}
		}
};

////////////////////////////////////StartImge/////////////////////////////////////////класс заставка

class StartImge: public animation
{
	public:

		StartImge(int handle,int left,int top,int id=-1):
		animation(handle,left,top)
		{
			this->handle=handle;
			this->left=left;
			this->top=top;
			this->id=id;
			count=1200/300;
			step=1200/count;
			speed=0;
			speed_max=50;
		}

		void SetXsrc(int xSrc)
		{
			this->xSrc=xSrc;
		}

		void Draw()//переопределен для отмены бесконечной анимации
		{
			if(xSrc<=1200)
			{
				SgDrawImageArea( handle, left,  top, xSrc, ySrc, step, 150 );
				
				speed++;
			
				if(speed>=speed_max)
				{
					xSrc+=step;speed=0;
				}
			}
		}
};

//////////////////////////////////player/////////////////////////////////////////класс игрок

class player: public animation
{
	protected:

		listptr<bullet*> ptr;//список снарядов
				
		int end,start;// конечное значение и перехордное значение
		int handletur,wtur,htur,lefttur,toptur,counttur,steptur,xSrctur,ySrctur,speed2;//дублирование для турбины
		int handleshot,wshot,hshot,leftshot,topshot ;//дублирование для выстрела
		int corectleft,corecttop;//коректировка левый верхний угол
		int i;	

	public:

		player(int handle,int left,int top,int id=-1):
		animation(handle,left,top)
		{
			this->handle=handle;
			this->left=left;
			this->top=top;
			this->id=id;
			speed=0;speed2=0;
			speed_max=5;
			heath=3;
		
			xSrc=6912;end=w;start=xSrc;corectleft=16;corecttop=21;//параметры для спрайта коробля

			//****************************для турбины
			handletur=SgLoadImage("img/turbine/thrust_orange_big2.PNG");
			SgGetImageSizes( handletur, wtur, htur );
			counttur=wtur/htur*2;//количество элементов в спрайте
			steptur=wtur/counttur;//шаг кадра	
			xSrctur=ySrctur=0;
			//*****************************для выстрела
			handleshot=SgLoadImage("img/projectile/projectile_bolt_red.png");
			SgGetImageSizes( handleshot, wshot, hshot );

		}
			//////////////////для маски/////////////////////////////
			int GetLeft_M(){return GetLeft()+25;}//возвращает левую точку маски
			int GetTop_M(){return GetTop()+15;}//возвращает верх точку маски
			int GetRight_M(){return GetRight()-25;}//возвращает правую сторону маски
			int GetBattom_M(){return GetBattom()-15;}//возвращает низ маски
			///////////////////////////////////////////////////////

			virtual void Draw();//метод отрисовки игрока (корабля), с турбиной и выстрелом
			void DrawShot();//метод отрисовки выстрела
			void DrawTur();//метод отрисовки турбины
			void DrawPlayer();//метод отрисовки корабля
			void MakeShot();//метод загрузка снаряда в список
			void DelShot();//метод удаление снаряда
			bool CrossShot(animation*obj);//метод проверки на столкновения снаряда с объектами
			~player();
};
		player::~player(){}		

		void player::MakeShot()
		{
			leftshot=left+(step/2)-5;//привязка к позиции корабля
			topshot=top;//привязка к позиции корабля
			ptr.add_tail(new bullet(handleshot,leftshot,topshot));//добавляем снаряд
		}

		void player::DelShot()
		{
			elem<bullet*>*pt=ptr.get_head();

			if(pt->data->GetTop()<0)
			{
				ptr.dell_head();
			}	
			else
			{
				pt=pt->next;
			}			

		}

		bool player::CrossShot(animation*obj)
		{
			i=0;

				elem<bullet*>*pt=ptr.get_head();

				while(pt)
				{
					if(pt->data->Cross(obj))	
					{ptr.deleting(i);return true;}
					
					pt=pt->next;
					i++;
				}
				return false;
		}

		void player::DrawShot()//отрисовка выстрела
		{
			elem<bullet*>*pt=ptr.get_head();

			while(pt)
			{
				if(pt->data)
				{
					pt->data->Move(0,-5);
					pt->data->Draw();
				}
				pt=pt->next;

				DelShot();

			}
		
		}
		
		void player::DrawTur()//отрисовка сопла
		{
			lefttur=left+(step/2)-corectleft;//привязка к позиции корабля
			toptur=(top+h)-corecttop;//привязка к позиции корабля

			SgDrawImageArea( handletur, lefttur,  toptur, xSrctur, ySrctur, steptur, htur );
			
			speed2++;

			if(speed2>=speed_max)
			{
				xSrctur+=steptur;speed2=0;
				if(xSrctur==wtur)
				xSrctur=0;
			}
		}

		void player::DrawPlayer()
		{
			SgDrawImageArea( handle, left,  top, xSrc, ySrc, step, h );
			speed++;
			
			if(speed>=speed_max)
			{
				xSrc+=step;speed=0;
				if(xSrc==end)xSrc=start;
			}

		}

		void player::Draw()
		{
			DrawPlayer();	
			DrawTur();
			DrawShot();
			//DrwRec();//тест
		}
		
////////////////////////////////////bots/////////////////////////////////////////класс боты

class bots: public player
{
	
	public:

		listptr<bullet*> ptr;//список снарядов

		bots(int handle,int left,int top,int id=-1):
		player(handle,left,top)
		{
			this->handle=handle;
			this->left=left;
			this->top=top;
			this->id=id;
			speed=0;speed2=0;
			speed_max=5;
			heath=3;
			
			//****************************для турбины
			handletur=SgLoadImage("img/turbine/thrust_blue.PNG");
			SgGetImageSizes( handletur, wtur, htur );
			corectleft=15;//коректировка левого угла
			corecttop=16;//коректировка верхнего угла
			counttur=wtur/htur;//количество элементов в спрайте
			steptur=wtur/counttur;//шаг кадра	
			xSrctur=ySrctur=xSrc=ySrc=0;
			//*****************************для выстрела
			handleshot=SgLoadImage("img/projectile/projectile_bolt_blue2.png");
			SgGetImageSizes( handleshot, wshot, hshot );
			
		}

		void MakeShot()
		{
			if( top==0 || top==50 || top==100 || top==150 || top==200 || top==250 || top==300 || top==350 || top==400 || top==450 || top==500 )
			{
				leftshot=left+(step/2)-5;//привязка к позиции корабля
				topshot=(top+h)-20;//привязка к позиции корабля
				ptr.add_tail(new bullet(handleshot,leftshot,topshot));//добавляем снаряд
			}
		}
	
		void DelShot()
		{
			elem<bullet*>*pt=ptr.get_head();

			if(pt->data->GetTop()> SgGetHeight ())
			{
				ptr.dell_head();
			}	
			else
			{
				pt=pt->next;
			}			
		}

		bool CrossShot(player*obj)
		{
			i=0;

				elem<bullet*>*pt=ptr.get_head();

				while(pt)
				{
					if(pt->data->Cross(obj))	
					{ptr.deleting(i);return true;}
					
					pt=pt->next;
					i++;
				}
				return false;
		}

		void DrawShot()//отрисовка выстрела
		{
			MakeShot();

			elem<bullet*>*pt=ptr.get_head();

			while(pt)
			{
				if(pt->data)
				{
					pt->data->Move(0,6);
					pt->data->Draw();
				}
				pt=pt->next;

				DelShot();

			}
		
		}
	
		void DrawTur()//отрисовка сопла
		{
			lefttur=left+(step/2)-corectleft;//привязка к позиции корабля
			toptur=top-corecttop;//привязка к позиции корабля

			SgDrawImageArea( handletur, lefttur,  toptur, xSrctur, ySrctur, steptur, htur );
			
			speed2++;

			if(speed2>=speed_max)
			{
				xSrctur+=steptur;speed2=0;
				if(xSrctur==wtur)
				xSrctur=0;
			}
		}

		void DrawBots()//отрисовка бота
		{
			SgDrawImageArea( handle, left,  top, xSrc, ySrc, step, h );
			speed++;
			
			if(speed>=speed_max)
			{
				xSrc+=step;speed=0;
				if(xSrc==w)
				xSrc=0;
			}

		}

		void Draw()
		{
			DrawBots();
			DrawTur();
			DrawShot();
			//DrwRec();//тест
		}
		
};


