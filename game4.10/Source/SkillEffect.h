#pragma once
#include "GameObject.h"
namespace game_framework {
	class SkillEffect {
	public:
		SkillEffect(int skillID, int createdTimes, int direction, int xPos, int yPos);
		int SkillsProcess(vector<pair<int, int>> theOthersPosition, int duration);
		void SkillsFeedbackStatus(vector<pair<int, int>>  theOthersPosition);
		boolean GarbageCollectorTimer(int duration);
		//void GarbageCollector();
		~SkillEffect();
		int createdTime;
		void OnShow(int id_x, int id_y, vector<pair<int, int>>theOthersPosition,int mainTime);
		void SetEffectObj(int direction, int x, int y);//x :腳色的 X ; y :腳色的Y
	protected:
		int xPos, yPos;
		int direction;
		int AnimationState;
		int AnimationCount;
		vector<string> feedbackStatus;
		vector<GameObject*> effectObj;
	private:
		int skillID;
		void CreatEffectObj();

		enum class skillsIdTable {
			frozenWave, frozenPunch, frozenSword, frozenStorm
		};
	};

}