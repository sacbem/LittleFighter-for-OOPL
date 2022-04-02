#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <typeinfo>
#include "CGameStateInit.h"
//#include "InitalPageMenu.h"

namespace game_framework {
	CGameStateInit::CGameStateInit(CGame* g): CGameState(g){
        startBtn = new StartBtn();
        settingBtn = new SettingBtn();
        selectCharacterMenu = new SelectCharacterMenu();
        photoSticker_1P = new PhotoSticker(0);
        photoSticker_2P = new PhotoSticker(1);
        photoSticker_seclecter = new Seclecter(0);
    }

	void CGameStateInit::OnInit(){
		/*
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		*/
		ShowInitProgress(0);	// 一開始的loading進度為0%
		/*
            開始載入資料
        */

        startBtn->Load();
        settingBtn->Load();
        countDown.AddBitmap(IDB_BITMAP25, RGB(0, 0, 0));
        for (int i = 4; i >=0 ; i--) {
            countDown.AddBitmap( 287- i , RGB(0, 0, 0));
        }
       
        attackScreen.AddBitmap(IDB_BITMAP23, RGB(0, 0, 0));
        attackScreen.AddBitmap(IDB_BITMAP14, RGB(0, 0, 0));
        black.LoadBitmap(IDB_BITMAP24);
		logo.LoadBitmap(IDB_BITMAP3);
        selectCharacterMenu->Load(IDB_BITMAP13);
        photoSticker_seclecter->Load(picStickers,picIDs,picNames);

		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		/*
         此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
        */

	}
    void CGameStateInit::OnBeginState(){
        keyCount = cursorClickLift = 0;;     
        loadMap = characterIsSeclected = 0;
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
        TRACE("posX: %d posY: %d\n", point.x, point.y);
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
                        //GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
                        SELECT_ENTER = true;
                        SELECTOR_ENABLE = true;
                    }
                }
            }
            if (point.x >= 525 * (0.81) + 20 && point.x <= 765 * (0.81) + 20) {
                if (point.y >= 300 * (0.94) && point.y <= 320 * (0.94)) {
                    if (nFlags == 1) {

                        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
                    }
                }
            }
        }
        else {

        }
    }
    void CGameStateInit::SetAnimation() {
        for (int i = 0; i < 4; i++) {               //上排
            attackScreen.SetTopLeft(155 + 152 * i, 136);
            attackScreen.OnShow();
        }
       
        for (int i = 0; i < 4; i++) {               //下排
            attackScreen.SetTopLeft(155 + 152 * i, 358);
            attackScreen.OnShow();
        }
        attackScreen.OnMove();
       
    }
    void CGameStateInit::SetCountdownAni() {
        for (int i = 2; i < 4; i++) {               //上排
            countDown.SetTopLeft(190 + 152 * i, 150);
            countDown.OnShow();
        }
        for (int i = 0; i < 4; i++) {               //下排
            countDown.SetTopLeft(190 + 152 * i, 372);
            countDown.OnShow();
        }
        countDown.OnMove();

    }
    void CGameStateInit::SetPhotoStickers() {
        if (SELECTOR_ENABLE) {
            int idGet = photoSticker_seclecter->GetCharacterID();
            switch (characterIsSeclected) {
            case 1:
                if (loadMap < characterIsSeclected) {
                    photoSticker_1P->Load(picStickers[idGet], picIDs[idGet],picNames[idGet]);
                    photoSticker_seclecter->SetXY(307, 136-20);
                    loadMap++;
                }
                photoSticker_1P->OnShow();
                break;
            case 2:
                if (loadMap < characterIsSeclected) {
                    photoSticker_2P->Load(picStickers[idGet], picIDs[idGet], picNames[idGet]);
                    loadMap++;
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
              if (MOUSE_ENABLE) {
                  if (cursorXY[0] >= 545*(0.81) + 20 && cursorXY[0] <= 745 * (0.81) + 20) {
                      if (cursorXY[1] >= 260 * (0.94) && cursorXY[1] <= 280 * (0.94)) {
                          startBtn->buttonTouch();
                          settingBtn->OnShow();
                      }
                  }
                  if (cursorXY[0] >= 525 * (0.81) + 20 && cursorXY[0] <= 765 * (0.81) + 20) {
                      if (cursorXY[1] >= 300 * (0.94) && cursorXY[1] <= 320 * (0.94)) {
                          settingBtn->buttonTouch();
                          startBtn->OnShow();
                      }
                  }
              }
              else {
                  switch (keyCount % 2) {
                  case 0:
                      startBtn->buttonTouch();
                      settingBtn->OnShow();
                      break;
                  case 1:
                      settingBtn->buttonTouch();
                      startBtn->OnShow();
                      break;
                  }
              }
          }
          else {

              ScreenClear();
              selectCharacterMenu->OnShow();

              if (!SELECTOR_ENABLE) {  //結束選角
                  SetCountdownAni();
                  
                  if(countDown.IsFinalBitmap())GotoGameState(GAME_STATE_RUN);
              }
              else { 
                  SetAnimation();
              }
              SetPhotoStickers();
          }

          
    
		/*
         Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
        */
	
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
        delete selectCharacterMenu ;
        delete photoSticker_1P ;
        delete photoSticker_2P ;
        delete photoSticker_seclecter ;
    }
}
