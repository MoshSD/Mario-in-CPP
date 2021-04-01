#include "CharacterMario.h"
#include "constants.h"
using namespace std;


CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{

}

CharacterMario::~CharacterMario()
{

}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			cout << "lefty" << endl;
			m_moving_left = true;
			break;
		case SDLK_RIGHT:
			cout << "righty" << endl;
			m_moving_right = true;
			break;
		case SDLK_SPACE:
			cout << "spacebar pressed" << endl;
			if (m_can_jump == true)
			{
				Jump();
				cout << m_can_jump << endl;
			}
		}		
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			m_moving_right = false;
			break;
		}
		break;

	default:;
	}


	Character::Update(deltaTime, e);

}

