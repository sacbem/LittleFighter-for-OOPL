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
		CMovingBitmap Defense[2][2];
		CMovingBitmap Roll[2][3];
		void LoadFreeze();
		void LoadFirzen();
		void LoadHenry();
		~CharacterAnimation();

	};
}