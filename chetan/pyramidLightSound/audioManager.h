#pragma once

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <al.h>
#include <alc.h>

#include "lib/cWaves/CWaves.h"

class AudioManager
{
    public:
        static ALboolean initialize();
        static ALboolean loadWaveAudio(const char* filePath, ALuint bufferId);

        static void setListenerPosition(float x, float y, float z);
        static void setListenerVelocity(float x, float y, float z);
        static ALfloat AudioManager::getBufferLength(ALuint buffer);
        static void cleanUp();

    private:
        AudioManager();
        AudioManager(const AudioManager&);
        ~AudioManager();

        static AudioManager *audioManager;

        FILE *logFile = NULL;
        CWaves *waveLoader = NULL;

        ALCdevice *device = NULL;
        ALCcontext *context = NULL;

        void log(const char* message, ...);
};
