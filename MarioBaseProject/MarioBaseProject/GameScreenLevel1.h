#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterLuigi.h"
#include "CharacterMario.h"
#include "LevelMap.h"





class Character;
class Texture2D;






class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;



private:
	Texture2D* m_background_texture;
	Character* my_character;
	CharacterMario* mario_Character;
	CharacterLuigi* luigi_Character;
	bool SetUpLevel();

	void SetLevelMap();

	LevelMap* m_level_map;


	};
#endif //_GAMESCREENLEVEL1_H