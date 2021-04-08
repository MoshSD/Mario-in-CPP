#include "GameScreenMenu.h"

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	SetUpLevel();
}

GameScreenMenu::~GameScreenMenu()
{
	m_background_texture = nullptr;
	m_background_texture_play = nullptr;
	m_background_texture_quit = nullptr;
}

void GameScreenMenu::Render()
{
	if(currentBackground == BACKGROUND_DEFAULT)
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	else if(currentBackground == BACKGROUND_PLAY)
	m_background_texture_play->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	else if (currentBackground == BACKGROUND_QUIT)
	m_background_texture_quit->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{

	if (m_current_background_num == 0)
	{
		currentBackground = BACKGROUND_DEFAULT;
	}
	else if (m_current_background_num == 1)
	{
		currentBackground = BACKGROUND_PLAY;
	}
	else if (m_current_background_num == 2)
	{
		currentBackground = BACKGROUND_QUIT;
	}



	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			m_current_background_num--;
			if (m_current_background_num <= 0)
			{
				m_current_background_num = 2;
			}
			break;
		case SDLK_DOWN:
			m_current_background_num++;
			if (m_current_background_num > 2)
			{
				m_current_background_num = 1;
			}
			break;
		case SDLK_RETURN:
			if (m_current_background_num == 2)
			{
				gameScreenManager->SetQuit(true);
			}
			else if (m_current_background_num == 1)
			{
				gameScreenManager->SetScreenToSwap(SCREEN_LEVEL1);
			}
			break;
		}
		break;
	default:;
	}




}

bool GameScreenMenu::SetUpLevel()
{
	//load background texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/MarioTitleNoCursor.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	//load the play background
	m_background_texture_play = new Texture2D(m_renderer);
	if (!m_background_texture_play->LoadFromFile("Images/MarioTitlePlayCursor.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	//load the quit background
	m_background_texture_quit = new Texture2D(m_renderer);
	if (!m_background_texture_quit->LoadFromFile("Images/MarioTitleQUitCursor.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}


	currentBackground = BACKGROUND_DEFAULT;
	m_background_yPos = 0.0f;
	m_current_background_num = 0;



	return true;
}
