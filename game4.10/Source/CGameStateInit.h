#include "InitalPageMenu.h"
#include <memory>
namespace game_framework {
	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame* g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
        void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作
        void ScreenClear();
        void SetAnimation();
       // void LoadphotoSticker();
        ~CGameStateInit();
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo, selectCharacterMenu,black;	// csie的logo
        shared_ptr<StartBtn> startBtn;
        shared_ptr<SettingBtn> settingBtn;
        vector<int> bitmap;
        CAnimation attackScreen;
        int keyCount;
        int cursorXY[2];
        int cursorClickLift;
        boolean mouseEnable;
        boolean selectEnter;
	};
}
