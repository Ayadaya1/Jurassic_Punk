#pragma once
#include "Entity.h"
#include "Maths.h"
#include <SDL.h>
#include<SDL_image.h>
#include<iostream>
#include"Enemy.h"

class Player :Entity
{
	bool isJumping;
	bool isFalling;
	bool isStanding;
	bool isRunning;
	bool CantMoveRight;
	bool CantMoveLeft;
	int g;
	Uint8 hp;
	const int JumpHeight = 400;
	int jump = 0;
public:
	Player(Vector2f p_pos, SDL_Texture* p_tex);
	void Move(int p_dir);
	void Animate(SDL_Texture* p_tex);
	Vector2f& getPos();
	SDL_Texture* GetTex();
	SDL_Rect GetCurrentFrame();
	void Gravity();
	void Jump();
	void Jumping();
	void BottomCol();
	void RunAnimation(SDL_Texture* p_tex, SDL_Texture* p_tex_right, int dir);
	void Running_Stop(int dir);
	void Jump_Animation(SDL_Texture* p_tex, SDL_Texture* p_tex_left, int dir);
	void Fall_Animation(SDL_Texture* p_tex, SDL_Texture* p_tex_right, int dir);
	bool Death();
	void hurt();
	void JumpCheck();
	void WontMoveRight(char p);
	void Falling_Stop(char p);
	bool GetFalling();
	int GetHP();
	void setHP(int a);
	void setPos(Vector2f v);
};