#include "audioManager.h"
#include "../logger/logger.h"

AudioManager::AudioManager()
{
    waveLoader = new CWaves();

    if(waveLoader == NULL)
    {
        logError("Not able to create wave loader.");
    }
}

ALboolean AudioManager::initialize()
{
    ALboolean initializationCompleted = AL_FALSE;
    device = alcOpenDevice(NULL);

    if(device)
    {
        logInfo("Audio device created: %s\n", alcGetString(device, ALC_DEVICE_SPECIFIER));
        context = alcCreateContext(device, NULL);

        if(context)
        {
            alcMakeContextCurrent(context);
            initializationCompleted = AL_TRUE;
            logInfo("Context created.\n");
        }
        else
        {
            alcCloseDevice(device);
            logError("Cannot create context.\n");
        }
    }
    else
    {
        logError("Cannot create audio device.\n");
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

    if(waveLoader)
    {
        WAVERESULT loadWaveResult = waveLoader->LoadWaveFile(filePath, &waveId);

        if(SUCCEEDED(loadWaveResult))
        {
            WAVERESULT waveSizeResult = waveLoader->GetWaveSize(waveId, (unsigned long *)&dataSize);
            WAVERESULT waveDataResult = waveLoader->GetWaveData(waveId, (void **)&data);
            WAVERESULT waveFrequencyResult = waveLoader->GetWaveFrequency(waveId, (unsigned long *)&frequency);
            WAVERESULT waveBufferFormatResult = waveLoader->GetWaveALBufferFormat(waveId, &alGetEnumValue, (unsigned long *)&bufferFormat);

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
                    logInfo("Wave file loaded: %s", filePath);
                }
                else
                {
                    logError("Not able to load audio data, error: %d, file: %s", error, filePath);
                }
            }
            else
            {
                logError("Not able to load wav data\n");
            }

            waveLoader->DeleteWaveFile(waveId);
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

void AudioManager::cleanUp()
{
    ALCcontext *pContext = alcGetCurrentContext();

	if(pContext == context)
    {
        alcMakeContextCurrent(NULL);
    }

	alcDestroyContext(context);
	alcCloseDevice(device);

    context = NULL;
    device = NULL;

    if (waveLoader)
	{
		delete waveLoader;
		waveLoader = NULL;
        logInfo("Audio device destroyed.\n");
	}
}

AudioManager::~AudioManager()
{
    cleanUp();
}
