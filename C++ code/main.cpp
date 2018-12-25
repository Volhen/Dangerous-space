//#include <iostream>
#include <Windows.h>
#include <ctime>
#include <fstream>
#include "graphics.h"
#include "list.h"
#include "Sound.h"
#include "gelements.h"
#include "portrayal.h"
#include "display.h"
#include "gapp.h"

//using namespace std;

class game:public gapp2
{
	protected:
		
		int top,//������� �������� �����
			left,//����� �������� �����
			n,r,t,//���������� ��������� (��� �������)
			count_game,//������� ������� ����
			regularity,//������������ �������� ���������
			speed_obj,//�������� �������� ��������
			point,//���������� �����
			trajectory,//���������� ��������
			levl,levl_1,levl_2,levl_3,//������ ����
			process,//������� ����
			death_count;//���������� ������� ������������

			bool SpacePressed,//��������� ��������� ������� (������� "����")
				EscapePressed;//��������� ��������� �������
		
		enum{MENU,NEW_GAME,CONTINUE,RESULTS,MANUAL,EXIT,DEATH_PLAYER};//ID ��������� ����
		
			
		listptr<animation*> at;//������ ����������� ��������
		listptr<bots*> bo;//������ �����
		listptr<bang*> bt;//������ �������
		listptr<life*> li;//������ �����
		listptr<stars*> star;//������ �����
		player*pl;//��������� �� ������ ������
		death_player*pld;//��������� �� ������ ������������ 
		display*di;//��������� �� ������ �������
		menu* me;//��������� �� ������ ����
		result*re;//��������� �� ���������
		options*op;//��������� �� �����
		sound_music*sm;//��������� �� ������ � ����
		sound_shot*so;//��������� �� ���� ��������
		sound_bang*sb;//��������� �� ���� ������
		sound_life*sl;//��������� �� ���� �����
		sound_game_over*gm;//��������� �� game over
		sound_music_game*smg;//��������� �� ������� �����
	public:
		
		game():
		gapp2(1024,700,"Dangerous space")
		{
			srand((unsigned)time(NULL));
			
			levl=1;//����������� ������ ���� �� �������
			levl_1=10;//������ �������
			levl_2=20;//������ �������
			levl_3=30;//������ �������
			process=MENU;//��������� ������� ����

			//////////////////////��������� ��������///////////////////////////////////
			di=new display();//����������� �������
			me=new menu();//����������� ����
			pl=new player(SgLoadImage("img/player/strip_player.png"),left,top);//����������� ������
			pld=new death_player();//����������� ������ ������
			re=new result();//���������
			op=new options();//�����
			////////////////////////////�������� �����/////////////////////////////////
			for(int i=0;i<15;i++)
			star.add_tail(new stars(SgLoadImage("img/display/sparkle.png"),rand()%SgGetWidth(),rand()%SgGetHeight()));	
			////////////////////////////����� � ������/////////////////////////////////
			so=new sound_shot(SgLoadSound("sound/Laser_Short.mp3"));//���� ��������
			sb=new sound_bang(SgLoadSound("sound/BTTLEXP1.wav"));//���� ������
			sl=new sound_life(SgLoadSound("sound/new_life.wav"));//���� �����
			sm=new sound_music(SgLoadSound("sound/Hardmash-(muzofon.com).mp3"));//���� ����
			gm=new sound_game_over(SgLoadSound("sound/Game Over.mp3"));//���� Game Over
			smg=new sound_music_game(SgLoadSound("sound/NASA-Zvuki-Kosmosa.mp3"));//���� Game 
		}
		///////////////��������//////////////////////////////
		void Process();//����������� �������
		void ProcessMenu();//������� ����
		void ProcessNewGame();//������� ����
		void ProcessContinueGame();//������� ����������� ����
		void ProcessResultsGame();//������� ���������� ���� 
		void ProcessManualGame();//������� ���������� ���� 
		void ProcessExit();//������� ������ �� ����
		/////////////////����������� ��������///////////////////////
		void ProcessDeathPlayer();//������� ������ ����� �� �����
		/////////////������ ���������////////////////////////
		void StartGame();//����� �������� ��� ����� ����
		void DeathPlayer();//������ ������������
		void ClearDrawObj();//����� �������� ������ �� ��������
		void DrawSpaceObj();//��������� ����������� ��������
		void DrawBots();//��������� �����
		void DrawBang();//��������� ������ ��� ��������� � �����
		void DrawLife();//��������� �������� �����
		void DrawDisplay();//��������� �������
		void DrawStars();//��������� ������� �����
		void ReversStars();//������ ����� ��� ����
		void CrossBorder();//����� �������� ������������ (�����������) ����������� �������� ��� ������������
		void CrossBorderShot();//����� �������� ������������ (�����������) ����������� ��������  �� �������� ������������
		void CrossBorderBots();//����� �������� ������������ (�����������) ���� � �������������
		void CrossBorderShotBots();//����� �������� ������������ (�����������) ������������ �� �������� ����
		void Input();//����� ����� ������ � ����������
		void HitCross();//����� ���������� � ���� �������� ���� ������������ �� ������� ����
		void Display();//����� ����������� �������� �������� ����
		void Move();//����� �������� ��������
		void MoveSpaceObj();//����� �������� ����������� ��������
		void MoveBots();//����� �������� �����
		void MoveBang();//����� �������� ������
		void MoveLife();//����� �������� �����
		void MoveStars();//����� �������� �����
		void MakeBang1(int left,int top);//����� �������� ������ (��������� � ������)
		void MakeBang2(int left,int top);//����� �������� ������ (��� ������ �������)
		void MakeBang3(int left,int top);//����� �������� ������ (��������� � ������������)
		void MakeLife(int left,int top);//����� �������� �����
		void SetSpaceObj();//����� ���������� �������� �������� ���� (������ ����)
		~game();
};

///////////////////////�������� �������////////////////////////////////////////////////
		
		void game::Process()
		{
			
			switch(process)
			{
				case MENU:ProcessMenu();break;
				case NEW_GAME:ProcessNewGame();break;
				case CONTINUE:ProcessContinueGame();break;
				case RESULTS:ProcessResultsGame();break;
				case MANUAL:ProcessManualGame();break;
				case EXIT:ProcessExit();break;
				case DEATH_PLAYER:ProcessDeathPlayer();break;
			}
		}
		
////////////////////��������///////////////////////////////////////////////////////////
		
		void game::ProcessMenu()
		{
			me->Draw();//��������� ����
			sm->PlaySoundW();//���� ����

			switch(me->GetIdButton())//������������ ������� � ������������ ������� ������
			{
				case MENU:
							smg->Pause();process=MENU;
					break;

				case NEW_GAME:
							sm->Pause();smg->PlaySoundW();StartGame();process=NEW_GAME;//��������� ������ ����,��������� ���� � ������ �������� ��������
					break;

				case CONTINUE:
								if(count_game>0 &&pl->LifeObject()){sm->Pause();smg->PlaySoundW();process=CONTINUE;}//���� ���� ���� ��� � ������������ �� ����
								else break;
					break;

				case RESULTS:
							process=RESULTS;
					break;

				case MANUAL:
							process=MANUAL;
					break;
				
				case EXIT:
							process=EXIT;			
			}
			me->RezetIdButton();//���������� ��������� �� ��������� ������� ������
		}

		void game::ProcessNewGame()
		{						
			Input();
			Move();
			HitCross();	
			Display();
		}

		void game::ProcessContinueGame()
		{
			Input();
			Move();
			HitCross();	
			Display();
		}

		void game::ProcessResultsGame()
		{
			re->Draw();
			if(SgIsKeyDown(VK_ESCAPE))//�������� �� ������� ������� "ESCAPE" (� ������� ������ ��� ��� ������ � ����)
			{
				process=MENU;//������������ �������� � ��������� �� ����
			}
			else EscapePressed=false;
		}

		void game::ProcessManualGame()
		{
			op->Draw();
			if(SgIsKeyDown(VK_ESCAPE))//�������� �� ������� ������� "ESCAPE" (� ������� ������ ��� ��� ������ � ����)
			{
				process=MENU;//������������ �������� � ��������� �� ����
			}
			else EscapePressed=false;
		}

		void game::ProcessExit()
		{
			exit_=true;
		}

		void game::ProcessDeathPlayer()
		{
			smg->Pause();//����� ��� ������ (��������)
			pld->SetPoint(point);
			pld->Draw();
			gm->PlaySoundW();//���� game over
				
			if(SgIsKeyDown(VK_ESCAPE))//�������� �� ������� ������� "ESCAPE" (� ������� ������ ��� ��� ������ � ����)
			{
				process=MENU;//������������ �������� � ��������� �� ����
			}
			else EscapePressed=false;
		}

////////////////////������ ���������///////////////////////////////////////////////////

		void game::StartGame()
		{
			///////////��������� ���������� �� ���������/////////////////
			left=450;//��������� ���������� ����� �����
			top=530;//��������� ����������������� �����
			SpacePressed=EscapePressed=false;//��������� ��������� ������� � ������� (�������� ��������� ��������)
			count_game=0;//������� ������� ���� 
			point=0;//���������� �����
			regularity=200;//������������ �������� ���������
			speed_obj=1;//��������� �������� �������� ��������
			trajectory=0;//��������� ��������� ��������
			levl=1;//����������� ������ ���� �� �������
			pl->SetHeath(3);//���������� ����� ������������ �� ���������
			pl->SetPozition(450,530);
			di->SetDrawLifeIndicator(3);//���������� ����� ������������ �� ��������� (�������)
			ClearDrawObj();//�������� ������ �� ��������
			/////////////////////////////////////////////////////////////
		}

		void game::ClearDrawObj()
		{
			at.clear();
			bo.clear();
			bt.clear();
			li.clear();
		}

		void game::Input()//����� ������ ������� �����(�������� �������)
		{
			
			if(SgIsKeyDown(VK_LEFT))//�������� �� ������� ������� "�����"
			{
				if(pl->GetLeft()>=-20)//����������� ������ �� ������� �������� ���� �����
				{	
					left-=15;
					pl->SetPozition(left,top);
				}
			}
			if(SgIsKeyDown(VK_RIGHT))//�������� �� ������� ������� "������"
			{
				if(pl->GetStep()+pl->GetLeft()<SgGetWidth()+20)//����������� ������ �� ������� �������� ���� ������
				{	
					left+=15;
					pl->SetPozition(left,top);
				}
			}
			if(SgIsKeyDown(VK_UP))//�������� �� ������� ������� "�����"
			{
				if(pl->GetTop()>=450)//����������� ������ �� ������� �������� ���� ������
				{
					top-=15;
					pl->SetPozition(left,top);
				}
			}
			if(SgIsKeyDown(VK_DOWN))//�������� �� ������� ������� "����"
			{
				if(pl->GetBattom()<=SgGetHeight())//����������� ������ �� ������� �������� ���� �����
				{
					top+=15;
					pl->SetPozition(left,top);
				}
			}
			if(SgIsKeyDown(VK_ESCAPE))//�������� �� ������� ������� "ESCAPE" (� ������� ������ ��� ��� ������ � ����)
			{
				process=MENU;//������������ �������� � ��������� �� ����
			}
			else EscapePressed=false;

			if(SgIsKeyDown(VK_SPACE))//�������� �� ������� ������� "space" (� ������� ������ ��� ������ ��� ��������)
			{
				so->PlaySoundW();//���� ��������
				if(!SpacePressed)
				{
					pl->MakeShot();
					SpacePressed=true;
				}
			}
			else SpacePressed=false;
		}

		void game::Move()
		{
			MoveStars();//�������� �����
			MoveSpaceObj();//�������� ����������� ��������
			MoveBots();//�������� �����
			MoveBang();//�������� ������
			MoveLife();//�������� �����
		}

		void game::HitCross()//����� ���������� � ���� �������� ���� ������������ �� ������� ����
		{
			CrossBorder();//�������� �� ������������ ������������ � ������������ ���������
			CrossBorderShot();//�������� �� ������������ ������� � ������������ ���������
			CrossBorderBots();//�������� �� ������������ ������������ � �����
			CrossBorderShotBots();//�������� �� ������������ ������� ���� � �������������
		}

		void game::Display()//����� ����������� �������� �������� ����
		{
			DrawStars();//��������� ������� �����
			pl->Draw();//��������� ������������
			SetSpaceObj();//���������� �������� ���� ���������
			DrawSpaceObj();//��������� ����������� ��������
			DrawBots();//��������� �����
			DrawBang();//��������� �������
			DrawLife();//��������� �����
			DrawDisplay();//��������� �������
		}

		void game::DrawSpaceObj()
		{
			n=0;
			elem<animation*>*ptr=at.get_head();

			while(ptr)
			{
				if(!ptr->data->LifeObject() || ptr->data->GetTop()>SgGetHeight ())//���� ������� ����, ������� ��� �� ������ �������� ��� ���� ����� �� ������� �������� ����
				{at.deleting(n);break;}
					
				else //���� ���, �� ������
					ptr->data->Draw();
				
				ptr=ptr->next;	
				n++;
			}
		}

		void game::DrawBots()
		{
			n=0;
			elem<bots*>*ptr=bo.get_head();

			while(ptr)
			{
				if(!ptr->data->LifeObject() || ptr->data->GetTop()>SgGetHeight ())//���� ������� ����, ������� ��� �� ������ �������� ��� ���� ����� �� ������� �������� ����
				{bo.deleting(n);break;}
					
				else //���� ���, �� ������
					ptr->data->Draw();
				
				ptr=ptr->next;	
				n++;
			}
		}

		void game::DrawBang()
		{
			n=0;
			elem<bang*>*ptr=bt.get_head();

			while(ptr)
			{
				if(ptr->data->StopDraw())//�������� �� ����� ��������, ���� 
				{bt.deleting(n);break;}//�������� ������ �� ������	

				else ptr->data->Draw();

				ptr=ptr->next;
				n++;
			}	
		}

		void game::DrawLife()
		{
			n=0;
			elem<life*>*ptr=li.get_head();

			while(ptr)
			{
				if(ptr->data->GetTop()>=SgGetHeight())//�������� �� ����� �� �������� ����
				{li.deleting(n);break;}//�������� ����� �� ������	

				else ptr->data->Draw();

				ptr=ptr->next;
				n++;
			}	
		}

		void game::DrawDisplay()
		{
			di->SetPoint(point);//���������� �����
			di->SetLevl(levl);//���������� ������
			di->Draw();//��������� �������
		}

		void game::DrawStars()
		{
			elem<stars*>*pt=star.get_head();

				while(pt)
				{
					pt->data->Draw();
					pt=pt->next;
				}	
			ReversStars();//������ �����
		}

		void game::ReversStars()
		{
			elem<stars*>*pt=star.get_head();
			while(pt)
				{
					if(pt->data->GetTop()>SgGetHeight())
					{pt->data->SetPozition(rand()%SgGetWidth(),rand()%10-50);}
					pt=pt->next;
				}	
		}

		void game::CrossBorder()
		{
			n=0;
			elem<animation*>*ptr=at.get_head();
			elem<life*>*ptr2=li.get_head();
			
			while(ptr)//��� �������� 
			{
				if(pl->Cross(ptr->data))//���� � ������������� ���������� ������
				{
					pl->ReduceHeath();//�������� ���� �����
						
					if(pl->LifeObject())//���� ������������ ��� - ��������� �����
					{
						MakeBang1(pl->GetLeft_M()+30,pl->GetBattom_M());//��������� �����
						at.deleting(n);//�������� ������� �� ������	
						di->DelDrawIndicator();//�������� ����� �� �������
						break;
					}

					else//���� ������ ������������ �� ����� ������ ������������
					{
						MakeBang2(pl->GetLeft(),pl->GetTop());
						process=DEATH_PLAYER;
					}
				}

				ptr=ptr->next;n++;
			}

			while(ptr2)//��� �����
			{
				if(pl->Cross(ptr2->data))//���� � ������������� ���������� ������
				{
					li.dell_head();//�������� ������� �� ������	
					sl->PlaySoundW();//�������� ����� �����

					if(pl->GetHeath()<5)//���� life < 6 , ���������
					{
						pl->AddHeath();//���������� �����
						di->AddLifeIndicator();//���������� ����� �� �������
					}
					
					//cout<<pl->GetHeath()<<endl;	
					break;
				}

				ptr2=ptr2->next;
			}
		}

		void game::CrossBorderShot()
		{
			
			elem<animation*>*ptr=at.get_head();
			elem<bots*>*ptr2=bo.get_head();
			
			while(ptr)//��� ����������� ��������
			{
				if(pl->CrossShot(ptr->data))
				{
					ptr->data->ReduceHeath();//�������� ���� �����
					

					if(ptr->data->LifeObject())//���� ������ ��� - ��������� �����
					MakeBang1(ptr->data->GetRight_M()-50,ptr->data->GetTop_M()+10);//��������� �����

					else//���� ������ ������� �� ����� ������
					{
						MakeBang2(ptr->data->GetRight_M()-60,ptr->data->GetTop_M());
						point+=50;
						MakeLife(ptr->data->GetRight_M()-60,ptr->data->GetTop_M());//������� �������� ����� ��� �������
					}
				}
				
				ptr=ptr->next;
			}
			while(ptr2)//��� �����
			{
				if(pl->CrossShot(ptr2->data))
				{
					ptr2->data->ReduceHeath();//�������� ���� �����

					if(ptr2->data->LifeObject())//���� ������ ��� - ��������� �����
					MakeBang1(ptr2->data->GetRight_M()-50,ptr2->data->GetTop_M()+35);//��������� �����

					else//���� ������ ������� �� ����� ������
					{
						MakeBang2(ptr2->data->GetRight_M()-55,ptr2->data->GetTop_M()+10);
						point+=100;
						MakeLife(ptr2->data->GetRight_M()-60,ptr2->data->GetTop_M());//������� �������� ����� ��� �������
					}
				}
				
				ptr2=ptr2->next;
			}

		}

		void game::CrossBorderBots()
		{
			n=0;
			elem<bots*>*ptr=bo.get_head();
			
			while(ptr)
			{
				if(pl->Cross(ptr->data))//���� � ������������� ���������� ���
				{
					pl->ReduceHeath();//�������� ���� ����� � ������������
						
					if(pl->LifeObject())//���� ������������ ��� - ��������� ����� ����
					{
						MakeBang1(pl->GetLeft(),pl->GetTop());//��������� �����
						bo.deleting(n);//�������� ������� �� ������	
						di->DelDrawIndicator();//�������� ����� �� �������
						break;
					}

					else//���� ������ ������������ �� ����� ������ ������������
					{
						MakeBang2(pl->GetLeft(),pl->GetTop());
						process=DEATH_PLAYER;
					}
				}

				ptr=ptr->next;n++;
			}
		}

		void game::CrossBorderShotBots()
		{
			elem<bots*>*ptr=bo.get_head();
			
			while(ptr)
			{
				if(ptr->data->CrossShot(pl) )
				{
					pl->ReduceHeath();//�������� ���� ����� � ������������

					if(pl->LifeObject())//���� ������������ ��� - ��������� �����
					{
						MakeBang3(pl->GetLeft(),pl->GetTop());//��������� �����
						di->DelDrawIndicator();//�������� ����� �� �������
						break;
					}

					else//���� ������ ������������ �� ����� ������
					{
						MakeBang2(pl->GetLeft(),pl->GetTop());
						process=DEATH_PLAYER;
					}
				}
				
				ptr=ptr->next;
			}

		}

		void game::MakeBang1(int left,int top)//�������� ������
		{
			bt.add_tail(new bang(SgLoadImage("img/bang/gun_blast3.PNG"),left,top));
			sb->PlaySoundW();//�������� ����� ������
		}

		void game::MakeBang2(int left,int top)
		{
			bt.add_tail(new bang(SgLoadImage("img/bang/Exp_type_C2.PNG"),left,top));//A2
			sb->PlaySoundW();//�������� ����� ������
		}

		void game::MakeBang3(int left,int top)
		{
			bt.add_tail(new bang(SgLoadImage("img/bang/gun_blast2.PNG"),left,top));//A2
			sb->PlaySoundW();//�������� ����� ������
		}
		
		void game::MakeLife(int left,int top)
		{
			n=rand()%10;//������� ��������� ����� � �������
			
			if(n==0)
			{
				li.add_tail(new life(SgLoadImage("img/spaceobjects/strip_spikey.PNG"),left,top));
			}
		}

		void game::MoveSpaceObj()
		{
			elem<animation*>*ptr=at.get_head();
			
			while(ptr)
			{
				ptr->data->Move(trajectory,speed_obj);				
				ptr=ptr->next;
			}
		}

		void game::MoveBots()
		{
			elem<bots*>*ptr=bo.get_head();
			
			while(ptr)
			{
				ptr->data->Move(0,speed_obj);				
				ptr=ptr->next;
			}
		}

		void game::MoveBang()
		{
			elem<bang*>*ptr=bt.get_head();

			while(ptr)
			{
				ptr->data->Move(0,1);				
				ptr=ptr->next;
			}
		}

		void game::MoveLife()
		{
			elem<life*>*ptr=li.get_head();

			while(ptr)
			{
				ptr->data->Move(0,1);				
				ptr=ptr->next;
			}
		}

		void game::MoveStars()
		{
			elem<stars*>*pt=star.get_head();

				while(pt)
				{
					pt->data->Move(0,speed_obj+1);
					pt=pt->next;
				}	
		}
		
		void game::SetSpaceObj()
		{
			//cout<<count_game<<endl;
			r=-1;//���������� �������
		
			n=rand()%regularity;//������������ �������� ��������
			
			if(n==0)
			{
				if(count_game<=levl_1)//******************************** 0 - 3 (Level (1))
				{
					r=rand()%4;
				}

				if(count_game>levl_1 && count_game<=levl_2)	//********** 4 - 5 (Level (2))
				{
					r=rand()%2+4;speed_obj=2;regularity=150;levl=2;
					
					t=rand()%10;//��� ��������� ���������� �������� ��������
					if(t==0)trajectory=rand()%3-1;
				}

				if(count_game>levl_2 && count_game<=levl_3) //********** 6 - 8 (Level (3))
				{
					 r=rand()%3+6; speed_obj=3;regularity=100;levl=3;
				}

				if(count_game>levl_3) //******************************** 8 (Level (4))
				{
					r=rand()%9; speed_obj=4;regularity=80;levl=4;

					t=rand()%10;//��� ��������� ���������� �������� ��������
					if(t==0)trajectory=rand()%3-1;
				}

				if(count_game>levl_3+levl_3) //************************* 8 (Level (5))
				{
					r=rand()%9; speed_obj=4;regularity=50;levl=5;

					t=rand()%10;//��� ��������� ���������� �������� ��������
					if(t==0)trajectory=rand()%3-1;
				}

				if(count_game>100) //*********************************** 8 (Level (6))
				{
					r=rand()%9;regularity=20;levl=6;

					t=rand()%10;//��� ��������� ���������� �������� ��������
					if(t==0)trajectory=rand()%3-1;
				}

				switch(r)
				{
					case 0:
							at.add_tail(new asteroid(SgLoadImage("img/asteroid/strip_rock_type_A.PNG"),rand()%SgGetWidth ()-20,-20));break;
					case 1:
							at.add_tail(new asteroid(SgLoadImage("img/asteroid/strip_rock_type_B.PNG"),rand()%SgGetWidth ()-20,-20));break;
					case 2:
							at.add_tail(new asteroid(SgLoadImage("img/asteroid/strip_rock_type_C.PNG"),rand()%SgGetWidth ()-20,-20));break;
					case 3:
							at.add_tail(new asteroid(SgLoadImage("img/asteroid/strip_rock_type_D.PNG"),rand()%SgGetWidth ()-20,-20));break;
					case 4:
							at.add_tail(new spaceobjects(SgLoadImage("img/spaceobjects/strip_saucer.PNG"),rand()%SgGetWidth ()-20,-20));break;
					case 5:
							at.add_tail(new spaceobjects(SgLoadImage("img/spaceobjects/strip_saucer_blades.PNG"),rand()%SgGetWidth ()-20,-20));break;
					case 6:
							bo.add_tail(new bots(SgLoadImage("img/bots/strip_fighter.PNG"),rand()%SgGetWidth ()-20,-20));break;
					case 7:
							bo.add_tail(new bots(SgLoadImage("img/bots/strip_scythe.PNG"),rand()%SgGetWidth ()-20,-20));break;
					case 8:
							bo.add_tail(new bots(SgLoadImage("img/bots/strip_slicer.PNG"),rand()%SgGetWidth ()-20,-20));break;
				}
				count_game++;//������� ������� ����
			}
		}

		game::~game()
		{
			delete pl;//��������� �� ������ ������
			delete pld;//��������� �� ������ ������������ 
			delete di;//��������� �� ������ �������
			delete me;//��������� �� ������ ����
			delete re;//��������� �� ���������
			delete op;//�����
			delete sm;//��������� �� ������ � ����
			delete so;//��������� �� ���� ��������
			delete sb;//��������� �� ����
			delete sl;//��������� �� ����
			delete gm;//��������� �� ����
			delete smg;//��������� �� ����
		}


void main()
{
	game app;
	app.WorkProcess();
}
