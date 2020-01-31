#include "EndState.h"
#include "Game.h"
#include "PlayState.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
EndState::EndState(GameState* state) : GameState(state)
{
	m_menu = nullptr;
	m_image = nullptr;
}
//------------------------------------------------------------------------------------------------------
//function that creates a new background screen object and menu
//------------------------------------------------------------------------------------------------------
bool EndState::OnEnter()
{
	m_menu = new MainMenu;
	m_menu->SetMenuText("PLAY AGAIN");
	m_menu->SetMenuText("QUIT GAME");

	m_image = new Background("Assets/Textures/End.png", "Assets/Audio/End.ogg");

	return true;
}
//------------------------------------------------------------------------------------------------------
//function that reads key presses, mouse clicks and updates all game objects in scene
//------------------------------------------------------------------------------------------------------
bool EndState::Update()
{
	//play the background music associated with the image
	//when the state transitions to the next state stop it
	//m_image->PlayMusic();

	//update the main menu to determine which menu choice was made
	m_menu->Update();

	//if player wants to play again then return to the main playing state
	if (m_menu->GetMenuOption() == PLAY)
	{
		m_image->StopMusic();
		m_isActive = m_isAlive = false;
		TheGame::Instance()->ChangeState(new PlayState(this));
	}

	//if player chose to exit the game then quit altogether
	if (m_menu->GetMenuOption() == QUIT)
	{
		m_image->StopMusic();
		m_isActive = m_isAlive = false;
	}

	return true;
}
//------------------------------------------------------------------------------------------------------
//function that renders the background image and menu
//------------------------------------------------------------------------------------------------------
bool EndState::Draw()
{
	m_image->Draw();
	m_menu->Draw();

	return true;
}
//------------------------------------------------------------------------------------------------------
//function that removes splash screen background object and menu from memory
//------------------------------------------------------------------------------------------------------
void EndState::OnExit()
{
	delete m_image;
	delete m_menu;
}