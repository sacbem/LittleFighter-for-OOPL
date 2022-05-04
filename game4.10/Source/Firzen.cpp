#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Character.h"
#include <cmath>
namespace game_framework {
	Firzen::Firzen() {
		Initialize();
	}

	void Firzen::LoadCharacter() {
		//normal state right
		Normal[0].AddBitmap(FIRZEN_NORMAL4, RGB(0, 0, 0));
		Normal[0].AddBitmap(FIRZEN_NORMAL3, RGB(0, 0, 0));
		Normal[0].AddBitmap(FIRZEN_NORMAL2, RGB(0, 0, 0));
		Normal[0].AddBitmap(FIRZEN_NORMAL1, RGB(0, 0, 0));
		//normal state left
		Normal[1].AddBitmap(FIRZEN_NORMAL4_REVERSE, RGB(0, 0, 0));
		Normal[1].AddBitmap(FIRZEN_NORMAL3_REVERSE, RGB(0, 0, 0));
		Normal[1].AddBitmap(FIRZEN_NORMAL2_REVERSE, RGB(0, 0, 0));
		Normal[1].AddBitmap(FIRZEN_NORMAL1_REVERSE, RGB(0, 0, 0));
		//walk right
		Walk[0].AddBitmap(FIRZEN_WALK1, RGB(0, 0, 0));
		Walk[0].AddBitmap(FIRZEN_WALK2, RGB(0, 0, 0));
		Walk[0].AddBitmap(FIRZEN_WALK3, RGB(0, 0, 0));
		Walk[0].AddBitmap(FIRZEN_WALK4, RGB(0, 0, 0));
		Walk[0].AddBitmap(FIRZEN_WALK3, RGB(0, 0, 0));
		Walk[0].AddBitmap(FIRZEN_WALK2, RGB(0, 0, 0));
		//walk left
		Walk[1].AddBitmap(FIRZEN_WALK1_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(FIRZEN_WALK2_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(FIRZEN_WALK3_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(FIRZEN_WALK4_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(FIRZEN_WALK3_REVERSE, RGB(0, 0, 0));
		Walk[1].AddBitmap(FIRZEN_WALK2_REVERSE, RGB(0, 0, 0));

		//Run right
		Run[0].AddBitmap(FIRZEN_RUN1, RGB(0, 0, 0));
		Run[0].AddBitmap(FIRZEN_RUN2, RGB(0, 0, 0));
		Run[0].AddBitmap(FIRZEN_RUN3, RGB(0, 0, 0));
		Run[0].AddBitmap(FIRZEN_RUN2, RGB(0, 0, 0));
		//run left
		Run[1].AddBitmap(FIRZEN_RUN1_REVERSE, RGB(0, 0, 0));
		Run[1].AddBitmap(FIRZEN_RUN2_REVERSE, RGB(0, 0, 0));
		Run[1].AddBitmap(FIRZEN_RUN3_REVERSE, RGB(0, 0, 0));
		Run[1].AddBitmap(FIRZEN_RUN2_REVERSE, RGB(0, 0, 0));

		RunStop[0].LoadBitmapA(".\\res\\Firzen\\Firzen_1\\firzen_1_19.bmp", RGB(0, 0, 0));
		RunStop[1].LoadBitmapA(".\\res\\Firzen\\Firzen_1_reverse\\firzen_1_reverse_10.bmp", RGB(0, 0, 0));

		//jump
		Jump[0][0].LoadBitmapA(".\\res\\Firzen\\Firzen_0\\firzen_0_60.bmp", RGB(0, 0, 0));
		Jump[0][1].LoadBitmapA(".\\res\\Firzen\\Firzen_0\\firzen_0_61.bmp", RGB(0, 0, 0));
		Jump[0][2].LoadBitmapA(".\\res\\Firzen\\Firzen_0\\firzen_0_62.bmp", RGB(0, 0, 0));
		Jump[0][3].LoadBitmapA(".\\res\\Firzen\\Firzen_0\\firzen_0_63.bmp", RGB(0, 0, 0));

		Jump[1][0].LoadBitmapA(".\\res\\Firzen\\Firzen_0_reverse\\firzen_0_reverse_69.bmp", RGB(0, 0, 0));
		Jump[1][1].LoadBitmapA(".\\res\\Firzen\\Firzen_0_reverse\\firzen_0_reverse_68.bmp", RGB(0, 0, 0));
		Jump[1][2].LoadBitmapA(".\\res\\Firzen\\Firzen_0_reverse\\firzen_0_reverse_67.bmp", RGB(0, 0, 0));
		Jump[1][3].LoadBitmapA(".\\res\\Firzen\\Firzen_0_reverse\\firzen_0_reverse_66.bmp", RGB(0, 0, 0));

		Defense[0][0].LoadBitmapA(".\\res\\Firzen\\Firzen_0\\firzen_0_56.bmp", RGB(0, 0, 0));
		Defense[0][1].LoadBitmapA(".\\res\\Firzen\\Firzen_0\\firzen_0_57.bmp", RGB(0, 0, 0));
		Defense[1][0].LoadBitmapA(".\\res\\Firzen\\Firzen_0_reverse\\firzen_0_reverse_53.bmp", RGB(0, 0, 0));
		Defense[1][1].LoadBitmapA(".\\res\\Firzen\\Firzen_0_reverse\\firzen_0_reverse_52.bmp", RGB(0, 0, 0));

		Roll[0][0].LoadBitmapA(".\\res\\Firzen\\Firzen_0\\firzen_0_58.bmp", RGB(0, 0, 0));
		Roll[0][1].LoadBitmapA(".\\res\\Firzen\\Firzen_0\\firzen_0_59.bmp", RGB(0, 0, 0));
		Roll[0][2].LoadBitmapA(".\\res\\Firzen\\Firzen_0\\firzen_0_69.bmp", RGB(0, 0, 0));
		Roll[1][0].LoadBitmapA(".\\res\\Firzen\\Firzen_0_reverse\\firzen_0_reverse_51.bmp", RGB(0, 0, 0));
		Roll[1][1].LoadBitmapA(".\\res\\Firzen\\Firzen_0_reverse\\firzen_0_reverse_50.bmp", RGB(0, 0, 0));
		Roll[1][2].LoadBitmapA(".\\res\\Firzen\\Firzen_0_reverse\\firzen_0_reverse_60.bmp", RGB(0, 0, 0));
	}

	Firzen::~Firzen() {

	}
}
