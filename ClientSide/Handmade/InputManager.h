#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

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
| 'InputManager' source files last updated in June 2019 									    |
#==============================================================================================*/

#include <string>
#include <SDL.h>
#include "AABB.h"
#include "Singleton.h"
#include "Sphere.h"

typedef const Uint8* KeyState;

class InputManager
{

public:

	enum ButtonState { UP, DOWN };
	enum CursorState { ON = 1, OFF = 0, SHOW = 1, HIDE = 0 };
	enum CursorType  { ARROW, IBEAM, WAIT, CROSSHAIR, WAIT_ARROW, NO = 10, HAND = 11 };

public:

	friend class Singleton<InputManager>;

public:

	bool IsXClicked();
	bool IsKeyPressed();
	bool IsMouseColliding(const AABB& bound);
	bool IsMouseColliding(const Sphere& bound);

public:

	KeyState GetKeyStates();

	SDL_Point GetMouseWheel();
	SDL_Point GetMouseMotion();
	SDL_Point GetMousePosition();
	
	ButtonState GetLeftButtonState();
	ButtonState GetRightButtonState();
	ButtonState GetMiddleButtonState();
		
	const std::string& GetInput();

	void SetMousePosition(int x, int y);
	void SetMouseCursorType(CursorType cursorType = ARROW);
	void SetMouseCursorState(CursorState cursorEnabled = ON, CursorState cursorVisible = SHOW);

public:

	void Update();
	void ClearInput();

private:

	InputManager();
	InputManager(const InputManager&);
	InputManager& operator=(const InputManager&);

private:

	bool m_isXClicked;
	bool m_isKeyPressed;
	std::string m_input;

	KeyState m_keyStates;
	SDL_Cursor* m_cursor;

	SDL_Point m_mouseWheel;
	SDL_Point m_mouseMotion;
	SDL_Point m_mousePosition;
	
	ButtonState m_leftButtonState;
	ButtonState m_rightButtonState;
	ButtonState m_middleButtonState;
	
};

typedef Singleton<InputManager> TheInput;

#endif