#include <vector>
namespace game_framework {
	class HealthBar {
	public:
		HealthBar();
		~HealthBar();
		void init();
		void OnShow(int hp, int InnerHp, int mana, int InnerMana);
		void OnLoad(int X, int Y);
		void loadSmallImg(int id);
	protected:
		vector<int> posistion_XY;
		CMovingBitmap img;
		CMovingBitmap imgCharacter;
		
		CMovingBitmap red;
		CMovingBitmap innerRed;
		vector<CMovingBitmap*> imgHealth;
		vector<CMovingBitmap*> imgInnerHealth;
		
		CMovingBitmap blue;
		CMovingBitmap innerBlue;
		vector<CMovingBitmap*> imgMana;
		vector<CMovingBitmap*> imgInnerMana;
	};
}