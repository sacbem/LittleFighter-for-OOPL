#include "InitalPageMenu.h"
#include "SelCharacterConfig.h"
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
        void SetCountdownAni();
        void SetPhotoStickers();
        ~CGameStateInit();
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
        /*
        //shared_ptr<SettingBtn> settingBtn;
        //shared_ptr<SelectCharacterMenu> selectCharacterMenu;
        //shared_ptr<Seclecter> photoSticker_seclecter;
        //shared_ptr<PhotoSticker>photoSticker_1P, photoSticker_2P;
        //shared_ptr<StartBtn> startBtn;
        */
		CMovingBitmap logo,black;	// csie的logo
        CAnimation attackScreen,countDown; //需改名 還沒選角的動畫 
        StartBtn * startBtn;
        SettingBtn * settingBtn;
        SelectCharacterMenu* selectCharacterMenu;
        PhotoSticker *photoSticker_1P, *photoSticker_2P;
        Seclecter* photoSticker_seclecter;
        vector<int> bitmap;
        vector<int> picStickers{ 188,189,190 }, picIDs{ 292,293,294 }, picNames{295,296,297};
        int keyCount;
        int cursorXY[2];
        int cursorClickLift;
        int characterID[2];
        int characterIsSeclected ;
        int loadMap;
        boolean MOUSE_ENABLE,SELECT_ENTER,SELECTOR_ENABLE;
 
        
	};
}
