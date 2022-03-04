#include "Entity.h"
#include <SDL.h>
#include<SDL_image.h>
#include<iostream>
#include "Maths.h"

Entity::Entity()
{
	pos = Vector2f(0, 0);
	tex = nullptr;
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 64;
	currentFrame.h = 64;
}
Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, int p_w, int p_h)
{
	pos = p_pos;
	tex = p_tex;
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_w;
	currentFrame.h = p_h;
}
Vector2f& Entity::getPos()
{
	return pos;
}
SDL_Texture* Entity::GetTex()
{
	return tex;
}
SDL_Rect Entity::GetCurrentFrame()
{
	return currentFrame;
}
void Entity::Move(float p_num)
{

}
void Entity::Animate()
{
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