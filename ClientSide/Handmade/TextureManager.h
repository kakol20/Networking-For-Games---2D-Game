#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

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
| 'TextureManager' source files last updated in June 2019 									    |
#==============================================================================================*/

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Singleton.h"

class TextureManager
{

public:

	enum DataType   { FONT_DATA, TEXTURE_DATA };
	enum RemoveType { CUSTOM_DATA, ALL_DATA };

public:

	friend class Singleton<TextureManager>;

public:

	TTF_Font* GetFont(const std::string& mapIndex);
	SDL_Texture* GetTexture(const std::string& mapIndex);

public:

	bool Initialize();
	bool LoadFontFromFile(const std::string& filename, int fontSize, const std::string& mapIndex);
	bool LoadTextureFromFile(const std::string& filename, const std::string& mapIndex);
	void UnloadFromMemory(DataType dataType, RemoveType removeType, const std::string& mapIndex = "");
	void ShutDown();

public:

	void Output();

private:

	TextureManager()  {}
	TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager&);

private:

	std::map<std::string, TTF_Font*> m_fontMap;
	std::map<std::string, SDL_Texture*> m_textureMap;
	
};

typedef Singleton<TextureManager> TheTexture;

#endif