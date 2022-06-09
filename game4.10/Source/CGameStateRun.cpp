#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <string> 
#include "CGameStateRun.h"
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#define  _CRTDBG_MAP_ALLOC
#include  < stdlib.h >
#include  < crtdbg.h >
#define Forest 0
#define HKC 1
#define BC 2
using namespace skillTable;
namespace game_framework {
	CGameStateRun::CGameStateRun(CGame* g) : CGameState(g) {
		characterList.reserve(2);
		theOthersPosition.reserve(2);
		HealthPlayer1 = new HealthBar();
		HealthPlayer2 = new HealthBar();
		map.push_back(new Map(BC));
		map.push_back(new Map(Forest));
		map.push_back(new Map(HKC));
		stageTitles.push_back(new CMovingBitmap());
		clearFlag = flaG = cheat = false;
		characterSlidePriority.reserve(2);

		characterSlidePriority.push_back(-1);
		characterSlidePriority.push_back(-1);
	}

	void CGameStateRun::OnBeginState() {

		for (int i = 0; i < 2; i++) {
			theOthersPosition.push_back(pair<int, int>(0, 0));
		}
		TimePassed = 0;
	}

	void CGameStateRun::OnMove() {					// 移動遊戲元素
		if (!map[mapNowID]->drops.empty()) {
			for (auto i : map[mapNowID]->drops) {
				i->OnMove();
			}
		}
		//clear drops
		auto it = map[mapNowID]->drops.begin();
		for (auto i : map[mapNowID]->drops) {
			if (i->GetHp() <= 0) {
				map[mapNowID]->drops.erase(it);
			}
			else {
				it++;
			}

		}

		int count = 0;
		for (auto i : characterList) {
			//check frozenSword spawn
			if (i->CharacterID == 2 && i->signalSpawnSword==true) {
				if (i->FrozenSwordMode == false) {
					map[mapNowID]->drops.push_back(new FieldObject(2, map[mapNowID]->GetMapID()));
					int id = map[mapNowID]->drops.size()-1;
					map[mapNowID]->drops[id]->SetOwner(i->serialNumber);
					map[mapNowID]->drops[id]->SetState(1);
					i->SetPickup(true, id, 2);
					i->Pickup(map[mapNowID]->drops[id]);
					i->FrozenSwordMode = true;
				}
				i->signalSpawnSword = false;
			}

			if (i->GetHealth() <= 0) {
				i->SetAlive(false);
			}
			count++;
		}

		SetAbonormalStatus();
		characterList[0]->OnMove();
		characterList[1]->OnMove();
		//Reset
		int x = 0;
		for (auto i : characterList) {
			tables[x++] = i->specialState;
		}
		SetCharacterSlide();

		SetAllCharacterPosition();

		int num0 = 0;
		int num1 = 0;
		for (auto i : characterList) {
			num1 = 0;
			for (auto j : characterList) {
				if (num0 != num1) {
					if (i->HitEnemy(j) && i->isAttacking) {
						if (j->HealthPoint >= 0) {
							j->SetKnock(true, i->GetDir(), i->AttackState);
							j->isGettingDamage(i->AttackPoint);
						}
					}
				}
				num1++;
			}
			num0++;
		}

		// 動態地圖相關
		map[mapNowID]->ResetCharactAccumulator(characterList[0]->GetDistance(), characterList[1]->GetDistance());
		characterList[0]->DistanceAccumulatorReset();
		characterList[1]->DistanceAccumulatorReset();
		//if (! characterList[0]->specialState) {
			map[mapNowID]->ScenesCamera(characterList[0]->DistanceAccumulatorReset(), characterList[0]->isRunning, characterList[0]->GetDir(), characterList[0]->GetDistance());
		//}
		//if (! characterList[1]->specialState) {
			map[mapNowID]->ScenesCamera(characterList[1]->DistanceAccumulatorReset(), characterList[1]->isRunning, characterList[1]->GetDir(), characterList[1]->GetDistance());
		//}
		if (map[mapNowID]->characterOffsetFlag) {
			CharacterMapPosOffset();
		}
		///
		CalculateDamage(theOthersPosition);
		//item block Character function
		int countOwner = 0;
		for (auto j : characterList) {
			for (auto i : map[mapNowID]->drops) {
				//Throw Object Hit Player
				if (i->GetState() == 2 || i->GetState()==3) {
					if (i->HitRectangle(j->GetX1(), j->GetY1(), j->GetX2(), j->GetY2())) {
						int yRange1 = j->GetY1()-10;
						int yRange2 = j->GetY1() + 20;
						if (yRange1 <= i->GetY() && i->GetY() <= yRange2) {
							if (i->GetOwner() != j->serialNumber) {
								j->isGettingDamage(50);
								j->SetKnock(true, i->GetDir(), 6);
							}
						}
					}
				}
				//frozen Sword Attack && Set Frozen
				if (i->itemType == 2) {
					if (i->HitWeapon(j->GetX1(), j->GetY1(), j->GetX2(), j->GetY2())) {
						int yRange1 = j->GetY1() - 10;
						int yRange2 = j->GetY1() + 20;
						if (yRange1 <= i->GetYB() && i->GetYB() <= yRange2) {
							if (i->isAttackFrame()) {
								if (i->GetOwner() != j->serialNumber) {
									j->isGettingDamage(50);
									j->specialState = 1;
									tables[countOwner] = 1;
								}
							}
						}
					}
				}
				//Determine Character can't run through item
				//in item's yPos range
				//Still some bug need to fix, like walked into left down will teleport
				if (i->itemType == 1 && i->GetState()==0) {
					if (i->GetY() - 40 <= j->GetY1() && j->GetY1() <= i->GetY()) {
						if (j->GetX1() > i->GetX() - 48 && !(j->GetX1() >= i->GetX() + 20)) {
							j->SetXY(i->GetX() - 48, j->GetY1());
						}
						if (j->GetX1() <= i->GetX() + 25 && !(j->GetX1() <= i->GetX() - 48)) {
							j->SetXY(i->GetX() + 25, j->GetY1());
						}
					}
					if (i->GetX() - 40 <= j->GetX1() && j->GetX1() <= i->GetX()) {
						if (j->GetY1() > i->GetY() - 48 && !(j->GetY1() >= i->GetY() + 5)) {
							j->SetXY(j->GetX1(), i->GetY() - 48);
						}
						if (j->GetY1() <= i->GetY() + 10 && !(j->GetY1() <= i->GetY() - 48)) {
							j->SetXY(j->GetX1(), i->GetY() + 10);
						}
					}
				}

			}
			countOwner++;
		}

		//Character NearItem
		for (auto j : characterList) {
			if (map[mapNowID]->drops.size() == 0) {
				j->isNearItem = false;
			}

			for (auto i : map[mapNowID]->drops) {
				j->NearItem(i->GetX(), i->GetY(), i->GetX() + 58, i->GetY() + 58, i->GetOwner());
				if (j->isNearItem == true) {
					break;
				}

			}
		}
		int num = 0;
		int num2 = 0;
		for (auto i : map[mapNowID]->drops) {
			for (auto j : characterList) {
				if (!j->isRunning) {
					if (i->HitPlayer(num2, j->GetX1(), j->GetY1(), j->GetX2(), j->GetY2(), j->isAttacking, j->isAttackFrame())) {
						if (j->isDropItem == false && j->isCarryItem == false && j->GetSkillSignal() == -1) {
							if (i->GetState() == 0) {
								j->SetPickup(true, num, i->itemType);
								i->SetState(1);
								i->SetOwner(j->serialNumber);
							}
						}
					}
				}
				if (i->GetOwner() == j->serialNumber && j->itemId == num) {
					if (i->GetState() == 1) {
						j->Pickup((map[mapNowID]->drops[num]));
					}
				}
				num2++;
			}
			num++;
		}
		if (characterList[0]->GetHealth() == 0) {
			GotoGameState(GAME_STATE_OVER);
		}
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		ShowInitProgress(50);
		Sleep(300);
		for (auto& i : map) {
			i->Load();
		}
		black.LoadBitmap(BITMAP_BLACKSCREEN); // 刷新畫面用
		black.SetTopLeft(0, 0);
		stageTitles[0]->LoadBitmapA(".\\res\\sys\\stage.bmp");
		stageTitles[0]->SetTopLeft(266, 280);
		HealthPlayer1->OnLoad(0, 0);
		HealthPlayer2->OnLoad(400, 0);
		go.LoadBitmapA(".\\res\\sys\\go.bmp", RGB(0, 0, 0));
		go.SetTopLeft(0, 200);
		switch (map[mapNowID]->GetMapID()) {
		case Forest:
			CAudio::Instance()->Load(Forest, "bgm\\stage1.wav");	// 載入編號0的聲音ding.wav
			CAudio::Instance()->Play(Forest, true);
			break;
		case HKC:
			//CAudio::Instance()->Load(HKC, "bgm\\stage2.wav");	// 載入編號0的聲音ding.wav
			//CAudio::Instance()->Play(HKC, true);
			break;
		case BC:
			//CAudio::Instance()->Load(BC, "bgm\\stage3.wav");	// 載入編號0的聲音ding.wav
			//CAudio::Instance()->Play(BC, true);
			break;
		default:
			break;
		}

	}

	void CGameStateRun::SetAbonormalStatus() {
		int x = 0;
		for (auto i : characterList) {
			i->specialState = tables[x++];
		}
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
		characterList[0]->InputKeyDown(nChar, CurrentTime, 0);
		//characterList[1]->InputKeyDown(nChar, CurrentTime, 1);
		frozenPunchList.insert(frozenPunchList.begin(), characterList[0]->frozenPunchs.begin(), characterList[0]->frozenPunchs.end());

		
		//Reset item state
		for (auto i : characterList) {
			if (i->isDropItem == true) {
				map[mapNowID]->drops[i->itemId]->liftUp(false, i->GetX1(), i->GetY1(), i->GetDir(), i->GetAnimationState(),i->GetRunCurrent());
				i->isCarryItem = false;
				i->isDropItem = false;
				i->ResetItem();
			}
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
		const char nextV = 0x56;
		characterList[0]->InputKeyUp(nChar, 0);
		//characterList[1]->InputKeyUp(nChar, 1);
		if (nChar == nextV) {
			cheat = true;
		}
		if (mapNowID < 1) {
			/*CAudio::Instance()->Stop(map[mapNowID]->GetMapID());
			mapNowID++;*/
			//switch (map[mapNowID]->GetMapID()) {
			//case Forest:
			//	CAudio::Instance()->Load(Forest, "bgm\\stage1.wav");	// 載入編號0的聲音ding.wav
			//	CAudio::Instance()->Play(Forest, true);
			//	break;
			//case HKC:
			//	//CAudio::Instance()->Load(HKC, "bgm\\stage2.wav");	// 載入編號0的聲音ding.wav
			//	//CAudio::Instance()->Play(HKC, true);
			//	break;
			//case BC:
			//	//CAudio::Instance()->Load(BC, "bgm\\stage3.wav");	// 載入編號0的聲音ding.wav
			//	//CAudio::Instance()->Play(BC, true);
			//	break;
			//default:
			//	break;
			//}
		}
	}
	
	void CGameStateRun::SetStageTitle() {
		stageTitles.push_back(new CMovingBitmap());
		if (cheat) {
			mapNowID = 1;
		}
		switch (mapNowID) {
		case 0:
			stageTitles[1]->LoadBitmapA(".\\res\\sys\\stage2.bmp");
			break;
		case 1:
			stageTitles[1]->LoadBitmapA(".\\res\\sys\\stage3.bmp");
			break;
		default:
			break;
		}
		stageTitles[1]->SetTopLeft(455, 280);

	}
	
	void CGameStateRun::ClearStageTitle() {
		delete stageTitles[1];
		stageTitles.pop_back();
	}
	
	void CGameStateRun::SetCharacterSlide() {
		constexpr int walk[2] = { 1,1001 };
		constexpr int run[2] = { 2,1010 };
		constexpr int resetNum = -1;
		int cnt = 0;
		for (auto i : characterList) {
			if (i->GetAnimationState() == walk[0] || i->GetAnimationState() == walk[1] || i->GetAnimationState() == run[0] || i->GetAnimationState() == run[1]) {
				if (characterSlidePriority[cnt] == resetNum) {
					characterSlidePriority[cnt] = TimePassed;
				}
			}
			else {
				characterSlidePriority[cnt] = resetNum;
			}
			cnt++;
		}
	}

	void CGameStateRun::SetAllCharacterPosition() {
		for (int i = 0; i < characterList.size(); i++) {
			theOthersPosition[i].first = characterList[i]->GetX1();
			theOthersPosition[i].second = characterList[i]->GetY1();
		}
	}

	void CGameStateRun::CharacterMapPosOffset() {
		constexpr int resetNum(-1);
		constexpr int characterMoving_dx(2);
		int index(-1);
		if ((characterSlidePriority[0] != -1 || characterSlidePriority[1] != -1) && characterSlidePriority[0] != characterSlidePriority[1]) {
			int direction;
			if (characterSlidePriority[0] > characterSlidePriority[1]) {
				direction = characterList[0]->GetDir() ? 1 : -1;
				index = 0;
			}
			else {
				index = 1;
				direction = characterList[1]->GetDir() ? 1 : -1;
			}
			for (auto i : characterList) {
				if (characterList[index]->GetDistance() > characterMoving_dx) {
					i->SetXY(i->GetX1() + 1 * direction, i->GetY1());
				}
			}
		}
	}

	void  CGameStateRun::CalculateDamage(vector<pair<int, int>> theOthersPosition) {

		for (int i = 0; i < 2; i++) {
			if (this->game->selectCharacterID[i] == 0) {
				static_cast<Woody*>(characterList[i])->DetectSkillDamage(theOthersPosition, tables);
			}
			else if (this->game->selectCharacterID[i] == 1) {
				static_cast<Freeze*>(characterList[i])->DetectSkillDamage(theOthersPosition, tables);
			}
			else if (this->game->selectCharacterID[i] == 2) {
				static_cast<Henry*>(characterList[i])->DetectSkillDamage(theOthersPosition, tables);
			}
		}

		if (characterList[0]->GetCalculateDamageRequest() || characterList[1]->GetCalculateDamageRequest()) {
			for (auto& u : characterList) {
				for (auto& i : u->hittedTable) { /// issue :可能不會改 !!!
					if (i.first == 0) {
						characterList[0]->isGettingDamage(i.second);
						if (characterList[1]->CharacterID != 2 && i.second!=0) {
							TRACE("Test \n");
							characterList[0]->SetKnock(true, u->GetDir(), 1);
						}
						this->game->totalDamage[0] += i.second;
					}
					else if (i.first == 1) {
						characterList[1]->isGettingDamage(i.second);
						this->game->totalDamage[1] += i.second;
						if (characterList[0]->CharacterID != 2 && i.second != 0) {
							characterList[1]->SetKnock(true, u->GetDir(), 1);
						}
					}
				}
			}
			for (auto& i : characterList[0]->hittedTable) {
				pair<int, int>().swap(i);
			}
			for (auto& i : characterList[1]->hittedTable) {
				pair<int, int>().swap(i);
			}

			characterList[0]->SetCalculateDamageRequest(false);
			characterList[1]->SetCalculateDamageRequest(false);
		}
	}

	boolean CompareC(Character* obj1, Character* obj2) {
		return obj1->GetY1() < obj2->GetY1();
	}

	boolean CompareF(FieldObject* obj1, FieldObject* obj2) {
		return obj1->GetY() < obj2->GetY();
	}

	boolean CompareFP(SkillEffect* s1, SkillEffect* s2) {
		return s1->yPos < s2->yPos;
	}

	void CGameStateRun::SortedShow() {
		vector<FieldObject*> dropCopy;
		vector<Character*> characterListCopy;
		vector<SkillEffect*> frozenPunchListCopy;
		vector<int> showSequence(3, 0), sequenceValue_Y(3, 0);
		boolean dropEmpty = map[mapNowID]->drops.empty(), characterEmpty = characterList.empty(), frozemPunchEmpty = frozenPunchList.empty();
		int totalSize = map[mapNowID]->drops.size() + characterList.size() + frozenPunchList.size();

		if (!dropEmpty) {
			dropCopy.assign(map[mapNowID]->drops.begin(), map[mapNowID]->drops.end());
			std::sort(dropCopy.begin(), dropCopy.end(), CompareF);
			sequenceValue_Y[0] = dropCopy[0]->GetY();
		}
		else {
			showSequence[0] = -1;
			sequenceValue_Y[0] = 10000;
		}
		if (!characterEmpty) {
			characterListCopy.assign(characterList.begin(), characterList.end());
			std::sort(characterListCopy.begin(), characterListCopy.end(), CompareC);
			sequenceValue_Y[1] = characterListCopy[0]->GetY1();
		}
		else {
			showSequence[1] = -1;
			sequenceValue_Y[1] = 10000;
		}
		if (!frozemPunchEmpty) {
			frozenPunchListCopy.assign(frozenPunchList.begin(), frozenPunchList.end());
			std::sort(frozenPunchList.begin(), frozenPunchList.end(), CompareFP);
			sequenceValue_Y[2] = frozenPunchListCopy[0]->yPos;
		}
		else {
			showSequence[2] = -1;
			sequenceValue_Y[2] = 10000;
		}

		for (int i = 0; i < totalSize; i++) {
			auto showingIndex = std::min_element(sequenceValue_Y.begin(), sequenceValue_Y.end()) - sequenceValue_Y.begin();
			switch (showingIndex) {
			case 0:
				dropCopy[showSequence[0]]->ShowAnimation();
				if (showSequence[0] < map[mapNowID]->drops.size() - 1) {
					showSequence[0] += 1;
					sequenceValue_Y[0] = dropCopy[showSequence[0]]->GetY();

				}
				else {
					sequenceValue_Y[0] = 1000;
				}
				break;
			case 1:
				characterListCopy[showSequence[1]]->OnShow(theOthersPosition, CurrentTime);
				if (showSequence[1] < characterList.size() - 1) {
					showSequence[1] += 1;
					sequenceValue_Y[1] = characterListCopy[showSequence[1]]->GetY1();
				}
				else {
					sequenceValue_Y[1] = 1000;
				}
				break;
			case 2:
				frozenPunchListCopy[showSequence[2]]->OnShow();
				if (showSequence[2] < frozenPunchListCopy.size() - 1) {
					showSequence[2]++;
					sequenceValue_Y[2] = frozenPunchListCopy[showSequence[2]]->yPos;
				}
				else {
					sequenceValue_Y[2] = 1000;
				}
				break;
			default:
				break;
			}

		}
	}

	void CGameStateRun::ResetGame() {
		int cnt = 0;
		if (!clearFlag) {
			clearedTime = TimePassed / 1000;
		}

		if (((!characterList[0]->GetAlive() || !characterList[1]->GetAlive()) && !flaG) || cheat) {

			clearFlag = true;
			black.ShowBitmap();
			if (stageTitles.size() == 1) {
				SetStageTitle();
			}
			for (auto x : stageTitles) {
				x->ShowBitmap();
			}
			if ((TimePassed / 1000 - clearedTime) == 2) {
				clearFlag = false;
				if (mapNowID < 2) {
					mapNowID++;
				}
				for (auto& i : characterList) {
					i->ClearSkill();
					i->ClearWeaponState();
					if (!i->GetAlive()) {
						delete i;
						characterList[cnt] = new  Henry(1, map[mapNowID]->GetMapID());
						characterList[cnt]->SetXY(400, 401);
						characterList[cnt]->SetCharacter();
						tables[1] = -1;
						if (cnt == 0) {
							delete HealthPlayer1;
							HealthPlayer1 = new HealthBar();
							HealthPlayer1->loadSmallImg(1);
							HealthPlayer1->OnLoad(400, 0);
						}
						else {
							delete HealthPlayer2;
							HealthPlayer2 = new HealthBar();
							HealthPlayer2->loadSmallImg(2);
							HealthPlayer2->OnLoad(400, 0);
						}
					}
					cnt++;
				}
				clearedTime = 0;
				flaG = true;
				cheat = false;
				ClearStageTitle();
			}
		}
	}


	void CGameStateRun::OnShow() {
		boolean showStatus;
		//get character
		if (GetCharacter == false) {
			map[mapNowID]->drops.push_back(new FieldObject(1, map[mapNowID]->GetMapID()));
			switch (this->game->selectCharacterID[0]) {
			case 0:
				characterList.push_back(new Woody(0, map[mapNowID]->GetMapID()));
				break;
			case 1:
				characterList.push_back(new Freeze(0, map[mapNowID]->GetMapID()));
				break;
			case 2:
				characterList.push_back(new Henry(0, map[mapNowID]->GetMapID()));
				break;
			default:
				characterList.push_back(new Freeze(0, map[mapNowID]->GetMapID()));

				break;
			}
			characterList[0]->SetDir(0);
			characterList[0]->SetXY(200, 400);
			characterList[0]->SetCharacter();

			switch (this->game->selectCharacterID[1]) {
			case 0:
				characterList.push_back(new Woody(1, map[mapNowID]->GetMapID()));
				break;
			case 1:
				characterList.push_back(new Freeze(1, map[mapNowID]->GetMapID()));
				break;
			case 2:
				characterList.push_back(new Henry(1, map[mapNowID]->GetMapID()));
				break;
			default:
				characterList.push_back(new Freeze(1, map[mapNowID]->GetMapID()));
				break;
			}
			characterList[1]->SetXY(400, 401);
			characterList[1]->SetCharacter();

			SetAllCharacterPosition();

			GetCharacter = true;
			HealthPlayer1->loadSmallImg(this->game->selectCharacterID[0]);
			HealthPlayer2->loadSmallImg(this->game->selectCharacterID[1]);

			GenerationTime = clock();
		}
		CurrentTime = clock();
		TimePassed = (CurrentTime - GenerationTime);
		MapAniCount++;
		if (MapAniCount < 50) {
			showStatus = true;
		}
		else if (MapAniCount <= 100) {
			showStatus = false;
			if (MapAniCount >= 100) {
				MapAniCount = 0;
			}
		}

		map[mapNowID]->PrintMap(showStatus);
		SortedShow();
		characterList[1]->EnemyAiMode(theOthersPosition[0].first, theOthersPosition[0].second, CurrentTime);
		if (TimePassed < 8000 && map[mapNowID]->GetMapID() != HKC) {
			if (clearedTime % 2 == 0) {
				go.ShowBitmap();
			}
		}
		HealthPlayer1->OnShow(characterList[0]->HealthPoint, characterList[0]->InnerHealPoint, characterList[0]->Mana, characterList[0]->InnerMana);
		HealthPlayer2->OnShow(characterList[1]->HealthPoint, characterList[1]->InnerHealPoint, characterList[1]->Mana, characterList[1]->InnerMana);

		ResetGame();
	}

	CGameStateRun::~CGameStateRun() {
		delete HealthPlayer1, HealthPlayer2, go;
		vector<Character*>().swap(characterList);
		vector<Map*>().swap(map);
		vector<CMovingBitmap*>().swap(stageTitles);
	}
}