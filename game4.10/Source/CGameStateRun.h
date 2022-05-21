#include "SkillEffect.h"
#include "Character.h"
#include "HealthBar.h"
#include "Map.h"
#include <ctime>
#include "FieldObject.h"
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
		void CalculateDamage(vector<pair<int, int>> theOthersPosition);
		friend class Freeze;
	protected:
		void OnMove();									
		void OnShow();									
	private:
		void DetectSkillDamage(vector<pair<int, int>> theOthersPosition);
		bool GetCharacter = false;
		vector<pair<int,int>> theOthersPosition;
		vector<Character*> characterList;
		vector<Freeze*> testFreeze;
		//Player & other
		//Character *PlayerTest;
		//Character *EnemyTest;
		FieldObject* boxTest;
		Map* maps;
		HealthBar* HealthPlayer1;
		HealthBar* HealthPlayer2;
		int CleanCounter=0;
		//Generate Time
		time_t GenerationTime;
		time_t CurrentTime;
		int TimePassed;
		int MapAniCount = 0;
		int registSerialNumber;

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
