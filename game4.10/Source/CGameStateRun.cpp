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
#define Forest 100
namespace game_framework {
	CGameStateRun::CGameStateRun(CGame* g): CGameState(g){
		PlayerTest = new Character();
		//EnemyTest = Character();
		HealthPlayer1 = new HealthBar();
		//HealthPlayer2 = new HealthBar();
        maps = new Map(Forest);
		//_CrtDumpMemoryLeaks();
	}

	void CGameStateRun::OnBeginState(){
		PlayerTest->SetXY(200, 200);
		//EnemyTest->SetXY(500, 200);
		//_CrtDumpMemoryLeaks();
	}
	void CGameStateRun::OnMove(){						// ���ʹC������
		CleanCounter++;
		if (CleanCounter >= 10) {
			CleanCounter = 0;
			/*
			if (EnemyTest->GetHealth() <= 0) {
				EnemyTest->SetAlive(false);
			}
			*/
		}

		PlayerTest->OnMove();
		//EnemyTest->OnMove();

		
		/*
		CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160����16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		CString str;
		str.Format("%d", PlayerTest->GetDir());
		CString str2;
		str2.Format("%d , %d", PlayerTest->GetX1(), PlayerTest->GetY1());
		pDC->TextOut(120, 220, str);
		pDC->TextOut(120, 320, str2);
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();

		//_CrtDumpMemoryLeaks();
		*/
		
		
		maps->ResetCharactAccumulator(PlayerTest->GetDistance(), PlayerTest->GetDistance());
		maps->ScenesCamera(PlayerTest->isRunning, PlayerTest->GetDir(), PlayerTest->GetDistance());
	}

	void CGameStateRun::OnInit(){
		ShowInitProgress(33);	
	
		ShowInitProgress(50);
		Sleep(300);

        maps->Load(Forest);
		HealthPlayer1->init();
		//HealthPlayer2->init();
		HealthPlayer1->OnLoad(0, 0);
		//HealthPlayer2->OnLoad(400, 0);
		//_CrtDumpMemoryLeaks();

	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		PlayerTest->InputKeyDown(nChar);
	}
	//int GetScenesPos(Map& map, const string type) {
	//	return type == "X" ? map.gameScenesPos_X : map.gameScenesPos_Y;
	//}
	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){
		PlayerTest->InputKeyUp(nChar);
	}

	void CGameStateRun::OnShow(){
		
		//get character
		if (PlayerTest->getCharacter == false ){ // && EnemyTest->getCharacter == false) {
			ifstream ifs;
			char buffer[2];
			ifs.open("CharacterSelected.txt");
			ifs.read(buffer, sizeof(buffer));
			ifs.close();
			PlayerTest->SetCharacter(buffer[0] - '0');
			//EnemyTest->SetCharacter(buffer[1] - '0');
			PlayerTest->getCharacter = true;
			//EnemyTest->getCharacter = true;
			//load HealthBar small character
			HealthPlayer1->loadSmallImg(buffer[0] - '0');
			//HealthPlayer2->loadSmallImg(buffer[1] - '0');
		}

        maps->PrintMap();
		PlayerTest->OnShow();
		
		HealthPlayer1->OnShow(PlayerTest->HealthPoint);
		//HealthPlayer2->OnShow(EnemyTest->HealthPoint);
		//_CrtDumpMemoryLeaks();
	}
    CGameStateRun::~CGameStateRun(){
		delete maps, HealthPlayer1;//, HealthPlayer2;
    }
}