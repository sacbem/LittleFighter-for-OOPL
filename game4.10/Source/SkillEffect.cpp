#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "SkillEffect.h"
namespace game_framework {
	SkillEffect::SkillEffect(int skillsID, int createdTimes,int dire ,int x, int y) {
		effectObj.reserve(5);
		skillID = skillsID;
		createdTime = createdTimes;
		xPos = x;
		yPos = y;
		direction = dire;
		AnimationState = 0;
		AnimationCount[0] = 0;
		AnimationCount[1] = 0;
		AnimationCount[2] = 0;
		timeCount = 0;
		isHit = false;
		CreatEffectObj();

	}
	void  SkillEffect::CreatEffectObj() {
		switch (skillID) {
		case static_cast<int>(skillsIdTable::frozenWave):
			effectObj.push_back(new GameObject(2, "Effect"));
			//effectObj[0]->Load(".\\res\\Freeze\\Freeze_ball\\freeze_ball_0.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\freeze_ball_0.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\freeze_ball_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\freeze_ball_2.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\freeze_ball_3.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\freeze_ball_8.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\freeze_ball_9.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\freeze_ball_4.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\freeze_ball_5.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\freeze_ball_6.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ball\\freeze_ball_7.bmp", RGB(0, 0, 0));

			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\freeze_ball_reverse_3.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\freeze_ball_reverse_2.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\freeze_ball_reverse_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\freeze_ball_reverse_0.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\freeze_ball_reverse_11.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\freeze_ball_reverse_10.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\freeze_ball_reverse_7.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\freeze_ball_reverse_6.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\freeze_ball_reverse_5.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ball_reverse\\freeze_ball_reverse_4.bmp", RGB(0, 0, 0));

			break;
		case static_cast<int>(skillsIdTable::frozenPunch):
			effectObj.push_back(new GameObject(2, "Effect"));
			effectObj.push_back(new GameObject(2, "Effect"));
			effectObj.push_back(new GameObject(2, "Effect"));
			effectObj.push_back(new GameObject(2, "Effect"));
			//0 1 ice_1
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_0.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_2.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_3.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_4.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_5.bmp", RGB(0, 0, 0));

			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_6.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_5.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_4.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_3.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_2.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_1.bmp", RGB(0, 0, 0));
			//2 3 ice_2
			effectObj[1]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_7.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_8.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_9.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_10.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_11.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_12.bmp", RGB(0, 0, 0));

			effectObj[1]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_13.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_12.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_11.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_10.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_9.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_8.bmp", RGB(0, 0, 0));
			//4 5 ice_3
			effectObj[2]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_14.bmp", RGB(0, 0, 0));
			effectObj[2]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_15.bmp", RGB(0, 0, 0));
			effectObj[2]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_16.bmp", RGB(0, 0, 0));
			effectObj[2]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_17.bmp", RGB(0, 0, 0));
			effectObj[2]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_18.bmp", RGB(0, 0, 0));
			effectObj[2]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_19.bmp", RGB(0, 0, 0));

			effectObj[2]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_20.bmp", RGB(0, 0, 0));
			effectObj[2]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_19.bmp", RGB(0, 0, 0));
			effectObj[2]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_18.bmp", RGB(0, 0, 0));
			effectObj[2]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_17.bmp", RGB(0, 0, 0));
			effectObj[2]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_16.bmp", RGB(0, 0, 0));
			effectObj[2]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_15.bmp", RGB(0, 0, 0));
			//6 7 ice_4
			effectObj[3]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_21.bmp", RGB(0, 0, 0));
			effectObj[3]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_22.bmp", RGB(0, 0, 0));
			effectObj[3]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_23.bmp", RGB(0, 0, 0));
			effectObj[3]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_24.bmp", RGB(0, 0, 0));
			effectObj[3]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_25.bmp", RGB(0, 0, 0));
			effectObj[3]->Load(0, ".\\res\\Freeze\\Freeze_col\\freeze_col_26.bmp", RGB(0, 0, 0));

			effectObj[3]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_27.bmp", RGB(0, 0, 0));
			effectObj[3]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_26.bmp", RGB(0, 0, 0));
			effectObj[3]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_25.bmp", RGB(0, 0, 0));
			effectObj[3]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_24.bmp", RGB(0, 0, 0));
			effectObj[3]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_23.bmp", RGB(0, 0, 0));
			effectObj[3]->Load(1, ".\\res\\Freeze\\Freeze_col_reverse\\freeze_col_reverse_22.bmp", RGB(0, 0, 0));
			break;
			//case static_cast<int>(skillsIdTable::frozenSword):
			//	effectObj.push_back(new GameObject("Effect"));
			//	break;
		case static_cast<int>(skillsIdTable::frozenStorm):
			effectObj.push_back(new GameObject(2,"Effect"));

			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ww\\Freeze_ww_0.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ww\\Freeze_ww_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ww\\Freeze_ww_2.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ww\\Freeze_ww_3.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ww\\Freeze_ww_4.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ww\\Freeze_ww_5.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ww\\Freeze_ww_6.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ww\\Freeze_ww_7.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ww\\Freeze_ww_8.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Freeze\\Freeze_ww\\Freeze_ww_9.bmp", RGB(0, 0, 0));

			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ww_reverse\\freeze_ww_reverse_4.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ww_reverse\\freeze_ww_reverse_3.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ww_reverse\\freeze_ww_reverse_2.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ww_reverse\\freeze_ww_reverse_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ww_reverse\\freeze_ww_reverse_0.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ww_reverse\\freeze_ww_reverse_9.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ww_reverse\\freeze_ww_reverse_8.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ww_reverse\\freeze_ww_reverse_7.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ww_reverse\\freeze_ww_reverse_6.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Freeze\\Freeze_ww_reverse\\freeze_ww_reverse_5.bmp", RGB(0, 0, 0));
			break;
		case static_cast<int>(skillsIdTable::normalArrow):
			effectObj.push_back(new GameObject(2, "Effect"));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_0.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_2.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_3.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_4.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_5.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_6.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_10.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_11.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_12.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_13.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_14.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_15.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_16.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_17.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_18.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow1\\Henry_arrow1_19.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_9.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_8.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_8.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_8.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_8.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_7.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_6.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_5.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_4.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_3.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_19.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_18.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_17.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_16.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_15.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_14.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_13.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_12.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_11.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow1_reverse\\Henry_arrow1_reverse_10.bmp", RGB(0, 0, 0));
			break;
		case static_cast<int>(skillsIdTable::pierceArrow):
			effectObj.push_back(new GameObject(2, "Effect"));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow2\\Henry_arrow2_0.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow2\\Henry_arrow2_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow2\\Henry_arrow2_2.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow2\\Henry_arrow2_3.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow2\\Henry_arrow2_4.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow2\\Henry_arrow2_5.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow2\\Henry_arrow2_6.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow2\\Henry_arrow2_7.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow2\\Henry_arrow2_8.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Henry\\Henry_arrow2\\Henry_arrow2_9.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow2_reverse\\Henry_arrow2_reverse_5.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow2_reverse\\Henry_arrow2_reverse_4.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow2_reverse\\Henry_arrow2_reverse_3.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow2_reverse\\Henry_arrow2_reverse_2.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow2_reverse\\Henry_arrow2_reverse_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow2_reverse\\Henry_arrow2_reverse_0.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow2_reverse\\Henry_arrow2_reverse_11.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow2_reverse\\Henry_arrow2_reverse_10.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow2_reverse\\Henry_arrow2_reverse_9.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Henry\\Henry_arrow2_reverse\\Henry_arrow2_reverse_8.bmp", RGB(0, 0, 0));
		case static_cast<int>(skillsIdTable::EnergyBlast):
			effectObj.push_back(new GameObject(2, "Effect"));
			effectObj.push_back(new GameObject(2, "Effect"));
			effectObj[0]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_0.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_2.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_3.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_4.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_5.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_6.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_7.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_3.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_2.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_1.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_0.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_7.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_6.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_5.bmp", RGB(0, 0, 0));
			effectObj[0]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_4.bmp", RGB(0, 0, 0));
			//second blast
			effectObj[1]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_8.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_9.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_10.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_11.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_4.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_5.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_6.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(0, ".\\res\\Woody\\Woody_ball\\Woody_ball_7.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_11.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_10.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_9.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_8.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_7.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_6.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_5.bmp", RGB(0, 0, 0));
			effectObj[1]->Load(1, ".\\res\\Woody\\Woody_ball_reverse\\Woody_ball_reverse_4.bmp", RGB(0, 0, 0));
		default:
			break;
		}
	}

	void SkillEffect::OnShow() {
		switch (skillID) {
			//////////////// Freeze
		case static_cast<int>(skillsIdTable::frozenWave):
			if (!isHit) {
				effectObj[0]->SetTopLeft(direction, AnimationCount[0] % 6, xPos, yPos);
				effectObj[0]->OnShow(direction, AnimationCount[0] % 6);
				AnimationCount[0]++;
				//SkillsProcess(theOthersPosition, mainTime - createdTime);
				if (direction == 0) {
					xPos += 5;
				}
				else if (direction == 1) {
					xPos -= 5;
				}
			}
			else if (isHit) {
				if (AnimationCount[1] <= 4) {
					effectObj[0]->SetTopLeft(direction, 6, xPos, yPos);
					effectObj[0]->OnShow(direction, 6);
				}
				else if(AnimationCount[1] <= 8) {
					effectObj[0]->SetTopLeft(direction, 7, xPos, yPos);
					effectObj[0]->OnShow(direction, 7);
				}
				else if (AnimationCount[1] <= 12) {
					effectObj[0]->SetTopLeft(direction, 8, xPos, yPos);
					effectObj[0]->OnShow(direction, 8);
				}
				else if (AnimationCount[1] <= 16) {
					effectObj[0]->SetTopLeft(direction, 9, xPos, yPos);
					effectObj[0]->OnShow(direction, 9);
				}
				else if (AnimationCount[1] > 16) {
					break;
				}
				AnimationCount[1]++;
			}
			break;
		case static_cast<int>(skillsIdTable::frozenPunch):
			if (timeCount >= 20) {
				if (direction == 0) {
					effectObj[2]->SetTopLeft(direction, AnimationCount[0], xPos + 40, yPos - 30);
					effectObj[2]->OnShow(direction, AnimationCount[0]);
					
				}
				else if (direction == 1) {
					effectObj[2]->SetTopLeft(direction, AnimationCount[0], xPos - 60, yPos - 30);
					effectObj[2]->OnShow(direction, AnimationCount[0]);
				}
				if (AnimationCount[0] < 5) {
					if (timeCount % 5 == 0) {
						AnimationCount[0]++;
					}
				}
			}
			if (timeCount >= 40) {
				if (direction == 0) {
					effectObj[1]->SetTopLeft(direction, AnimationCount[1], xPos + 80, yPos - 30);
					effectObj[1]->OnShow(direction, AnimationCount[1]);
				}
				else if (direction == 1) {
					effectObj[1]->SetTopLeft(direction, AnimationCount[1], xPos - 100, yPos - 30);
					effectObj[1]->OnShow(direction, AnimationCount[1]);
				}
				if (AnimationCount[1] < 5) {
					if (timeCount % 5 == 0) {
						AnimationCount[1]++;
					}
				}
			}
			if (timeCount >= 60) {
				if (direction == 0) {
					effectObj[0]->SetTopLeft(direction, AnimationCount[2], xPos + 140, yPos - 30);
					effectObj[0]->OnShow(direction, AnimationCount[2]);
				}
				else if (direction == 1) {
					effectObj[0]->SetTopLeft(direction, AnimationCount[2], xPos - 160, yPos - 30);
					effectObj[0]->OnShow(direction, AnimationCount[2]);
				}
				if (AnimationCount[2] < 5) {
					if (timeCount % 5 == 0) {
						AnimationCount[2]++;
					}
				}
			}

			timeCount++;
			break;
		case static_cast<int>(skillsIdTable::frozenSword):

			break;
		case static_cast<int>(skillsIdTable::frozenStorm):
			if (timeCount >= 16 && timeCount<200) {
				if (timeCount < 180) {
					effectObj[0]->SetTopLeft(direction, AnimationCount[0] % 8, xPos-40, yPos-70);
					effectObj[0]->OnShow(direction, AnimationCount[0] % 8);
				}
				else if (timeCount < 190) {
					effectObj[0]->SetTopLeft(direction, 8, xPos - 40, yPos - 70);
					effectObj[0]->OnShow(direction, 8);
				}
				else if (timeCount < 200) {
					effectObj[0]->SetTopLeft(direction, 9, xPos - 40, yPos - 70);
					effectObj[0]->OnShow(direction, 9);
				}

				if (direction == 0) {
					xPos += 2;
				}
				else if (direction == 1) {
					xPos -= 2;
				}
			}
			if (timeCount % 5 == 0) {
				AnimationCount[0]++;
			}
			timeCount++;
			break;
			////////////////
		case static_cast<int>(skillsIdTable::normalArrow):
			if (timeCount >= 20) {
				effectObj[0]->SetTopLeft(direction, 1, xPos, yPos);
				effectObj[0]->OnShow(direction, 1);
				AnimationCount[0]++;
				//SkillsProcess(theOthersPosition, mainTime - createdTime);
				if (direction == 0) {
					xPos += 5;
				}
				else if (direction == 1) {
					xPos -= 5;
				}
			}
			timeCount++;
			break;
		case static_cast<int>(skillsIdTable::pierceArrow):
			if (timeCount >= 20) {
				effectObj[0]->SetTopLeft(direction, AnimationCount[0] % 6, xPos, yPos);
				effectObj[0]->OnShow(direction, AnimationCount[0] % 6);
				AnimationCount[0]++;
				//SkillsProcess(theOthersPosition, mainTime - createdTime);
				if (direction == 0) {
					xPos += 8;
				}
				else if (direction == 1) {
					xPos -= 8;
				}
			}
			timeCount++;
			break;
		case static_cast<int>(skillsIdTable::EnergyBlast):
			effectObj[0]->SetTopLeft(direction, AnimationCount[0] % 4, xPos, yPos);
			effectObj[0]->OnShow(direction, AnimationCount[0] % 4);
			if (timeCount >= 20) {
				int dd;
				if (direction == 0) {
					dd = -50;
				}
				else if (direction == 1) {
					dd = +50;
				}
				effectObj[1]->SetTopLeft(direction, AnimationCount[1] % 4, xPos + dd, yPos);
				effectObj[1]->OnShow(direction, AnimationCount[1] % 4);
				AnimationCount[1]++;
			}
			AnimationCount[0]++;
			if (direction == 0) {
				xPos += 5;
			}
			else if (direction == 1) {
				xPos -= 5;
			}
			timeCount++;
			break;
		default:
			break;
		}
	}

	SkillEffect::~SkillEffect() {
		vector<GameObject*>().swap(effectObj);
	}
}