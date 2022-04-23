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

namespace game_framework {
	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g)
	{
		PlayerTest = Character();
		//EnemyTest = Character();
		HealthPlayer1 = new HealthBar();
		//HealthPlayer2 = new HealthBar();
        maps = new MapGenerator();
		//_CrtDumpMemoryLeaks();
	}

	void CGameStateRun::OnBeginState()
	{
		PlayerTest.SetXY(200, 200);
		//EnemyTest->SetXY(500, 200);
		//_CrtDumpMemoryLeaks();

	}
    void  CGameStateRun::MapSlide() {
        if (PlayerTest.isWalking) {
            //TRACE("--------------- %d -------------%d \n", PlayerTest.isRunning, PlayerTest.GetDistance());
            if (PlayerTest.GetDir()) {
                maps->ScenesCamera(true, 0);
            }
            else {
                maps->ScenesCamera(false, 0);
            }

        }
        else if (PlayerTest.GetDistance() > 50) {
          
            if (PlayerTest.GetDir()) {
                maps->ScenesCamera(true, 1);
            }
            else {
                maps->ScenesCamera(false, 1);
            }
            PlayerTest.SetAccumulator(PlayerTest.GetX1(), PlayerTest.GetY1());

        }
		//_CrtDumpMemoryLeaks();

    }
	void CGameStateRun::OnMove()						// 移動遊戲元素
	{
		CleanCounter++;
		if (CleanCounter >= 10) {
			CleanCounter = 0;
			/*
			if (EnemyTest->GetHealth() <= 0) {
				EnemyTest->SetAlive(false);
			}
			*/
		}

		PlayerTest.OnMove();
		//EnemyTest->OnMove();
        MapSlide();
		/*
		//x bound
		if (PlayerTest.GetX1() <= 0) {
			PlayerTest.SetXY(0, PlayerTest.GetY1());
		}
		else if (PlayerTest.GetX2()>=800) {
			PlayerTest.SetXY(800-(PlayerTest.GetX2()-PlayerTest.GetX1()), PlayerTest.GetY1());
		}
		//y bound
		if(PlayerTest.GetY1() <= 200) {
			PlayerTest.SetXY(PlayerTest.GetX1(), 200);
			
		}
		else if (PlayerTest.GetY2() >= 580) {
			PlayerTest.SetXY(PlayerTest.GetX1(),580- (PlayerTest.GetY2() - PlayerTest.GetY1()));
		}
		*/
		//x bound
		/*
		if (EnemyTest->GetX1() <= 0) {
			EnemyTest->SetXY(0, EnemyTest->GetY1());
		}
		else if (EnemyTest->GetX2() >= 800) {
			EnemyTest->SetXY(800 - (EnemyTest->GetX2() - EnemyTest->GetX1()), EnemyTest->GetY1());
		}
		//y bound
		if (EnemyTest->GetY1() <= 200) {
			if (EnemyTest->isJumpping==false) {
				EnemyTest->SetXY(EnemyTest->GetX1(), 200);
			}
		}
		else if (EnemyTest->GetY2() >= 580) {
			EnemyTest->SetXY(EnemyTest->GetX1(), 580 - (EnemyTest->GetY2() - EnemyTest->GetY1()));
		}
		if (PlayerTest.HitEnemy(EnemyTest) && PlayerTest.isAttacking) {
			if (EnemyTest->HealthPoint>0) {
				int hitDirection = PlayerTest.GetDir();
				EnemyTest->SetGettingHit(true, hitDirection);
				EnemyTest->HealthPoint -= PlayerTest.AttackPoint;
			}
		}
		*/

		
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));

		CString str;
		str.Format("%d", PlayerTest.GetDir());
		CString str2;
		str2.Format("%d , %d", PlayerTest.GetX1(), PlayerTest.GetY1());
		pDC->TextOut(120, 220, str);
		pDC->TextOut(120, 320, str2);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();

		//_CrtDumpMemoryLeaks();

	}

	void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
	{
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		//
		// 開始載入資料
		//

		//
		// 完成部分Loading動作，提高進度
		//
		ShowInitProgress(50);
		Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep							

		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//

        maps->Load(0);
		HealthPlayer1->init();
		//HealthPlayer2->init();
		HealthPlayer1->OnLoad(0, 0);
		//HealthPlayer2->OnLoad(400, 0);
		//_CrtDumpMemoryLeaks();

	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		PlayerTest.InputKeyDown(nChar);
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		PlayerTest.InputKeyUp(nChar);
	}

	void CGameStateRun::OnShow(){
		//get character
		if (PlayerTest.getCharacter == false ){ // && EnemyTest->getCharacter == false) {
			ifstream ifs;
			char buffer[2];
			ifs.open("CharacterSelected.txt");
			ifs.read(buffer, sizeof(buffer));
			ifs.close();
			PlayerTest.SetCharacter(buffer[0] - '0');
			//EnemyTest->SetCharacter(buffer[1] - '0');
			PlayerTest.getCharacter = true;
			//EnemyTest->getCharacter = true;
			//load HealthBar small character
			HealthPlayer1->loadSmallImg(buffer[0] - '0');
			//HealthPlayer2->loadSmallImg(buffer[1] - '0');
		}

        maps->PrintMap();
		PlayerTest.OnShow();
		//EnemyTest->OnShow();
		HealthPlayer1->OnShow(PlayerTest.HealthPoint);
		//HealthPlayer2->OnShow(EnemyTest->HealthPoint);
		//_CrtDumpMemoryLeaks();
	}
    CGameStateRun::~CGameStateRun(){
		delete maps, HealthPlayer1;//, HealthPlayer2;
    }
}