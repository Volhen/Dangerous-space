#pragma once

class gapp // ��������� ������� ����� ����������� ����������
{
protected:
	int w, // ������ ���� ����
		h, // ������ ���� ����
		pause, // ����� � ������������
		backcolor; // ������� ����
	bool exit_; // ��� ������
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

		listptr<object2D*> ctrl;//������ ������� ����
	
		bool prevleftdown;//����������� ��������� ����� ������ ����
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
			CheckMouse();//������� ����
			KeyDown();//������� �����
			
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

		void gapp2::OnClick(object2D*obj){}//����� ������ ����� ���� �� �������� ����������

		void gapp2::PressButtom(object2D*obj){}//����� ������ ������� ������� 

		void gapp2::CheckMouse()//����� ������ ����� ���� �� �������� ����������
		{
			int mousex,mousey;
			
			SgGetCursorPos(mousex,mousey);

			bool leftdown=SgIsKeyDown(VK_LBUTTON);

			elem<object2D*>*ptr=ctrl.get_head();

			while(ptr)
			{
				if(ptr->data->visible)
				{
					if(ptr->data->MouseCheck(mousex,mousey,leftdown)&&prevleftdown && !leftdown) //���� ��� ��������� ������ ������� � ���� ������ ������ �������, � ������ �� ������, �� ��� ���� �� ������
						OnClick(ptr->data);
				}
				ptr=ptr->next;
			}

			prevleftdown=leftdown;//�������������� ��������� ����
		}

		void gapp2::KeyDown()//����� ������ ������� �����
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

		object2D*gapp2::GetObj(int id)//����� ��������� ������� �� ID
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
