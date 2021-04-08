#include "GameScreenManager.h"







GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	isQuitting = false;
	m_renderer = renderer;
	ChangeScreen(startScreen);

}



GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;

}

void GameScreenManager::SetScreenToSwap(SCREENS new_screen)
{
	newscreen = new_screen;
}

void GameScreenManager::Render()
{
	m_current_screen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	
	m_current_screen->Update(deltaTime, e);

	if (newscreen != SCREEN_NONE)
	{
		ChangeScreen(newscreen);
		newscreen = SCREEN_NONE;
	}

}


void GameScreenManager::ChangeScreen(SCREENS new_screen)
{


	//Clear up old screen
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}

	GameScreenLevel1* m_level1Screen;
	GameScreenLevel2* m_level2Screen;
	GameScreenMenu* m_menuScreen;
	GameScreenOver* m_gameOverScreen;
	GameScreenYouWin* m_gameWinScreen;

	switch (new_screen)
	{

	case SCREEN_LEVEL1:
		cout << "e" << endl;
		m_level1Screen = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)m_level1Screen;
		m_level1Screen = nullptr;
		break;

	case SCREEN_MENU:
		cout << "o" << endl;
		m_menuScreen = new GameScreenMenu(m_renderer);
		m_current_screen = (GameScreen*)m_menuScreen;
		m_menuScreen = nullptr;
		break;

	case SCREEN_GAMEOVER:
		cout << "Game over" << endl;
		m_gameOverScreen = new GameScreenOver(m_renderer);
		m_current_screen = (GameScreen*)m_gameOverScreen;
		m_gameOverScreen = nullptr;
		break;

	case SCREEN_LEVEL2:
		cout << "Level 2" << endl;
		m_level2Screen = new GameScreenLevel2(m_renderer);
		m_current_screen = (GameScreen*)m_level2Screen;
		m_level2Screen = nullptr;
		break;

	case SCREEN_WIN:
		cout << "You win" << endl;
		m_gameWinScreen = new GameScreenYouWin(m_renderer);
		m_current_screen = (GameScreen*)m_gameWinScreen;
		m_gameWinScreen = nullptr;
		break;

	default:
		break;
	}


	m_current_screen->PassManager(this);


}