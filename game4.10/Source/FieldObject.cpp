#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameObject.h"
#include "FieldObject.h"

namespace game_framework {
	FieldObject::FieldObject(int num) {
		OwnerId = -1;
		id = num;
		Hp = 20;
		direction = 0;
		AnimationState = 5;
		AnimationCount = 0;
		state = 0;
		Init();
	}

	void FieldObject::Init() {
		switch (id)
		{
		case 0:
			Obj = new GameObject(2, "Weapon");
			//GameObject(2,"Weapon");
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

	int FieldObject::HitRectangle(int ownerid, int tx1, int ty1, int tx2, int ty2) {
		int x1 = xPos;
		int y1 = yPos;
		int x2 = x1 + 58;
		int y2 = y1 + 58;

		if (tx2 >= x1 && ty2 >= y1 && tx1 <= x2 && ty1 <= y2) {
			TRACE("Hit Box 2\n");
			if (state == 0) {
				TRACE("Hit Box & state=0\n");
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
	};

	int FieldObject::GetState() {
		return state;
	}

	void FieldObject::liftUp(bool flag, int x, int y, int dir) {
		if (flag == true) {
			xPos = x+10;
			yPos = y-40;
			direction = dir;
			state = 1;
		}
		else if (flag == false) {
			spawnY = y + 22;
			state = 3;
			OwnerId = -1;
		}
	};

	void FieldObject::ShowAnimation() {
		TRACE("ss %d\n", state);
		//TRACE("AC %d\n", AnimationCount);

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

			if (state == 2 || state == 3) {
				ShowRoll();
			}
			else if (state == 0) {
				ShowStatic();
			}
		}
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