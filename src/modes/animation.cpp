#include "headers/animation.hpp"

#include "../headers/leds_controller.hpp"

AnimationMode::AnimationMode(LedsController* ledsController) : Mode(ledsController){
     this->ledsController = ledsController;
     this->modeLabel = ModeLabel::animations;
     this->microphone = new Microphone();
     currenKavetList = AnimationKaveListLabel::ALL;

     keepAnimation = false;
     initAnimTime = Utils::getTimeSinceEpoch();

     stairsRandomAnim = false;

     setStairsAnim(0);
     setAnimation(selectNewKaveAnimation());
}


void AnimationMode::displayMode(){

     if(initAnimTime+durationAnim<Utils::getTimeSinceEpoch() && !keepAnimation){        
        nextAnimation();     
     }

     currentKaveAnimation->displayAnimation();


     if(ledsController->canShowStairs() && isStairsDisplayed){
          currentStairsAnimation->displayAnimation();
     } else if(ledsController->canShowStairs() && !isStairsDisplayed){
          currentStairsAnimation->init();
          currentStairsAnimation->displayAnimation();
          isStairsDisplayed = true;
     } else if(!ledsController->canShowStairs() && isStairsDisplayed){
          isStairsDisplayed = false;
          ledsController->getStairsLeds()->ClearTo(0);
          ledsController->getStairsLeds()->Show();
     }
     

     delay(1);
}

void AnimationMode::startMode(){
     sendModeData();
     microphone->start();
     currentStairsAnimation->init();
}

void AnimationMode::stopMode(){
     microphone->stop();
}

void AnimationMode::sendModeData(){
     ledsController->getWifiManager()->sendAllClientData(Flags::A_KEEP_ANIMATION, keepAnimation ? 1 : 0, 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::A_TYPE_ANIMATION, currenKavetList, 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::SENSOR_STAIRS, ledsController->getUseStairsSensor() ? 1 : 0, 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::A_STAIRS_RANDOM_ANIM, stairsRandomAnim ? 1 : 0, 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::A_STAIRS_CURRENT_ANIM, currentStairsAnimation->getFlag(), 0, 0);
}

int AnimationMode::selectNewKaveAnimation(){
     int index = rand() % allListsKave[currenKavetList].size();
     return allListsKave[currenKavetList][index];
}

void AnimationMode::setAnimation(int kaveAnimation){

     initAnimTime = Utils::getTimeSinceEpoch();

     durationAnim = std::chrono::duration_cast< std::chrono::milliseconds >(
          std::chrono::milliseconds(random(15000)+18000)
     );

     switch (kaveAnimation)
     {
     case WHITE_DOTS:
          currentKaveAnimation = new WhiteDots(ledsController, microphone, kaveAnimation);
          break;

     case SIX_BARS_COLORED:
          currentKaveAnimation = new SixBarsColored(ledsController, microphone, kaveAnimation);
          break;

     }

     if(stairsRandomAnim && ledsController->getUseStairsSensor() && !ledsController->canShowStairs()){

          int anim = rand()%countStairsAnim;
          setStairsAnim(anim);
     }
}

void AnimationMode::setStairsAnim(int anim){
     
     switch(anim){
          case AnimationStairsLabel::RAINBOW:
               currentStairsAnimation = new StairsRainbow(ledsController, microphone, anim);
               break;
          case AnimationStairsLabel::FADE_IN:
               currentStairsAnimation = new StairsFadeIn(ledsController, microphone, anim);
               break;
          default:
               Serial.println("bad index anim stairs : " + anim);
               break;
     }
}

void AnimationMode::nextAnimation(){
     setAnimation(selectNewKaveAnimation());
}

void AnimationMode::setKaveList(int typeAnimation){
     currenKavetList = typeAnimation;
     nextAnimation();
}

void AnimationMode::setKeepAnimation(bool keep){
     keepAnimation = keep;
}

void AnimationMode::setStairsRandomAnim(bool random){
     stairsRandomAnim = random;
}

