#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameStateOver.h"
namespace game_framework {
	CGameStateOver::CGameStateOver(CGame* g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 300;
	}

	void CGameStateOver::OnInit()
	{
		ShowInitProgress(66);
		ShowInitProgress(100);
		EndGame.LoadBitmapA(".\\res\\GameOver.bmp");
		EndGame.SetTopLeft(0,0);
	}

	void CGameStateOver::OnShow()
	{
		EndGame.ShowBitmap();
	}
}