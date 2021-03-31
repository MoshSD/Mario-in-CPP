#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include <string>
#include "Texture2D.h"
using namespace std;


class Texture2D;


class Character
{
	protected:
		SDL_Renderer* m_renderer;
		Vector2D m_position;
		Texture2D* m_texture;
		bool m_moving_left;
		bool m_moving_right;
		bool m_jumping;
		bool m_can_jump;
		bool m_jump_force;


		virtual void MoveLeft(float deltaTime);
		virtual void MoveRight(float deltaTime);

		float m_collision_radius;



	public:
		Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
		~Character();

		virtual void Render();
		virtual void Update(float deltaTime, SDL_Event e);
		virtual void AddGravity(float deltaTime);
		virtual void Jump();
		void SetPosition(Vector2D new_position);
		Vector2D GetPosition();

		float GetCollisionRadius();

		Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }

	private:
		FACING m_facing_direction;
		bool falling = true;

};

#endif //_CHARACTER_H