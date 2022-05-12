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
