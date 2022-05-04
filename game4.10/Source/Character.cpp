#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include <cmath>
namespace game_framework {

	Character::Character() {
		Initialize();
	}

	Character::Character(Character const & other): name(other.name) {
		Initialize();
	}

	bool Character::GetAlive() {
		return isAlive;
	}

	int Character::GetX1() {
		return xPos;
	}
	boolean Character::IsStatic() {
		if (!this->AnimationState) {
			return true;
		}
		else {
			return false;
		}
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
	void Character::Initialize() {
		DelayCounter = 0;
		Delay = 7;
		
		xPos = 200;
		yPos = 200;
		xAccumulator = yAccumulator = 200;
		//moving statement
		isRunning = isWalking = isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		UnMovable = StopRun = false;

		isDefense = false;

		//init jump
		isJumpping = island = false;

		direction = 1;
		getCharacter = false;

		HealthPoint = 360;
		AttackPoint = 10;
		DefencePoint = 5;
		walkedDistance = 0;
		SetMapBorder(0);

		//re
		AnimationState = 0;
		speed = 2;

		//time
		KeyBoardInputTime = 0;
		LastInputTime = 0;
	}

	void Character::DistaceAccumulator() {
		walkedDistance = (abs((GetX1() - xAccumulator) ^ 2 + (GetY1() - yAccumulator) ^ 2)) ^ (1 / 2);
	}
	int Character::GetDistance() {
		return walkedDistance;
	}
	void Character::SetAccumulator(int x, int y, boolean resetSignal) {
		if (resetSignal) {
			walkedDistance = 0;
			xAccumulator = x;
			yAccumulator = y;
		}
	}

	void Character::InputKeyDown(UINT nChar) {

		const char KEY_LEFT = 0x41; // keyboard���b�Y 0x25
		const char KEY_UP = 0x57; // keyboard�W�b�Y 0x26
		const char KEY_RIGHT = 0x44; // keyboard�k�b�Y 0x27
		const char KEY_DOWN = 0x53; // keyboard�U�b�Y 0x28
		const char KEY_SPACE = 0x20; // keyboard SPACE
		const char KEY_CTRL = 0x11; //keyboard ctrl

		Diff = KeyBoardInputTime - LastInputTime;
		LastInputTime = KeyBoardInputTime;
		if (!UnMovable) {
			//here has a problem
			if (isRunning) {
				if (direction==0) {
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
			
			if (Diff <= 10) {
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
			}
			if (nChar == KEY_RIGHT) {
				SetMovingRight(true);
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
	}

	void Character::InputKeyUp(UINT nChar) {
		const char KEY_LEFT = 0x41; // keyboard���b�Y 0x25
		const char KEY_UP = 0x57; // keyboard�W�b�Y 0x26
		const char KEY_RIGHT = 0x44; // keyboard�k�b�Y 0x27
		const char KEY_DOWN = 0x53; // keyboard�U�b�Y 0x28
		const char KEY_SPACE = 0x20; // keyboard SPACE

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

		LastInput = nChar;
	}

	void Character::OnMove() {
		AnimationCount++;
		TRACE("Count %d\n", AnimationCount);
		TRACE("Count %d\n", AnimationState);
		
		SetMoving();
		if (isJumpping) {
			JumpCount++;
		}
		//calculate input time diff
		KeyBoardInputTime++;
	}

	void Character::SetMovingDown(bool flag) {
		isMovingDown = flag;
	}

	void Character::SetMovingUp(bool flag) {
		isMovingUp = flag;
	}

	void Character::SetMovingLeft(bool flag) {
		if (!isRunning) {
			if (flag == true) {
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
				isMovingLeft = false;
			}
			else {
				isMovingRight = flag;
			}
		}
	}

	void Character::SetRunning(bool flag) {
		if (flag==true) {
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
		if (!isJumpping) {
			isJumpping = flag;
			JumpYposTemp = yPos + 1;
			isRising = true;
			AnimationState = 4;
		}
	}

	void Character::SetDefense(bool flag) {
		isDefense = flag;
		if (flag == true) {
			//reset
			DefenseCount = 0;
		}
	}

	void Character::SetMoving() {
		if (isRunning) {
			if (isJumpping) {
				speed = 7;
			}
			else {
				speed = 4;
			}
		}
		else {
			speed = 2;
		}
		if (isMovingLeft) {
			this->SetXY(xPos - speed, yPos);
			DistaceAccumulator();
			isWalking = true;
			direction = 1;
		}
		if (isMovingRight) {
			this->SetXY(xPos + speed, yPos);
			DistaceAccumulator();
			isWalking = true;

			direction = 0;
		}
		if (isMovingUp) {
			if (!isJumpping) {
				this->SetXY(xPos, yPos - 1);
				isWalking = true;
			}
		}
		if (isMovingDown) {
			if (!isJumpping) {
				this->SetXY(xPos, yPos + 1);
				isWalking = true;
			}
		}

		if (!isMovingUp && !isMovingDown && !isMovingLeft && !isMovingRight) {
			isWalking = false;
			//Walk[direction].Reset();
			AnimationState = 0;
		}

		if (isWalking) {
			if (isMovingLeft && isMovingRight) {
				AnimationState = 0;
			}
			else {
				AnimationState = 1;
			}
		}
		else {
			AnimationState = 0;
		}

		if (isDefense) {
			if (!isRunning) {
				isWalking = isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
			}
			DefenseCount++;
			if (DefenseCount >= 50) {
				isDefense = false;
				UnMovable = false;
			}
			else {
				AnimationState = 7;
				UnMovable = true;
			}
		}
		if (isRunning) {
			AnimationState = 2;
			if (isDefense) {
				//Roll
				RollCount++;
				if (RollCount <= 10) {
					AnimationState = 9;
				}
				else if (RollCount <= 20) {
					AnimationState = 10;
				}
				else if (RollCount <= 30) {
					AnimationState = 5;
					if (RollCount == 30) {
						RollCount = 0;
						isDefense = false;
						UnMovable = false;
						isRunning = false;
						isWalking = isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
					}
				}
			}
		}
		else if (StopRun) {
			if (RunCount<=10) {
				RunCount++;
				AnimationState = 3;
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
					InitialVelocity = 15;
					YVelocity = InitialVelocity;
				}
			}
			if (JumpCount < 3) {
				AnimationState = 4;
			}
			if (JumpCount < 6) {
				AnimationState = 5;
			}
			if (JumpCount >= 6) {
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
							JumpCountTemp = JumpCount+1;
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

	void Character::SetMapBorder(int mapID) {
		xMapBorderMin = -50;
		xMapBorderMax = 750;
		switch (mapID) {
		case 0:
			yMapBorderMin = 300;
			yMapBorderMax = 500;
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
	}

	void Character::OnShow() {
		switch (AnimationState)
		{
		case 0:
			Animation.Normal[direction].OnMove();
			Animation.Normal[direction].SetTopLeft(xPos, yPos);
			Animation.Normal[direction].OnShow();
			break;
		case 1:
			Animation.Walk[direction].OnMove();
			Animation.Walk[direction].SetTopLeft(xPos, yPos);
			Animation.Walk[direction].OnShow();
			break;
		case 2:
			Animation.Run[direction].OnMove();
			Animation.Run[direction].SetTopLeft(xPos, yPos);
			Animation.Run[direction].OnShow();
			break;
		case 3:
			Animation.RunStop[direction].SetTopLeft(xPos, yPos);
			Animation.RunStop[direction].ShowBitmap();
			break;
		case 4:
			Animation.Jump[direction][0].SetTopLeft(xPos, yPos);
			Animation.Jump[direction][0].ShowBitmap();
			break;
		case 5:
			//land
			Animation.Jump[direction][1].SetTopLeft(xPos, yPos);
			Animation.Jump[direction][1].ShowBitmap();
			break;
		case 6:
			if (isRunning) {
				Animation.Jump[direction][3].SetTopLeft(xPos, yPos);
				Animation.Jump[direction][3].ShowBitmap();
				break;
			}
			else {
				Animation.Jump[direction][2].SetTopLeft(xPos, yPos);
				Animation.Jump[direction][2].ShowBitmap();
				break;
			}
		case 7:
			Animation.Defense[direction][0].SetTopLeft(xPos, yPos);
			Animation.Defense[direction][0].ShowBitmap();
			break;
		case 8:
			Animation.Defense[direction][1].SetTopLeft(xPos, yPos);
			Animation.Defense[direction][1].ShowBitmap();
			break;
		case 9:
			Animation.Roll[direction][0].SetTopLeft(xPos, yPos);
			Animation.Roll[direction][0].ShowBitmap();
			break;
		case 10:
			Animation.Roll[direction][1].SetTopLeft(xPos, yPos);
			Animation.Roll[direction][1].ShowBitmap();
			break;
		default:
			break;
		}
	}

	Character::~Character() {
		
	}

	int Freeze::HitEnemy(Character* enemy) {
		DelayCounter--;

		if (DelayCounter < 0) {
			DelayCounter = Delay;
			return HitRectangle(enemy->GetX1() + 20, enemy->GetY1() + 20, enemy->GetX2() - 20, enemy->GetY2() - 20);
		}
		else {
			return 0;
		}
	}

	int Freeze::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
		int x1 = xPos;
		int y1 = yPos;
		int x2 = x1 + Animation.Normal[0].Width();
		int y2 = y1 + Animation.Normal[0].Height();

		if (tx2 >= x1 && ty2 >= y1 && tx1 <= x2 && ty1 <= y2) {
			return 1;
		}
		else {
			return 0;
		}
	}

	void Freeze::SetCharacter(){
		Animation.LoadFreeze();
		name = "Firzen";
	}
	//void Firzen::
}

