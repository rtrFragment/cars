#include "audioManager.h"
#include "lib/logger/logger.h"

AudioManager* AudioManager::audioManager = nullptr;
ALboolean AudioManager::initializationCompleted = AL_FALSE;

AudioManager::AudioManager() {}
AudioManager::AudioManager(const AudioManager&) {}

ALboolean AudioManager::initialize()
{
    if(audioManager == nullptr)
    {
        AudioManager::initializationCompleted = AL_FALSE;
        audioManager = new AudioManager();

        audioManager->waveLoader = new CWaves();

        if(audioManager->waveLoader == NULL)
        {
            logError("Not able to create wave loader.\n");
        }

        audioManager->device = alcOpenDevice(NULL);

        if(audioManager->device)
        {
            logInfo("Audio device created: %s\n", alcGetString(audioManager->device, ALC_DEVICE_SPECIFIER));
            audioManager->context = alcCreateContext(audioManager->device, NULL);

            if(audioManager->context)
            {
                alcMakeContextCurrent(audioManager->context);
                initializationCompleted = AL_TRUE;
                logInfo("Context created.\n");
            }
            else
            {
                alcCloseDevice(audioManager->device);
                logError("Cannot create context.\n");
            }
        }
        else
        {
            logError("Cannot create audio device.\n");
        }
    }

    return initializationCompleted;
}

ALboolean AudioManager::loadWaveAudio(const char* filePath, ALuint bufferId)
{
    ALboolean loaded = AL_FALSE;
	WAVEID waveId = 0;
	ALint dataSize = 0;
    ALint frequency = 0;
	ALenum bufferFormat;
	ALchar *data = NULL;

    if(audioManager->waveLoader)
    {
        WAVERESULT loadWaveResult = audioManager->waveLoader->LoadWaveFile(filePath, &waveId);

        if(SUCCEEDED(loadWaveResult))
        {
            WAVERESULT waveSizeResult = audioManager->waveLoader->GetWaveSize(waveId, (unsigned long *)&dataSize);
            WAVERESULT waveDataResult = audioManager->waveLoader->GetWaveData(waveId, (void **)&data);
            WAVERESULT waveFrequencyResult = audioManager->waveLoader->GetWaveFrequency(waveId, (unsigned long *)&frequency);
            WAVERESULT waveBufferFormatResult = audioManager->waveLoader->GetWaveALBufferFormat(waveId, &alGetEnumValue, (unsigned long *)&bufferFormat);

            logInfo("Buffer format: %d\n", bufferFormat);

            if(SUCCEEDED(waveSizeResult) && SUCCEEDED(waveDataResult) && SUCCEEDED(waveFrequencyResult) && SUCCEEDED(waveBufferFormatResult))
            {
                // Clear any errors
                alGetError();

                // Load the data to buffer
                alBufferData(bufferId, bufferFormat, data, dataSize, frequency);

                ALenum error =  alGetError();

                if(error == AL_NO_ERROR)
                {
                    loaded = AL_TRUE;
                    logInfo("Wave file loaded: %s\n", filePath);
                }
                else
                {
                    logError("Not able to load audio data, error: %d, file: %s\n", error, filePath);
                }
            }
            else
            {
                logError("Not able to load wav data\n");
            }

            audioManager->waveLoader->DeleteWaveFile(waveId);
        }
        else
        {
            logError("Not able to load audio file '%s'\n", filePath);
        }
    }

    return loaded;
}

void AudioManager::setListenerPosition(float x, float y, float z)
{
    alListener3f(AL_POSITION, x, y, z);
}

void AudioManager::setListenerVelocity(float x, float y, float z)
{
    alListener3f(AL_VELOCITY, x, y, z);
}

ALfloat AudioManager::getBufferLength(ALuint buffer)
{
    ALint size;
    ALint bits;
    ALint channels;
    ALint freq;

    alGetBufferi(buffer, AL_SIZE, &size);
    alGetBufferi(buffer, AL_BITS, &bits);
    alGetBufferi(buffer, AL_CHANNELS, &channels);
    alGetBufferi(buffer, AL_FREQUENCY, &freq);

    ALenum error =  alGetError();

    if(error != AL_NO_ERROR)
    {
        return 0.0f;
    }

    return (ALfloat)((ALuint)size / channels / (bits / 8)) / (ALfloat)freq;
}

void AudioManager::cleanUp()
{
    if(audioManager != nullptr)
    {
        delete audioManager;
        audioManager = nullptr;
    }
}

AudioManager::~AudioManager()
{
    ALCcontext *pContext = alcGetCurrentContext();

	if(pContext == audioManager->context)
    {
        alcMakeContextCurrent(NULL);
    }

	alcDestroyContext(audioManager->context);
	alcCloseDevice(audioManager->device);

    audioManager->context = NULL;
    audioManager->device = NULL;

    if (audioManager->waveLoader)
	{
		delete audioManager->waveLoader;
		audioManager->waveLoader = NULL;
        logInfo("Audio device destroyed.\n");
	}
}
