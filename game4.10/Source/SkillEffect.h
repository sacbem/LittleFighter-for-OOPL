#pragma once
#include "GameObject.h"
namespace game_framework {
    class SkillEffect {
    public:
        SkillEffect(int skillID, int createdTimes, int direction, int xPos, int yPos);
        ~SkillEffect();
        int createdTime;
        void OnShow();
        int GetDir();
        int xPos, yPos;
        int yTemp;
        bool isHit;
    protected:
        int direction;
        int AnimationState;
        int AnimationCount[3];
        int timeCount;
        vector<string> feedbackStatus;
        vector<GameObject*> effectObj;
    private:
        int skillID;
        void CreatEffectObj();

        enum class skillsIdTable {
            frozenWave, frozenPunch, frozenSword, frozenStorm, normalArrow, pierceArrow, EnergyBlast, airWave, demonicSong, downArrow, upArrow, downArrow2, EnergyBlast2
        };
    };

}