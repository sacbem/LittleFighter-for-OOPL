#include <vector>
namespace game_framework {
	class Character
	{
	public:
		Character();
		~Character();
		int  GetX1();					// Chracter左上角 x 座標
		int  GetY1();					// Chracter左上角 y 座標
		int  GetX2();					// Chracter右下角 x 座標
		int  GetY2();					// Chracter右下角 y 座標
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetRunning(bool flag);
		void SetJump(bool flag);
		void SetAttack(bool flag);
		void SetDefense(bool flag);
		void SetXY(int X, int Y);

	protected:
		CAnimation Animation;
		CAnimation Walking;
		CAnimation Attacking;
		int xPos, yPos;
		//judge
		//basic movement
		bool isRunning;
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isJumpping;
		//Attack
		bool isAttacking;
		bool isDefending;
	};
}