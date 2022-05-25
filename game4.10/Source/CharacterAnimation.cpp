#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CharacterAnimation.h"
namespace game_framework {
	CharacterAnimation::CharacterAnimation() {

	}
	void CharacterAnimation::LoadWoody() {
		//normal state right
		Normal[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_0.bmp", RGB(0, 0, 0));
		Normal[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_1.bmp", RGB(0, 0, 0));
		Normal[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_2.bmp", RGB(0, 0, 0));
		Normal[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_3.bmp", RGB(0, 0, 0));
		//normal state left
		Normal[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_9.bmp", RGB(0, 0, 0));
		Normal[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_8.bmp", RGB(0, 0, 0));
		Normal[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_7.bmp", RGB(0, 0, 0));
		Normal[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_6.bmp", RGB(0, 0, 0));
		//walk right
		Walk[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_4.bmp", RGB(0, 0, 0));
		Walk[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_5.bmp", RGB(0, 0, 0));
		Walk[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_6.bmp", RGB(0, 0, 0));
		Walk[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_7.bmp", RGB(0, 0, 0));
		Walk[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_6.bmp", RGB(0, 0, 0));
		Walk[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_5.bmp", RGB(0, 0, 0));
		//walk left
		Walk[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_5.bmp", RGB(0, 0, 0));
		Walk[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_4.bmp", RGB(0, 0, 0));
		Walk[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_3.bmp", RGB(0, 0, 0));
		Walk[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_2.bmp", RGB(0, 0, 0));
		Walk[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_3.bmp", RGB(0, 0, 0));
		Walk[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_4.bmp", RGB(0, 0, 0));

		//Run right
		Run[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_20.bmp", RGB(0, 0, 0));
		Run[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_21.bmp", RGB(0, 0, 0));
		Run[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_22.bmp", RGB(0, 0, 0));
		Run[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_21.bmp", RGB(0, 0, 0));
		//run left
		Run[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_29.bmp", RGB(0, 0, 0));
		Run[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_28.bmp", RGB(0, 0, 0));
		Run[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_27.bmp", RGB(0, 0, 0));
		Run[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_28.bmp", RGB(0, 0, 0));

		RunStop[0].LoadBitmapA(".\\res\\Woody\\Woody_1\\woody_1_44.bmp", RGB(0, 0, 0));
		RunStop[1].LoadBitmapA(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_45.bmp", RGB(0, 0, 0));

		//jump
		Jump[0][0].LoadBitmapA(".\\res\\Woody\\Woody_0\\woody_0_60.bmp", RGB(0, 0, 0));
		Jump[0][1].LoadBitmapA(".\\res\\Woody\\Woody_0\\woody_0_61.bmp", RGB(0, 0, 0));
		Jump[0][2].LoadBitmapA(".\\res\\Woody\\Woody_0\\woody_0_62.bmp", RGB(0, 0, 0));
		Jump[0][3].LoadBitmapA(".\\res\\Woody\\Woody_0\\woody_0_63.bmp", RGB(0, 0, 0));

		Jump[1][0].LoadBitmapA(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_69.bmp", RGB(0, 0, 0));
		Jump[1][1].LoadBitmapA(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_68.bmp", RGB(0, 0, 0));
		Jump[1][2].LoadBitmapA(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_67.bmp", RGB(0, 0, 0));
		Jump[1][3].LoadBitmapA(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_66.bmp", RGB(0, 0, 0));

		Defense[0][0].LoadBitmapA(".\\res\\Woody\\Woody_0\\woody_0_56.bmp", RGB(0, 0, 0));
		Defense[0][1].LoadBitmapA(".\\res\\Woody\\Woody_0\\woody_0_57.bmp", RGB(0, 0, 0));
		Defense[1][0].LoadBitmapA(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_53.bmp", RGB(0, 0, 0));
		Defense[1][1].LoadBitmapA(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_52.bmp", RGB(0, 0, 0));

		Roll[0][0].LoadBitmapA(".\\res\\Woody\\Woody_0\\woody_0_58.bmp", RGB(0, 0, 0));
		Roll[0][1].LoadBitmapA(".\\res\\Woody\\Woody_0\\woody_0_59.bmp", RGB(0, 0, 0));
		Roll[0][2].LoadBitmapA(".\\res\\Woody\\Woody_0\\woody_0_69.bmp", RGB(0, 0, 0));
		Roll[1][0].LoadBitmapA(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_51.bmp", RGB(0, 0, 0));
		Roll[1][1].LoadBitmapA(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_50.bmp", RGB(0, 0, 0));
		Roll[1][2].LoadBitmapA(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_60.bmp", RGB(0, 0, 0));
		//Attack
		NormalAttack1[0][0].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_10.bmp", RGB(0, 0, 0));
		NormalAttack1[0][1].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_11.bmp", RGB(0, 0, 0));
		NormalAttack1[0][2].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_12.bmp", RGB(0, 0, 0));
		NormalAttack1[1][0].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_19.bmp", RGB(0, 0, 0));
		NormalAttack1[1][1].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_18.bmp", RGB(0, 0, 0));
		NormalAttack1[1][2].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_17.bmp", RGB(0, 0, 0));

		NormalAttack2[0][0].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_13.bmp", RGB(0, 0, 0));
		NormalAttack2[0][1].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_14.bmp", RGB(0, 0, 0));
		NormalAttack2[0][2].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_15.bmp", RGB(0, 0, 0));
		NormalAttack2[1][0].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_16.bmp", RGB(0, 0, 0));
		NormalAttack2[1][1].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_15.bmp", RGB(0, 0, 0));
		NormalAttack2[1][2].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_14.bmp", RGB(0, 0, 0));

		NormalAttack3[0][0].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_8.bmp", RGB(0, 0, 0));
		NormalAttack3[0][1].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_9.bmp", RGB(0, 0, 0));
		NormalAttack3[0][2].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_66.bmp", RGB(0, 0, 0));
		NormalAttack3[0][3].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_19.bmp", RGB(0, 0, 0));
		NormalAttack3[0][4].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_65.bmp", RGB(0, 0, 0));
		NormalAttack3[0][5].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_39.bmp", RGB(0, 0, 0));
		NormalAttack3[0][6].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_36.bmp", RGB(0, 0, 0));
		NormalAttack3[1][0].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_1.bmp", RGB(0, 0, 0));
		NormalAttack3[1][1].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_0.bmp", RGB(0, 0, 0));
		NormalAttack3[1][2].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_63.bmp", RGB(0, 0, 0));
		NormalAttack3[1][3].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_10.bmp", RGB(0, 0, 0));
		NormalAttack3[1][4].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_64.bmp", RGB(0, 0, 0));
		NormalAttack3[1][5].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_30.bmp", RGB(0, 0, 0));
		NormalAttack3[1][6].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_40.bmp", RGB(0, 0, 0));

		HeavyAttack[0][0].LoadBitmap(".\\res\\Woody\\Woody_1\\woody_1_30.bmp", RGB(0, 0, 0));
		HeavyAttack[0][1].LoadBitmap(".\\res\\Woody\\Woody_1\\woody_1_31.bmp", RGB(0, 0, 0));
		HeavyAttack[0][2].LoadBitmap(".\\res\\Woody\\Woody_1\\woody_1_32.bmp", RGB(0, 0, 0));
		HeavyAttack[0][3].LoadBitmap(".\\res\\Woody\\Woody_1\\woody_1_33.bmp", RGB(0, 0, 0));
		HeavyAttack[0][4].LoadBitmap(".\\res\\Woody\\Woody_1\\woody_1_34.bmp", RGB(0, 0, 0));
		HeavyAttack[1][0].LoadBitmap(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_39.bmp", RGB(0, 0, 0));
		HeavyAttack[1][1].LoadBitmap(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_38.bmp", RGB(0, 0, 0));
		HeavyAttack[1][2].LoadBitmap(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_37.bmp", RGB(0, 0, 0));
		HeavyAttack[1][3].LoadBitmap(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_36.bmp", RGB(0, 0, 0));
		HeavyAttack[1][4].LoadBitmap(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_35.bmp", RGB(0, 0, 0));

		JumpAttack[0][0].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_16.bmp", RGB(0, 0, 0));
		JumpAttack[0][1].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_17.bmp", RGB(0, 0, 0));
		JumpAttack[0][2].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_18.bmp", RGB(0, 0, 0));
		JumpAttack[1][0].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_13.bmp", RGB(0, 0, 0));
		JumpAttack[1][1].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_12.bmp", RGB(0, 0, 0));
		JumpAttack[1][2].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_11.bmp", RGB(0, 0, 0));

		JumpHeavyAttack[0][0].LoadBitmap(".\\res\\Woody\\Woody_1\\woody_1_37.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[0][1].LoadBitmap(".\\res\\Woody\\Woody_1\\woody_1_38.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[0][2].LoadBitmap(".\\res\\Woody\\Woody_1\\woody_1_39.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[1][0].LoadBitmap(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_32.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[1][1].LoadBitmap(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_31.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[1][2].LoadBitmap(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_30.bmp", RGB(0, 0, 0));
		//Knock
		Knock[0][0].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_53.bmp", RGB(0, 0, 0));
		Knock[0][1].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_54.bmp", RGB(0, 0, 0));
		Knock[0][2].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_55.bmp", RGB(0, 0, 0));
		Knock[1][0].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_56.bmp", RGB(0, 0, 0));
		Knock[1][1].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_55.bmp", RGB(0, 0, 0));
		Knock[1][2].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_54.bmp", RGB(0, 0, 0));

		Knock2[0][0].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_46.bmp", RGB(0, 0, 0));
		Knock2[0][1].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_47.bmp", RGB(0, 0, 0));
		Knock2[0][2].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_48.bmp", RGB(0, 0, 0));
		Knock2[1][0].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_43.bmp", RGB(0, 0, 0));
		Knock2[1][1].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_42.bmp", RGB(0, 0, 0));
		Knock2[1][2].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_41.bmp", RGB(0, 0, 0));

		KnockFront[0][0].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_30.bmp", RGB(0, 0, 0));
		KnockFront[0][1].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_31.bmp", RGB(0, 0, 0));
		KnockFront[0][2].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_32.bmp", RGB(0, 0, 0));
		KnockFront[0][3].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_33.bmp", RGB(0, 0, 0));
		KnockFront[0][4].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_34.bmp", RGB(0, 0, 0));
		KnockFront[0][5].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_35.bmp", RGB(0, 0, 0));
		KnockFront[0][6].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_36.bmp", RGB(0, 0, 0));
		KnockFront[1][0].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_39.bmp", RGB(0, 0, 0));
		KnockFront[1][1].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_38.bmp", RGB(0, 0, 0));
		KnockFront[1][2].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_37.bmp", RGB(0, 0, 0));
		KnockFront[1][3].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_36.bmp", RGB(0, 0, 0));
		KnockFront[1][4].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_35.bmp", RGB(0, 0, 0));
		KnockFront[1][5].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_34.bmp", RGB(0, 0, 0));
		KnockFront[1][6].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_33.bmp", RGB(0, 0, 0));

		KnockBack[0][0].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_40.bmp", RGB(0, 0, 0));
		KnockBack[0][1].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_41.bmp", RGB(0, 0, 0));
		KnockBack[0][2].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_42.bmp", RGB(0, 0, 0));
		KnockBack[0][3].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_43.bmp", RGB(0, 0, 0));
		KnockBack[0][4].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_44.bmp", RGB(0, 0, 0));
		KnockBack[0][5].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_45.bmp", RGB(0, 0, 0));
		KnockBack[0][6].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_36.bmp", RGB(0, 0, 0));
		KnockBack[1][0].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_49.bmp", RGB(0, 0, 0));
		KnockBack[1][1].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_48.bmp", RGB(0, 0, 0));
		KnockBack[1][2].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_47.bmp", RGB(0, 0, 0));
		KnockBack[1][3].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_46.bmp", RGB(0, 0, 0));
		KnockBack[1][4].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_45.bmp", RGB(0, 0, 0));
		KnockBack[1][5].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_44.bmp", RGB(0, 0, 0));
		KnockBack[1][6].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_33.bmp", RGB(0, 0, 0));

		itemNormal[0].LoadBitmap(".\\res\\Woody\\Woody_0\\woody_0_27.bmp", RGB(0, 0, 0));
		itemNormal[1].LoadBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_23.bmp", RGB(0, 0, 0));

		itemWalk[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_23.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_24.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_25.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_26.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_25.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Woody\\Woody_0\\woody_0_24.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_26.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_25.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_24.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_23.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_24.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_25.bmp", RGB(0, 0, 0));

		itemRun[0].AddBitmap(".\\res\\Woody\\Woody_1\\woody_1_55.bmp", RGB(0, 0, 0));
		itemRun[0].AddBitmap(".\\res\\Woody\\Woody_1\\woody_1_56.bmp", RGB(0, 0, 0));
		itemRun[0].AddBitmap(".\\res\\Woody\\Woody_1\\woody_1_57.bmp", RGB(0, 0, 0));
		itemRun[0].AddBitmap(".\\res\\Woody\\Woody_1\\woody_1_56.bmp", RGB(0, 0, 0));
		itemRun[1].AddBitmap(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_54.bmp", RGB(0, 0, 0));
		itemRun[1].AddBitmap(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_53.bmp", RGB(0, 0, 0));
		itemRun[1].AddBitmap(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_52.bmp", RGB(0, 0, 0));
		itemRun[1].AddBitmap(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_53.bmp", RGB(0, 0, 0));

		itemThrow[0][0].LoadBitmapA(".\\res\\Woody\\Woody_0\\woody_0_27.bmp", RGB(0, 0, 0));
		itemThrow[0][1].LoadBitmapA(".\\res\\Woody\\Woody_0\\woody_0_28.bmp", RGB(0, 0, 0));
		itemThrow[1][0].LoadBitmapA(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_22.bmp", RGB(0, 0, 0));
		itemThrow[1][1].LoadBitmapA(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_21.bmp", RGB(0, 0, 0));

		itemRunThrow[0][0].LoadBitmapA(".\\res\\Woody\\Woody_1\\woody_1_58.bmp", RGB(0, 0, 0));
		itemRunThrow[0][1].LoadBitmapA(".\\res\\Woody\\Woody_1\\woody_1_26.bmp", RGB(0, 0, 0));
		itemRunThrow[1][0].LoadBitmapA(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_51.bmp", RGB(0, 0, 0));
		itemRunThrow[1][1].LoadBitmapA(".\\res\\Woody\\Woody_1_reverse\\woody_1_reverse_23.bmp", RGB(0, 0, 0));

		Frozen[0][0].LoadBitmapA(".\\res\\Woody\\Woody_0\\woody_0_8.bmp", RGB(0, 0, 0));
		Frozen[0][1].LoadBitmapA(".\\res\\Woody\\Woody_0\\woody_0_9.bmp", RGB(0, 0, 0));
		Frozen[1][0].LoadBitmapA(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_1.bmp", RGB(0, 0, 0));
		Frozen[1][1].LoadBitmapA(".\\res\\Woody\\Woody_0_reverse\\woody_0_reverse_0.bmp", RGB(0, 0, 0));
	}
	
	void CharacterAnimation::LoadFreeze() {
		//normal state right
		Normal[0].AddBitmap(FREEZE_NORMAL4, RGB(0, 0, 0));
		Normal[0].AddBitmap(FREEZE_NORMAL3, RGB(0, 0, 0));
		Normal[0].AddBitmap(FREEZE_NORMAL2, RGB(0, 0, 0));
		Normal[0].AddBitmap(FREEZE_NORMAL1, RGB(0, 0, 0));
		//normal state left
		Normal[1].AddBitmap(FREEZE_NORMAL4_REVERSE, RGB(0, 0, 0));
		Normal[1].AddBitmap(FREEZE_NORMAL3_REVERSE, RGB(0, 0, 0));
		Normal[1].AddBitmap(FREEZE_NORMAL2_REVERSE, RGB(0, 0, 0));
		Normal[1].AddBitmap(FREEZE_NORMAL1_REVERSE, RGB(0, 0, 0));
		//walk right
		Walk[0].AddBitmap(FREEZE_WALK1, RGB(0, 0, 0));
		Walk[0].AddBitmap(FREEZE_WALK2, RGB(0, 0, 0));
		Walk[0].AddBitmap(FREEZE_WALK3, RGB(0, 0, 0));
		Walk[0].AddBitmap(FREEZE_WALK4, RGB(0, 0, 0));
		Walk[0].AddBitmap(FREEZE_WALK3, RGB(0, 0, 0));
		Walk[0].AddBitmap(FREEZE_WALK2, RGB(0, 0, 0));
		//walk left
		Walk[1].AddBitmap(FREEZE_WALK1_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(FREEZE_WALK2_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(FREEZE_WALK3_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(FREEZE_WALK4_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(FREEZE_WALK3_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(FREEZE_WALK2_REVERSE, RGB(0, 0, 0));

		//Run right
		Run[0].AddBitmap(FREEZE_RUN1, RGB(0, 0, 0));
		Run[0].AddBitmap(FREEZE_RUN2, RGB(0, 0, 0));
		Run[0].AddBitmap(FREEZE_RUN3, RGB(0, 0, 0));
		Run[0].AddBitmap(FREEZE_RUN2, RGB(0, 0, 0));
		//run left
		Run[1].AddBitmap(FREEZE_RUN1_REVERSE, RGB(0, 0, 0));
		Run[1].AddBitmap(FREEZE_RUN2_REVERSE, RGB(0, 0, 0));
		Run[1].AddBitmap(FREEZE_RUN3_REVERSE, RGB(0, 0, 0));
		Run[1].AddBitmap(FREEZE_RUN2_REVERSE, RGB(0, 0, 0));

		RunStop[0].LoadBitmapA(".\\res\\Freeze\\Freeze_1\\freeze_1_44.bmp", RGB(0, 0, 0));
		RunStop[1].LoadBitmapA(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_45.bmp", RGB(0, 0, 0));

		//jump
		Jump[0][0].LoadBitmapA(".\\res\\Freeze\\Freeze_0\\freeze_0_60.bmp", RGB(0, 0, 0));
		Jump[0][1].LoadBitmapA(".\\res\\Freeze\\Freeze_0\\freeze_0_61.bmp", RGB(0, 0, 0));
		Jump[0][2].LoadBitmapA(".\\res\\Freeze\\Freeze_0\\freeze_0_62.bmp", RGB(0, 0, 0));
		Jump[0][3].LoadBitmapA(".\\res\\Freeze\\Freeze_0\\freeze_0_63.bmp", RGB(0, 0, 0));

		Jump[1][0].LoadBitmapA(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_69.bmp", RGB(0, 0, 0));
		Jump[1][1].LoadBitmapA(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_68.bmp", RGB(0, 0, 0));
		Jump[1][2].LoadBitmapA(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_67.bmp", RGB(0, 0, 0));
		Jump[1][3].LoadBitmapA(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_66.bmp", RGB(0, 0, 0));

		Defense[0][0].LoadBitmapA(".\\res\\Freeze\\Freeze_0\\freeze_0_56.bmp", RGB(0, 0, 0));
		Defense[0][1].LoadBitmapA(".\\res\\Freeze\\Freeze_0\\freeze_0_57.bmp", RGB(0, 0, 0));
		Defense[1][0].LoadBitmapA(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_53.bmp", RGB(0, 0, 0));
		Defense[1][1].LoadBitmapA(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_52.bmp", RGB(0, 0, 0));

		Roll[0][0].LoadBitmapA(".\\res\\Freeze\\Freeze_0\\freeze_0_58.bmp", RGB(0, 0, 0));
		Roll[0][1].LoadBitmapA(".\\res\\Freeze\\Freeze_0\\freeze_0_59.bmp", RGB(0, 0, 0));
		Roll[0][2].LoadBitmapA(".\\res\\Freeze\\Freeze_0\\freeze_0_69.bmp", RGB(0, 0, 0));
		Roll[1][0].LoadBitmapA(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_51.bmp", RGB(0, 0, 0));
		Roll[1][1].LoadBitmapA(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_50.bmp", RGB(0, 0, 0));
		Roll[1][2].LoadBitmapA(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_60.bmp", RGB(0, 0, 0));
		//Attack
		NormalAttack1[0][0].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_10.bmp", RGB(0, 0, 0));
		NormalAttack1[0][1].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_11.bmp", RGB(0, 0, 0));
		NormalAttack1[1][0].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_19.bmp", RGB(0, 0, 0));
		NormalAttack1[1][1].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_18.bmp", RGB(0, 0, 0));

		NormalAttack2[0][0].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_12.bmp", RGB(0, 0, 0));
		NormalAttack2[0][1].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_13.bmp", RGB(0, 0, 0));
		NormalAttack2[1][0].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_17.bmp", RGB(0, 0, 0));
		NormalAttack2[1][1].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_16.bmp", RGB(0, 0, 0));

		NormalAttack3[0][0].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_17.bmp", RGB(0, 0, 0));
		NormalAttack3[0][1].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_18.bmp", RGB(0, 0, 0));
		NormalAttack3[0][2].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_19.bmp", RGB(0, 0, 0));
		NormalAttack3[1][0].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_12.bmp", RGB(0, 0, 0));
		NormalAttack3[1][1].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_11.bmp", RGB(0, 0, 0));
		NormalAttack3[1][2].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_10.bmp", RGB(0, 0, 0));

		HeavyAttack[0][0].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_32.bmp", RGB(0, 0, 0));
		HeavyAttack[0][1].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_33.bmp", RGB(0, 0, 0));
		HeavyAttack[0][2].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_34.bmp", RGB(0, 0, 0));
		HeavyAttack[0][3].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_35.bmp", RGB(0, 0, 0));
		HeavyAttack[0][4].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_36.bmp", RGB(0, 0, 0));
		HeavyAttack[1][0].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_37.bmp", RGB(0, 0, 0));
		HeavyAttack[1][1].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_36.bmp", RGB(0, 0, 0));
		HeavyAttack[1][2].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_35.bmp", RGB(0, 0, 0));
		HeavyAttack[1][3].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_34.bmp", RGB(0, 0, 0));
		HeavyAttack[1][4].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_33.bmp", RGB(0, 0, 0));

		JumpAttack[0][0].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_14.bmp", RGB(0, 0, 0));
		JumpAttack[0][1].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_15.bmp", RGB(0, 0, 0));
		JumpAttack[0][2].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_16.bmp", RGB(0, 0, 0));
		JumpAttack[1][0].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_15.bmp", RGB(0, 0, 0));
		JumpAttack[1][1].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_14.bmp", RGB(0, 0, 0));
		JumpAttack[1][2].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_13.bmp", RGB(0, 0, 0));

		JumpHeavyAttack[0][0].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_37.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[0][1].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_38.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[0][2].LoadBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_39.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[1][0].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_32.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[1][1].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_31.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[1][2].LoadBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_30.bmp", RGB(0, 0, 0));
		//Knock
		Knock[0][0].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_53.bmp", RGB(0, 0, 0));
		Knock[0][1].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_54.bmp", RGB(0, 0, 0));
		Knock[0][2].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_55.bmp", RGB(0, 0, 0));
		Knock[1][0].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_56.bmp", RGB(0, 0, 0));
		Knock[1][1].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_55.bmp", RGB(0, 0, 0));
		Knock[1][2].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_54.bmp", RGB(0, 0, 0));

		Knock2[0][0].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_46.bmp", RGB(0, 0, 0));
		Knock2[0][1].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_47.bmp", RGB(0, 0, 0));
		Knock2[0][2].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_48.bmp", RGB(0, 0, 0));
		Knock2[1][0].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_43.bmp", RGB(0, 0, 0));
		Knock2[1][1].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_42.bmp", RGB(0, 0, 0));
		Knock2[1][2].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_41.bmp", RGB(0, 0, 0));
		
		KnockFront[0][0].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_30.bmp", RGB(0, 0, 0));
		KnockFront[0][1].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_31.bmp", RGB(0, 0, 0));
		KnockFront[0][2].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_32.bmp", RGB(0, 0, 0));
		KnockFront[0][3].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_33.bmp", RGB(0, 0, 0));
		KnockFront[0][4].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_34.bmp", RGB(0, 0, 0));
		KnockFront[0][5].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_35.bmp", RGB(0, 0, 0));
		KnockFront[0][6].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_36.bmp", RGB(0, 0, 0));
		KnockFront[1][0].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_39.bmp", RGB(0, 0, 0));
		KnockFront[1][1].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_38.bmp", RGB(0, 0, 0));
		KnockFront[1][2].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_37.bmp", RGB(0, 0, 0));
		KnockFront[1][3].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_36.bmp", RGB(0, 0, 0));
		KnockFront[1][4].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_35.bmp", RGB(0, 0, 0));
		KnockFront[1][5].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_34.bmp", RGB(0, 0, 0));
		KnockFront[1][6].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_33.bmp", RGB(0, 0, 0));

		KnockBack[0][0].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_40.bmp", RGB(0, 0, 0));
		KnockBack[0][1].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_41.bmp", RGB(0, 0, 0));
		KnockBack[0][2].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_42.bmp", RGB(0, 0, 0));
		KnockBack[0][3].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_43.bmp", RGB(0, 0, 0));
		KnockBack[0][4].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_44.bmp", RGB(0, 0, 0));
		KnockBack[0][5].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_45.bmp", RGB(0, 0, 0));
		KnockBack[0][6].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_36.bmp", RGB(0, 0, 0));
		KnockBack[1][0].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_49.bmp", RGB(0, 0, 0));
		KnockBack[1][1].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_48.bmp", RGB(0, 0, 0));
		KnockBack[1][2].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_47.bmp", RGB(0, 0, 0));
		KnockBack[1][3].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_46.bmp", RGB(0, 0, 0));
		KnockBack[1][4].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_45.bmp", RGB(0, 0, 0));
		KnockBack[1][5].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_44.bmp", RGB(0, 0, 0));
		KnockBack[1][6].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_33.bmp", RGB(0, 0, 0));

		itemNormal[0].LoadBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_23.bmp", RGB(0, 0, 0));
		itemNormal[1].LoadBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_26.bmp", RGB(0, 0, 0));

		itemWalk[0].AddBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_23.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_24.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_25.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_26.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_25.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Freeze\\Freeze_0\\freeze_0_24.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_26.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_25.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_24.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_23.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_24.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_25.bmp", RGB(0, 0, 0));

		itemRun[0].AddBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_55.bmp", RGB(0, 0, 0));
		itemRun[0].AddBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_56.bmp", RGB(0, 0, 0));
		itemRun[0].AddBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_57.bmp", RGB(0, 0, 0));
		itemRun[0].AddBitmap(".\\res\\Freeze\\Freeze_1\\freeze_1_56.bmp", RGB(0, 0, 0));
		itemRun[1].AddBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_54.bmp", RGB(0, 0, 0));
		itemRun[1].AddBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_53.bmp", RGB(0, 0, 0));
		itemRun[1].AddBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_52.bmp", RGB(0, 0, 0));
		itemRun[1].AddBitmap(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_53.bmp", RGB(0, 0, 0));

		itemThrow[0][0].LoadBitmapA(".\\res\\Freeze\\Freeze_0\\freeze_0_27.bmp", RGB(0, 0, 0));
		itemThrow[0][1].LoadBitmapA(".\\res\\Freeze\\Freeze_0\\freeze_0_28.bmp", RGB(0, 0, 0));
		itemThrow[1][0].LoadBitmapA(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_22.bmp", RGB(0, 0, 0));
		itemThrow[1][1].LoadBitmapA(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_21.bmp", RGB(0, 0, 0));

		itemRunThrow[0][0].LoadBitmapA(".\\res\\Freeze\\Freeze_1\\freeze_1_58.bmp", RGB(0, 0, 0));
		itemRunThrow[0][1].LoadBitmapA(".\\res\\Freeze\\Freeze_1\\freeze_1_26.bmp", RGB(0, 0, 0));
		itemRunThrow[1][0].LoadBitmapA(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_51.bmp", RGB(0, 0, 0));
		itemRunThrow[1][1].LoadBitmapA(".\\res\\Freeze\\Freeze_1_reverse\\freeze_1_reverse_23.bmp", RGB(0, 0, 0));

		Frozen[0][0].LoadBitmapA(".\\res\\Freeze\\Freeze_0\\freeze_0_8.bmp", RGB(0, 0, 0));
		Frozen[0][1].LoadBitmapA(".\\res\\Freeze\\Freeze_0\\freeze_0_9.bmp", RGB(0, 0, 0));
		Frozen[1][0].LoadBitmapA(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_1.bmp", RGB(0, 0, 0));
		Frozen[1][1].LoadBitmapA(".\\res\\Freeze\\Freeze_0_reverse\\freeze_0_reverse_0.bmp", RGB(0, 0, 0));
	}

	void CharacterAnimation::LoadHenry() {
		//normal state right
		Normal[0].AddBitmap(HENRY_NORMAL4, RGB(0, 0, 0));
		Normal[0].AddBitmap(HENRY_NORMAL3, RGB(0, 0, 0));
		Normal[0].AddBitmap(HENRY_NORMAL2, RGB(0, 0, 0));
		Normal[0].AddBitmap(HENRY_NORMAL1, RGB(0, 0, 0));
		//normal state left
		Normal[1].AddBitmap(HENRY_NORMAL4_REVERSE, RGB(0, 0, 0));
		Normal[1].AddBitmap(HENRY_NORMAL3_REVERSE, RGB(0, 0, 0));
		Normal[1].AddBitmap(HENRY_NORMAL2_REVERSE, RGB(0, 0, 0));
		Normal[1].AddBitmap(HENRY_NORMAL1_REVERSE, RGB(0, 0, 0));
		//walk right
		Walk[0].AddBitmap(HENRY_WALK1, RGB(0, 0, 0));
		Walk[0].AddBitmap(HENRY_WALK2, RGB(0, 0, 0));
		Walk[0].AddBitmap(HENRY_WALK3, RGB(0, 0, 0));
		Walk[0].AddBitmap(HENRY_WALK4, RGB(0, 0, 0));
		Walk[0].AddBitmap(HENRY_WALK3, RGB(0, 0, 0));
		Walk[0].AddBitmap(HENRY_WALK2, RGB(0, 0, 0));
		//walk left
		Walk[1].AddBitmap(HENRY_WALK1_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(HENRY_WALK2_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(HENRY_WALK3_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(HENRY_WALK4_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(HENRY_WALK3_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(HENRY_WALK2_REVERSE, RGB(0, 0, 0));

		//Run right
		Run[0].AddBitmap(HENRY_RUN1, RGB(0, 0, 0));
		Run[0].AddBitmap(HENRY_RUN2, RGB(0, 0, 0));
		Run[0].AddBitmap(HENRY_RUN3, RGB(0, 0, 0));
		Run[0].AddBitmap(HENRY_RUN2, RGB(0, 0, 0));
		//run left
		Run[1].AddBitmap(HENRY_RUN1_REVERSE, RGB(0, 0, 0));
		Run[1].AddBitmap(HENRY_RUN2_REVERSE, RGB(0, 0, 0));
		Run[1].AddBitmap(HENRY_RUN3_REVERSE, RGB(0, 0, 0));
		Run[1].AddBitmap(HENRY_RUN2_REVERSE, RGB(0, 0, 0));

		RunStop[0].LoadBitmapA(".\\res\\Henry\\Henry_1\\henry_1_19.bmp", RGB(0, 0, 0));
		RunStop[1].LoadBitmapA(".\\res\\Henry\\Henry_1_reverse\\henry_1_reverse_10.bmp", RGB(0, 0, 0));

		//jump
		Jump[0][0].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_60.bmp", RGB(0, 0, 0));
		Jump[0][1].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_61.bmp", RGB(0, 0, 0));
		Jump[0][2].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_62.bmp", RGB(0, 0, 0));
		Jump[0][3].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_63.bmp", RGB(0, 0, 0));

		Jump[1][0].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_69.bmp", RGB(0, 0, 0));
		Jump[1][1].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_68.bmp", RGB(0, 0, 0));
		Jump[1][2].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_67.bmp", RGB(0, 0, 0));
		Jump[1][3].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_66.bmp", RGB(0, 0, 0));

		Defense[0][0].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_56.bmp", RGB(0, 0, 0));
		Defense[0][1].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_57.bmp", RGB(0, 0, 0));
		Defense[1][0].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_53.bmp", RGB(0, 0, 0));
		Defense[1][1].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_52.bmp", RGB(0, 0, 0));

		//this need add 0_19 && reverse_10
		Roll[0][0].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_16.bmp", RGB(0, 0, 0));
		Roll[0][1].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_17.bmp", RGB(0, 0, 0));
		Roll[0][2].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_18.bmp", RGB(0, 0, 0));
		Roll[0][3].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_12.bmp", RGB(0, 0, 0));
		Roll[0][4].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_13.bmp", RGB(0, 0, 0));
		Roll[1][0].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_13.bmp", RGB(0, 0, 0));
		Roll[1][1].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_12.bmp", RGB(0, 0, 0));
		Roll[1][2].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_11.bmp", RGB(0, 0, 0));
		Roll[1][3].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_17.bmp", RGB(0, 0, 0));
		Roll[1][4].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_16.bmp", RGB(0, 0, 0));



		//Attack
		NormalAttack1[0][0].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_10.bmp", RGB(0, 0, 0));
		NormalAttack1[0][1].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_11.bmp", RGB(0, 0, 0));
		NormalAttack1[0][2].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_12.bmp", RGB(0, 0, 0));
		NormalAttack1[0][3].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_13.bmp", RGB(0, 0, 0));
		NormalAttack1[0][4].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_14.bmp", RGB(0, 0, 0));
		NormalAttack1[0][5].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_15.bmp", RGB(0, 0, 0));
		NormalAttack1[1][0].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_19.bmp", RGB(0, 0, 0));
		NormalAttack1[1][1].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_18.bmp", RGB(0, 0, 0));
		NormalAttack1[1][2].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_17.bmp", RGB(0, 0, 0));
		NormalAttack1[1][3].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_16.bmp", RGB(0, 0, 0));
		NormalAttack1[1][4].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_15.bmp", RGB(0, 0, 0));
		NormalAttack1[1][5].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_14.bmp", RGB(0, 0, 0));

		NormalAttack2[0][0].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_12.bmp", RGB(0, 0, 0));
		NormalAttack2[0][1].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_13.bmp", RGB(0, 0, 0));
		NormalAttack2[1][0].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_17.bmp", RGB(0, 0, 0));
		NormalAttack2[1][1].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_16.bmp", RGB(0, 0, 0));

		NormalAttack3[0][0].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_17.bmp", RGB(0, 0, 0));
		NormalAttack3[0][1].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_18.bmp", RGB(0, 0, 0));
		NormalAttack3[0][2].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_19.bmp", RGB(0, 0, 0));
		NormalAttack3[1][0].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_12.bmp", RGB(0, 0, 0));
		NormalAttack3[1][1].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_11.bmp", RGB(0, 0, 0));
		NormalAttack3[1][2].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_10.bmp", RGB(0, 0, 0));

		HeavyAttack[0][0].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_37.bmp", RGB(0, 0, 0));
		HeavyAttack[0][1].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_29.bmp", RGB(0, 0, 0));
		HeavyAttack[0][2].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_38.bmp", RGB(0, 0, 0));
		HeavyAttack[0][3].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_39.bmp", RGB(0, 0, 0));
		HeavyAttack[1][0].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_32.bmp", RGB(0, 0, 0));
		HeavyAttack[1][1].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_20.bmp", RGB(0, 0, 0));
		HeavyAttack[1][2].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_31.bmp", RGB(0, 0, 0));
		HeavyAttack[1][3].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_30.bmp", RGB(0, 0, 0));

		JumpAttack[0][0].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_8.bmp", RGB(0, 0, 0));
		JumpAttack[0][1].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_9.bmp", RGB(0, 0, 0));
		JumpAttack[0][2].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_49.bmp", RGB(0, 0, 0));
		JumpAttack[0][3].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_58.bmp", RGB(0, 0, 0));
		JumpAttack[0][4].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_59.bmp", RGB(0, 0, 0));
		JumpAttack[1][0].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_1.bmp", RGB(0, 0, 0));
		JumpAttack[1][1].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_0.bmp", RGB(0, 0, 0));
		JumpAttack[1][2].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_40.bmp", RGB(0, 0, 0));
		JumpAttack[1][3].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_51.bmp", RGB(0, 0, 0));
		JumpAttack[1][4].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_50.bmp", RGB(0, 0, 0));

		JumpHeavyAttack[0][0].LoadBitmap(".\\res\\Henry\\Henry_1\\henry_1_36.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[0][1].LoadBitmap(".\\res\\Henry\\Henry_1\\henry_1_37.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[0][2].LoadBitmap(".\\res\\Henry\\Henry_1\\henry_1_38.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[1][0].LoadBitmap(".\\res\\Henry\\Henry_1_reverse\\henry_1_reverse_33.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[1][1].LoadBitmap(".\\res\\Henry\\Henry_1_reverse\\henry_1_reverse_32.bmp", RGB(0, 0, 0));
		JumpHeavyAttack[1][2].LoadBitmap(".\\res\\Henry\\Henry_1_reverse\\henry_1_reverse_31.bmp", RGB(0, 0, 0));
		//Knock
		Knock[0][0].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_53.bmp", RGB(0, 0, 0));
		Knock[0][1].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_54.bmp", RGB(0, 0, 0));
		Knock[0][2].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_55.bmp", RGB(0, 0, 0));
		Knock[1][0].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_56.bmp", RGB(0, 0, 0));
		Knock[1][1].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_55.bmp", RGB(0, 0, 0));
		Knock[1][2].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_54.bmp", RGB(0, 0, 0));

		Knock2[0][0].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_46.bmp", RGB(0, 0, 0));
		Knock2[0][1].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_47.bmp", RGB(0, 0, 0));
		Knock2[0][2].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_48.bmp", RGB(0, 0, 0));
		Knock2[1][0].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_43.bmp", RGB(0, 0, 0));
		Knock2[1][1].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_42.bmp", RGB(0, 0, 0));
		Knock2[1][2].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_41.bmp", RGB(0, 0, 0));

		KnockFront[0][0].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_30.bmp", RGB(0, 0, 0));
		KnockFront[0][1].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_31.bmp", RGB(0, 0, 0));
		KnockFront[0][2].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_32.bmp", RGB(0, 0, 0));
		KnockFront[0][3].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_33.bmp", RGB(0, 0, 0));
		KnockFront[0][4].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_34.bmp", RGB(0, 0, 0));
		KnockFront[0][5].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_35.bmp", RGB(0, 0, 0));
		KnockFront[0][6].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_36.bmp", RGB(0, 0, 0));
		KnockFront[1][0].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_39.bmp", RGB(0, 0, 0));
		KnockFront[1][1].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_38.bmp", RGB(0, 0, 0));
		KnockFront[1][2].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_37.bmp", RGB(0, 0, 0));
		KnockFront[1][3].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_36.bmp", RGB(0, 0, 0));
		KnockFront[1][4].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_35.bmp", RGB(0, 0, 0));
		KnockFront[1][5].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_34.bmp", RGB(0, 0, 0));
		KnockFront[1][6].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_33.bmp", RGB(0, 0, 0));

		KnockBack[0][0].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_40.bmp", RGB(0, 0, 0));
		KnockBack[0][1].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_41.bmp", RGB(0, 0, 0));
		KnockBack[0][2].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_42.bmp", RGB(0, 0, 0));
		KnockBack[0][3].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_43.bmp", RGB(0, 0, 0));
		KnockBack[0][4].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_44.bmp", RGB(0, 0, 0));
		KnockBack[0][5].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_45.bmp", RGB(0, 0, 0));
		KnockBack[0][6].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_36.bmp", RGB(0, 0, 0));
		KnockBack[1][0].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_49.bmp", RGB(0, 0, 0));
		KnockBack[1][1].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_48.bmp", RGB(0, 0, 0));
		KnockBack[1][2].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_47.bmp", RGB(0, 0, 0));
		KnockBack[1][3].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_46.bmp", RGB(0, 0, 0));
		KnockBack[1][4].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_45.bmp", RGB(0, 0, 0));
		KnockBack[1][5].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_44.bmp", RGB(0, 0, 0));
		KnockBack[1][6].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_33.bmp", RGB(0, 0, 0));

		itemNormal[0].LoadBitmap(".\\res\\Henry\\Henry_0\\henry_0_23.bmp", RGB(0, 0, 0));
		itemNormal[1].LoadBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_26.bmp", RGB(0, 0, 0));

		itemWalk[0].AddBitmap(".\\res\\Henry\\Henry_0\\henry_0_23.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Henry\\Henry_0\\henry_0_24.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Henry\\Henry_0\\henry_0_25.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Henry\\Henry_0\\henry_0_26.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Henry\\Henry_0\\henry_0_25.bmp", RGB(0, 0, 0));
		itemWalk[0].AddBitmap(".\\res\\Henry\\Henry_0\\henry_0_24.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_26.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_25.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_24.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_23.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_24.bmp", RGB(0, 0, 0));
		itemWalk[1].AddBitmap(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_25.bmp", RGB(0, 0, 0));

		itemRun[0].AddBitmap(".\\res\\Henry\\Henry_1\\henry_1_55.bmp", RGB(0, 0, 0));
		itemRun[0].AddBitmap(".\\res\\Henry\\Henry_1\\henry_1_56.bmp", RGB(0, 0, 0));
		itemRun[0].AddBitmap(".\\res\\Henry\\Henry_1\\henry_1_57.bmp", RGB(0, 0, 0));
		itemRun[0].AddBitmap(".\\res\\Henry\\Henry_1\\henry_1_56.bmp", RGB(0, 0, 0));
		itemRun[1].AddBitmap(".\\res\\Henry\\Henry_1_reverse\\henry_1_reverse_54.bmp", RGB(0, 0, 0));
		itemRun[1].AddBitmap(".\\res\\Henry\\Henry_1_reverse\\henry_1_reverse_53.bmp", RGB(0, 0, 0));
		itemRun[1].AddBitmap(".\\res\\Henry\\Henry_1_reverse\\henry_1_reverse_52.bmp", RGB(0, 0, 0));
		itemRun[1].AddBitmap(".\\res\\Henry\\Henry_1_reverse\\henry_1_reverse_53.bmp", RGB(0, 0, 0));

		itemThrow[0][0].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_27.bmp", RGB(0, 0, 0));
		itemThrow[0][1].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_28.bmp", RGB(0, 0, 0));
		itemThrow[1][0].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_22.bmp", RGB(0, 0, 0));
		itemThrow[1][1].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_21.bmp", RGB(0, 0, 0));

		itemRunThrow[0][0].LoadBitmapA(".\\res\\Henry\\Henry_1\\henry_1_58.bmp", RGB(0, 0, 0));
		itemRunThrow[0][1].LoadBitmapA(".\\res\\Henry\\Henry_1\\henry_1_26.bmp", RGB(0, 0, 0));
		itemRunThrow[1][0].LoadBitmapA(".\\res\\Henry\\Henry_1_reverse\\henry_1_reverse_51.bmp", RGB(0, 0, 0));
		itemRunThrow[1][1].LoadBitmapA(".\\res\\Henry\\Henry_1_reverse\\henry_1_reverse_23.bmp", RGB(0, 0, 0));

		Frozen[0][0].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_8.bmp", RGB(0, 0, 0));
		Frozen[0][1].LoadBitmapA(".\\res\\Henry\\Henry_0\\henry_0_9.bmp", RGB(0, 0, 0));
		Frozen[1][0].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_1.bmp", RGB(0, 0, 0));
		Frozen[1][1].LoadBitmapA(".\\res\\Henry\\Henry_0_reverse\\henry_0_reverse_0.bmp", RGB(0, 0, 0));
	}
	CharacterAnimation::~CharacterAnimation() {

	}
}
