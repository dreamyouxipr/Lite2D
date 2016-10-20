#include"AudioEngine.h"




AudioEngine*AudioEngine::getInstance()
{
	static AudioEngine*ins = nullptr;

	if (ins == nullptr)
	{
		ins = new AudioEngineFMOD;
	}
	return ins;


}

FMOD_SYSTEM* _system;


AudioEngineFMOD::AudioEngineFMOD()
{
	FMOD_System_Create(&_system);
	FMOD_System_Init(_system, 32, FMOD_INIT_NORMAL, 0);



}

void AudioEngineFMOD::playBackgroundMusic(const std::string &file, bool loop)
{

	FMOD_System_CreateSound(_system, file.c_str(), FMOD_SOFTWARE, 0, &_sound_back);

	FMOD_System_PlaySound(_system, FMOD_CHANNEL_FREE, _sound_back, 0, 0);

	if (loop)
	{
		FMOD_Channel_SetMode(_channel_back, FMOD_LOOP_NORMAL);
		FMOD_Channel_SetLoopCount(_channel_back, -1);

	}


}


void AudioEngineFMOD::playEffect(const std::string &file)
{
	FMOD_System_PlaySound(_system, FMOD_CHANNEL_FREE, getEffect(file), 0, &_channl_effect);
}



void AudioEngineFMOD::stopAllEffects()
{


}

void AudioEngineFMOD::stopBackgroundMusic()
{
	if (_sound_back && _channel_back)
	{
		//FMOD_Channel_Stop(_channel_back);
		FMOD_Sound_Release(_sound_back);
		_sound_back = nullptr;
		_channel_back = nullptr;
	}

}



FMOD_SOUND* AudioEngineFMOD::getEffect(const std::string &file)
{
	auto iter = _map_effects.find(file);

	if (iter == _map_effects.end())
	{
		// not cache  add to cache

		FMOD_SOUND *sound;
		FMOD_System_CreateSound(_system, file.c_str(), FMOD_SOFTWARE, 0, &sound);

		_map_effects.insert(std::pair<std::string, FMOD_SOUND*>(file, sound));

		return sound;

	}

	return iter->second;
}

AudioEngineFMOD::~AudioEngineFMOD()
{
	FMOD_System_Close(_system);
	FMOD_System_Release(_system);
}



void AudioEngineFMOD::pauseBackgroundMusic()
{

	if (_sound_back && _channel_back)
	{
		FMOD_Channel_SetPaused(_channel_back, true);
	}


}


void AudioEngineFMOD::resumeBackgroundMusic()
{

	if (_sound_back && _channel_back)
	{
		FMOD_Channel_SetPaused(_channel_back, false);
	}

}


void AudioEngineFMOD::setBackgroundVolume(float _volume)
{
	if (_sound_back && _channel_back)
	{
		FMOD_Channel_SetVolume(_channel_back, _volume);
	}

}



