#pragma once
#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H
#include "Character.h"
#include "constants.h"


class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	
	bool GetInjured();
	void TakeDamage();
	void Jump();
	void FlipDirection(FACING directionToFace);

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_injured_time;
	float m_movement_speed;
	

	bool m_injured;

	void FlipRightWayUp();
	




	FACING m_facing_direction;


};

#endif _CHARACTERKOOPA_H
