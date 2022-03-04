#pragma once
#include "Entity.h"
#include "Maths.h"
#include "Player.h"
#include <SDL.h>
#include<SDL_image.h>
#include<iostream>

class Enemy :public Entity
{
	bool isJumping;
	bool isFalling;
	bool isRunning;
	bool Right;
	int g;
	unsigned char hp;
	const int JumpHeight = 500;
	int jump = 0;
public:
	Enemy(Vector2f p_pos, SDL_Texture* p_tex);
	Enemy(const Enemy& p_enemy);
	void Chase(Player& p_player);
	void Animate(SDL_Texture* p_tex);
	Vector2f& getPos();
	SDL_Texture* GetTex();
	SDL_Rect GetCurrentFrame();
	void Gravity();
	void Jump();
	void Jumping();
	void BottomCol();
	void RunAnimation(SDL_Texture* p_tex, SDL_Texture* p_tex_right);
	void Running_Stop();
	void HeadsRight(Player& p_player);
	int collide(Player& p_player,int score);
	void Whatchadoin();
	void TopCollision(Player& p_player);
	void setpos(Vector2f v);
};