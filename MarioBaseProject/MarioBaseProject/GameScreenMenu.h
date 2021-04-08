#pragma once

#include "GameScreen.h"
#include "Commons.h"
#include "constants.h"
#include "Character.h"
#include "CharacterLuigi.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "GameScreenManager.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include <vector>


#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H

class Texture2D;

class GameScreenMenu : GameScreen
{



public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;


private:
	SDL_Renderer* m_renderer;
	Texture2D* m_background_texture;
	Texture2D* m_background_texture_play;
	Texture2D* m_background_texture_quit;


	float m_background_yPos;
	int m_current_background_num;


	enum BACKGROUNDS
	{
		BACKGROUND_DEFAULT,
		BACKGROUND_PLAY,
		BACKGROUND_QUIT
	};

	BACKGROUNDS currentBackground;

	bool SetUpLevel();

protected:


};


#endif _GAMESCREENMENU_H

