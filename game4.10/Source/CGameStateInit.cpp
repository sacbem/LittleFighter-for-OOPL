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
        startBtn = make_shared<StartBtn>(StartBtn());
        settingBtn = make_shared<SettingBtn>(SettingBtn());
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
        attackScreen.AddBitmap(IDB_BITMAP23,RGB(0,0,0));
        attackScreen.AddBitmap(IDB_BITMAP14, RGB(0,0,0));
        black.LoadBitmap(IDB_BITMAP24);
        startBtn->Load();
        settingBtn->Load();
		logo.LoadBitmap(IDB_BITMAP3);
        selectCharacterMenu.LoadBitmap(IDB_BITMAP13);
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		/*
         此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
        */

	}

    void CGameStateInit::OnBeginState(){
        keyCount = 0;
        cursorClickLift = 0;
        mouseEnable = false;
        selectEnter = false;
	}
    void CGameStateInit::ScreenClear() {
        black.SetTopLeft(0, 0);   //清除畫面用
        black.ShowBitmap();       //
    }
    void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point) {

		cursorXY[0] = point.x;
		cursorXY[1] = point.y;
        mouseEnable = true;
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
          mouseEnable = false;
          if (selectEnter) {
              switch (nChar) {
              case KEY_W:
                  ++keyCount;
                  break;
              case KEY_S:
                  ++keyCount;
                  break;
              case KEY_ENTER:
                  if ((keyCount % 2) == 0) {
                      selectEnter = true;
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

          }

     }

    void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point){
        if (!selectEnter) {
            if (point.x >= 545 * (0.81) + 20 && point.x <= 745 * (0.81) + 20) {
                if (point.y >= 260 * (0.94) && point.y <= 280 * (0.94)) {
                    if (nFlags == 1) {
                        //GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
                        selectEnter = true;
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
            ///
        }
    }
    void  CGameStateInit::SetAnimation() {
        for (int i = 0; i < 4; i++) {               //上排
            attackScreen.SetTopLeft(155 + 152 * i, 136);
            attackScreen.OnMove();
            attackScreen.OnShow();
        }
        for (int i = 0; i < 4; i++) {               //上排
            attackScreen.SetTopLeft(155 + 152 * i, 358);
            attackScreen.OnMove();
            attackScreen.OnShow();
        }
    }

    void CGameStateInit::OnShow(){
		/*
         貼上logo
        */

          logo.SetTopLeft(0, 0);
          logo.ShowBitmap();
          startBtn->OnShow();
          settingBtn->OnShow();
          if (!selectEnter) {
              if (mouseEnable) {
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
              selectCharacterMenu.SetTopLeft((SIZE_X - 704) / 2, (SIZE_Y-487)/2);
              selectCharacterMenu.ShowBitmap();
              SetAnimation();

              //GotoGameState(GAME_STATE_RUN);  // 切換至GAME_STATE_RUN
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

    }
}
