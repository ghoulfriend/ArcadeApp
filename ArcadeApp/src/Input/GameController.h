#ifndef INPUT_GAMECONTROLLER_H_
#define INPUT_GAMECONTROLLER_H_

//a lot of these are to hide the SDL implementation details
#include "InputAction.h"
#include <vector> // all of our mappings

class GameController
{
public:
	GameController();
	const InputAction& GetActionForKey(InputKey key);
	void AddInputActionForKey(const ButtonAction& buttonAction);
	void ClearAll();

	static bool IsPressed(InputState state);
	static bool IsReleased(InputState state);
	static InputKey ActionKey();//example A fires a missle
	static InputKey CancelKey();
	static InputKey LeftKey();
	static InputKey RightKey();
	static InputKey UpKey();
	static InputKey DownKey();

	inline const MouseMovedAction GetMouseMovedAction() {return mMouseMovedAction;}
	inline void SetMouseMovedAction(const MouseMovedAction& mouseMovedAction) {mMouseMovedAction = mouseMovedAction;}

	MouseInputAction GetMouseButtonActionForMouseButton(MouseButton button);
	void AddMouseButtonAction(const MouseButtonAction& mouseButtonAction);

	static MouseButton LeftMouseButton();
	static MouseButton RightMouseButton();


private:
	std::vector<ButtonAction> mButtonActions;
	std::vector<MouseButtonAction> mMouseButtonActions;

	MouseMovedAction mMouseMovedAction;
};



#endif /* INPUT_GAMECONTROLLER_H_ */
