#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include "Character.h"
#include "Collisions.h"








GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	m_level_map = nullptr;
	
}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;
	//delete my_character;
	delete mario_Character;
	delete luigi_Character;
	//my_character = nullptr;
	mario_Character = nullptr;
	luigi_Character = nullptr;

}

void GameScreenLevel1::Render() 
{
	//Draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	//my_character->Render();
	mario_Character->Render();
	luigi_Character->Render();
}

void  GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
{
	//Update character
	//my_character->Update(deltaTime, e);
	mario_Character->Update(deltaTime, e);
	luigi_Character->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(mario_Character, luigi_Character))
	{
		cout << "Circle hit!" << endl;
	}
	//Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }
	if (Collisions::Instance()->Box(mario_Character->GetCollisionBox(),luigi_Character->GetCollisionBox()))
	{
		cout << "Box hit!" << endl;
	}

}

bool GameScreenLevel1::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	SetLevelMap();


	//set up player character
	//my_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64, 330));
	mario_Character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	luigi_Character = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);


	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
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


