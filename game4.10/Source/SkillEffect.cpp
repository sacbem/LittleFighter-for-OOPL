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
		default:
			break;
		}
	}

	void SkillEffect::OnShow() {
		switch (skillID) {
			//////////////// Freeze
		case static_cast<int>(skillsIdTable::frozenWave):
			//effectObj[0]->OnShow(id_x, id_y);
			//TRACE("skill show %d %d\n", id_x, id_y);
			if (timeCount >= 16) {
				effectObj[0]->SetTopLeft(direction, AnimationCount[0] % 6, xPos, yPos);
				effectObj[0]->OnShow(direction, AnimationCount[0] % 6);
				//TRACE("Count %d\n", AnimationCount);
				AnimationCount[0]++;
				if (direction == 0) {
					xPos += 5;
				}
				else if (direction == 1) {
					xPos -= 5;
				}
			}
			timeCount++;

			/*
			for (auto& i : effectObj) {
				i->OnShow(direction, AnimaiotnState);
			}
			*/
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
			//for (auto& i : effectObj) {

			//}
			break;
		case static_cast<int>(skillsIdTable::frozenSword):
			//for (auto& i : effectObj) {

			//}
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
			//for (auto& i : effectObj) {

			//}
			break;
			////////////////
		default:
			break;
		}
		/*
			CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
			CFont f, * fp;
			f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
			fp = pDC->SelectObject(&f);					// 選用 font f
			pDC->SetBkColor(RGB(0, 0, 0));
			pDC->SetTextColor(RGB(255, 255, 0));
			CString str;
			str.Format("%d", AnimationCount);
			pDC->TextOut(xPos+50, yPos, str);
			pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
			CDDraw::ReleaseBackCDC();
		*/
	}

	void  SkillEffect::SetEffectObj(int dir, int x, int y) { //按下組合鍵後 被呼叫一次
		switch (skillID) {
			//////////////// Freeze
		case static_cast<int>(skillsIdTable::frozenWave):
			//TRACE("skill setEffect %d %d\n", x, y);
			//for (auto& i : effectObj) {
				//i->SetTopLeft(direction, AnimationState, x, y);
			//}
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
	boolean  SkillEffect::SkillsProcess(vector<pair<int, int>>theOthersPosition,int duration) {
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

		if (GarbageCollectorTimer(duration)) {
			return true;
		}
		else {
			return false;
		}
	}
	boolean SkillEffect::GarbageCollectorTimer(int duration) {
		const int skill_duration_1 = 5;
		switch (duration) {
		case skill_duration_1:
			return true;
			break;
		default:
			return false;
			break;
		}
	}
	void  SkillEffect::SkillsFeedbackStatus(vector<pair<int, int>> theOthersPosition) {

		switch (skillID) {
			//////////////// Freeze
		case static_cast<int>(skillsIdTable::frozenWave):
			for (auto& i : effectObj) {
				for (int h = 0; h < theOthersPosition.size(); h++) {
					if (i->GetPositionXY("X") == theOthersPosition[h].first) {
						if (i->GetPositionXY("Y") == theOthersPosition[h].second) {
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