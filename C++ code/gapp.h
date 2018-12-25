#pragma once

class gapp // Реализуем базовый класс графическое приложение
{
protected:
	int w, // ширина граф окна
		h, // высота граф окна
		pause, // пауза в милисекундах
		backcolor; // фоновый цвет
	bool exit_; // для выхода
public:
	gapp(int w, int h, char *title="gapp",int pause=15,int backcolor=0)
	{
		this->w=w;
		this->h=h;
		this->backcolor=backcolor;
		this->pause=pause;
		SgHideConsole();
		SgCreate(w,h,title);
		exit_=false;
	}
	virtual ~gapp();
	virtual void StartProcess();
	virtual void Process();
	virtual void EndProcess();
	virtual void WorkProcess();
};
	gapp::~gapp()
	{
		SgDestroy();
		SgShowConsole();
	}
	void gapp::StartProcess()
	{
		SgBeginDraw();
		SgClearScreen(backcolor);
	}
	void gapp::Process(){}

	void gapp::EndProcess()
	{
		SgEndDraw();
		SgPause(pause);
	}
	void gapp::WorkProcess()
	{
		while(!exit_&&SgIsActive())
		{
			StartProcess();
			Process();
			EndProcess();
		}
	}

////////////////////////////////////
class gapp2:public gapp
{
	protected:

		listptr<object2D*> ctrl;//список объктов окна
	
		bool prevleftdown;//передыдущее состояние левой кнопки мыши
		bool prevkey;

	public:

		gapp2(int w,int h, char*title):
		gapp(w,h,title),ctrl()
		{
			prevleftdown=prevkey=false;
		}
		void Process();
		virtual void OnClick(object2D*obj);
		virtual void PressButtom(object2D*obj);
		virtual void CheckMouse();
		virtual void KeyDown();
		object2D* GetObj(int id);
};	
		void gapp2::Process()
		{
			CheckMouse();//нажатие мыши
			KeyDown();//нажатие клавы
			
			elem<object2D*>*ptr=ctrl.get_head();

			while(ptr)
			{
				if(ptr->data->visible)
				{
					ptr->data->Draw();
					
				}
				ptr=ptr->next;
			}
		}

		void gapp2::OnClick(object2D*obj){}//метод вызова клика мыши на элементе управления

		void gapp2::PressButtom(object2D*obj){}//метод вызова нажатие клавиши 

		void gapp2::CheckMouse()//метод вызова клика мыши на элементе управления
		{
			int mousex,mousey;
			
			SgGetCursorPos(mousex,mousey);

			bool leftdown=SgIsKeyDown(VK_LBUTTON);

			elem<object2D*>*ptr=ctrl.get_head();

			while(ptr)
			{
				if(ptr->data->visible)
				{
					if(ptr->data->MouseCheck(mousex,mousey,leftdown)&&prevleftdown && !leftdown) //если мыш находится внутри объекта и была нажата внутри объекта, а сейчас не нажата, то это клик на объект
						OnClick(ptr->data);
				}
				ptr=ptr->next;
			}

			prevleftdown=leftdown;//перезаписываем состояние мыши
		}

		void gapp2::KeyDown()//метод вызова нажатия клавы
		{
			
			if(SgIsKeyDown(VK_LEFT) || SgIsKeyDown(VK_RIGHT) || SgIsKeyDown(VK_UP) || SgIsKeyDown(VK_DOWN) || SgIsKeyDown(VK_SPACE))
			{				
				elem<object2D*>*ptr=ctrl.get_head();

				while(ptr)
				{
					if(ptr->data->visible)
					{
						PressButtom(ptr->data);
					}
					ptr=ptr->next;
				}

			}
			
		}

		object2D*gapp2::GetObj(int id)//метод получения объекта по ID
		{
			elem<object2D*>*ptr=ctrl.get_head();

			while(ptr)
			{
				if(ptr->data->id==id)
				{
					return ptr->data;
				}
				ptr=ptr->next;

			}
			return NULL;
		}
