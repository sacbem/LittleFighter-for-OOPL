#include "CharacterAnimation.h"
namespace game_framework {
	class Character
	{
	public:
		Character();
		Character(Character const & other);
		~Character();
		//int HitEnemy(Character* enemy);
		virtual int HitEnemy(Character* enemy)=0;
		bool GetAlive();
		int  GetX1();					// Chracter���W�� x �y��
		int  GetY1();					// Chracter���W�� y �y��
		int  GetX2();					// Chracter�k�U�� x �y��
		int  GetY2();					// Chracter�k�U�� y �y��
		int	 GetDir();
		int	 GetHealth();
		void Initialize();
		virtual void SetCharacter() = 0;
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
		boolean IsStatic();
		boolean  DistanceAccumulatorReset();
		void SetAlive(bool flag);
		void SetXY(int X, int Y);
		//void SetStatic();
		//int GetState() ; //static :1 walking :2 running : 3
        int GetDistance();
        //void SetAccumulator(int, int,boolean resetSignal);
		void SetMapBorder(int mapID);
		//basic informtion
		bool getCharacter=false;
		int characterNumber;
		int HealthPoint;
		int AttackPoint;
		int DefencePoint;
		bool isAlive;
		bool isWalking;
		bool isRunning;
		bool StopRun;
	protected:
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
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
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
		CharacterAnimation Animation;
		string name;
	private:
		//CMovingBitmap shadow;
		//CMovingBitmap nameImg;
		
		//Animation Properties
		int AnimationState=0;
		int AnimationCount = 0;
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
		//int HitRectangle(int tx1, int ty1, int tx2, int ty2);
		virtual int HitRectangle(int tx1, int ty1, int tx2, int ty2) = 0;

		//keyInput
		int KeyBoardInputTime;
		int LastInputTime;
		int Diff;
		UINT LastInput;									//�W�@�ӿ�J
	};
	
	class Freeze:public Character {
	public:
		//change to freeze

		CMovingBitmap NormalAttack[2][4]; //0_10 ~ 13
		CMovingBitmap NormalAttack2[2][3]; //0_50 ~ 52
		CMovingBitmap HeavyAttack[2][4]; //0_17 0_18 0_19 0_29
		CMovingBitmap JumpAttack[2][3]; //0_14 0_15 0_16
		CMovingBitmap AttackLand[2][2]; //0_39  0_49

		int AttackPoint;
		int AttackState = 0;
		void setAttack(bool flag);
		void ShowAttack();
		virtual void SetCharacter() override;
		virtual int HitEnemy(Character* enemy) override;
	private:
		virtual int HitRectangle(int tx1, int ty1, int tx2, int ty2) override;
	};
	
	
}