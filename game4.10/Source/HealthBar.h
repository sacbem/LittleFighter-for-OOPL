#include <vector>
namespace game_framework {
	class HealthBar{
	public:
		HealthBar();
		~HealthBar();
		void init();
		void OnShow(int hp);
		void OnLoad(int X, int Y);
		void loadSmallImg(int id);
	protected:
		vector<int> posistion_XY;
		CMovingBitmap img;
		CMovingBitmap red;
		CMovingBitmap imgCharacter;
		vector<CMovingBitmap*> imgHealth;
	};
}