#pragma once
#ifndef _GAMESCREENYOUWIN_H
#define _GAMESCREENYOUWIN_H


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

class Texture2D;

class GameScreenYouWin : GameScreen
{

public:
	GameScreenYouWin(SDL_Renderer* renderer);
	~GameScreenYouWin();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;


private:
	SDL_Renderer* m_renderer;
	Texture2D* m_background_texture;
	Texture2D* m_background_texture_scores;
	Texture2D* m_background_texture_menu;


	float m_background_yPos;
	int m_current_background_num;


	enum BACKGROUNDS
	{
		BACKGROUND_DEFAULT,
		BACKGROUND_SCORES,
		BACKGROUND_MENU
	};

	BACKGROUNDS currentBackground;

	bool SetUpLevel();


};



#endif _GAMESCREENYOUWIN_H
