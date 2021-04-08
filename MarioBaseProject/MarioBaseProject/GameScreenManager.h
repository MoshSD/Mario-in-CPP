#pragma once
#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenMenu.h"
#include "GameScreenOver.h"
#include "GameScreenYouWin.h"


class GameScreen;
class GameScreenLevel1;
class GameScreenLevel2;
class GameScreenMenu;
class GameScreenOver;
class GameScreenYouWin;


 
class GameScreenManager
{
	private:
		SDL_Renderer* m_renderer;
		GameScreen* m_current_screen;
		bool isQuitting = false;

		SCREENS newscreen = SCREEN_NONE;
	public:

		GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
		~GameScreenManager();





		void SetScreenToSwap(SCREENS new_screen);
		void Render();
		void Update(float deltaTime, SDL_Event e);
		void ChangeScreen(SCREENS new_screen);
		void SetQuit(bool setQuit) { isQuitting = setQuit; }
		bool Quitting() { return isQuitting; }


};

