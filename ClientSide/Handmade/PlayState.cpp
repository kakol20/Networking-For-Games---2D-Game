#include <iostream>
#include <time.h>
#include "EndState.h"
#include "Game.h"
#include "InputManager.h"
#include "MenuState.h"
#include "PlayState.h"
#include "TextureManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults
//------------------------------------------------------------------------------------------------------
PlayState::PlayState(GameState* state) : GameState(state)
{
	m_image = nullptr;
}
//------------------------------------------------------------------------------------------------------
//function that creates a new background screen object
//------------------------------------------------------------------------------------------------------
bool PlayState::OnEnter()
{
	m_image = new Background("Assets/Textures/Play.png", "Assets/Audio/Play.ogg");

	m_mainGame.Init();
	return true;
}
//------------------------------------------------------------------------------------------------------
//function that reads key presses, mouse clicks and updates all game objects in scene
//------------------------------------------------------------------------------------------------------
bool PlayState::Update()
{
	//play the background music associated with the image
	//when the state transitions to the next state stop it
	//m_image->PlayMusic();

	m_mainGame.Update();

	//read keyboard state
	KeyState keys = TheInput::Instance()->GetKeyStates();

	//the M key moves to the main menu
	if (keys[SDL_SCANCODE_M])
	{
		//m_image->StopMusic();

		m_mainGame.SetExit(true);
		m_mainGame.CloseSocket();
		m_mainGame.Shutdown();

		m_isActive = m_isAlive = false;
		TheGame::Instance()->ChangeState(new MenuState(this));
	}

	//the Q key moves to the ending state
	if (keys[SDL_SCANCODE_Q])
	{
		//m_image->StopMusic();
		m_mainGame.SetExit(true);
		m_mainGame.CloseSocket();
		m_mainGame.Shutdown();


		m_isActive = m_isAlive = false;
		TheGame::Instance()->ChangeState(new EndState(this));
	}

	return true;
}
//------------------------------------------------------------------------------------------------------
//function that renders the background image and all game objects in scene
//------------------------------------------------------------------------------------------------------
bool PlayState::Draw()
{
	//render the background image
	m_image->Draw();

	m_mainGame.Draw();

	return true;
}
//------------------------------------------------------------------------------------------------------
//function that removes all game objects from memory
//------------------------------------------------------------------------------------------------------
void PlayState::OnExit()
{
	//destroy all individual game objects
	delete m_image;
}