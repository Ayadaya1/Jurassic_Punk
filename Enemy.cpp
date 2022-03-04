#include "Entity.h"
#include <SDL.h>
#include<SDL_image.h>
#include<iostream>
#include "Maths.h"
#include "Enemy.h"
#include "Player.h"
#include <time.h>

void Enemy::Chase(Player& p_player)
{
	if (p_player.getPos().x > pos.x + currentFrame.w)
	{
		if (isRunning == false)
		{
			currentFrame.y = 0;
			currentFrame.x = 0;
		}
		isRunning = true;
		pos.x += 25;
	}
	else if (p_player.getPos().x + p_player.GetCurrentFrame().w < pos.x)
	{
		if (isRunning == false)
		{
			currentFrame.y = 0;
			currentFrame.x = 0;
		}
		isRunning = true;
		pos.x -= 25;
	}
	else if ((p_player.getPos().x - 500 >= pos.x && p_player.getPos().x > pos.x) || (p_player.getPos().x + 500 <= pos.x && p_player.getPos().x < pos.x))
	{
		if (isRunning == true)
		{
			isRunning = false;
			currentFrame.x = 0;
			currentFrame.y = 0;
		}
	}
	else
	{
		if (isRunning == true)
		{
			isRunning = false;
			currentFrame.x = 0;
			currentFrame.y = 0;
		}
	}
}
Enemy::Enemy(Vector2f p_pos, SDL_Texture* p_tex)
{
	hp = 1;
	isJumping = false;
	isFalling = true;
	isRunning = false;
	Right = false;
	pos = p_pos;
	tex = p_tex;
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 64;
	currentFrame.h = 64;
	g = 0;
}
Enemy::Enemy(const Enemy& p_enemy)
{
	hp = p_enemy.hp;
	isJumping = p_enemy.isJumping;
	isFalling = p_enemy.isFalling;
	Right = p_enemy.Right;
	pos = p_enemy.pos;
	tex = p_enemy.tex;
	currentFrame.x = p_enemy.currentFrame.x;
	currentFrame.y = p_enemy.currentFrame.y;
	currentFrame.w = p_enemy.currentFrame.w;
	currentFrame.h = p_enemy.currentFrame.h;
	g = p_enemy.g;
}
Vector2f& Enemy::getPos()
{
	return pos;
}
SDL_Texture* Enemy::GetTex()
{
	return tex;
}
SDL_Rect Enemy::GetCurrentFrame()
{
	return currentFrame;
}
void Enemy::Animate(SDL_Texture* p_tex)
{
	if (isRunning == false&&isFalling==false)
	{
		if (isRunning == false&&isFalling==false)
		tex = p_tex;
		currentFrame.x += 96;
		if (currentFrame.x + 96 > 928 + 16)
		{
			currentFrame.x = 0;
			currentFrame.y += 96;
		}
		if (currentFrame.y == 672 && currentFrame.x + 96 > 352)
		{
			currentFrame.x = 0;
			currentFrame.y = 0;
		}
	}
}
void Enemy::Gravity()
{
	if (isFalling == true)
	{
		isRunning = false;
		g++;
		pos.y += 20 + g;
	}
}
void Enemy::Jump()
{
	if (isFalling == false)
		isJumping = true;
	if (isRunning == true)
		isRunning = false;
	currentFrame.x = 0;
	currentFrame.y = 0;
}
void Enemy::Jumping()
{
	if (isJumping == true && isFalling == false)
	{
		if (jump < JumpHeight)
		{
			pos.y -= 20;
			jump += 20;
		}
		else
		{
			isJumping = false;
			jump = 0;
			isFalling = true;
		}
	}
}
void Enemy::BottomCol()
{
	if (pos.y + GetCurrentFrame().h*4>=1080)
	{
		pos.y = 1080 - GetCurrentFrame().h*4+4;
		isFalling = false;
		g = 0;
	}
}
void Enemy::RunAnimation(SDL_Texture* p_tex, SDL_Texture* p_tex_right)
{
	
	if (isRunning == true)
	{
		if (Right == true)
			tex = p_tex_right;
		else if (Right == false)
			tex = p_tex;
		if (Right == false)
		{
			currentFrame.x += 64;
			if (currentFrame.x + 64 > 320)
			{
				currentFrame.x = 0;
				currentFrame.y += 64;
			}
			if (currentFrame.y == 256 && currentFrame.x > 63)
			{
				currentFrame.x = 128;
				currentFrame.y = 0;
			}
		}
		else
		{
			currentFrame.x -= 64;
			if (currentFrame.x - 64 < 0)
			{
				currentFrame.x = 256;
				currentFrame.y += 64;
			}
			if (currentFrame.y == 256 && currentFrame.x < 256)
			{
				currentFrame.x = 128;
				currentFrame.y = 0;
			}
		}
	}
}
void Enemy::Running_Stop()
{
	isRunning = false;
	currentFrame.x = 0;
	currentFrame.y = 0;
}
void Enemy::HeadsRight(Player& p_player)
{
	if (pos.x < p_player.getPos().x)
		Right = true;
	else
		Right = false;
}
int Enemy::collide(Player& p_player, int score)
{
	if ((pos.x <= p_player.getPos().x + p_player.GetCurrentFrame().w * 4-36 && pos.y > p_player.getPos().x && pos.y > p_player.getPos().y + p_player.GetCurrentFrame().h * 4) || pos.x + currentFrame.w * 4 >= p_player.getPos().x)
	{
		if (pos.x <= p_player.getPos().x + p_player.GetCurrentFrame().w * 4 - 36 &&  pos.y < p_player.getPos().y + p_player.GetCurrentFrame().h * 4)
		{
			pos.x += 20;
			if (p_player.GetFalling() == false)
				p_player.hurt();
			else score++;
			if (Right == true)
				pos.x -= 1500 + rand() % 1000;
			else
				pos.x += 1500 + rand() % 1000;
		}

	}
	return score;
}
void Enemy::Whatchadoin()
{
	std::cout << isRunning<<" ";
}
void Enemy::TopCollision(Player& p_player)
{
	if ((pos.y <= p_player.getPos().y + p_player.GetCurrentFrame().h * 4) && (pos.x + currentFrame.w * 4 >= p_player.getPos().x && pos.x <= p_player.getPos().x + p_player.GetCurrentFrame().w * 4))
	{
		p_player.Falling_Stop(1);
		std::cout << "Udobno." << std::endl;
	}
	else
		p_player.Falling_Stop(2);
}
void Enemy::setpos(Vector2f v)
{
	pos.x = v.x;
	pos.y = v.y;
}