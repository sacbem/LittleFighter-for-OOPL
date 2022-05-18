#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include "time.h"
#include <cmath>
#include <algorithm>
#include <time.h>
namespace game_framework {
	Woody::Woody() {
		for (int i = 0; i < 5; i++) {
			skillsEffect_InFieldNumber.push_back(0);
		}
		//energyBlast.reserve(1);
	}

	int Woody::HitEnemy(Character* enemy) {
		if (isAttackFrame()) {
			return HitRectangle(enemy->GetX1() + 30, enemy->GetY1() + 20, enemy->GetX2() - 30, enemy->GetY2() - 20);
		}
		else {
			return 0;
		}
	}

	int Woody::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
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

	void Woody::SetCharacter() {
		Animation.LoadWoody();
		InitSpecialAttack();
		name = "Woody";
	}

	void Woody::ShowDefense() {
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

	void Woody::ShowRoll() {
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

	void Woody::SetAttack(bool flag) {
		if (flag == true) {
			if (!isAttacking) {
				isAttacking = true;
				if (skillSignal == 1) {
					AttackState = 3;
				}
				else if (isRunning && isJumpping) {
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

	void Woody::ShowAttack() {
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
				AnimationState = 30;
			}
			else if (AttackCount <= 20) {
				AnimationState = 31;
			}
			else if (AttackCount <= 30) {
				AnimationState = 32;
				if (AttackCount >= 30) {
					SetAttack(false);
				}
			}
			break;
		case 2:
			if (AttackCount <= 10) {
				AnimationState = 40;
			}
			else if (AttackCount <= 20) {
				AnimationState = 41;
			}
			else if (AttackCount <= 30) {
				AnimationState = 42;
				if (AttackCount >= 30) {
					SetAttack(false);
				}
			}
			break;
		case 11:
			//copy 1
			if (AttackCount <= 10) {
				AnimationState = 30;
			}
			else if (AttackCount <= 20) {
				AnimationState = 31;
			}
			else if (AttackCount <= 30) {
				AnimationState = 32;
				if (AttackCount >= 30) {
					SetAttack(false);
				}
			}
			break;
		case 12:
			//copy 2
			if (AttackCount <= 10) {
				AnimationState = 40;
			}
			else if (AttackCount <= 20) {
				AnimationState = 41;
			}
			else if (AttackCount <= 30) {
				AnimationState = 42;
				if (AttackCount >= 30) {
					SetAttack(false);
				}
			}
			break;
		case 3:
			if (AttackCount <= 10) {
				AnimationState = 50;
			}
			else if (AttackCount <= 20) {
				AnimationState = 51;
			}
			else if (AttackCount <= 30) {
				AnimationState = 52;
			}
			else if (AttackCount <= 40) {
				AnimationState = 53;
			}
			else if (AttackCount <= 50) {
				AnimationState = 54;
			}
			else if (AttackCount <= 60) {
				AnimationState = 55;
			}
			else if (AttackCount <= 70) {
				AnimationState = 56;
				if (AttackCount >= 70) {
					SetAttack(false);
				}
			}
			break;
		case 4:
			//heavy attack
			if (AttackCount <= 5) {
				AnimationState = 60;
			}
			else if (AttackCount <= 10) {
				AnimationState = 61;
			}
			else if (AttackCount <= 15) {
				AnimationState = 62;
			}
			else if (AttackCount <= 20) {
				AnimationState = 63;
			}
			else if (AttackCount <= 25) {
				AnimationState = 64;
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
				AnimationState = 70;
			}
			else if (AttackCount <= 20) {
				AnimationState = 71;
			}
			else if (AttackCount <= 30) {
				AnimationState = 72;
				if (AttackCount == 30) {
					SetAttack(false);
				}
			}
			break;
		case 6:
			//JumpHeavyAttack
			if (AttackCount <= 10) {
				AnimationState = 80;
			}
			else if (AttackCount <= 20) {
				AnimationState = 81;
			}
			else if (AttackCount <= 30) {
				AnimationState = 82;
				if (AttackCount == 30) {
					SetAttack(false);
				}
			}
			break;
		}
	}

	bool Woody::isAttackFrame() {
		switch (AnimationState) {
		case 32:
			return true;
			break;
		case 42:
			return true;
			break;
		case 53:
			return true;
			break;
		case 54:
			return true;
			break;
		case 62:
			return true;
			break;
		case 63:
			return true;
			break;
		case 81:
			return true;
			break;
		case 82:
			return true;
			break;
		case 242:
			return true;
			break;
		case 243:
			return true;
			break;
		case 244:
			return true;
			break;
		case 245:
			return true;
			break;
		case 246:
			return true;
			break;
		case 247:
			return true;
			break;
		case 248:
			return true;
			break;
		default:
			return false;
			break;
		}
	}

	bool Woody::AttackReach() {
		if (AttackAccumulator >= 400) {
			return true;
		}
		else {
			return false;
		}
	}

	void Woody::SetKnock(bool flag, int Dir, int AttState) {
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
				else if (AttState == 12 || AttState == 5) {
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

	void Woody::ShowKnock() {
		//TRACE("Hit %d\n", isGettingHit);
		//TRACE("Damage %d\n", DamageAccumulator);
		//TRACE("Attack %d\n", AttackAccumulator);
		KnockCount++;
		switch (KnockState) {
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
			if (KnockCount == 0) {
				//init velocity
				InitialVelocity = 2;
				YVelocity = InitialVelocity;
			}
			if (KnockCount <= 3) {
				AnimationState = 110;
				SetXY(xPos + KnockSpeed * 3, yPos);
			}
			else if (KnockCount <= 6) {
				AnimationState = 111;
				SetXY(xPos + KnockSpeed * 3, yPos);
			}
			else if (KnockCount <= 30) {
				AnimationState = 112;
				SetXY(xPos + KnockSpeed * 3, yPos);
			}
			else if (KnockCount <= 40) {
				AnimationState = 113;
				SetXY(xPos + KnockSpeed * 3, yPos);
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
			if (KnockCount == 0) {
				//init velocity
				InitialVelocity = 2;
				YVelocity = InitialVelocity;
			}
			else if (KnockCount <= 10) {
				AnimationState = 120;
				SetXY(xPos + KnockSpeed * 3, yPos);
			}
			else if (KnockCount <= 20) {
				AnimationState = 121;
				SetXY(xPos + KnockSpeed * 3, yPos);
			}
			else if (KnockCount <= 30) {
				AnimationState = 122;
				SetXY(xPos + KnockSpeed * 3, yPos);
			}
			else if (KnockCount <= 40) {
				SetXY(xPos + KnockSpeed * 3, yPos);
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

	void Woody::SetSkill(int createdTimes) {
		/*
		auto frozenWaves_Begin = frozenWaves.begin();
		auto frozenPunchs_Begin = frozenPunchs.begin();
		auto frozenStorms_Begin = frozenStorms.begin();
		//TRACE("Signal %d\n", this->GetSkillSignal());
		if (this->GetSkillSignal() == 0) {
			frozenWaves.insert(frozenWaves_Begin, new SkillEffect(0, createdTimes, direction, xPos, yPos));
			skillsEffect_InFieldNumber[0] = frozenWaves.size();
		}
		else if (this->GetSkillSignal() == 1) {
			frozenPunchs.insert(frozenPunchs_Begin, new SkillEffect(1, createdTimes, direction, xPos, yPos));
			skillsEffect_InFieldNumber[1] = frozenPunchs.size();
		}
		else if (this->GetSkillSignal() == 3) {
			frozenStorms.insert(frozenStorms_Begin, new SkillEffect(3, createdTimes, direction, xPos, yPos));
			skillsEffect_InFieldNumber[3] = frozenStorms.size();
		}
		*/
	}

	void Woody::EffectObjectAliveManager(int mainTime) {
		/*
		const int frozenWaves_AliveTime = 10000;
		const int frozenPunchs_AliveTime = 10000;
		const int frozenStorms_AliveTime = 4500;
		for (auto& i : frozenWaves) {
			if (mainTime - i->createdTime >= frozenWaves_AliveTime) {
				delete i;
				frozenWaves.pop_back();
			}
		}
		for (auto& i : frozenPunchs) {
			TRACE("Time m %d\n", mainTime);
			TRACE("Time c %d\n", i->createdTime);
			TRACE("Time %d\n", mainTime - i->createdTime);
			if (mainTime - i->createdTime >= frozenPunchs_AliveTime) {
				delete i;
				frozenPunchs.pop_back();
			}
		}
		for (auto& i : frozenStorms) {
			TRACE("Time m %d\n", mainTime);
			TRACE("Time c %d\n", i->createdTime);
			TRACE("Time %d\n", mainTime - i->createdTime);
			if (mainTime - i->createdTime >= frozenStorms_AliveTime) {
				delete i;
				frozenStorms.pop_back();
			}
		}
		*/
	}

	void Woody::InitSpecialAttack() {
		//FrozenStorms
		energyBlastAnimation[0][0].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_0.bmp", RGB(0, 0, 0));
		energyBlastAnimation[0][1].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_1.bmp", RGB(0, 0, 0));
		energyBlastAnimation[0][2].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_2.bmp", RGB(0, 0, 0));
		energyBlastAnimation[0][3].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_3.bmp", RGB(0, 0, 0));
		energyBlastAnimation[0][4].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_4.bmp", RGB(0, 0, 0));
		energyBlastAnimation[0][5].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_5.bmp", RGB(0, 0, 0));
		energyBlastAnimation[0][6].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_6.bmp", RGB(0, 0, 0));
		energyBlastAnimation[0][7].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_7.bmp", RGB(0, 0, 0));
		energyBlastAnimation[0][8].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_8.bmp", RGB(0, 0, 0));
		energyBlastAnimation[0][9].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_9.bmp", RGB(0, 0, 0));
		energyBlastAnimation[0][10].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_10.bmp", RGB(0, 0, 0));
		energyBlastAnimation[0][11].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_11.bmp", RGB(0, 0, 0));
		energyBlastAnimation[1][0].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_9.bmp", RGB(0, 0, 0));
		energyBlastAnimation[1][1].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_8.bmp", RGB(0, 0, 0));
		energyBlastAnimation[1][2].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_7.bmp", RGB(0, 0, 0));
		energyBlastAnimation[1][3].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_6.bmp", RGB(0, 0, 0));
		energyBlastAnimation[1][4].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_5.bmp", RGB(0, 0, 0));
		energyBlastAnimation[1][5].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_4.bmp", RGB(0, 0, 0));
		energyBlastAnimation[1][6].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_3.bmp", RGB(0, 0, 0));
		energyBlastAnimation[1][7].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_2.bmp", RGB(0, 0, 0));
		energyBlastAnimation[1][8].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_1.bmp", RGB(0, 0, 0));
		energyBlastAnimation[1][9].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_0.bmp", RGB(0, 0, 0));
		energyBlastAnimation[1][10].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_19.bmp", RGB(0, 0, 0));
		energyBlastAnimation[1][11].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_18.bmp", RGB(0, 0, 0));

		//FrozenPunch
		footKnifeAnimation[0][0].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_8.bmp", RGB(0, 0, 0));
		footKnifeAnimation[0][1].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_9.bmp", RGB(0, 0, 0));
		footKnifeAnimation[0][2].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_66.bmp", RGB(0, 0, 0));
		footKnifeAnimation[0][3].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_19.bmp", RGB(0, 0, 0));
		footKnifeAnimation[0][4].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_65.bmp", RGB(0, 0, 0));
		footKnifeAnimation[0][5].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_39.bmp", RGB(0, 0, 0));
		footKnifeAnimation[0][6].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_36.bmp", RGB(0, 0, 0));
		footKnifeAnimation[1][0].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_1.bmp", RGB(0, 0, 0));
		footKnifeAnimation[1][1].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_0.bmp", RGB(0, 0, 0));
		footKnifeAnimation[1][2].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_63.bmp", RGB(0, 0, 0));
		footKnifeAnimation[1][3].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_10.bmp", RGB(0, 0, 0));
		footKnifeAnimation[1][4].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_64.bmp", RGB(0, 0, 0));
		footKnifeAnimation[1][5].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_30.bmp", RGB(0, 0, 0));
		footKnifeAnimation[1][6].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_40.bmp", RGB(0, 0, 0));

		//Woody Ball Attack
		demonFootAnimation[0][0].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_20.bmp", RGB(0, 0, 0));
		demonFootAnimation[0][1].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_21.bmp", RGB(0, 0, 0));
		demonFootAnimation[0][2].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_22.bmp", RGB(0, 0, 0));
		demonFootAnimation[0][3].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_23.bmp", RGB(0, 0, 0));
		demonFootAnimation[0][4].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_24.bmp", RGB(0, 0, 0));
		demonFootAnimation[0][5].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_25.bmp", RGB(0, 0, 0));
		demonFootAnimation[0][6].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_26.bmp", RGB(0, 0, 0));
		demonFootAnimation[0][7].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_27.bmp", RGB(0, 0, 0));
		demonFootAnimation[0][8].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_28.bmp", RGB(0, 0, 0));
		demonFootAnimation[0][9].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_29.bmp", RGB(0, 0, 0));
		demonFootAnimation[0][10].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_30.bmp", RGB(0, 0, 0));
		demonFootAnimation[1][0].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_29.bmp", RGB(0, 0, 0));
		demonFootAnimation[1][1].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_28.bmp", RGB(0, 0, 0));
		demonFootAnimation[1][2].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_27.bmp", RGB(0, 0, 0));
		demonFootAnimation[1][3].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_26.bmp", RGB(0, 0, 0));
		demonFootAnimation[1][4].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_25.bmp", RGB(0, 0, 0));
		demonFootAnimation[1][5].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_24.bmp", RGB(0, 0, 0));
		demonFootAnimation[1][6].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_23.bmp", RGB(0, 0, 0));
		demonFootAnimation[1][7].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_22.bmp", RGB(0, 0, 0));
		demonFootAnimation[1][8].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_21.bmp", RGB(0, 0, 0));
		demonFootAnimation[1][9].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_20.bmp", RGB(0, 0, 0));
		demonFootAnimation[1][10].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_39.bmp", RGB(0, 0, 0));

		//Frozen Swords
		tankAnimation[0][0].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_12.bmp", RGB(0, 0, 0));
		tankAnimation[0][1].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_13.bmp", RGB(0, 0, 0));
		tankAnimation[0][2].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_14.bmp", RGB(0, 0, 0));
		tankAnimation[0][3].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_15.bmp", RGB(0, 0, 0));
		tankAnimation[0][4].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_16.bmp", RGB(0, 0, 0));
		tankAnimation[0][5].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_17.bmp", RGB(0, 0, 0));
		tankAnimation[0][6].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_18.bmp", RGB(0, 0, 0));
		tankAnimation[1][0].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_17.bmp", RGB(0, 0, 0));
		tankAnimation[1][1].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_16.bmp", RGB(0, 0, 0));
		tankAnimation[1][2].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_15.bmp", RGB(0, 0, 0));
		tankAnimation[1][3].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_14.bmp", RGB(0, 0, 0));
		tankAnimation[1][4].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_13.bmp", RGB(0, 0, 0));
		tankAnimation[1][5].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_12.bmp", RGB(0, 0, 0));
		tankAnimation[1][6].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_11.bmp", RGB(0, 0, 0));

		teleportationAnimation[0][0].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_31.bmp", RGB(0, 0, 0));
		teleportationAnimation[0][1].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_32.bmp", RGB(0, 0, 0));
		teleportationAnimation[0][2].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_33.bmp", RGB(0, 0, 0));
		teleportationAnimation[0][3].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_34.bmp", RGB(0, 0, 0));
		teleportationAnimation[0][4].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_35.bmp", RGB(0, 0, 0));
		teleportationAnimation[0][5].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_36.bmp", RGB(0, 0, 0));
		teleportationAnimation[0][6].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_37.bmp", RGB(0, 0, 0));
		teleportationAnimation[0][7].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_38.bmp", RGB(0, 0, 0));
		teleportationAnimation[0][8].LoadBitmap(".\\res\\Woody\\Woody_2\\woody_2_39.bmp", RGB(0, 0, 0));
		teleportationAnimation[1][0].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_38.bmp", RGB(0, 0, 0));
		teleportationAnimation[1][1].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_37.bmp", RGB(0, 0, 0));
		teleportationAnimation[1][2].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_36.bmp", RGB(0, 0, 0));
		teleportationAnimation[1][3].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_35.bmp", RGB(0, 0, 0));
		teleportationAnimation[1][4].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_34.bmp", RGB(0, 0, 0));
		teleportationAnimation[1][5].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_33.bmp", RGB(0, 0, 0));
		teleportationAnimation[1][6].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_32.bmp", RGB(0, 0, 0));
		teleportationAnimation[1][7].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_31.bmp", RGB(0, 0, 0));
		teleportationAnimation[1][8].LoadBitmap(".\\res\\Woody\\Woody_2_reverse\\woody_2_reverse_30.bmp", RGB(0, 0, 0));
	}

	void Woody::OnMove() {
		/*TRACE("UnMove %d\n", UnMovable);*/
		AnimationCount++;
		if (AnimationCount == 0) {
			UnMovable = false;
		}
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

		//TRACE("d %d\n", direction);
		//TRACE("E d %d\n", hitDirection);
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
			//if (KnockCount ==  || KnockCount == 110) {
			//}
		}
		if (skillSignal != -1) {
			CallSpecial();
		}

		//calculate input time diff
		KeyBoardInputTime++;
	}

	void Woody::OnShow(vector<pair<int, int>>theOthersPosition, int mainTime) {
		//TRACE("isAttacking %d\n", isAttacking);
		switch (AnimationState)
		{
		case 0:
			Animation.Normal[direction].OnMove();
			Animation.Normal[direction].SetTopLeft(xPos, yPos);
			Animation.Normal[direction].OnShow();

			//Fool-proof mechanism
			skillSignal = -1;
			UnMovable = false;
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
		case 11:
			Animation.Roll[direction][2].SetTopLeft(xPos, yPos);
			Animation.Roll[direction][2].ShowBitmap();
			break;
		case 12:
			Animation.Roll[direction][3].SetTopLeft(xPos, yPos);
			Animation.Roll[direction][3].ShowBitmap();
			break;
		case 13:
			Animation.Roll[direction][4].SetTopLeft(xPos, yPos);
			Animation.Roll[direction][4].ShowBitmap();
			break;
			//Attack
		case 30:
			Animation.NormalAttack1[direction][0].SetTopLeft(xPos, yPos);
			Animation.NormalAttack1[direction][0].ShowBitmap();
			break;
		case 31:
			Animation.NormalAttack1[direction][1].SetTopLeft(xPos, yPos);
			Animation.NormalAttack1[direction][1].ShowBitmap();
			break;
		case 32:
			Animation.NormalAttack1[direction][2].SetTopLeft(xPos, yPos);
			Animation.NormalAttack1[direction][2].ShowBitmap();
			break;
		case 40:
			Animation.NormalAttack2[direction][0].SetTopLeft(xPos, yPos);
			Animation.NormalAttack2[direction][0].ShowBitmap();
			break;
		case 41:
			Animation.NormalAttack2[direction][1].SetTopLeft(xPos, yPos);
			Animation.NormalAttack2[direction][1].ShowBitmap();
			break;
		case 42:
			Animation.NormalAttack2[direction][2].SetTopLeft(xPos, yPos);
			Animation.NormalAttack2[direction][2].ShowBitmap();
			break;
		case 50:
			Animation.NormalAttack3[direction][0].SetTopLeft(xPos, yPos);
			Animation.NormalAttack3[direction][0].ShowBitmap();
			break;
		case 51:
			Animation.NormalAttack3[direction][1].SetTopLeft(xPos, yPos);
			Animation.NormalAttack3[direction][1].ShowBitmap();
			break;
		case 52:
			Animation.NormalAttack3[direction][2].SetTopLeft(xPos, yPos);
			Animation.NormalAttack3[direction][2].ShowBitmap();
			break;
		case 53:
			Animation.NormalAttack3[direction][3].SetTopLeft(xPos, yPos);
			Animation.NormalAttack3[direction][3].ShowBitmap();
			break;
		case 54:
			Animation.NormalAttack3[direction][4].SetTopLeft(xPos, yPos);
			Animation.NormalAttack3[direction][4].ShowBitmap();
			break;
		case 55:
			Animation.NormalAttack3[direction][5].SetTopLeft(xPos, yPos);
			Animation.NormalAttack3[direction][5].ShowBitmap();
			break;
		case 56:
			Animation.NormalAttack3[direction][6].SetTopLeft(xPos, yPos);
			Animation.NormalAttack3[direction][6].ShowBitmap();
			break;
		case 60:
			Animation.HeavyAttack[direction][0].SetTopLeft(xPos, yPos);
			Animation.HeavyAttack[direction][0].ShowBitmap();
			break;
		case 61:
			Animation.HeavyAttack[direction][1].SetTopLeft(xPos, yPos);
			Animation.HeavyAttack[direction][1].ShowBitmap();
			break;
		case 62:
			Animation.HeavyAttack[direction][2].SetTopLeft(xPos, yPos);
			Animation.HeavyAttack[direction][2].ShowBitmap();
			break;
		case 63:
			Animation.HeavyAttack[direction][3].SetTopLeft(xPos, yPos);
			Animation.HeavyAttack[direction][3].ShowBitmap();
			break;
		case 64:
			Animation.HeavyAttack[direction][4].SetTopLeft(xPos, yPos);
			Animation.HeavyAttack[direction][4].ShowBitmap();
			break;
		case 70:
			Animation.JumpAttack[direction][0].SetTopLeft(xPos, yPos);
			Animation.JumpAttack[direction][0].ShowBitmap();
			break;
		case 71:
			Animation.JumpAttack[direction][1].SetTopLeft(xPos, yPos);
			Animation.JumpAttack[direction][1].ShowBitmap();
			break;
		case 72:
			Animation.JumpAttack[direction][2].SetTopLeft(xPos, yPos);
			Animation.JumpAttack[direction][2].ShowBitmap();
			break;
		case 73:
			Animation.JumpAttack[direction][3].SetTopLeft(xPos, yPos);
			Animation.JumpAttack[direction][3].ShowBitmap();
			break;
		case 74:
			Animation.JumpAttack[direction][4].SetTopLeft(xPos, yPos);
			Animation.JumpAttack[direction][4].ShowBitmap();
			break;
		case 80:
			Animation.JumpHeavyAttack[direction][0].SetTopLeft(xPos, yPos);
			Animation.JumpHeavyAttack[direction][0].ShowBitmap();
			break;
		case 81:
			Animation.JumpHeavyAttack[direction][1].SetTopLeft(xPos, yPos);
			Animation.JumpHeavyAttack[direction][1].ShowBitmap();
			break;
		case 82:
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
		case 190:
			energyBlastAnimation[direction][0].SetTopLeft(xPos, yPos);
			energyBlastAnimation[direction][0].ShowBitmap();
			break;
		case 191:
			energyBlastAnimation[direction][1].SetTopLeft(xPos, yPos);
			energyBlastAnimation[direction][1].ShowBitmap();
			break;
		case 192:
			energyBlastAnimation[direction][2].SetTopLeft(xPos, yPos);
			energyBlastAnimation[direction][2].ShowBitmap();
			break;
		case 193:
			energyBlastAnimation[direction][3].SetTopLeft(xPos, yPos);
			energyBlastAnimation[direction][3].ShowBitmap();
			break;
		case 194:
			energyBlastAnimation[direction][4].SetTopLeft(xPos, yPos);
			energyBlastAnimation[direction][4].ShowBitmap();
			break;
		case 195:
			energyBlastAnimation[direction][5].SetTopLeft(xPos, yPos);
			energyBlastAnimation[direction][5].ShowBitmap();
			break;
		case 196:
			energyBlastAnimation[direction][6].SetTopLeft(xPos, yPos);
			energyBlastAnimation[direction][6].ShowBitmap();
			break;
		case 197:
			energyBlastAnimation[direction][7].SetTopLeft(xPos, yPos);
			energyBlastAnimation[direction][7].ShowBitmap();
			break;
		case 198:
			energyBlastAnimation[direction][8].SetTopLeft(xPos, yPos);
			energyBlastAnimation[direction][8].ShowBitmap();
			break;
		case 199:
			energyBlastAnimation[direction][9].SetTopLeft(xPos, yPos);
			energyBlastAnimation[direction][9].ShowBitmap();
			break;
		case 200:
			energyBlastAnimation[direction][10].SetTopLeft(xPos, yPos);
			energyBlastAnimation[direction][10].ShowBitmap();
			break;
			//Frozen Punch
		case 210:
			footKnifeAnimation[direction][0].SetTopLeft(xPos, yPos);
			footKnifeAnimation[direction][0].ShowBitmap();
			break;
		case 211:
			footKnifeAnimation[direction][1].SetTopLeft(xPos, yPos);
			footKnifeAnimation[direction][1].ShowBitmap();
			break;
		case 212:
			footKnifeAnimation[direction][2].SetTopLeft(xPos, yPos);
			footKnifeAnimation[direction][2].ShowBitmap();
			break;
		case 213:
			footKnifeAnimation[direction][3].SetTopLeft(xPos, yPos);
			footKnifeAnimation[direction][3].ShowBitmap();
			break;
		case 214:
			footKnifeAnimation[direction][4].SetTopLeft(xPos, yPos);
			footKnifeAnimation[direction][4].ShowBitmap();
			break;
		case 215:
			footKnifeAnimation[direction][5].SetTopLeft(xPos, yPos);
			footKnifeAnimation[direction][5].ShowBitmap();
			break;
		case 216:
			footKnifeAnimation[direction][6].SetTopLeft(xPos, yPos);
			footKnifeAnimation[direction][6].ShowBitmap();
			break;
			//frozenStorms
		case 240:
			demonFootAnimation[direction][0].SetTopLeft(xPos, yPos);
			demonFootAnimation[direction][0].ShowBitmap();
			break;
		case 241:
			demonFootAnimation[direction][1].SetTopLeft(xPos, yPos);
			demonFootAnimation[direction][1].ShowBitmap();
			break;
		case 242:
			demonFootAnimation[direction][2].SetTopLeft(xPos, yPos);
			demonFootAnimation[direction][2].ShowBitmap();
			break;
		case 243:
			demonFootAnimation[direction][3].SetTopLeft(xPos, yPos);
			demonFootAnimation[direction][3].ShowBitmap();
			break;
		case 244:
			demonFootAnimation[direction][4].SetTopLeft(xPos, yPos);
			demonFootAnimation[direction][4].ShowBitmap();
			break;
		case 245:
			demonFootAnimation[direction][5].SetTopLeft(xPos, yPos);
			demonFootAnimation[direction][5].ShowBitmap();
			break;
		case 246:
			demonFootAnimation[direction][6].SetTopLeft(xPos, yPos);
			demonFootAnimation[direction][6].ShowBitmap();
			break;
		case 247:
			demonFootAnimation[direction][7].SetTopLeft(xPos, yPos);
			demonFootAnimation[direction][7].ShowBitmap();
			break;
		case 248:
			demonFootAnimation[direction][8].SetTopLeft(xPos, yPos);
			demonFootAnimation[direction][8].ShowBitmap();
			break;
		case 249:
			demonFootAnimation[direction][9].SetTopLeft(xPos, yPos);
			demonFootAnimation[direction][9].ShowBitmap();
			break;
		case 250:
			demonFootAnimation[direction][10].SetTopLeft(xPos, yPos);
			demonFootAnimation[direction][10].ShowBitmap();
			break;
		case 230:
			tankAnimation[direction][0].SetTopLeft(xPos, yPos);
			tankAnimation[direction][0].ShowBitmap();
			break;
		case 231:
			tankAnimation[direction][1].SetTopLeft(xPos, yPos);
			tankAnimation[direction][1].ShowBitmap();
			break;
		case 232:
			tankAnimation[direction][2].SetTopLeft(xPos, yPos);
			tankAnimation[direction][2].ShowBitmap();
			break;
		case 233:
			tankAnimation[direction][3].SetTopLeft(xPos, yPos);
			tankAnimation[direction][3].ShowBitmap();
			break;
		case 234:
			tankAnimation[direction][4].SetTopLeft(xPos, yPos);
			tankAnimation[direction][4].ShowBitmap();
			break;
		case 235:
			tankAnimation[direction][5].SetTopLeft(xPos, yPos);
			tankAnimation[direction][5].ShowBitmap();
			break;
		case 236:
			tankAnimation[direction][6].SetTopLeft(xPos, yPos);
			tankAnimation[direction][6].ShowBitmap();
			break;
		case 260:
			teleportationAnimation[direction][0].SetTopLeft(xPos, yPos);
			teleportationAnimation[direction][0].ShowBitmap();
			break;
		case 261:
			teleportationAnimation[direction][1].SetTopLeft(xPos, yPos);
			teleportationAnimation[direction][1].ShowBitmap();
			break;
		case 262:
			teleportationAnimation[direction][2].SetTopLeft(xPos, yPos);
			teleportationAnimation[direction][2].ShowBitmap();
			break;
		case 263:
			teleportationAnimation[direction][3].SetTopLeft(xPos, yPos);
			teleportationAnimation[direction][3].ShowBitmap();
			break;
		case 264:
			teleportationAnimation[direction][4].SetTopLeft(xPos, yPos);
			teleportationAnimation[direction][4].ShowBitmap();
			break;
		case 265:
			teleportationAnimation[direction][5].SetTopLeft(xPos, yPos);
			teleportationAnimation[direction][5].ShowBitmap();
			break;
		case 266:
			teleportationAnimation[direction][6].SetTopLeft(xPos, yPos);
			teleportationAnimation[direction][6].ShowBitmap();
			break;
		case 267:
			teleportationAnimation[direction][7].SetTopLeft(xPos, yPos);
			teleportationAnimation[direction][7].ShowBitmap();
			break;
		case 268:
			teleportationAnimation[direction][8].SetTopLeft(xPos, yPos);
			teleportationAnimation[direction][8].ShowBitmap();
			break;
		default:
			break;
		}
		//Special Attack Animation
		EffectObjectAliveManager(mainTime);
		ShowSpecialAttack();
	}

	void Woody::CallEnergyBlast() {
		//frozenWaves[0]->SetEffectObj(direction, SpCount%10, xPos+50);

		//TRACE("SpCount %d\n", SpCount);
		SpCount++;
		if (SpCount <= 4) {
			AnimationState = 190;
		}
		else if (SpCount <= 8) {
			AnimationState = 191;
		}
		else if (SpCount <= 12) {
			AnimationState = 192;
		}
		else if (SpCount <= 16) {
			AnimationState = 193;
		}
		else if (SpCount <= 20) {
			AnimationState = 194;
		}
		else if (SpCount <= 24) {
			AnimationState = 195;
		}
		else if (SpCount <= 28) {
			AnimationState = 196;
		}
		else if (SpCount <= 32) {
			AnimationState = 197;
		}
		else if (SpCount <= 36) {
			AnimationState = 198;
		}
		else if (SpCount <= 40) {
			AnimationState = 199;
		}
		else if (SpCount <= 44) {
			AnimationState = 200;
			if (SpCount >= 44) {
				SpCount = 0;
				//Clear State
				skillSignal = -1;
			}
		}
	}

	void Woody::CallFootKnife() {
		SetAttack(true);
	}

	void Woody::CallDemonFoot() {
		//TRACE("SP %d\n", SpCount);
		SetAttack(true);
		SpCount++;
		if (SpCount <= 10) {
			AnimationState = 240;
		}
		else if (SpCount <= 20) {
			AnimationState = 241;
		}
		else if (SpCount <= 30) {
			AnimationState = 242;
		}
		else if (SpCount <= 40) {
			AnimationState = 243;
		}
		else if (SpCount <= 50) {
			AnimationState = 244;
		}
		else if (SpCount <= 60) {
			AnimationState = 245;
		}
		else if (SpCount <= 70) {
			AnimationState = 246;
		}
		else if (SpCount <= 80) {
			AnimationState = 247;
		}
		else if (SpCount <= 90) {
			AnimationState = 248;
		}
		else if (SpCount <= 100) {
			AnimationState = 249;
		}
		else if (SpCount <= 44) {
			AnimationState = 250;
		}
		else if (SpCount > 44) {
			SetAttack(false);
			SpCount = 0;
			skillSignal = -1;
		}
		if (direction == 0) {
			this->SetXY(xPos+1,yPos);
		}
		else if (direction == 1) {
			this->SetXY(xPos - 1, yPos);
		}
	}

	void Woody::CallTank() {
		SpCount++;
		if (SpCount <= 4) {
			AnimationState = 230;
		}
		else if (SpCount <= 8) {
			AnimationState = 231;
		}
		else if (SpCount <= 12) {
			AnimationState = 232;
		}
		else if (SpCount <= 16) {
			AnimationState = 233;
		}
		else if (SpCount <= 20) {
			AnimationState = 234;
		}
		else if (SpCount <= 24) {
			AnimationState = 235;
			if (SpCount >= 24) {
				SpCount = 0;
				skillSignal = -1;
			}
		}
		if (direction == 0) {
			this->SetXY(xPos + 5, yPos);
		}
		else if (direction == 1) {
			this->SetXY(xPos - 5, yPos);
		}
	}
	
	void Woody::CallTeleportation() {
		SpCount++;
		if (SpCount <= 10) {
			AnimationState = 260;
		}
		else if (SpCount <= 20) {
			AnimationState = 261;
		}
		else if (SpCount <= 30) {
			AnimationState = 262;
		}
		else if (SpCount <= 40) {
			AnimationState = 263;
		}
		else if (SpCount <= 50) {
			AnimationState = 264;
		}
		else if (SpCount <= 60) {
			AnimationState = 265;
			if (SpCount == 60) {
				if (direction == 0) {
					this->SetXY(xPos + 400, yPos);
				}
				else if (direction == 1) {
					this->SetXY(xPos - 400, yPos);
				}
			}
		}
		else if (SpCount <= 70) {
			AnimationState = 266;
		}
		else if (SpCount <= 80) {
			AnimationState = 267;
		}
		else if (SpCount <= 90) {
			AnimationState = 268;
			if (SpCount >= 90) {
				SpCount = 0;
				skillSignal = -1;
			}
		}
	}

	void Woody::CallSpecial() {
		switch (skillSignal)
		{
		case -1:
			break;
		case 0:
			return CallEnergyBlast();
			break;
		case 1:
			return CallFootKnife();
			break;
		case 2:
			return CallDemonFoot();
			break;
		case 3:
			return CallTank();
			break;
		case 4:
			return CallTeleportation();
			break;
		default:
			break;
		}
	}

	void Woody::ShowSpecialAttack() {
		/*
		vector<SkillEffect*>  frozenWavesSorted, frozenPunchsSorted, frozenSwordsSorted, frozenStormsSorted;
		frozenWavesSorted = frozenWaves;
		frozenPunchsSorted = frozenPunchs;
		frozenStormsSorted = frozenStorms;

		std::sort(frozenWavesSorted.begin(), frozenWavesSorted.end(), mycompare);
		std::sort(frozenPunchsSorted.begin(), frozenPunchsSorted.end(), mycompare);
		std::sort(frozenStormsSorted.begin(), frozenStormsSorted.end(), mycompare);
		/*
		for (int i = frozenWavesSorted.size()-1; i >= 0; i--) {
			frozenWavesSorted[i]->OnShow();
		}
		for (int i = frozenPunchsSorted.size()-1; i >= 0; i--) {
			TRACE("Y %d\n", frozenPunchs[i]->yPos);
			frozenPunchsSorted[i]->OnShow();
		}
		for (int i = frozenStormsSorted.size()-1; i >= 0; i--) {
			frozenStormsSorted[i]->OnShow();
		}
		for (auto& i : frozenWavesSorted) {
			i->OnShow();
		}
		for (auto& i : frozenPunchsSorted) {
			i->OnShow();
		}
		for (auto& i : frozenStormsSorted) {
			i->OnShow();
		}
		*/
	}
}