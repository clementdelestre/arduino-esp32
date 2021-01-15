#include "headers/utils.hpp"

int Utils::maxLuminosity = 150;

std::chrono::milliseconds Utils::getTimeSinceEpoch(){
    return std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );
}

RgbColor Utils::getRandomColor(){
    return RgbColor(random(maxLuminosity), random(maxLuminosity), random(maxLuminosity));
}

RgbColor Utils::getFixedRandomColor(){
    RgbColor colors[] = { 
        RgbColor(maxLuminosity, 0, 0), 
        RgbColor(0, maxLuminosity, 0), 
        RgbColor(0, 0, maxLuminosity), 

        RgbColor(maxLuminosity, maxLuminosity, 0), 
        RgbColor(maxLuminosity, 0, maxLuminosity), 
        RgbColor(0, maxLuminosity, maxLuminosity)
    };

    return colors[random(6)];
}

int Utils::kaveNumAnimation = 17;
RgbColor Utils::cineDefaultColor = RgbColor(255, 0, 100);

