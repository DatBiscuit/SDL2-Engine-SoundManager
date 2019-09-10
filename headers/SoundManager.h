#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <map>
#include <fstream>

class SoundManager {

public:

    std::string soundDir = "../sounds/";
    std::string musicDir = "../music/";
    std::string fileFormat = ".wav";

    std::map<std::string, Mix_Music*> MusicMap;
    std::map<std::string, Mix_Chunk*> SoundMap;


    // //The sound effects that will be used
    // Mix_Chunk *gScratch = NULL;
    // Mix_Chunk *gHigh = NULL;
    // Mix_Chunk *gMedium = NULL;
    // Mix_Chunk *gLow = NULL;

    SoundManager();
    ~SoundManager();
    bool Init();
    bool InitMusic();
    bool InitSound();
    void playMusic(std::string songName);
    void playSound(std::string soundName, int loops);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();

};

