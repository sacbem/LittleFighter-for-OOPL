#pragma once
#include "GameObject.h"
namespace game_framework {
    class SkillEffect {
    public:
        SkillEffect(int skillID);
        boolean SkillsProcess(vector<vector<int>> theOthersPosition);
        void SkillsFeedbackStatus(vector<vector<int>>  theOthersPosition);
        boolean GarbageCollectorTimer();
        //void GarbageCollector();
        ~SkillEffect();
    protected:
        vector<GameObject*> effectObj;
        vector<string> feedbackStatus;
    private:
        void CreatEffectObj();
        void SetEffectObj(int x, int y);//x :腳色的 X ; y :腳色的Y       
        int skillID;
        enum class skillsIdTable {
            frozenWave, frozenPunch, frozenSword, frozenStorm
        };
    };

}