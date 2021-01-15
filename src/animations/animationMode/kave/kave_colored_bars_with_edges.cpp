#include "headers/kave_colored_bars_with_edges.hpp"
#include "../../../leds/leds_controller.hpp"

KaveColoredBarsWithEdges::KaveColoredBarsWithEdges(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  

    refreshMs = std::chrono::milliseconds(75);    

    barCurrentColor = Utils::getRandomColor();
    barTargetColor = Utils::getRandomColor();

    colorProgress = 0;
}

void KaveColoredBarsWithEdges::animationContent(){    
  
    ledsController->getKaveLeds()->clearTo(0);

    RgbColor updateEdgesColor = RgbColor().LinearBlend(edgesCurrentColor, edgesTargetColor, colorProgress);
    RgbColor updateBarColor = RgbColor().LinearBlend(barCurrentColor, barTargetColor, colorProgress).Dim(max(255*microphone->getLowFrequency(), (float) 20));

    for(int x = 0; x<ledsController->getKaveLeds()->getLength()/8; x++){
        RgbColor localColor =  updateEdgesColor.Dim(255-255*x/(ledsController->getKaveLeds()->getLength()/8));
        ledsController->getKaveLeds()->setPixelColor(x, localColor);
        ledsController->getKaveLeds()->setPixelColor(ledsController->getKaveLeds()->getLength() - x, localColor);
    }

    //Le nombre de barres à afficher
    int numBars = 5*microphone->getMediumFrequency();
    for(int bar = 0; bar<numBars;bar++){
        //To determine the position of the bar, excluding the edges
        int initialLed = ledsController->getKaveLeds()->getLength()/8 + random(ledsController->getKaveLeds()->getLength()*3/4-lengthBar);    

        for(int x = 0; x<lengthBar;x++){
            ledsController->getKaveLeds()->setPixelColor(initialLed + x, updateBarColor);
        }

    }

    colorProgress+=0.05;
    
    if(colorProgress > 1){
        edgesCurrentColor = edgesTargetColor;
        edgesTargetColor = Utils::getFixedRandomColor();

        barCurrentColor = barTargetColor;
        barTargetColor = getColorWithDefault(Utils::getRandomColor());

        colorProgress = 0;
    }

    ledsController->getKaveLeds()->show();

}
