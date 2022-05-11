#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "SkillEffect.h"
namespace game_framework {
	SkillEffect::SkillEffect(int skillsID, int createdTimes) {
		effectObj.reserve(5);
		skillID = skillsID;
		createdTime = createdTimes;
		CreatEffectObj();
	}
	void  SkillEffect::CreatEffectObj() {
		switch (skillID) {
		case static_cast<int>(skillsIdTable::frozenWave):
			effectObj.push_back(new GameObject(2,"Effect"));
			//effectObj[0]->Load(".\\res\\Freeze\\Freeze_ball\\Freeze_ball_0.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\Freeze_ball_0.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\Freeze_ball_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\Freeze_ball_2.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\Freeze_ball_3.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\Freeze_ball_8.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\Freeze_ball_9.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\Freeze_ball_4.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\Freeze_ball_5.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\Freeze_ball_6.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\Freeze_ball_7.bmp", RGB(0, 0, 0));

			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\Freeze_ball_reverse_3.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\Freeze_ball_reverse_2.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\Freeze_ball_reverse_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\Freeze_ball_reverse_0.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\Freeze_ball_reverse_11.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\Freeze_ball_reverse_10.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\Freeze_ball_reverse_7.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\Freeze_ball_reverse_6.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\Freeze_ball_reverse_5.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\Freeze_ball_reverse_4.bmp", RGB(0, 0, 0));
			
			break;
		case static_cast<int>(skillsIdTable::frozenPunch):
			effectObj.push_back(new GameObject(8,"Effect"));
			//0 1 ice_1
			effectObj[1]->Load(0, ".\\res\\Freeze\\Freeze_col\\Freeze_col_0.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Freeze\\Freeze_col\\Freeze_col_1.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Freeze\\Freeze_col\\Freeze_col_2.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Freeze\\Freeze_col\\Freeze_col_3.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Freeze\\Freeze_col\\Freeze_col_4.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Freeze\\Freeze_col\\Freeze_col_5.bmp", RGB(0, 0, 0));

			effectObj[1]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_6.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_5.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_4.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_3.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_2.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_1.bmp", RGB(0, 0, 0));
			//2 3 ice_2
			effectObj[1]->Load(2, ".\\res\\Freeze\\Freeze_col\\Freeze_col_7.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(2, ".\\res\\Freeze\\Freeze_col\\Freeze_col_8.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(2, ".\\res\\Freeze\\Freeze_col\\Freeze_col_9.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(2, ".\\res\\Freeze\\Freeze_col\\Freeze_col_10.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(2, ".\\res\\Freeze\\Freeze_col\\Freeze_col_11.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(2, ".\\res\\Freeze\\Freeze_col\\Freeze_col_12.bmp", RGB(0, 0, 0));

			effectObj[1]->Load(3, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_13.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(3, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_12.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(3, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_11.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(3, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_10.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(3, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_9.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(3, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_8.bmp", RGB(0, 0, 0));
			//4 5 ice_3
			effectObj[1]->Load(4, ".\\res\\Freeze\\Freeze_col\\Freeze_col_14.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(4, ".\\res\\Freeze\\Freeze_col\\Freeze_col_15.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(4, ".\\res\\Freeze\\Freeze_col\\Freeze_col_16.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(4, ".\\res\\Freeze\\Freeze_col\\Freeze_col_17.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(4, ".\\res\\Freeze\\Freeze_col\\Freeze_col_18.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(4, ".\\res\\Freeze\\Freeze_col\\Freeze_col_19.bmp", RGB(0, 0, 0));

			effectObj[1]->Load(5, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_20.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(5, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_19.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(5, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_18.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(5, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_17.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(5, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_16.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(5, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_15.bmp", RGB(0, 0, 0));
			//6 7 ice_4
			effectObj[1]->Load(6, ".\\res\\Freeze\\Freeze_col\\Freeze_col_21.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(6, ".\\res\\Freeze\\Freeze_col\\Freeze_col_22.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(6, ".\\res\\Freeze\\Freeze_col\\Freeze_col_23.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(6, ".\\res\\Freeze\\Freeze_col\\Freeze_col_24.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(6, ".\\res\\Freeze\\Freeze_col\\Freeze_col_25.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(6, ".\\res\\Freeze\\Freeze_col\\Freeze_col_26.bmp", RGB(0, 0, 0));

			effectObj[1]->Load(7, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_27.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(7, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_26.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(7, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_25.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(7, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_24.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(7, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_23.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(7, ".\\res\\Freeze\\Freeze_col_reverse\\Freeze_col_reverse_22.bmp", RGB(0, 0, 0));
			break;
		//case static_cast<int>(skillsIdTable::frozenSword):
		//	effectObj.push_back(new GameObject("Effect"));
		//	break;
		//case static_cast<int>(skillsIdTable::frozenStorm):
		//	effectObj.push_back(new GameObject("Effect"));

		//	break;
		default:
			break;
		}
	}

	void SkillEffect::OnShow(int id_x, int id_y) {
		for (auto i : effectObj) {
			i->OnShow(id_x, id_y);
		}
	}

	void  SkillEffect::SetEffectObj(int x, int y) { //���U�զX��� �Q�I�s�@��
		switch(skillID) {
			//////////////// Freeze
		case static_cast<int>(skillsIdTable::frozenWave):
			for (auto& i : effectObj) {
				i->SetTopLeft(0, 0, x, y);
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
	boolean  SkillEffect::SkillsProcess(vector<vector<int>> theOthersPosition,int duration) {
		switch (skillID) {
			//////////////// Freeze
		case static_cast<int>(skillsIdTable::frozenWave):
			for (auto& i : effectObj) {
				//i->SetTopLeft(i->GetPositionXY("X") + 1, i->GetPositionXY("Y"));
				//i->OnShow();
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

		if (GarbageCollectorTimer(duration)) {
			return true;
		}
		else {
			return false;
		}
	}
	boolean SkillEffect:: GarbageCollectorTimer(int duration) {
		const int skill_duration_1 = 5;
		switch (duration){
		case skill_duration_1:
			return true;
			break;
		default:
			return false;
			break;
		}
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
	void SkillEffect::OnShow() {
		for (auto i : effectObj) {
			i->OnShow();
		}
	}
	SkillEffect::~SkillEffect() {
		for (auto& i : effectObj) {
			delete i;
		}
	}
}