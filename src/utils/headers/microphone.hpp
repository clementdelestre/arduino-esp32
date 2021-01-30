#include <arduinoFFT.h>

#include "utils.hpp"
#include <chrono>

#ifndef MICROPHONE_INCLUDED
#define MICROPHONE_INCLUDED

#define SAMPLES 256           // Must be a power of 2 default: 1024
#define SAMPLING_FREQUENCY 40000 // default: 40000 Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define amplitude 200   

#define MICROPHONE 34

class Microphone {


    private:

        unsigned int sampling_period_us;
        unsigned long microseconds;
        double vReal[SAMPLES];
        double vImag[SAMPLES];
        unsigned long newTime, oldTime;
        int dominant_value;
        arduinoFFT FFT;

        float max_low_frequency;
        float max_high_frequency;
        float max_medium_frequency;

        float percent_low_frequency;
        float percent_high_frequency;
        float percent_medium_frequency;


        TaskHandle_t microphoneTask;
        void startThread();
        static void _startThread(void* parameter);

        bool* running;

        std::chrono::milliseconds calibrationTime;

    public:
        Microphone();
              
        void start();
        void stop();

        float getLowFrequency();
        float getMediumFrequency();
        float getHighFrequency();



};

#endif