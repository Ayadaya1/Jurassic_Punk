#include "Entity.h"
#include <SDL.h>
#include<SDL_image.h>
#include<iostream>
#include "Maths.h"
#include "Enemy.h"
#include "Player.h"

void Player::Move(int p_dir)
{
	if (isRunning == false && isJumping == false && isFalling == false)
	{
		if (p_dir == 1)
		{
			currentFrame.y = 36;
			currentFrame.x = 10;
		}
		else
		{
			currentFrame.y = 36;
			currentFrame.x = 548;
		}
		isRunning = true;
	}
	if (p_dir == 1&&CantMoveRight==false)
		pos.x += 5;
	else if (p_dir == 2)
		pos.x -= 5;
}
Player::Player(Vector2f p_pos, SDL_Texture* p_tex)
{
	hp = 3;
	isJumping = false;
	isFalling = true;
	isRunning = false;
	CantMoveLeft = false;
	CantMoveRight = false;
	pos = p_pos;
	tex = p_tex;
	currentFrame.x = 0;
	currentFrame.y = 36;
	currentFrame.w = 80;
	currentFrame.h = 86;
	g = 0;
}
Vector2f& Player::getPos()
{
	return pos;
}
SDL_Texture* Player::GetTex()
{
	return tex;
}
SDL_Rect Player::GetCurrentFrame()
{
	return currentFrame;
}
void Player::Animate(SDL_Texture* p_tex)
{
	if (isRunning == false&&isJumping==false&&isFalling==false)
	{
		tex = p_tex;
		while (currentFrame.y < 36)
			currentFrame.y++;
		currentFrame.x += 128;
		if (currentFrame.x  > 776)
		{
			currentFrame.x = 0;
			currentFrame.y += 128;
		}
		if (currentFrame.y == 676 && currentFrame.x > 384)
		{
			currentFrame.x = 0;
			currentFrame.y = 36;
		}
	}
}
void Player::Gravity()
{
	if (isFalling == true)
	{
		g+=3;
		pos.y += 20 + g;
	}
}
void Player::Jump()
{
	if (isFalling == false&&isJumping==false)
		isJumping = true;
	if (isRunning == true)
		isRunning = false;
	currentFrame.x = 128;
	currentFrame.y = 164;
}
void Player::Jumping()
{
	if (isJumping == true && isFalling == false)
	{
		if (jump < JumpHeight)
		{
			pos.y -= 35;
			jump += 35;
		}
		else
		{
			isJumping = false;
			jump = 0;
			isFalling = true;
		}
	}
}
void Player::BottomCol()
{
	if (pos.y + GetCurrentFrame().h * 4 >= 1080)
	{
		pos.y = 1080 - GetCurrentFrame().h * 4 + 4;
		if (isFalling == true)
		{
			currentFrame.x = 8;
			currentFrame.y = 36;
		}
		isFalling = false;
		g = 0;
	}
	if (pos.x < 0)
		pos.x = 0;
	if (pos.x + currentFrame.w * 4 > 1920)
		pos.x = 1920 - currentFrame.w * 4;
}
void Player::RunAnimation(SDL_Texture* p_tex, SDL_Texture* p_tex_left, int dir)
{

	if (isRunning == true && isJumping == false && isFalling==false)
	{
		if (dir == 1)
			tex = p_tex;
		else
			tex = p_tex_left;
		if (dir == 1)
		{
			currentFrame.x += 128;
			if (currentFrame.x > 512 && currentFrame.y < 420)
			{
				currentFrame.x = 10;
				currentFrame.y += 128;
			}
			if (currentFrame.y == 420 && currentFrame.x > 512)
			{
				currentFrame.x = 10;
				currentFrame.y = 36;
			}
		}
		else
		{
			currentFrame.x -= 128;
			if (currentFrame.x <0 && currentFrame.y < 420)
			{
				currentFrame.x = 548;
				currentFrame.y += 128;
			}
			if (currentFrame.y == 420 && currentFrame.x <0)
			{
				currentFrame.x = 548;
				currentFrame.y = 36;
			}
		}
	}
}
void Player::Running_Stop(int dir)
{
	if (isRunning == true)
	{
		if (dir == 1)
		{
			currentFrame.x = 10;
			currentFrame.y = 36;
		}
		else if(dir == 2)
		{
			currentFrame.x = 548;
			currentFrame.y = 36;
		}
	}
	isRunning = false;
}
void Player::Jump_Animation(SDL_Texture* p_tex, SDL_Texture* p_tex_left, int dir)
{
	if (isJumping == true&&isFalling==false)
	{
		tex = p_tex;
		while (currentFrame.y < 36)
			currentFrame.y++;
		currentFrame.x += 128;
		if (currentFrame.x > 776)
		{
			currentFrame.x = 0;
			currentFrame.y += 128;
		}
		if (currentFrame.y == 292 && currentFrame.x > 0)
		{
			currentFrame.x = 384;
			currentFrame.y = 164;
		}
	}
}
void Player::Fall_Animation(SDL_Texture* p_tex, SDL_Texture* p_tex_right, int dir)
{
	if (isFalling == true)
	{
		tex = p_tex;
		while (currentFrame.y < 36)
			currentFrame.y++;
		currentFrame.x += 128;
		if (currentFrame.x > 776)
		{
			currentFrame.x = 0;
			currentFrame.y += 128;
		}
		if (currentFrame.y == 548 && currentFrame.x > 512)
		{
			currentFrame.x = 384;
			currentFrame.y = 256;
		}
	}
}
bool Player::Death()
{
	if (hp == 0)
		return true;
	else
		return false;
}
void Player::hurt()
{
	if (hp > 0)
		hp--;
}
void Player::JumpCheck()
{
	std::cout << isRunning<<" ";
}
void Player::WontMoveRight(char p)
{
	if (p == 1)
		CantMoveRight = true;
	else
		CantMoveRight = false;
}
void Player::Falling_Stop(char p)
{
	if (p == 1)
		isFalling = false;
	else
		isFalling = true;
}
bool Player::GetFalling()
{
	return isFalling;
}
int Player::GetHP()
{
	return hp;
}
void Player::setHP(int a)
{
	hp = a;
}
void Player::setPos(Vector2f v)
{
	pos.x = v.x;
	pos.y = v.y;
	isFalling = true;
	currentFrame.x = 384;
	currentFrame.y = 164;
}