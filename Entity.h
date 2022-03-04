#pragma once
#include <SDL.h>
#include<SDL_image.h>
#include"Maths.h"


class Entity
{
protected:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
public:
	Entity();
	Entity(Vector2f p_pos,SDL_Texture* p_tex, int p_w, int p_h);
	void Move(float p_num);
	Vector2f& getPos();
	SDL_Texture* GetTex();
	SDL_Rect GetCurrentFrame();
	void Animate();
};
class Platform:Entity
{

};
