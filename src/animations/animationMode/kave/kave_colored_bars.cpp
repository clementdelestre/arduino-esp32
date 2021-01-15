#include "headers/kave_colored_bars.hpp"
#include "../../../leds/leds_controller.hpp"

KaveColoredBars::KaveColoredBars(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  

    refreshMs = std::chrono::milliseconds(75);    

    barCurrentColor = Utils::getRandomColor();
    barTargetColor = Utils::getRandomColor();

    colorProgress = 0;
}

void KaveColoredBars::animationContent(){    
  
    ledsController->getKaveLeds()->clearTo(0);
    RgbColor updateBarColor = RgbColor().LinearBlend(barCurrentColor, barTargetColor, colorProgress).Dim(max(255*microphone->getLowFrequency(), (float) 20));

    //Le nombre de barres à afficher
    int numBars = 6*microphone->getLowFrequency() +1;
    for(int bar = 0; bar<numBars;bar++){

        //To determine the position of the bar, excluding the edges
        int initialLed = random(ledsController->getKaveLeds()->getLength()-lengthBar);    

        for(int x = 0; x<lengthBar;x++){
            ledsController->getKaveLeds()->setPixelColor(initialLed + x, updateBarColor);
        }

    }

    colorProgress+=0.05;
    
    if(colorProgress > 1){
        barCurrentColor = barTargetColor;
        barTargetColor = getColorWithDefault(Utils::getRandomColor());

        colorProgress = 0;
    }

    ledsController->getKaveLeds()->show();

}
