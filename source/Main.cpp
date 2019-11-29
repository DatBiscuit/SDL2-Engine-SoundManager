#include <time.h>
#include "Rendering.h"
#include "SoundManager.h"
#include <SDL_mixer.h>

#define FILE_PATH "../sounds/test.wav"
#define SOUND2 "../sounds/doorslam.wav"

int main(int argc, char *args[])
{
	SDL_Init(SDL_INIT_AUDIO);


	SoundManager* device = new SoundManager();
	SoundManager* device2 = new SoundManager();
	//TODO: condense for creating audio object
	AudioObject* data = device->CreateAudioFromFile(FILE_PATH);
	data->m_sampleInfo.volume = 1.0;
	AudioObject sound(data->m_sampleInfo, data);

	AudioObject* slamdata = device2->CreateAudioFromFile(SOUND2);
	slamdata->m_sampleInfo.volume = 2.0;
	AudioObject slam(slamdata->m_sampleInfo, slamdata);

	// device->playMusic();

	char in = 0;
	while(in != 'q') {
		std::cin >> in;
		switch(in) {
			case 'a': 
				device->PlayAudio(sound);
				break;
			case 's':
				device->PauseAudio(sound);
				break;
			case 'd':
				device->StopAudio(sound);
				break;
			//TODO: be able to play music overtop each other
			case 'f':
				device2->PlayAudio(slam);
			default:
				break;
		}
	}

	device->ReleaseAudio(data);
	delete device;

	SDL_Quit();
	return 0;
}