#include "headers/transition.hpp"
#include "../leds/leds_controller.hpp"

TransitionMode::TransitionMode(LedsController* ledsController) : Mode(ledsController){
     this->ledsController = ledsController;
     this->modeLabel = ModeLabel::transition;

     loadTransition();
}

void TransitionMode::startMode(){
     sendModeData();
     loadTransition();
}

void TransitionMode::displayMode(){

     RgbColor color = RgbColor().LinearBlend(this->colors[index], this->colors[index+1], this->progress);

     ledsController->getKaveLeds()->clearTo(color);
     if(ledsController->canShowStairs()){
          ledsController->getStairsLeds()->clearTo(color);
     } else {
          ledsController->getStairsLeds()->clearTo(RgbColor(0));
     }

     progress+=0.01;

     if(this->progress == 1){
          this->progress = 0;
          index++;
     }

     if(index == countTransition){
          index = 0;
     }

     delay(5 + (200-this->speed));
}

void TransitionMode::loadTransition(){
     speed = ledsController->getNVSStorage()->getInt("transition_speed") ?: 50;

     this->countTransition = ledsController->getNVSStorage()->getBlobSize("transition_colors") ?: 0;

     if(countTransition != 0){
          uint8_t colorsData[countTransition];
          ledsController->getNVSStorage()->getBlob("transition_colors", colorsData, countTransition);

          this->colors = {};

          for(int x = 0;x<countTransition;x++){
               this->colors.push_back(RgbColor(colorsData[x]));
          }
     } else {
          this->colors.push_back(RgbColor(0));
          this->colors.push_back(RgbColor(0));
     }

     this->index = 0;   
}

void TransitionMode::sendModeData(){
     
}

