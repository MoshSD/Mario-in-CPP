#include "GameScreenYouWin.h"

GameScreenYouWin::GameScreenYouWin(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_renderer = renderer;
	SetUpLevel();
}

GameScreenYouWin::~GameScreenYouWin()
{
	m_background_texture = nullptr;
	m_background_texture_scores = nullptr;
	m_background_texture_menu = nullptr;
}

void GameScreenYouWin::Render()
{
	if (currentBackground == BACKGROUND_DEFAULT)
		m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	else if (currentBackground == BACKGROUND_SCORES)
		m_background_texture_scores->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	else if (currentBackground == BACKGROUND_MENU)
		m_background_texture_menu->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

}

void GameScreenYouWin::Update(float deltaTime, SDL_Event e)
{
	if (m_current_background_num == 0)
	{
		currentBackground = BACKGROUND_DEFAULT;
	}
	else if (m_current_background_num == 1)
	{
		currentBackground = BACKGROUND_SCORES;
	}
	else if (m_current_background_num == 2)
	{
		currentBackground = BACKGROUND_MENU;
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
			if (m_current_background_num == 1)
			{
				cout << "here is where scores would be shown" << endl;
			}
			else if (m_current_background_num == 2)
			{
				gameScreenManager->SetScreenToSwap(SCREEN_MENU);
			}
			break;
		}
		break;
	default:;
	}


}

bool GameScreenYouWin::SetUpLevel()
{
	//load background texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/YouWinDefault.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	//load the play background
	m_background_texture_scores = new Texture2D(m_renderer);
	if (!m_background_texture_scores->LoadFromFile("Images/YouWinScoresCursor.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	//load the quit background
	m_background_texture_menu = new Texture2D(m_renderer);
	if (!m_background_texture_menu->LoadFromFile("Images/YouWinMenuCursor.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}


	currentBackground = BACKGROUND_DEFAULT;
	m_background_yPos = 0.0f;
	m_current_background_num = 0;



	return true;
}
