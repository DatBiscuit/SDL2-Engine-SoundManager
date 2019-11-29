#include "SoundManager.h"

static void MyAudioCallback(void* userdata, Uint8* streamIn, int length) {
    SoundManager* context = (SoundManager*)userdata;
    context->GenerateSamples(streamIn, length);
}

SoundManager::SoundManager() {
    SDL_AudioSpec spec;

    //TODO: dont hardcode these values
    SDL_zero(spec);
    spec.freq = 44100;
    spec.format = AUDIO_S16SYS;
    spec.channels = 2; //working with stereo audio of 2 channels
    spec.samples = 2048;
    spec.callback = MyAudioCallback;
    spec.userdata = this;

    //TODO handle different specs
    m_device = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
    if(m_device == 0) {
        throw SDL_GetError();
    }
    SDL_PauseAudioDevice(m_device, 0);

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw SDL_GetError();
    }

}

SoundManager::~SoundManager() {
    SDL_CloseAudioDevice(m_device);
}


void SoundManager::PlayAudio(AudioObject& ao) {
    SDL_LockAudioDevice(m_device); //prevents no other thread will effect the audio buffer
    
    // prevents duplicates otherwise it would remove them before adding them
    RemoveAudio(ao); //dont play the same sound twice
    m_playingAudio.push_back(&ao);

    SDL_UnlockAudioDevice(m_device);
}

void SoundManager::PauseAudio(AudioObject& ao) {
    SDL_LockAudioDevice(m_device); //prevents no other thread will effect the audio buffer
    
    // prevents duplicates otherwise it would remove them before adding them
    RemoveAudio(ao); //dont play the same sound twice


    SDL_UnlockAudioDevice(m_device);
}

void SoundManager::StopAudio(AudioObject& ao) {
    SDL_LockAudioDevice(m_device); //prevents no other thread will effect the audio buffer
    
    // prevents duplicates otherwise it would remove them before adding them
    if(RemoveAudio(ao)) { //dont play the same sound twice
        ao.SetPos(0.0);
    }

    SDL_UnlockAudioDevice(m_device);
}

bool SoundManager::RemoveAudio(AudioObject& ao) {
    std::vector<AudioObject*>::iterator it = m_playingAudio.begin();
    std::vector<AudioObject*>::iterator end = m_playingAudio.end();

    for(; it != end; ++it) {
        if(*it == &ao) {
            m_playingAudio.erase(it);
            return true;
        }
    }
    return false;
}

void SoundManager::GenerateSamples(Uint8* streamIn, int streamInLen) {
    size_t streamLen = (size_t)(streamInLen/2); //gets the number of samples which is 2 bytes per sample

    m_stream.reserve(streamLen);
    float* floatStream = *(float**)(&m_stream);

    for(size_t i = 0; i < streamLen; i++) {
        floatStream[i] = 0.0f;
    }

    std::vector<AudioObject*>::iterator it = m_playingAudio.begin();
    std::vector<AudioObject*>::iterator end = m_playingAudio.end();

    for(; it != end; ++it) {
        if(!(*it)->GenerateSamples(floatStream, streamLen)) {
            RemoveAudio(*(*it)); //has no more samples to generate
        }
    }

    Sint16* stream = (Sint16*)streamIn;
    for(size_t i = 0; i < streamLen; i++) {
        float val = floatStream[i];

        if(val > 1.0f) {
            val = 1.0f;
        } else if (val < -1.0f) {
            val = -1.0f;
        }

        stream[i] = (Sint16)(val * 32767);
    }
}

AudioObject* SoundManager::CreateAudioFromFile(const std::string& filePath) {
    return new AudioObject(filePath);
}

void SoundManager::ReleaseAudio(AudioObject* audioData) {
    if(audioData) {
        delete audioData;
    }
}

void SoundManager::playMusic() {
    //if there is no music playing
	if(Mix_PlayingMusic() == 0) {
		//Play the music
        Mix_Music *Background = Mix_LoadMUS("../sounds/test.wav");
		Mix_PlayMusic(Background, -1 );
	}
}