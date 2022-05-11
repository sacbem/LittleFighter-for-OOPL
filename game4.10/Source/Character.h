#pragma once
#include "SkillEffect.h"
#include "CharacterAnimation.h"

namespace game_framework {
	class Character{
	public:
		Character();
		Character(Character const & other);
		~Character();
		//int HitEnemy(Character* enemy);
	
	
		bool GetAlive();
		int  GetX1();					// Chracter
		int  GetY1();					// Chracter
		int  GetX2();					// Chracter
		int  GetY2();					// Chracter
		int	 GetDir();
		int	 GetHealth();
		void isGettingDamage(int Damage);
		int GetDistance();
		int GetMovingTime(boolean isLeft);
		int GetSkillSignal();
		void Initialize();

		virtual void SetCharacter() = 0;
		virtual void OnShow()=0;
		virtual void OnMove() = 0;
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetMovingUp(bool flag);
		void SetRunning(bool flag);
		void SetJumpping(bool flag);
		void SetDefense(bool flag);
		void SetAlive(bool flag);
		void SetXY(int X, int Y);
		void SetMapBorder(int mapID);
		virtual void SetAttack(bool flag) = 0;
		virtual void SetKnock(bool flag, int Dir, int AttState)=0;
		virtual void SetSkill(int createdTimes) =0;
		void InputKeyDown(UINT nChar);
		void InputKeyUp(UINT nChar);

		boolean IsStatic();
		boolean  DistanceAccumulatorReset();
		virtual int HitEnemy(Character* enemy) = 0;

		
		//basic informtion
		bool getCharacter=false;
		int characterNumber;
		int HealthPoint;
		int InnerHealPoint;
		int Mana;
		int InnerMana;
		int AttackPoint;
		int DefencePoint;
		bool isAlive;
		bool isWalking;
		bool isHitting;
		bool isRunning;
		bool StopRun;

		bool isAttacking;
		bool isGettingHit;
		//call Attack & Defense
		virtual void ShowDefense() = 0;
		virtual void ShowRoll () = 0;
		virtual void ShowAttack() = 0;
		virtual void ShowKnock() = 0;
		int AttackState = 0;

		int leftTime = 0;
		int rightTime = 0;
		vector<int>skillsEffect_InFieldNumber;
		int KeyBoardInputTime;
		friend class SkillEffect;
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
		bool isMovingDown;
		bool isMovingLeft;
		bool isMovingRight;
		bool isMovingUp;
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
		int DefenseCount = 0;
		//Attack
		int LastAttackState = 0;
		int AttackCount = 0;
		int AttackLong = 0;
		int AttackAccumulator = 0;
		
		int KnockState = 0;
		int LastKnockState = 0;
		int KnockCount = 0;
		int DamageAccumulator = 0;
		int KnockSpeed;
		int skillSignal;

		int SpecialAttackState = 0;
		virtual void CallSpecial() = 0;

		virtual bool isAttackFrame() = 0;
		virtual bool AttackReach() = 0;

		CharacterAnimation Animation;
		string name;
		
		//Animation Properties
		int AnimationState;
		int AnimationCount = 0;
		//Jump
		int JumpCount = 0;
		int JumpCountTemp = 0;
		//Run
		int RunCount = 0;
		//Defense
		//Roll
		int RollCount = 0;
		//basic function
		
		
		time_t L_start, L_finish;
		time_t R_start, R_finish;
		void SetMoving();
	private:
		//CMovingBitmap shadow;
		//CMovingBitmap nameImg;
		
		//basic information
		int speed=2;
		
		//hit box
		//int HitRectangle(int tx1, int ty1, int tx2, int ty2);
		virtual int HitRectangle(int tx1, int ty1, int tx2, int ty2) = 0;

		//keyInput
		int LastInputTime;
		int Diff;
		UINT LastInput;									//�W�@�ӿ�J
	};
	
	class Freeze:public Character {
	public:
		//change to freeze
		Freeze();
		virtual void OnShow() override;
		virtual void OnMove() override;

		virtual void SetAttack(bool flag) override;
		virtual void ShowAttack() override;
		virtual void SetCharacter() override;
		virtual void SetSkill(int createdTimes) override;
		virtual int HitEnemy(Character* enemy) override;
		virtual bool isAttackFrame() override;
		void EffectObjectAliveManager(int mainTime);
		~Freeze();

		//Knock
		virtual void ShowKnock() override;
		virtual void SetKnock(bool flag, int Dir, int AttState) override;

		//Movement
		virtual void ShowDefense() override;
		virtual void ShowRoll() override;
		//Special Attack;
		virtual void CallSpecial() override;

		int SpCount=0;
		void InitSpecialAttack();
		void FrozenBall();
	protected:
		CMovingBitmap FrozenBallAnimation[2][6];
		virtual bool AttackReach() override;

	private:
		virtual int HitRectangle(int tx1, int ty1, int tx2, int ty2) override;
		vector <SkillEffect*> frozenWaves, frozenPunchs, frozenSwords, frozenStorms;
		vector <int>  frozenWaves_Duration;
	};
	
	
}