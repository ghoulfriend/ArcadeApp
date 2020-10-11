//All the game scene does is refer to the game
//Uses game in constructor, Inits, Updates, and draws
#include "GameScene.h"
#include <iostream>


GameScene::GameScene(std::unique_ptr<Game> optrGame) : mGame(std::move(optrGame))
{

}
void GameScene::Init()
{
	mGame->Init(mGameController);
}
void GameScene::Update(uint32_t dt)
{
	mGame->Update(dt);
	std::cout << "Game Updating" << std::endl;
}
void GameScene::Draw(Screen& screen)
{
	mGame->Draw(screen);
	std::cout << "Game Drawing" << std::endl;
}

const std::string& GameScene::GetSceneName() const
{
	return mGame->GetName();
}


