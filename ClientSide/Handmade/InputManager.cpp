#include "InputManager.h"
#include "ScreenManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values 
//------------------------------------------------------------------------------------------------------
InputManager::InputManager()
{

	m_isXClicked = false;
	m_isKeyPressed = false;

	m_cursor = nullptr;
	m_keyStates = nullptr;
	
	m_mouseWheel = { 0, 0 };
	m_mouseMotion = { 0, 0 };
	m_mousePosition = { 0, 0 };

	m_leftButtonState = UP;
	m_rightButtonState = UP;
	m_middleButtonState = UP;
	
}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag stating if X has been clicked
//------------------------------------------------------------------------------------------------------
bool InputManager::IsXClicked()
{

	return m_isXClicked;

}
//------------------------------------------------------------------------------------------------------
//predicate function that returns flag stating if a key has been pressed
//------------------------------------------------------------------------------------------------------
bool InputManager::IsKeyPressed()
{

	return m_isKeyPressed;

}
//------------------------------------------------------------------------------------------------------
//predicate function that checks if mouse cursor collides with passed box bound
//------------------------------------------------------------------------------------------------------
bool InputManager::IsMouseColliding(const AABB& bound)
{

	//create a temporary bounding box to represent mouse cursor
	AABB tempBound;

	//set mouse cursor bounds of 1x1 based on mouse position
	tempBound.SetPosition(m_mousePosition.x, m_mousePosition.y);
	tempBound.SetDimension(1, 1);

	//return flag based on if mouse collides with bound
	return tempBound.IsColliding(bound);

}
//------------------------------------------------------------------------------------------------------
//predicate function that checks if mouse cursor collides with passed sphere bound
//------------------------------------------------------------------------------------------------------
bool InputManager::IsMouseColliding(const Sphere& bound)
{

	//create a temporary sphere bound to represent mouse cursor
	Sphere tempBound;

	//set mouse cursor radius of 1 based on mouse position
	tempBound.SetPosition(m_mousePosition.x, m_mousePosition.y);
	tempBound.SetRadius(1);

	//return flag based on if mouse collides with bound
	return tempBound.IsColliding(bound);

}
//------------------------------------------------------------------------------------------------------
//getter function that returns pointer to array of key states
//------------------------------------------------------------------------------------------------------
KeyState InputManager::GetKeyStates()
{

	return m_keyStates;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns motion value of mouse wheel movement
//------------------------------------------------------------------------------------------------------
SDL_Point InputManager::GetMouseWheel()
{

	return m_mouseWheel;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns motion value of mouse movement
//------------------------------------------------------------------------------------------------------
SDL_Point InputManager::GetMouseMotion()
{

	return m_mouseMotion;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns position of mouse
//------------------------------------------------------------------------------------------------------
SDL_Point InputManager::GetMousePosition()
{

	return m_mousePosition;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns state of left mouse button
//------------------------------------------------------------------------------------------------------
InputManager::ButtonState InputManager::GetLeftButtonState()
{

	return m_leftButtonState;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns state of right mouse button
//------------------------------------------------------------------------------------------------------
InputManager::ButtonState InputManager::GetRightButtonState()
{

	return m_rightButtonState;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns state of middle mouse button
//------------------------------------------------------------------------------------------------------
InputManager::ButtonState InputManager::GetMiddleButtonState()
{

	return m_middleButtonState;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns string input entered via keyboard
//------------------------------------------------------------------------------------------------------
const std::string& InputManager::GetInput()
{

	return m_input;

}
//------------------------------------------------------------------------------------------------------
//setter function that places mouse cursor at passed position
//------------------------------------------------------------------------------------------------------
void InputManager::SetMousePosition(int x, int y)
{

	SDL_WarpMouseInWindow(TheScreen::Instance()->GetWindow(), x, y);

}
//------------------------------------------------------------------------------------------------------
//setter function that creates a system mouse cursor 
//------------------------------------------------------------------------------------------------------
void InputManager::SetMouseCursorType(CursorType cursorType)
{

	//first destroy old cursor object from memory
	SDL_FreeCursor(m_cursor);

	//based on type of cursor value passed, create mouse cursor using SDL ID flag value 
	m_cursor = SDL_CreateSystemCursor(SDL_SystemCursor(cursorType));
	
	//use cursor pointer to assign cursor to SDL
	SDL_SetCursor(m_cursor);

}
//------------------------------------------------------------------------------------------------------
//setter function that enables, disables, shows or hides the mouse cursor
//------------------------------------------------------------------------------------------------------
void InputManager::SetMouseCursorState(CursorState cursorEnabled, CursorState cursorVisible)
{

	//if mouse cursor is enabled then check if it's visible  
	//and display the cursor accordingly, and keep the mouse 
	//cursor within the window border as long as it's enabled
	if (cursorEnabled)
	{
		
		if (cursorVisible)
		{
			SDL_ShowCursor(1);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		else
		{
			SDL_ShowCursor(0);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}

	}

	//if mouse cursor is disabled then hide it and free it from the window border
	else
	{
		SDL_ShowCursor(0);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
	
}
//------------------------------------------------------------------------------------------------------
//function that processes all keyboard and mouse events
//------------------------------------------------------------------------------------------------------
void InputManager::Update()
{

	//variable to store SDL event data
	SDL_Event events;

	//reset window quitting flag 
	m_isXClicked = false;

	//reset mouse wheel and mouse motion so that it's processed from scratch
	m_mouseWheel  = { 0, 0 };
	m_mouseMotion = { 0, 0 };	

	//store state of keyboard in array
	m_keyStates = SDL_GetKeyboardState(nullptr);

	//check for events on SDL event queue and keep this
	//loop running until all events have been processed
	while(SDL_PollEvent(&events))
	{
			
		//check which type of event occurred and process accordingly
		switch(events.type)
		{
		
			//top right X on game window has been clicked
			case SDL_QUIT:
			{
				m_isXClicked = true;
				break;
			}
		
			//a key is released 
			case SDL_KEYUP: 
			{
				m_isKeyPressed = false;
				break;
			}
		
			//a key is pressed so here we store all 
			//entered keyboard keys into a string for 
			//possible text input in the client code
			case SDL_KEYDOWN:
			{
				
				m_isKeyPressed = true;

				//erase the last character if BACKSPACE is pressed
				if (events.key.keysym.sym == SDLK_BACKSPACE && m_input.size() > 0)
				{
					m_input.erase(m_input.end() - 1);
				}
				
				//otherwise enter all keys into the string except the ENTER key!
				else if(events.key.keysym.sym != SDLK_RETURN)
				{
					m_input += events.key.keysym.sym;
				}

				break;

			}

			//the mouse was moved so set the 
			//position and mouse motion value
			case SDL_MOUSEMOTION:
			{
				m_mousePosition.x = events.motion.x;
				m_mousePosition.y = events.motion.y;
				m_mouseMotion.x = events.motion.xrel;
				m_mouseMotion.y = events.motion.yrel;
				break;
			}

			//the mouse wheel was moved 
			case SDL_MOUSEWHEEL:
			{
				m_mouseWheel.x = events.wheel.x;
				m_mouseWheel.y = events.wheel.y;
			}

			//a mouse button was clicked or released
			case SDL_MOUSEBUTTONUP: 
			case SDL_MOUSEBUTTONDOWN:
			{
				
				//set position of mouse
				m_mousePosition.x = events.motion.x;
				m_mousePosition.y = events.motion.y;
				
				//temporarily store button state for assigning below
				ButtonState state = ((events.button.state == SDL_PRESSED) ? DOWN : UP);

				//based on which of the three mouse buttons was pressed 
				//or released, assign flag to button's state variable
				switch(events.button.button)
				{
				
					case SDL_BUTTON_LEFT:
					{
						m_leftButtonState = state;
						break;
					}
				
					case SDL_BUTTON_MIDDLE:
					{
						m_middleButtonState = state;
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						m_rightButtonState = state;
						break;
					}
				
					break;

				}

				break;

			}

		}

	}

}
//------------------------------------------------------------------------------------------------------
//function that flushes all characters from string input container
//------------------------------------------------------------------------------------------------------
void InputManager::ClearInput()
{

	m_input.clear();

}