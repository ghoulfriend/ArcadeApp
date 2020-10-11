#include "App.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "ArcadeScene.h"
#include <cassert>
#include "BreakOut.h"
#include "Tetris.h"
#include "GameScene.h"

App& App::Singleton()
{
	static App theApp;
	return theApp;
}
bool App::Init(uint32_t width, uint32_t height, uint32_t mag)
{
	mnoptrWindow = mScreen.Init(width,height, mag);

	std::unique_ptr<ArcadeScene> arcadeScene = std::make_unique<ArcadeScene>();

	PushScene(std::move(arcadeScene));


	//TEMPORARY
//	{
//		std::unique_ptr<BreakOut> breakoutGame = std::make_unique<BreakOut>();
//
//		std::unique_ptr<GameScene> breakoutScene = std::make_unique<GameScene>(std::move(breakoutGame));
//
//		PushScene(std::move(breakoutScene));
//	}
	//TEMPORARY
	{
		std::unique_ptr<Tetris> tetrisGame = std::make_unique<Tetris>();

		std::unique_ptr<GameScene> tetrisScene = std::make_unique<GameScene>(std::move(tetrisGame));

		PushScene(std::move(tetrisScene));
	}

	return mnoptrWindow != nullptr;
}
void App::Run()
{
	if( mnoptrWindow )
	{

		bool running = true;


		uint32_t lastTick = SDL_GetTicks();
		uint32_t currentTick = lastTick;
		uint32_t dt = 10;
		uint32_t accumulator = 0;


		mInputController.Init([&running](uint32_t dt, InputState state){
			running = false;
		});

		while (running)
		{

			currentTick = SDL_GetTicks();
			uint32_t frameTime = currentTick - lastTick;
			if( frameTime > 300 )
			{
				frameTime = 300;
			}
			lastTick = currentTick;
			accumulator += frameTime;

			//Input
			mInputController.Update(dt);

			Scene* topScene = App::TopScene();
			assert(topScene && "Why don't we have a scene?");

			if(topScene)
			{
				//Update
				while(accumulator >= dt)
				{
					//update current scene by dt
					topScene->Update(dt);
					accumulator -= dt;
				}

				//Render
				topScene->Draw(mScreen);
			}

			mScreen.SwapScreens();
		}
	}

}

void App::PushScene(std::unique_ptr<Scene> scene)//consume function basically Move Semantics takes ownership
{
	assert(scene && "Don't push nullptr");
	if(scene)
	{
		scene->Init();
		mInputController.SetGameController(scene->GetGameController());
		mSceneStack.emplace_back(std::move(scene));//this moves it over -- scene is an l-value must cast to r-value
		SDL_SetWindowTitle(mnoptrWindow, TopScene()->GetSceneName().c_str());
	}
}
void App::PopScene()
{
	if(mSceneStack.size() > 1)
	{
		mSceneStack.pop_back();
	}

	if(TopScene())
	{
		//reset game controller after pop
		mInputController.SetGameController(TopScene()->GetGameController());
		SDL_SetWindowTitle(mnoptrWindow, TopScene()->GetSceneName().c_str());
	}

}
Scene* App::TopScene()
{
	if(mSceneStack.empty())
	{
		return nullptr;
	}

	return mSceneStack.back().get();//get gets unique ptr
}

const std::string& App::GetBasePath()
{
	static std::string basePath = SDL_GetBasePath();
	return basePath;
}
