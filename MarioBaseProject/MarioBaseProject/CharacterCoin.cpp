#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_position = start_position;
	m_current_frame = 0;


	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterCoin::~CharacterCoin()
{
}

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	CoinAnimation(deltaTime);
}

void CharacterCoin::Render()
{


	//get the portion of the sprite sheet you want to draw 
	//{xPos, yPos, width of sprite, height of sprite}
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0 ,m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//Then draw it facing the right direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}

}


void CharacterCoin::CoinAnimation(float deltaTime)
{
	m_frame_delay -= deltaTime;

	if (m_frame_delay <= 0.0f)
	{
		//reset frame delay count
		m_frame_delay = ANIMATION_DELAY;

		//move the frame over
		m_current_frame++;

		//loop frame around if it goes beyond the number of frames
		if (m_current_frame > 2)
			m_current_frame = 0;

	}
}