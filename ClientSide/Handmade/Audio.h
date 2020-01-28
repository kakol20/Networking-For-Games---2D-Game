#ifndef AUDIO_H
#define AUDIO_H

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
| 'Audio' source files last updated in June 2019     									        |
#==============================================================================================*/

#include <string>
#include <SDL_mixer.h>

class Audio
{
public:

	enum AudioType { MUSIC_AUDIO, VOICE_AUDIO };
	enum LoopType { PLAY_ONCE = 1, PLAY_ENDLESS = -1 };

public:

	Audio();

public:

	void SetVolume(int volume);
	void SetAudio(const std::string& mapIndex, AudioType audioType);

public:

	bool Play(LoopType loopType = PLAY_ONCE);
	void Pause();
	void Resume();
	void Stop();

private:

	Mix_Music* m_audio;
};

#endif