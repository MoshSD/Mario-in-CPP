#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Commons.h"
#include "constants.h"
#include "Character.h"
#include "CharacterLuigi.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include <vector>


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
	SDL_Renderer* m_renderer;
	Texture2D* m_background_texture;
	Character* my_character;
	CharacterMario* mario_Character;
	CharacterLuigi* luigi_Character;
	CharacterKoopa* koopa_Character;
	CharacterCoin* coin_Character;
	
	bool SetUpLevel();
	bool m_screenshake;
	bool mario_dead;
	bool kill_mario_run;


	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	float m_koopa_timer;
	float mario_dead_timer;

	void SetLevelMap();
	void DoScreenShake();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position, FACING direction);
	void KillMario();



	int m_score = 0;





	LevelMap* m_level_map;
	PowBlock* m_pow_block;

	vector<CharacterKoopa*> m_enemies;
	vector<CharacterCoin*> m_coins;

protected:

	};
#endif //_GAMESCREENLEVEL1_H