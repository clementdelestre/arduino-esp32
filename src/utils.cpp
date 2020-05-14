#include "headers/utils.hpp"

std::chrono::milliseconds Utils::getTimeSinceEpoch(){
    return std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );
}

RgbColor Utils::getRandomColor(){
    return RgbColor(random(255), random(255), random(255));
}

RgbColor Utils::getFixedRandomColor(){
    int max_color = 255;
    RgbColor colors[] = { 
        RgbColor(max_color, 0, 0), 
        RgbColor(0, max_color, 0), 
        RgbColor(0, 0, max_color), 

        RgbColor(max_color, max_color, 0), 
        RgbColor(max_color, 0, max_color), 
        RgbColor(0, max_color, max_color)
    };

    return colors[random(6)];
}

int Utils::kaveNumAnimation = 17;
RgbColor Utils::cineDefaultColor = RgbColor(255, 0, 100);

