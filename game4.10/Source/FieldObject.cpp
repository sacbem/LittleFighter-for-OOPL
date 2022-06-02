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
		id = num;
		switch (num)
		{
		case 0:
			TRACE("0\n");
			itemType = 1;
			break;
		case 1:
			TRACE("1\n");
			itemType = 1;
			break;
		case 2:
			TRACE("2\n");
			itemType = 2;
			break;
		default:
			break;
		}
		TRACE("Get Type %d %d\n", itemType, num);
		Hp = 20;
		direction = 0;
		AnimationState = 5;
		AnimationCount = 0;
		state = 0;
		SetMapBorder(mapID);
		Init();
		SetMapBorder(mapID);
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
		//spawnX = rand() % (600 - 100 + 1) + 100;
		//spawnY = rand() % (400 - 200 + 1) + 200;
		spawnX = 350;
		spawnY = 350;
		xPos = spawnX;
		yPos = -80;
		
		Obj->SetTopLeft(direction, 0, spawnX, -80);

		//set velocity
		InitialVelocity = 10;
		YVelocity = InitialVelocity;
	}

	int FieldObject::HitPlayer(int ownerid, int tx1, int ty1, int tx2, int ty2, bool isAttacking) {
		int yRange1 = ty1 - 20;
		int yRange2 = ty1 + 20;
		if (yRange1 <= ty1 && ty1 <= yRange2) {
			if (isAttacking) {
				Hp -= 1;
				return HitRectangle(ownerid, tx1 + 30, ty1 + 20, tx2 - 30, ty2 - 20);
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

	int FieldObject::HitRectangle(int ownerid, int tx1, int ty1, int tx2, int ty2) {
		int x1 = xPos;
		int y1 = yPos;
		int x2 = x1 + 58;
		int y2 = y1 + 58;

		if (tx2 >= x1 && ty2 >= y1 && tx1 <= x2 && ty1 <= y2) {
			if (state == 0) {
				//state = 1;
				OwnerId = ownerid;
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

	void FieldObject::liftUp(bool flag, int x, int y, int dir) {
		switch (itemType)
		{
		case 1:
			if (flag == true) {
				xPos = x+10;
				yPos = y-40;
				direction = dir;
				state = 1;
			}
			else if (flag == false) {
				spawnY = y + 22;
				state = 3;
			}
			break;
		case 2:
			if (flag == true) {
				xPos = x;
				yPos = y;
				direction = dir;
				state = 1;
			}
			else if (flag == false) {
				spawnY = y + 22;
				state = 3;
			}
			break;
		default:
			break;
		}
	};

	void FieldObject::ShowAnimation() {
		Obj->SetTopLeft(direction, AnimationState, xPos, yPos);
		Obj->OnShow(direction, AnimationState);
	}

	void FieldObject::OnMove() {
		if (state != 1) {
			if (yPos < spawnY) {
				yPos += YVelocity;
				Obj->SetTopLeft(direction, AnimationState, xPos, yPos);
				YVelocity++;
			}
			else {
				yPos = spawnY;
				Obj->SetTopLeft(direction, AnimationState, xPos, yPos);
				YVelocity = InitialVelocity;
			}

			if (state == 2 || state==3) {
				ShowRoll();
			}
			else if (state == 0) {
				ShowStatic();
				OwnerId = -1;
			}
		}
	}
	int FieldObject::GetX() {
		return xPos;
	}
	int FieldObject::GetY() {
		return yPos;
	}

	void FieldObject::ShowStatic() {
		Obj->SetTopLeft(direction, 0, xPos, yPos);
		Obj->OnShow(direction, 0);
	}

	void FieldObject::ShowRoll() {
		if (state == 2 || state == 3) {
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
				Obj->SetTopLeft(direction, AnimationState, xPos, yPos);
			}
			else if (direction == 1) {
				xPos -= 10;
				Obj->SetTopLeft(direction, AnimationState, xPos, yPos);
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

	FieldObject::~FieldObject() {
		delete Obj;
	}
}