#include <iostream>
#include "App.h"


using namespace std;



int main(int argc, char * argv[])
{
	if(App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION))
	{
		App::Singleton().Run();
	}

    return 0;
}
