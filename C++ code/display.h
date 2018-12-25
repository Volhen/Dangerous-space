#pragma once
using namespace std;
//////////////////////////display/////////////////////////////////////////����� �����
class display: public gwindow
{
	protected:

		int handle;//������������� �����������
		int point;//����
		int levl;//������� ����
		int life;//������� ����
		int x,n;//���������� ��� ���������� ����������� ������� �����
		
		listptr<picture*> pic;//������ ������ �� �������
		listptr<picture*> dis;//������ ��������� �������
		listptr<StartImge*> at;//������ 3,2,1 go!

	public:

		display(char*title="",int left=15, int top=15,int w=100, int h=100, int id=-1):
		gwindow(left,top,w,h,title)
		{
			textcolor=sgRGB(255,255,255);
			levl=1;
			x=970;
			life=3;
					
			///////////////////���������� �� �������/////////////////////////////			
			dis.add_tail(new picture(SgLoadImage("img/display/life.png"),0,576));
			dis.add_tail(new picture(SgLoadImage("img/display/2.png"),783,0));
			dis.add_tail(new picture(SgLoadImage("img/display/3.png"),0,0));
			at.add_tail(new StartImge(SgLoadImage("img/display/777.png"),362,275));
						
		}

		void DrawStart();//������������ ������ ����
		void DrawImage();//������������ ������ ����
		void DrawText();//��� ��������� ���������� �����
		void DrawIndicatorHeat();//������������ ���������� ����� �� �������
		void DrawIndicatorLevl();//������������ ���������� ������ �� �������
		void DrawIndicator();//������������ ���������� �����, �����,������ ������������ 
		void Draw();//����� ��������� �������
		void SetPoint(int point);//��������� ���������� �����
		void SetLevl(int levl);//��������� ������ ����
		void SetDrawLifeIndicator(int life);//��������� ���������� ����� �� 
		int GetPoint();//���������� ���������� �����
		void AddLifeIndicator();// ���������� ��������� �����
		void DelDrawIndicator();//�������� ���������� �����
		void DelAllDrawIndicator();//�������� ���������� ����� (�����)
		
		
};
			
		void display::SetDrawLifeIndicator(int l)
		{
			x=970;//���������� �� ���������
			if(pic.get_count()>0)DelAllDrawIndicator();
			for(int i=0;i<l;i++)
			AddLifeIndicator();
		}

		void display::DrawStart()
		{
			elem<StartImge*>*pt=at.get_head();
		
				pt->data->Draw();
				pt=pt->next;
		}

		void display::SetPoint(int point)
		{
			this->point=point;
		}

		void display::SetLevl(int levl)
		{
			this->levl=levl;
		}

		void display::DrawText()
		{
			SgSelectFont(texth,textw,textcolor);
			SgDrawText(left,top,"%s%i","Score: ", point);
		}
		
		void display::DrawIndicatorLevl()
		{
			SgSelectFont(texth,textw,textcolor);
			SgDrawText(42,582,"%i", levl);
		}
		
		int display::GetPoint(){return point;}

		void display::DelDrawIndicator()
		{
			pic.dell_tail();
			x+=35;
		}

		void display::DelAllDrawIndicator()
		{
			pic.clear();			
		}

		void display::AddLifeIndicator()// ���������� ��� �����
		{
			pic.add_tail(new picture(SgLoadImage("img/display/S5.png"),x,10));
			x-=35;
		}

		void display::DrawIndicatorHeat()
		{
			elem<picture*>*pt=pic.get_head();

			while(pt)
			{
				pt->data->Draw();
				pt=pt->next;
			}
		}

		void display::DrawIndicator()//����������
		{
			elem<picture*>*pt=dis.get_head();

				while(pt)
				{
					pt->data->Draw();
					pt=pt->next;
				}
		}

		void display::Draw()
		{
			DrawStart();
			DrawIndicator();
			DrawIndicatorHeat();
			DrawText();
			DrawIndicatorLevl();
		}

////////////////////////////button//////////////////////////////////����� ������
class button:public gwindow
{
	
	protected:
		
		int r0,g0,b0,r1,g1,b1;
		listptr<picture*> pic;//������ �������� ��� ������

	public:
		button(int left, int top,int w, int h, char*title,int id=-1):
		gwindow(left,top,w,h,title)
		{
			this->id=id;
			r0=g0=b0=192;
			r1=g1=b1=128;
			
			mouseuse=true;

			pic.add_tail(new picture(SgLoadImage("img/button/s2_button_on.png"),left,top));
			pic.add_tail(new picture(SgLoadImage("img/button/s2_button_off.png"),left,top));
		}
	
		void DrawMouseDown();//��������� ������� �� ����
		void Drawmousein();//��������� ���������� ����
		void Drawmouse();//��������� �������� ����
		void Draw();//������� ����������� ����
};
		void button::DrawMouseDown()
		{
			elem<picture*>*ptr=pic.get_element(0);
			ptr->data->Draw();
			
			SgSelectFont(texth,textw,sgRGB(230,12,30));
		}

		void button::Drawmousein()
		{
			elem<picture*>*ptr=pic.get_element(1);
			ptr->data->Draw();
			
			SgSelectFont(texth,textw,sgRGB(0,245,0));
		}

		void button::Drawmouse()
		{
			elem<picture*>*ptr=pic.get_element(1);
			ptr->data->Draw();
			
			SgSelectFont(texth,textw,sgRGB(0,0,0));
		}

		void button::Draw()
		{
			if(mousedown)//���� ��� ������
			{
				DrawMouseDown();
			}
			else
			if(mousein)
			{	
				Drawmousein();
			}
			else
			{
				Drawmouse();
			}

			SgDrawText(left+(w-textw*strlen(text))/2,top+(h-texth)/2,text);//������������ ������

		}
		

//////////////////////////MENU/////////////////////////////////////////����� MENU
class menu: public  button
{
	listptr<picture*> pic;//������ ��������
	listptr<button*> but;//������ ������
	int IdButton;//ID ������� ������ ����
	bool prevleftdown;//����������� ��������� ����� ������ ����
	

	enum{MENU,NEW_GAME,CONTINUE,RESULTS,MANUAL,EXIT};//ID �������

	public:
			menu(int left=0, int top=0,int w=256, int h=64, char*title="",int id=-1):
			button(left,top,w,h,title)
			{
				this->id=id;
				this->left=left;
				this->top=top;
				this->w=w;
				this->h=h;
				prevleftdown=false;
				pic.add_tail(new picture(SgLoadImage("img/Backgrounds/Background7.jpg"),left,top));
				pic.add_tail(new picture(SgLoadImage("img/letters/Dangerous.png"),177,50));
				but.add_tail(new button(384,200,256,64,"NEW GAME",NEW_GAME));
				but.add_tail(new button(384,274,256,64,"CONTINUE",CONTINUE));
				but.add_tail(new button(384,348,256,64,"RESULTS",RESULTS));
				but.add_tail(new button(384,422,256,64,"MANUAL",MANUAL));
				but.add_tail(new button(384,496,256,64,"EXIT",EXIT));
				IdButton=0;		
			}

			void DrawBackgrounds();//��� ����
			void DrawButton();//��������� ������ ����
			void Draw();//��������� ����
			void OnClick(button* obj);//����� ���������� ������� ������� ����� 
			void CheckMouse();//����� ������ ����� ���� �� �������� ����������
			int GetIdButton();//����� ���������� ������� ID ������ ��� ������� ����
			void RezetIdButton();//����� �������������� ��������� IdButton
			
};

	void menu::DrawBackgrounds()
	{
		elem<picture*>*pt=pic.get_head();

		while(pt)
		{
			pt->data->Draw();
			pt=pt->next;
		}
	}

	void menu::DrawButton()
	{
		elem<button*>*pt=but.get_head();

		while(pt)
		{
			pt->data->Draw();
			pt=pt->next;
		}
	}

	void menu::OnClick(button* obj)
	{
		IdButton=obj->GetId();
	}
	
	int menu::GetIdButton(){return IdButton;}

	void menu::RezetIdButton(){IdButton=0;}

	void menu::CheckMouse()
	{
		int mousex,mousey;
			
		SgGetCursorPos(mousex,mousey);

		bool leftdown=SgIsKeyDown(VK_LBUTTON);

		elem<button*>*ptr=but.get_head();

		while(ptr)
		{
			if(ptr->data)
			{
				if(ptr->data->MouseCheck(mousex,mousey,leftdown)&&prevleftdown && !leftdown) //���� ��� ��������� ������ ������� � ���� ������ ������ �������, � ������ �� ������, �� ��� ���� �� ������
					OnClick(ptr->data);
			}
			ptr=ptr->next;
		}

		prevleftdown=leftdown;//�������������� ��������� ����
	}
	
	void menu::Draw()
	{
		CheckMouse();
		DrawBackgrounds();
		DrawButton();
	}


////////////////////////////death_player/////////////////////////////////////////����� ������ ������������
class death_player: public  picture
{
	int point,SEC;
	listptr<picture*> pic;//������ ��������
	public:
			death_player(int handle=0,int left=0,int top=0,int id=-1):
			picture(handle,left,top)
			{
				this->handle=handle;
				this->left=left;
				this->top=top;
				this->id=id;
				SEC=point=0;
				pic.add_tail(new picture(SgLoadImage("img/Backgrounds/D.jpg"),left,top));
			}
			void SetPoint(int point);//��������� �����
			void DrawText();//����� ������ � ����������� ������
			void DrawBackgrounds();//��������� ��������
			void Draw();
			void LoadPoints();//�������� ����������� (�����)
			void SavePointsBest();//���������� ������� ���������� (�����)
			void SavePoints();//���������� �������� ����������
			
};
	
		void death_player::LoadPoints()
		{
			ifstream f("Results/Points_best",ios::binary|ios::in);

			if(!f)
			{
				SavePointsBest();return;//���� ����� ���, �� ��������� ������� � �������
			}
			
			int temp_point=0;

			f.read((char*)&temp_point,sizeof(temp_point));
			f.close();

			if(temp_point<=point)//���� ����������� ��������� ������ �� ������������ ����� ������
			SavePointsBest();
			
			SavePoints();//��������� ������� ���������
		}

		void death_player::SavePointsBest()
		{
			time_t seconds = time(NULL);
			tm* timeinfo = localtime(&seconds);//�������� ������� �������� ������
			SEC=seconds;

			ofstream f("Results/Points_best",ios::out|ios::binary/*| ios::app*/);
			f.write((char*)&point,sizeof(point));//���������� � ���� point
			f.write((char*)&SEC,sizeof(SEC));//���������� � ���� �������
			f.write("\n",sizeof(char));
			f.close();

		}

		void death_player::SavePoints()
		{
			time_t seconds = time(NULL);
			tm* timeinfo = localtime(&seconds);//�������� ������� �������� ������
			SEC=seconds;

			ofstream f("Results/Points",ios::out|ios::binary/*| ios::app*/);
			f.write((char*)&point,sizeof(point));//���������� � ���� point
			f.write((char*)&SEC,sizeof(SEC));//���������� � ���� �������
			f.write("\n",sizeof(char));
			f.close();

		}

		void death_player::SetPoint(int point)
		{
			this->point=point;
		}

		void death_player::DrawText()
		{
			SgSelectFont(20,10,sgRGB(0,245,0));
			SgDrawText(((SgGetWidth()-10)/2)-10,(SgGetHeight()-20)/2,"%s%s%i","You died !!!\n","Score: ", point);
			LoadPoints();
		}

		void death_player::DrawBackgrounds()
		{
			elem<picture*>*pt=pic.get_head();

			while(pt)
			{
				pt->data->Draw();
				pt=pt->next;
			}
		}

		void death_player::Draw()
		{
			DrawBackgrounds();
			DrawText();
		}

////////////////////////////result/////////////////////////////////////////����� result
class result: public  picture
{
	int point,b_point,SEC,b_SEC,n;
	int year,month,day,hour,min,sec;//date and time 
	int b_year,b_month,b_day,b_hour,b_min,b_sec;//the best point 
	listptr<picture*> pic;//������ ��������
	
	public:
			result(int handle=0,int left=0,int top=0,int id=-1):
			picture(handle,left,top)
			{
				this->handle=handle;
				this->left=left;
				this->top=top;
				this->id=id;
				n=1;
				year=month=day=hour=min=sec=SEC=point=0;
				b_year=b_month=b_day=b_hour=b_min=b_sec=b_SEC=b_point=0;
				pic.add_tail(new picture(SgLoadImage("img/Backgrounds/Background2.png"),left,top));

			}
			void DrawText();//����� ������ � ����������� ������
			void DrawBackgrounds();//��������� ��������
			void Draw();
			void LoadPoints();//�������� ����������� (the best)
			
};
		
		void result::LoadPoints()
		{
			ifstream f_b("Results/Points_best",ios::binary|ios::in);//�������� ������� ����������
			ifstream f("Results/Points",ios::binary|ios::in);//�������� ���������� ���������� ����������

			if(!f_b && !f)
			{
				SgSelectFont(40,20,sgRGB(255,0,0));
				SgDrawText((SgGetWidth ()-400)/2,SgGetHeight ()/2,"%s","NO DATA OF RESULT !!!");
				return;
			}
			///////////////////////�������� ������� ����������////////////////////////////////
			f_b.read((char*)&b_point,sizeof(b_point));
			f_b.read((char*)&b_SEC,sizeof(b_SEC));
			f_b.close();
			
			time_t b_seconds = b_SEC;
			tm* b_timeinfo = localtime(&b_seconds);//�������� �������� ������
		
			b_year=b_timeinfo->tm_year+1900;
			b_month=b_timeinfo->tm_mon+1;
			b_day=b_timeinfo->tm_mday;
			b_hour=b_timeinfo->tm_hour;
			b_min=b_timeinfo->tm_min;
			b_sec=b_timeinfo->tm_sec;

			///////////////////////�������� ���������� ���������� ����������//////////////////

			f.read((char*)&point,sizeof(point));
			f.read((char*)&SEC,sizeof(SEC));
			f.close();
			
			time_t seconds = SEC;
			tm* timeinfo = localtime(&seconds);//�������� �������� ������
		
			year=timeinfo->tm_year+1900;
			month=timeinfo->tm_mon+1;
			day=timeinfo->tm_mday;
			hour=timeinfo->tm_hour;
			min=timeinfo->tm_min;
			sec=timeinfo->tm_sec;
		}

		void result::DrawText()
		{			
			LoadPoints();
			SgSelectFont(30,15,sgRGB(0,245,0));
			SgDrawText((SgGetWidth ()-110)/2,50,"%s","RESULTS:");
			SgSelectFont(20,10,sgRGB(255,0,0));
			SgDrawText(160,100,"%s","�");
			SgDrawText(360,100,"%s","DATE");
			SgDrawText(560,100,"%s","TIME");
			SgDrawText(760,100,"%s","SCORE");

			//////////////�/////////////// ������ ���������
			SgSelectFont(20,10,sgRGB(255,165,0));
			SgDrawText(160,140,"%s","best result");
			SgSelectFont(20,10,sgRGB(0,245,0));
			//////////////DATE////////////
			SgDrawText(360,140,"%i%s%i%s%i",b_day,"/",b_month,"/",b_year);
			//////////////Time////////////
			SgDrawText(560,140,"%i%s%i%s%i",b_hour,":",b_min,":",b_sec);
			//////////////Time////////////
			SgDrawText(760,140,"%i",b_point);

			//////////////�/////////////// ��������� ���������
			SgSelectFont(20,10,sgRGB(255,165,0));
			SgDrawText(160,180,"%s","last result");
			SgSelectFont(20,10,sgRGB(0,245,0));
			//////////////DATE////////////
			SgDrawText(360,180,"%i%s%i%s%i",day,"/",month,"/",year);
			//////////////Time////////////
			SgDrawText(560,180,"%i%s%i%s%i",hour,":",min,":",sec);
			//////////////Time////////////
			SgDrawText(760,180,"%i",point);
		}

		void result::DrawBackgrounds()
		{
			elem<picture*>*pt=pic.get_head();

			while(pt)
			{
				pt->data->Draw();
				pt=pt->next;
			}
		}

		void result::Draw()
		{
			DrawBackgrounds();
			DrawText();
		}

////////////////////////////Options/////////////////////////////////////////����� Options
class options: public  picture
{
	listptr<picture*> at;//������ ����������� �������� ��� �����
	listptr<picture*> bc;//������ �������� ��� Backgrounds
	public:
			options(int handle=0,int left=0,int top=0,int id=-1):
			picture(handle,left,top)
			{
				this->handle=handle;
				this->left=left;
				this->top=top;
				this->id=id;
				
				bc.add_tail(new picture(SgLoadImage("img/Backgrounds/Background3.png"),left,top));
							
				at.add_tail(new picture(SgLoadImage("img/Options/rock_type_A0000.png"),50,100));
				at.add_tail(new picture(SgLoadImage("img/Options/saucer_blades0000.png"),30,150));	
				at.add_tail(new picture(SgLoadImage("img/Options/saucer0000.png"),30,250));	
				at.add_tail(new picture(SgLoadImage("img/Options/fighter0000.png"),30,350));
				at.add_tail(new picture(SgLoadImage("img/Options/scythe0000.png"),130,350));
				at.add_tail(new picture(SgLoadImage("img/Options/slicer0000.png"),230,350));
				at.add_tail(new picture(SgLoadImage("img/Options/spikey0003.png"),30,450));
				at.add_tail(new picture(SgLoadImage("img/Options/player0004.png"),30,550));

			}
			
			void DrawAnimation();//��������� ��������
			void DrawText();//����� ������ 
			void DrawBackgrounds();//��������� ��������
			void Draw();
			
};
		
		void options::DrawAnimation()
		{
			elem<picture*>*ptr=at.get_head();

			while(ptr)
			{
				if(ptr->data)
				{
					ptr->data->Draw();	
					ptr=ptr->next;	
				}
			}
		}

		void options::DrawText()
		{
			SgSelectFont(30,15,sgRGB(0,245,0));
			SgDrawText(50,50,"%s","SPACE OBJECTS:");
			SgSelectFont(20,10,sgRGB(255,0,0));
			SgDrawText(180,110,"%s","- space objects of three kinds (2 life);");
			SgDrawText(180,190,"%s","- space objects of extraterrestrial origin (3 life);");
			SgDrawText(180,290,"%s","- space objects of extraterrestrial origin (3 life);");
			SgDrawText(350,390,"%s","- alien spaceships (4 life);");
			SgDrawText(180,490,"%s","- restores the user's life (10 percent chance);");
			SgDrawText(180,590,"%s","- the spacecraft user;");
		}
		
		void options::DrawBackgrounds()
		{
			elem<picture*>*pt=bc.get_head();

			while(pt)
			{
				pt->data->Draw();
				pt=pt->next;
			}
		}

		void options::Draw()
		{
			DrawBackgrounds();
			DrawText();
			DrawAnimation();
		}