#pragma once
//////////////////////////Sound/////////////////////////////////////////����� ���� (����� ����������� �����)
class sound
{
	protected:

		int handle; //������������� �����
		long volume;//������� �����
		double seconds;//�������, � ������� ���� ��������������  
		int id;//id

	public:

		sound(int handle,long volume=0,double seconds=0,int id=-1)
		
		{
			this->handle=handle;
			this->volume=volume;
			this->seconds=seconds;
			this->id=id;
			
		}
		
		virtual void PlaySound()//��������������� ������
		{
			SgPlaySound (handle );
		}
		
		virtual~sound()=0
		{
			SgDestroySound ( handle ); 
		}
};

	
//////////////////////////SoundShot/////////////////////////////////////////����� ���� ��������
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

//////////////////////////SoundBang/////////////////////////////////////////����� ���� ������
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

//////////////////////////SoundLife/////////////////////////////////////////����� ���� �����
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
//////////////////////////Game Over/////////////////////////////////////////����� ���� Game Over
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

//////////////////////////Soundmusic/////////////////////////////////////////����� ������
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
//////////////////////////SoundmusicGame/////////////////////////////////////////����� ������ ����
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

	