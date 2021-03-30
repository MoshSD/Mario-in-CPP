#include "CharacterLuigi.h"
#include "Constants.h"


CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position) : Character(renderer, imagePath, start_position)
{

}

CharacterLuigi::~CharacterLuigi()
{

}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	cout << m_position.y << endl;
	AddGravity(deltaTime);

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

	//deal with jumping first
	if (m_jumping)
	{
		//adjust position
		m_position.y -= m_jump_force * deltaTime;

		//reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		//is jump force 0?
		if (m_jump_force <= 0.0f)
			m_jumping = false;
	}


	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			cout << "lefty" << endl;
			m_moving_left = true;
			break;
		case SDLK_d:
			cout << "righty" << endl;
			m_moving_right = true;
			break;
		case SDLK_k:
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
}