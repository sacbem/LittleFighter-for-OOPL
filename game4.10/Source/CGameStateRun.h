#include "Character.h"
#include "MapGenerator.h"
#include "HealthBar.h"
#include <ctime>
namespace game_framework {
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame* g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
        void MapSlide();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		//Player & other
		Character PlayerTest;
		//Character* EnemyTest;
        MapGenerator* maps;
		HealthBar* HealthPlayer1;
		//HealthBar* HealthPlayer2;
		int CleanCounter=0;
	};
}
