namespace game_framework {
	class Character
	{
	public:
		Character();
		//Character(Character const& other);
		~Character();
		int HitEnemy(Character* enemy);
		bool GetAlive();
		int  GetX1();					// Chracter左上角 x 座標
		int  GetY1();					// Chracter左上角 y 座標
		int  GetX2();					// Chracter右下角 x 座標
		int  GetY2();					// Chracter右下角 y 座標
		int	 GetDir();
		int	 GetHealth();
		void Initialize();
		void SetCharacter(int num);
		void LoadCharacter();
		void OnShow();
		void OnMove();
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetRunning(bool flag);
		void SetJumpping(bool flag);
		void SetDefense(bool flag);
		void InputKeyDown(UINT nChar);
		void InputKeyUp(UINT nChar);
		
		void SetAlive(bool flag);
		void SetXY(int X, int Y);
        int GetDistance();
        void SetAccumulator(int, int);
		void SetMapBorder(int mapID);
		//basic informtion
		bool getCharacter;
		int characterNumber;
		string name;
		int HealthPoint;
		int AttackPoint;
		int DefencePoint;
		bool isAlive;
		bool isWalking;
		bool isRunning;
		bool StopRun;

	protected:
		//CMovingBitmap shadow;
		//CMovingBitmap nameImg;
        CMovingBitmap photoSticker;

        void DistaceAccumulator();

		int DelayCounter;
		int Delay;
		int xPos, yPos;
		int xMapBorderMax, yMapBorderMax;
		int xMapBorderMin, yMapBorderMin;
        int xAccumulator, yAccumulator;
		//judge
		//direction
		int direction;				// 0=Left 1=Right
		int hitDirection;
		//basic movement
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
        int walkedDistance;

		bool UnMovable;
		//for jump
		bool isJumpping;
		bool isRising;
		int JumpYposTemp;
		int YVelocity;
		int InitialVelocity;
		bool island;
		//Defense
		bool isDefense;

		//Animation Properties
		//normal state
		CAnimation Normal[2];
		CAnimation Walk[2];
		CAnimation Run[2];
		CMovingBitmap RunStop[2];
		CMovingBitmap Jump[2][4];
		CMovingBitmap Defense[2][2];
		CMovingBitmap Roll[2][3];
	private:
		int AnimationState=0;
		//Jump
		int JumpCount = 0;
		int JumpCountTemp = 0;
		//Run
		int RunCount = 0;
		//Defense
		int DefenseCount = 0;
		//Roll
		int RollCount = 0;
		//basic function
		void SetMoving();

		//basic information
		int speed=2;

		//hit box
		int HitRectangle(int tx1, int ty1, int tx2, int ty2);

		//keyInput
		int KeyBoardInputTime;
		int LastInputTime;
		int Diff;
		UINT LastInput;									//上一個輸入
	};
	/*
	class Firzen : public Character{
		virtual void LoadCharacter() override;
	};
	*/
}