namespace game_framework {
	class Enemy
	{
	public:
		Enemy();
		~Enemy();
		bool GetAlive();
		int  GetX1();					// Chracter左上角 x 座標
		int  GetY1();					// Chracter左上角 y 座標
		int  GetX2();					// Chracter右下角 x 座標
		int  GetY2();					// Chracter右下角 y 座標
		int	 GetDir();
		int	 GetHealth();
		void Initialize();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetWalking(bool flag);
		void SetJump(bool flag);
		void SetRunning(bool flag);
		void SetAttack(bool flag);
		void SetDefense(bool flag);
		void SetGettingHit(bool flag, int Dir);
		void SetGettingUp(bool flag);
		void SetAlive(bool flag);
		void SetXY(int X, int Y);

		//basic informtion
		int HealthPoint;
		int AttackPoint;
		int DefencePoint;
		bool isAlive;
		bool isGettingHit; // 0 = not hit 1=hit by right 2=hit by left
		bool isGettingUp;
		
		bool isJumpping;
		//Running
		bool isRunning;
		//Attack
		bool isAttacking;
		//Defend
		bool isDefending;

	protected:
		CAnimation Animation;		// normal state
		CAnimation AnimationReverse;// normal state reverse
		CAnimation Walking;
		CAnimation WalkingReverse;
		CAnimation Attacking;
		CAnimation AttackingReverse;
		CAnimation Jump;
		CAnimation JumpReverse;
		CAnimation Running;
		CAnimation RunningReverse;		
		CAnimation Knock;
		CAnimation KnockReverse;
		CAnimation KnockBack;
		CAnimation KnockBackReverse;
		CAnimation Getup;
		CAnimation GetupReverse;
		CAnimation GetupBack;
		CAnimation GetupBackReverse;

		void ShowNormal(int Dir);
		void ShowWalking(int Dir);
		void ShowAttacking(int Dir);
		void ShowJump(int Dir);
		void ShowRun(int Dir);
		void ShowGettingUP(int Dir);
		void ShowKnock(int Dir, int HitDir);

		int xPos, yPos;
		//judge
		//direction
		int direction;				// 0=Left 1=Right
		int hitDirection;
		//basic movement
		bool isWalking;
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		//Jumping
		bool isRising;
		int JumpYposTemp;
		int YVelocity;
		int InitialVelocity;
	private:
		int HitRectangle(int tx1, int ty1, int tx2, int ty2);
	};
}