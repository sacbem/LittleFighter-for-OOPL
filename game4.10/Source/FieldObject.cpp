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
		id = num;
		direction = 0;
		AnimationState = 5;
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
		spawnX = rand() % (600 - 100 + 1) + 100;
		spawnY = rand() % (400 - 200 + 1) + 200;

		xPos = spawnX;
		yPos = -80;
		
		
		Obj->SetTopLeft(direction, 0, spawnX, -80);

		//set velocity
		InitialVelocity = 10;
		YVelocity = InitialVelocity;
	}

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
		}
	}
	int FieldObject::GetY() {
		return yPos;
	}
	void FieldObject::ShowRoll() {
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
			if (AnimationCount == 20) {
				state = 0;
			}
		}
		AnimationCount++;
		if (direction == 0) {
			xPos += 1;
			Obj->SetTopLeft(direction, AnimationState, xPos, yPos);
		}
		else if (direction == 1) {
			xPos -= 1;
			Obj->SetTopLeft(direction, AnimationState, xPos, yPos);
		}
	}

	FieldObject::~FieldObject() {
		delete Obj;
	}
}