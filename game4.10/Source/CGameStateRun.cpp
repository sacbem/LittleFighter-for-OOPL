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
using namespace std;
#define  _CRTDBG_MAP_ALLOC
#include  < stdlib.h >
#include  < crtdbg.h >
#define Forest 0
#define HKC 1
#define BC 2
using namespace skillTable;
namespace game_framework {
	CGameStateRun::CGameStateRun(CGame* g): CGameState(g){
		characterList.reserve(2);
		theOthersPosition.reserve(2);
		//characterList[1] = new Character();
		HealthPlayer1 = new HealthBar();
		HealthPlayer2 = new HealthBar();
		maps = new Map(BC);
		
		//GenerationTime = clock();

	}

	void CGameStateRun::OnBeginState()
	{
		//_CrtDumpMemoryLeaks();
		for (int i = 0; i < 2; i++) {
			theOthersPosition.push_back(pair<int,int>(0,0));
		}
		TimePassed = 0;
	}
   
	void CGameStateRun::OnMove()	{					// 移動遊戲元素
		//boxTest->OnMove();

		CleanCounter++;
		if (CleanCounter >= 10) {
			CleanCounter = 0;
			if (characterList[1]->GetHealth() <= 0) {
				characterList[1]->SetAlive(false);
			}
		}
		characterList[0]->OnMove();
		characterList[1]->OnMove();
		SetAllCharacterPosition();
		if (characterList[0]->HitEnemy(characterList[1]) && characterList[0]->isAttacking) {
			if (characterList[1]->HealthPoint > 0) {
				//int hitDirection = characterList[0]->GetDir();
				characterList[1]->SetKnock(true, characterList[0]->GetDir(), characterList[0]->AttackState);
				characterList[1]->isGettingDamage(characterList[0]->AttackPoint);
			}
		}
		maps->ResetCharactAccumulator(characterList[0]->GetDistance(), characterList[0]->GetDistance());
		//characterList[1]->OnMove();
		characterList[0]->DistanceAccumulatorReset();
	
		maps->ScenesCamera(characterList[0]->DistanceAccumulatorReset(),characterList[0]->isRunning,characterList[0]->GetDir(), characterList[0]->GetDistance());

		CalculateDamage(theOthersPosition);

		for (auto i : characterList[0]->hittedTable) {
			//TRACE("hitter table %d %d\n", i.first, i.second);
		}
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		ShowInitProgress(50);
		Sleep(300);

		maps->Load();
		HealthPlayer1->init();
		HealthPlayer2->init();

		HealthPlayer1->OnLoad(0, 0);
		HealthPlayer2->OnLoad(400, 0);

	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
		characterList[0]->InputKeyDown(nChar, CurrentTime);
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){
		characterList[0]->InputKeyUp(nChar);
	}
	
	void CGameStateRun::SetAllCharacterPosition() {
		for (int i = 0; i < characterList.size(); i++) {
			theOthersPosition[i].first = characterList[i]->GetX1();
			theOthersPosition[i].second = characterList[i]->GetY1();
		}
	}
	void  CGameStateRun::CalculateDamage(vector<pair<int, int>> theOthersPosition) {
		int player1Damage =0, player2Damage = 0;
		for (int i = 0; i < 2; i++) {
			if (this->game->selectCharacterID[i] == 0) {
				static_cast<Freeze*>(characterList[i])->DetectSkillDamage(theOthersPosition);
			}
			else if (this->game->selectCharacterID[i] == 1) {
				static_cast<Freeze*>(characterList[i])->DetectSkillDamage(theOthersPosition);
			}
			else if (this->game->selectCharacterID[i] == 2) {
				static_cast<Freeze*>(characterList[i])->DetectSkillDamage(theOthersPosition);
			}
		}

		for (auto& u : characterList) {
			for (auto &i : u->hittedTable) { /// issue :可能不會改 !!!
				if (i.first == 1) {
					//player1Damage += i.second;
					//TRACE("dama %d\n", i.second);
					characterList[1]->isGettingDamage(i.second);
				}
				else if (i.first == 2) {
					//player2Damage += i.second;
					characterList[0]->isGettingDamage(i.second);
				}
			}
		}
		//characterList[1]->isGettingDamage(player2Damage);
		boxTest->OnMove();
	}

	void CGameStateRun::OnShow(){
		boolean showStatus;
		//get character
		if (GetCharacter == false ){ // && characterList[1]->getCharacter == false) {
			boxTest = new FieldObject(0);

			switch (this->game->selectCharacterID[0])
			{
			case 0:
				characterList.push_back(new Woody(0));
				registSerialNumber=0;
				break;
			case 1:
				characterList.push_back(new Freeze(0));
				registSerialNumber = 1;
				break;
			case 2:
				characterList.push_back(new Henry(0));
				registSerialNumber = 2;
				break;
			default:
				characterList.push_back(new Freeze(0));
				registSerialNumber = 1;

				break;
			}
			characterList[0]->SetXY(200, 500);
			characterList[0]->SetCharacter();

			switch (this->game->selectCharacterID[1])
			{
			case 0:
				characterList.push_back(new Woody(registSerialNumber == 0 ? 0 : 2));
				break;
			case 1:
				characterList.push_back(new Freeze(registSerialNumber == 0 ? 0 : 2));
				break;
			case 2:
				characterList.push_back(new Henry(registSerialNumber == 0 ? 0 : 2));
				break;
			default:
				characterList.push_back(new Freeze(registSerialNumber == 0 ? 0 : 2));
				break;
			}
			characterList[1]->SetXY(400, 500);
			characterList[1]->SetCharacter();
			
			//characterList[1]->SetCharacter(buffer[1] - '0');
			SetAllCharacterPosition();
			TRACE("Pos f %d\n", theOthersPosition[1].first);
			TRACE("Pos s %d\n", theOthersPosition[1].second);

			GetCharacter = true;
			//load HealthBar small character
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
		//TRACE("MapAniCount %d\n", MapAniCount);
		//showStatus = MapAniCount % 2 == 0 ? true : false;
		maps->PrintMap(showStatus);
		characterList[0]->OnShow(theOthersPosition, CurrentTime);
		characterList[1]->OnShow(theOthersPosition, CurrentTime);
		HealthPlayer1->OnShow(characterList[0]->HealthPoint, characterList[0]->InnerHealPoint, characterList[0]->Mana, characterList[0]->InnerMana);
		HealthPlayer2->OnShow(characterList[1]->HealthPoint, characterList[1]->InnerHealPoint, characterList[1]->Mana, characterList[1]->InnerMana);
	
		
		//imgs[0][0]->ShowBitmap();
		boxTest->ShowAnimation();
	}

	CGameStateRun::~CGameStateRun(){
		delete maps, HealthPlayer1, HealthPlayer2;
		//delete boxTest;

		for (auto& i : characterList) {
			delete i;
		}
	}
}