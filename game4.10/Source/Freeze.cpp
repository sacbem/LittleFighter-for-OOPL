#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include <algorithm>
#include <time.h>
#include <cstdlib>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"

namespace game_framework {
	Freeze::Freeze(int num, int mapID) {
		CharacterID = 2;
		serialNumber = num;
		SetMapBorder(mapID);
		for (int i = 0; i < 5; i++) {
			skillsEffect_InFieldNumber.push_back(0);
		}
		frozenWaves.reserve(1);
		frozenPunchs.reserve(1);
		frozenSwords.reserve(1);
		frozenStorms.reserve(1);
		hittedLog.resize(4);
		SetCalculateDamageRequest(false);
	}

	int Freeze::HitEnemy(Character* enemy) {
		if (isAttackFrame()) {
			int yRange1 = yPos - 20;
			int yRange2 = yPos + 20;
			if(yRange1<=enemy->GetY1() && enemy->GetY1() <= yRange2) {
				return HitRectangle(enemy->GetX1() + 30, enemy->GetY1() + 20, enemy->GetX2() - 30, enemy->GetY2() - 20);
			}
			else {
				return 0;
			}
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
			return 0;
		}
	}

	void Freeze::SetCharacter() {
		Animation.LoadFreeze();
		InitSpecialAttack();
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
			if (isCarryItem == true) {
				SetPickup(false, itemId, itemType);
			}
			if (!isAttacking) {
				isAttacking = true;
				if (isNearItem) {
					LastAttackState = AttackState;
					AttackState = 9;
				}
				else if (isRunning && isJumpping) {
					LastAttackState = AttackState;
					AttackState = 6;
				}
				else if (isRunning) {
					LastAttackState = AttackState;
					if (isCarryItem) {
						LastAttackState = AttackState;
						AttackState = 8;
					}
					else {
						AttackState = 4;
					}
				}
				else if (isJumpping) {
					LastAttackState = AttackState;
					AttackState = 5;
				}
				else if (isCarryItem) {
					LastAttackState = AttackState;
					AttackState = 7;
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
						TRACE("LastAttackState %d\n", LastAttackState);
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
		case 7:
			//Throw
			if (AttackCount <= 10) {
				AnimationState = 1020;
			}
			else if (AttackCount <= 20) {
				AnimationState = 1021;
				if (AttackCount == 20) {
					SetAttack(false);
				}
			}
			break;
		case 8:
			//Run Throw
			if (AttackCount <= 10) {
				AnimationState = 1030;
			}
			else if (AttackCount <= 20) {
				AnimationState = 1031;
				if (AttackCount == 20) {
					SetAttack(false);
					UnMovable = false;
					isRunning = false;
					isWalking = isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
					AttackAccumulator = 0;
				}
			}
			break;
		case 9:
			//Grab
			if (AttackCount <= 10) {
				AnimationState = 400;
				if (AttackCount == 10) {
					SetAttack(false);
				}
			}
			break;
		}
	}

	bool Freeze::isAttackFrame() {
		switch (AnimationState) {
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
				//Break Ice
				specialState = 0;
				FrozenCount = 400;
				UnMovable = false;

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
						KnockState = 8;
					}
					else if (direction == 1 && Dir == 1) {
						KnockState = 7;
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

	void Freeze::SetSkill(int createdTimes) {
		auto frozenWaves_Begin = frozenWaves.begin();
		auto frozenPunchs_Begin = frozenPunchs.begin();
		auto frozenStorms_Begin = frozenStorms.begin();
		
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
	}

	void Freeze::EffectObjectAliveManager(int mainTime) {
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
			if (mainTime - i->createdTime >= frozenPunchs_AliveTime) {
				delete i;
				frozenPunchs.pop_back();
			}
		}
		for (auto& i : frozenStorms) {
			if (mainTime - i->createdTime >= frozenStorms_AliveTime) {
				delete i;
				frozenStorms.pop_back();
			}
		}
	}

	void Freeze::ClearSkill() {
		for (auto& i : frozenWaves) {
			delete i;
			frozenWaves.pop_back();
		}
		for (auto& i : frozenPunchs) {
			delete i;
			frozenPunchs.pop_back();
		}
		for (auto& i : frozenStorms) {
			delete i;
			frozenStorms.pop_back();
		}
	}

	void Freeze::InitSpecialAttack() {
		//Freeze Ball Attack
		frozenWavesAnimation[0][0].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_0.bmp", RGB(0, 0, 0));
		frozenWavesAnimation[0][1].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_1.bmp", RGB(0, 0, 0));
		frozenWavesAnimation[0][2].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_2.bmp", RGB(0, 0, 0));
		frozenWavesAnimation[0][3].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_3.bmp", RGB(0, 0, 0));
		frozenWavesAnimation[0][4].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_4.bmp", RGB(0, 0, 0));
		frozenWavesAnimation[0][5].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_5.bmp", RGB(0, 0, 0));
		frozenWavesAnimation[1][0].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_9.bmp", RGB(0, 0, 0));
		frozenWavesAnimation[1][1].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_8.bmp", RGB(0, 0, 0));
		frozenWavesAnimation[1][2].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_7.bmp", RGB(0, 0, 0));
		frozenWavesAnimation[1][3].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_6.bmp", RGB(0, 0, 0));
		frozenWavesAnimation[1][4].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_5.bmp", RGB(0, 0, 0));
		frozenWavesAnimation[1][5].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_4.bmp", RGB(0, 0, 0));

		//FrozenPunch
		frozenPunchsAnimation[0][0].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_8.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[0][1].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_9.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[0][2].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_17.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[0][3].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_18.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[0][4].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_19.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[0][5].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_45.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[0][6].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_46.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[0][7].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_49.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[1][0].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_1.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[1][1].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_0.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[1][2].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_12.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[1][3].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_11.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[1][4].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_10.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[1][5].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_44.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[1][6].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_43.bmp", RGB(0, 0, 0));
		frozenPunchsAnimation[1][7].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_40.bmp", RGB(0, 0, 0));

		//FrozenStorms
		frozenStormsAnimation[0][0].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_10.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[0][1].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_11.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[0][2].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_12.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[0][3].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_13.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[0][4].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_14.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[0][5].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_15.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[0][6].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_16.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[0][7].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_17.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[0][8].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_18.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[1][0].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_19.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[1][1].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_18.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[1][2].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_17.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[1][3].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_16.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[1][4].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_15.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[1][5].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_14.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[1][6].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_13.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[1][7].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_12.bmp", RGB(0, 0, 0));
		frozenStormsAnimation[1][8].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_11.bmp", RGB(0, 0, 0));

		//Frozen Swords
		frozenSwordsAnimation[0][0].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_20.bmp", RGB(0, 0, 0));
		frozenSwordsAnimation[0][1].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_21.bmp", RGB(0, 0, 0));
		frozenSwordsAnimation[0][2].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_22.bmp", RGB(0, 0, 0));
		frozenSwordsAnimation[0][3].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_23.bmp", RGB(0, 0, 0));
		frozenSwordsAnimation[0][4].LoadBitmap(".\\res\\Freeze\\Freeze_2\\freeze_2_24.bmp", RGB(0, 0, 0));
		frozenSwordsAnimation[1][0].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_29.bmp", RGB(0, 0, 0));
		frozenSwordsAnimation[1][1].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_28.bmp", RGB(0, 0, 0));
		frozenSwordsAnimation[1][2].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_27.bmp", RGB(0, 0, 0));
		frozenSwordsAnimation[1][3].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_26.bmp", RGB(0, 0, 0));
		frozenSwordsAnimation[1][4].LoadBitmap(".\\res\\Freeze\\Freeze_2_reverse\\freeze_2_reverse_25.bmp", RGB(0, 0, 0));

	}

	void Freeze::OnMove() {
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
		if (isAlive) {
			if (AnimationCount % 150 == 0) {
				if (HealthPoint <= InnerHealPoint && InnerHealPoint > 0) {
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
		}
		//Reset Damage
		if (AttackLong >= 50) {
			AttackAccumulator = 0;
		}
		if (DamageAccumulator >= 400) {
			DamageAccumulator = 0;
		}
		//some basic movement

		SetMoving();
	
		//Frozen
		if (specialState == 1) {
			TRACE("Freeze\n");
			ShowFrozen();
		}
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
					KnockSpeed = 1;
				}
				else if (hitDirection == 1) {
					KnockSpeed = -1;
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
		}
		if (skillSignal != -1) {
			CallSpecial();
		}

		//calculate input time diff
		KeyBoardInputTime++;
	}

	bool mycompare(SkillEffect* s1, SkillEffect* s2) {
		return s1->yPos < s2->yPos;
	}

	void Freeze::ShowFrozenPunch() {
		vector<SkillEffect*>  frozenPunchsSorted;
		frozenPunchsSorted = frozenPunchs;
		std::sort(frozenPunchsSorted.begin(), frozenPunchsSorted.end(), mycompare);
		for (auto& i : frozenPunchsSorted) {
			i->OnShow();
		}
	}

	void Freeze::OnShow(vector<pair<int, int>>theOthersPosition, int mainTime) {
		switch (AnimationState)
		{
		case 0:
			if (isCarryItem && itemType == 1) {
				Animation.itemNormal[direction].SetTopLeft(xPos, yPos);
				Animation.itemNormal[direction].ShowBitmap();
			}
			else{
				Animation.Normal[direction].OnMove();
				Animation.Normal[direction].SetTopLeft(xPos, yPos);
				Animation.Normal[direction].OnShow();
			}

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
		case 200:
			frozenWavesAnimation[direction][0].SetTopLeft(xPos, yPos);
			frozenWavesAnimation[direction][0].ShowBitmap();
			break;
		case 201:
			frozenWavesAnimation[direction][1].SetTopLeft(xPos, yPos);
			frozenWavesAnimation[direction][1].ShowBitmap();
			break;
		case 202:
			frozenWavesAnimation[direction][2].SetTopLeft(xPos, yPos);
			frozenWavesAnimation[direction][2].ShowBitmap();
			break;
		case 203:
			frozenWavesAnimation[direction][3].SetTopLeft(xPos, yPos);
			frozenWavesAnimation[direction][3].ShowBitmap();
			break;
		case 204:
			frozenWavesAnimation[direction][4].SetTopLeft(xPos, yPos);
			frozenWavesAnimation[direction][4].ShowBitmap();
			break;
		case 205:
			frozenWavesAnimation[direction][5].SetTopLeft(xPos, yPos);
			frozenWavesAnimation[direction][5].ShowBitmap();
			break;
			//Frozen Punch
		case 210:
			frozenPunchsAnimation[direction][0].SetTopLeft(xPos, yPos);
			frozenPunchsAnimation[direction][0].ShowBitmap();
			break;
		case 211:
			frozenPunchsAnimation[direction][1].SetTopLeft(xPos, yPos);
			frozenPunchsAnimation[direction][1].ShowBitmap();
			break;
		case 212:
			frozenPunchsAnimation[direction][2].SetTopLeft(xPos, yPos);
			frozenPunchsAnimation[direction][2].ShowBitmap();
			break;
		case 213:
			frozenPunchsAnimation[direction][3].SetTopLeft(xPos, yPos);
			frozenPunchsAnimation[direction][3].ShowBitmap();
			break;
		case 214:
			frozenPunchsAnimation[direction][4].SetTopLeft(xPos, yPos);
			frozenPunchsAnimation[direction][4].ShowBitmap();
			break;
		case 215:
			frozenPunchsAnimation[direction][5].SetTopLeft(xPos, yPos);
			frozenPunchsAnimation[direction][5].ShowBitmap();
			break;
		case 216:
			frozenPunchsAnimation[direction][6].SetTopLeft(xPos, yPos);
			frozenPunchsAnimation[direction][6].ShowBitmap();
			break;
		case 217:
			frozenPunchsAnimation[direction][7].SetTopLeft(xPos, yPos);
			frozenPunchsAnimation[direction][7].ShowBitmap();
			break;
			//frozenStorms
		case 220:
			frozenStormsAnimation[direction][0].SetTopLeft(xPos, yPos);
			frozenStormsAnimation[direction][0].ShowBitmap();
			break;
		case 221:
			frozenStormsAnimation[direction][1].SetTopLeft(xPos, yPos);
			frozenStormsAnimation[direction][1].ShowBitmap();
			break;
		case 222:
			frozenStormsAnimation[direction][2].SetTopLeft(xPos, yPos);
			frozenStormsAnimation[direction][2].ShowBitmap();
			break;
		case 223:
			frozenStormsAnimation[direction][3].SetTopLeft(xPos, yPos);
			frozenStormsAnimation[direction][3].ShowBitmap();
			break;
		case 224:
			frozenStormsAnimation[direction][4].SetTopLeft(xPos, yPos);
			frozenStormsAnimation[direction][4].ShowBitmap();
			break;
		case 225:
			frozenStormsAnimation[direction][5].SetTopLeft(xPos, yPos);
			frozenStormsAnimation[direction][5].ShowBitmap();
			break;
		case 226:
			frozenStormsAnimation[direction][6].SetTopLeft(xPos, yPos);
			frozenStormsAnimation[direction][6].ShowBitmap();
			break;
		case 227:
			frozenStormsAnimation[direction][7].SetTopLeft(xPos, yPos);
			frozenStormsAnimation[direction][7].ShowBitmap();
			break;
		case 228:
			frozenStormsAnimation[direction][8].SetTopLeft(xPos, yPos);
			frozenStormsAnimation[direction][8].ShowBitmap();
			break;
		case 230:
			frozenSwordsAnimation[direction][0].SetTopLeft(xPos, yPos);
			frozenSwordsAnimation[direction][0].ShowBitmap();
			break;
		case 231:
			frozenSwordsAnimation[direction][1].SetTopLeft(xPos, yPos);
			frozenSwordsAnimation[direction][1].ShowBitmap();
			break;
		case 232:
			frozenSwordsAnimation[direction][2].SetTopLeft(xPos, yPos);
			frozenSwordsAnimation[direction][2].ShowBitmap();
			break;
		case 233:
			frozenSwordsAnimation[direction][3].SetTopLeft(xPos, yPos);
			frozenSwordsAnimation[direction][3].ShowBitmap();
			break;
		case 234:
			frozenSwordsAnimation[direction][4].SetTopLeft(xPos, yPos);
			frozenSwordsAnimation[direction][4].ShowBitmap();
			break;
		case 400:
			Animation.Grab[direction].SetTopLeft(xPos, yPos);
			Animation.Grab[direction].ShowBitmap();
			break;
		//Frozen state
		case 300:
			Animation.Frozen[direction][0].SetTopLeft(xPos, yPos);
			Animation.Frozen[direction][0].ShowBitmap();
			break;
		case 301:
			Animation.Frozen[direction][1].SetTopLeft(xPos, yPos);
			Animation.Frozen[direction][1].ShowBitmap();
			break;
		//Carrying item
		case 1000:
			Animation.itemNormal[direction].SetTopLeft(xPos, yPos);
			Animation.itemNormal[direction].ShowBitmap();
			break;
		case 1001:
			Animation.itemWalk[direction].OnMove();
			Animation.itemWalk[direction].SetTopLeft(xPos, yPos);
			Animation.itemWalk[direction].OnShow();
			break;
		case 1010:
			Animation.itemRun[direction].OnMove();
			Animation.itemRun[direction].SetTopLeft(xPos, yPos);
			Animation.itemRun[direction].OnShow();
			break;
		case 1020:
			Animation.itemThrow[direction][0].SetTopLeft(xPos, yPos);
			Animation.itemThrow[direction][0].ShowBitmap();
			break;
		case 1021:
			Animation.itemThrow[direction][1].SetTopLeft(xPos, yPos);
			Animation.itemThrow[direction][1].ShowBitmap();
			break;
		case 1030:
			Animation.itemRunThrow[direction][0].SetTopLeft(xPos, yPos);
			Animation.itemRunThrow[direction][0].ShowBitmap();
			break;
		case 1031:
			Animation.itemRunThrow[direction][1].SetTopLeft(xPos, yPos);
			Animation.itemRunThrow[direction][1].ShowBitmap();
			break;
		case 2000:
			Animation.Dead[direction][0].SetTopLeft(xPos, yPos);
			Animation.Dead[direction][0].ShowBitmap();
			break;
		case 2001:
			Animation.Dead[direction][1].SetTopLeft(xPos, yPos);
			Animation.Dead[direction][1].ShowBitmap();
			break;
		default:
			break;
		}
		//Special Attack Animation
		EffectObjectAliveManager(mainTime);
		ShowSpecialAttack();
		ShowFrozenPunch();
	}

	void Freeze::CallfrozenWaves() {
		
		SpCount++;
		if (SpCount <= 4) {
			AnimationState = 200;
		}
		else if (SpCount <= 8) {
			AnimationState = 201;
		}
		else if (SpCount <= 12) {
			AnimationState = 202;
		}
		else if (SpCount <= 16) {
			AnimationState = 203;
		}
		else if (SpCount <= 20) {
			AnimationState = 204;
		}
		else if (SpCount <= 24) {
			AnimationState = 205;
			if (SpCount >= 24) {
				SpCount = 0;
				//Clear State
				skillSignal = -1;
			}
		}
	}

	void Freeze::CallfrozenPunchs() {
		SpCount++;
		if (SpCount <= 4) {
			AnimationState = 210;
		}
		else if (SpCount <= 8) {
			AnimationState = 211;
		}
		else if (SpCount <= 12) {
			AnimationState = 212;
		}
		else if (SpCount <= 16) {
			AnimationState = 213;
		}
		else if (SpCount <= 20) {
			AnimationState = 214;
		}
		else if (SpCount <= 24) {
			AnimationState = 215;
		}
		else if (SpCount <= 35) {
			AnimationState = 216;
		}
		else if (SpCount <= 40) {
			AnimationState = 217;
			if (SpCount >= 40) {
				SpCount = 0;
				skillSignal = -1;
			}
		}
	}

	void Freeze::CallfrozenStorms() {
		SpCount++;
		if (SpCount <= 4) {
			AnimationState = 220;
		}
		else if (SpCount <= 8) {
			AnimationState = 221;
		}
		else if (SpCount <= 12) {
			AnimationState = 222;
		}
		else if (SpCount <= 16) {
			AnimationState = 223;
		}
		else if (SpCount <= 20) {
			AnimationState = 224;
		}
		else if (SpCount <= 24) {
			AnimationState = 225;
		}
		else if (SpCount <= 28) {
			AnimationState = 226;
		}
		else if (SpCount <= 32) {
			AnimationState = 227;
		}
		else if (SpCount <= 36) {
			AnimationState = 228;
			if (SpCount >= 36) {
				SpCount = 0;
				skillSignal = -1;
			}
		}
	}

	void Freeze::CallfrozenSwords() {
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

				//need fix this one
			}
		}
	}

	void Freeze::CallSpecial() {
		switch (skillSignal){
		case -1:
			break;
		case 0:
			return CallfrozenWaves();
			break;
		case 1:
			return CallfrozenPunchs();
			break;
		case 2:
			return CallfrozenSwords();
			break;
		case 3:
			return CallfrozenStorms();
			break;
		default:
			break;
		}
	}

	void Freeze::ShowSpecialAttack() {
		for (auto& i : frozenWaves) {
			i->OnShow();
		}
		for (auto& i : frozenStorms) {
			i->OnShow();
		}
	}
	
	void Freeze::DetectSkillDamage(vector<pair<int, int>> theOthersPosition, int *n) {
		pair<int, int> itr(0, 0);  // first : characterID second :damage
		int attackDirection = this->GetDir() ? -1 : 1;
		int yRange1 = 0, yRange2 = 0 ;
		for (auto& i : frozenWaves) {
			for (int h = 0; h < theOthersPosition.size(); h++) {
				if (h != this->serialNumber) {
					if (i->xPos+4 <= theOthersPosition[h].first+50 && i->xPos+78 >= theOthersPosition[h].first + 30) {
						if (i->yPos+23 <= theOthersPosition[h].second+60 && i->yPos+57 >= theOthersPosition[h].second+20) {
							yRange1 = i->yPos - 20;
							yRange2 = i->yPos + 20;
							if (yRange1 <= theOthersPosition[h].second && theOthersPosition[h].second <= yRange2) {
								if (!i->isHit) {
									itr.first = h; itr.second = 500;
									hittedLog[0].push_back(h);
									hittedTable.push_back(itr);
									i->isHit = true;
									this->SetCalculateDamageRequest(true);
									n[h] = 1;
								}
							}
						}
					}
				}
			}
		}

		for (auto& i : frozenPunchs) {
			for (int h = 0; h < theOthersPosition.size(); h++) {
				if (h != this->serialNumber) {
					if (this->direction == 1) {
						if (i->xPos - 149 <= theOthersPosition[h].first + 50 && i->xPos >= theOthersPosition[h].first + 30) {
							if (i->yPos - 30 <= theOthersPosition[h].second + 60 && i->yPos + 79 >= theOthersPosition[h].second + 20) {
								yRange1 = i->yPos - 20;
								yRange2 = i->yPos + 20;
								if (yRange1 <= theOthersPosition[h].second && theOthersPosition[h].second <= yRange2) {
									if (!i->isHit) {
										itr.first = h; itr.second = 500;
										hittedTable.push_back(itr);
										i->isHit = true;
										this->SetCalculateDamageRequest(true);
										n[h] = 1;
									}
								}
							}
						}
					}
					else {
						if (i->xPos + 40 * attackDirection <= theOthersPosition[h].first + 50 && i->xPos + 209 * attackDirection >= theOthersPosition[h].first + 30) {
							if (i->yPos - 30 <= theOthersPosition[h].second + 60 && i->yPos + 79 >= theOthersPosition[h].second + 20) {
								yRange1 = i->yPos - 20;
								yRange2 = i->yPos + 20;
								if (yRange1 <= theOthersPosition[h].second && theOthersPosition[h].second <= yRange2) {
									if (!i->isHit) {
										itr.first = h; itr.second = 500;
										hittedTable.push_back(itr);
										i->isHit = true;
										this->SetCalculateDamageRequest(true);
										n[h] = 1;
									}
								}
							}
						}
					}
				}
			}
		}

		for (auto& i : frozenStorms) {
			for (int h = 0; h < theOthersPosition.size(); h++) {
				if (h != this->serialNumber) {
					if (i->xPos - 35 <= theOthersPosition[h].first + 50 && i->xPos + 124 >= theOthersPosition[h].first + 30) {
						if (i->yPos - 70 <= theOthersPosition[h].second + 60 && i->yPos + 89 >= theOthersPosition[h].second + 20) {
							yRange1 = i->yPos - 20;
							yRange2 = i->yPos + 20;
							if (yRange1 <= theOthersPosition[h].second && theOthersPosition[h].second <= yRange2) {
								if (!i->isHit) {
									itr.first = h; itr.second = 900;
									hittedTable.push_back(itr);
									i->isHit = true;
									this->SetCalculateDamageRequest(true);
									n[h] = 1;
								}
							}
						}
					}
				}
			}
		}
	}
	
	void Freeze::EnemyAiMode(int anotherCharacterPosX, int anotherCharacterPosY, int createdTimes) {
		int coin = createdTimes + 1 + rand() % (10 - 1 + 1);
		int diffX = this->xPos - anotherCharacterPosX;
		int diffY = this->yPos - anotherCharacterPosY;
		
		if (diffX > 0) {
			if (diffX > 80) {
				this->SetMovingRight(false);
				this->SetMovingLeft(true);
				SetRunning(true);
			}
			else if (diffX <= 80 ) {
				this->isRunning = false;
				this->SetMovingLeft(true);
			}
			else {
				this->SetMovingRight(false);
				this->SetMovingLeft(false);
				this->isWalking = false;
				this->isRunning = false;
			}
		}
		else if (diffX < 0) {
			if (abs(diffX) > 80 ) {
				this->SetMovingLeft(false);
				this->SetMovingRight(true);
				SetRunning(true);
			}
			else  if (abs(diffX) <= 80) {

				this->isRunning = false;
				this->SetMovingRight(true);
			} 
			else {
				this->SetMovingRight(false);
				this->SetMovingLeft(false);
				this->isWalking = false;
				this->isRunning = false;
			}
		}
		if (diffY != 0) {
			
			this->SetMovingDown(diffY > 0 ? false : true);
			this->SetMovingUp( diffY > 0 ? true : false);
		}
		else {
			this->SetMovingUp(false);
			this->SetMovingDown(false);
		}

		if (coin % 3 == 0  && coin % 7 == 0) {
			if (diffY == 0 && Mana >= 600) {
				skillSignal = 0;
				this->SetSkill(createdTimes);
				Mana -= 600;
			}
			else if (abs(diffX) <= 360 && abs(diffY) < 40 && Mana >= 900) {
				skillSignal = 3;
				this->SetSkill(createdTimes);
				Mana -= 900;
			}
			else  if (abs(diffX) <= 30 && abs(diffY) < 30) {
				this->SetAttack(true);
			}
		}
		else if (coin % 2 == 0 && coin % 5 == 0) {
			if (abs(diffX) <= 140 && abs(diffY) < 20 && Mana >= 450) {
				skillSignal = 1;
				this->SetSkill(createdTimes);
				Mana -= 450;
			}
			else  if (abs(diffX) <= 30 && abs(diffY) < 30) {
				this->SetAttack(true);
			}
			else if (abs(diffX) <= 360 && abs(diffY) < 30 && Mana >= 900) {
				skillSignal = 3;
				this->SetSkill(createdTimes);
				Mana -= 900;
			}
		}
		else {
			if (abs(diffX) <= 30 && abs(diffY) < 30) {
				this->SetAttack(true);
			}
			if (abs(diffX) <= 140 && abs(diffY) < 20 && Mana >= 450) {
				skillSignal = 1;
				this->SetSkill(createdTimes);
				Mana -= 450;
			}
		}

		//skillSignal = -1;
		if (AttackCount >= 30) {
			this->SetAttack(false);
		}
	}
}