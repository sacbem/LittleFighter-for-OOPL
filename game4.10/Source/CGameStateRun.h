#include "Character.h"
#include "HealthBar.h"
#include "SkillEffect.h"
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
		//void MapSlide();
		vector<vector<int>> charactersPosition;
	protected:
		void OnMove();									
		void OnShow();									
	private:
		bool GetCharacter = false;
		vector<Character*> CharacterList;
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
