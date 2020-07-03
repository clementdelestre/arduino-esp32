#include <Arduino.h>
#include "WiFi.h"

#include "mode.hpp"
#include "animations/animations_constructor.hpp"
#include "../../utils/headers/microphone.hpp"

#include "../../animations/animationMode/kave/headers/kave_off.hpp"
#include "../../animations/animationMode/kave/headers/kave_white_dots.hpp"
#include "../../animations/animationMode/kave/headers/kave_six_bars_colored.hpp"
#include "../../animations/animationMode/kave/headers/kave_centered_bar.hpp"
#include "../../animations/animationMode/kave/headers/kave_change_color.hpp"
#include "../../animations/animationMode/kave/headers/kave_strobodots.hpp"
#include "../../animations/animationMode/kave/headers/kave_colored_bars.hpp"
#include "../../animations/animationMode/kave/headers/kave_gradient_from_edges.hpp"
#include "../../animations/animationMode/kave/headers/kave_opacity.hpp"
#include "../../animations/animationMode/kave/headers/kave_slide.hpp"
#include "../../animations/animationMode/kave/headers/kave_scroll.hpp"
#include "../../animations/animationMode/kave/headers/kave_colored_bars_with_edges.hpp"
#include "../../animations/animationMode/kave/headers/kave_fire.hpp"
#include "../../animations/animationMode/kave/headers/kave_side_bars.hpp"
#include "../../animations/animationMode/kave/headers/kave_three_bars.hpp"
#include "../../animations/animationMode/kave/headers/kave_moving_bars.hpp"
#include "../../animations/animationMode/kave/headers/kave_transition_splash.hpp"

#include "../../animations/animationMode/stairs/headers/stairs_rainbow.hpp"
#include "../../animations/animationMode/stairs/headers/stairs_fade_in.hpp"

#include "../../animations/animationMode/kave/headers/kave_stroboscope.hpp"
#include "../../animations/animationMode/stairs/headers/stairs_stroboscope.hpp"

#ifndef ANIMATION_MODE_H_INCLUDED
#define ANIMATION_MODE_H_INCLUDED

class LedsController;

enum AnimationKaveLabel {    
    KAVE_OFF = 0,
    KAVE_CHANGE_COLOR = 1,   
    KAVE_STROBOSCOPE = 2,
    KAVE_CENTERED_BAR = 3,
    KAVE_WHITE_DOTS = 4,
    KAVE_STROBODOTS = 5,
    KAVE_COLORED_BARS = 6,
    KAVE_GRADIENT_FROM_EDGES = 7,
    KAVE_OPACITY = 8,
    KAVE_SIX_BARS_COLORED = 9,
    KAVE_SLIDE = 10,
    KAVE_SCROLL = 11,
    KAVE_COLORED_BARS_WITH_EDGES = 12,
    KAVE_FIRE = 13,
    KAVE_SIDE_BARS = 14,
    KAVE_THREE_BARS = 15,
    KAVE_MOVING_BARS = 16,
    KAVE_TRANSITION_SPLASH= 17,
};

enum AnimationStairsLabel {
    RAINBOW = 0,
    FADE_IN = 1,
    STAIRS_STROBOSCOPE = 2,
};

class AnimationMode : public Mode {

    private:

        std::chrono::milliseconds initAnimTime;
        std::chrono::seconds durationAnim;

        bool keepAnimation;
        bool mainAutoColor;
        RgbColor mainColor;

        // KAVE
        Microphone* microphone;

        AnimationConstructor* currentKaveAnimation;

        const  std::vector<int> listAllKaveAnimation = {
            KAVE_WHITE_DOTS,
            KAVE_SIX_BARS_COLORED,
            KAVE_CENTERED_BAR,
            KAVE_CHANGE_COLOR,
            KAVE_STROBODOTS,
            KAVE_COLORED_BARS,
            KAVE_GRADIENT_FROM_EDGES,
            KAVE_OPACITY,
            KAVE_SLIDE,
            KAVE_SCROLL,
            KAVE_COLORED_BARS_WITH_EDGES,
            KAVE_FIRE,
            KAVE_SIDE_BARS,
            KAVE_THREE_BARS,
            KAVE_MOVING_BARS,
            KAVE_TRANSITION_SPLASH,
        };

        const  std::vector<int> categoryAnimationSoft = {
            KAVE_SIX_BARS_COLORED,
            KAVE_CENTERED_BAR,
            KAVE_CHANGE_COLOR,
            KAVE_GRADIENT_FROM_EDGES,
            KAVE_SLIDE,
            KAVE_FIRE,
            KAVE_SIDE_BARS,
            KAVE_MOVING_BARS
        };

        const  std::vector<int> categoryAnimationHard = {
            KAVE_WHITE_DOTS,
            KAVE_CHANGE_COLOR,
            KAVE_STROBODOTS,
            KAVE_COLORED_BARS,
            KAVE_OPACITY,
            KAVE_SCROLL,
            KAVE_COLORED_BARS_WITH_EDGES,
            KAVE_FIRE,
            KAVE_SIDE_BARS,  
            KAVE_THREE_BARS,   
            KAVE_TRANSITION_SPLASH,      
        };

        const  std::vector<int> categoryAnimationVeryHard = {
            KAVE_WHITE_DOTS,
            KAVE_STROBODOTS,
            KAVE_COLORED_BARS,
            KAVE_SCROLL,
            KAVE_TRANSITION_SPLASH,
        };

        std::vector<int> listKaveActivatedAnimation;


        //STAIRS
        AnimationConstructor* currentStairsAnimation;
        bool stairsRandomAnim;

        bool isStairsDisplayed = true;

        //number of animation, useful for random select
        const int countStairsAnim = 2;


        //STROBOSCOPE
        int stroboscopeSpeed;
        bool stroboscopeAutoStop;
        bool stroboscopeEnabled;
        AnimationConstructor* stroboscopeOldStairsAnim;

    public:
        AnimationMode(LedsController* ledsController);
        void init() override;
        void displayMode() override;

        void startMode() override;
        void stopMode() override;

        void sendModeData() override;

        int selectRandomKaveAnimation();
        int selectRandomStairsAnimation();

        void setCategory(int category);

        //Change animation for Kave AND Stairs
        void setKaveAnimation(int kaveAnimation);
        void nextKaveAnimation();

        void setKeepAnimation(bool keep);

        void setStairsRandomAnim(bool random);
        void setStairsAnim(int anim);

        void setMainAutoColor(bool autoColor);
        bool getMainAutoColor();

        void setMainColor(RgbColor color);
        RgbColor getMainColor();

        Microphone* getMicrophone();

        void setEnableAnimation(int animation, bool enable);
        void sendEnabledAnimations(WiFiClient* client);

        //STROBOSCOPE

        void setStroboscopeSpeed(int speed);
        int getStroboscopeSpeed();
        void setStroboscopeAutoStop(bool autoStop);
        void startStroboscope();
        
};

#endif