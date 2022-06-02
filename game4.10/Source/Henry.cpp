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
	Henry::Henry(int num,int mapID) {
		CharacterID = 3;
		serialNumber = num;
		SetMapBorder(mapID);
		for (int i = 0; i < 5; i++) {
			skillsEffect_InFieldNumber.push_back(0);
		}
		arrow.reserve(1);
		downArrow.reserve(1);
		downArrow2.reserve(1);
		upArrow.reserve(1);
		airwave.reserve(1);
		pierceArrow.reserve(1);
		demonicSong.reserve(1);
		hittedLog.resize(4);
		SetCalculateDamageRequest(false);
	}

	int Henry::HitEnemy(Character* enemy) {
		if (isAttackFrame()) {
			int yRange1 = yPos - 20;
			int yRange2 = yPos + 20;
			if (yRange1 <= enemy->GetY1() && enemy->GetY1() <= yRange2) {
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

	int Henry::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
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

	void Henry::DetectSkillDamage(vector<pair<int, int>> theOthersPosition, int* n) {
		pair<int, int> itr(0, 0);  // first 第幾隻腳色 second 傷害
		int attackDirection = this->GetDir() ? -1 : 1;

		for (auto& i : arrow) {
			for (int h = 0; h < theOthersPosition.size(); h++) {
				if (h != this->serialNumber) {
					if (i->xPos <= theOthersPosition[h].first + 50 && i->xPos + 48 >= theOthersPosition[h].first + 30) {
						if (i->yPos + 20 <= theOthersPosition[h].second + 60 && i->yPos + 28 >= theOthersPosition[h].second + 20) {
							int yRange1 = i->yPos - 20;
							int yRange2 = i->yPos + 20;
							if (yRange1 <= theOthersPosition[h].second && theOthersPosition[h].second <= yRange2) {
								if (!i->isHit) {
									itr.first = h; itr.second = 250;
									hittedLog[0].push_back(h);
									hittedTable.push_back(itr);
									i->isHit = true;
									this->SetCalculateDamageRequest(true);
								}
							}
						}
					}
				}
			}
		}

		for (auto& i : upArrow) {
			for (int h = 0; h < theOthersPosition.size(); h++) {
				if (h != this->serialNumber) {
					if (i->xPos <= theOthersPosition[h].first + 50 && i->xPos + 48 >= theOthersPosition[h].first + 30) {
						if (i->yPos + 20 <= theOthersPosition[h].second + 60 && i->yPos + 28 >= theOthersPosition[h].second + 20) {
							int yRange1 = i->yPos - 20;
							int yRange2 = i->yPos + 20;
							if (yRange1 <= theOthersPosition[h].second && theOthersPosition[h].second <= yRange2) {
								if (!i->isHit) {
									itr.first = h; itr.second = 250;
									hittedLog[0].push_back(h);
									hittedTable.push_back(itr);
									i->isHit = true;
									this->SetCalculateDamageRequest(true);
								}
							}
						}
					}
				}
			}
		}

		for (auto& i : downArrow) {
			for (int h = 0; h < theOthersPosition.size(); h++) {
				if (h != this->serialNumber) {
					if (i->xPos <= theOthersPosition[h].first + 50 && i->xPos + 48 >= theOthersPosition[h].first + 30) {
						if (i->yPos + 20 <= theOthersPosition[h].second + 60 && i->yPos + 28 >= theOthersPosition[h].second + 20) {
							int yRange1 = i->yPos + 20 - 20;
							int yRange2 = i->yPos + 20 + 20;
							if (yRange1 <= theOthersPosition[h].second && theOthersPosition[h].second <= yRange2) {
								if (!i->isHit) {
									itr.first = h; itr.second = 250;
									hittedLog[0].push_back(h);
									hittedTable.push_back(itr);
									i->isHit = true;
									this->SetCalculateDamageRequest(true);
								}
							}
						}
					}
				}
			}
		}

		for (auto& i : downArrow2) {
			for (int h = 0; h < theOthersPosition.size(); h++) {
				if (h != this->serialNumber) {
					if (i->xPos <= theOthersPosition[h].first + 50 && i->xPos + 48 >= theOthersPosition[h].first + 30) {
						if (i->yPos + 20 <= theOthersPosition[h].second + 60 && i->yPos + 28 >= theOthersPosition[h].second + 20) {
							int yRange1 = i->yPos - 20;
							int yRange2 = i->yPos + 20;
							if (yRange1 <= theOthersPosition[h].second && theOthersPosition[h].second <= yRange2) {
								if (!i->isHit) {
									itr.first = h; itr.second = 250;
									hittedLog[0].push_back(h);
									hittedTable.push_back(itr);
									i->isHit = true;
									this->SetCalculateDamageRequest(true);
								}
							}
						}
					}
				}
			}
		}

		for (auto& i : airwave) {
			for (int h = 0; h < theOthersPosition.size(); h++) {
				if (h != this->serialNumber) {
					if (!this->direction) {
						if (i->xPos - 239 <= theOthersPosition[h].first + 50 && i->xPos - 60 >= theOthersPosition[h].first + 30) {
							if (i->yPos - 30 <= theOthersPosition[h].second + 60 && i->yPos + 79 >= theOthersPosition[h].second + 20) {
								int yRange1 = i->yPos - 20;
								int yRange2 = i->yPos + 20;
								if (yRange1 <= theOthersPosition[h].second && theOthersPosition[h].second <= yRange2) {
									if (!i->isHit) {
										itr.first = h; itr.second = 500;
										hittedTable.push_back(itr);
										i->isHit = true;
										this->SetCalculateDamageRequest(true);
									}
								}
							}
						}
					}
					else {
						if (i->xPos + 40 * attackDirection <= theOthersPosition[h].first + 50 && i->xPos + 229 * attackDirection >= theOthersPosition[h].first + 30) {
							if (i->yPos - 30 <= theOthersPosition[h].second + 60 && i->yPos + 79 >= theOthersPosition[h].second + 20) {
								int yRange1 = i->yPos - 20;
								int yRange2 = i->yPos + 20;
								if (yRange1 <= theOthersPosition[h].second && theOthersPosition[h].second <= yRange2) {
									if (!i->isHit) {
										itr.first = h; itr.second = 500;
										hittedTable.push_back(itr);
										i->isHit = true;
										this->SetCalculateDamageRequest(true);
									}
								}
							}
						}
					}
				}
			}
		}
		for (auto& i : pierceArrow) {  /// issue 不會穿透 需 hittedLog 正常  
			for (int h = 0; h < theOthersPosition.size(); h++) {
				if (h != this->serialNumber) {
					if(i->xPos <= theOthersPosition[h].first + 50 && i->xPos + 48 >= theOthersPosition[h].first + 30) {
						if (i->yPos + 20 <= theOthersPosition[h].second + 60 && i->yPos + 28 >= theOthersPosition[h].second + 20) {
							int yRange1 = i->yPos - 20;
							int yRange2 = i->yPos + 20;
							if (yRange1 <= theOthersPosition[h].second && theOthersPosition[h].second <= yRange2) {
								if (!i->isHit) {
									itr.first = h; itr.second = 900;
									hittedTable.push_back(itr);
									i->isHit = true;
									this->SetCalculateDamageRequest(true);
								}
							}
						}
					}
				}
			}
		}

		for (auto& i : arrowRain) {
			for (int h = 0; h < theOthersPosition.size(); h++) {
				if (h != this->serialNumber) {
					if (i->xPos + 4 <= theOthersPosition[h].first + 50 && i->xPos + 78 >= theOthersPosition[h].first + 30) {
						if (i->yPos + 23 <= theOthersPosition[h].second + 60 && i->yPos + 57 >= theOthersPosition[h].second + 20) {
							int yRange1 = i->yPos - 20;
							int yRange2 = i->yPos + 20;
							if (yRange1 <= theOthersPosition[h].second && theOthersPosition[h].second <= yRange2) {
								if (!i->isHit) {
									itr.first = h; itr.second = 500;
									hittedLog[0].push_back(h);
									hittedTable.push_back(itr);
									i->isHit = true;
									this->SetCalculateDamageRequest(true);
								}
							}
						}
					}
				}
			}
		}

		for (auto& i : demonicSong) {
			for (int h = 0; h < theOthersPosition.size(); h++) {
				if (h != this->serialNumber) {
					if (i->xPos + 4 <= theOthersPosition[h].first + 50 && i->xPos + 78 >= theOthersPosition[h].first + 30) {
						if (i->yPos + 23 <= theOthersPosition[h].second + 60 && i->yPos + 57 >= theOthersPosition[h].second + 20) {
							if (!i->isHit) {
								itr.first = h; itr.second = 500;
								hittedLog[0].push_back(h);
								hittedTable.push_back(itr);
								i->isHit = true;
								this->SetCalculateDamageRequest(true);
							}
						}
					}
				}
			}
		}
	}

	void Henry::SetCharacter() {
		Animation.LoadHenry();
		InitSpecialAttack();
		name = "Henry";
	}

	void Henry::ShowDefense() {
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
	
	void Henry::ShowRoll() {
		//Roll
		RollCount++;
		if (RollCount <= 10) {
			AnimationState = 9;
		}
		else if (RollCount <= 20) {
			AnimationState = 10;
		}
		else if (RollCount <= 30) {
			AnimationState = 11;
		}
		else if (RollCount <= 40) {
			AnimationState = 12;
		}
		else if (RollCount <= 49) {
			AnimationState = 13;
			if (RollCount >= 49) {
				RollCount = 0;
				isDefense = false;
				UnMovable = false;
				SetRunning(false);
				TRACE("Run %d\n", isRunning);
			}
		}
	}

	void Henry::SetAttack(bool flag) {
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
					auto downArrow_Begin = downArrow.begin();
					if (this->AttackState == 5) {
						TRACE("DOWN ARROW\n");
						downArrow.insert(downArrow_Begin, new SkillEffect(9, CurrentTime, direction, xPos-10, yPos-10));
						skillsEffect_InFieldNumber[0] = downArrow.size();
					}
				}
				else if (isCarryItem) {
					LastAttackState = AttackState;
					AttackState = 7;
				}
				else {
					if (!isHitting) {
						LastAttackState = AttackState;
						AttackState = 1;
						auto arrow_Begin = arrow.begin();
						if (this->AttackState == 1) {
							arrow.insert(arrow_Begin, new SkillEffect(4, CurrentTime, direction, xPos, yPos + 20));
							skillsEffect_InFieldNumber[0] = arrow.size();
						}
					}
					else {
						LastAttackState = AttackState;
						AttackState = 1;
						auto arrow_Begin = arrow.begin();
						if (this->AttackState == 1) {
							arrow.insert(arrow_Begin, new SkillEffect(4, CurrentTime, direction, xPos, yPos + 20));
							skillsEffect_InFieldNumber[0] = arrow.size();
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

	void Henry::ShowAttack() {
		AttackCount++;
		switch (AttackState)
		{
		case 1:
			if (AttackCount <= 5) {
				AnimationState = 30;
			}
			else if (AttackCount <= 10) {
				AnimationState = 31;
			}
			else if (AttackCount <= 15) {
				AnimationState = 32;
			}
			else if (AttackCount <= 20) {
				AnimationState = 33;
			}
			else if (AttackCount <= 25) {
				AnimationState = 34;
			}
			else if (AttackCount <= 30) {
				AnimationState = 35;
				if (AttackCount >= 30) {
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
				if (AttackCount == 20) {
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
			if (AttackCount <= 5) {
				AnimationState = 70;
			}
			else if (AttackCount <= 10) {
				AnimationState = 71;
			}
			else if (AttackCount <= 15) {
				AnimationState = 72;
			}
			else if (AttackCount <= 20) {
				AnimationState = 73;
			}
			else if (AttackCount <= 35) {
				AnimationState = 74;
				if (AttackCount == 35) {
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

	bool Henry::isAttackFrame() {
		switch (AnimationState) {
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
		default:
			return false;
			break;
		}
	}

	bool Henry::AttackReach() {
		if (AttackAccumulator >= 400) {
			return true;
		}
		else {
			return false;
		}
	}

	void Henry::SetKnock(bool flag, int Dir, int AttState) {
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

	void Henry::ShowKnock() {
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

	void Henry::SetSkill(int createdTimes) {
		auto downArrow_Begin = downArrow.begin();
		auto downArrow2_Begin = downArrow2.begin();
		auto arrow_Begin = arrow.begin();
		auto upArrow_Begin = upArrow.begin();

		auto pierceArrow_Begin = pierceArrow.begin();
		auto airwave_Begin = airwave.begin();
		auto demonicSong_Begin = demonicSong.begin();
	
		if (this->GetSkillSignal() == 1) {
			pierceArrow.insert(pierceArrow_Begin, new SkillEffect(5, createdTimes, direction, xPos, yPos+20));
			skillsEffect_InFieldNumber[1] = pierceArrow.size();
		}
		else if (this->GetSkillSignal() == 0) {
			airwave.insert(airwave_Begin, new SkillEffect(7, createdTimes, direction, xPos, yPos + 20));
			skillsEffect_InFieldNumber[1] = airwave.size();
		}
		else if (this->GetSkillSignal() == 2) {
			//call three type of Arrow
			upArrow.insert(upArrow_Begin, new SkillEffect(10, createdTimes, direction, xPos-10, yPos + 20));
			skillsEffect_InFieldNumber[1] = upArrow.size();

			arrow.insert(arrow_Begin, new SkillEffect(4, createdTimes, direction, xPos-10, yPos + 20));
			skillsEffect_InFieldNumber[1] = arrow.size();

			downArrow2.insert(downArrow2_Begin, new SkillEffect(11, createdTimes, direction, xPos - 10, yPos + 20));
			skillsEffect_InFieldNumber[0] = downArrow2.size();
		}
		else if (this->GetSkillSignal() == 3) {
			demonicSong.insert(demonicSong_Begin, new SkillEffect(8, createdTimes, direction, xPos, yPos));
			skillsEffect_InFieldNumber[1] = demonicSong.size();
		}
	}

	void Henry::EffectObjectAliveManager(int mainTime) {
		const int arrow_AliveTime = 10000;
		const int downArrow_AliveTime = 10000;
		const int pierceArrow_AliveTime = 10000;
		const int airwave_AliveTime = 10000;
		const int demonicSong_AliveTime = 6000;
		for (auto& i : arrow) {
			if (mainTime - i->createdTime >= arrow_AliveTime) {
				delete i;
				arrow.pop_back();
			}
		}
		for (auto& i : downArrow) {
			if (mainTime - i->createdTime >= arrow_AliveTime) {
				delete i;
				downArrow.pop_back();
			}
		}
		for (auto& i : downArrow2) {
			if (mainTime - i->createdTime >= arrow_AliveTime) {
				delete i;
				downArrow2.pop_back();
			}
		}
		for (auto& i : upArrow) {
			if (mainTime - i->createdTime >= arrow_AliveTime) {
				delete i;
				upArrow.pop_back();
			}
		}
		for (auto& i : pierceArrow) {
			if (mainTime - i->createdTime >= pierceArrow_AliveTime) {
				delete i;
				pierceArrow.pop_back();
			}
		}
		for (auto& i : airwave) {
			if (mainTime - i->createdTime >= airwave_AliveTime) {
				delete i;
				airwave.pop_back();
			}
		}
		for (auto& i : demonicSong) {
			if (mainTime - i->createdTime >= demonicSong_AliveTime) {
				delete i;
				demonicSong.pop_back();
			}
		}
	}

	void Henry::ClearSkill() {
		for (auto& i : arrow) {
			delete i;
			arrow.pop_back();
		}
		for (auto& i : downArrow) {
			delete i;
			downArrow.pop_back();
		}
		for (auto& i : downArrow2) {
			delete i;
			downArrow2.pop_back();
		}
		for (auto& i : upArrow) {
			delete i;
			upArrow.pop_back();
		}
		for (auto& i : pierceArrow) {
			delete i;
			pierceArrow.pop_back();
		}
		for (auto& i : airwave) {
			delete i;
			airwave.pop_back();
		}
		for (auto& i : demonicSong) {
			delete i;
			demonicSong.pop_back();
		}
	}

	void Henry::InitSpecialAttack() {
		//airWave
		airWaveAnimation[0][0].LoadBitmap(".\\res\\Henry\\Henry_1\\Henry_1_65.bmp", RGB(0, 0, 0));
		airWaveAnimation[0][1].LoadBitmap(".\\res\\Henry\\Henry_1\\Henry_1_66.bmp", RGB(0, 0, 0));
		airWaveAnimation[0][2].LoadBitmap(".\\res\\Henry\\Henry_1\\Henry_1_67.bmp", RGB(0, 0, 0));
		airWaveAnimation[0][3].LoadBitmap(".\\res\\Henry\\Henry_1\\Henry_1_68.bmp", RGB(0, 0, 0));
		airWaveAnimation[0][4].LoadBitmap(".\\res\\Henry\\Henry_1\\Henry_1_69.bmp", RGB(0, 0, 0));
		airWaveAnimation[0][5].LoadBitmap(".\\res\\Henry\\Henry_1\\Henry_1_59.bmp", RGB(0, 0, 0));
		airWaveAnimation[1][0].LoadBitmap(".\\res\\Henry\\Henry_1_reverse\\Henry_1_reverse_64.bmp", RGB(0, 0, 0));
		airWaveAnimation[1][1].LoadBitmap(".\\res\\Henry\\Henry_1_reverse\\Henry_1_reverse_63.bmp", RGB(0, 0, 0));
		airWaveAnimation[1][2].LoadBitmap(".\\res\\Henry\\Henry_1_reverse\\Henry_1_reverse_62.bmp", RGB(0, 0, 0));
		airWaveAnimation[1][3].LoadBitmap(".\\res\\Henry\\Henry_1_reverse\\Henry_1_reverse_61.bmp", RGB(0, 0, 0));
		airWaveAnimation[1][4].LoadBitmap(".\\res\\Henry\\Henry_1_reverse\\Henry_1_reverse_60.bmp", RGB(0, 0, 0));
		airWaveAnimation[1][5].LoadBitmap(".\\res\\Henry\\Henry_1_reverse\\Henry_1_reverse_50.bmp", RGB(0, 0, 0));

		//pierceArrow
		pierceArrowAnimation[0][0].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_4.bmp", RGB(0, 0, 0));
		pierceArrowAnimation[0][1].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_5.bmp", RGB(0, 0, 0));
		pierceArrowAnimation[0][2].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_6.bmp", RGB(0, 0, 0));
		pierceArrowAnimation[0][3].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_7.bmp", RGB(0, 0, 0));
		pierceArrowAnimation[1][0].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_5.bmp", RGB(0, 0, 0));
		pierceArrowAnimation[1][1].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_4.bmp", RGB(0, 0, 0));
		pierceArrowAnimation[1][2].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_3.bmp", RGB(0, 0, 0));
		pierceArrowAnimation[1][3].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_2.bmp", RGB(0, 0, 0));

		//arrowRain
		arrowRainAnimation[0][0].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_10.bmp", RGB(0, 0, 0));
		arrowRainAnimation[0][1].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_11.bmp", RGB(0, 0, 0));
		arrowRainAnimation[0][2].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_12.bmp", RGB(0, 0, 0));
		arrowRainAnimation[0][3].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_13.bmp", RGB(0, 0, 0));
		arrowRainAnimation[0][4].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_14.bmp", RGB(0, 0, 0));
		arrowRainAnimation[0][5].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_15.bmp", RGB(0, 0, 0));
		arrowRainAnimation[0][6].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_16.bmp", RGB(0, 0, 0));
		arrowRainAnimation[0][7].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_17.bmp", RGB(0, 0, 0));
		arrowRainAnimation[1][0].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_19.bmp", RGB(0, 0, 0));
		arrowRainAnimation[1][1].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_18.bmp", RGB(0, 0, 0));
		arrowRainAnimation[1][2].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_17.bmp", RGB(0, 0, 0));
		arrowRainAnimation[1][3].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_16.bmp", RGB(0, 0, 0));
		arrowRainAnimation[1][4].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_15.bmp", RGB(0, 0, 0));
		arrowRainAnimation[1][5].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_14.bmp", RGB(0, 0, 0));
		arrowRainAnimation[1][6].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_13.bmp", RGB(0, 0, 0));
		arrowRainAnimation[1][7].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_12.bmp", RGB(0, 0, 0));

		//demonic Song
		demonicSongAnimation[0][0].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_0.bmp", RGB(0, 0, 0));
		demonicSongAnimation[0][1].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_1.bmp", RGB(0, 0, 0));
		demonicSongAnimation[0][2].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_2.bmp", RGB(0, 0, 0));
		demonicSongAnimation[0][3].LoadBitmap(".\\res\\Henry\\Henry_2\\Henry_2_3.bmp", RGB(0, 0, 0));
		demonicSongAnimation[1][0].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_9.bmp", RGB(0, 0, 0));
		demonicSongAnimation[1][1].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_8.bmp", RGB(0, 0, 0));
		demonicSongAnimation[1][2].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_7.bmp", RGB(0, 0, 0));
		demonicSongAnimation[1][3].LoadBitmap(".\\res\\Henry\\Henry_2_reverse\\Henry_2_reverse_6.bmp", RGB(0, 0, 0));
	}

	void Henry::OnMove() {
		
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
		if (specialState == 1) {
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

	void Henry::OnShow(vector<pair<int, int>>theOthersPosition, int mainTime) {
		CurrentTime = mainTime;
		switch (AnimationState)
		{
		case 0:
			if (isCarryItem) {
				Animation.itemNormal[direction].SetTopLeft(xPos, yPos);
				Animation.itemNormal[direction].ShowBitmap();
			}
			else if (!isCarryItem) {
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
		case 33:
			Animation.NormalAttack1[direction][3].SetTopLeft(xPos, yPos);
			Animation.NormalAttack1[direction][3].ShowBitmap();
			break;
		case 34:
			Animation.NormalAttack1[direction][4].SetTopLeft(xPos, yPos);
			Animation.NormalAttack1[direction][4].ShowBitmap();
			break;
		case 35:
			Animation.NormalAttack1[direction][5].SetTopLeft(xPos, yPos);
			Animation.NormalAttack1[direction][5].ShowBitmap();
			break;
		case 40:
			Animation.NormalAttack2[direction][0].SetTopLeft(xPos, yPos);
			Animation.NormalAttack2[direction][0].ShowBitmap();
			break;
		case 41:
			Animation.NormalAttack2[direction][1].SetTopLeft(xPos, yPos);
			Animation.NormalAttack2[direction][1].ShowBitmap();
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
		case 200:
			airWaveAnimation[direction][0].SetTopLeft(xPos, yPos);
			airWaveAnimation[direction][0].ShowBitmap();
			break;
		case 201:
			airWaveAnimation[direction][1].SetTopLeft(xPos, yPos);
			airWaveAnimation[direction][1].ShowBitmap();
			break;
		case 202:
			airWaveAnimation[direction][2].SetTopLeft(xPos, yPos);
			airWaveAnimation[direction][2].ShowBitmap();
			break;
		case 203:
			airWaveAnimation[direction][3].SetTopLeft(xPos, yPos);
			airWaveAnimation[direction][3].ShowBitmap();
			break;
		case 204:
			airWaveAnimation[direction][4].SetTopLeft(xPos, yPos);
			airWaveAnimation[direction][4].ShowBitmap();
			break;
		case 205:
			airWaveAnimation[direction][5].SetTopLeft(xPos, yPos);
			airWaveAnimation[direction][5].ShowBitmap();
			break;
			//Frozen Punch
		case 210:
			pierceArrowAnimation[direction][0].SetTopLeft(xPos, yPos);
			pierceArrowAnimation[direction][0].ShowBitmap();
			break;
		case 211:
			pierceArrowAnimation[direction][1].SetTopLeft(xPos, yPos);
			pierceArrowAnimation[direction][1].ShowBitmap();
			break;
		case 212:
			pierceArrowAnimation[direction][2].SetTopLeft(xPos, yPos);
			pierceArrowAnimation[direction][2].ShowBitmap();
			break;
		case 213:
			pierceArrowAnimation[direction][3].SetTopLeft(xPos, yPos);
			pierceArrowAnimation[direction][3].ShowBitmap();
			break;
			//frozenStorms
		case 220:
			arrowRainAnimation[direction][0].SetTopLeft(xPos, yPos);
			arrowRainAnimation[direction][0].ShowBitmap();
			break;
		case 221:
			arrowRainAnimation[direction][1].SetTopLeft(xPos, yPos);
			arrowRainAnimation[direction][1].ShowBitmap();
			break;
		case 222:
			arrowRainAnimation[direction][2].SetTopLeft(xPos, yPos);
			arrowRainAnimation[direction][2].ShowBitmap();
			break;
		case 223:
			arrowRainAnimation[direction][3].SetTopLeft(xPos, yPos);
			arrowRainAnimation[direction][3].ShowBitmap();
			break;
		case 224:
			arrowRainAnimation[direction][4].SetTopLeft(xPos, yPos);
			arrowRainAnimation[direction][4].ShowBitmap();
			break;
		case 225:
			arrowRainAnimation[direction][5].SetTopLeft(xPos, yPos);
			arrowRainAnimation[direction][5].ShowBitmap();
			break;
		case 226:
			arrowRainAnimation[direction][6].SetTopLeft(xPos, yPos);
			arrowRainAnimation[direction][6].ShowBitmap();
			break;
		case 227:
			arrowRainAnimation[direction][7].SetTopLeft(xPos, yPos);
			arrowRainAnimation[direction][7].ShowBitmap();
			break;
		case 230:
			demonicSongAnimation[direction][0].SetTopLeft(xPos, yPos);
			demonicSongAnimation[direction][0].ShowBitmap();
			break;
		case 231:
			demonicSongAnimation[direction][1].SetTopLeft(xPos, yPos);
			demonicSongAnimation[direction][1].ShowBitmap();
			break;
		case 232:
			demonicSongAnimation[direction][2].SetTopLeft(xPos, yPos);
			demonicSongAnimation[direction][2].ShowBitmap();
			break;
		case 233:
			demonicSongAnimation[direction][3].SetTopLeft(xPos, yPos);
			demonicSongAnimation[direction][3].ShowBitmap();
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
	}

	void Henry::CallairWave() {
	
		SpCount++;
		if (SpCount <= 10) {
			AnimationState = 200;
		}
		else if (SpCount <= 20) {
			AnimationState = 201;
		}
		else if (SpCount <= 30) {
			AnimationState = 202;
		}
		else if (SpCount <= 40) {
			AnimationState = 203;
		}
		else if (SpCount <= 50) {
			AnimationState = 204;
		}
		else if (SpCount <= 60) {
			AnimationState = 205;
			if (SpCount >= 60) {
				SpCount = 0;
				//Clear State
				skillSignal = -1;
			}
		}
	}

	void Henry::CallpierceArrow() {
		SpCount++;
		if (SpCount <= 10) {
			AnimationState = 30;
		}
		else if (SpCount <= 20) {
			AnimationState = 31;
		}
		else if (SpCount <= 30) {
			AnimationState = 210;
		}
		else if (SpCount <= 40) {
			AnimationState = 211;
		}
		else if (SpCount <= 50) {
			AnimationState = 212;
		}
		else if (SpCount <= 60) {
			AnimationState = 213;
			if (SpCount >= 60) {
				SpCount = 0;
				skillSignal = -1;
			}
		}
	}

	void Henry::CallarrowRain() {
		SpCount++;
		if (SpCount <= 5) {
			AnimationState = 220;
		}
		else if (SpCount <= 10) {
			AnimationState = 221;
		}
		else if (SpCount <= 15) {
			AnimationState = 222;
		}
		else if (SpCount <= 20) {
			AnimationState = 223;
		}
		else if (SpCount <= 25) {
			AnimationState = 224;
		}
		else if (SpCount <= 30) {
			AnimationState = 225;
		}
		else if (SpCount <= 35) {
			AnimationState = 226;
		}
		else if (SpCount <= 40) {
			AnimationState = 227;
			if (SpCount >= 40) {
				SpCount = 0;
				skillSignal = -1;
			}
		}
	}

	void Henry::CalldemonicSong() {
		SpCount++;
		if (SpCount <= 80) {
			AnimationState = 230;
		}
		else if (SpCount <= 160) {
			AnimationState = 231;
		}
		else if (SpCount <= 240) {
			AnimationState = 232;
		}
		else if (SpCount <= 320) {
			AnimationState = 233;
			if (SpCount >= 320) {
				SpCount = 0;
				skillSignal = -1;
			}
		}
	}

	void Henry::CallSpecial() {
		switch (skillSignal)
		{
		case -1:
			break;
		case 0:
			return CallairWave();
			break;
		case 1:
			return CallpierceArrow();
			break;
		case 2:
			return CallarrowRain();
			break;
		case 3:
			return CalldemonicSong();
			break;
		default:
			break;
		}
	}

	void Henry::ShowSpecialAttack() {
		for (auto& i : arrow) {
			i->OnShow();
		}
		for (auto& i : downArrow) {
			i->OnShow();
		}
		for (auto& i : downArrow2) {
			i->OnShow();
		}
		for (auto& i : upArrow) {
			i->OnShow();
		}
		for (auto& i : pierceArrow) {
			i->OnShow();
		}
		for (auto& i : airwave) {
			i->OnShow();
		}
		for (auto& i : demonicSong) {
			i->OnShow();
		}
	}
	
	void Henry::EnemyAiMode(int anotherCharacterPosX, int anotherCharacterPosY, int createdTimes) {
		int diffX = this->xPos - anotherCharacterPosX;
		int diffY = this->yPos - anotherCharacterPosY;
		if (diffX > 0) {
			if (diffX > 10) {
				this->SetMovingRight(false);
				this->SetMovingLeft(true);
				SetRunning(true);
			}
			else {
				SetRunning(false);
				this->SetMovingLeft(true);
			}
		}
		else if (diffX < 0) {
			if (diffX < -10) {
				this->SetMovingLeft(false);
				this->SetMovingRight(true);
				SetRunning(true);
			}
			else {
				SetRunning(false);
				this->SetMovingRight(true);
			}
		}
		if (diffY > 0) {
			SetRunning(false);
			this->SetMovingDown(false);
			this->SetMovingUp(true);
		}
		else {
			SetRunning(false);
			this->SetMovingUp(false);
			this->SetMovingDown(true);
		}
	}
}