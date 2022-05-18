#include "SkillEffect.h"
#include "Character.h"
#include "HealthBar.h"
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
		//void MapSlide();
		
	protected:
		void OnMove();									
		void OnShow();									
	private:
		void DetectSkillDamage();
		bool GetCharacter = false;
		vector<pair<int,int>> theOthersPosition;
		vector<Character*> characterList;
		//Player & other
		Character *PlayerTest;
		Character *EnemyTest;
		Map* maps;
		HealthBar* HealthPlayer1;
		HealthBar* HealthPlayer2;
		int CleanCounter=0;
		//Generate Time
		time_t GenerationTime;
		time_t CurrentTime;
		int TimePassed;

	};
}
namespace skillTable {
	// Freeze
	constexpr int frozenWave = 0x00;
	constexpr int frozenPunch = 0x01;
	constexpr int frozenSword = 0x02;
	constexpr int frozenStorm = 0x03;
	// Henry 
	constexpr int airWave = 0x10;
	constexpr int pierceArrow = 0x11;
	constexpr int arrowRain = 0x12;
	constexpr int demonicSong = 0x13;
	// Woody 
	constexpr int energyBlast = 0x20;
	constexpr int footKnife = 0x21;
	constexpr int demonFoot = 0x22;
	constexpr int tank = 0x23;
	constexpr int teleportation = 0x24;

}
