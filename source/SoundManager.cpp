#include "SoundManager.h"

SoundManager::SoundManager() { }

SoundManager::~SoundManager() {
    
}

bool SoundManager::Init() {
    return InitMusic() && InitSound();
}

bool SoundManager::InitMusic() {
	bool success = true;

    std::string songName;
    Mix_Music *addMusic = NULL;

    std::ifstream s((musicDir + "songList.txt").c_str());
    //while loop
    while(s >> songName) {
	    //load music
        std::string nameOfSong = musicDir + songName + fileFormat;
        addMusic = Mix_LoadMUS(nameOfSong.c_str());
        if(addMusic == NULL) {
            std::cout << "Failed to load beat music! Error: " << Mix_GetError() << std::endl;
            success = false;
        }
        //add the music to the map
        MusicMap.insert({songName, addMusic});
    }

    return success;
}

bool SoundManager::InitSound() {
    //loading success flag
    bool success = true;
    std::string soundName;
    Mix_Chunk *addSound = NULL;

    std::ifstream s((soundDir + "soundList.txt").c_str());
    //while loop
    while(s >> soundName) {
	    //load music
        std::string nameOfSound = soundDir + soundName + fileFormat;
        addSound = Mix_LoadWAV(nameOfSound.c_str());
        if(addSound == NULL) {
            std::cout << "Failed to load beat music! Error: " << Mix_GetError() << std::endl;
            success = false;
        }
        //add the music to the map
        SoundMap.insert({soundName, addSound});
    }

    return success;
}

void SoundManager::playMusic(std::string songName) {
    //if there is no music playing
	if(Mix_PlayingMusic() == 0) {
		//Play the music
		Mix_PlayMusic( MusicMap[songName], -1 );
	}
}

void SoundManager::playSound(std::string soundName, int loops) {
    Mix_PlayChannel(-1, SoundMap[soundName], loops);
}

void SoundManager::stopMusic() {
    Mix_HaltMusic();
}

void SoundManager::pauseMusic() {
    Mix_PauseMusic();
}

void SoundManager::resumeMusic() {
    Mix_ResumeMusic();
}
