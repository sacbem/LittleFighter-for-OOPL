#pragma once
#include "GameObject.h"

namespace game_framework {
	class FieldObject {
	public:
		FieldObject(int num, int MapID);
		//Heavy Object
		// 0	box
		// 1	stone
		//Weapon
		// 2 Frozen Sword
		int itemType;
		// 0 NONE
		// 1 HeavyObject type
		// 2 weapon type
		void Init();
		void Throw(bool flag, int dir);
		void SetKnock();
		void SetState(int s);
		void SetOwner(int id);
		void SetXY(int x, int y);
		void SetMapBorder(int mapID);
		//for weapon type function
		void SetAnimationState(int aniState);
		int GetAnimationState();

		//Hit Character
		int HitPlayer(int ownerId, int tx1, int ty1, int tx2, int ty2,bool isAttacking);
		int HitRectangle(int tx1, int ty1, int tx2, int ty2); //for map 
		int HitRectangle(int ownerId, int tx1, int ty1, int tx2, int ty2); //for grab

		void liftUp(bool flag, int x, int y, int dir);
		void PickedUp(bool flag, int x, int y);
		int GetState();
		int GetOwner();
		int GetDir();
		void OnMove();
		void ShowAnimation();
		void ShowStatic();
		void ShowRoll();
		int GetX();
		int GetY();
		int Hp;
		~FieldObject();
	protected:
		int OwnerId;
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
		// is Throw     2
		// isRoll		3
		int AnimationState;
		int AnimationCount;

		int xMapBorderMin;
		int xMapBorderMax;
		int yMapBorderMin;
		int yMapBorderMax;
	private:
		enum class objectIdTable {
			Box, Stone
		};
	};
}
