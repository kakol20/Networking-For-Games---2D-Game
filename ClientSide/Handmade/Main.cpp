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
| 'Main' source file last updated in July 2019 									                |
#==============================================================================================*/

//include SDL main header file to prevent
//main lib conflicts in Release mode
#include <SDL.h>
#include "Game.h"
#include "MenuState.h"

//------------------------------------------------------------------------------------------------------
//main function that processes everything
//------------------------------------------------------------------------------------------------------
int main(int argc, char* args[])
{
	//initialize the game
	if (!(TheGame::Instance()->Initialize("Multiplayer Tag", 1280, 720)))
	{
		return 0;
	}

	//create the first state to be used in the game
	TheGame::Instance()->AddState(new MenuState(nullptr));

	//run the game
	if (!TheGame::Instance()->Run())
	{
		return 0;
	}

	//close down the game
	TheGame::Instance()->ShutDown();

	//end application
	return 0;
}