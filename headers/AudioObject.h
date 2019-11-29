#ifndef AUDIO_OBJECT_INCLUDED_H
#define AUDIO_OBJECT_INCLUDED_H
#include <SDL.h>
#include <SDL_mixer.h>
#include <cstddef>
#include <string>

class AudioObject {

public:

    struct SampleInfo {
        double volume;
    };

    // struct AudioData {
    //     Uint8* pos;
    //     Uint32 length;
    // };

    SampleInfo m_sampleInfo;

    AudioObject(const SampleInfo& info, AudioObject* data);
    AudioObject(const std::string& fileName);
    ~AudioObject();

    bool GenerateSamples(float* stream, size_t streamLength);
    size_t GenerateSamples(float* stream, size_t streamLength, 
			size_t pos, const SampleInfo& info);
    void SetPos(double pos);
    size_t GetAudioLength();

private:

    AudioObject* data;
    size_t m_audioPos;
    size_t m_audioLength;

    Uint8* m_pos;
    Uint8* m_start;
    Uint8* m_end;
    // Uint32 m_length;

    size_t PosToAbsolutePos(double pos);


};


#endif