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
		CMovingBitmap Roll[2][3];
		//Battle Animation
		CMovingBitmap Defense[2][2];
		CMovingBitmap NormalAttack1[2][2];
		CMovingBitmap NormalAttack2[2][2];
		CMovingBitmap NormalAttack3[2][3];
		CMovingBitmap HeavyAttack[2][5];
		CMovingBitmap JumpAttack[2][3];
		CMovingBitmap JumpHeavyAttack[2][3];
		CMovingBitmap AttackLand[2][2];
		//GettingHit
		CMovingBitmap Knock[2][3];
		CMovingBitmap Knock2[2][3];
		CMovingBitmap KnockFront[2][7];
		CMovingBitmap KnockBack[2][7];

		void LoadFreeze();
		void LoadWoody();
		void LoadHenry();
		~CharacterAnimation();
	};
}