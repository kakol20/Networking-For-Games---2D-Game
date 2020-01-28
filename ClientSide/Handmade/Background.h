#ifndef BACKGROUND_H
#define BACKGROUND_H

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
| 'Background' source files last updated in July 2019 									        |
#==============================================================================================*/

#include "Audio.h"
#include "GameObject.h"
#include "Sprite.h"

class Background : public GameObject
{
public:

	Background(const std::string& imageFilename, const std::string& audioFilename);
	virtual ~Background();

public:

	virtual void Update() {}
	virtual bool Draw();

public:

	void PlayMusic();
	void StopMusic();

protected:

	bool m_isPlaying;
	std::string m_imageName;
	std::string m_audioName;

	Audio m_music;
	Sprite m_image;
};

#endif