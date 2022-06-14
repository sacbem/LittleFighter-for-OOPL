#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <typeinfo>
#include "CGameStateInit.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

namespace game_framework {
	CGameStateInit::CGameStateInit(CGame* g): CGameState(g){
		startBtn = new StartBtn();
		settingBtn = new SettingBtn();
		aboutBtn = new AboutBtn();
		keyBtn = new KeyBtn();
		selectCharacterMenu = new SelectCharacterMenu();
		photoSticker_1P = new PhotoSticker(0);
		photoSticker_2P = new PhotoSticker(1);
		photoSticker_seclecter = new Seclecter(0);

		isKey = false;
		isAbout = false;
	}

	void CGameStateInit::OnInit(){
		ShowInitProgress(0);

		AboutInfo.LoadBitmapA(".\\res\\AboutPanel.bmp");
		KeyInfo.LoadBitmapA(".\\res\\KeyPanel.bmp");

		startBtn->Load();
		settingBtn->Load();
		aboutBtn->Load();
		keyBtn->Load();
		CAudio::Instance()->Load(0, "bgm\\main.wav");
	
		countDown.AddBitmap(BITMAP_COUNTDOWN_BACK, RGB(0, 0, 0));
		for (int i = 4; i >=0 ; i--) {
			countDown.AddBitmap( BITMAP_COUNTDOWN_5- i , RGB(0, 0, 0));
		}
	   
		attackScreen.AddBitmap(BITMAP_PRESSATTACK_0, RGB(0, 0, 0));
		attackScreen.AddBitmap(BITMAP_PRESSATTACK_1, RGB(0, 0, 0));
		black.LoadBitmap(BITMAP_BLACKSCREEN);
		logo.LoadBitmap(IDB_BITMAP3);
		selectCharacterMenu->Load(BITMAP_SELECTMENU);
		photoSticker_seclecter->Load(picStickers,picIDs,picNames);
		CAudio::Instance()->Play(0, true);
		Sleep(300);				

	}
	void CGameStateInit::OnBeginState(){
		keyCount = cursorClickLift = 0;;     
		loadedImg = characterIsSeclected = enterCounter = 0;
		//countDown.SetDelayCount(50);
		MOUSE_ENABLE = SELECT_ENTER = SELECTOR_ENABLE = false;
		for (int i = 0; i < 3;i++) {
			characterID[i] = 0;
		}
		
	}
	void CGameStateInit::ScreenClear() {
		black.SetTopLeft(0, 0);   //清除畫面用
		black.ShowBitmap();       //
	}
	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point) {

		cursorXY[0] = point.x;
		cursorXY[1] = point.y;
		MOUSE_ENABLE = true;
	   
		if (cursorXY[0] >= 545 * (0.81) + 20 && cursorXY[0] <= 745 * (0.81) + 20) {
			if (cursorXY[1] >= 260 * (0.94) && cursorXY[1] <= 280 * (0.94)) {
			keyCount = 0;                   //回歸正常計數
			}
		}
		if (cursorXY[0] >= 525 * (0.81) + 20 && cursorXY[0] <= 765 * (0.81) + 20) {
			if (cursorXY[1] >= 300 * (0.94) && cursorXY[1] <= 320 * (0.94)) {
			keyCount = 1;                   //回歸正常計數
			}
		}
		}
	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){
		  const char KEY_ESC = 27;
		  const char KEY_ENTER = 13;
		  const char KEY_W = 87;
		  const char KEY_A = 65;
		  const char KEY_S = 83;
		  const char KEY_D = 68;
		  if (nChar == KEY_ESC) {
			  isAbout = false;
			  isKey = false;
		  }

		  MOUSE_ENABLE = false;
		  if (!SELECT_ENTER) {
			  switch (nChar) {
			  case KEY_W:
				  ++keyCount;
				  break;
			  case KEY_S:
				  ++keyCount;
				  break;
			  case KEY_ENTER:
				  if ((keyCount % 2) == 0) {
					  SELECT_ENTER = true;
					  SELECTOR_ENABLE = true;
				  }
				  if ((keyCount % 2) == 1) {
					  PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
				  }
				  break;
			  default:
				  break;
			  }
		  }
		else {
			if (SELECT_ENTER) { 
				switch (nChar) {
				    case KEY_W:
						characterID[characterIsSeclected]++;
						if (characterID[characterIsSeclected] > 2) {
							characterID[characterIsSeclected] = 0;
						}
						photoSticker_seclecter->IsSeclected(characterID[characterIsSeclected]);
					break;
					case KEY_S:
						characterID[characterIsSeclected]--;
						if (characterID[characterIsSeclected] < 0) {
							characterID[characterIsSeclected] = 2;
						}
						photoSticker_seclecter->IsSeclected(characterID[characterIsSeclected]);
					break;
					case KEY_ENTER:
						if (SELECTOR_ENABLE) {
							characterIsSeclected++;
							if (characterIsSeclected == 1) {
								int idGet = photoSticker_seclecter->GetCharacterID();
								photoSticker_1P->Load(picStickers[idGet], picIDs[idGet], picNames[idGet]);
								photoSticker_seclecter->SetXY(336, 195);
								photoSticker_seclecter->SetSeclectedID(0);
							}
						}
					break;
				}
			}
		}
	}
	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point){
		if (!SELECT_ENTER) {
			if (point.x >= 545 * (0.81) + 20 && point.x <= 745 * (0.81) + 20) {
				if (point.y >= 260 * (0.94) && point.y <= 280 * (0.94)) {
					if (nFlags == 1) {
						SELECT_ENTER = true;
						SELECTOR_ENABLE = true;
						isAbout = false;
						isKey = false;
					}
				}
			}
			if (point.x >= 525 * (0.81) + 20 && point.x <= 765 * (0.81) + 20) {
				if (point.y >= 300 * (0.94) && point.y <= 320 * (0.94)) {
					if (nFlags == 1) {
						isAbout = false;
						isKey = false;
						PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
					}
				}
			}
			if (point.x >= 545 * (0.81) + 20 && point.x <= 745 * (0.81) + 20) {
				if (point.y >= 340 * (0.94) && point.y <= 360 * (0.94)) {
					if (nFlags == 1) {
						isAbout = true;
						isKey = false;
					}
				}
			}
			if (point.x >= 525 * (0.81) + 20 && point.x <= 765 * (0.81) + 20) {
				if (point.y >= 385 * (0.94) && point.y <= 405 * (0.94)) {
					if (nFlags == 1) {
						isAbout = false;
						isKey = true;
					}
				}
			}
		}
		else {

		}
	}
	void CGameStateInit::SetAnimation() {
		for (int i = 0; i < 3; i++) {               
			attackScreen.SetTopLeft(165 + 169 * i, 210);
			attackScreen.OnShow();
		}
		attackScreen.OnMove();
	   
	}
	void CGameStateInit::SetCountdownAni() {
		for (int i = 2; i < 3; i++) {               
			countDown.SetTopLeft(200 + 169 * i, 220);
			countDown.OnShow();
		}
		countDown.OnMove();
	}
	void CGameStateInit::SetPhotoStickers() {
		if (SELECTOR_ENABLE) {
			int idGet = photoSticker_seclecter->GetCharacterID();
			switch (characterIsSeclected) {
			case 1:
				idGet = photoSticker_seclecter->GetCharacterID();
				if (loadedImg < characterIsSeclected) {
					loadedImg++;
				}
				photoSticker_1P->OnShow();
				break;
			case 2:
				idGet = photoSticker_seclecter->GetCharacterID();
				if (loadedImg < characterIsSeclected) {
					photoSticker_2P->Load(picStickers[idGet], picIDs[idGet], picNames[idGet]);
					loadedImg++;
				}
				photoSticker_2P->OnShow();
				SELECTOR_ENABLE = false;
				break;
			}
			photoSticker_seclecter->OnShow();
		}
		else {
			photoSticker_1P->OnShow();
			photoSticker_2P->OnShow();
		}
	}
  
	void CGameStateInit::OnShow() {
		logo.SetTopLeft(0, 0);
		logo.ShowBitmap();

		if (!SELECT_ENTER) {
		startBtn->OnShow();
		settingBtn->OnShow();
		aboutBtn->OnShow();
		keyBtn->OnShow();

		if (isAbout) {
			AboutInfo.SetTopLeft(0, 0);
			AboutInfo.ShowBitmap();
		}
		if (isKey) {
			KeyInfo.SetTopLeft(0,0);
			KeyInfo.ShowBitmap();
		}

		if (MOUSE_ENABLE) {
			if (cursorXY[0] >= 545*(0.81) + 20 && cursorXY[0] <= 745 * (0.81) + 20) {
				if (cursorXY[1] >= 260 * (0.94) && cursorXY[1] <= 280 * (0.94)) {
					startBtn->buttonTouch();
					settingBtn->OnShow();
					aboutBtn->OnShow();
					keyBtn->OnShow();
				}
			}
			if (cursorXY[0] >= 525 * (0.81) + 20 && cursorXY[0] <= 765 * (0.81) + 20) {
				if (cursorXY[1] >= 300 * (0.94) && cursorXY[1] <= 320 * (0.94)) {
					settingBtn->buttonTouch();
					startBtn->OnShow();
					aboutBtn->OnShow();
					keyBtn->OnShow();
				}
			}
			if (cursorXY[0] >= 525 * (0.81) + 20 && cursorXY[0] <= 765 * (0.81) + 20) {
				if (cursorXY[1] >= 340 * (0.94) && cursorXY[1] <= 360 * (0.94)) {
					settingBtn->OnShow();
					startBtn->OnShow();
					aboutBtn->buttonTouch();
					keyBtn->OnShow();
				}
			}
			if (cursorXY[0] >= 525 * (0.81) + 20 && cursorXY[0] <= 765 * (0.81) + 20) {
				if (cursorXY[1] >= 385 * (0.94) && cursorXY[1] <= 405 * (0.94)) {
					settingBtn->OnShow();
					startBtn->OnShow();
					aboutBtn->OnShow();
					keyBtn->buttonTouch();
				}
			}
		}
			else {
				switch (keyCount % 2) {
				case 0:
					startBtn->buttonTouch();
					settingBtn->OnShow();
					aboutBtn->OnShow();
					keyBtn->OnShow();
				break;
				case 1:
					settingBtn->buttonTouch();
					startBtn->OnShow();
					aboutBtn->OnShow();
					keyBtn->OnShow();
				break;
				case 2:
					settingBtn->OnShow();
					startBtn->OnShow();
					aboutBtn->buttonTouch();
					keyBtn->OnShow();
					break;
				case 3:
					settingBtn->OnShow();
					startBtn->OnShow();
					aboutBtn->OnShow();
					keyBtn->buttonTouch();
					break;
				}
			}
		}
		else {
			ScreenClear();
			selectCharacterMenu->OnShow();
			if (!SELECTOR_ENABLE) {  //結束選角
				SetCountdownAni();
				if (countDown.IsFinalBitmap()){
					this->game->selectCharacterID[0] = characterID[0];
					this->game->selectCharacterID[1] = characterID[1];
					CAudio::Instance()->Stop(0);
					GotoGameState(GAME_STATE_RUN);
				}
			  }
			  else { 
				  SetAnimation();
			  }
			  SetPhotoStickers();
		  }         
	
		 CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		 CFont f, * fp;
		 f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		 fp = pDC->SelectObject(&f);					// 選用 font f
		 pDC->SetBkColor(RGB(0, 0, 0));
		 pDC->SetTextColor(RGB(255, 255, 0));

		 pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		 CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}

	CGameStateInit::~CGameStateInit(){
		delete startBtn;
		delete settingBtn;
		delete aboutBtn;
		delete keyBtn;
		delete selectCharacterMenu ;
		delete photoSticker_1P ;
		delete photoSticker_2P ;
		delete photoSticker_seclecter ;
	}
}
