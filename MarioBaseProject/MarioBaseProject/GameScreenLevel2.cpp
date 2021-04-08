#include "GameScreenLevel2.h"
#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include "Character.h"
#include "Collisions.h"
#include "CharacterKoopa.h"







GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	SetUpLevel();
	m_level_map = nullptr;

}

GameScreenLevel2::~GameScreenLevel2()
{
	m_background_texture = nullptr;
	//delete my_character;
	delete mario_Character;
	delete luigi_Character;
	//my_character = nullptr;
	mario_Character = nullptr;
	luigi_Character = nullptr;
	koopa_Character = nullptr;
	coin_Character = nullptr;

	m_pow_block = nullptr;



	//Delete enemies
	m_enemies.clear();
	m_coins.clear();

}

void GameScreenLevel2::Render()
{
	//Draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);


	//Draw the enemies
	for (CharacterKoopa* enemy : m_enemies)
		enemy->Render();
	for (CharacterCoin* coin : m_coins)
		coin->Render();


	mario_Character->Render();
	luigi_Character->Render();
	m_pow_block->Render();
}

void  GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	/*
	 * do the screen shake if required
	 */



	if (m_score == 400)
	{
		gameScreenManager->SetScreenToSwap(SCREEN_WIN);
	}



	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

	if (mario_dead == true)
	{
		cout << mario_dead_timer << endl;
		if (mario_dead_timer <= 0.0)
		{
			gameScreenManager->SetScreenToSwap(SCREEN_GAMEOVER);
		}
		else
		{
			mario_dead_timer -= deltaTime;
		}
	}


	//Update character
	//my_character->Update(deltaTime, e);
	mario_Character->Update(deltaTime, e);
	luigi_Character->Update(deltaTime, e);

	//if (Collisions::Instance()->Circle(mario_Character, luigi_Character))
	//{

	//}
	//Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }
	//if (Collisions::Instance()->Box(mario_Character->GetCollisionBox(),luigi_Character->GetCollisionBox()))
	//{

	//}

	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime, e);

}

void GameScreenLevel2::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
	int enemyIndexToDelete = -1;
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}

}

void GameScreenLevel2::UpdateEnemies(float deltaTime, SDL_Event e)
{


	if (!m_enemies.empty())
	{

		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//flip the koopa when he hits the wall
			if (m_enemies[i]->GetPosition().x + 32 > SCREEN_WIDTH)
				m_enemies[i]->FlipDirection(FACING_LEFT);
			else if (m_enemies[i]->GetPosition().x < 0)
				m_enemies[i]->FlipDirection(FACING_RIGHT);




			//check if the enemy is on the bottom row of the tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is enemy off screen to the left or to the right
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f)) m_enemies[i]->SetAlive(false);
			}

			//now do the update
			m_enemies[i]->Update(deltaTime, e);


			//check to see if the enemy collides with the player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{

			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], mario_Character))
				{

					if (m_enemies[i]->GetInjured() == true)
					{
						m_enemies[i]->SetAlive(false);
						m_score += 100;
						
					}
					else
					{

						if (kill_mario_run == false)
						{
							kill_mario_run = true;
							KillMario();
							cout << "RARST KLARD" << endl;

						}
					}
				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 for each update
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
			//CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		}



	}
}

void GameScreenLevel2::UpdateCoins(float deltaTime, SDL_Event e)
{

	if (!m_coins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < m_coins.size(); i++)
		{

			//now do the update
			m_coins[i]->Update(deltaTime, e);


			//check to see if the enemy collides with the player
			if ((m_coins[i]->GetPosition().y > 300.0f || m_coins[i]->GetPosition().y <= 64.0f) && (m_coins[i]->GetPosition().x < 64.0f || m_coins[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{

			}
			else
			{
				if (Collisions::Instance()->Circle(m_coins[i], mario_Character))
				{
					m_coins[i]->SetAlive(false);
					m_score += 100;
				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_coins[i]->GetAlive())
			{
				coinIndexToDelete = i;
			}
		}

		//remove dead enemies -1 for each update
		if (coinIndexToDelete != -1)
		{
			m_coins.erase(m_coins.begin() + coinIndexToDelete);

		}



	}
}



void GameScreenLevel2::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopa_Character = new CharacterKoopa(m_renderer, "Images/Koopa.png", position, m_level_map, direction, speed);
	m_enemies.push_back(koopa_Character);
}

void GameScreenLevel2::CreateCoin(Vector2D position, FACING direction)
{
	CharacterCoin* coin_Character = new CharacterCoin(m_renderer, "Images/Coin.png", position, m_level_map, direction);
	m_coins.push_back(coin_Character);
}

void GameScreenLevel2::KillMario()
{
	mario_Character->Jump();

	mario_dead = true;
	//int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	//									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	//									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	//									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	//									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	//									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	//									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	//									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	//									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	//									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	//									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	//									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	//								{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };
	//
	//clear any old maps
	//if (m_level_map != nullptr)
	//{
	//	delete m_level_map;
	//}

	//set the new one
	//m_level_map = new LevelMap(map);






}




void GameScreenLevel2::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(mario_Character->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			//collided while jumping
			if (mario_Character->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				mario_Character->CancelJump();

			}
		}
	}

}




bool GameScreenLevel2::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB2.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	SetLevelMap();


	//set up player character
	//my_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64, 330));
	mario_Character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	luigi_Character = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);


	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;
	mario_dead_timer = 1.5f;
	mario_dead = false;
	kill_mario_run = false;


	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(150, 164), FACING_LEFT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 164), FACING_LEFT, KOOPA_SPEED);
	CreateCoin(Vector2D(325, 164), FACING_RIGHT);
	CreateCoin(Vector2D(175, 164), FACING_RIGHT);
	CreateCoin(Vector2D(120, 32), FACING_RIGHT);
	CreateCoin(Vector2D(380, 32), FACING_RIGHT);



	return true;
}

void GameScreenLevel2::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);
}



