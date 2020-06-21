#include "headers/kave_colored_bars_with_edges.hpp"
#include "../../../headers/leds_controller.hpp"

KaveColoredBarsWithEdges::KaveColoredBarsWithEdges(LedsController* ledsController, Microphone* microphone, int flag) : AnimationConstructor(ledsController, microphone, flag){  

    refreshMs = std::chrono::milliseconds(75);    

    barCurrentColor = Utils::getRandomColor();
    barTargetColor = Utils::getRandomColor();

    colorProgress = 0;
}

void KaveColoredBarsWithEdges::animationContent(){    
  
    ledsController->getKaveLeds()->ClearTo(0);

    RgbColor updateEdgesColor = RgbColor().LinearBlend(edgesCurrentColor, edgesTargetColor, colorProgress);
    RgbColor updateBarColor = RgbColor().LinearBlend(barCurrentColor, barTargetColor, colorProgress).Dim(max(255*microphone->getLowFrequency(), (float) 20));

    for(int x = 0; x<ledsController->getKaveLeds()->PixelCount()/8; x++){
        RgbColor localColor =  updateEdgesColor.Dim(255-255*x/(ledsController->getKaveLeds()->PixelCount()/8));
        ledsController->getKaveLeds()->SetPixelColor(x, localColor);
        ledsController->getKaveLeds()->SetPixelColor(ledsController->getKaveLeds()->PixelCount() - x, localColor);
    }

    //Le nombre de barres à afficher
    int numBars = 5*microphone->getMediumFrequency();
    for(int bar = 0; bar<numBars;bar++){
        //To determine the position of the bar, excluding the edges
        int initialLed = ledsController->getKaveLeds()->PixelCount()/8 + random(ledsController->getKaveLeds()->PixelCount()*3/4-lengthBar);    

        for(int x = 0; x<lengthBar;x++){
            ledsController->getKaveLeds()->SetPixelColor(initialLed + x, updateBarColor);
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

    ledsController->getKaveLeds()->Show();

}
