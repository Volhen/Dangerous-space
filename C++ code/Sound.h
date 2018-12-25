#pragma once
//////////////////////////Sound/////////////////////////////////////////класс звук (чисто виртуальный класс)
class sound
{
	protected:

		int handle; //Идентификатор звука
		long volume;//уровень звука
		double seconds;//Секунды, с которых надо воспроизводить  
		int id;//id

	public:

		sound(int handle,long volume=0,double seconds=0,int id=-1)
		
		{
			this->handle=handle;
			this->volume=volume;
			this->seconds=seconds;
			this->id=id;
			
		}
		
		virtual void PlaySound()//воспроизведение звуков
		{
			SgPlaySound (handle );
		}
		
		virtual~sound()=0
		{
			SgDestroySound ( handle ); 
		}
};

	
//////////////////////////SoundShot/////////////////////////////////////////класс звук выстрела
class sound_shot: public sound
{
	public:

		sound_shot(int handle=0,int id=-1):
		sound(handle)
		
		{
			this->handle=handle;
			this->id=id;
			
		}
};

//////////////////////////SoundBang/////////////////////////////////////////класс звук взрыва
class sound_bang: public sound
{
	public:

		sound_bang(int handle=0,int id=-1):
		sound(handle)
		
		{
			this->handle=handle;
			this->id=id;
			
		}
	
};

//////////////////////////SoundLife/////////////////////////////////////////класс звук жизни
class sound_life: public sound
{
	public:

		sound_life(int handle=0,int id=-1):
		sound(handle)
		
		{
			this->handle=handle;
			this->id=id;
			
		}
	
};
//////////////////////////Game Over/////////////////////////////////////////класс звук Game Over
class sound_game_over: public sound
{

	public:

		sound_game_over(int handle=0,int id=-1):
		sound(handle)
		
		{
			this->handle=handle;
			this->id=id;
			
		}
			
};

//////////////////////////Soundmusic/////////////////////////////////////////класс музыка
class sound_music: public sound
{
	public:

		sound_music(int handle=0,int id=-1):
		sound(handle)
		
		{
			this->handle=handle;
			this->id=id;
			
		}
		void PlaySound()
		{
			SgPlaySound (handle ); 
		}
		void Pause()
		{
			SgPauseSound ( handle );
		}
	
};
//////////////////////////SoundmusicGame/////////////////////////////////////////класс музыка игры
class sound_music_game: public sound_music
{
	public:

		sound_music_game(int handle=0,int id=-1):
		sound_music()
		
		{
			this->handle=handle;
			this->id=id;
			
		}
		
};

	