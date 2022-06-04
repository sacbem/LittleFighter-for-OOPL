namespace game_framework {
	class CharacterAnimation
	{
	public:
		CharacterAnimation();
		//normal Animation
		CAnimation Normal[2];
		CAnimation Walk[2];
		CAnimation Run[2];
		CMovingBitmap RunStop[2];
		CMovingBitmap Jump[2][4];
		CMovingBitmap Roll[2][5];
		//Battle Animation
		CMovingBitmap Defense[2][2];
		CMovingBitmap NormalAttack1[2][6];
		CMovingBitmap NormalAttack2[2][3];
		CMovingBitmap NormalAttack3[2][7];
		CMovingBitmap HeavyAttack[2][5];
		CMovingBitmap JumpAttack[2][5];
		CMovingBitmap JumpHeavyAttack[2][3];
		CMovingBitmap AttackLand[2][2];
		//GettingHit
		CMovingBitmap Knock[2][3];
		CMovingBitmap Knock2[2][3];
		CMovingBitmap KnockFront[2][7];
		CMovingBitmap KnockBack[2][7];
		//Carry item
		CMovingBitmap itemNormal[2];
		CAnimation itemWalk[2];
		CAnimation itemRun[2];
		CMovingBitmap itemThrow[2][2];
		CMovingBitmap itemRunThrow[2][2];
		CMovingBitmap Frozen[2][2];
		//weapon
		CMovingBitmap weaponNormalAttack1[2][4];
		CMovingBitmap weaponNormalAttack2[2][3];
		CMovingBitmap weaponHeavyAttack[2][2];
		CMovingBitmap weaponJumpAttack[2][4];
		CMovingBitmap weaponJumpHeavyAttack[2][4];

		CMovingBitmap Grab[2];
		CMovingBitmap Dead[2][2];

		void LoadFreeze();
		void LoadWoody();
		void LoadHenry();
		~CharacterAnimation();
	};
}