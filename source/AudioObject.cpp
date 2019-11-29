#include "AudioObject.h"


//TODO: pass some type of variable to get the audio length
AudioObject::AudioObject(const SampleInfo& info, AudioObject* data) : 
    m_audioPos(0), 
    m_sampleInfo(info), 
    data(data),
    m_audioLength(data->GetAudioLength()),
    m_pos(data->m_pos),
    m_start(data->m_start),
    m_end(data->m_end) {}

AudioObject::AudioObject(const std::string& fileName) {
    
    SDL_AudioSpec wavSpec;
    Uint8* wavStart;
    Uint32 wavLength;

    if(SDL_LoadWAV(fileName.c_str(), &wavSpec, &wavStart, &wavLength) == NULL) {
        throw fileName;
    }
    
    m_pos = wavStart;
    // m_length = wavLength;
    m_start = wavStart;
    m_end = m_start + wavLength;
}

AudioObject::~AudioObject() {
    SDL_FreeWAV(m_start);
}


//TODO: give m_audioPos and set that equal to some audiodata that will generate samples
bool AudioObject::GenerateSamples(float* stream, size_t streamLength) {
    m_audioPos = GenerateSamples(stream, streamLength, m_audioPos, m_sampleInfo);

    if(m_audioPos == (size_t)-1) {
        m_audioPos = 0;
        return false;
    }
    return true;
}

void AudioObject::SetPos(double pos) {
    if(pos < 0.0) {
        pos = 0.0;
    } else if (pos > 1.0) {
        pos = 1.0;
    }

    m_audioPos = PosToAbsolutePos(pos);
}

size_t AudioObject::PosToAbsolutePos(double pos) {
    return (size_t)(pos * m_audioLength);
}

size_t AudioObject::GetAudioLength() {
    return (size_t)(m_end - m_start);
}

size_t AudioObject::GenerateSamples(float* stream, size_t streamLength, 
	size_t pos, const SampleInfo& info) {
        //TODO: handle not hard coding pitch
        float pitch = 1.0f;
        m_pos = m_start + pos;

        if(m_pos >= m_end || m_pos < m_start) {
            return (size_t)-1;
        }

        Uint32 length = (Uint32)streamLength;
        Uint32 lengthLeft = (Uint32)((m_end - m_pos)/pitch);

        length = (length > lengthLeft ? lengthLeft : length);

        Sint16* samples = (Sint16*)m_pos;
        float sampleIndex = 0;

        float factor = (float)info.volume*1.0f/32768;
        for(Uint32 i = 0; i < length; i++) {
            stream[i] = (samples[(size_t)sampleIndex]) * factor; //conversion factor
            sampleIndex += pitch;
        }

        m_pos = (Uint8*)(samples + (size_t)sampleIndex);
        // m_length -= (length*2);
        return (size_t)(m_pos - m_start);
}