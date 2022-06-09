#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameObject.h"
#include "FieldObject.h"

namespace game_framework {
	FieldObject::FieldObject(int num, int mapID) {
		OwnerId = -1;
		OwnerAnimationState = -1;
		id = num;
		switch (num)
		{
		case 0:
			TRACE("0\n");
			itemType = 1;
			AnimationState = 5;
			break;
		case 1:
			TRACE("1\n");
			itemType = 1;
			AnimationState = 5;
			break;
		case 2:
			TRACE("2\n");
			itemType = 2;
			AnimationState = 1;
			break;
		default:
			break;
		}
		Hp = 20;
		direction = 0;
		AnimationCount = 0;
		state = 0;
		liftCount = 0;
		fixAniCount = 0;
		SetMapBorder(mapID);
		Init();
	}

	FieldObject::FieldObject(int num, int mapID, int Owner, int x, int y) {
		OwnerId = Owner;
		id = num;
		switch (num)
		{
		case 0:
			TRACE("0\n");
			itemType = 1;
			AnimationState = 5;
			break;
		case 1:
			TRACE("1\n");
			itemType = 1;
			AnimationState = 5;
			break;
		case 2:
			TRACE("2\n");
			itemType = 2;
			AnimationState = 1;
			break;
		default:
			break;
		}
		TRACE("Get Type %d %d\n", itemType, num);
		Hp = 20;
		direction = 0;
		AnimationCount = 0;
		state = 0;
		liftCount = 0;
		fixAniCount = 0;
		SetMapBorder(mapID);
		Init();

		spawnX = x;
		spawnY = y;
		xPos = x;
		yPos = y;
		xBitmap = x;
		yBitmap = y;
	}

	void FieldObject::SetMapBorder(int mapID) {
		xMapBorderMin = -50;
		xMapBorderMax = 810;
		switch (mapID) {
		case 0:
			yMapBorderMin = 300;
			yMapBorderMax = 500;
		case 1:
			yMapBorderMin = 255;
			yMapBorderMax = 530;
			break;
		case 2:
			yMapBorderMin = 240;
			yMapBorderMax = 450;
			break;
		default:
			break;
		}
	}

	void FieldObject::Init() {
		switch (id)
		{
		case 0:
			Obj = new GameObject(2, "Weapon");
			Obj->Load(".//res//Box//Box_0//box_0.bmp", RGB(0, 0, 0));

			Obj->Load(0, ".//res//Box//Box_0//box_0.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//Box//Box_0//box_1.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//Box//Box_0//box_2.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//Box//Box_0//box_3.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//Box//Box_0//box_4.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//Box//Box_0//box_5.bmp", RGB(0, 0, 0));

			Obj->Load(1, ".//res//Box//Box_0_reverse//box_reverse_1.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//Box//Box_0_reverse//box_reverse_2.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//Box//Box_0_reverse//box_reverse_3.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//Box//Box_0_reverse//box_reverse_4.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//Box//Box_0_reverse//box_reverse_5.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//Box//Box_0_reverse//box_reverse_6.bmp", RGB(0, 0, 0));
			break;
		case 1:
			Obj = new GameObject(2, "Weapon");
			Obj->Load(".//res//Stone//Stone_0//stone_0.bmp", RGB(0, 0, 0));

			Obj->Load(0, ".//res//Stone//Stone_0//stone_0.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//Stone//Stone_0//stone_1.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//Stone//Stone_0//stone_2.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//Stone//Stone_0//stone_3.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//Stone//Stone_0//stone_4.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//Stone//Stone_0//stone_5.bmp", RGB(0, 0, 0));

			Obj->Load(1, ".//res//Stone//Stone_0_reverse//stone_reverse_1.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//Stone//Stone_0_reverse//stone_reverse_2.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//Stone//Stone_0_reverse//stone_reverse_3.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//Stone//Stone_0_reverse//stone_reverse_4.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//Stone//Stone_0_reverse//stone_reverse_5.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//Stone//Stone_0_reverse//stone_reverse_6.bmp", RGB(0, 0, 0));
			break;
		case 2:
			Obj = new GameObject(2, "Weapon");
			Obj->Load(".//res//frozen_sword//frozen_sword_0//frozen_sword_20.bmp", RGB(0, 0, 0));

			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_20.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_21.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_22.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_23.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_24.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_25.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_26.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_27.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_28.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_29.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_30.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_31.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_32.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_33.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_34.bmp", RGB(0, 0, 0));
			Obj->Load(0, ".//res//frozen_sword//frozen_sword_0//frozen_sword_35.bmp", RGB(0, 0, 0));

			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_29.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_28.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_27.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_26.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_25.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_24.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_23.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_22.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_21.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_20.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_39.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_38.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_37.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_36.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_35.bmp", RGB(0, 0, 0));
			Obj->Load(1, ".//res//frozen_sword//frozen_sword_0_reverse//frozen_sword_reverse_34.bmp", RGB(0, 0, 0));
			break;

		default:
			break;
		}
		
		srand(time(NULL));
		//spawn random x
		//xMapBorderMax
		spawnX = rand() % (xMapBorderMax - xMapBorderMin + 1) + xMapBorderMin;
		spawnY = rand() % (yMapBorderMax - yMapBorderMin + 1) + yMapBorderMin;
		//spawnX = 350;
		//spawnY = 350;
		xPos = spawnX;
		yPos = -80;
		xBitmap = xPos;
		yBitmap = yPos;
		
		Obj->SetTopLeft(direction, 0, spawnX, -80);

		//set velocity
		InitialVelocity = 1;
		YVelocity = InitialVelocity;
	}

	int FieldObject::HitPlayer(int ownerid, int tx1, int ty1, int tx2, int ty2, bool isAttacking, bool isAttackFrame) {
		int yRange1 = ty1 - 20;
		int yRange2 = ty1 + 20;
		if (yRange1 <= ty1 && ty1 <= yRange2) {
			if (isAttacking) {
				TRACE("Object Hp %d\n", Hp);
				return HitRectangle(ownerid, tx1 + 30, ty1 + 20, tx2 - 30, ty2 - 20, isAttackFrame);
			}
		}
		else {
			return 0;
		}
	}

	int FieldObject::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
		int x1 = xPos;
		int y1 = yPos;
		int x2 = x1 + 58;
		int y2 = y1 + 58;

		if (tx2 >= x1 && ty2 >= y1 && tx1 <= x2 && ty1 <= y2) {
			int yRange1 = ty1 - 20;
			int yRange2 = ty1 + 20;
			if (yRange1 <= ty1 && ty1 <= yRange2) {
				return 1;
			}
		}
		else {
			return 0;
		}
	}

	int FieldObject::HitRectangle(int ownerId, int tx1, int ty1, int tx2, int ty2, bool AttackFrame) {
		int x1 = xPos;
		int y1 = yPos;
		int x2 = x1 + 58;
		int y2 = y1 + 58;

		if (tx2 >= x1 && ty2 >= y1 && tx1 <= x2 && ty1 <= y2) {
			if (state == 0) {
				if (AttackFrame) {
					Hp -= 1;
				}
				//state = 1;
				OwnerId = ownerId;
				return 1;
			}
		}
		else {
			return 0;
		}
	}

	int FieldObject::HitRectangle(int ownerId, int tx1, int ty1, int tx2, int ty2) {
		int x1 = xPos;
		int y1 = yPos;
		int x2 = x1 + 58;
		int y2 = y1 + 58;

		if (tx2 >= x1 && ty2 >= y1 && tx1 <= x2 && ty1 <= y2) {
			if (state == 0) {
				//state = 1;
				OwnerId = ownerId;
				return 1;
			}
		}
		else {
			return 0;
		}
	}

	int FieldObject::HitWeapon(int tx1, int ty1, int tx2, int ty2) {
		int x1 = xBitmap;
		int y1 = yBitmap;
		int x2 = x1 + 58;
		int y2 = y1 + 58;


		if (tx2 >= x1 && ty2 >= y1 && tx1 <= x2 && ty1 <= y2) {
			int yRange1 = ty1 - 20;
			int yRange2 = ty1 + 20;
			if (yRange1 <= ty1 && ty1 <= yRange2) {
				return 1;
			}
		}
		else {
			return 0;
		}
	}


	void FieldObject::SetState(int s) {
		state = s;
	}

	void FieldObject::SetOwner(int id) {
		OwnerId = id;
	}

	void FieldObject::SetXY(int x, int y) {
		xPos = x > xMapBorderMax ? xMapBorderMax : x;
		xPos = xPos < xMapBorderMin ? xMapBorderMin : xPos;
		yPos = y > yMapBorderMax ? yMapBorderMax : y;
		yPos = yPos < yMapBorderMin ? yMapBorderMin : yPos;
		xBitmap = xPos;
		yBitmap = yPos;
		Obj->SetTopLeft(xPos, yPos);
	};

	int FieldObject::GetState() {
		return state;
	}

	int FieldObject::GetOwner() {
		return OwnerId;
	}

	int FieldObject::GetDir() {
		return direction;
	}

	int FieldObject::GetHp() {
		return Hp;
	}

	void FieldObject::DetectAnimation(int x, int y, int Animation, int CAniCurrent) {
		//TRACE("getAni %d\n", Animation);
		OwnerAnimationState = Animation;
		switch (Animation)
		{
		case 0: case 1:
			if (direction == 0) {
				xBitmap = x - 5;
			}
			else {
				xBitmap = x + 15;
			}
			yBitmap = y - 20;
			AnimationState = 15;
			break;
		case 2:
			switch (CAniCurrent)
			{
			case 3:
				AnimationState = 14;
				if (direction == 0) {
					xBitmap = x + 7;
				}
				else {
					xBitmap = x+7;
				}
				yBitmap = y - 15;
				break;
			case 2:
				AnimationState = 1;
				if (direction == 0) {
					xBitmap = x + 18;
				}
				else {
					xBitmap = x-5;
				}
				yBitmap = y - 20;
				break;
			case 0:
				AnimationState = 1;
				if (direction == 0) {
					xBitmap = x + 18;
				}
				else {
					xBitmap = x - 5;
				}
				yBitmap = y - 20;
				break;
			case 1:
				AnimationState = 5;
				if (direction == 0) {
					xBitmap = x;
				}
				else {
					xBitmap = x;
				}
				yBitmap = y + 23;
				break;
			default:
				break;
			}
			break;
		case 3:
			AnimationState = 5;
			if (direction == 0) {
				xBitmap = x+20;
			}
			else {
				xBitmap = x;
			}
			yBitmap = y + 23;
			break;
		case 4: case 5: case 10:
			AnimationState = 5;
			if (direction == 0) {
				xBitmap = x;
			}
			else {
				xBitmap = x;
			}
			yBitmap = y + 40;
			break;
		case 6: case 102:
			AnimationState = 5;
			if (direction == 0) {
				xBitmap = x;
			}
			else {
				xBitmap = x;
			}
			yBitmap = y + 20;
			break;
		case 7: case 8: case 9:
			AnimationState = 1;
			if (direction == 0) {
				xBitmap = x + 18;
			}
			else {
				xBitmap = x - 5;
			}
			yBitmap = y - 20;
			break;
		case 100: case 101: case 110: case 120:
			AnimationState = 13;
			if (direction == 0) {
				xBitmap = x-20;
			}
			else {
				xBitmap = x+20;
			}
			yBitmap = y - 5;
			break;
		case 103:
			AnimationState = 6;
			if (direction == 0) {
				xBitmap = x;
			}
			else {
				xBitmap = x;
			}
			yBitmap = y + 14;
			break;
		case 104:
			AnimationState = 5;
			if (direction == 0) {
				xBitmap = x+4;
			}
			else {
				xBitmap = x-4;
			}
			yBitmap = y + 18;
			break;
		case 105:
			AnimationState = 5;
			if (direction == 0) {
				xBitmap = x + 4;
			}
			else {
				xBitmap = x - 4;
			}
			yBitmap = y + 18;
			break;
		case 111: case 121:
			AnimationState = 5;
			if (direction == 0) {
				xBitmap = x + 23;
			}
			else {
				xBitmap = x - 23;
			}
			yBitmap = y - 7;
			break;
		case 112: case 113: case 122: case 123:
			AnimationState = 4;
			if (direction == 0) {
				xBitmap = x + 32;
			}
			else {
				xBitmap = x - 32;
			}
			yBitmap = y - 2;
			break;
		case 114: case 115: case 116: case 125: case 126:
			AnimationState = 5;
			if (direction == 0) {
				xBitmap = x;
			}
			else {
				xBitmap = x;
			}
			yBitmap = y + 40;
			break;
		case 124:
			AnimationState = 5;
			if (direction == 0) {
				xBitmap = x+40;
			}
			else {
				xBitmap = x-40;
			}
			yBitmap = y + 40;
			break;
		case 1100:
			if (direction == 0) {
				xBitmap = x - 5;
			}
			else {
				xBitmap = x + 15;
			}
			yBitmap = y - 20;
			AnimationState = 15;
			break;
		case 1101:
			AnimationState = 13;
			if (direction == 0) {
				xBitmap = x - 23;
			}
			else {
				xBitmap = x + 23;
			}
			yBitmap = y - 33;
			break;
		case 1103:
			AnimationState = 2;
			if (direction == 0) {
				xBitmap = x + 50;
			}
			else {
				xBitmap = x-30;
			}
			yBitmap = y - 3;
			break;
		case 1110:
			AnimationState = 12;
			if (direction == 0) {
				xBitmap = x - 36;
			}
			else {
				xBitmap = x + 36;
			}
			yBitmap = y - 5;
			break;
		case 1111: case 1120:
			AnimationState = 13;
			if (direction == 0) {
				xBitmap = x - 11;
			}
			else {
				xBitmap = x + 11;
			}
			yBitmap = y - 19;
			break;
		case 1121: case 1102: case 1112:
			AnimationState = 4;
			if (direction == 0) {
				xBitmap = x + 57;
			}
			else {
				xBitmap = x - 30;
			}
			yBitmap = y + 16;
			break;
		case 1130: case 1140:
			AnimationState = 14;
			if (direction == 0) {
				xBitmap = x - 26;
			}
			else {
				xBitmap = x + 26;
			}
			yBitmap = y - 36;
			break;
		case 1131: case 1141:
			AnimationState = 14;
			if (direction == 0) {
				xBitmap = x - 11;
			}
			else {
				xBitmap = x + 11;
			}
			yBitmap = y - 56;
			break;
		case 1132: case 1142:
			AnimationState = 2;
			if (direction == 0) {
				xBitmap = x + 41;
			}
			else {
				xBitmap = x - 41;
			}
			yBitmap = y - 16;
			break;
		case 1133: case 1143:
			AnimationState = 2;
			if (direction == 0) {
				xBitmap = x + 37;
			}
			else {
				xBitmap = x - 37;
			}
			yBitmap = y - 10;
			break;
		default:
			if (direction == 0) {
				xBitmap = x - 5;
			}
			else {
				xBitmap = x + 15;
			}
			yBitmap = y - 20;
			AnimationState = 15;
			break;
		}
	}


	void FieldObject::liftUp(bool flag, int x, int y, int dir, int ani, int CAniCurrent) {
		switch (itemType)
		{
		case 1:
			if (flag == true) {
				xPos = x+10;
				yPos = y-40;
				xBitmap = xPos;
				yBitmap = yPos;
				direction = dir;
				state = 1;
			}
			else if (flag == false) {
				spawnY = y + 22;
				state = 3;
			}
			liftCount++;
			break;
		case 2:
			if (flag == true) {
				xPos = x;
				yPos = y+50;
				direction = dir;
				state = 1;
				DetectAnimation(x,y,ani, CAniCurrent);
				//AnimationState = 1;
			}
			else if (flag == false) {
				spawnY = y + 22;
				state = 3;
			}
			liftCount++;
			break;
		default:
			break;
		}
	};

	void FieldObject::ShowAnimation() {
		Obj->SetTopLeft(direction, AnimationState, xBitmap, yBitmap);
		Obj->OnShow(direction, AnimationState);
	}

	void FieldObject::OnMove() {
		//TRACE("Owner %d\n", OwnerId);
		if (state != 1) {
			if (yPos < spawnY) {
				yPos += YVelocity;
				xBitmap = xPos;
				yBitmap = yPos;
				Obj->SetTopLeft(direction, AnimationState, xBitmap, yBitmap);
				YVelocity++;
			}
			else {
				yPos = spawnY;
				xBitmap = xPos;
				yBitmap = yPos;
				Obj->SetTopLeft(direction, AnimationState, xBitmap, yBitmap);
				YVelocity = InitialVelocity;
			}

			if (state == 2 || state==3) {
				ShowRoll();
			}
			else if (state == 0) {
				ShowStatic();
				OwnerId = -1;
				OwnerAnimationState = -1;
			}
		}
	}

	int FieldObject::GetX() {
		return xPos;
	}

	int FieldObject::GetY() {
		return yPos;
	}

	int FieldObject::GetXB() {
		return xBitmap;
	}

	int FieldObject::GetYB() {
		return yBitmap;
	}

	void FieldObject::ShowStatic() {
		if (itemType == 1) {
			Obj->SetTopLeft(direction, 0, xPos, yPos);
			Obj->OnShow(direction, 0);
		}
		else if(itemType==2) {
			Obj->SetTopLeft(direction, 0, xBitmap, yBitmap);
			Obj->OnShow(direction, 0);
		}
	}

	void FieldObject::ShowRoll() {
		if (state == 2 || state == 3) {
			if (itemType == 1) {
				AnimationCount++;
				if (AnimationCount <= 4) {
					AnimationState = 1;
				}
				else if (AnimationCount <= 8) {
					AnimationState = 2;
				}
				else if (AnimationCount <= 12) {
					AnimationState = 3;
				}
				else if (AnimationCount <= 16) {
					AnimationState = 4;
				}
				else if (AnimationCount <= 20) {
					AnimationState = 5;
					if (AnimationCount >= 20) {
						AnimationCount = 0;
						Hp -= 5;
						state = 0;
					}
				}
				if (direction == 0) {
					xPos += 10;
					xBitmap = xPos;
					yBitmap = yPos;
					Obj->SetTopLeft(direction, AnimationState, xBitmap, yBitmap);
				}
				else if (direction == 1) {
					xPos -= 10;
					xBitmap = xPos;
					yBitmap = yPos;
					Obj->SetTopLeft(direction, AnimationState, xBitmap, yBitmap);
				}
			}
			else if (itemType == 2) {
				AnimationCount++;
				if (AnimationCount % 2 == 0) {
					AnimationState++;
					if (AnimationState == 16) {
						AnimationState = 0;
					}
				}
				if (AnimationCount >= 20) {
					AnimationCount = 0;
					Hp -= 5;
					state = 0;
				}
				if (direction == 0) {
					xPos += 10;
					xBitmap = xPos;
					yBitmap = yPos;
					Obj->SetTopLeft(direction, AnimationState, xBitmap, yBitmap);
				}
				else if (direction == 1) {
					xPos -= 10;
					xBitmap = xPos;
					yBitmap = yPos;
					Obj->SetTopLeft(direction, AnimationState, xBitmap, yBitmap);
				}
			}
		}
	}

	void FieldObject::Throw(bool flag, int dir) {
		if (flag == true) {
			state = 3;
			direction = dir;
		}
		else if(flag==false) {
			state = 0;
			AnimationCount = 0;
		}
	}

	bool FieldObject::isAttackFrame() {
		switch (OwnerAnimationState)
		{
		case 1102: case 1103: case 1111: case 1112: case 1121:  case 1132: case 1133: case 1142: case 1143:
			return true;
			break;
		default:
			return false;
			break;
		}
	}

	FieldObject::~FieldObject() {
		delete Obj;
	}
}