#include "headers/microphone.hpp"

Microphone::Microphone(){
    sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
    FFT = arduinoFFT();

    max_low_frequency = 1;
    max_high_frequency = 1;
    max_medium_frequency = 1;

    percent_low_frequency = 0;
    percent_high_frequency = 0;
    percent_medium_frequency = 0;

    running = new bool(false);

    calibrationTime = Utils::getTimeSinceEpoch();
}


void Microphone::startThread(){
    bool calibration = false;
    calibrationTime = Utils::getTimeSinceEpoch()-std::chrono::seconds(24);

    while(*running){
        float low_frequency = 0;
        float high_frequency = 0;
        float medium_frequency = 0;

        for (int i = 0; i < SAMPLES; i++) {
            newTime = micros();
            vReal[i] = analogRead(MICROPHONE); 
            vImag[i] = 0;
            while ((micros() - newTime) < sampling_period_us) { /* do nothing to wait */ }
        }

        FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

        //for (int i = 2; i < (SAMPLES/2); i++){ 
        for (int i = 2; i < 60; i++){ 
            int val = vReal[i];

            if(i<=8 && val > 700){
                low_frequency+=val;
            } else if(i>8 && val > 300) {
                high_frequency+=val;
            }

            if(val > 500){
                medium_frequency+=val;
            }
 
        }

        if(calibrationTime+std::chrono::seconds(15)<Utils::getTimeSinceEpoch()){ 
            if(!calibration){
                //start calibration mic
                max_low_frequency = 1;
                max_high_frequency = 1;
                max_medium_frequency = 1;
            }

            calibration = true;
            //todo
            if(low_frequency>max_low_frequency) max_low_frequency = low_frequency;
            if(high_frequency>max_high_frequency) max_high_frequency = high_frequency;
            if(medium_frequency>max_medium_frequency) max_medium_frequency = medium_frequency;

            if(calibrationTime+std::chrono::seconds(18)<Utils::getTimeSinceEpoch()){
                //stop calibration mic
                calibrationTime = Utils::getTimeSinceEpoch();
                calibration = false;
            }
        }
        //todo
        percent_low_frequency = (low_frequency/max_low_frequency > 1) ? 1 : low_frequency/max_low_frequency;
        percent_high_frequency = (high_frequency/max_high_frequency > 1) ? 1 : high_frequency/max_high_frequency;
        percent_medium_frequency = (medium_frequency/max_medium_frequency > 1) ? 1 : medium_frequency/max_medium_frequency;

        //Serial.println(percent_low_frequency);
        delay(5);
    }

    vTaskDelete(microphoneTask);

}

float Microphone::getLowFrequency(){
    return percent_low_frequency;
}

float Microphone::getMediumFrequency(){
    return percent_medium_frequency;
}

float Microphone::getHighFrequency(){
    return percent_high_frequency;
}

void Microphone::_startThread(void* parameter){
    Microphone* microphone = (Microphone*) parameter;
    microphone->startThread();
}


void Microphone::start(){
    *running = true;
    xTaskCreatePinnedToCore(
        _startThread, /* Function to implement the task */
        "LED_KAVE_MICROPHONE", /* Name of the task */
        10000,  /* Stack size in words */
        this,  /* Task input parameter */
        1,  /* Priority of the task */
        &microphoneTask,  /* Task handle. */
        1); /* Core where the task should run */
}

void Microphone::stop(){
    *running = false;
}

