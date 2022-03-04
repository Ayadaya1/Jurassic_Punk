#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Enemy.h"
#include "Entity.h"
#include "RenderWindow.h"
#include "Utils.h"
#include "Player.h"
#include "SDL_ttf.h"
#include <time.h>
#include "SDL_mixer.h"


using namespace std;

void renderText(const string& message, SDL_Color color, int x, int y, int w, int h,RenderWindow p_window, TTF_Font* font);
int write_file(char* filename, int hs);
int read_file(char* filename);
const Uint8* keys = SDL_GetKeyboardState(NULL);
const int HEIGHT = 1080;
const int WIDTH = 1920;
int Init();

int main(int argc, char* argv[])
{
	if (Init() != 0)
		return 1;
	RenderWindow window("Jurassic Punk", WIDTH, HEIGHT);
	int windowRefreshRate = window.getRefreshRate();
	cout << windowRefreshRate;
	TTF_Font* font = TTF_OpenFont("Comic Sans.ttf", 16);
	SDL_Texture* Idle_Police = window.loadTexture("gfx/idle_police.png");
	SDL_Texture* bg1 = window.loadTexture("gfx/Jurassic_Background_1.png");
	SDL_Texture* Police_run = window.loadTexture("gfx/police_run.png");
	SDL_Texture* Police_run_right = window.loadTexture("gfx/police_run_right.png");
	SDL_Texture* Dino_Jump = window.loadTexture("gfx/dino_jump.png");
	SDL_Texture* Dino_Run = window.loadTexture("gfx/dino_run.png");
	SDL_Texture* Dino_Run_Left = window.loadTexture("gfx/dino_run_left.png");
	SDL_Texture* Heart = window.loadTexture("gfx/heart.png");
	SDL_Texture* menu1 = window.loadTexture("gfx/menu1.png");
	SDL_Texture* menu2 = window.loadTexture("gfx/menu2.png");
	SDL_Texture* Loss = window.loadTexture("gfx/Lose.png");
	SDL_Color color = { 255,255,255,255 };
	SDL_Surface* surf = TTF_RenderUNICODE_Blended(font, reinterpret_cast<Uint16 const*>(L"Ñ÷¸ò:"), color);
	SDL_Texture* scoretex = SDL_CreateTextureFromSurface(window.GetRen(), surf);
	surf = TTF_RenderUNICODE_Blended(font, reinterpret_cast<Uint16 const*>(L"Ðåêîðä:"), color);
	SDL_Texture* highscoretex = SDL_CreateTextureFromSurface(window.GetRen(), surf);
	string scorestring;
	string str = "Ñ÷¸ò:";
	if (SDL_Init(SDL_INIT_AUDIO) < 0) exit(1);
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	Mix_Music* mus, * mus2, * mus3;
	mus = Mix_LoadMUS("Sounds/menutheme.wav");
	mus2 = Mix_LoadMUS("Sounds/maintheme.wav");
	mus3 = Mix_LoadMUS("Sounds/salvation.wav");
	if (mus2 == NULL)
		exit(1);
	//Mix_PlayMusic(mus,1);

	bool gameRunning = true;
	bool menu = true;
	char filename[20] = "highscores.bin";
	SDL_Event e;
	Entity heart;
	Entity scoreentity(Vector2f(1650, 50), scoretex, 100, 64);
	Entity highscoreentity(Vector2f(1600, 100), highscoretex, 150, 64);
	vector<Enemy> enemies;
	vector<Entity> hearts =
	{
		Entity(Vector2f(50,50),Heart,64,64),
		Entity(Vector2f(100,50),Heart,64,64),
		Entity(Vector2f(150,50),Heart,64,64)
	};
	Player player(Vector2f(300, 300), Dino_Jump);
	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();
	int dir = 0;
	int score = 0, highscore = read_file(filename);
	char hschar[8];
	_itoa(highscore, hschar, 10);
	string hsstring = string(hschar);
	int menuu = 1;
	char scorechar[8];


	Mix_PlayMusic(mus, -1);
	while (gameRunning)
	{
		bool played = false;
		while (menu)
		{
			SDL_Event m;
			while (SDL_PollEvent(&m))
			{
				if (m.type == SDL_QUIT)
					menu = false;
				if (m.type == SDL_KEYDOWN)
				{
					if (m.key.keysym.sym == SDLK_UP || m.key.keysym.sym == SDLK_DOWN)
					{
						if (menuu == 1)
							menuu = 2;
						else
							menuu = 1;
					}
					if (m.key.keysym.sym == SDLK_ESCAPE)
					{
						menu = false;
						if (!played)
							gameRunning = false;
					}
					if (m.key.keysym.sym == SDLK_RETURN)
					{
						if (menuu == 1)
						{
							Mix_HaltMusic();
							Mix_PlayMusic(mus2, -1);
							played = true;
							menu = false;
						}
						else
						{
							menu = false;
							gameRunning = false;
						}
					}
				}
			}
			switch (menuu)
			{
			case 1:
				window.RenderBackGround(menu1);
				break;
			case 2:
				window.RenderBackGround(menu2);
				break;
			}
			window.Display();

		}
		if (player.Death())
		{
			Mix_HaltMusic();
			Mix_PlayMusic(mus3, 1);
			enemies.clear();
		}
		while (player.Death())
		{

			player.setPos(Vector2f(300, 300));
			window.RenderBackGround(Loss);
			window.Display();
			SDL_Event m;
			while (SDL_PollEvent(&m))
			{
				if (m.type == SDL_QUIT)
					menu = false;
				if (m.type == SDL_KEYDOWN)
				{
					if (m.key.keysym.sym == SDLK_RETURN)
					{
						player.setHP(3);
						if (score > highscore)
						{
							highscore = score;
							write_file(filename, highscore);
						}
						score = 0;
						Mix_HaltMusic();
						Mix_PlayMusic(mus, -1);
						menu = true;
					}
				}
			}
		}
		int startTicks = SDL_GetTicks();
		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;
		currentTime = newTime;
		accumulator += frameTime;
		while (accumulator >= timeStep)
		{
			while (menu)
			{
				SDL_Event m;
				while (SDL_PollEvent(&m))
				{
					if (m.type == SDL_QUIT)
						menu = false;
					if (m.type == SDL_KEYDOWN)
					{
						if (m.key.keysym.sym == SDLK_UP || m.key.keysym.sym == SDLK_DOWN)
						{
							if (menuu == 1)
								menuu = 2;
							else
								menuu = 1;
						}
						if (m.key.keysym.sym == SDLK_ESCAPE)
						{
							Mix_HaltMusic();
							Mix_PlayMusic(mus2, -1);
							menu = false;
						}
						if (m.key.keysym.sym == SDLK_RETURN)
						{
							if (menuu == 1)
							{
								Mix_HaltMusic();
								Mix_PlayMusic(mus2, -1);
								menu = false;
							}
							else
							{
								menu = false;
								gameRunning = false;
							}
						}
					}
				}
				switch (menuu)
				{
				case 1:
					window.RenderBackGround(menu1);
					break;
				case 2:
					window.RenderBackGround(menu2);
					break;
				}
				window.Display();

			}

			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					gameRunning = false;
				if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_ESCAPE)
					{
						menu = true;
						Mix_HaltMusic();
						Mix_PlayMusic(mus,-1);
					}
				}
				if (e.type == SDL_KEYUP)
				{
					if (e.key.keysym.sym == SDLK_RIGHT)
					{
						player.Running_Stop(dir);
					}
					if (e.key.keysym.sym == SDLK_LEFT)
					{
						player.Running_Stop(dir);
					}
				}
			}
			if (keys[SDL_SCANCODE_RIGHT] && !keys[SDL_SCANCODE_LEFT])
			{
				dir = 1;
				player.Move(dir);
			}
			if (keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT])
			{
				dir = 2;
				player.Move(dir);
			}
			if (keys[SDL_SCANCODE_RIGHT] && keys[SDL_SCANCODE_LEFT])
			{
				player.Running_Stop(dir);
			}
			if (keys[SDL_SCANCODE_UP])
			{
				player.Jump();
			}
			cout << dir << " ";
			accumulator -= timeStep;
		}
		if (score % 10 == 0&&(enemies.size())<=(score/10)&&enemies.size()<=10
			)
		{
			if (score % 20 != 0 || score == 0)
			{
				Enemy Wilson(Vector2f(2000, 1000), Idle_Police);
				enemies.push_back(Wilson);
			}
			if (score % 20 == 0 || score == 0)
			{
				Enemy Brad(Vector2f(-2000, 1000), Idle_Police);
				enemies.push_back(Brad);
			}
		}
		const float alpha = accumulator / timeStep;
		player.Jumping();
		window.Clear();
		window.RenderBackGround(bg1);
		for (int i = 0; i < player.GetHP(); i++)
		{
			window.Render(hearts[i]);
		}
		player.Gravity();
		player.BottomCol();
		for (Enemy& e : enemies)
		{
			e.Gravity();
			e.BottomCol();
			e.HeadsRight(player);
			score = e.collide(player, score);
			window.Render(e);
		}
		_itoa(score, scorechar, 10);
		scorestring = string(scorechar);
		window.Render(scoreentity);
		window.Render(highscoreentity);
		renderText(scorestring, color, 1775, 50, 64, 64, window, font);
		renderText(hsstring, color, 1775, 100, 64, 64,window,font);
		window.Render(player);
		window.Display();
		int frameTicks = SDL_GetTicks() - startTicks;
		cout << frameTicks << ", ";
		if (frameTicks < 1000 / window.getRefreshRate() * 2)
			SDL_Delay((1000 / (window.getRefreshRate() / 2) - frameTicks) * 4);
		cout << (1000 / (window.getRefreshRate() / 2) - frameTicks) * 4 << endl;
		for (Enemy& e : enemies)
		{
			e.Chase(player);
			e.Animate(Idle_Police);
			e.RunAnimation(Police_run, Police_run_right);
		}
		player.Jump_Animation(Dino_Jump, Dino_Jump, dir);
		player.RunAnimation(Dino_Run, Dino_Run_Left, dir);
		player.Fall_Animation(Dino_Jump, Dino_Jump, dir);
		player.JumpCheck();
		dir = 0;
	}
	window.cleanUp();
	SDL_DestroyTexture(Police_run_right);
	SDL_DestroyTexture(Police_run);
	SDL_DestroyTexture(Dino_Jump);
	SDL_DestroyTexture(bg1);
	SDL_DestroyTexture(Heart);
	SDL_DestroyTexture(menu1);
	SDL_DestroyTexture(menu2);
	SDL_DestroyTexture(Dino_Jump);
	SDL_DestroyTexture(Dino_Run);
	SDL_DestroyTexture(Dino_Run_Left);
	SDL_DestroyTexture(scoretex);
	SDL_DestroyTexture(highscoretex);
	Mix_FreeMusic(mus);
	Mix_FreeMusic(mus2);
	Mix_FreeMusic(mus3);
	enemies.clear();
	SDL_Quit();
	return 0;
}
int Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL_Init Error: " << SDL_GetError();
		return 1;
	}
	if (!(IMG_Init(IMG_INIT_JPG)))
	{
		cout << "IMG_Init Error: " << SDL_GetError() << endl;
		return 1;
	}
	if (TTF_Init()!=0)
	{
		cout << "TTF_Init Error: " << SDL_GetError() << endl;
		return 1;
	}
	if (Mix_Init(MIX_INIT_OGG) == 0)
		return 0;
	return 0;
}
void renderText(const string& message, SDL_Color color, int x, int y, int w, int h, RenderWindow p_window, TTF_Font* font)
{
	int iw, ih;
	SDL_Rect dst = { x,y,w,h };
	SDL_Surface* text = TTF_RenderUTF8_Solid(font, message.c_str(), color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(p_window.GetRen(),text);
	SDL_FreeSurface(text);
	SDL_RenderCopy(p_window.GetRen(), tex, NULL, &dst);
	SDL_QueryTexture(tex, NULL, NULL, &iw, &ih);
}
int write_file(char* filename, int hs)
{
	FILE* f;
	if ((f = fopen(filename, "wb")) == NULL)
	{
		perror("Error while creating a file");
		return 0;
	}
	else
		fwrite(&hs, sizeof(int), 1, f);
	return 1;
}
int read_file(char* filename)
{
	FILE* f;
	int hs;
	if ((f = fopen(filename, "rb")) == NULL)
	{
		perror("Error while reading the file");
		return 0;
	}
	else
		cout << "File written!";
	fread(&hs, sizeof(int), 1, f);
	fclose(f);
	return hs;
}
