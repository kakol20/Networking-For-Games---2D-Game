#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

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
| 'AudioManager' source files last updated in June 2019 									    |
#==============================================================================================*/

#include <map>
#include <string>
#include <SDL_mixer.h>
#include "Singleton.h"

class AudioManager
{
public:

	enum RemoveType { CUSTOM_AUDIO, ALL_AUDIO };
	enum AudioType { SFX_AUDIO, MUSIC_AUDIO, VOICE_AUDIO };

public:

	friend class Singleton<AudioManager>;

public:

	Mix_Chunk* GetSFXData(const std::string& mapIndex);
	Mix_Music* GetMusicData(const std::string& mapIndex);
	Mix_Music* GetVoiceData(const std::string& mapIndex);

public:

	bool Initialize();
	bool LoadFromFile(const std::string& filename, AudioType audioType, const std::string& mapIndex);
	void UnloadFromMemory(AudioType audioType, RemoveType removeType, const std::string& mapIndex = "");
	void ShutDown();

public:

	void Output();

private:

	AudioManager() {}
	AudioManager(const AudioManager&);
	AudioManager& operator=(const AudioManager&);

private:

	std::map<std::string, Mix_Chunk*> m_sfxDataMap;
	std::map<std::string, Mix_Music*> m_musicDataMap;
	std::map<std::string, Mix_Music*> m_voiceDataMap;
};

typedef Singleton<AudioManager> TheAudio;

#endif