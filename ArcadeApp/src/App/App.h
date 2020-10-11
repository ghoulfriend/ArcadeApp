#ifndef APP_APP_H_
#define APP_APP_H_

#include "Screen.h"
#include <stdint.h>
#include <vector>
#include <memory>
#include "Scene.h"
#include "InputController.h"

static const int SCREEN_WIDTH = 224;
static const int SCREEN_HEIGHT = 288;
static const int MAGNIFICATION = 3;

struct SDL_Window;

class App
{
public:
	static App& Singleton();
	bool Init(uint32_t width, uint32_t height, uint32_t mag);
	void Run();//main loop for everything

	inline uint32_t Width() const {return mScreen.Width();}
	inline uint32_t Height() const {return mScreen.Height();}

	void PushScene(std::unique_ptr<Scene> scene);//consume function basically Move Semantics takes ownership
	void PopScene();
	Scene* TopScene(); //current scene

	static const std::string& GetBasePath();
private:
	Screen mScreen;
	SDL_Window* mnoptrWindow;

	std::vector<std::unique_ptr<Scene>> mSceneStack;
	InputController mInputController;
};


#endif /* APP_APP_H_ */
