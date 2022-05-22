#pragma once
#include "Character.h"
#include "GameObject.h"

namespace game_framework {
	class FieldObject {
	public:
		FieldObject(int num);
		// 0	box
		// 1	stone
		void Init();
		void Throw(bool flag, int dir);
		void SetKnock();
		void PickedUp(Character &player);
		void OnMove();
		void ShowAnimation();
		void ShowStatic();
		void ShowRoll();
		int GetY();
		int Hp;
		~FieldObject();
	protected:
		int id;
		GameObject* Obj;
		int spawnX, spawnY;
		int xPos, yPos;
		int YVelocity;
		int InitialVelocity;
		int direction;
		int state;
		// static		0
		// isHolding	1
		// isThrow		2
		// isRoll		3
		int AnimationState;
		int AnimationCount;
	private:
		enum class objectIdTable {
			Box, Stone
		};
	};
}
