#pragma once
#ifndef _CHARACTERCOIN_H
#define _CHARACTERCOIN_H
#include "Character.h"
#include "constants.h"



class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing);
	~CharacterCoin();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();


private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_frame_delay;

	int m_current_frame;

	void CoinAnimation(float deltaTime);


	FACING m_facing_direction;

};
#endif _CHARACTERCOIN_H
