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
using namespace skillTable;
namespace game_framework {
	CGameStateRun::CGameStateRun(CGame* g): CGameState(g){
		characterList.reserve(2);
		theOthersPosition.reserve(2);
		//EnemyTest = new Character();
		HealthPlayer1 = new HealthBar();
		HealthPlayer2 = new HealthBar();
		maps = new Map(HKC);
		
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
	
		CleanCounter++;
		if (CleanCounter >= 10) {
			CleanCounter = 0;
			if (EnemyTest->GetHealth() <= 0) {
				EnemyTest->SetAlive(false);
			}
		}
		PlayerTest->OnMove();
		EnemyTest->OnMove();
		SetAllCharacterPosition();
		if (PlayerTest->HitEnemy(EnemyTest) && PlayerTest->isAttacking) {
			if (EnemyTest->HealthPoint > 0) {
				//int hitDirection = PlayerTest->GetDir();
				EnemyTest->SetKnock(true, PlayerTest->GetDir(), PlayerTest->AttackState);
				EnemyTest->isGettingDamage(PlayerTest->AttackPoint);
			}
		}
		maps->ResetCharactAccumulator(PlayerTest->GetDistance(), PlayerTest->GetDistance());
		//EnemyTest->OnMove();
		PlayerTest->DistanceAccumulatorReset();
		maps->ScenesCamera(PlayerTest->DistanceAccumulatorReset(),PlayerTest->isRunning,PlayerTest->GetDir(), PlayerTest->GetDistance());
	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		ShowInitProgress(50);
		Sleep(300);

		maps->Load(HKC);
		HealthPlayer1->init();
		HealthPlayer2->init();

		HealthPlayer1->OnLoad(0, 0);
		HealthPlayer2->OnLoad(400, 0);

	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
		PlayerTest->InputKeyDown(nChar, CurrentTime);
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){
		PlayerTest->InputKeyUp(nChar);
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
			for (auto i : u->hittedTable) { /// issue :可能不會改 !!!
				if (i.first == 1) {
					player1Damage += i.second;
				}
				else if (i.first == 2) {
					player2Damage += i.second;
				}
			}
		}
		
		characterList[0]->isGettingDamage(player1Damage);
		characterList[1]->isGettingDamage(player2Damage);
	}

	void CGameStateRun::OnShow(){
		boolean showStatus;
		
		//get character
		if (GetCharacter == false ){ // && EnemyTest->getCharacter == false) {
			PlayerTest = new Freeze();
			
			PlayerTest->SetXY(200, 200);
			PlayerTest->SetCharacter();

			EnemyTest = new Freeze();
			EnemyTest->SetXY(400,200);
			EnemyTest->SetCharacter();
			
			//EnemyTest->SetCharacter(buffer[1] - '0');
			SetAllCharacterPosition();

			GetCharacter = true;
			//load HealthBar small character
			HealthPlayer1->loadSmallImg(this->game->selectCharacterID[0]);
			HealthPlayer2->loadSmallImg(this->game->selectCharacterID[1]);

			GenerationTime = clock();
		}
		CurrentTime = clock();
		TimePassed = (CurrentTime - GenerationTime)/1000;
		//TRACE("TimePassed %d\n", TimePassed);
		showStatus = TimePassed % 2 == 0 ? true : false;
		maps->PrintMap(showStatus);
		PlayerTest->OnShow(theOthersPosition, CurrentTime);
		EnemyTest->OnShow(theOthersPosition, CurrentTime);
		HealthPlayer1->OnShow(PlayerTest->HealthPoint, PlayerTest->InnerHealPoint, PlayerTest->Mana, PlayerTest->InnerMana);
		HealthPlayer2->OnShow(EnemyTest->HealthPoint, EnemyTest->InnerHealPoint, EnemyTest->Mana, EnemyTest->InnerMana);
	
		
		//imgs[0][0]->ShowBitmap();
	}

	CGameStateRun::~CGameStateRun(){
		delete maps, HealthPlayer1, HealthPlayer2, PlayerTest, EnemyTest;

		for (auto& i : characterList) {
			delete i;
		}
	}
}