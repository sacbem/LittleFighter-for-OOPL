#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include "time.h"
#include <cmath>
#include <time.h>
namespace game_framework {

	Character::Character() {
		Initialize();
	}

	Character::Character(Character const& other) : name(other.name) {
		Initialize();
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
		DelayCounter = 50;
		Delay = 30;

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

		HealthPoint = 1000;
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
	int Character::GetMovingTime(boolean isLeft){
		return isLeft ? leftTime : rightTime;
	}
	boolean Character::DistanceAccumulatorReset() {
		if (this->AnimationState  || walkedDistance < 3) {
			return false;
		}
		else {
			walkedDistance = 0;
			xAccumulator = xPos;
			yAccumulator = yPos;
			return true;
		}
	}

	void Character::isGettingDamage(int Damage) {
		HealthPoint -= Damage;
		InnerHealPoint -= Damage / 2;
		DamageAccumulator += Damage;
	}

	void Character::InputKeyDown(UINT nChar) {

		const char KEY_LEFT = 0x41; // keyboard���b�Y 0x25
		const char KEY_UP = 0x57; // keyboard�W�b�Y 0x26
		const char KEY_RIGHT = 0x44; // keyboard�k�b�Y 0x27
		const char KEY_DOWN = 0x53; // keyboard�U�b�Y 0x28
		const char KEY_SPACE = 0x20; // keyboard SPACE
		const char KEY_CTRL = 0x11; //keyboard ctrl
		const char KEY_ENTER = 0x0D; // keyboard ENTER


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
		}
	}

	void Character::InputKeyUp(UINT nChar) {
		const char KEY_LEFT = 0x41; // keyboard���b�Y 0x25
		const char KEY_UP = 0x57; // keyboard�W�b�Y 0x26
		const char KEY_RIGHT = 0x44; // keyboard�k�b�Y 0x27
		const char KEY_DOWN = 0x53; // keyboard�U�b�Y 0x28
		const char KEY_SPACE = 0x20; // keyboard SPACE
		const char KEY_ENTER = 0x0D; // keyboard ENTER

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

	void Character::OnMove() {
		AnimationCount++;
		if (!isAttacking) {
			AttackLong = 0;
		}
		else {
			AttackLong++;
		}
		//Heal
		if (AnimationCount % 150 == 0) {
			if (HealthPoint <= InnerHealPoint) {
				HealthPoint += 30;
				if (HealthPoint >= 1800) {
					HealthPoint = 1800;
				}
			}
		}
		if (AnimationCount % 30 == 0) {
			if (Mana <= InnerMana) {
				Mana += 10;
				if (Mana >= 1800) {
					Mana = 1800;
				}
			}
		}
		//Reset Damage
		if (AttackLong >= 50) {
			AttackAccumulator = 0;
		}
		if (DamageAccumulator >= 400) {
			DamageAccumulator = 0;
		}

		TRACE("d %d\n", direction);
		TRACE("E d %d\n", hitDirection);
		//some basic movement

		/*
		if (isGettingHit) {
		}
		*/
		SetMoving();
		if (isJumpping) {
			JumpCount++;
		}
		if (isDefense) {
			ShowDefense();
		}
		if (isAttacking) {
			ShowAttack();
		}
		if (isRunning && isDefense) {
			ShowRoll();
		}
		if (isGettingHit) {
			ShowKnock();

			if (direction == 0) {
				if (hitDirection == 0) {
					this->SetXY(xPos - 1, yPos);
				}
				else if (hitDirection == 1) {
					this->SetXY(xPos + 1, yPos);
				}
			}
			else if (direction == 1) {
				if (hitDirection == 0) {
					this->SetXY(xPos + 1, yPos);
				}
				else if (hitDirection == 1) {
					this->SetXY(xPos - 1, yPos);
				}
			}
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
				LeftCount = 0;
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
				RightCount = 0;
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
			if ((!isDefense && !isAttacking) || isRunning) {
				this->SetXY(xPos - speed, yPos);
				DistaceAccumulator();
				isWalking = true;
				direction = 1;
			}
			L_finish = clock();
			LeftCount = (L_finish - L_start) / 1000;
		}
		if (isMovingRight) {
			if ((!isDefense && !isAttacking) || isRunning) {
				this->SetXY(xPos + speed, yPos);
				DistaceAccumulator();
				isWalking = true;
				direction = 0;
			}
			R_finish = clock();
			RightCount = (R_finish - R_start) / 1000;
		}

		//TRACE("RightCount %d\n", RightCount);
		//TRACE("LeftCount %d\n", LeftCount);
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

		if (isRunning) {
			AnimationState = 2;
		}
		else if (StopRun) {
			if (RunCount <= 10) {
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
			//Attack
		case 11:
			Animation.NormalAttack1[direction][0].SetTopLeft(xPos, yPos);
			Animation.NormalAttack1[direction][0].ShowBitmap();
			break;
		case 12:
			Animation.NormalAttack1[direction][1].SetTopLeft(xPos, yPos);
			Animation.NormalAttack1[direction][1].ShowBitmap();
			break;
		case 13:
			Animation.NormalAttack2[direction][0].SetTopLeft(xPos, yPos);
			Animation.NormalAttack2[direction][0].ShowBitmap();
			break;
		case 14:
			Animation.NormalAttack2[direction][1].SetTopLeft(xPos, yPos);
			Animation.NormalAttack2[direction][1].ShowBitmap();
			break;
		case 15:
			Animation.NormalAttack3[direction][0].SetTopLeft(xPos, yPos);
			Animation.NormalAttack3[direction][0].ShowBitmap();
			break;
		case 16:
			Animation.NormalAttack3[direction][1].SetTopLeft(xPos, yPos);
			Animation.NormalAttack3[direction][1].ShowBitmap();
			break;
		case 17:
			Animation.NormalAttack3[direction][2].SetTopLeft(xPos, yPos);
			Animation.NormalAttack3[direction][2].ShowBitmap();
			break;
		case 18:
			Animation.HeavyAttack[direction][0].SetTopLeft(xPos, yPos);
			Animation.HeavyAttack[direction][0].ShowBitmap();
			break;
		case 19:
			Animation.HeavyAttack[direction][1].SetTopLeft(xPos, yPos);
			Animation.HeavyAttack[direction][1].ShowBitmap();
			break;
		case 20:
			Animation.HeavyAttack[direction][2].SetTopLeft(xPos, yPos);
			Animation.HeavyAttack[direction][2].ShowBitmap();
			break;
		case 21:
			Animation.HeavyAttack[direction][3].SetTopLeft(xPos, yPos);
			Animation.HeavyAttack[direction][3].ShowBitmap();
			break;
		case 22:
			Animation.HeavyAttack[direction][4].SetTopLeft(xPos, yPos);
			Animation.HeavyAttack[direction][4].ShowBitmap();
			break;
		case 23:
			Animation.JumpAttack[direction][0].SetTopLeft(xPos, yPos);
			Animation.JumpAttack[direction][0].ShowBitmap();
			break;
		case 24:
			Animation.JumpAttack[direction][1].SetTopLeft(xPos, yPos);
			Animation.JumpAttack[direction][1].ShowBitmap();
			break;
		case 25:
			Animation.JumpAttack[direction][2].SetTopLeft(xPos, yPos);
			Animation.JumpAttack[direction][2].ShowBitmap();
			break;
		case 26:
			Animation.JumpHeavyAttack[direction][0].SetTopLeft(xPos, yPos);
			Animation.JumpHeavyAttack[direction][0].ShowBitmap();
			break;
		case 27:
			Animation.JumpHeavyAttack[direction][1].SetTopLeft(xPos, yPos);
			Animation.JumpHeavyAttack[direction][1].ShowBitmap();
			break;
		case 28:
			Animation.JumpHeavyAttack[direction][2].SetTopLeft(xPos, yPos);
			Animation.JumpHeavyAttack[direction][2].ShowBitmap();
			break;
			//Since Knock is complicated, so begin at 100
		case 100:
			Animation.Knock[direction][0].SetTopLeft(xPos, yPos);
			Animation.Knock[direction][0].ShowBitmap();
			break;
		case 101:
			Animation.Knock[direction][1].SetTopLeft(xPos, yPos);
			Animation.Knock[direction][1].ShowBitmap();
			break;
		case 102:
			Animation.Knock[direction][2].SetTopLeft(xPos, yPos);
			Animation.Knock[direction][2].ShowBitmap();
			break;
		case 103:
			Animation.Knock2[direction][0].SetTopLeft(xPos, yPos);
			Animation.Knock2[direction][0].ShowBitmap();
			break;
		case 104:
			Animation.Knock2[direction][1].SetTopLeft(xPos, yPos);
			Animation.Knock2[direction][1].ShowBitmap();
			break;
		case 105:
			Animation.Knock2[direction][2].SetTopLeft(xPos, yPos);
			Animation.Knock2[direction][2].ShowBitmap();
			break;
		case 110:
			Animation.KnockFront[direction][0].SetTopLeft(xPos, yPos);
			Animation.KnockFront[direction][0].ShowBitmap();
			break;
		case 111:
			Animation.KnockFront[direction][1].SetTopLeft(xPos, yPos);
			Animation.KnockFront[direction][1].ShowBitmap();
			break;
		case 112:
			Animation.KnockFront[direction][2].SetTopLeft(xPos, yPos);
			Animation.KnockFront[direction][2].ShowBitmap();
			break;
		case 113:
			Animation.KnockFront[direction][3].SetTopLeft(xPos, yPos);
			Animation.KnockFront[direction][3].ShowBitmap();
			break;
		case 114:
			Animation.KnockFront[direction][4].SetTopLeft(xPos, yPos);
			Animation.KnockFront[direction][4].ShowBitmap();
			break;
		case 115:
			Animation.KnockFront[direction][5].SetTopLeft(xPos, yPos);
			Animation.KnockFront[direction][5].ShowBitmap();
			break;
		case 116:
			Animation.KnockFront[direction][6].SetTopLeft(xPos, yPos);
			Animation.KnockFront[direction][6].ShowBitmap();
			break;
		case 120:
			Animation.KnockBack[direction][0].SetTopLeft(xPos, yPos);
			Animation.KnockBack[direction][0].ShowBitmap();
			break;
		case 121:
			Animation.KnockBack[direction][1].SetTopLeft(xPos, yPos);
			Animation.KnockBack[direction][1].ShowBitmap();
			break;
		case 122:
			Animation.KnockBack[direction][2].SetTopLeft(xPos, yPos);
			Animation.KnockBack[direction][2].ShowBitmap();
			break;
		case 123:
			Animation.KnockBack[direction][3].SetTopLeft(xPos, yPos);
			Animation.KnockBack[direction][3].ShowBitmap();
			break;
		case 124:
			Animation.KnockBack[direction][4].SetTopLeft(xPos, yPos);
			Animation.KnockBack[direction][4].ShowBitmap();
			break;
		case 125:
			Animation.KnockBack[direction][5].SetTopLeft(xPos, yPos);
			Animation.KnockBack[direction][5].ShowBitmap();
			break;
		case 126:
			Animation.KnockBack[direction][6].SetTopLeft(xPos, yPos);
			Animation.KnockBack[direction][6].ShowBitmap();
			break;
		default:
			break;
		}
	}

	Character::~Character() {

	}

	int Freeze::HitEnemy(Character* enemy) {
		if (isAttackFrame()) {
			return HitRectangle(enemy->GetX1() + 30, enemy->GetY1() + 20, enemy->GetX2() - 30, enemy->GetY2() - 20);
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
			isHitting = true;
			AttackAccumulator += AttackPoint;
			return 1;
		}
		else {
			isHitting = false;
			//AttackAccumulator = 0;
			return 0;
		}
	}

	void Freeze::SetCharacter() {
		Animation.LoadFreeze();
		name = "Freeze";
	}

	void Freeze::ShowDefense() {
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

	void Freeze::ShowRoll() {
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

	void Freeze::SetAttack(bool flag) {
		if (flag == true) {
			if (!isAttacking) {
				isAttacking = true;
				if (isRunning && isJumpping) {
					LastAttackState = AttackState;
					AttackState = 6;
				}
				else if (isRunning) {
					LastAttackState = AttackState;
					AttackState = 4;
				}
				else if (isJumpping) {
					LastAttackState = AttackState;
					AttackState = 5;
				}
				else {
					if (!isHitting) {
						LastAttackState = AttackState;
						if (LastAttackState == 1) {
							AttackState = 2;
							LastAttackState = 0;
						}
						else {
							AttackState = 1;
						}
					}
					else {
						LastAttackState = AttackState;
						//TRACE("LastAttackState %d\n", LastAttackState);
						switch (LastAttackState)
						{
						case 1:
							AttackState = 2;
							break;
						case 2:
							AttackState = 11;
							break;
						case 11:
							AttackState = 12;
							break;
						case 12:
							AttackState = 3;
							break;
						case 3:
							AttackState = 1;
							break;
						default:
							AttackState = 1;
							break;
						}
						//TRACE("AttackState %d\n", AttackState);
					}
				}
			}
		}
		else if (flag == false) {
			isAttacking = false;
			AttackCount = 0;
			LastAttackState = AttackState;
		}
	}

	void Freeze::ShowAttack() {
		//TRACE("Attacl %d\n", AttackAccumulator);
		//TRACE("Count %d\n", AttackCount);
		//TRACE("Attack %d\n", AttackState);
		//TRACE("Last Attack %d\n", LastAttackState);
		//TRACE("Animation %d\n", AnimationState);
		//TRACE("Hit %d\n", isHitting);
		AttackCount++;
		switch (AttackState)
		{
		case 1:
			if (AttackCount <= 10) {
				AnimationState = 11;
			}
			else if (AttackCount <= 20) {
				AnimationState = 12;
				if (AttackCount >= 20) {
					SetAttack(false);
				}
			}
			break;
		case 2:
			if (AttackCount <= 10) {
				AnimationState = 13;
			}
			else if (AttackCount <= 20) {
				AnimationState = 14;
				if (AttackCount >= 20) {
					SetAttack(false);
				}
			}
			break;
		case 11:
			//copy 1
			if (AttackCount <= 10) {
				AnimationState = 11;
			}
			else if (AttackCount <= 20) {
				AnimationState = 12;
				if (AttackCount >= 20) {
					SetAttack(false);
				}
			}
			break;
		case 12:
			//copy 2
			if (AttackCount <= 10) {
				AnimationState = 13;
			}
			else if (AttackCount <= 20) {
				AnimationState = 14;
				if (AttackCount >= 20) {
					SetAttack(false);
				}
			}
			break;
		case 3:
			if (AttackCount <= 10) {
				AnimationState = 15;
			}
			else if (AttackCount <= 20) {
				AnimationState = 16;
			}
			else if (AttackCount <= 30) {
				AnimationState = 17;
				if (AttackCount >= 30) {
					SetAttack(false);
				}
			}
			break;
		case 4:
			//heavy attack
			if (AttackCount <= 5) {
				AnimationState = 18;
			}
			else if (AttackCount <= 10) {
				AnimationState = 19;
			}
			else if (AttackCount <= 15) {
				AnimationState = 20;
			}
			else if (AttackCount <= 20) {
				AnimationState = 21;
			}
			else if (AttackCount <= 25) {
				AnimationState = 22;
				if (AttackCount == 25) {
					SetAttack(false);
					UnMovable = false;
					isRunning = false;
					isWalking = isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
					AttackAccumulator = 0;
				}
			}
			break;
		case 5:
			//JumpAttack
			if (AttackCount <= 10) {
				AnimationState = 23;
			}
			else if (AttackCount <= 20) {
				AnimationState = 24;
			}
			else if (AttackCount <= 30) {
				AnimationState = 25;
				if (AttackCount == 30) {
					SetAttack(false);
				}
			}
			break;
		case 6:
			//JumpHeavyAttack
			if (AttackCount <= 10) {
				AnimationState = 26;
			}
			else if (AttackCount <= 20) {
				AnimationState = 27;
			}
			else if (AttackCount <= 30) {
				AnimationState = 28;
				if (AttackCount == 30) {
					SetAttack(false);
				}
			}
			break;
		}
	}

	bool Freeze::isAttackFrame() {
		switch (AnimationState)
		{
		case 12:
			return true;
			break;
		case 14:
			return true;
			break;
		case 17:
			return true;
			break;
		case 20:
			return true;
			break;
		case 21:
			return true;
			break;
		case 24:
			return true;
			break;
		case 27:
			return true;
			break;
		default:
			return false;
			break;
		}
	}

	bool Freeze::AttackReach() {
		if (AttackAccumulator >= 400) {
			return true;
		}
		else {
			return false;
		}
	}

	void Freeze::SetKnock(bool flag, int Dir, int AttState) {
		if (flag == true) {
			if (!isGettingHit) {
				isGettingHit = true;
				hitDirection = Dir;
				if (AttState == 1 || AttState == 11) {
					LastKnockState = KnockState;
					KnockState = 1;
				}
				else if (AttState == 2) {
					LastKnockState = KnockState;
					KnockState = 2;
				}
				else if (AttState == 12 || AttState==5) {
					LastKnockState = KnockState;
					KnockState = 3;
				}
				else if (AttState == 3 || AttState == 4 || AttState == 6) {
					LastKnockState = KnockState;
					if (direction == 0 && Dir == 0) {
						KnockState = 7;
					}
					else if (direction == 1 && Dir == 1) {
						KnockState = 8;
					}
					else if (direction == 0 && Dir == 1) {
						KnockState = 8;
					}
					else if (direction == 1 && Dir == 0) {
						KnockState = 7;
					}
					JumpYposTemp = yPos + 1;
					isRising = true;
				}
			}
		}
		else if (flag == false) {
			isGettingHit = false;
			KnockCount = 0;
			LastKnockState = KnockState;
		}
	}

	void Freeze::ShowKnock() {
		//TRACE("Hit %d\n", isGettingHit);
		//TRACE("Damage %d\n", DamageAccumulator);
		//TRACE("Attack %d\n", AttackAccumulator);
		KnockCount++;
		switch (KnockState)
		{
		case 1:
			if (KnockCount <= 10) {
				AnimationState = 100;
				if (KnockCount == 10) {
					isGettingHit = false;
					KnockCount = 0;
					LastKnockState = KnockState;
				}
			}
			break;
		case 2:
			if (KnockCount <= 10) {
				AnimationState = 101;
				if (KnockCount == 10) {
					isGettingHit = false;
					KnockCount = 0;
					LastKnockState = KnockState;
				}
			}
			break;
		case 3:
			if (KnockCount <= 10) {
				AnimationState = 102;
				if (KnockCount == 10) {
					isGettingHit = false;
					KnockCount = 0;
					LastKnockState = KnockState;
				}
			}
			break;
		case 4:
			if (KnockCount <= 10) {
				AnimationState = 103;
				if (KnockCount == 10) {
					isGettingHit = false;
					KnockCount = 0;
					LastKnockState = KnockState;
				}
			}
			break;
		case 5:
			if (KnockCount <= 10) {
				AnimationState = 104;
				if (KnockCount == 10) {
					isGettingHit = false;
					KnockCount = 0;
					LastKnockState = KnockState;
				}
			}
			break;
		case 6:
			if (KnockCount <= 10) {
				AnimationState = 105;
				if (KnockCount == 10) {
					isGettingHit = false;
					KnockCount = 0;
					LastKnockState = KnockState;
				}
			}
			break;
		case 7:
			if (KnockCount <= 10) {
				AnimationState = 110;
			}
			else if (KnockCount <= 20) {
				AnimationState = 111;
			}
			else if (KnockCount <= 30) {
				AnimationState = 112;
			}
			else if (KnockCount <= 40) {
				AnimationState = 113;
			}
			else if (KnockCount <= 100) {
				AnimationState = 114;
			}
			else if (KnockCount <= 105) {
				AnimationState = 115;
			}
			else if (KnockCount <= 110) {
				AnimationState = 116;
				if (KnockCount >= 110) {
					isGettingHit = false;
					KnockCount = 0;
					LastKnockState = KnockState;
					DamageAccumulator = 0;
				}
			}
			break;
		case 8:
			if (KnockCount <= 10) {
				AnimationState = 120;
			}
			else if (KnockCount <= 20) {
				AnimationState = 121;
			}
			else if (KnockCount <= 30) {
				AnimationState = 122;
			}
			else if (KnockCount <= 40) {
				AnimationState = 123;
			}
			else if (KnockCount <= 100) {
				AnimationState = 124;
			}
			else if (KnockCount <= 105) {
				AnimationState = 125;
			}
			else if (KnockCount <= 110) {
				AnimationState = 126;
				if (KnockCount == 110) {
					isGettingHit = false;
					KnockCount = 0;
					LastKnockState = KnockState;
					DamageAccumulator = 0;
				}
			}
			break;
		default:
			break;
		}
	}
}


