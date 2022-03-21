#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameStateRun.h"

namespace game_framework {
	CGameStateRun::CGameStateRun(CGame* g)
		: CGameState(g)
	{
		PlayerTest = new Character();
	}

	CGameStateRun::~CGameStateRun()
	{
		delete PlayerTest;
	}

	void CGameStateRun::OnBeginState()
	{
		PlayerTest->Initialize();
	}

	void CGameStateRun::OnMove()						// 移動遊戲元素
	{
		PlayerTest->OnMove();
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

		PlayerTest->LoadBitmap();
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_SPACE = 0x20; // keyboard SPACE
		//if (nChar == KEY_LEFT)
			
		//if (nChar == KEY_RIGHT)
			//sister.SetMovingRight(true);
		// if (nChar == KEY_UP)
			// sister.SetJumpimg(true);
		if (nChar == KEY_LEFT) {
			PlayerTest->SetMovingLeft(true);
			PlayerTest->SetRunning(true);
		}
		if (nChar == KEY_RIGHT) {
			PlayerTest->SetMovingRight(true);
			PlayerTest->SetRunning(true);
		}
		if (nChar == KEY_UP) {
			PlayerTest->SetMovingUp(true);
			PlayerTest->SetRunning(true);
		}
		if (nChar == KEY_DOWN) {
			PlayerTest->SetMovingDown(true);
			PlayerTest->SetRunning(true);
		}
		if (nChar == KEY_SPACE)
			PlayerTest->SetAttack(true);
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		const char KEY_SPACE = 0x20; // keyboard SPACE
		//if (nChar == KEY_LEFT)
			//sister.SetMovingLeft(false);
		//if (nChar == KEY_RIGHT)
			//sister.SetMovingRight(false);

		if (nChar == KEY_LEFT) {
			PlayerTest->SetMovingLeft(false);
			PlayerTest->SetRunning(false);
		}
		if (nChar == KEY_RIGHT) {
			PlayerTest->SetMovingRight(false);
			PlayerTest->SetRunning(false);
		}
		if (nChar == KEY_UP) {
			PlayerTest->SetMovingUp(false);
			PlayerTest->SetRunning(false);
		}
		if (nChar == KEY_DOWN) {
			PlayerTest->SetMovingDown(false);
			PlayerTest->SetRunning(false);
		}
		if (nChar == KEY_SPACE)
			PlayerTest->SetAttack(false);
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnShow()
	{
		//map.OnShow(); // 顯示地圖
		//sister.OnShow();
		PlayerTest->OnShow();
	}
}