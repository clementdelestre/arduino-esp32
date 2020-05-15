#include <Arduino.h>
#include "mode.hpp"
#include "animations/headers/animations_constructor.hpp"
#include "../../utils/headers/microphone.hpp"

#include "../../animations/headers/kave_white_dots.hpp"
#include "../../animations/headers/kave_six_bars_colored.hpp"

#include "../../animations/headers/stairs_rainbow.hpp"
#include "../../animations/headers/stairs_fade_in.hpp"

#ifndef ANIMATION_MODE_H_INCLUDED
#define ANIMATION_MODE_H_INCLUDED

class LedsController;

enum AnimationKaveListLabel {
    SOFT = 0,
    ALL = 1,
    HARD = 2
};

enum AnimationKaveLabel {
    WHITE_DOTS = 0,
    SIX_BARS_COLORED = 1
};

enum AnimationStairsLabel {
    RAINBOW = 0,
    FADE_IN = 1
};

class AnimationMode : public Mode {

    private:

        std::chrono::milliseconds initAnimTime;
        std::chrono::milliseconds durationAnim;

        bool keepAnimation;

        // KAVE
        Microphone* microphone;

        AnimationConstructor* currentKaveAnimation;
        int currenKavetList;

        const  std::vector<int> listAllKaveAnimation = {
            WHITE_DOTS,
            SIX_BARS_COLORED
        };

        const  std::vector<int> listSoftKaveAnimation = {
            SIX_BARS_COLORED
        };

        const  std::vector<int> listHardKaveAnimation = {
            WHITE_DOTS
        };

        const std::vector<std::vector<int>> allListsKave = {listSoftKaveAnimation, listAllKaveAnimation, listHardKaveAnimation};


        //STAIRS
        AnimationConstructor* currentStairsAnimation;
        bool stairsRandomAnim;

        bool isStairsDisplayed = true;

        //number of animation, useful for random select
        const int countStairsAnim = 2;

    public:
        AnimationMode(LedsController* ledsController);
        void displayMode() override;

        void startMode() override;
        void stopMode() override;

        void sendModeData() override;

        int selectNewKaveAnimation();

        //Change animation for Kave AND Stairs
        void setAnimation(int kaveAnimation);
        void nextAnimation();

        void setKaveList(int typeAnimation);
        void setKeepAnimation(bool keep);

        void setStairsRandomAnim(bool random);
        void setStairsAnim(int anim);

        Microphone* getMicrophone();

};

#endif