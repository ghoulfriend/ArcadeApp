#include "GameController.h"
#include "InputAction.h"
#include <SDL2/SDL.h>
#include <iostream>

GameController::GameController() : mMouseMovedAction(nullptr) //standard game controller wont have mousemovedaction set initially.
{

}
const InputAction& GameController::GetActionForKey(InputKey key)
{
	for(const auto& buttonAction: mButtonActions)
	{
		if(key == buttonAction.key)
		{
			return buttonAction.action;
		}
	}

	return [](uint32_t, InputState){};
}
void GameController::AddInputActionForKey(const ButtonAction& buttonAction)
{
	//add a bunttonAction to our vector
	mButtonActions.push_back(buttonAction);
}
void GameController::ClearAll()
{
	mButtonActions.clear();//clears vector
}

bool GameController::IsPressed(InputState state)
{
	return state == SDL_PRESSED;
}
bool GameController::IsReleased(InputState state)
{
	return state == SDL_RELEASED;
}
InputKey GameController::ActionKey()//example A fires a missle
{
	return static_cast<InputKey>(SDLK_a);
}
InputKey GameController::CancelKey()
{
	return static_cast<InputKey>(SDLK_s); // s key
}
InputKey GameController::LeftKey()
{
	return static_cast<InputKey>(SDLK_LEFT); // SDLKey
}
InputKey GameController::RightKey()
{
	return static_cast<InputKey>(SDLK_RIGHT);
}
InputKey GameController::UpKey()
{
	return static_cast<InputKey>(SDLK_UP);
}
InputKey GameController::DownKey()
{
	return static_cast<InputKey>(SDLK_DOWN);
}
MouseInputAction GameController::GetMouseButtonActionForMouseButton(MouseButton button)
{
	//mMouseButtonActions were set up in Init()
	for(const auto& buttonAction: mMouseButtonActions)
	{
		if(button == buttonAction.mouseButton)
		{
			return buttonAction.mouseInputAction;
		}
	}

	return [](InputState state, const MousePosition& pos){
	};
}

void GameController::AddMouseButtonAction(const MouseButtonAction& mouseButtonAction)
{
	mMouseButtonActions.push_back(mouseButtonAction);
}
MouseButton GameController::LeftMouseButton()
{
	return static_cast<MouseButton>(SDL_BUTTON_LEFT);
}
MouseButton GameController::RightMouseButton()
{
	return static_cast<MouseButton>(SDL_BUTTON_RIGHT);
}
