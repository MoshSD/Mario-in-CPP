#pragma once
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>
#include <string>
#include "Commons.h"

class GameScreenManager;

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void PassManager(GameScreenManager* manager) { gameScreenManager = manager; }

protected:
	SDL_Renderer* m_renderer;
	GameScreenManager* gameScreenManager;

};

#endif //_GAMESCREEN_H

