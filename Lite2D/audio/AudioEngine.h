#ifndef __AUDIOENGINE__
#define __AUDIOENGINE__

#include "../base/Ref.h"

#include "../3party/fmod/fmod.hpp"




class DLL AudioEngine :public Ref
{
public:
	static AudioEngine*getInstance();

	virtual void playBackgroundMusic(const std::string &file, bool loop = true) = 0;
	virtual void pauseBackgroundMusic()=0;
	virtual void resumeBackgroundMusic() = 0;
	virtual void stopBackgroundMusic() = 0;

	virtual void setBackgroundVolume(float _volume)=0;





	virtual void playEffect(const std::string &file) = 0;
	virtual void stopAllEffects() = 0;


protected:



};


#include <unordered_map>

class   AudioEngineFMOD :public AudioEngine
{
public:

	void playBackgroundMusic(const std::string &file ,bool loop = true) override;
	void playEffect(const std::string &file)override;

	virtual void pauseBackgroundMusic()override;
	virtual void resumeBackgroundMusic()override;

	virtual void setBackgroundVolume(float _volume)override;

	void stopBackgroundMusic() override;
	void stopAllEffects() override;
	~AudioEngineFMOD();

private:
	std::unordered_map<std::string, FMOD_SOUND*> _map_effects;
//	std::unordered_map< FMOD_SOUND*,> _map_effects;




	FMOD_SOUND *_sound_back = 0;
	FMOD_CHANNEL*_channel_back = 0;
	FMOD_CHANNEL *_channl_effect=0;
	FMOD_SOUND*getEffect(const std::string &file);

	AudioEngineFMOD();
	friend class AudioEngine;


	//	FMOD_SOUND
};








#endif


