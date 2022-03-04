#pragma once
#include <SDL.h>
#include<SDL_image.h>
#include"Entity.h"
#include "Enemy.h"
#include "Player.h"

class RenderWindow
{
	SDL_Window* win;
	SDL_Renderer* ren;
public:
	RenderWindow(const char* p_title,int p_w, int p_h);
	void cleanUp();
	SDL_Texture* loadTexture(const char* p_filePath);
	SDL_Renderer* GetRen();
	int getRefreshRate();
	void Clear();
	void Render(Entity& p_entity);
	void Render(Enemy& p_entity);
	void Render(Player& p_entity);
	void Display();
	void RenderBackGround(SDL_Texture* p_tex);
};