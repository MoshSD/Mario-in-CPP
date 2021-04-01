#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "constants.h"
#include "Character.h"
#include "CharacterLuigi.h"
#include "CharacterMario.h"
#include "LevelMap.h"
#include "PowBlock.h"



class PowBlock;
class Character;
class Texture2D;






class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();


private:
	Texture2D* m_background_texture;
	Character* my_character;
	CharacterMario* mario_Character;
	CharacterLuigi* luigi_Character;
	
	bool SetUpLevel();
	bool m_screenshake;

	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	void SetLevelMap();
	void DoScreenShake();

	LevelMap* m_level_map;
	PowBlock* m_pow_block;


	};
#endif //_GAMESCREENLEVEL1_H