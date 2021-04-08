#include "CharacterLuigi.h"
#include "Constants.h"


CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{

}

CharacterLuigi::~CharacterLuigi()
{

}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	//AddGravity(deltaTime);




	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = true;
			break;
		case SDLK_d:
			m_moving_right = true;
			break;
		case SDLK_k:
			if (m_can_jump == true)
			{
				Jump();
			}
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = false;
			break;
		case SDLK_d:
			m_moving_right = false;
			break;
		}
		break;

	default:;
	}



	Character::Update(deltaTime, e);



}