#include <vector>
namespace game_framework {
	class HealthBar{
	public:
		HealthBar();
		~HealthBar();
		void GetHealth(int n);
		void SetXY(int X, int Y);
		void OnShow();
		void OnLoad();
	protected:
		vector<int> posistion_XY;
		CMovingBitmap img;
		int life;
	};
}