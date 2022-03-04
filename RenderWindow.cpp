#include "Platform.h"
#include <SDL.h>
#include <iostream>
#include<SDL_image.h>
#include "RenderWindow.h"
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:win(nullptr), ren(nullptr)
{
	win = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (win == nullptr)
		std::cout << "CreateWindow Error: " << SDL_GetError();
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == nullptr)
		std::cout << "CreateRenderer Error: " << SDL_GetError();
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(win);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(ren, p_filePath);
	if (texture == nullptr)
	{
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	}
	return texture;
}

SDL_Renderer* RenderWindow::GetRen()
{
	return ren;
}

void RenderWindow::Clear()
{
	SDL_RenderClear(ren);
}

void RenderWindow::Render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.GetCurrentFrame().x;
	src.y = p_entity.GetCurrentFrame().y;
	src.w = p_entity.GetCurrentFrame().w;
	src.h = p_entity.GetCurrentFrame().h;
	SDL_Rect dst;
	dst.x = p_entity.getPos().x;
	dst.y = p_entity.getPos().y;
	dst.w = p_entity.GetCurrentFrame().w;
	dst.h = p_entity.GetCurrentFrame().h;
	SDL_RenderCopy(ren, p_entity.GetTex(), NULL, &dst);
}
void RenderWindow::Render(Enemy& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.GetCurrentFrame().x;
	src.y = p_entity.GetCurrentFrame().y;
	src.w = p_entity.GetCurrentFrame().w;
	src.h = p_entity.GetCurrentFrame().h;
	SDL_Rect dst;
	dst.x = p_entity.getPos().x;
	dst.y = p_entity.getPos().y;
	dst.w = p_entity.GetCurrentFrame().w * 4;
	dst.h = p_entity.GetCurrentFrame().h * 4;
	SDL_RenderCopy(ren, p_entity.GetTex(), &src, &dst);
}
void RenderWindow::Render(Player& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.GetCurrentFrame().x;
	src.y = p_entity.GetCurrentFrame().y;
	src.w = p_entity.GetCurrentFrame().w;
	src.h = p_entity.GetCurrentFrame().h;
	SDL_Rect dst;
	dst.x = p_entity.getPos().x;
	dst.y = p_entity.getPos().y;
	dst.w = p_entity.GetCurrentFrame().w * 4;
	dst.h = p_entity.GetCurrentFrame().h * 4;
	SDL_RenderCopy(ren, p_entity.GetTex(), &src, &dst);
}
void RenderWindow::Display()
{
	SDL_RenderPresent(ren);
}
int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(win);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);
	return mode.refresh_rate;
}
void RenderWindow::RenderBackGround(SDL_Texture* p_tex)
{
	SDL_RenderCopy(ren, p_tex, NULL, NULL);
}