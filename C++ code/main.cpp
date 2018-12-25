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
		
		int top,//верхнее значение точки
			left,//левое значение точки
			n,r,t,//количество элементов (для рандома)
			count_game,//счетчик события игры
			regularity,//регулярность загрузки окбъектов
			speed_obj,//скорость движения объектов
			point,//количество очков
			trajectory,//траектория объектов
			levl,levl_1,levl_2,levl_3,//уровни игры
			process,//процесс игры
			death_count;//количество смертей пользователя

			bool SpacePressed,//первичное положение пробела (клавиша "огня")
				EscapePressed;//первичное положение эскейпа
		
		enum{MENU,NEW_GAME,CONTINUE,RESULTS,MANUAL,EXIT,DEATH_PLAYER};//ID процессов игры
		
			
		listptr<animation*> at;//список космических объектов
		listptr<bots*> bo;//список ботов
		listptr<bang*> bt;//список взрывов
		listptr<life*> li;//список жизни
		listptr<stars*> star;//список звезд
		player*pl;//указатель на объект игрока
		death_player*pld;//указатель на смерть пользователя 
		display*di;//указатель на объект дисплея
		menu* me;//указатель на объект меню
		result*re;//указатель на результат
		options*op;//указатель на опции
		sound_music*sm;//указатель на музыку в меню
		sound_shot*so;//указатель на звук выстрела
		sound_bang*sb;//указатель на звук взрыва
		sound_life*sl;//указатель на звук жизни
		sound_game_over*gm;//указатель на game over
		sound_music_game*smg;//указатель на игровую музку
	public:
		
		game():
		gapp2(1024,700,"Dangerous space")
		{
			srand((unsigned)time(NULL));
			
			levl=1;//отображение уровня игры на дисплее
			levl_1=10;//первый уровень
			levl_2=20;//второй уровень
			levl_3=30;//третий уровень
			process=MENU;//начальный процесс игры

			//////////////////////отрисовка объектов///////////////////////////////////
			di=new display();//отображение дисплэя
			me=new menu();//отображение меню
			pl=new player(SgLoadImage("img/player/strip_player.png"),left,top);//отображение игрока
			pld=new death_player();//отображение смерти плеера
			re=new result();//результат
			op=new options();//опции
			////////////////////////////загрузка звезд/////////////////////////////////
			for(int i=0;i<15;i++)
			star.add_tail(new stars(SgLoadImage("img/display/sparkle.png"),rand()%SgGetWidth(),rand()%SgGetHeight()));	
			////////////////////////////звуки и музыка/////////////////////////////////
			so=new sound_shot(SgLoadSound("sound/Laser_Short.mp3"));//звук выстрела
			sb=new sound_bang(SgLoadSound("sound/BTTLEXP1.wav"));//звук взрыва
			sl=new sound_life(SgLoadSound("sound/new_life.wav"));//звук жизни
			sm=new sound_music(SgLoadSound("sound/Hardmash-(muzofon.com).mp3"));//звук меню
			gm=new sound_game_over(SgLoadSound("sound/Game Over.mp3"));//звук Game Over
			smg=new sound_music_game(SgLoadSound("sound/NASA-Zvuki-Kosmosa.mp3"));//звук Game 
		}
		///////////////процессы//////////////////////////////
		void Process();//выполняемый процесс
		void ProcessMenu();//процесс меню
		void ProcessNewGame();//процесс игры
		void ProcessContinueGame();//процесс продолжения игры
		void ProcessResultsGame();//процесс результаты игры 
		void ProcessManualGame();//процесс инструкции игры 
		void ProcessExit();//процесс выхода из игры
		/////////////////специальные процессы///////////////////////
		void ProcessDeathPlayer();//процесс смерти вывод на экран
		/////////////методы процессов////////////////////////
		void StartGame();//метод обнуляет для новой игры
		void DeathPlayer();//смерть пользователя
		void ClearDrawObj();//метод отчистки экрана от объектов
		void DrawSpaceObj();//отрисовка космических объектов
		void DrawBots();//отрисовка ботов
		void DrawBang();//отрисовка взрыва при попадании в обект
		void DrawLife();//отрисовка движения жизни
		void DrawDisplay();//отрисовка дисплея
		void DrawStars();//отрисовка фоновых звезд
		void ReversStars();//реверс звезд для фона
		void CrossBorder();//метод проверки столкновения (пересечения) космических объектов для пользователя
		void CrossBorderShot();//метод проверки столкновения (пересечения) космических объектов  со снарядом пользователя
		void CrossBorderBots();//метод проверки столкновения (пересечения) бота с пользователем
		void CrossBorderShotBots();//метод проверки столкновения (пересечения) пользователя со снарядом бота
		void Input();//метод ввода данных с клавиатуры
		void HitCross();//метод включающий в себя проверку всех столкновений на игровом поле
		void Display();//метод отображение объектов игрового поля
		void Move();//метод движения объектов
		void MoveSpaceObj();//метод движения космических объектов
		void MoveBots();//метод движения ботов
		void MoveBang();//метод движения взрыва
		void MoveLife();//метод движения жизни
		void MoveStars();//метод движения звезд
		void MakeBang1(int left,int top);//метод загрузки взрыва (попадания в объект)
		void MakeBang2(int left,int top);//метод загрузки взрыва (при смерти объекта)
		void MakeBang3(int left,int top);//метод загрузки взрыва (попадания в пользователя)
		void MakeLife(int left,int top);//метод загрузки жизни
		void SetSpaceObj();//метод заполнения объектов игрового поля (логика игры)
		~game();
};

///////////////////////основной процесс////////////////////////////////////////////////
		
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
		
////////////////////процессы///////////////////////////////////////////////////////////
		
		void game::ProcessMenu()
		{
			me->Draw();//отрисовка меню
			sm->PlaySoundW();//звук меню

			switch(me->GetIdButton())//переключение режимов в соответствие нажатой кнопки
			{
				case MENU:
							smg->Pause();process=MENU;
					break;

				case NEW_GAME:
							sm->Pause();smg->PlaySoundW();StartGame();process=NEW_GAME;//отключаем музыку меню,обнуление игры и запуск игрового процесса
					break;

				case CONTINUE:
								if(count_game>0 &&pl->LifeObject()){sm->Pause();smg->PlaySoundW();process=CONTINUE;}//если игра есть уже и пользователь не мерт
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
			me->RezetIdButton();//возвращает положение по умолчанию нажатой кнопки
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
			if(SgIsKeyDown(VK_ESCAPE))//проверка на нажатие стрелки "ESCAPE" (в игровом случае это для выхода в меню)
			{
				process=MENU;//переключение процесса с игровойго на меню
			}
			else EscapePressed=false;
		}

		void game::ProcessManualGame()
		{
			op->Draw();
			if(SgIsKeyDown(VK_ESCAPE))//проверка на нажатие стрелки "ESCAPE" (в игровом случае это для выхода в меню)
			{
				process=MENU;//переключение процесса с игровойго на меню
			}
			else EscapePressed=false;
		}

		void game::ProcessExit()
		{
			exit_=true;
		}

		void game::ProcessDeathPlayer()
		{
			smg->Pause();//пауза при смерти (звуковая)
			pld->SetPoint(point);
			pld->Draw();
			gm->PlaySoundW();//звук game over
				
			if(SgIsKeyDown(VK_ESCAPE))//проверка на нажатие стрелки "ESCAPE" (в игровом случае это для выхода в меню)
			{
				process=MENU;//переключение процесса с игровойго на меню
			}
			else EscapePressed=false;
		}

////////////////////методы процессов///////////////////////////////////////////////////

		void game::StartGame()
		{
			///////////обнуление параметров по умолчанию/////////////////
			left=450;//первичные координаты левой точки
			top=530;//первичные координатыверхней точки
			SpacePressed=EscapePressed=false;//первичное положение пробела и эскейпа (загрузка стартовой картинки)
			count_game=0;//счетчик события игры 
			point=0;//количество очков
			regularity=200;//регулярность загрузки окбъектов
			speed_obj=1;//первичная скорость движения объектов
			trajectory=0;//первичная траетория объектов
			levl=1;//отображение уровня игры на дисплее
			pl->SetHeath(3);//количество жизни пользователя по умолчанию
			pl->SetPozition(450,530);
			di->SetDrawLifeIndicator(3);//количество жизни пользователя по умолчанию (дисплей)
			ClearDrawObj();//отчистка экрана от объектов
			/////////////////////////////////////////////////////////////
		}

		void game::ClearDrawObj()
		{
			at.clear();
			bo.clear();
			bt.clear();
			li.clear();
		}

		void game::Input()//метод вызова нажатия клавы(движение каробля)
		{
			
			if(SgIsKeyDown(VK_LEFT))//проверка на нажатие стрелки "влево"
			{
				if(pl->GetLeft()>=-20)//ограничение выхода за пределы игрового поля слева
				{	
					left-=15;
					pl->SetPozition(left,top);
				}
			}
			if(SgIsKeyDown(VK_RIGHT))//проверка на нажатие стрелки "вправо"
			{
				if(pl->GetStep()+pl->GetLeft()<SgGetWidth()+20)//ограничение выхода за пределы игрового поля справо
				{	
					left+=15;
					pl->SetPozition(left,top);
				}
			}
			if(SgIsKeyDown(VK_UP))//проверка на нажатие стрелки "вверх"
			{
				if(pl->GetTop()>=450)//ограничение выхода за пределы игрового поля сверху
				{
					top-=15;
					pl->SetPozition(left,top);
				}
			}
			if(SgIsKeyDown(VK_DOWN))//проверка на нажатие стрелки "вниз"
			{
				if(pl->GetBattom()<=SgGetHeight())//ограничение выхода за пределы игрового поля снизу
				{
					top+=15;
					pl->SetPozition(left,top);
				}
			}
			if(SgIsKeyDown(VK_ESCAPE))//проверка на нажатие стрелки "ESCAPE" (в игровом случае это для выхода в меню)
			{
				process=MENU;//переключение процесса с игровойго на меню
			}
			else EscapePressed=false;

			if(SgIsKeyDown(VK_SPACE))//проверка на нажатие стрелки "space" (в игровом случае это кнопка для стрельбы)
			{
				so->PlaySoundW();//звук выстрела
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
			MoveStars();//движение звезд
			MoveSpaceObj();//движение космических объектов
			MoveBots();//движение ботов
			MoveBang();//движение взрыва
			MoveLife();//движение жизни
		}

		void game::HitCross()//метод включающий в себя проверку всех столкновений на игровом поле
		{
			CrossBorder();//проверка на столкновения пользователя с космическими объектами
			CrossBorderShot();//проверка на столкновение снаряда с космическими объектами
			CrossBorderBots();//проверка на столкновения пользователя с ботом
			CrossBorderShotBots();//проверка на столкновение снаряда бота с пользователем
		}

		void game::Display()//метод отображение объектов игрового поля
		{
			DrawStars();//отрисовка фоновых звезд
			pl->Draw();//отрисовка пользователя
			SetSpaceObj();//заполнения игрового поля объектами
			DrawSpaceObj();//отрисовка космических объектов
			DrawBots();//отрисовка ботов
			DrawBang();//отрисовка взрывов
			DrawLife();//отрисовка жизни
			DrawDisplay();//отрисовка дисплея
		}

		void game::DrawSpaceObj()
		{
			n=0;
			elem<animation*>*ptr=at.get_head();

			while(ptr)
			{
				if(!ptr->data->LifeObject() || ptr->data->GetTop()>SgGetHeight ())//если объекта умер, удаляем его из списка объектов или если вышел за границы игрового поля
				{at.deleting(n);break;}
					
				else //если нет, то рисуем
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
				if(!ptr->data->LifeObject() || ptr->data->GetTop()>SgGetHeight ())//если объекта умер, удаляем его из списка объектов или если вышел за границы игрового поля
				{bo.deleting(n);break;}
					
				else //если нет, то рисуем
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
				if(ptr->data->StopDraw())//проверка на конец анимации, усли 
				{bt.deleting(n);break;}//удаление взрыва из списка	

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
				if(ptr->data->GetTop()>=SgGetHeight())//проверка на выход из игрового поля
				{li.deleting(n);break;}//удаление жизни из списка	

				else ptr->data->Draw();

				ptr=ptr->next;
				n++;
			}	
		}

		void game::DrawDisplay()
		{
			di->SetPoint(point);//добавление очков
			di->SetLevl(levl);//добавление уровня
			di->Draw();//отрисовка дисплея
		}

		void game::DrawStars()
		{
			elem<stars*>*pt=star.get_head();

				while(pt)
				{
					pt->data->Draw();
					pt=pt->next;
				}	
			ReversStars();//реверс звезд
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
			
			while(ptr)//для объектов 
			{
				if(pl->Cross(ptr->data))//если с пользователем столкнулся объект
				{
					pl->ReduceHeath();//отнимаем очки жизни
						
					if(pl->LifeObject())//если пользователь жив - загружаем взрыв
					{
						MakeBang1(pl->GetLeft_M()+30,pl->GetBattom_M());//загружаем взрыв
						at.deleting(n);//удаление объекта из списка	
						di->DelDrawIndicator();//удаление жизни из дисплея
						break;
					}

					else//если смерть пользователя то взрыв смерти пользователя
					{
						MakeBang2(pl->GetLeft(),pl->GetTop());
						process=DEATH_PLAYER;
					}
				}

				ptr=ptr->next;n++;
			}

			while(ptr2)//для жизни
			{
				if(pl->Cross(ptr2->data))//если с пользователем столкнулся объект
				{
					li.dell_head();//удаление объекта из списка	
					sl->PlaySoundW();//загрузка звука жизни

					if(pl->GetHeath()<5)//если life < 6 , добавляем
					{
						pl->AddHeath();//добавление жизни
						di->AddLifeIndicator();//добавление жизни на дисплее
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
			
			while(ptr)//для космических объектов
			{
				if(pl->CrossShot(ptr->data))
				{
					ptr->data->ReduceHeath();//отнимаем очки жизни
					

					if(ptr->data->LifeObject())//если объект жив - загружаем взрыв
					MakeBang1(ptr->data->GetRight_M()-50,ptr->data->GetTop_M()+10);//загружаем взрыв

					else//если смерть объекта то взрыв смерти
					{
						MakeBang2(ptr->data->GetRight_M()-60,ptr->data->GetTop_M());
						point+=50;
						MakeLife(ptr->data->GetRight_M()-60,ptr->data->GetTop_M());//вариант создание жизни для коробля
					}
				}
				
				ptr=ptr->next;
			}
			while(ptr2)//для ботов
			{
				if(pl->CrossShot(ptr2->data))
				{
					ptr2->data->ReduceHeath();//отнимаем очки жизни

					if(ptr2->data->LifeObject())//если объект жив - загружаем взрыв
					MakeBang1(ptr2->data->GetRight_M()-50,ptr2->data->GetTop_M()+35);//загружаем взрыв

					else//если смерть объекта то взрыв смерти
					{
						MakeBang2(ptr2->data->GetRight_M()-55,ptr2->data->GetTop_M()+10);
						point+=100;
						MakeLife(ptr2->data->GetRight_M()-60,ptr2->data->GetTop_M());//вариант создание жизни для коробля
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
				if(pl->Cross(ptr->data))//если с пользователем столкнулся бот
				{
					pl->ReduceHeath();//отнимаем очки жизни у пользователя
						
					if(pl->LifeObject())//если пользователь жив - загружаем взрыв бота
					{
						MakeBang1(pl->GetLeft(),pl->GetTop());//загружаем взрыв
						bo.deleting(n);//удаление объекта из списка	
						di->DelDrawIndicator();//удаление жизни из дисплея
						break;
					}

					else//если смерть пользователя то взрыв смерти пользователя
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
					pl->ReduceHeath();//отнимаем очки жизни у пользователя

					if(pl->LifeObject())//если пользователь жив - загружаем взрыв
					{
						MakeBang3(pl->GetLeft(),pl->GetTop());//загружаем взрыв
						di->DelDrawIndicator();//удаление жизни из дисплея
						break;
					}

					else//если смерть пользователя то взрыв смерти
					{
						MakeBang2(pl->GetLeft(),pl->GetTop());
						process=DEATH_PLAYER;
					}
				}
				
				ptr=ptr->next;
			}

		}

		void game::MakeBang1(int left,int top)//загрузка взрыва
		{
			bt.add_tail(new bang(SgLoadImage("img/bang/gun_blast3.PNG"),left,top));
			sb->PlaySoundW();//загрузка звука взрыва
		}

		void game::MakeBang2(int left,int top)
		{
			bt.add_tail(new bang(SgLoadImage("img/bang/Exp_type_C2.PNG"),left,top));//A2
			sb->PlaySoundW();//загрузка звука взрыва
		}

		void game::MakeBang3(int left,int top)
		{
			bt.add_tail(new bang(SgLoadImage("img/bang/gun_blast2.PNG"),left,top));//A2
			sb->PlaySoundW();//загрузка звука взрыва
		}
		
		void game::MakeLife(int left,int top)
		{
			n=rand()%10;//вариант получение жизни с объекта
			
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
			r=-1;//сбрасываем счетчик
		
			n=rand()%regularity;//регулярность загрузки объектов
			
			if(n==0)
			{
				if(count_game<=levl_1)//******************************** 0 - 3 (Level (1))
				{
					r=rand()%4;
				}

				if(count_game>levl_1 && count_game<=levl_2)	//********** 4 - 5 (Level (2))
				{
					r=rand()%2+4;speed_obj=2;regularity=150;levl=2;
					
					t=rand()%10;//для изменения траектории движения объектов
					if(t==0)trajectory=rand()%3-1;
				}

				if(count_game>levl_2 && count_game<=levl_3) //********** 6 - 8 (Level (3))
				{
					 r=rand()%3+6; speed_obj=3;regularity=100;levl=3;
				}

				if(count_game>levl_3) //******************************** 8 (Level (4))
				{
					r=rand()%9; speed_obj=4;regularity=80;levl=4;

					t=rand()%10;//для изменения траектории движения объектов
					if(t==0)trajectory=rand()%3-1;
				}

				if(count_game>levl_3+levl_3) //************************* 8 (Level (5))
				{
					r=rand()%9; speed_obj=4;regularity=50;levl=5;

					t=rand()%10;//для изменения траектории движения объектов
					if(t==0)trajectory=rand()%3-1;
				}

				if(count_game>100) //*********************************** 8 (Level (6))
				{
					r=rand()%9;regularity=20;levl=6;

					t=rand()%10;//для изменения траектории движения объектов
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
				count_game++;//счетчик события игры
			}
		}

		game::~game()
		{
			delete pl;//указатель на объект игрока
			delete pld;//указатель на смерть пользователя 
			delete di;//указатель на объект дисплея
			delete me;//указатель на объект меню
			delete re;//указатель на результат
			delete op;//опции
			delete sm;//указатель на музыку в меню
			delete so;//указатель на звук выстрела
			delete sb;//указатель на звук
			delete sl;//указатель на звук
			delete gm;//указатель на звук
			delete smg;//указатель на звук
		}


void main()
{
	game app;
	app.WorkProcess();
}
