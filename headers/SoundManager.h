#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include "AudioObject.h"
#include <string>
#include <cmath>

class SoundManager {

public:

        SoundManager();
        ~SoundManager();

        void GenerateSamples(Uint8* streamIn, int streamInLen);
        void PlayAudio(AudioObject& ao);
        void PauseAudio(AudioObject& ao);
        void StopAudio(AudioObject& ao);
        void playMusic();

       SDL_AudioSpec wavSpec;
       Uint8* wavStart;
       Uint32 wavLength;

       //SDL_AudioDeviceID device;
    //    AudioData audio;

        // void MyAudioCallback(void* userdata, Uint8* stream, int streamLength);

       AudioObject* CreateAudioFromFile(const std::string& filePath);

       void ReleaseAudio(AudioObject* audioData);
       
    //    bool loadwav();
    //    void freewav();
    //    bool createdevice();
    //    void closedevice();





private:
    SDL_AudioDeviceID m_device;
    std::vector<float> m_stream;
    std::vector<AudioObject*> m_playingAudio; //list of audio currently being played

    bool RemoveAudio(AudioObject& ao);

    SoundManager(SoundManager& other) { (void)other; }
    void operator=(const SoundManager& other) { (void)other; }


};

