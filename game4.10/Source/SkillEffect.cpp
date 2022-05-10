#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "SkillEffect.h"
namespace game_framework {
    SkillEffect::SkillEffect(int skillsID) {
        effectObj.reserve(5);
        skillID = skillsID;
        CreatEffectObj();

    }
    void  SkillEffect::CreatEffectObj() {
        switch (skillID) {
        case static_cast<int>(skillsIdTable::frozenWave):
            effectObj.push_back(new GameObject("Effect"));
            //effectObj[0]->Load(BitMapID);
            break;
        case static_cast<int>(skillsIdTable::frozenPunch):
            //for (int i = 0; i < x; i++) {
            effectObj.push_back(new GameObject("Effect"));
            //effectObj[i]->Load(BitMapID);
            //}
            break;
        case static_cast<int>(skillsIdTable::frozenSword):
            //for (int i = 0; i < x; i++) {
            effectObj.push_back(new GameObject("Effect"));
            //effectObj[i]->Load(BitMapID);
            //}
            break;
        case static_cast<int>(skillsIdTable::frozenStorm):
            //for (int i = 0; i < x; i++) {
            effectObj.push_back(new GameObject("Effect"));
            //effectObj[i]->Load(BitMapID);
            //}
            break;

        default:
            break;
        }
    }
    void  SkillEffect::SetEffectObj(int x, int y) { //按下組合鍵後 被呼叫一次
        switch(skillID) {
            //////////////// Freeze
        case static_cast<int>(skillsIdTable::frozenWave):
            for (auto& i : effectObj) {
                i->SetTopLeft( x + 50 , y + 70);
            }
            break;
        case static_cast<int>(skillsIdTable::frozenPunch):
            //for (auto& i : effectObj) {

            //}
            break;
        case static_cast<int>(skillsIdTable::frozenSword):
            //for (auto& i : effectObj) {

            //}
            break;
        case static_cast<int>(skillsIdTable::frozenStorm):
            //for (auto& i : effectObj) {

            //}
            break;
        ////////////////
        default:
            break;
        }
    }
    boolean  SkillEffect::SkillsProcess(vector<vector<int>> theOthersPosition) {
        switch (skillID) {
            //////////////// Freeze
        case static_cast<int>(skillsIdTable::frozenWave):
            for (auto& i : effectObj) {
                i->SetTopLeft(i->GetPositionXY("X") + 1, i->GetPositionXY("Y"));
            }
            break;
        case static_cast<int>(skillsIdTable::frozenPunch):
            //for (auto& i : effectObj) {

            //}
            break;
        case static_cast<int>(skillsIdTable::frozenSword):
            //for (auto& i : effectObj) {

            //}
            break;
        case static_cast<int>(skillsIdTable::frozenStorm):
            //for (auto& i : effectObj) {

            //}
            break;
            ////////////////
        default:
            break;
        }
        SkillsFeedbackStatus(theOthersPosition);

        if (GarbageCollectorTimer()) {
            return true;
        }
        else {
            return false;
        }
    }
    boolean SkillEffect:: GarbageCollectorTimer() {
        return true;

    }
    void  SkillEffect::SkillsFeedbackStatus(vector<vector<int>> theOthersPosition) {

        switch (skillID) {
         //////////////// Freeze
        case static_cast<int>(skillsIdTable::frozenWave):
            for (auto& i : effectObj) {
                for (int h = 0; h < theOthersPosition.size(); h++) {
                    if (i->GetPositionXY("X") == theOthersPosition[h][0]) {
                        if (i->GetPositionXY("Y") == theOthersPosition[h][1]) {
                            feedbackStatus[h] = "Freezed";
                        }
                    }
                }
            }
            break;
        case static_cast<int>(skillsIdTable::frozenPunch):
            
            break;
        case static_cast<int>(skillsIdTable::frozenSword):
            
            break;
        case static_cast<int>(skillsIdTable::frozenStorm):
           
            break;
            
        default:
            break;
        }

    }

    SkillEffect::~SkillEffect() {
        for (auto& i : effectObj) {
            delete i;
        }
    }
}