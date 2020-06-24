#include "headers/animation.hpp"

#include "../headers/leds_controller.hpp"

AnimationMode::AnimationMode(LedsController* ledsController) : Mode(ledsController){
     this->ledsController = ledsController;
     this->modeLabel = ModeLabel::animations;
     this->microphone = new Microphone();

     keepAnimation = false;
     initAnimTime = Utils::getTimeSinceEpoch();

     stairsRandomAnim = false;

     mainAutoColor = true;
     mainColor = Utils::getFixedRandomColor();

     //enable all animation
     listKaveActivatedAnimation = listAllKaveAnimation;
     //disable stroboscope and off
     setEnableAnimation(AnimationKaveLabel::KAVE_STROBOSCOPE, false);
     setEnableAnimation(AnimationKaveLabel::KAVE_OFF, false);

     stroboscopeSpeed = 50;
     stroboscopeAutoStop = true;
     stroboscopeEnabled = false;

     
}

void AnimationMode::init(){
     setStairsAnim(0);
     setKaveAnimation(selectRandomKaveAnimation());
}


void AnimationMode::displayMode(){

     if(initAnimTime+durationAnim<Utils::getTimeSinceEpoch() && !keepAnimation && (!stroboscopeEnabled || stroboscopeAutoStop)){        
        nextKaveAnimation();     
     }

     currentKaveAnimation->displayAnimation();


     if(ledsController->canShowStairs() && isStairsDisplayed){
          currentStairsAnimation->displayAnimation();
     } else if(ledsController->canShowStairs() && !isStairsDisplayed){

          if(stairsRandomAnim && !stroboscopeSpeed){
               setStairsAnim(selectRandomStairsAnimation());
          }

          currentStairsAnimation->init();
          currentStairsAnimation->displayAnimation();
          isStairsDisplayed = true;
     } else if(!ledsController->canShowStairs() && isStairsDisplayed){
          isStairsDisplayed = false;
          ledsController->getStairsLeds()->ClearTo(0);
          ledsController->getStairsLeds()->Show();
     }
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
     ledsController->getWifiManager()->sendAllClientData(Flags::SENSOR_STAIRS, ledsController->getUseStairsSensor() ? 1 : 0, 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::A_KAVE_CURRENT_ANIM, currentKaveAnimation->getFlag(), 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::A_STAIRS_RANDOM_ANIM, stairsRandomAnim ? 1 : 0, 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::A_STAIRS_CURRENT_ANIM, currentStairsAnimation->getFlag(), 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::A_MAIN_COLOR_AUT0, mainAutoColor ? 1 : 0, 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::A_MAIN_COLOR, mainColor.R, mainColor.G, mainColor.B);
     ledsController->getWifiManager()->sendAllClientData(Flags::A_STROBOSCOPE_SPEED, stroboscopeSpeed, 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::A_STOP_AUTO_STROBOSCOPE, stroboscopeAutoStop ? 1 : 0, 0, 0);
     ledsController->getWifiManager()->sendAllClientData(Flags::A_START_STROBOSCOPE, stroboscopeEnabled ? 1 : 0, 0, 0);
}

int AnimationMode::selectRandomKaveAnimation(){
     if(listKaveActivatedAnimation.size() != 0){
          int index = rand() % listKaveActivatedAnimation.size();
          return listKaveActivatedAnimation[index];
     } else {
          return 0;
     }
     
}

int AnimationMode::selectRandomStairsAnimation(){
     return rand()%countStairsAnim;
}

void AnimationMode::setKaveAnimation(int kaveAnimation){

     initAnimTime = Utils::getTimeSinceEpoch();

     durationAnim = std::chrono::duration_cast< std::chrono::milliseconds >(
          std::chrono::milliseconds(random(15000)+18000)
     );   

     if(stroboscopeEnabled){
          stroboscopeEnabled = false;
          ledsController->getWifiManager()->sendAllClientData(Flags::A_START_STROBOSCOPE, 0, 0, 0);
          setStairsAnim(stroboscopeOldStairsAnim->getFlag());
     } 

     switch (kaveAnimation)
     {
     case AnimationKaveLabel::KAVE_OFF:
          currentKaveAnimation = new KaveOff(ledsController, microphone, kaveAnimation);
          break;
     case AnimationKaveLabel::KAVE_WHITE_DOTS:
          currentKaveAnimation = new WhiteDots(ledsController, microphone, kaveAnimation);
          break;

     case AnimationKaveLabel::KAVE_SIX_BARS_COLORED:
          currentKaveAnimation = new SixBarsColored(ledsController, microphone, kaveAnimation);
          break;
     case AnimationKaveLabel::KAVE_STROBOSCOPE:
          currentKaveAnimation = new KaveStroboscope(ledsController, microphone, kaveAnimation);
          break;
     case AnimationKaveLabel::KAVE_CENTERED_BAR:
          currentKaveAnimation = new KaveCenteredBar(ledsController, microphone, kaveAnimation);
          break;
     case AnimationKaveLabel::KAVE_CHANGE_COLOR:
          currentKaveAnimation = new KaveChangeColor(ledsController, microphone, kaveAnimation);
          break;
     case AnimationKaveLabel::KAVE_STROBODOTS:
          currentKaveAnimation = new KaveStrobodots(ledsController, microphone, kaveAnimation);
          break;
     case AnimationKaveLabel::KAVE_COLORED_BARS:
          currentKaveAnimation = new KaveColoredBars(ledsController, microphone, kaveAnimation);
          break;
     case AnimationKaveLabel::KAVE_GRADIENT_FROM_EDGES:
          currentKaveAnimation = new KaveGradientFromEdges(ledsController, microphone, kaveAnimation);
          break;
     case AnimationKaveLabel::KAVE_OPACITY:
          currentKaveAnimation = new KaveOpacity(ledsController, microphone, kaveAnimation);
          break;
     case AnimationKaveLabel::KAVE_SLIDE:
          currentKaveAnimation = new KaveSlide(ledsController, microphone, kaveAnimation);
          break;
     case AnimationKaveLabel::KAVE_SCROLL:
          currentKaveAnimation = new KaveScroll(ledsController, microphone, kaveAnimation);
          break;
     case AnimationKaveLabel::KAVE_COLORED_BARS_WITH_EDGES:
          currentKaveAnimation = new KaveColoredBarsWithEdges(ledsController, microphone, kaveAnimation);
          break;
     }

     //useful for stroboscope
     currentKaveAnimation->init();

     if(stairsRandomAnim && ledsController->getUseStairsSensor() && !ledsController->canShowStairs()){
          setStairsAnim(selectRandomStairsAnimation());
     }

     ledsController->getWifiManager()->sendAllClientData(Flags::A_KAVE_CURRENT_ANIM, currentKaveAnimation->getFlag(), 0, 0);
}

void AnimationMode::setStairsAnim(int anim){

     switch(anim){
          case AnimationStairsLabel::RAINBOW:
               currentStairsAnimation = new StairsRainbow(ledsController, microphone, anim);
               break;
          case AnimationStairsLabel::FADE_IN:
               currentStairsAnimation = new StairsFadeIn(ledsController, microphone, anim);
               break;
          case AnimationStairsLabel::STAIRS_STROBOSCOPE:
               currentStairsAnimation = new StairsStroboscope(ledsController, microphone, anim);
               break;
          default:
               Serial.println("bad index anim stairs : " + anim);
               break;
     }

     ledsController->getWifiManager()->sendAllClientData(Flags::A_STAIRS_CURRENT_ANIM, currentStairsAnimation->getFlag(), 0, 0);

}

void AnimationMode::nextKaveAnimation(){
     setKaveAnimation(selectRandomKaveAnimation());
}

void AnimationMode::setKeepAnimation(bool keep){
     keepAnimation = keep;
     ledsController->getWifiManager()->sendAllClientData(Flags::A_KEEP_ANIMATION, keepAnimation ? 1 : 0, 0, 0);
}

void AnimationMode::setStairsRandomAnim(bool random){
     stairsRandomAnim = random;
     ledsController->getWifiManager()->sendAllClientData(Flags::A_STAIRS_RANDOM_ANIM, stairsRandomAnim ? 1 : 0, 0, 0);
}

void AnimationMode::setMainAutoColor(bool autoColor){
     mainAutoColor = autoColor;
     currentKaveAnimation->init();
     currentStairsAnimation->init();
     ledsController->getWifiManager()->sendAllClientData(Flags::A_MAIN_COLOR_AUT0, mainAutoColor ? 1 : 0, 0, 0);
}

bool AnimationMode::getMainAutoColor(){
     return mainAutoColor;
}

void AnimationMode::setMainColor(RgbColor color){
     mainColor = color;
     currentKaveAnimation->init();
     currentStairsAnimation->init();
     ledsController->getWifiManager()->sendAllClientData(Flags::A_MAIN_COLOR, color.R, color.G, color.B);
}

RgbColor AnimationMode::getMainColor(){
     return mainColor;
}

void AnimationMode::setEnableAnimation(int animation, bool enable){
     if (std::find(listKaveActivatedAnimation.begin(), listKaveActivatedAnimation.end(), animation) != listKaveActivatedAnimation.end()){
          //animation is already enable
          if(!enable){
               std::vector<int>::iterator position = std::find(listKaveActivatedAnimation.begin(), listKaveActivatedAnimation.end(), animation);
               if (position != listKaveActivatedAnimation.end())
                    listKaveActivatedAnimation.erase(position);
          }
     } else {
          //animation is already disable
          if(enable){
               listKaveActivatedAnimation.push_back(animation);
          }
     }	
}

void AnimationMode::sendEnabledAnimations(WiFiClient* client){
     for (int value : listKaveActivatedAnimation) {  
          ledsController->getWifiManager()->sendData(client, Flags::A_GET_ENABLED_ANIMATIONS, value, 0, 0);
     }
     ledsController->getWifiManager()->sendAllClientData(Flags::A_KAVE_CURRENT_ANIM, currentKaveAnimation->getFlag(), 0, 0);
}

void AnimationMode::setCategory(int category){
     switch (category)
     {
     case 0:
          listKaveActivatedAnimation = listAllKaveAnimation;
          break;
     case 1:
          listKaveActivatedAnimation = {};
          break;
     case 2:
          listKaveActivatedAnimation = categoryAnimationSoft;
          break;
     case 3:
          listKaveActivatedAnimation = categoryAnimationHard;
          break;
     case 4:
          listKaveActivatedAnimation = categoryAnimationVeryHard;
          break;    
     }
     nextKaveAnimation();
}

void AnimationMode::setStroboscopeSpeed(int speed){
     stroboscopeSpeed = speed;
}

int AnimationMode::getStroboscopeSpeed(){
     return stroboscopeSpeed;
}

void AnimationMode::setStroboscopeAutoStop(bool autoStop){
     stroboscopeAutoStop = autoStop;
     ledsController->getWifiManager()->sendAllClientData(Flags::A_STOP_AUTO_STROBOSCOPE, stroboscopeAutoStop ? 1 : 0, 0, 0);
}

void AnimationMode::startStroboscope(){   

     stroboscopeOldStairsAnim = currentStairsAnimation;
   
     setKaveAnimation(AnimationKaveLabel::KAVE_STROBOSCOPE);
     setStairsAnim(AnimationStairsLabel::STAIRS_STROBOSCOPE);

     stroboscopeEnabled = true;
     ledsController->getWifiManager()->sendAllClientData(Flags::A_START_STROBOSCOPE, 1, 0, 0);
}

