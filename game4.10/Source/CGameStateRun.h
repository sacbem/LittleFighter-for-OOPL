#include "SkillEffect.h"
#include "Character.h"
#include "HealthBar.h"
#include "FieldObject.h"
#include "Map.h"
#include <ctime>
namespace game_framework {
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame* g);
		~CGameStateRun();
		void OnBeginState();
		void OnInit();
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void SetAllCharacterPosition();
		void SetAbonormalStatus();
		void CalculateDamage(vector<pair<int, int>> theOthersPosition);
		void CharacterMapPosOffset();
		void SetCharacterSlide();
		void ResetGame();
		void SetStageTitle();
		void ClearStageTitle();
		friend class Freeze;

		int tables[2] = {-1, -1};
	protected:
		void OnMove();									
		void OnShow();		
		void SortedShow();
	private:
		void DetectSkillDamage(vector<pair<int, int>> theOthersPosition);
		bool GetCharacter = false;
		CMovingBitmap black , go;
		vector<CMovingBitmap*> stageTitles;
		vector<pair<int,int>> theOthersPosition;
		vector<Character*> characterList;
		vector<SkillEffect*> frozenPunchList; /// ©ñ¸m±¼¸¨ª«
		vector<int>statusTableAll;
		vector<int> characterSlidePriority; //walk 1000 1 run 1010 2  
		vector <Map*> map;
		HealthBar* HealthPlayer1;
		HealthBar* HealthPlayer2;
		//Generate Time
		time_t GenerationTime;
		time_t CurrentTime;
		boolean clearFlag;
		boolean flaG ,cheat;
		int clearedTime;
		int TimePassed;
		int MapAniCount = 0;
		int registSerialNumber;
		int mapNowID = 0;
		bool secrestSkillsTrigger;
	};
}
namespace skillTable {
	// Woody 
	constexpr int energyBlast = 0x00;
	constexpr int footKnife = 0x01;
	constexpr int demonFoot = 0x02;
	constexpr int tank = 0x03;
	constexpr int teleportation = 0x04;
	// Freeze
	constexpr int frozenWave = 0x10;
	constexpr int frozenPunch = 0x11;
	constexpr int frozenSword = 0x12;
	constexpr int frozenStorm = 0x13;
	// Henry 
	constexpr int airWave = 0x20;
	constexpr int pierceArrow = 0x21;
	constexpr int arrowRain = 0x22;
	constexpr int demonicSong = 0x23;

}
