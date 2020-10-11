#include "ArcadeScene.h"

#include "Screen.h"
#include "AARectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Color.h"
#include "Star.h"
#include "Line2D.h"
#include "GameController.h"
#include <iostream>

#include <algorithm>


ArcadeScene::ArcadeScene()
{

}
void ArcadeScene::Init()
{
	ButtonAction action;
	action.key = GameController::ActionKey();
	action.action = [](uint32_t dt, InputState state)
	{
		if(GameController::IsPressed(state))
		{
			std::cout << "Action button was pressed!" << std::endl;
		}
	};
	mGameController.AddInputActionForKey(action);
	//we have something for the keys, now lets add something for the mouse events..

	MouseButtonAction mouseAction;
	mouseAction.mouseButton = GameController::LeftMouseButton();
	mouseAction.mouseInputAction = [](InputState state, const MousePosition& position)
	{
		if(GameController::IsPressed(state))
		{
			std::cout << "Left Mouse button pressed!" << std::endl;
		}
	};

	mGameController.AddMouseButtonAction(mouseAction);

	mGameController.SetMouseMovedAction( [] (const MousePosition& mousePosition){
		std::cout << "Mouse position x: " << mousePosition.xPos << ", y: " << mousePosition.yPos << std::endl;
	});
}
void ArcadeScene::Update(uint32_t dt)
{

}
void ArcadeScene::Draw(Screen& theScreen)
{

	std::vector<Star> stars = Star::createStars(10, theScreen.Width(), theScreen.Height() / 3);

	std::sort(stars.begin(), stars.end(), [](Star s1, Star s2)
	{
		return s1.getSideLen() > s2.getSideLen();
	});

	float xOffset = 0;
	float padding = 10;
	for(Star& star : stars)
	{
		star.moveTo(Vec2D(xOffset + padding + star.getSideLen() ,25));
		xOffset += padding + star.getSideLen();
	}

	for(Star star : stars)
	{
		theScreen.Draw(star, Color::Yellow(), true, Color::Yellow());
	}
}
const std::string& ArcadeScene::GetSceneName() const
{
	static std::string sceneName = "Arcade Scene";
	return sceneName;
}
std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game)
{
	switch(game)
	{
	case TETRIS:
	{

	}
	break;

	case BREAK_OUT:
	{

	}
	break;

	case ASTEROIDS:
	{

	}
	break;

	case PACMAN:
	{

	}
	break;

	default:
	{

	}
	break;
	}

	return nullptr;
}
