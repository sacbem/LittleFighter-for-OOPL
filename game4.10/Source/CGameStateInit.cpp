#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameStateInit.h"
//#include "InitalPageMenu.h"

namespace game_framework {
	CGameStateInit::CGameStateInit(CGame* g): CGameState(g){
        settingBtn = new SettingBtn();
        startBtn = new StartBtn();
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
		logo.LoadBitmap(IDB_BITMAP3);
		Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		/*
         此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
        */

	}

	void CGameStateInit::OnBeginState(){
        keyCount = 0;
        cursorClickLift = 0;
	}

    	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point) {

		cursorXY[0] = point.x;
		cursorXY[1] = point.y;
		if (cursorXY[0] >= 545 && cursorXY[0] <= 745) {
		    if (cursorXY[1] >= 260 && cursorXY[1] <= 280) {
			keyCount = 0;                   //回歸正常計數
		    }
		}
		if (cursorXY[0] >= 525 && cursorXY[0] <= 765) {
		    if (cursorXY[1] >= 300 && cursorXY[1] <= 320) {
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
          switch (nChar){
               case KEY_W:
                    ++keyCount;  
               break;
               case KEY_S:
               ++keyCount;
               break;
               case KEY_ENTER:
                    if ((keyCount % 2) == 0) {
                        GotoGameState(GAME_STATE_RUN);  // 切換至GAME_STATE_RUN
                    }
                    if ((keyCount % 2) == 1) {
                        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
                    }
               break;
               default:
                    break;
          }
     }

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point){

     if (point.x >= 545 && point.x <= 745) {
          if (point.y >= 260 && point.y <= 280) {
               if (nFlags == 1) {
                    GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
               } 
          }
     }
     if (point.x >= 525 && point.x <= 765) {
          if (point.y >= 300 && point.y <= 320) {
                    if (nFlags == 1) {
                         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
                    }
               }
          }
     }


     void CGameStateInit::OnShow()
	{
		/*
         貼上logo
        */

          logo.SetTopLeft(0, 0);
          logo.ShowBitmap();
          startBtn->OnShow();
          settingBtn->OnShow();
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
          if (cursorXY[0]>= 545 && cursorXY[0] <= 745) {
               if (cursorXY[1] >= 260 && cursorXY[1] <= 280) {
                    startBtn->buttonTouch();
                    settingBtn->OnShow();
               }
        }
        if (cursorXY[0] >= 525 && cursorXY[0] <= 765) {
             if (cursorXY[1] >= 300 && cursorXY[1] <= 320) {
               settingBtn->buttonTouch();
               startBtn->OnShow();
          }
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
    }
}
