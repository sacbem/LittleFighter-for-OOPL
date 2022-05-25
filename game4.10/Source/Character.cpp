#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include "FieldObject.h"
#include "time.h"
#include <cmath>
#include <algorithm>
#include <time.h>
namespace game_framework {
	Character::Character() {
		Initialize();
	}
	void Character::Initialize() {
		DelayCounter = 50;
		Delay = 30;

		xPos = 200;
		yPos = 200;
		skillSignal = -1;
		xAccumulator = yAccumulator = 200;
		//moving statement
		isRunning = isWalking = isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		UnMovable = StopRun = false;

		isDefense = false;
		isGettingHit = false;
		isAttacking = false;
		isHitting = false;
		hitDirection = 0;
		KnockSpeed = 0;

		itemId = -1;
		isCarryItem = false;
		isDropItem = false;

		//init jump
		isJumpping = island = false;

		direction = 1;

		HealthPoint = 1800;
		InnerHealPoint = 1800;
		Mana = 900;
		InnerMana = 1800;

		AttackPoint = 10;
		DefencePoint = 5;
		walkedDistance = 0;
		SetMapBorder(0);

		//re
		AnimationState = 0;
		speed = 2;
		AttackCount = 0;

		KnockState = 0;
		LastKnockState = 0;
		if (direction == 0) {
			if (hitDirection == 0) {
				KnockSpeed = -1;
			}
			else if (hitDirection == 1) {
				KnockSpeed = 1;
			}
		}
		else if (direction == 1) {
			if (hitDirection == 0) {
				KnockSpeed = 1;
			}
			else if (hitDirection == 1) {
				KnockSpeed = -1;
			}
		}

		//time
		KeyBoardInputTime = 0;
		LastInputTime = 0;
	}
	
	Character::Character(Character const& other) : name(other.name) {
		Initialize();
	}

	void Character::SetPickup(bool flag, int Id) {
		if (flag == true) {
			if (isCarryItem == false && isDropItem == false) {
				if (itemId == -1) {
					//TRACE("Call PickUP\n");
					isCarryItem = true;
					isDropItem = false;
					itemId = Id;
				}
			}
		}
		else if (flag == false) {
			//TRACE("Call NOT PickUP\n");
			isCarryItem = false;
			isDropItem = true;
			itemId = -1;
		}
	}

	void Character::Pickup(FieldObject *other) {
		other->liftUp(true,xPos,yPos,direction);
	}

	bool Character::GetAlive() {
		return isAlive;
	}

	int Character::GetX1() {
		return xPos;
	}
	
	boolean Character::IsStatic() {
		return this->AnimationState ? false : true;
	}
	boolean Character::IsInBorder(int mapID) {
		return xPos == 0 || xPos == 794 ? true : false;
	}
	int Character::GetX2() {
		return xPos + Animation.Normal[0].Width();
	}

	int Character::GetY1() {
		return yPos;
	}

	int Character::GetY2() {
		return yPos + Animation.Normal[0].Height();
	}

	int Character::GetHealth() {
		return HealthPoint;
	}

	int Character::GetDir() {
		return direction;
	}
	int Character::GetMovingUp_Down() {
		if (isMovingDown) {
			return 1;
		}
		if (isMovingUp) {
			return 2;
		}
		return 0;
	}
	int Character::GetSkillSignal() {
		return skillSignal;
	}
	boolean Character::GetCalculateDamageRequest() {
		return calculateDamage_Request;
	}
	void Character::DistaceAccumulator() {
		walkedDistance = (abs((GetX1() - xAccumulator) ^ 2 + (GetY1() - yAccumulator) ^ 2)) ^ (1 / 2);
		
	}
	
	int Character::GetDistance() {
		return walkedDistance;
	}
	
	int Character::GetMovingTime(boolean isLeft){
		return isLeft ? leftTime : rightTime;
	}
	
	boolean Character::DistanceAccumulatorReset() {
		if ( walkedDistance < 5 && AnimationState != 0 ) {
			return false;
		}
		else {
			walkedDistance = 0;
			xAccumulator = xPos;
			yAccumulator = yPos;
			return true;
		}
	}
	void Character::SetCalculateDamageRequest(boolean val) {
		calculateDamage_Request = val;
	}
	void Character::isGettingDamage(int Damage) {
		HealthPoint -= Damage;
		InnerHealPoint -= Damage / 2;
		DamageAccumulator += Damage;
	}

	void Character::InputKeyDown(UINT nChar, int createdTime, int playerID) {
		const char KEY_LEFT = playerID ? 0x25 : 0x41; // keyboard���b�Y 0x25
		const char KEY_UP = playerID ? 0x26: 0x57; // keyboard�W�b�Y 0x26
		const char KEY_RIGHT = playerID ? 0x27 : 0x44; // keyboard�k�b�Y 0x27
		const char KEY_DOWN = playerID ? 0x28 : 0x53; // keyboard�U�b�Y 0x28
		const char KEY_SPACE = playerID ? 0x30 : 0x20; // keyboard SPACE
		const char KEY_CTRL = playerID ? 0x31 : 0x11; //keyboard ctrl
		const char KEY_ENTER = playerID ? 0x32 : 0x0D; // keyboard ENTER
		
		const char KEY_H = 0x48;
		const char KEY_J = 0x4A;
		const char KEY_K = 0x4B;
		const char KEY_L = 0x4C;
		const char KEY_U = 0x55;

		const char KEY_Z = 0x5A;
		const char KEY_X = 0x58;
		const char KEY_C = 0x43;
		const char KEY_V = 0x56;
		const char KEY_B = 0x42;

		Diff = KeyBoardInputTime - LastInputTime;
		LastInputTime = KeyBoardInputTime;
		if (!UnMovable) {
			//here has a problem
			if (isRunning) {
				if (direction == 0) {
					if (nChar == KEY_LEFT) {
						SetRunning(false);
					}
				}
				else if (direction == 1) {
					if (nChar == KEY_RIGHT) {
						SetRunning(false);
					}
				}
			}
			else if (!isRunning && !isWalking) {
				//Sp
				if (nChar == KEY_H) {
					//TRACE("Sp \n");
					if (Mana >= 250) {
						Mana -= 10;
						skillSignal = 0;
						UnMovable = true;
					}
				}
				else if (nChar == KEY_J) {
					//TRACE("Sp \n");
					if (Mana >= 250) {
						Mana -= 10;
						skillSignal = 1;
						UnMovable = true;
					}
				}
				else if (nChar == KEY_K) {
					//TRACE("Sp \n");
					if (Mana >= 250) {
						Mana -= 10;
						skillSignal = 2;
						UnMovable = true;
					}
				}
				else if (nChar == KEY_L) {
					//TRACE("Sp \n");
					if (Mana >= 250) {
						Mana -= 10;
						skillSignal = 3;
						UnMovable = true;
					}
				}
				else if (nChar == KEY_U) {
					//TRACE("Sp \n");
					if (Mana >= 250) {
						Mana -= 10;
						skillSignal = 4;
						UnMovable = true;
					}
				}
				
				SetSkill(createdTime);
			}
			//detect double click
			if (Diff <= 20) {
				if (nChar == KEY_LEFT && LastInput == KEY_LEFT) {
					SetMovingLeft(true);
					SetRunning(true);
				}
				else if (nChar == KEY_RIGHT && LastInput == KEY_RIGHT) {
					SetMovingRight(true);
					SetRunning(true);
				}
			}
			if (nChar == KEY_LEFT) {
				SetMovingLeft(true);
				L_start = clock();
			}
			if (nChar == KEY_RIGHT) {
				SetMovingRight(true);
				R_start = clock();
			}
			if (nChar == KEY_UP) {
				SetMovingUp(true);
			}
			if (nChar == KEY_DOWN) {
				SetMovingDown(true);
			}
			if (nChar == KEY_SPACE) {
				SetJumpping(true);
			}
			if (nChar == KEY_CTRL) {
				SetDefense(true);
			}
		}
		if (nChar == KEY_ENTER) {
			SetAttack(true);
			if (isCarryItem == true) {
				SetPickup(false, itemId);
			}
		}
		/*
		if (nChar == KEY_TEST_SKILL1) {
			skillSignal = 0;
		}
		*/
	}

	void Character::InputKeyUp(UINT nChar, int playerID) {
		const char KEY_LEFT = playerID ? 0x25 : 0x41; // keyboard���b�Y 0x25
		const char KEY_UP = playerID ? 0x26 : 0x57; // keyboard�W�b�Y 0x26
		const char KEY_RIGHT = playerID ? 0x27 : 0x44; // keyboard�k�b�Y 0x27
		const char KEY_DOWN = playerID ? 0x28 : 0x53; // keyboard�U�b�Y 0x28

		const char KEY_SPACE = playerID ? 0x30 : 0x20; // keyboard SPACE
		const char KEY_ENTER = playerID ? 0x32 : 0x0D; // keyboard ENTER
		

		if (nChar == KEY_LEFT) {
			if (isRunning == false) {
				SetMovingRight(false);
			}
		}
		if (nChar == KEY_RIGHT) {
			if (isRunning == false) {
				SetMovingLeft(false);
			}
		}

		if (nChar == KEY_LEFT) {
			SetMovingLeft(false);
		}
		if (nChar == KEY_RIGHT) {
			SetMovingRight(false);
		}
		if (nChar == KEY_UP) {
			SetMovingUp(false);
		}
		if (nChar == KEY_DOWN) {
			SetMovingDown(false);
		}
		if (nChar == KEY_SPACE) {
			SetJumpping(false);
		}

		if (AttackCount >= 30) {
			if (nChar == KEY_ENTER) {
				SetAttack(false);
			}
		}
		LastInput = nChar;
	}

	void Character::SetMovingDown(bool flag) {
		isMovingDown = flag;
	}

	void Character::SetMovingUp(bool flag) {
		isMovingUp = flag;
	}
	void Character::SetAbonormalStatus(int characterID, boolean val) {
		statusTable.push_back(pair<int, boolean>(characterID, val));
	}
	void Character::SetMovingLeft(bool flag) {
		if (!isRunning) {
			if (flag == true) {
				leftTime = 0;
				isMovingLeft = flag;
				isMovingRight = false;
			}
			else {
				isMovingLeft = flag;
			}
		}
	}

	void Character::SetMovingRight(bool flag) {
		if (!isRunning) {
			if (flag == true) {
				isMovingRight = flag;
				rightTime = 0;
				isMovingLeft = false;
			}
			else {
				isMovingRight = flag;
			}
		}
	}

	void Character::SetRunning(bool flag) {
		if (flag == true) {
			isRunning = flag;
			isWalking = false;
		}
		else {
			isRunning = flag;
			isWalking = false;
			isMovingLeft = false;
			isMovingRight = false;
			StopRun = true;
		}
	}

	void Character::SetJumpping(bool flag) {
		if (!isCarryItem) {
			if (!isJumpping) {
				isJumpping = flag;
				JumpYposTemp = yPos + 1;
				isRising = true;
				AnimationState = 4;
			}
		}
	}

	void Character::SetDefense(bool flag) {
		if (!isCarryItem) {
			isDefense = flag;
			if (flag == true) {
				//reset
				DefenseCount = 0;
			}
		}
	}

	void Character::SetMoving() {
		TRACE("AniState %d\n", AnimationState);
		if (isRunning) {
			if (isJumpping) {
				speed = 7;
			}
			else {
				speed = 5;
			}
		}
		else {
			speed = 2;
		}
		if (isMovingLeft) {
			
			if ((!isDefense && !isAttacking) || isRunning) {
				this->SetXY(xPos - speed, yPos);
				DistaceAccumulator();
				isWalking = true;
				direction = 1;
			}
			//L_finish = clock();
			//leftTime = (L_finish - L_start) / 1000;
			leftTime++;
		}
		if (isMovingRight) {
			
			if ((!isDefense && !isAttacking) || isRunning) {
				this->SetXY(xPos + speed, yPos);
				DistaceAccumulator();
				isWalking = true;
				direction = 0;
			}
			//R_finish = clock();
			//rightTime = (R_finish - R_start) / 1000;
			rightTime++;
		}

		if (isMovingUp) {
			if (!isDefense && !isAttacking) {
				if (!isJumpping) {
					this->SetXY(xPos, yPos - 1);
					isWalking = true;
				}
			}
		}
		if (isMovingDown) {
			if (!isDefense && !isAttacking) {
				if (!isJumpping) {
					this->SetXY(xPos, yPos + 1);
					isWalking = true;
				}
			}
		}

		if (!isMovingUp && !isMovingDown && !isMovingLeft && !isMovingRight) {
			isWalking = false;
			//Walk[direction].Reset();
			if (isCarryItem) {
				AnimationState = 1000;
			}
			else if (!isCarryItem) {
				AnimationState = 0;
			}
		}

		if (isWalking) {
			if (isMovingLeft && isMovingRight) {
				if (isCarryItem) {
					AnimationState = 1000;
				}
				else if (!isCarryItem) {
					AnimationState = 0;
				}
			}
			else {
				if (isCarryItem) {
					AnimationState = 1001;
				}
				else if (!isCarryItem) {
					AnimationState = 1;
				}
			}
		}
		else {
			if (isCarryItem) {
				AnimationState = 1000;
			}
			else if (!isCarryItem) {
				AnimationState = 0;
			}
		}

		if (isRunning) {
			if (isCarryItem) {
				AnimationState = 1010;
			}
			else if (!isCarryItem) {
				AnimationState = 2;
			}
		}
		else if (StopRun) {
			if (RunCount <= 10) {
				RunCount++;
				if (isCarryItem) {
					AnimationState = 1000;
				}
				else if (!isCarryItem) {
					AnimationState = 3;
				}
			}
			else {
				StopRun = false;
				RunCount = 0;
			}
		}
		if (isJumpping) {
			UnMovable = true;
			if (JumpCount == 0) {
				if (isRunning) {
					//init velocity
					InitialVelocity = 10;
					YVelocity = InitialVelocity;
				}
				else {
					InitialVelocity = 12;
					YVelocity = InitialVelocity;
				}
			}
			if (JumpCount < 3) {
				AnimationState = 4;
			}
			else if (JumpCount < 6) {
				AnimationState = 5;
			}
			else if (JumpCount >= 6) {
				AnimationState = 6;
				//make some delay
				if (JumpCount % 2 == 0) {
					if (isRising) {
						AnimationState = 6;
						if (YVelocity > 0) {
							yPos -= YVelocity;
							YVelocity--;
						}
						else {
							isRising = false;
							YVelocity = 1;
							JumpCountTemp = JumpCount + 1;
						}
					}
					else if (!isRising) {
						if (yPos < JumpYposTemp - 1) {
							AnimationState = 6;
							yPos += YVelocity;
							YVelocity++;
						}
						else {
							yPos = JumpYposTemp - 1;
							YVelocity = InitialVelocity;
							island = true;
						}
					}
				}
			}
			if (island) {
				if (JumpCount >= JumpCountTemp * 2 + 6) { 
					isJumpping = false;
					island = false;
					UnMovable = false;
					JumpCount = 0;
					JumpCountTemp = 0;

					if (isRunning) {
						SetRunning(false);
					}
				}
				if (JumpCount >= JumpCountTemp * 2) {
					AnimationState = 5;
				}
			}
		}
	}
	void Character::ClearAbonormalStatus() {
		vector<pair<int, boolean>>().swap(statusTable);
	}
	void Character::SetMapBorder(int mapID) {
		xMapBorderMin = -50;
		xMapBorderMax = 810;
		switch (mapID) {
		case 0:
			yMapBorderMin = 300;
			yMapBorderMax = 500;
		case 1 : 
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

	void Character::SetAlive(bool flag) {
		isAlive = flag;
	}

	void Character::SetXY(int X, int Y) {
		xPos = X > xMapBorderMax ? xMapBorderMax : X;
		xPos = xPos < xMapBorderMin ? xMapBorderMin : xPos;
		if (!isJumpping) {
			yPos = Y > yMapBorderMax ? yMapBorderMax : Y;
			yPos = yPos < yMapBorderMin ? yMapBorderMin : yPos;
		}
		TRACE("Y %d\n", yPos);
	}

	Character::~Character() {

	}
}


