#ifndef ANIMATION_H
#define ANIMATION_H

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
| 'Animation' source files last updated in June 2019     									    |
#==============================================================================================*/

#include "Sprite.h"

class Animation : public Sprite
{
public:

	Animation();
	virtual ~Animation() {}

public:

	bool IsAnimationDead();
	bool& IsAnimationLooping();
	void SetAnimationVelocity(float velocity);

public:

	virtual void Draw(int xPosition = 0, int yPosition = 0,
		double angle = 0.0, FlipType flipType = NO_FLIP);

protected:

	bool m_isAnimationDead;
	bool m_isAnimationLoopFinal;
	bool m_isAnimationLooping;

	double m_timeElapsed;
	float m_animationVelocity;
};

#endif