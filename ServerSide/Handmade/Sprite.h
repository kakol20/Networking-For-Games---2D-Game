#ifndef SPRITE_H
#define SPRITE_H

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
| 'Sprite' source files last updated in June 2019     									        |
#==============================================================================================*/

#include <string>
#include <SDL.h>

class Sprite
{
public:

	enum FlipType { NO_FLIP, HORIZONTAL, VERTICAL };

public:

	Sprite();
	virtual ~Sprite() {}

public:

	void SetTextureCel(int column, int row);
	void SetTexture(const std::string& mapIndex);
	void SetSpriteDimension(int width, int height);
	void SetTextureDimension(int column, int row, int width, int height);

public:

	virtual void Draw(int xPosition = 0, int yPosition = 0,
		double angle = 0.0, FlipType flipType = NO_FLIP);

protected:

	void BlitSprite(int xPosition, int yPosition, double angle, FlipType flipType);

protected:

	int m_textureIndex;

	SDL_Point m_textureCel;
	SDL_Point m_spriteDimension;

	SDL_Texture* m_texture;
	SDL_Rect m_textureDimension;
};

#endif