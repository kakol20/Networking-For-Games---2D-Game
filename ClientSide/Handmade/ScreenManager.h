#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

/*==============================================================================================#
|                                                                                               |
| Copyright (c) 2019 Karsten Vermeulen. All rights reserved.                                    |
|                                                                                               |
| All code has been written by Karsten Vermeulen as part of the 'Handmade Lite' game engine,    |
| for the purposes of educating other fellow programmers, programming students and anyone else  |
| wishing to learn about game development, C++ and OOP. The structure of the engine, class      |
| design and overall code is constantly under development.                                      |
|                                                                                               |
| Designed to teach. Made from scratch. Built by hand.  						                |
|																							    |
#===============================================================================================#
|																								|
| If you like 'Handmade Lite' and wish to show your support, if you have any questions about    |
| the project, or if you just want to reach out, please find me on the following channels:      |
|																						        |
| Web: http://www.karstenvermeulen.com														    |
| Facebook: https://www.facebook.com/KarstensCorner								                |
| Twitter: https://twitter.com/KarstensCorner													|
| LinkedIn: https://www.linkedin.com/in/karstenvermeulen                                        |
| GitHub: https://github.com/djkarstenv									                        |
|                                                                                               |
#===============================================================================================#
| 'ScreenManager' source files last updated in June 2019 									    |
#==============================================================================================*/

#include <string>
#include <SDL.h>
#include "Singleton.h"

class ScreenManager
{
public:

	friend class Singleton<ScreenManager>;

public:

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();
	SDL_Point GetScreenSize();

public:

	void SetClearColor(Uint8 r, Uint8 g, Uint8 b);

public:

	bool Initialize(const std::string& windowTitle, int width = 1024,
		int height = 768, bool fullscreen = false);

	void Update();
	void Draw();

	void ShutDown();

private:

	ScreenManager();
	ScreenManager(const ScreenManager&);
	ScreenManager& operator=(const ScreenManager&);

private:

	int m_width;
	int m_height;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};

typedef Singleton<ScreenManager> TheScreen;

#endif